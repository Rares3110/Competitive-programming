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
};
point operator * (double value, point b)
{
	return { value * b.x, value * b.y };
}