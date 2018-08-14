# Introduction to GPU computing (via OpenCL)

## *What* is GPU computing and *why* is GPU computing?

## Overall introduction to OpenCL

* host-device architecture
    * emphasize that host and device are abstracted concept rather than a concrete one.
    * what is a host
        * usually a regular x86 program (or arm depending on the platform)
        * runs on a general purpose device (most of the time, CPU). Such device usually is optmized for efficient control flows rather than raw computation power. 2 ~ 8 computation units.
        * example: a web server, CLI/GUI program, mobile application.
    * what is a device
        * it is perfectly valid that in an OpenCL program to have both host and the device mapped to the same CPU.
        * it is also valid that a single program will have multiple devices.
        * where the _kernel_ is going to be ran.
            * _kernel_ is the program that runs on device.
            * it's called _kernel_ than _program_ since in OpenCL, device adapted a different memory model than host memory model. (this is usally due to different architecture of the devices. E.g. GPU, FPGA, ASIC)
            * this is enable programmers to utilize specialized hardwares in different architectures to speed up the computation.
            * we write _kernels_ in a C/C++ like language.
    * how do they work together (command queue)
        * the foundation of OpenCL concurrency model.
        * each command queue corresponds to a single device
            * when there exists multiple devices, multiple command queue is required
        * enables asychronous programming model
        * completions or other signals are exposed through _Events_
            * callback can be register to events
        * command queues contains sequence of computation to be performed on the device
            * data read / write
            * queueing kernel
        * both host and device can append operation to the command queue
        * the command queue can be executed out of order on some supported platforms if specified

# Hardware mapping (overview, skip through the details)

OpenCL is designed to run on top of devices with various form factors, such as CPU, GPU, FPGA or ASIC. However, to fully utilize the potential of the particular platform, it is up to the programmer to exploit the special hardwares present in each individual device.

For example, most of the GPU contains high brandwidth, low latency programmable scratchpad memory, (e.g. AMD's LDS) which can significantly improve memory I/O performance. Or in some other cases, by limiting the size of local buffer of each kernel, the hardware scheduler can multiplex more kernel instances on top of a single compute unit.

It is important for developers to understand the underlying architecture that they are developing against, rather than fully relying on the compiler to perform all the optimizations.

* CPU
    * essentially a thread pool where operations are asychronously posted to the thread pool and the result is being computed
* GPU
    * High throughput design. Hence different techniques are required to efficiently use the hardware.
        * GPU threading => _wavefront_ (AMD) or _warp_ (Nvidia)
        * Hardware controlled multithreading, utilizing the high level of parallalism to cover the high latency come with the high throughput design.
    * Different memory model.
    * CU (can multiplex 40x wavefronts on a single CU) -> SIMD units (4x SIMD unit in GCN) -> SIMD lane (or vALU, 16x vALU in GCN)

# Live demo

95% speedup (between naive implementation vs implementation exploiting memory access pattern)
Showing three different programs that perform exact same computation.
Choosing between FFT or Surf image clustering
1. regular x86 program 
2. naive GPU implementation
3. GPU implementation sped up by exploiting specialized hardware

# Beyond

OpenCL (its kernal language) has been frequently used as the compilation target from other higher level languages. (such as Python and Ruby) This enables developers to take advantage of the language features in those languages well still be able to develop scalable computation intensive software.
