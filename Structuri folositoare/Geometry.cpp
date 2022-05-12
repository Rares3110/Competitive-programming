class point
{
public:
	double x, y;

	point()
	{
		x = 0.0; y = 0.0;
	}
	point(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
	point(pair<double, double> pereche)
	{
		this->x = pereche.first;
		this->y = pereche.second;
	}
	point operator + (point b)
	{
		return { this->x + b.x, this->y + b.y };
	}
	point operator - (point b)
	{
		return { this->x - b.x, this->y - b.y };
	}
	void operator += (point b)
	{
		this->x += b.x;
		this->y += b.y;
	}
	void operator -= (point b)
	{
		this->x -= b.x;
		this->y -= b.y;
	}
	point operator * (double value)
	{
		return { this->x * value, this->y * value };
	}
	point operator / (double value)
	{
		return { this->x / value, this->y / value };
	}
	friend point operator * (double value, point b);
	double operator * (point b)
	{
		return this->x * b.y - this->y * b.x;
	}
	static double euclidDist(point a, point b)
	{
		return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}
	static double manhattanDist(point a, point b)
	{
		return fabs(a.x - b.x) + fabs(a.y - b.y);
	}
	static double leftFromLineFactor(point p, point l1, point l2)
	{
		return (p - l1) * (p - l2);
	}
	static double panta(point a, point b)
	{
		return (b.y - a.y) / (b.x - a.x);
	}
	const bool operator < (const point& b) const
	{
		if (abs(x - b.x) > 0.00001)
			return x < b.x;
		else
			return y < b.y;
	}
};
point operator * (double value, point b)
{
	return { value * b.x, value * b.y };
}

class Line
{
public:
	double a, b, c;
	//ax + by + c = 0

	Line()
	{
		a = 0;
		b = 1;
		c = 0;
	}
	Line(double a, double b, double c)
	{
		this->a = a;
		this->b = b;
		this->c = c;
	}
	Line(point p1, point p2)
	{
		if (abs(p1.x - p2.x) < 0.00001)
		{
			b = 0;
			a = 1;
			c = - p1.x;
		}
		else
		{
			b = 1;
			a = -point::panta(p1, p2);
			c = -a * p1.x - p1.y;
		}
	}
	point getPointFromX(double xValue)
	{
		return { xValue, -(this->a * xValue + this->c) / this->b };
	}
	point getPointFromY(double yValue)
	{
		return { -(this->b * yValue + this->c) / this->a, yValue };
	}
	bool isHorizontal()
	{
		if (abs(a) < 0.00001)
			return true;
		return false;
	}
	bool isVertical()
	{
		if (abs(b) < 0.00001)
			return true;
		return false;
	}
	bool onLine(point punct)
	{
		if (abs(a * punct.x + b * punct.y + c) < 0.00001)
			return true;
		return false;
	}
	static point pointFromIntersection(Line l1, Line l2)
	{
		double x = (l1.b * l2.c - l2.b * l1.c) / (l1.a * l2.b - l2.a * l1.b);
		double y = (l1.c * l2.a - l2.c * l1.a) / (l1.a * l2.b - l2.a * l1.b);
		return { x, y };
	}
	static bool paralel(Line l1, Line l2)
	{
		if (abs(l1.a * l2.b - l2.a * l1.b) < 0.00001)
			return true;
		return false;
	}
	const bool operator < (const Line& ln) const
	{
		if (abs(a - ln.a) > 0.00001)
			return a < ln.a;
		else if (abs(a - ln.a) > 0.00001)
			return b < ln.b;
		else
			return c < ln.c;
	}
};
