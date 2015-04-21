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


int main()
{
	boost::scoped_array<char > image(new char [WIDTH*HEIGHT*3*sizeof(char)]);

	// clear to white
	setBGColour(image.get(),255,255,255);


	for(int y=0; y<HEIGHT; ++y)
	{
		for(int x=0; x<WIDTH; ++x)
		{
			if( (y%20) && (x%20))
			{
				setPixel(image.get(),x,y,255,0,0);
			}
			else
			{
					setPixel(image.get(),x,y,255,255,255);
			}
		}
	}

	Magick::Image output(WIDTH,HEIGHT,"RGB",Magick::CharPixel,image.get());
	output.depth(16);
	output.write("Test.png");
	return EXIT_SUCCESS;
}
