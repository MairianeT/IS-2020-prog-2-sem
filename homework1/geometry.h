#ifndef GEOMETRY_H 
#define GEOMETRY_H 

class Point
{
public:
	int px;
	int py;

	Point();
	Point(int x, int y);
	Point(const Point& pt);
	Point& operator=(const Point& pt);

	void SetPoint(int x, int y);

	int getX() const { return px; }
	int getY() const { return py; }
};


class PolygonalChain 
{
public:
	int pn;
	Point* PointArray;

	PolygonalChain(int n, Point pt_arr[]);
	PolygonalChain(const PolygonalChain& pc);
	PolygonalChain& operator=(const PolygonalChain& pc);
	virtual ~PolygonalChain();

	int getN() const { return pn; }
	Point getPoint(int k) const;

	virtual double perimeter() const;
};

class ClosedPolygonalChain: public PolygonalChain
{
public:
	ClosedPolygonalChain(int n, Point pt_arr[]);
	ClosedPolygonalChain(const ClosedPolygonalChain& cpc);
	ClosedPolygonalChain& operator=(const ClosedPolygonalChain& cpc);

	virtual double perimeter() const;

};

class Polygon : public ClosedPolygonalChain
{
public:
	Polygon(int n, Point pt_arr[]);
	Polygon(const Polygon& p);
	Polygon& operator=(const Polygon& p);

	double area() const;
};

class Triangle: public Polygon
{
public:
	Triangle(int n, Point pt_arr[]);
	Triangle(const Triangle& t);
	Triangle& operator=(const Triangle& t);

	bool hasRightAngle() const;
	bool isTriangleIsosceles() const;
};

class Trapezoid : public Polygon
{
public:
	Trapezoid(int n, Point pt_arr[]);
	Trapezoid(const Trapezoid& tz);
	Trapezoid& operator=(const Trapezoid& tz);

	double height() const;
};

class RegularPolygon : public Polygon
{
public:
	RegularPolygon(int n, Point pt_arr[]);
	RegularPolygon(const RegularPolygon& rp);
	RegularPolygon& operator=(const RegularPolygon& rp);

	double Angle() const;
	virtual double perimeter() const;
	virtual double area() const;
	
};


#endif
