template <class T> class AIB
{
private:
	T* tree, lung;
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
