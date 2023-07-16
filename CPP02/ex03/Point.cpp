#include "Point.hpp"

Point::Point() : _x(0), _y(0) {}

Point::Point(const float x, const float y) : _x(x), _y(y) {}

Point::Point(const Point &src) : _x(src._x), _y(src._y) {}

Point &Point::operator=(const Point &object)
{
	Point dup(object);
	return dup;
}

Point::~Point() {}

Fixed Point::getX(void) const
{
	return _x;
}

Fixed Point::getY(void) const
{
	return _y;
}
