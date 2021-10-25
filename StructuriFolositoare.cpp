class Union
{
private:
	int *tata, *marime, lung;
public:
	Union(int lungime)
	{
		lung = lungime;
		tata = new int[lung + 1];
		marime = new int[lung + 1];
		reset();
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

//declarare: Trie(nr = numar de litere din alfabet, functie hash care sa transforme literele din alfabet in numere de la 0 la nr - 1
/*
exemplu 1:
	int Hash(char litera)
	{return litera - 'a';}

	Trie trie(26, Hash);
	trie.inserare("cuvant");

exemplu 2:
	int Hash(char cifra)
	{return cifra - '0';}

	Trie trie(10, Hash);
	trie.inserare(to_string(1234));
*/
class Trie
{
private:
	int sizeAlf;
	int (*Hash)(char);

	struct nod
	{
		int apar = 0, term = 0;
		nod **alf;
	};
	nod *origin;

public:
	Trie(int sizeAlfabet, int (*HashFunction)(char))
	{
		sizeAlf = sizeAlfabet;
		Hash = HashFunction;

		origin = new nod();
		origin->alf = new nod*[sizeAlf]();
	}
	void inserare(string sir)
	{
		nod* poz = origin;

		for (auto lit : sir)
		{
			int nr = Hash(lit);
			if (poz->alf[nr] == NULL)
			{
				nod* newRam = new nod();
				newRam->alf = new nod * [sizeAlf]();
				poz->alf[nr] = newRam;
			}

			poz = poz->alf[nr];
			poz->apar++;
		}

		poz->term++;
	}
	void stergere(string sir)
	{
		if (!aparitii(sir))
			return;

		stack <nod*> s;
		nod* poz = origin;

		for (auto lit : sir)
		{
			s.push(poz);
			poz = poz->alf[Hash(lit)];
		}

		s.top()->alf[Hash(sir[sir.size() - 1])]->term--;

		for(int i = sir.size() - 1; i >= 0; i--)
		{
			nod* curent = s.top();
			nod* urm = curent->alf[Hash(sir[i])];
			s.pop();
			urm->apar--;

			if (urm->apar == 0)
			{
				delete urm;
				curent->alf[Hash(sir[i])] = NULL;
			}
		}
	}
	int aparitii(string sir)
	{
		nod* poz = origin;

		for (auto lit : sir)
			if (poz->alf[Hash(lit)] == NULL)
				return 0;
			else
				poz = poz->alf[Hash(lit)];

		return poz->term;
	}
};
