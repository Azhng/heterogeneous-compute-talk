# Introduction to Heterogeneous Computing

Talk slide [link](https://docs.google.com/presentation/d/18HCdxBnlxYUKSPgIGO4HGV6BKZPRFhG8Meaa-DfUARg/edit?usp=sharing)

## Build instruction:

```bash
cd /path/to/project/root
mkdir build
cd build
cmake ..
make
```

This builds 5 executables:
* `hello` => a simple hello world example
* `add_cpu` => perform arithmetic operations on a large array using CPU
* `add_gpu` => perform same operation using GPU
* `rotate_cpu` => rotate an image using CPU
* `rotate_gpu` => same operation using GPU
