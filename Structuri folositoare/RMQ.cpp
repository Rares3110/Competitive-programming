//declarare: RMQ(vector pe care se face rmq, lungimea lui, functia de comparare)
//atentie la functia de comparare
/*
exemplu:
	RMQ <int> rmq(vect, n, min);
	cout << rmq.query(2, 7);
*/
template <class T> class RMQ
{
private:
	T** rmq;
	int rMax, length;
	const T& (*compare)(const T&, const T&);
public:
	RMQ()
	{
		rmq = NULL;
		compare = NULL;
		rMax = 0;
		length = 0;
	}
	RMQ(T vector[], int length, const T& (*compare)(const T&, const T&))
	{
		this->length = length;
		this->compare = compare;
		rMax = log2(length);
		rmq = new T * [rMax + 1];

		rmq[0] = new int[length + 1];
		for (int i = 1; i <= length; i++)
			rmq[0][i] = vector[i];

		for (int r = 1, l = 1; r <= rMax; r++, l *= 2)
		{
			rmq[r] = new int[length - l * 2 + 2];
			for (int i = 1; i <= length - l * 2 + 1; i++)
				rmq[r][i] = compare(rmq[r - 1][i], rmq[r - 1][i + l]);
		}
	}
	RMQ(const RMQ& copyRmq)
	{
		this->compare = copyRmq.compare;
		this->rMax = copyRmq.rMax;
		this->length = copyRmq.length;
		
		rmq = new T * [rMax + 1];
		rmq[0] = new int[length + 1];
		for (int i = 1; i <= length; i++)
			rmq[0][i] = copyRmq.rmq[0][i];

		for (int r = 1, l = 1; r <= rMax; r++, l *= 2)
		{
			rmq[r] = new int[length - l * 2 + 2];
			for (int i = 1; i <= length - l * 2 + 1; i++)
				rmq[r][i] = copyRmq.rmq[r][i];
		}
	}
	void operator =(const RMQ& copyRmq)
	{
		if (rmq != NULL)
		{
			for (int i = 0; i <= rMax; i++)
				delete[] rmq[i];

			delete[] rmq;
		}
		this->rmq = NULL;
		this->compare = copyRmq.compare;
		this->rMax = copyRmq.rMax;
		this->length = copyRmq.length;

		rmq = new T * [rMax + 1];
		rmq[0] = new int[length + 1];
		for (int i = 1; i <= length; i++)
			rmq[0][i] = copyRmq.rmq[0][i];

		for (int r = 1, l = 1; r <= rMax; r++, l *= 2)
		{
			rmq[r] = new int[length - l * 2 + 2];
			for (int i = 1; i <= length - l * 2 + 1; i++)
				rmq[r][i] = copyRmq.rmq[r][i];
		}
	}
	~RMQ()
	{
		if (rmq != NULL)
		{
			for (int i = 0; i <= rMax; i++)
				delete[] rmq[i];

			delete[] rmq;
		}
	}
	T query(int st, int dr)
	{
		int r = log2(dr - st + 1);
		return compare(rmq[r][st], rmq[r][dr - (1 << r) + 1]);
	}
};
