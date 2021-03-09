#include "geometry.h"
#include <math.h>

#define PI   3.14159265358979323846

Point::Point(int x, int y)
{
	SetPoint(x, y);
}

Point::Point()
{
	SetPoint(0, 0);
}

void Point::SetPoint(int x, int y)
{
	px = x;
	py = y;
}


Point::Point(const Point& pt)
{
	px = pt.px;
	py = pt.py;
}

Point& Point::operator=(const Point& pt)
{
	if (&pt == this)
		return *this;
	//todo variables shoudnt start with capital letter
	px = pt.px;
	py = pt.py;
	return *this;
}


PolygonalChain::PolygonalChain(int n, Point pt_arr[])
{
	pn = n;
	PointArray = new Point[n];
	for (int i = 0; i < n; i++)
	{
		PointArray[i] = pt_arr[i];
	}
}

double side(int x1, int x2, int y1, int y2) {
	return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

PolygonalChain::PolygonalChain(const PolygonalChain& pc)
{
	pn = pc.pn;
	PointArray = new Point[pn];
	for (int i = 0; i < pn; i++)
	{
		PointArray[i] = pc.PointArray[i];
	}
}

PolygonalChain& PolygonalChain::operator=(const PolygonalChain& pc)
{
	if (&pc == this)
		return *this;
	delete[] PointArray;
	pn = pc.pn;
	PointArray = new Point[pn];
	for (int i = 0; i < pn; i++)
	{
		PointArray[i] = pc.PointArray[i];
	}
	return *this;
}

PolygonalChain:: ~PolygonalChain()
{
	delete[] PointArray;
	PointArray = nullptr;
}

Point PolygonalChain::getPoint(int k) const
{
	Point pt = PointArray[k];
	return pt;
}


double PolygonalChain::perimeter() const
{
	double a = 0, p = 0;
	for (int i = 0; i < pn - 1; i++)
	{
		a = sqrt(side(PointArray[i].getX(), PointArray[i + 1].getX(), PointArray[i].getY(), PointArray[i + 1].getY()));
		p += a;
	}

	return p;
}

double ClosedPolygonalChain::perimeter() const
{
	double a = 0, p = 0;

	p = PolygonalChain::perimeter();
	p += sqrt(side(PointArray[0].getX(), PointArray[pn - 1].getX(), PointArray[0].getY(), PointArray[pn - 1].getY()));

	return p;
}

ClosedPolygonalChain::ClosedPolygonalChain(int n, Point pt_arr[]) :PolygonalChain(n, pt_arr)
{
}

ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain& cpc) : PolygonalChain(cpc)
{
}

ClosedPolygonalChain& ClosedPolygonalChain::operator=(const ClosedPolygonalChain& cpc)
{
	PolygonalChain::operator=(cpc);
	return *this;
}


Polygon::Polygon(int n, Point pt_arr[]) :ClosedPolygonalChain(n, pt_arr)
{
}

double Polygon::area() const
{
	double s = 0;
	for (int i = 0; i < pn - 1; i++)
	{
		s += PointArray[i].getX() * PointArray[i + 1].getY();
		s -= PointArray[i + 1].getX() * PointArray[i].getY();
	}

	s += PointArray[pn - 1].getX() * PointArray[0].getY();
	s -= PointArray[0].getX() * PointArray[pn - 1].getY();
	return fabs(s) / 2;
}

Polygon::Polygon(const Polygon& p) :ClosedPolygonalChain(p)
{
}

Polygon& Polygon::operator=(const Polygon& p)
{
	ClosedPolygonalChain::operator=(p);
	return *this;
}


bool Triangle::isTriangleIsosceles() const
{
	double a2, b2, c2;

	a2 = side(PointArray[0].getX(), PointArray[1].getX(), PointArray[0].getY(), PointArray[1].getY());
	b2 = side(PointArray[1].getX(), PointArray[2].getX(), PointArray[1].getY(), PointArray[2].getY());
	c2 = side(PointArray[0].getX(), PointArray[2].getX(), PointArray[0].getY(), PointArray[2].getY());

	return (a2 == b2 || a2 == c2 || b2 == c2);
}

Triangle::Triangle(int n, Point* pt_arr) :Polygon(n, pt_arr)
{
}
bool Triangle::hasRightAngle() const
{
	double a2, b2, c2;

	a2 = side(PointArray[0].getX(), PointArray[1].getX(), PointArray[0].getY(), PointArray[1].getY());
	b2 = side(PointArray[1].getX(), PointArray[2].getX(), PointArray[1].getY(), PointArray[2].getY());
	c2 = side(PointArray[0].getX(), PointArray[2].getX(), PointArray[0].getY(), PointArray[2].getY());

	return (a2 + b2 == c2 || a2 + c2 == b2 || c2 + b2 == a2);
}

Triangle::Triangle(const Triangle& t) :Polygon(t)
{
}

Triangle& Triangle::operator=(const Triangle& t)
{
	Polygon::operator=(t);
	return *this;
}


Trapezoid::Trapezoid(int n, Point* pt_arr) :Polygon(n, pt_arr)
{
}

Trapezoid::Trapezoid(const Trapezoid& tz) : Polygon(tz)
{
}

Trapezoid& Trapezoid::operator=(const Trapezoid& tz)
{
	Polygon::operator=(tz);
	return *this;
}


double Trapezoid::height() const
{
	double s = this->area();

	double a, b;

	a = sqrt(side(PointArray[2].getX(), PointArray[1].getX(), PointArray[2].getY(), PointArray[1].getY()));
	b = sqrt(side(PointArray[3].getX(), PointArray[0].getX(), PointArray[3].getY(), PointArray[0].getY()));
	return (2 * s) / (a + b);
}


RegularPolygon::RegularPolygon(int n, Point pt_arr[]) :Polygon(n, pt_arr)
{
}


RegularPolygon::RegularPolygon(const RegularPolygon& rp) : Polygon(rp)
{
}

RegularPolygon& RegularPolygon::operator=(const RegularPolygon& rp)
{
	Polygon::operator=(rp);
	return *this;
}


double RegularPolygon::perimeter() const
{
	return pn * sqrt(side(PointArray[0].getX(), PointArray[1].getX(), PointArray[0].getY(), PointArray[1].getY()));
}

double RegularPolygon::area() const
{
	return (pn * sqrt(side(PointArray[0].getX(), PointArray[1].getX(), PointArray[0].getY(), PointArray[1].getY())) *
		sqrt(side(PointArray[0].getX(), PointArray[1].getX(), PointArray[0].getY(), PointArray[1].getY()))) /
		(4 * tan(PI / pn));
}
