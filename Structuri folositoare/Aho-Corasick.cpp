class AC_automaton
{
private:
	int sizeAlf;
	int (*Hash)(char);

	struct nod
	{
		vector <int> apar;
		nod **alf, *fail;
	};
	nod *origin;

	vector <int> Union (vector <int>& a, vector <int>& b)
	{
		vector <int> c;
		int st = 0, dr = 0;
		while(st < a.size() && dr < b.size())
			if(a[st] <= b[dr])
				c.push_back(a[st++]);
			else
				c.push_back(b[dr++]);

		while(st < a.size())
			c.push_back(a[st++]);

		while(dr < b.size())
			c.push_back(b[dr++]);

		return c;
	}
	void inserare(string& cuv, int index)
	{
		nod* poz = origin;

		for (auto lit : cuv)
		{
			int nr = Hash(lit);
			if (poz->alf[nr] == NULL)
			{
				nod* newRam = new nod();
				newRam->alf = new nod * [sizeAlf]();
				poz->alf[nr] = newRam;
			}

			poz = poz->alf[nr];
		}

		poz->apar.push_back(index);
	}
	void bfs()
	{
		queue <nod*> q;
		origin -> fail = origin;
		for(int i = 0; i < sizeAlf; i++)
			if(origin -> alf[i] != NULL)
			{
				origin -> alf[i] -> fail = origin;
				q.push(origin -> alf[i]);
			}

		while(!q.empty())
		{
			nod* curent = q.front();
			q.pop();

			for(int i = 0; i < sizeAlf; i++)
				if(curent -> alf[i] != NULL)
				{
					nod* findNod = curent;
					while(findNod != origin && findNod -> fail -> alf[i] == NULL)
						findNod = findNod -> fail;

					if(findNod -> fail -> alf[i] != NULL)
						curent -> alf[i] -> fail = findNod -> fail -> alf[i];
					else
						curent -> alf[i] -> fail = origin;

					curent -> alf[i] -> apar = Union(curent -> alf[i] -> apar, curent -> alf[i] -> fail -> apar);
					q.push(curent -> alf[i]);
				}
		}
	}
public:
	AC_automaton(string cuv[], int numarCuv, int sizeAlfabet, int (*HashFunction)(char))
	{
		sizeAlf = sizeAlfabet;
		Hash = HashFunction;

		origin = new nod();
		origin->alf = new nod*[sizeAlf]();

		for(int i = 1; i <= numarCuv; i++)
			inserare(cuv[i], i);

		bfs();
	}
	void sendAparitii(string &sir, int numarApar[])
	{
		nod* poz = origin;
		for(int i = 0; i < sir.size(); i++)
		{
			while(poz != origin && poz -> alf[Hash(sir[i])] == NULL)
				poz = poz -> fail;

			if(poz -> alf[Hash(sir[i])] != NULL)
				poz = poz -> alf[Hash(sir[i])];
			
			for(auto index : poz->apar)
				numarApar[index]++;
		}
	}
};
