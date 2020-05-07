#include <OpenImageIO/imageio.h>
#include <iostream>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <memory>
const unsigned int WIDTH=800;
const unsigned int HEIGHT=800;


int main()
{
  std::unique_ptr<unsigned char []> image(new unsigned char [WIDTH*HEIGHT*3*sizeof(unsigned char)]);

// set pixel as lambda
  auto setPixel = [&image](size_t _x, size_t _y, unsigned char _r, unsigned char _g, unsigned char _b)
  {
    size_t index           = (_y * WIDTH * 3) + _x * 3;
    image.get()[index]     = _r;
    image.get()[index + 1] = _g;
    image.get()[index + 2] = _b;
  };

  // setBGColour
    auto setBGColour = [&image](unsigned char _r, unsigned char _g, unsigned char _b)
    {
      size_t end =          WIDTH*HEIGHT*3*sizeof(unsigned char);
      for(size_t index=0; index<end; index+=3)
      {
        image.get()[index]     = _r;
        image.get()[index + 1] = _g;
        image.get()[index + 2] = _b;
      }
    };
	// clear to white
  setBGColour(255,255,255);


  for(size_t y=0; y<HEIGHT; ++y)
	{
    for(size_t x=0; x<WIDTH; ++x)
		{
			if( (y%20) && (x%20))
			{
        setPixel(x,y,255,0,0);
			}
			else
			{
        setPixel(x,y,255,255,255);
			}
		}
	}

  using namespace OIIO;


  std::unique_ptr<ImageOutput> out = ImageOutput::create ("test.tiff");
  if(!out)
  {
    std::cout<<"error with image\n";
    return EXIT_FAILURE;
  }
  ImageSpec spec (WIDTH,HEIGHT,3, TypeDesc::UCHAR);
  out->open("test.tiff",spec);
  out->write_image(TypeDesc::UCHAR,image.get());
  out->close();

	return EXIT_SUCCESS;
}
