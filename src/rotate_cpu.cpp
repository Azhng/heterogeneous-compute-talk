#include <cstdint>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb_image.h>
#include <stb_image_write.h>

int main() {
  int width, height, bpp;
  uint8_t* img = stbi_load("./resources/cat.jpg", &width, &height, &bpp, 1);

  stbi_write_png("out.png", width, height, 1, img, width);
  stbi_image_free(img);

  return 0;
}
