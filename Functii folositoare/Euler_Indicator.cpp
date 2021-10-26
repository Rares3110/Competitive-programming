//returneaza indicatorul lui Euler pentru un numar

template <class T> T eulerIndicator(T number)
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