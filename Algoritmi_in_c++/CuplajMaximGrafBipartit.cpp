#include <bits/stdc++.h>
#define tooHigh 20001

using namespace std;

/*
Alogritmul Hopcroft-Karp:
>> BFS pornind de la toate nodurile care nu au pereche din prima multime:
reguli pentru a 2-a multime:
-- se alege nodul pereche din prima multime.
reguli pentru prima multime:
-- daca este vizitat se adauga intr-un graf pe nivele.
-- daca nu este vizitat atunci cautam cu DFS un drum pe graful nou pana la primul nivel.
>> Se observa din DFS un drum de tip (nod1 - nod2 = nod3 - ... - nod4 = nod5 - nod6) unde = inseamna ca avem 
pereche. Pentru a adauga o pereche modificam drumul in (nod1 = nod2 - nod3 = ... = nod4 - nod5 = nod6) 
si stergem toate nodurile drumului din graful pe nivele.
>> Repetam pana nu mai gasim nici-un drum.
*/

ifstream fin("fisier.in");
ofstream fout("fisier.out");
int n, m, e;
vector <int> gf[20001];
int rez, per[20001];

int nivel[20001], drum[20001];
bool dfs(int nod, int lung = 1)
{
	drum[lung] = nod;

	if (nivel[nod] == 1)
	{
		for (int i = 1; i <= lung; i += 2)
		{
			per[drum[i]] = drum[i + 1];
			per[drum[i + 1]] = drum[i];
			nivel[drum[i]] = tooHigh;
			nivel[drum[i + 1]] = tooHigh;
		}

		rez++;
		return true;
	}

	bool found = false;
	if (lung % 2 == 1)
	{
		for (auto vec : gf[nod])
			if (nivel[vec] < nivel[nod])
			{
				found = max(found, dfs(vec, lung + 1));
				if (found)
					break;
			}
	}
	else if (nivel[per[nod]] < nivel[nod])
		found = max(found, dfs(per[nod], lung + 1));

	return found;
}
bool bfs()
{
	queue <int> q;

	for (int i = 1; i <= n + m; i++)
		nivel[i] = tooHigh;

	for (int i = 1; i <= n; i++)
		if (!per[i])
		{
			q.push(i);
			nivel[i] = 1;
		}

	bool found = false;
	while (!q.empty())
	{
		int nod = q.front();
		q.pop();

		if (nod <= n)
		{
			for (auto vec : gf[nod])
				if (nivel[vec] == tooHigh)
				{
					nivel[vec] = nivel[nod] + 1;
					q.push(vec);
				}
		}
		else if (!per[nod])
		{
			found = max(found, dfs(nod));
		}
		else
		{
			nivel[per[nod]] = nivel[nod] + 1;
			q.push(per[nod]);
		}
	}

	return found;
}

int main()
{
	fin >> n >> m >> e;

	for (int k = 1, i, j; k <= e; k++)
	{
		fin >> i >> j;
		j += n;
		gf[i].push_back(j);
		gf[j].push_back(i);
	}

	while (bfs());

	fout << rez << '\n';

	for (int i = 1; i <= n; i++)
		if (per[i])
			fout << i << ' ' << per[i] - n << '\n';

	return 0;
}