#define CL_TARGET_OPENCL_VERSION 220

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>


int main() {
    const size_t N = 1 << 20;

    try {
      // Get list of OpenCL platforms.
      std::vector<cl::Platform> platform;
      cl::Platform::get(&platform);

      if (platform.empty()) {
          std::cerr << "OpenCL platforms not found." << std::endl;
          return 1;
      }

      cl::Context context;
      std::vector<cl::Device> device;

      for(auto p = platform.begin(); device.empty() && p != platform.end(); p++) {
        std::vector<cl::Device> pldev;

        try {
          p->getDevices(CL_DEVICE_TYPE_GPU, &pldev);

          for (auto d = pldev.begin(); device.empty() && d != pldev.end(); d++) {
            if (!d->getInfo<CL_DEVICE_AVAILABLE>()) continue;

            std::string ext = d->getInfo<CL_DEVICE_EXTENSIONS>();
            device.push_back(*d);
            context = cl::Context(device);
          }
        } catch (...) {
          device.clear();
        }
      }

      if (device.empty()) {
        std::cerr << "GPU not found." << std::endl;
        return 1;
      }

      std::cout << "Device found: " << device[0].getInfo<CL_DEVICE_NAME>() << std::endl;

      // Create command queue.
      cl::CommandQueue queue(context, device[0]);

      // Read and compile OpenCL program for found device.
      std::ifstream srcStream("./kernels/add.cl");
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
        program.build(device);
      } catch (const cl::Error&) {
        std::cerr
          << "OpenCL compilation error" << std::endl
          << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device[0])
          << std::endl;
        return 1;
      }

      cl::Kernel add(program, "add");

      // Prepare input data.
      std::vector<float> a(N, 1);
      std::vector<float> b(N, 2);
      std::vector<float> c(N);

      // Allocate device buffers and transfer input data to device.
      cl::Buffer A(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
        a.size() * sizeof(float), a.data());

      cl::Buffer B(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
        b.size() * sizeof(float), b.data());

      cl::Buffer C(context, CL_MEM_READ_WRITE,
        c.size() * sizeof(float));

      // Set kernel parameters.
      add.setArg(0, static_cast<cl_ulong>(N));
      add.setArg(1, A);
      add.setArg(2, B);
      add.setArg(3, C);

      // Launch kernel on the compute device.
      queue.enqueueNDRangeKernel(add, cl::NullRange, N, cl::NullRange);

      // Get result back to host.
      queue.enqueueReadBuffer(C, CL_TRUE, 0, c.size() * sizeof(float), c.data());

      // Should get '3' here.
      std::cout << c[42] << std::endl;
    } catch (const cl::Error &err) {
      std::cerr
          << "OpenCL error: "
          << err.what() << "(" << err.err() << ")"
          << std::endl;
      return 1;
  }
}
