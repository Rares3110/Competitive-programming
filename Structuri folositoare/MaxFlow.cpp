/*exemplu apelare:
vector <pair<int, long>> gf[] = {...}
al 2-lea parametru este capacitatea muchiei
n = numar de noduri
primul nod este sursa si nodul n este destinatia

MaxFlow<long>::assignMaxSize(n);
MaxFlow<long>::generate(n, gf);
cout << MaxFlow<long>::rezultat;

variabilele relevante sunt publice
*/
template <class T> class MaxFlow
{
public:
	static int gfSize;
	static vector <int>* gf;
	static T **cap, **flux;
	static T rezultat;
private:
	static vector <int>* gft;
	//bfs
	static int* nivel;
	static bool* viz, * usefull;
	//drum + dfs
	static pair <int, int>* muchie;
	static int* tabel;

	static bool bfs()
	{
		fill(viz + 1, viz + 1 + gfSize, 0);
		fill(usefull + 1, usefull + 1 + gfSize, 0);
		queue <int> q;
		q.push(1);

		viz[1] = usefull[1] = 1;
		nivel[1] = 1;

		while (!q.empty())
		{
			int nod = q.front();
			q.pop();

			for (const auto& vec : gf[nod])
				if (!viz[vec] && cap[nod][vec])
				{
					viz[vec] = 1;
					nivel[vec] = nivel[nod] + 1;
					q.push(vec);
					usefull[vec] = 1;
				}

			for (const auto& vec : gft[nod])
				if (!viz[vec] && flux[nod][vec])
				{
					viz[vec] = 1;
					nivel[vec] = nivel[nod] + 1;
					q.push(vec);
					usefull[vec] = 1;
				}
		}

		return viz[gfSize];
	}

	static void drum(const int& lung)
	{
		T minim;

		if (tabel[1] == 1)
			minim = cap[muchie[1].first][muchie[1].second];
		else
			minim = flux[muchie[1].first][muchie[1].second];

		for (int i = 2; i <= lung; i++)
			if (tabel[i] == 1)
				minim = min(minim, cap[muchie[i].first][muchie[i].second]);
			else
				minim = min(minim, flux[muchie[i].first][muchie[i].second]);

		for (int i = 1; i <= lung; i++)
			if (tabel[i] == 1)
			{
				cap[muchie[i].first][muchie[i].second] -= minim;
				flux[muchie[i].second][muchie[i].first] += minim;
			}
			else
			{
				flux[muchie[i].first][muchie[i].second] -= minim;
				cap[muchie[i].second][muchie[i].first] += minim;
			}

		rezultat += minim;
	}

	static bool dfs(int nod = 1, int vf = 1)
	{
		if (nod == gfSize)
		{
			drum(vf - 1);
			return true;
		}

		bool found = 0;
		for (const auto& vec : gf[nod])
			if (nivel[vec] > nivel[nod] && cap[nod][vec])
			{
				muchie[vf] = { nod, vec };
				tabel[vf] = 1;
				usefull[vec] = dfs(vec, vf + 1);
				if (usefull[vec]) found = true;
			}

		for (const auto& vec : gft[nod])
			if (nivel[vec] > nivel[nod] && flux[nod][vec])
			{
				muchie[vf] = { nod, vec };
				tabel[vf] = 2;
				usefull[vec] = dfs(vec, vf + 1);
				if (usefull[vec]) found = true;
			}

		return found;
	}

	static void deleteAll()
	{
		delete[] gf;
		delete[] gft;
		delete[] nivel;
		delete[] viz;
		delete[] usefull;
		delete[] muchie;
		delete[] tabel;
		
		if(cap != NULL)
		{
			for(int i = 0; i <= gfSize; i++)
			{
				delete[] cap[i];
				delete[] flux[i];
			}

			delete[] cap;
			delete[] flux;
		}
	}
public:
	static void assignMaxSize(const int& n)
	{
		deleteAll();
		gf = new vector <int>[n + 1]();
		gft = new vector <int>[n + 1]();
		nivel = new int[n + 1]();
		viz = new bool[n + 1]();
		usefull = new bool[n + 1]();
		muchie = new pair<int, int>[n + 1]();
		tabel = new int[n + 1]();
		
		cap = new T*[n + 1]();
		flux = new T*[n + 1]();
		for(int i = 0; i <= n; i++)
		{
			cap[i] = new T[n + 1]();
			flux[i] = new T[n + 1]();
		}
	}
	static void generate(const int& n, const vector <pair<int, T>> graf[])
	{
		for(int i = 1; i <= n; i++)
		{
			fill(cap[i] + 1, cap[i] + 1 + n, 0);
			fill(flux[i] + 1, flux[i] + 1 + n, 0);
		}

		rezultat = 0;
		gfSize = n;
		
		for (int i = 1; i <= n; i++)
			for (const auto& vec : graf[i])
			{
				gf[i].push_back(vec.first);
				gft[vec.first].push_back(i);
				cap[i][vec.first] = cap[vec.first][i] = vec.second;
			}

		while (bfs())
			while (dfs());
	}
};
template <class T> int MaxFlow<T>::gfSize = 0;
template <class T> vector <int>* MaxFlow<T>::gf = NULL;
template <class T> vector <int>* MaxFlow<T>::gft = NULL;
template <class T> T** MaxFlow<T>::cap = NULL;
template <class T> T** MaxFlow<T>::flux = NULL;
template <class T> int* MaxFlow<T>::nivel = NULL;
template <class T> bool* MaxFlow<T>::viz = NULL;
template <class T> bool* MaxFlow<T>::usefull = NULL;
template <class T> pair <int, int>* MaxFlow<T>::muchie = NULL;
template <class T> int* MaxFlow<T>::tabel = NULL;
template <class T> T MaxFlow<T>::rezultat = 0;
