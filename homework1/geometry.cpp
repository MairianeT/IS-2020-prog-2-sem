#include "geometry.h"
#include <math.h>
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
	Px = x;
	Py = y;
}


Point::Point(const Point& pt)
{
	Px = pt.Px;
	Py = pt.Py;
}

Point& Point::operator=(const Point& pt)
{
	if (&pt == this)
		return *this;
	Px = pt.Px;
	Py = pt.Py;
	return *this;
}


PolygonalChain::PolygonalChain(int n, Point pt_arr[])
{
	Pn = n;
	PointArray = new Point[n];
	for (int i = 0; i < n; i++)
	{
		PointArray[i] = pt_arr[i];
	}
}

PolygonalChain::PolygonalChain(const PolygonalChain& pc)
{
	Pn = pc.Pn;
	PointArray = new Point[Pn];
	for (int i = 0; i < Pn; i++)
	{
		PointArray[i] = pc.PointArray[i];
	}
}

PolygonalChain& PolygonalChain::operator=(const PolygonalChain& pc)
{
	if (&pc == this)
		return *this;
	delete[] PointArray;
	Pn = pc.Pn;
	PointArray = new Point[Pn];
	for (int i = 0; i < Pn; i++)
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
	double a = 0, P = 0;
	for (int i = 0; i < Pn - 1; i++)
	{
		a = sqrt(((double)PointArray[i].getX() - (double)PointArray[i + 1].getX()) * ((double)PointArray[i].getX() - (double)PointArray[i + 1].getX()) +
			((double)PointArray[i].getY() - (double)PointArray[i + 1].getY()) * ((double)PointArray[i].getY() - (double)PointArray[i + 1].getY()));
		P += a;
	}

	return P;
}

double ClosedPolygonalChain::perimeter() const
{
	double a = 0, P = 0;

	for (int i = 0; i < Pn - 1; i++)
	{
		a = sqrt(((double)PointArray[i].getX() - (double)PointArray[i + 1].getX()) * ((double)PointArray[i].getX() - (double)PointArray[i + 1].getX()) +
			((double)PointArray[i].getY() - (double)PointArray[i + 1].getY()) * ((double)PointArray[i].getY() - (double)PointArray[i + 1].getY()));
		P += a;
	}

	P += sqrt(((double)PointArray[0].getX() - (double)PointArray[Pn - 1].getX()) * ((double)PointArray[0].getX() - (double)PointArray[Pn - 1].getX()) +
		((double)PointArray[0].getY() - (double)PointArray[Pn - 1].getY()) * ((double)PointArray[0].getY() - (double)PointArray[Pn - 1].getY()));

	return P;
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

ClosedPolygonalChain::~ClosedPolygonalChain()
{
	PolygonalChain::~PolygonalChain();
}


Polygon::Polygon(int n, Point pt_arr[]) :ClosedPolygonalChain(n, pt_arr)
{
}

double Polygon::area() const
{
	double S = 0;
	for (int i = 0; i < Pn - 1; i++)
	{
		S += (double)PointArray[i].getX() * (double)PointArray[i + 1].getY();
		S -= (double)PointArray[i + 1].getX() * (double)PointArray[i].getY();
	}

	S += (double)PointArray[Pn - 1].getX() * (double)PointArray[0].getY();
	S -= (double)PointArray[0].getX() * (double)PointArray[Pn - 1].getY();
	return fabs(S) / 2;
}

Polygon::Polygon(const Polygon& p) :ClosedPolygonalChain(p)
{
}

Polygon& Polygon::operator=(const Polygon& p)
{
	ClosedPolygonalChain::operator=(p);
	return *this;
}

Polygon::~Polygon()
{
	ClosedPolygonalChain::~ClosedPolygonalChain();
}


bool Triangle::isTriangleIsosceles() const
{
	double a2, b2, c2;
	a2 = ((double)PointArray[0].getX() - (double)PointArray[1].getX()) * ((double)PointArray[0].getX() - (double)PointArray[1].getX()) +
		((double)PointArray[0].getY() - (double)PointArray[1].getY()) * ((double)PointArray[0].getY() - (double)PointArray[1].getY());
	b2 = ((double)PointArray[1].getX() - (double)PointArray[2].getX()) * ((double)PointArray[1].getX() - (double)PointArray[2].getX()) +
		((double)PointArray[1].getY() - (double)PointArray[2].getY()) * ((double)PointArray[1].getY() - (double)PointArray[2].getY());
	c2 = ((double)PointArray[0].getX() - (double)PointArray[2].getX()) * ((double)PointArray[0].getX() - (double)PointArray[2].getX()) +
		((double)PointArray[0].getY() - (double)PointArray[2].getY()) * ((double)PointArray[0].getY() - (double)PointArray[2].getY());

	if (a2 == b2 || a2 == c2 || b2 == c2) return true;
	else return false;
}

Triangle::Triangle(int n, Point* pt_arr) :Polygon(n, pt_arr)
{
}

bool Triangle::hasRightAngle() const
{
	double a2, b2, c2;

	a2 = ((double)PointArray[0].getX() - (double)PointArray[1].getX()) * ((double)PointArray[0].getX() - (double)PointArray[1].getX()) +
		((double)PointArray[0].getY() - (double)PointArray[1].getY()) * ((double)PointArray[0].getY() - (double)PointArray[1].getY());
	b2 = ((double)PointArray[2].getX() - (double)PointArray[1].getX()) * ((double)PointArray[2].getX() - (double)PointArray[1].getX()) +
		((double)PointArray[2].getY() - (double)PointArray[1].getY()) * ((double)PointArray[2].getY() - (double)PointArray[1].getY());
	c2 = ((double)PointArray[0].getX() - (double)PointArray[2].getX()) * ((double)PointArray[0].getX() - (double)PointArray[2].getX()) +
		((double)PointArray[0].getY() - (double)PointArray[2].getY()) * ((double)PointArray[0].getY() - (double)PointArray[2].getY());

	if (a2 + b2 == c2 || a2 + c2 == b2 || c2 + b2 == a2) return true;
	else return false;
}

Triangle::Triangle(const Triangle& t) :Polygon(t)
{
}

Triangle& Triangle::operator=(const Triangle& t)
{
	Polygon::operator=(t);
	return *this;
}

Triangle::~Triangle()
{
	Polygon::~Polygon();
}

bool Trapezoid::isTrapezoidIsosceles() const
{
	double a2, b2;
	a2 = ((double)PointArray[0].getX() - (double)PointArray[1].getX()) * ((double)PointArray[0].getX() - (double)PointArray[1].getX()) +
		((double)PointArray[0].getY() - (double)PointArray[1].getY()) * ((double)PointArray[0].getY() - (double)PointArray[1].getY());
	b2 = ((double)PointArray[3].getX() - (double)PointArray[2].getX()) * ((double)PointArray[3].getX() - (double)PointArray[2].getX()) +
		((double)PointArray[3].getY() - (double)PointArray[2].getY()) * ((double)PointArray[3].getY() - (double)PointArray[2].getY());

	if (a2 == b2) return true;
	else return false;
}

Trapezoid::Trapezoid(int n, Point* pt_arr) :Polygon(n, pt_arr)
{
}

Trapezoid::Trapezoid(const Trapezoid& tz) :Polygon(tz) 
{
}

Trapezoid& Trapezoid::operator=(const Trapezoid& tz)
{
	Polygon::operator=(tz);
	return *this;
}

Trapezoid::~Trapezoid()
{
	Polygon::~Polygon();
}

double Trapezoid::height() const
{
	double S = this->area();

	double a, b;

	a = sqrt(((double)PointArray[2].getX() - (double)PointArray[1].getX()) * ((double)PointArray[2].getX() - (double)PointArray[1].getX()) +
		((double)PointArray[2].getY() - (double)PointArray[1].getY()) * ((double)PointArray[2].getY() - (double)PointArray[1].getY()));
	b = sqrt(((double)PointArray[3].getX() - (double)PointArray[0].getX()) * ((double)PointArray[3].getX() - (double)PointArray[0].getX()) +
		((double)PointArray[3].getY() - (double)PointArray[0].getY()) * ((double)PointArray[3].getY() - (double)PointArray[0].getY()));

	return (2 * S) / (a + b);
}


double RegularPolygon::SumAngle() const
{
	return ((double)Pn - 2) * 180;
}

double RegularPolygon::r() const
{
	double r = 2 * this->area() / this->perimeter();
	return r;
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

RegularPolygon::~RegularPolygon()
{
	Polygon::~Polygon();
}

double RegularPolygon::Angle() const
{
	double ang = ((double)Pn - 2) * 180 / Pn;
	return ang;
}

