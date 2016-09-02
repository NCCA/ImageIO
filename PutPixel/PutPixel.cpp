#include <Magick++.h>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <algorithm>



int main()
{
  constexpr unsigned int           WIDTH     = 800;
  constexpr unsigned int           HEIGHT    = 800;
  constexpr auto                   imageSize = WIDTH * HEIGHT * 3 * sizeof(unsigned char);
  // c++ 11
  //std::unique_ptr<unsigned char[]> image( new unsigned char[imageSize]);
  // c++ 14
  std::unique_ptr<unsigned char[]> image=std::make_unique<unsigned char []>(imageSize);

  // set pixel as lambda
  auto setPixel = [&image](size_t _x, size_t _y, unsigned char _r, unsigned char _g, unsigned char _b)
  {
    size_t index           = (_y * WIDTH * 3) + _x * 3;
    image.get()[index]     = _r;
    image.get()[index + 1] = _g;
    image.get()[index + 2] = _b;
  };

  size_t checkSize=10;

  for(size_t y=0; y<HEIGHT; ++y)
	{
    for(size_t x=0; x<WIDTH; ++x)
		{
      if( (x /checkSize + y /checkSize) % 2  < 1 )
			{
        setPixel(x,y,255,0,0);
			}
			else
			{
        setPixel(x,y,255,255,255);
			}
		}
	}

	Magick::Image output(WIDTH,HEIGHT,"RGB",Magick::CharPixel,image.get());
	output.depth(16);
  output.write("Test.jpg");
	return EXIT_SUCCESS;
}
