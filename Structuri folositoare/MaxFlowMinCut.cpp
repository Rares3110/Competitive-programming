template <class T> class MaxFlowMinCost
{
public:
	static int gfSize;
	static vector <int>* gf;
	static map <pair<int, int>, T> cap, flux, cost;
	static T rezultatFlux, rezultatCost;
private:
	static vector <int>* gft;
	static bool* beenThere;
	//bellman-ford
	static T* dist;
	//djikstra
	static int* tata, * tabelTata;
	static T* positiveDist, * newDist;
	static bool* viz;
	//drum
	static pair <int, int>* muchie;
	static int* tabel;

	static void bellman()
	{
		queue <int> q;
		bool* inQ = new bool[gfSize + 1]();
		fill(inQ + 1, inQ + 1 + gfSize, 0);
		fill(beenThere + 1, beenThere + 1 + gfSize, 0);

		q.push(1);
		inQ[1] = beenThere[1] = true;
		dist[1] = 0;

		while (!q.empty())
		{
			int nod = q.front();
			q.pop();
			inQ[nod] = 0;

			for (const auto& vec : gf[nod])
				if (!beenThere[vec] || dist[nod] + cost[{nod, vec}] < dist[vec])
				{
					beenThere[vec] = true;
					dist[vec] = dist[nod] + cost[{nod, vec}];
					if (!inQ[vec])
					{
						q.push(vec);
						inQ[vec] = 1;
					}
				}
		}

		delete[] inQ;
	}

	static bool djikstra()
	{
		priority_queue <pair<int, int>> pq;
		pq.push({ 0, 1 });
		positiveDist[1] = 0;
		fill(viz + 1, viz + 1 + gfSize, 0);
		fill(beenThere + 1, beenThere + 1 + gfSize, 0);
		beenThere[1] = true;

		while (!pq.empty())
		{
			int nod = pq.top().second;
			pq.pop();

			if (viz[nod] == 1)
				continue;
			viz[nod] = 1;

			for (const auto& vec : gf[nod])
			{
				int positiveArc = cost[{nod, vec}] + dist[nod] - dist[vec];

				if (cap[{nod, vec}] && (!beenThere[vec] || positiveDist[nod] + positiveArc < positiveDist[vec]))
				{
					beenThere[vec] = true;
					positiveDist[vec] = positiveDist[nod] + positiveArc;
					pq.push({ -positiveDist[vec], vec });
					newDist[vec] = newDist[nod] + cost[{nod, vec}];

					tata[vec] = nod;
					tabelTata[vec] = 1;
				}
			}

			for (const auto& vec : gft[nod])
			{
				int positiveArc = -cost[{vec, nod}] + dist[nod] - dist[vec];
				if (flux[{nod, vec}] && (!beenThere[vec] || positiveDist[nod] + positiveArc < positiveDist[vec]))
				{
					beenThere[vec] = true;
					positiveDist[vec] = positiveDist[nod] + positiveArc;
					pq.push({ -positiveDist[vec], vec });
					newDist[vec] = newDist[nod] - cost[{vec, nod}];

					tata[vec] = nod;
					tabelTata[vec] = 2;
				}
			}
		}

		for (int i = 1; i <= gfSize; i++)
			dist[i] = newDist[i];

		return beenThere[gfSize];
	}

	static void drum(const int& lung)
	{
		T minim, suma = 0;

		if (tabel[1] == 1)
			minim = cap[{muchie[1].first, muchie[1].second}];
		else
			minim = flux[{muchie[1].first, muchie[1].second}];

		for (int i = 2; i <= lung; i++)
			if (tabel[i] == 1)
				minim = min(minim, cap[{muchie[i].first, muchie[i].second}]);
			else
				minim = min(minim, flux[{muchie[i].first, muchie[i].second}]);

		for (int i = 1; i <= lung; i++)
			if (tabel[i] == 1)
			{
				suma += cost[{muchie[i].first, muchie[i].second}] * minim;
				cap[{muchie[i].first, muchie[i].second}] -= minim;
				flux[{muchie[i].second, muchie[i].first}] += minim;
			}
			else
			{
				suma += -cost[{muchie[i].second, muchie[i].first}] * minim;
				flux[{muchie[i].first, muchie[i].second}] -= minim;
				cap[{muchie[i].second, muchie[i].first}] += minim;
			}

		rezultatFlux += minim;
		rezultatCost += suma;
	}

	static void deleteAll()
	{
		delete[] gf;
		delete[] gft;
		delete[] viz;
		delete[] beenThere;
		delete[] dist;
		delete[] positiveDist;
		delete[] tata;
		delete[] tabelTata;
		delete[] newDist;
		delete[] tabel;
		delete[] muchie;
		cap.clear();
		flux.clear();
		cost.clear();
	}
	static void assignAll(const int& n)
	{
		gf = new vector <int>[n + 1]();
		gft = new vector <int>[n + 1]();
		beenThere = new bool[n + 1]();
		viz = new bool[n + 1]();
		dist = new T[n + 1]();
		positiveDist = new T[n + 1]();
		newDist = new T[n + 1]();
		tata = new int[n + 1]();
		tabelTata = new int[n + 1]();
		tabel = new int[n + 1]();
		muchie = new pair<int, int>[n + 1]();
		gfSize = n;
		rezultatFlux = 0;
		rezultatCost = 0;
	}
public:
	static void generate(const int& n, vector <tuple<int, T, T>> graf[])
	{
		deleteAll();
		assignAll(n);

		for (int i = 1; i <= n; i++)
			for (const auto& vec : graf[i])
			{
				gf[i].push_back(get<0>(vec));
				gft[get<0>(vec)].push_back(i);
				cap[{i, get<0>(vec)}] = get<1>(vec);
				cost[{i, get<0>(vec)}] = get<2>(vec);
			}

		bellman();

		while (djikstra())
		{
			int nod = gfSize, vf = 0;
			while (nod != 1)
			{
				muchie[++vf] = { tata[nod], nod };
				tabel[vf] = tabelTata[nod];
				nod = tata[nod];
			}

			drum(vf);
		}
	}
};
template <class T> int MaxFlowMinCost<T>::gfSize = 0;
template <class T> vector <int>* MaxFlowMinCost<T>::gf = NULL;
template <class T> vector <int>* MaxFlowMinCost<T>::gft = NULL;
template <class T> map <pair<int, int>, T> MaxFlowMinCost<T>::cap = {};
template <class T> map <pair<int, int>, T> MaxFlowMinCost<T>::flux = {};
template <class T> map <pair<int, int>, T> MaxFlowMinCost<T>::cost = {};
template <class T> T MaxFlowMinCost<T>::rezultatFlux = 0;
template <class T> T MaxFlowMinCost<T>::rezultatCost = 0;
template <class T> bool* MaxFlowMinCost<T>::viz = NULL;
template <class T> bool* MaxFlowMinCost<T>::beenThere = NULL;
template <class T> T* MaxFlowMinCost<T>::dist = NULL;
template <class T> T* MaxFlowMinCost<T>::positiveDist = NULL;
template <class T> T* MaxFlowMinCost<T>::newDist = NULL;
template <class T> int* MaxFlowMinCost<T>::tata = NULL;
template <class T> int* MaxFlowMinCost<T>::tabelTata = NULL;
template <class T> int* MaxFlowMinCost<T>::tabel = NULL;
template <class T> pair <int, int>* MaxFlowMinCost<T>::muchie = NULL;
