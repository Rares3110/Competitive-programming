/*exemplu apelare:
vector <pair<int, long>> gf[] = {...};
al doilea parametru este capacitatea muchiei
n = numar de noduri;

rezultat = MaxFlow<long>generare(n, gf);
*/
template <class T> class MaxFlow
{
	static int gfSize;
	static vector <int> *gf, *gft;
	static map <pair<int, int>, T> cost, flux; 
	static T rezultat;
 
	//bfs
	static int *nivel;
	static bool *viz, *usefull;
 
	//drum + dfs
	static pair <int, int> *muchie;
	static int *tabel;
 
	static bool bfs()
	{
		fill(viz + 1, viz + 1 + gfSize, 0);
		fill(usefull + 1, usefull + 1 + gfSize, 0);
		queue <int> q;
		q.push(1);
		
		viz[1] = usefull[1] = 1;
		nivel[1] = 1;
 
		while(!q.empty())
		{
			int nod = q.front();
			q.pop();
 
			for (auto vec : gf[nod])
				if (!viz[vec] && cost[{nod, vec}])
				{
					viz[vec] = 1;
					nivel[vec] = nivel[nod] + 1;
					q.push(vec);
					usefull[vec] = 1;
				}
 
			for (auto vec : gft[nod])
				if (!viz[vec] && flux[{nod, vec}])
				{
					viz[vec] = 1;
					nivel[vec] = nivel[nod] + 1;
					q.push(vec);
					usefull[vec] = 1;
				}
		}
		
		return viz[gfSize];
	}
 
	static void drum(const int &lung)
	{
		T minim;
 
		if (tabel[1] == 1)
			minim = cost[{muchie[1].first, muchie[1].second}];
		else
			minim = flux[{muchie[1].first, muchie[1].second}];
 
		for (int i = 2; i <= lung; i++)
			if (tabel[i] == 1)
				minim = min(minim, cost[{muchie[i].first, muchie[i].second}]);
			else
				minim = min(minim, flux[{muchie[i].first, muchie[i].second}]);
 
		for (int i = 1; i <= lung; i++)
			if (tabel[i] == 1)
			{
				cost[{muchie[i].first, muchie[i].second}] -= minim;
				flux[{muchie[i].second, muchie[i].first}] += minim;
			}
			else
			{
				flux[{muchie[i].first, muchie[i].second}] -= minim;
				cost[{muchie[i].second, muchie[i].first}] += minim;
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
		for (auto vec : gf[nod])
			if (nivel[vec] > nivel[nod] && cost[{nod, vec}])
			{
				muchie[vf] = {nod, vec};
				tabel[vf] = 1;
				usefull[vec] = dfs(vec, vf + 1);
				if(usefull[vec]) found = true;
			}
 
		for (auto vec : gft[nod])
			if (nivel[vec] > nivel[nod] && flux[{nod, vec}])
			{
				muchie[vf] = {nod, vec};
				tabel[vf] = 2;
				usefull[vec] = dfs(vec, vf + 1);
				if(usefull[vec]) found = true;
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
		cost.clear();
		flux.clear();
	}
	static void assignAll(const int &n)
	{
		gf = new vector <int> [n + 1]();
		gft = new vector <int> [n + 1]();
		nivel = new int [n + 1]();
		viz = new bool[n + 1]();
		usefull = new bool [n + 1]();
		muchie = new pair<int, int> [n + 1]();
		tabel = new int [n + 1]();
		rezultat = 0;
		gfSize = n;
	}
public:
	static T generate(const int &n, const vector <pair<int, T>> graf[])
	{
		deleteAll();
		assignAll(n);
 
		for(int i = 1; i <= n; i++)
			for(auto vec : graf[i])
			{
				gf[i].push_back(vec.first);
				gft[vec.first].push_back(i);
				cost[{i, vec.first}] = cost[{vec.first, i}] = vec.second;
			}
 
		while(bfs())
			while(dfs());
		
		return rezultat;
	}
};
template <class T> int MaxFlow<T>::gfSize = 0;
template <class T> vector <int>* MaxFlow<T>::gf = NULL;
template <class T> vector <int>* MaxFlow<T>::gft = NULL;
template <class T> map <pair<int, int>, T> MaxFlow<T>::cost = {};
template <class T> map <pair<int, int>, T> MaxFlow<T>::flux = {};
template <class T> int* MaxFlow<T>::nivel = NULL;
template <class T> bool* MaxFlow<T>::viz = NULL;
template <class T> bool* MaxFlow<T>::usefull = NULL;
template <class T> pair <int, int>* MaxFlow<T>::muchie = NULL;
template <class T> int* MaxFlow<T>::tabel = NULL;
template <class T> T MaxFlow<T>::rezultat = 0;