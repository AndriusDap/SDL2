#include "Includes.h"

class Glyph {
public:
	float x;
	float y;
	float width;
	float height;
	float xoffset;
	float yoffset;
	float xadvance;
	Glyph()
	{}

	Glyph(int _x, int _y, int _width, int _height, int _xoffset, int _yoffset, int _xadvance)
	{
		float pageSize = 1024.0f;

		x = _x / pageSize; 
		y = _y / pageSize; 
		width = _width / pageSize; 
		height = _height / pageSize; 
		xoffset = _xoffset / pageSize; 
		yoffset = _yoffset / pageSize; 
		xadvance = _xadvance / pageSize;
	}

};


























