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
