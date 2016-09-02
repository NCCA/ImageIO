#include <iostream>
#include <Magick++.h>
#include <iostream>
#include <math.h>
#include <cstdlib>

// define widht and height of image
const static int WIDTH=720;
const static int  HEIGHT=576;

int main()
{
  // allocate and array of char for image
  // where data is packed in RGB format 0-255 where 0=no intensity
  // 255 = full intensity
  unsigned char  *image = new unsigned char [WIDTH*HEIGHT*3*sizeof(char)];
  // index into our image array
  unsigned long int index=0;
  // now loop for width and height of image and fill in
  for(int y=0; y<HEIGHT; ++y)
  {
    for(int x=0; x<WIDTH; ++x)
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
  Magick::Image output(WIDTH,HEIGHT,"RGB",Magick::CharPixel,image);
  // set the output image depth to 16 bit
  output.depth(16);
  // write the file
  output.write("Test.pdf");
  // delete the image data.
  delete [] image;
  return EXIT_SUCCESS;
}
