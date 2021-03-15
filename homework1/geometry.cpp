#include "geometry.h"
#include <math.h>

#define PI  3.14159265358979323846

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

Point& Point::operator= (const Point& pt)
{
	if (&pt == this)
		return *this;
	//fixed variables shoudnt start with capital letter
	//dont remove todo's, rename it to fixed
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

//fixed what side is it

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
	//fixed no point to do it
}

Point PolygonalChain::getPoint(int k) const
{
	Point pt = PointArray[k];
	return pt;
}


double PolygonalChain::perimeter() const
{
	double per = 0;
	for (int i = 0; i < pn - 1; i++)
	{
		per += sqrt(pow((PointArray[i].getX() - PointArray[i + 1].getX()), 2) + pow((PointArray[i].getY() - PointArray[i + 1].getY()), 2));
	}

	return per;
}

double ClosedPolygonalChain::perimeter() const
{
	double per = 0;

	per = PolygonalChain::perimeter();
	per += sqrt(pow(PointArray[0].getX() - PointArray[pn - 1].getX(), 2) + pow(PointArray[0].getY() - PointArray[pn - 1].getY(), 2));

	return per;
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
	//fixed you dont need double for s
	int sum = 0;
	for (int i = 0; i < pn - 1; i++)
	{
		sum += PointArray[i].getX() * PointArray[i + 1].getY();
		sum -= PointArray[i + 1].getX() * PointArray[i].getY();
	}

	sum += PointArray[pn - 1].getX() * PointArray[0].getY();
	sum -= PointArray[0].getX() * PointArray[pn - 1].getY();
	return fabs(sum) * 0.5;
}

Polygon::Polygon(const Polygon& p) :ClosedPolygonalChain(p)
{
}

Polygon& Polygon::operator=(const Polygon& p)
{
	ClosedPolygonalChain::operator=(p);
	return *this;
}


Triangle::Triangle(int n, Point* pt_arr) :Polygon(n, pt_arr)
{
}
bool Triangle::hasRightAngle() const
{
	double a2, b2, c2;

	a2 = pow(PointArray[0].getX() - PointArray[1].getX(), 2) + pow(PointArray[0].getY() - PointArray[1].getY(), 2);
	b2 = pow(PointArray[1].getX() - PointArray[2].getX(), 2) + pow(PointArray[1].getY() - PointArray[2].getY(), 2);
	c2 = pow(PointArray[0].getX() - PointArray[2].getX(), 2) + pow(PointArray[0].getY() - PointArray[2].getY(), 2);

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

	a = sqrt(pow(PointArray[2].getX() - PointArray[1].getX(), 2) + pow(PointArray[2].getY() - PointArray[1].getY(), 2));
	b = sqrt(pow(PointArray[3].getX() - PointArray[0].getX(), 2) + pow(PointArray[3].getY() - PointArray[0].getY(), 2));
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
	return pn * sqrt(pow(PointArray[0].getX() - PointArray[1].getX(), 2) + pow(PointArray[0].getY() - PointArray[1].getY(), 2));
}

double RegularPolygon::area() const
{
	return (pn * sqrt(pow(PointArray[0].getX() - PointArray[1].getX(), 2) + pow(PointArray[0].getY() - PointArray[1].getY(), 2)) *
		sqrt(pow(PointArray[0].getX() - PointArray[1].getX(), 2) + pow(PointArray[0].getY() - PointArray[1].getY(), 2))) /
		(4 * tan(PI / pn));
}
