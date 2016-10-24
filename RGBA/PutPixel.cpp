#include <Magick++.h>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <algorithm>


int main()
{
  constexpr unsigned int WIDTH      = 800;
  constexpr unsigned int HEIGHT     = 800;
  constexpr unsigned int pixelDepth = 4;
  constexpr auto         imageSize  = WIDTH * HEIGHT * pixelDepth * sizeof(unsigned char);
  // c++ 11
  //std::unique_ptr<unsigned char[]> image( new unsigned char[imageSize]);
  // c++ 14
  std::unique_ptr<unsigned char[]> image = std::make_unique<unsigned char[]>(imageSize);


  // set pixel as lambda
  auto setPixel = [&image](size_t _x, size_t _y, unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) {
    size_t index           = (_y * WIDTH * pixelDepth) + _x * pixelDepth;
    image.get()[index]     = _r;
    image.get()[index + 1] = _g;
    image.get()[index + 2] = _b;
    image.get()[index + 3] = _a;
  };
  // set background as lambda

  auto setBackground = [&image](unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) {
    auto start = image.get();
    auto end   = image.get() + imageSize;
    while (start != end)
    {
      *start       = _r;
      *(start + 1) = _g;
      *(start + 2) = _b;
      *(start + 3) = _a;
      start += pixelDepth;
    }
  };


  size_t checkSize = 10;
  setBackground(0, 0, 0, 0);

  for (size_t y = 200; y < 600; ++y)
  {
    for (size_t x = 200; x < 600; ++x)
    {
      if ((x / checkSize + y / checkSize) % 2 < 1)
      {
        setPixel(x, y, 255, 0, 0, 0);
      }
      else
      {
        setPixel(x, y, 255, 255, 255, 0);
      }
    }
  }

  Magick::Image output(WIDTH, HEIGHT, "RGBA", Magick::CharPixel, image.get());
  output.depth(16);
  output.write("Test.jpg");
  return EXIT_SUCCESS;
}
