class Union
{
private:
	int* tata, * marime, lung;
public:
	Union()
	{
		tata = NULL;
		marime = NULL;
		lung = 0;
	}
	Union(int lungime)
	{
		lung = lungime;
		tata = new int[lung + 1];
		marime = new int[lung + 1];
		reset();
	}
	Union(const Union& copyUnion)
	{
		lung = copyUnion.lung;
		tata = new int[lung + 1];
		marime = new int[lung + 1];

		for (int i = 1; i <= lung; i++)
		{
			tata[i] = copyUnion.tata[i];
			marime[i] = copyUnion.marime[i];
		}
	}
	void operator =(const Union& copyUnion)
	{
		delete[] tata;
		delete[] marime;
		tata = NULL;
		marime = NULL;

		lung = copyUnion.lung;
		tata = new int[lung + 1];
		marime = new int[lung + 1];

		for (int i = 1; i <= lung; i++)
		{
			tata[i] = copyUnion.tata[i];
			marime[i] = copyUnion.marime[i];
		}
	}
	~Union()
	{
		delete[] tata;
		delete[] marime;
	}
	void reset()
	{
		for (int i = 1; i <= lung; i++)
		{
			tata[i] = i;
			marime[i] = 1;
		}
	}
	void uneste(int nod1, int nod2)
	{
		int r1 = radacina(nod1), r2 = radacina(nod2);

		if (r1 == r2)
			return;

		if (marime[r1] < marime[r2])
			swap(r1, r2);

		tata[r2] = r1;
		marime[r1] += marime[r2];
	}
	int sizeSet(int nod)
	{
		return marime[radacina(nod)];
	}
	int radacina(int nod)
	{
		while (nod != tata[nod])
			nod = tata[nod];

		return nod;
	}
};
