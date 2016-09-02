#include <iostream>
#include <Magick++.h>
#include <boost/scoped_array.hpp>
#include <cstdio>

// for more details see this site some greate stuff here (this code was modified from it)
// http://www.exploringbinary.com/ten-ways-to-check-if-an-integer-is-a-power-of-two-in-c/
bool isPowerOfTwo (unsigned int _x)
{
 while (((_x % 2) == 0) && _x > 1) /* While x is even and > 1 */
 {
     _x /= 2;
 }
  return (_x == 1);
}




void getRGB(
            const unsigned char *_data,
            int _x, int _y, unsigned char &o_r, unsigned char &o_g,
            unsigned char &o_b, int _width
            )
{
  o_r=_data[((_width*3)*_y)+(_x*3)];
  o_g=_data[((_width*3)*_y)+(_x*3)+1];
  o_b=_data[((_width*3)*_y)+(_x*3)+2];
}

int main(int argc, char **argv)
{

  if(argc <2 )
  {
    std::cerr <<"Usage MipMap [filename]\n";
    exit(EXIT_SUCCESS);
  }

  Magick::Image image;

  image.read(argv[1]);

  int width=image.size().width();
  int height=image.size().height();
  std::cout<<"Image size is "<<width<<" "<<height<<"\n";
  bool hasTransparency=image.matte();
  // check that the images are powers of two
  if(!isPowerOfTwo(width) && !isPowerOfTwo(height))
  {
    std::cout<<"Both width and height must be powers of 2 for this to work\n";
    exit(EXIT_FAILURE);
  }
  // only going to deal with RGB for now
  unsigned char *sourceImage= new unsigned char[width*height*3];

  unsigned int i=-1;
  // this is slow and we could use the image.getPixels to acces the raw data, however this will mean
  // we have to manage bits per pixe and other type information the method below is easy to use
  // as the quantum will always be converted for us to the correct type (uchar)
  Magick::Color c;
  for(int h=0; h<height; ++h)
  {
    for(int w=0; w<width; ++w)
    {
      c=image.pixelColor(w,h);
      sourceImage[++i]= c.redQuantum();
      sourceImage[++i]= c.greenQuantum();
      sourceImage[++i]= c.blueQuantum();
    }
  }

  // loop until we run out of mip levels
  int mipLevel=2;

  for(int ml=width/2; ml>=2; ml/=2)
  {
    unsigned char *destImage = new unsigned char[(width/2*height/2)*3];
    i=0;
    unsigned char r1,g1,b1;
    unsigned char r2,g2,b2;
    unsigned char r3,g3,b3;
    unsigned char r4,g4,b4;

    // now loop and average the source image data into the new one
    for(int h=0; h<height/mipLevel; ++h)
    {
      for(int w=0; w<width/mipLevel; ++w)
      {

        int dw=w*mipLevel;
        int dh=h*mipLevel;

        getRGB(sourceImage,dw,dh,r1,g1,b1,width);
        getRGB(sourceImage,dw+1,dh,r2,g2,b2,width);
        getRGB(sourceImage,dw,dh+1,r3,g3,b3,width);
        getRGB(sourceImage,dw+1,dh+1,r4,g4,b4,width);

        destImage[i]=sqrt ((r1*r1+r2*r2+r3*r3+r4*r4)/4);
        destImage[i+1]=sqrt ((g1*g1+g2*g2+g3*g3+g4*g4)/4);
        destImage[i+2]=sqrt ((b1*b1+b2*b2+b3*b3+b4*b4)/4);
//        destImage[i]= ((r1+r2+r3+r4)/4);
//        destImage[i+1]= ((g1+g2+g3+g4)/4);
//        destImage[i+2]= ((b1+b2+b3+b4)/4);

        i+=3;
       }
    }

    // write out image and close
    Magick::Image output(width/mipLevel,height/mipLevel,"RGB",Magick::CharPixel,destImage);
    output.depth(16);
    char str[40];
    static int f=0;
    sprintf(str,"%02dmipmap%dx%d.png",f++, ml,ml);
    output.write(str);
    mipLevel*=2;
}// end of each mip

}
