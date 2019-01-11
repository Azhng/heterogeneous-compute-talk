#define CL_TARGET_OPENCL_VERSION 220

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb_image.h>
#include <stb_image_write.h>

#include "./utils.hpp"

int main() {
    try {
      // Get list of OpenCL platforms.
      std::vector<cl::Platform> platforms;
      cl::Platform::get(&platforms);

      if (platforms.empty()) {
          std::cerr << "OpenCL platformss not found." << std::endl;
          return 1;
      }

      cl::Context context;
      std::vector<cl::Device> devices;

      for(auto p : platforms) {
        if (!devices.empty()) {
          break;
        }
        std::vector<cl::Device> pldev;

        try {
          p.getDevices(CL_DEVICE_TYPE_GPU, &pldev);

          for (auto d = pldev.begin(); devices.empty() && d != pldev.end(); d++) {
            if (!d->getInfo<CL_DEVICE_AVAILABLE>()) continue;

            std::string ext = d->getInfo<CL_DEVICE_EXTENSIONS>();
            devices.push_back(*d);
            context = cl::Context(devices);
          }
        } catch (...) {
          devices.clear();
        }
      }

      if (devices.empty()) {
        std::cerr << "GPU not found." << std::endl;
        return 1;
      }

      std::cout << "Device found: " << devices[0].getInfo<CL_DEVICE_NAME>() << std::endl;

      // Create command queue.
      cl::CommandQueue queue(context, devices[0]);

      // Read and compile OpenCL program for found devices.
      std::ifstream srcStream("./kernels/rotate.cl");
      if (!srcStream.good()) {
        throw std::runtime_error{"unable to read kernel"};
      }

      std::stringstream src;
      src << srcStream.rdbuf();
      std::string srcStr = src.str();

      cl::Program program(context, cl::Program::Sources(
            1, std::make_pair(srcStr.c_str(), srcStr.length())
            ));

      try {
        program.build(devices);
      } catch (const cl::Error&) {
        std::cerr
          << "OpenCL compilation error" << std::endl
          << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(devices[0])
          << std::endl;
        return 1;
      }

      cl::Kernel rotate(program, "rotation");

      // Prepare input data.
      int width, height, bpp;

      float* inputImageRaw = stbi_loadf("./resources/cat.jpg", &width, &height, &bpp, 1);
      cl::Image2D inputImage(context,
          CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
          cl::ImageFormat(CL_R, CL_FLOAT),
          width,
          height,
          0,
          (void*)inputImageRaw);

      cl::Image2D outputImage(context,
          CL_MEM_WRITE_ONLY,
          cl::ImageFormat(CL_R, CL_FLOAT),
          width,
          height,
          0,
          nullptr);

      // Set kernel parameters.
      cl_int status;
      status = rotate.setArg(0, inputImage);
      status |= rotate.setArg(1, outputImage);
      status |= rotate.setArg(2, width);
      status |= rotate.setArg(3, height);
      status |= rotate.setArg(4, 45.0f);

      if (status) {
        throw std::runtime_error{"unable to set argument"};
      }

      struct timespec start, end;
      clock_gettime(CLOCK_MONOTONIC, &start);

      // Launch kernel on the compute device.
      queue.enqueueNDRangeKernel(rotate, cl::NullRange, cl::NDRange(width, height), cl::NDRange(8, 8));

      // Get result back to host.
      float* outputRaw = (float*)malloc(sizeof(float) * width * height);

      // who the hell designed this stupid fucking API
      cl::size_t<3> origin;
      origin[0] = 0;
      origin[1] = 0;
      origin[2] = 0;

      cl::size_t<3> region;
      region[0] = width;
      region[1] = height;
      region[2] = 1;

      queue.enqueueReadImage(outputImage, CL_TRUE, origin, region, 0, 0, outputRaw);

      clock_gettime(CLOCK_MONOTONIC, &end);
      print_timediff("computation time: ", start, end);

      stbi_write_hdr("out_gpu.hdr", width, height, 1, outputRaw);

      free(outputRaw);
      stbi_image_free(inputImageRaw);
    } catch (const cl::Error &err) {
      std::cerr
          << "OpenCL error: "
          << err.what() << "(" << err.err() << ")"
          << std::endl;
      return 1;
    }
  return 0;
}
