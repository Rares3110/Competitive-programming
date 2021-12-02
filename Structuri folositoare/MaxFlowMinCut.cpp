/*exemplu apelare:
vector <pair<int, long, long>> gf[] = {...}
al 2-lea parametru este capacitatea muchiei si al 3-lea este costul muchiei
n = numar de noduri
primul nod este sursa si nodul n este destinatia

MaxFlowMinCost<long>::generate(n, gf);

!IMPORTANT! este mai lenta varianta asta decat cea fara clase
variabilele relevante sunt publice
*/
template <class T> class MaxFlowMinCost
{
public:
	static int gfSize;
	static vector <int>* gf;
	static T **cap, **flux, **cost;
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
				if (!beenThere[vec] || dist[nod] + cost[nod][vec] < dist[vec])
				{
					beenThere[vec] = true;
					dist[vec] = dist[nod] + cost[nod][vec];
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
				int positiveArc = cost[nod][vec] + dist[nod] - dist[vec];
 
				if (cap[nod][vec] && (!beenThere[vec] || positiveDist[nod] + positiveArc < positiveDist[vec]))
				{
					beenThere[vec] = true;
					positiveDist[vec] = positiveDist[nod] + positiveArc;
					pq.push({ -positiveDist[vec], vec });
					newDist[vec] = newDist[nod] + cost[nod][vec];
 
					tata[vec] = nod;
					tabelTata[vec] = 1;
				}
			}
 
			for (const auto& vec : gft[nod])
			{
				int positiveArc = -cost[vec][nod] + dist[nod] - dist[vec];
				if (flux[nod][vec] && (!beenThere[vec] || positiveDist[nod] + positiveArc < positiveDist[vec]))
				{
					beenThere[vec] = true;
					positiveDist[vec] = positiveDist[nod] + positiveArc;
					pq.push({ -positiveDist[vec], vec });
					newDist[vec] = newDist[nod] - cost[vec][nod];
 
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
				suma += cost[muchie[i].first][muchie[i].second] * minim;
				cap[muchie[i].first][muchie[i].second] -= minim;
				flux[muchie[i].second][muchie[i].first] += minim;
			}
			else
			{
				suma += -cost[muchie[i].second][muchie[i].first] * minim;
				flux[muchie[i].first][muchie[i].second] -= minim;
				cap[muchie[i].second][muchie[i].first] += minim;
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
		
		if(cap != NULL)
		{
			for(int i = 0; i <= gfSize; i++)
			{
				delete[] cap[i];
				delete[] flux[i];
				delete[] cost[i];
			}
 
			delete[] cap;
			delete[] flux;
			delete[] cost;
		}
	}
public:
	static void assignMaxSize(const int& n)
	{
		deleteAll();
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
 
		cap = new T*[n + 1]();
		flux = new T*[n + 1]();
		cost = new T*[n + 1]();
		for(int i = 0; i <= n; i++)
		{
			cap[i] = new T[n + 1]();
			flux[i] = new T[n + 1]();
			cost[i] = new T[n + 1]();
		}
	}
	static void generate(const int& n, vector <tuple<int, T, T>> graf[])
	{
		for(int i = 1; i <= gfSize; i++)
		{
			gf[i].clear();
			gft[i].clear();
		}
		
		for(int i = 1; i <= n; i++)
		{
			fill(cap[i] + 1, cap[i] + 1 + n, 0);
			fill(flux[i] + 1, flux[i] + 1 + n, 0);
			fill(cost[i] + 1, cost[i] + 1 + n, 0);
		}
		
		gfSize = n;
		rezultatFlux = 0;
		rezultatCost = 0;
		
		for (int i = 1; i <= n; i++)
			for (const auto& vec : graf[i])
			{
				gf[i].push_back(get<0>(vec));
				gft[get<0>(vec)].push_back(i);
				cap[i][get<0>(vec)] = get<1>(vec);
				cost[i][get<0>(vec)] = get<2>(vec);
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
template <class T> T** MaxFlowMinCost<T>::cap = NULL;
template <class T> T** MaxFlowMinCost<T>::flux = NULL;
template <class T> T** MaxFlowMinCost<T>::cost = NULL;
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
