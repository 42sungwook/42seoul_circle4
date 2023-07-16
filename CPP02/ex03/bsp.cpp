#include "Point.hpp"

static int calculateOrientation(const Point &p1, const Point &p2, const Point &p3)
{
	Fixed value = (p2.getY() - p1.getY()) * (p3.getX() - p2.getX()) - (p2.getX() - p1.getX()) * (p3.getY() - p2.getY());
	if (value == 0)
		return 0; // Collinear
	else if (value > 0)
		return 1; // Clockwise
	else
		return 2; // Counterclockwise
}

// Function to check if a point is inside a triangle
bool isPointInsideTriangle(const Point &p, const Point &p1, const Point &p2, const Point &p3)
{
	int orientation1 = calculateOrientation(p1, p2, p);
	int orientation2 = calculateOrientation(p2, p3, p);
	int orientation3 = calculateOrientation(p3, p1, p);

	// The point is inside the triangle if all orientations are the same
	return (orientation1 == orientation2 && orientation2 == orientation3);
}