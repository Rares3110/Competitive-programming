class LCA
{
private:
	int **rmq;
	int rMax, length;
	const int& compare(const int& a, const int& b)
	{
		if (nivel[a] <= nivel[b])
			return a;
		return b;
	}
	void buildRmq(int length)
	{
		this->length = length;
		rMax = log2(length);
		rmq = new int * [rMax + 1];

		rmq[0] = new int[length + 1];
		for (int i = 1; i <= length; i++)
			rmq[0][i] = gfEuler[i];

		for (int r = 1, l = 1; r <= rMax; r++, l *= 2)
		{
			rmq[r] = new int[length - l * 2 + 2];
			for (int i = 1; i <= length - l * 2 + 1; i++)
				rmq[r][i] = compare(rmq[r - 1][i], rmq[r - 1][i + l]);
		}
	}
	int queryRmq(int st, int dr)
	{
		int r = log2(dr - st + 1);
		return compare(rmq[r][st], rmq[r][dr - (1 << r) + 1]);
	}

	int *gfEuler, *nivel, *st, *dr, gfSize, poz;
	void dfsNivel(vector <int> gf[], int nod, int niv = 1)
	{
		gfEuler[++poz] = nod;
		nivel[nod] = niv;
		st[nod] = min(st[nod], poz);
		dr[nod] = max(dr[nod], poz);

		for (auto vec : gf[nod])
			if (!nivel[vec])
			{
				dfsNivel(gf, vec, niv + 1);

				gfEuler[++poz] = nod;
				nivel[nod] = niv;
				st[nod] = min(st[nod], poz);
				dr[nod] = max(dr[nod], poz);
			}
	}
public:
	LCA()
	{
		rmq = NULL;
		rMax = length = 0;
		gfEuler = nivel = st = dr = NULL;
		gfSize = 0;
	}
	LCA(vector <int> gf[], int gfSize, int varf)
	{
		this->gfSize = gfSize;
		gfEuler = new int[gfSize * 2];
		nivel = new int[gfSize + 1];
		st = new int[gfSize + 1];
		dr = new int[gfSize + 1];

		for (int i = 1; i <= gfSize; i++)
		{
			nivel[i] = 0;
			st[i] = 2 * gfSize;
			dr[i] = 0;
		}

		poz = 0;
		dfsNivel(gf, varf);
		buildRmq(gfSize * 2 - 1);
	}
	LCA(const LCA& copyLca)
	{
		this->gfSize = copyLca.gfSize;
		gfEuler = new int[gfSize * 2];
		nivel = new int[gfSize + 1];
		st = new int[gfSize + 1];
		dr = new int[gfSize + 1];

		for (int i = 1; i <= gfSize; i++)
		{
			nivel[i] = copyLca.nivel[i];
			st[i] = copyLca.st[i];
			dr[i] = copyLca.dr[i];
		}

		for (int i = 1; i <= gfSize * 2 - 1; i++)
			gfEuler[i] = copyLca.gfEuler[i];

		buildRmq(gfSize * 2 - 1);
	}
	void operator =(const LCA& copyLca)
	{
		if (rmq != NULL)
		{
			for (int i = 0; i <= rMax; i++)
				delete[] rmq[i];
			delete[] rmq;

			delete[] gfEuler;
			delete[] nivel;
			delete[] st;
			delete[] dr;

			rmq = NULL;
			rMax = length = 0;
			gfEuler = nivel = st = dr = NULL;
			gfSize = 0;
		}

		this->gfSize = copyLca.gfSize;
		gfEuler = new int[gfSize * 2];
		nivel = new int[gfSize + 1];
		st = new int[gfSize + 1];
		dr = new int[gfSize + 1];

		for (int i = 1; i <= gfSize; i++)
		{
			nivel[i] = copyLca.nivel[i];
			st[i] = copyLca.st[i];
			dr[i] = copyLca.dr[i];
		}

		for (int i = 1; i <= gfSize * 2 - 1; i++)
			gfEuler[i] = copyLca.gfEuler[i];

		buildRmq(gfSize * 2 - 1);
	}
	~LCA()
	{
		if (rmq != NULL)
		{
			for (int i = 0; i <= rMax; i++)
				delete[] rmq[i];
			delete[] rmq;

			delete[] gfEuler;
			delete[] nivel;
			delete[] st;
			delete[] dr;
		}
	}
	int query(int a, int b)
	{
		return queryRmq(min(st[a], st[b]), max(dr[a], dr[b]));
	}
};
