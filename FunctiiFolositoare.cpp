//sorteaza un vector si elimina duplicatele

template <class T> void sortUnique(vector <T> &vect)
{
	sort(vect.begin(), vect.end());

	int poz = 0;
	for (int i = 1; i < vect.size(); i++)
		if (vect[i] != vect[i - 1])
			vect[++poz] = vect[i];

	vect.erase(vect.begin() + poz + 1, vect.end());
}

template <class T> void sortUnique(T vect[], int left, int &right)
{
	sort(vect + left, vect + right + 1);

	int poz = left;
	for (int i = left + 1; i <= right; i++)
		if (vect[i] != vect[i - 1])
			vect[++poz] = vect[i];

	right = poz;
}

template <class T> T eulerNumber(T number)
{
	vector<pair<T, int>> dv;

	for(T d = 2; d * d <= number; d++)
		if(number % d == 0)
		{
			dv.push_back({d, 0});
			while(number % d == 0)
			{
				dv[dv.size() - 1].second++;
				number /= d;
			}
		}

	if(number > 1)
		dv.push_back({number, 1});

	T rez = 1;
	for(auto per : dv)
	{
		for(int i = 1; i <= per.second - 1; i++)
			rez *= per.first;
		rez *= (per.first - 1);
	}

	return rez;
}
