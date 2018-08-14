# Scope
A very specific narrow topic within GPGPU computing (implemented using OpenCL / CUDA)

# Potential topics

* OpenCL: Introduction
    * Command Queue model
    * Host memory model
        * opencl native memory types 
        * shared virtual memory
    * Device memory model
        * global memory
        * local memory
        * constant memory
        * private memory
    * Kernel execution domain 
        * work item 
        * work group
        * events
        * out-of-order command queue
        * use event to implement kernel dependency
    * Synchronization techniques
        * barriers
        * fences
        * atomics
        * memory ordering

* OpenCL: Implementation on different hardware
    * Multi-core CPU
        * multiplexing work group on a single physical GPU
        * vectorization
    * GPU
        * GPU threading
        * Overall Sea Island ISA
        * SIMD unit mapping to work items & work groups


* OpenCL: live demo - 95% efficiency improvement
    * Image clustering example from the book
        * naive CPU implementation
        * naive GPU implementation
        * GPU implementation with coalesced memory
        * GPU implementation with vectorization
        * GPU implementation with local memory (programmable scratch pad memory)
        * GPU implementation with constant memory
    * FFT implementation
