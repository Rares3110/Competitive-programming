#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

/*
Algoritm:
>> Bellman-Ford pentru aflarea distantelor.
>> Djikstra repetat pentru aflarea drumurilor, cu arce speciale pentru a avea doar valori pozitive.
*/

ifstream fin("fisier.in");
ofstream fout("fisier.out");
vector <int> gf[351], gft[351];
int cap[351][351], flux[351][351], cost[351][351];
int n, m, s, d, rezultat;

int dist[351];
void bellman_ford()  //primul Bellman-Ford care sa calculeze distantele minime
{
	for (int i = 1; i <= n; i++)
		if (i != s)
			dist[i] = 1 << 26;

	queue <int> q;
	bitset <351> inQ;
	q.push(s);
	inQ[s] = 1;

	while (!q.empty())
	{
		int nod = q.front();
		q.pop();
		inQ[nod] = 0;

		for (auto vec : gf[nod])
			if (dist[nod] + cost[nod][vec] < dist[vec])
			{
				dist[vec] = dist[nod] + cost[nod][vec];
				if (!inQ[vec])
				{
					q.push(vec);
					inQ[vec] = 1;
				}
			}
	}
}
int positiveDist[351], tata[351], tabelTata[351], newDist[351];
bool djikstra()  //Djikstra pentru aflarea drumului minim cu ajutorul altor arce
{
	for (int i = 1; i <= n; i++)
		if (i != s)
			positiveDist[i] = 1 << 26;

	priority_queue <pair<int, int>> pq;
	bitset <351> viz;
	pq.push({ 0, s });

	while (!pq.empty())
	{
		int nod = pq.top().second;
		pq.pop();

		if (viz[nod] == 1)
			continue;
		viz[nod] = 1;

		for (auto vec : gf[nod])
		{
			int positiveArc = cost[nod][vec] + dist[nod] - dist[vec];
			/*
			fie un arc de la x -> y, valoare(x -> y) >= distanta(y) - distanta(x)
			prin urmare valoare(x -> y) + distanta(x) - distanta(y) >= 0
			ne intereseaza doar acea diferenta intre valoarea arcului si distanta minima
			*/
			if (cap[nod][vec] && positiveDist[nod] + positiveArc < positiveDist[vec])
			{
				positiveDist[vec] = positiveDist[nod] + positiveArc;
				pq.push({ -positiveDist[vec], vec });
				/*
				daca am schimbat in graful pozitiv atunci schimbam si in cel original
				schimbam abia la final deoarece graful pozitiv functioneaza cu valorile 
				originale si daca am schimba acum in dist am creea erori 
				*/
				newDist[vec] = newDist[nod] + cost[nod][vec];

				tata[vec] = nod;
				tabelTata[vec] = 1;
			}
		}

		for (auto vec : gft[nod])
		{
			int positiveArc = -cost[vec][nod] + dist[nod] - dist[vec];
			if (flux[nod][vec] && positiveDist[nod] + positiveArc < positiveDist[vec])
			{
				positiveDist[vec] = positiveDist[nod] + positiveArc;
				pq.push({ -positiveDist[vec], vec });
				newDist[vec] = newDist[nod] - cost[vec][nod];

				tata[vec] = nod;
				tabelTata[vec] = 2;
			}
		}
	}

	for (int i = 1; i <= n; i++)
		dist[i] = newDist[i];

	if (positiveDist[d] != (1 << 26))
		return true;
	return false;
}
pair <int, int> muchie[351];
int tabel[351];
void drum(int lung)
{
	int minim = 1 << 26, suma = 0;

	for (int i = 1; i <= lung; i++)
		if (tabel[i] == 1)
			minim = min(minim, cap[muchie[i].F][muchie[i].S]);
		else
			minim = min(minim, flux[muchie[i].F][muchie[i].S]);

	for (int i = 1; i <= lung; i++)
		if (tabel[i] == 1)
		{
			suma += cost[muchie[i].F][muchie[i].S] * minim;
			cap[muchie[i].F][muchie[i].S] -= minim;
			flux[muchie[i].S][muchie[i].F] += minim;
		}
		else
		{
			suma += -cost[muchie[i].S][muchie[i].F] * minim;
			flux[muchie[i].F][muchie[i].S] -= minim;
			cap[muchie[i].S][muchie[i].F] += minim;
		}

	rezultat += suma;
}

int main()
{
	fin >> n >> m >> s >> d;

	for (int k = 1, i, j, Cap, Cost; k <= m; k++)
	{
		fin >> i >> j >> Cap >> Cost;

		gf[i].push_back(j);
		gft[j].push_back(i);
		cap[i][j] = Cap;
		cost[i][j] = Cost;
	}

	bellman_ford();

	while (djikstra())
	{
		int nod = d, vf = 0;
		while (nod != s)
		{
			muchie[++vf] = { tata[nod], nod };
			tabel[vf] = tabelTata[nod];
			nod = tata[nod];
		}

		drum(vf);
	}

	fout << rezultat;
	return 0;
}