#include <iostream>
#include <OpenImageIO/imageio.h>

#include <cmath>
#include <memory>
#include <cstdlib>

// define widht and height of image
constexpr int WIDTH=720;
constexpr int  HEIGHT=576;

int main()
{
  // allocate and array of char for image
  // where data is packed in RGB format 0-255 where 0=no intensity
  // 255 = full intensity
  std::unique_ptr<unsigned char  []>image( new unsigned char [WIDTH*HEIGHT*3*sizeof(char)]);
  // index into our image array
  size_t index=0;
  // now loop for width and height of image and fill in
  for(size_t y=0; y<HEIGHT; ++y)
  {
    for(size_t x=0; x<WIDTH; ++x)
    {
      // set red channel to full
      image[index]=255;
      // G&B to off
      image[index+1]=0;
      image[index+2]=0;
      // now skip to next RGB block
      index+=3;
    } // end of width loop
  } // end of height loop

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

