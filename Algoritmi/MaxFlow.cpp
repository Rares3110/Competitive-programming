#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

/*
Algoritmul Dinic:
>> BFS pentru a construi un graf pe nivele incepand de la sursa, in ideea de a minimiza lungimea 
drumului. 
>> Dupa DFS-uri repetate in care cautam doar de la un nivel mai mare decat cel initial pana nu mai 
putem ajunge la destinatie, mai mult, daca dupa un DFS pe un nod nu am ajuns la destinatie, 
il marcam ca sa nu mai pierdem iar vremea cu el.
>> Repetam pana BFS-ul nu mai ajunge la destinatie.
*/

ifstream fin("fisier.in");
ofstream fout("fisier.out");
int n, m, cost[1001][1001], flux[1001][1001];
vector <int> gf[1001], gft[1001];
int rezultat;

int nivel[1001];
bool usefull[1001];
bool bfs()
{
	bitset <1001> viz;
	queue <int> q;
	q.push(1);
	viz[1] = 1;
	nivel[1] = 1;
	usefull[1] = 1;

	for (int i = 2; i <= n; i++)
		usefull[i] = 0;

	while (!q.empty())
	{
		int nod = q.front();
		q.pop();

		for (auto vec : gf[nod])
			if (!viz[vec] && cost[nod][vec])
			{
				viz[vec] = 1;
				nivel[vec] = nivel[nod] + 1;
				q.push(vec);
				usefull[vec] = 1;
			}

		for (auto vec : gft[nod])
			if (!viz[vec] && flux[nod][vec])
			{
				viz[vec] = 1;
				nivel[vec] = nivel[nod] + 1;
				q.push(vec);
				usefull[vec] = 1;
			}
	}

	if (viz[n] == 1)
		return true;
	return false;
}
pair <int, int> muchie[1001];
int tabel[1001];
void drum(int lung)
{
	int minim = (1 << 28);

	for (int i = 1; i <= lung; i++)
		if (tabel[i] == 1)
			minim = min(minim, cost[muchie[i].F][muchie[i].S]);
		else
			minim = min(minim, flux[muchie[i].F][muchie[i].S]);

	for (int i = 1; i <= lung; i++)
		if (tabel[i] == 1)
		{
			cost[muchie[i].F][muchie[i].S] -= minim;
			flux[muchie[i].S][muchie[i].F] += minim;
		}
		else
		{
			flux[muchie[i].F][muchie[i].S] -= minim;
			cost[muchie[i].S][muchie[i].F] += minim;
		}

	rezultat += minim;
}
bool dfs(int nod = 1, int vf = 1)
{
	if (nod == n)
	{
		drum(vf - 1);
		return true;
	}

	bool found = 0;

	for (auto vec : gf[nod])
		if (nivel[vec] > nivel[nod] && cost[nod][vec])
		{
			muchie[vf] = { nod, vec };
			tabel[vf] = 1;
			usefull[vec] = dfs(vec, vf + 1);
			found = max(found, usefull[vec]);
		}

	for (auto vec : gft[nod])
		if (nivel[vec] > nivel[nod] && flux[nod][vec])
		{
			muchie[vf] = { nod, vec };
			tabel[vf] = 2;
			usefull[vec] = dfs(vec, vf + 1);
			found = max(found, usefull[vec]);
		}

	return found;
}

int main()
{
	fin >> n >> m;

	for (int k = 1, i, j, c; k <= m; k++)
	{
		fin >> i >> j >> c;
		gf[i].push_back(j);
		cost[i][j] = c;
		gft[j].push_back(i);
	}

	while (bfs())
		while (dfs());

	fout << rezultat;
	return 0;
}