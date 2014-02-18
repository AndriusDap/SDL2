#include "Rectangle.h"


Rectangle::Rectangle(double X, double Y, double Width, double Height)
{
	x = X;
	y = Y;
	width = Width;
	height = Height;
}

inline bool isInRange(double value, double point, double width)
{
	return (value >= point) && (value <= point + width); 
}

bool Rectangle::isIntersecting(Rectangle R)
{
	bool intersectsX = isInRange(x, R.x, R.width) || isInRange(R.x, x, width);
	bool intersectsY = isInRange(y, R.y, R.height) || isInRange(R.y, y, height);
	return intersectsX && intersectsY;
}

bool Rectangle::isInside(double X, double Y)
{
	return isInRange(X, x, width) && isInRange(Y, y, height);
}


Rectangle::~Rectangle(void)
{

}
