#include <cstdint>
#include <cstdio>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb_image.h>
#include <stb_image_write.h>

#include "./utils.hpp"

int main() {
  int width, height, bpp;
  long double theta = 22.0f / 7.0f / 3.0f;

  uint8_t* img = stbi_load("./resources/cat.jpg", &width, &height, &bpp, 1);
  uint8_t* output = (uint8_t*)malloc(sizeof(uint8_t) * width * height);
  memset(output, 0, width * height);

  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  int x0 = width / 2;
  int y0 = -height / 2;

  // covnert to 2d array representation
  uint8_t (*mat)[640] = (uint8_t (*)[640])img;
  uint8_t (*omat)[640] = (uint8_t (*)[640])output;

  for (int row=0; row<480; ++row) {
    for (int col=0; col<640; ++col) {
      //printf("col: %d, row: %d, val: %d\n", col, row, mat[row][col]);
      int x = col * cos(theta) - row * sin(theta) + x0;
      int y = col * sin(theta) + row * cos(theta) + y0;
      if (x < 0 || x >= width || y < 0 || y >= height) {
        continue;
      }
      //printf("x: %d, y: %d - ", x, y);
      omat[row][col] = mat[y][x];
    }
    //printf("\n");
  }

  clock_gettime(CLOCK_MONOTONIC, &end);
  print_timediff("computation time: ", start, end);

  stbi_write_png("out_cpu.png", width, height, 1, output, width);

  free(output);
  stbi_image_free(img);

  return 0;
}
