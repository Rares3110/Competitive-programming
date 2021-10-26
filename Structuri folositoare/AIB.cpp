template <class T> class AIB
{
private:
	T* tree;
	int lung;
	T sum_part(int poz)
	{
		T rez = 0;

		while (poz)
		{
			rez += tree[poz];
			poz -= poz & -poz;
		}

		return rez;
	}
public:
	AIB(int lungime)
	{
		lung = lungime;
		tree = new T[lung + 1]();
	}
	~AIB()
	{
		delete[] tree;
	}
	void add(int poz, T value)
	{
		while (poz <= lung)
		{
			tree[poz] += value;
			poz += poz & -poz;
		}
	}
	T sum(int st, int dr)
	{
		return sum_part(dr) - sum_part(st - 1);
	}
};

template <class T> class AIB_2D
{
private:
	T **tree;
	int lung_lin, lung_col;
	T sum_part(int lin, int col)
	{
		T rez = 0;

		for (int i = lin; i; i -= i & -i)
			for (int j = col; j; j -= j & -j)
				rez = (rez + tree[i][j]);

		return rez;
	}
public:
	AIB_2D(int lung_lin, int lung_col)
	{
		this->lung_lin = lung_lin;
		this->lung_col = lung_col;

		tree = new T*[lung_lin + 1]();
		for(int i = 0; i <= lung_lin; i++)
			tree[i] = new T[lung_col + 1]();
	}
	~AIB_2D()
	{
		for (int i = 0; i <= lung_lin; i++)
			delete[] tree[i];
		delete[] tree;
	}
	void add(int poz_lin, int poz_col, T value)
	{
		for (int i = poz_lin; i <= lung_lin; i += i & -i)
			for (int j = poz_col; j <= lung_col; j += j & -j)
				tree[i][j] += value;
	}
	T sum(int start_lin, int start_col, int end_lin, int end_col)
	{
		return sum_part(end_lin, end_col) - sum_part(start_lin - 1, end_col)
			- sum_part(end_lin, start_col - 1) + sum_part(start_lin - 1, start_col - 1);
	}
};
