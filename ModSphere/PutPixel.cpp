#include <iostream>
#include <Magick++.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <boost/scoped_array.hpp>

const unsigned int WIDTH=800;
const unsigned int HEIGHT=800;

void setPixel(char *_data,unsigned  int _x,unsigned int _y, char _r,char _g, char _b)
{
	unsigned int index=(_y*WIDTH*3)+_x*3;
	_data[index]=_r;
	_data[index+1]=_g;
	_data[index+2]=_b;
}

void setBGColour(char *_data,char _r, char _g, char _b)
{
	for(unsigned int y=0; y<HEIGHT; ++y)
	{
		for(unsigned int x=0; x<WIDTH; ++x)
		{
				setPixel(_data,x,y,_r,_g,_b);
		}
	}
}

// code modified from Computer Graphics with OpenGL F.S. Hill
// get the value on the sphere at co-ord s,t
float fakeSphere(float _s, float _t)
{
	float r=sqrt((_s-0.5)*(_s-0.5)+(_t-0.5)*(_t-0.5));
	if(r<0.5)
	{
		return 1-r/0.5;
	}
	else
	{
		return 1.0;
	}
}

int main()
{
	boost::scoped_array<float > image(new float [WIDTH*HEIGHT*3*sizeof(float)]);

	// index into our data structure
	unsigned long int index=0;
	// Our step in texture space from 0-1 within the width of the image
	float sStep=1.0/WIDTH;
	float tStep=1.0/HEIGHT;
	// actual S,T value for texture space
	float s=0.0;
	float t=0.0;
	float ss,tt;
	// loop for the image dimensions
	for(int y=0; y<HEIGHT; y++)
	{
		for(int x=0; x<WIDTH; x++)
		{
			ss=fmod(s*8,1.0);
			tt=fmod(t*8,1.0);
			// fill the data values with sphere values
			image[index]=fakeSphere(ss,tt);
			image[index+1]=fakeSphere(ss,tt);
			image[index+2]=fakeSphere(ss,tt);
			// update the S value
			s+=sStep;
			// step to the next image index
			index+=3;
		}
		// update the T value
		t+=tStep;
		// reset S to the left hand value
		s=0.0;
	}
	Magick::Image output(WIDTH,HEIGHT,"RGB",Magick::FloatPixel,image.get());
	output.depth(16);
	output.write("Test.png");
	return EXIT_SUCCESS;
}
