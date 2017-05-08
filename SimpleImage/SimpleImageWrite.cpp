#include <iostream>
#include <Magick++.h>
#include <iostream>
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
  // now create an image data block
  Magick::Image output(WIDTH,HEIGHT,"RGB",Magick::CharPixel,image.get());
  // set the output image depth to 16 bit
  output.depth(16);
  // write the file
  output.write("Test.tiff");
  
  return EXIT_SUCCESS;
}

