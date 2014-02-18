#pragma once
class Rectangle
{
public:
	double x;
	double y;
	double width;
	double height;

	Rectangle(double X, double Y, double Width, double Height);
	virtual ~Rectangle(void);
	bool isIntersecting(Rectangle R);
	bool isInside(double X, double Y);
};

