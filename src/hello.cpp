#define CL_TARGET_OPENCL_VERSION 220

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>

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
          p.getDevices(CL_DEVICE_TYPE_ALL, &pldev);

          for (auto d = pldev.begin(); devices.empty() && d != pldev.end(); d++) {
            if (!d->getInfo<CL_DEVICE_AVAILABLE>()) continue;

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
      std::ifstream srcStream("./kernels/hello.cl");
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

      cl::Kernel add(program, "hello");

      // Allocate device buffers and transfer input data to device.
      cl::Buffer S(context, CL_MEM_READ_WRITE, 13 * sizeof(char));

      // Set kernel parameters.
      add.setArg(0, S);

      // Launch kernel on the compute device.
      queue.enqueueNDRangeKernel(add, cl::NullRange, 4, 2);

      // Get result back to host.
      char data[13];
      queue.enqueueReadBuffer(S, CL_TRUE, 0, 13 * sizeof(char), data);

      // Should get '3' here.
      std::cout << data << std::endl;
    } catch (const cl::Error &err) {
      std::cerr
          << "OpenCL error: "
          << err.what() << "(" << err.err() << ")"
          << std::endl;
      return 1;
  }
}
