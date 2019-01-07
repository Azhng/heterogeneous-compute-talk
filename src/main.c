#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

#define MEM_SIZE (128)
#define MAX_SOURCE_SIZE (0x100000)

int main(void){
    cl_device_id device_id = NULL;
    cl_context context = NULL;
    cl_command_queue command_queue = NULL;
    cl_mem memobj = NULL;
    cl_program program = NULL;
    cl_kernel kernel = NULL;
    cl_platform_id platform_id = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret; 

    char string[MEM_SIZE];

    FILE * fp; 
    char filename[] = "./kernels/hello.cl";
    char *source_str; 
    size_t source_size; 

    fp = fopen(filename, "r");
    if(!fp){
        fprintf(stderr, "Failed to load kernel\n");
        exit(1);
    }

    source_str = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);

    // get platform and devcie info 
    ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);

    // create context 
    context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

    // create command queue
    command_queue = clCreateCommandQueueWithProperties(context, device_id, 0, &ret);

    // create memory buffer 
    memobj = clCreateBuffer(context, CL_MEM_READ_WRITE, MEM_SIZE * sizeof(char), NULL, &ret);

    // create kernel program from source 
    program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t*)&source_size, &ret);

    // build kernel program 
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

    // create opencl kernel 
    kernel = clCreateKernel(program, "hello", &ret);    

    // set opencl kernel parameter 
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj);

    size_t globalWorkSize [1] ;
    globalWorkSize[0] = 4;
    size_t localWorkSize [1] ;
    localWorkSize[0] = 2;

    // execute opencl kernel 
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);

    // copy result from memory buffer 
    ret = clEnqueueReadBuffer(command_queue, memobj, CL_TRUE, 0, MEM_SIZE * sizeof(char), string, 0, NULL, NULL);

    // displaying result 
    puts(string);

    // clean up 
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(memobj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);

    free(source_str);
    return 0;
}

