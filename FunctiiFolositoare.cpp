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

template <class T> void sortUnique(T vect[], int offset, int &length)
{
	sort(vect + offset, vect + offset + length);

	int poz = offset;
	for (int i = offset + 1; i <= offset + length - 1; i++)
		if (vect[i] != vect[i - 1])
			vect[++poz] = vect[i];

	length = poz - offset + 1;
}
