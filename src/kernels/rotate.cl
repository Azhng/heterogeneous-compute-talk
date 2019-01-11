__constant sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_FILTER_LINEAR | CLK_ADDRESS_CLAMP;

__kernel void rotation(
    __read_only image2d_t inputImage,
    __write_only image2d_t outputImage,
    int imageWidth,
    int imageHeight,
    float theta
    ) {
  int x = get_global_id(0);
  int y = get_global_id(1);

  float x0 = imageWidth / 2.0f;
  float y0 = imageHeight / 2.0f;

  int xprime = x-x0;
  int yprime = y-x0;

  float sinTheta = sin(theta);
  float cosTheta = cos(theta);

  float2 readCoords;
  readCoords.x = xprime * cosTheta - yprime * sinTheta + x0;
  readCoords.y = xprime * sinTheta + yprime * cosTheta + y0;

  float value;
  value = read_imagef(inputImage, sampler, readCoords).x;

  write_imagef(outputImage, (int2)(x, y), (float4)(value, 0.f, 0.f, 0.f));
}
