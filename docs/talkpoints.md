# Introduction to Heterogeneous Computing

## What is Heterogenous computing

Essentially, performing computations on different architectures, such as x86, arm, MIPS, GCN etc. that might involve different hardwares. Different hardwares have different capabilities, e.g. (CPU, GPU etc.), and this is the reason why Heterogeneous computing is desirable. 

### Demo #1
_run the demo of cpu vs gpu compute_

## The challenges of heterogenous computing

Well, it turns out, it's kinda hard to do it.

* How do we effectively schedule different jobs onto different hardwares.
* How do we write programs that runs on different architecture, (sometimes very different)
* How do different architectures in a single system communicate (and synchronize)

## Solution - OpenCL

OpenCL - Open Computing Language. What OpenCL provides is in fact a concrete definition of:
* Standard language that can be used to define computation across all types of hardware
* Execution / Concurrency Model
* Memory Model (Host & Device)

## Command Queue & Host-Device Model
* Define: Host
* Define: Device 
* Command Queue
  * IO commands or launching Kernels
* Define Kernels
* // source code walk through of hello.cpp
* // source code walk through of add_gpu.cpp

## Hardware mapping
* CPU
* GPU

### Demo #2
Blackbox demo: image rotation probably


// ========================================================= //
### host-device architecture
* host and device are abstracted concept rather than a concrete one.
* Host
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

### Hardware mapping

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

