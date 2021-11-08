class LongInt
{
private:
	static const long long Baza = 1000000000;
	vector <long long> cifre;
	bool isNeg;
	static void checkBit(LongInt& a, int poz)
	{
		while (a.cifre[poz] >= Baza)
		{
			if (a.cifre.size() - 1 == poz)
				a.cifre.push_back(a.cifre[poz] / Baza);
			else
				a.cifre[poz + 1] += a.cifre[poz] / Baza;

			a.cifre[poz] %= Baza;
			poz++;
		}
	}
	static void checkBitNeg(LongInt& a, int poz)
	{
		while (a.cifre[poz] < 0)
		{
			a.cifre[poz] += Baza;
			a.cifre[poz + 1]--;
			poz++;
		}
	}
public:
	LongInt()
	{
		cifre.push_back(0);
		isNeg = 0;
	}
	LongInt(long long a)
	{
		if (a < 0)
		{
			a *= -1;
			isNeg = 1;
		}
		else
			isNeg = 0;

		while (a >= Baza)
		{
			cifre.push_back(a % Baza);
			a /= Baza;
		}
		cifre.push_back(a);
	}
	LongInt(const string& a)
	{
		int minPoz = 0;
		if (a[0] == '-')
		{
			isNeg = 1;
			minPoz = 1;
		}
		else
			isNeg = 0;

		for (int i = a.size() - 1, nr; i >= minPoz; i -= 9)
		{
			nr = 0;
			for (int j = max(i - 8, minPoz); j <= i; j++)
				nr = nr * 10 + a[j] - '0';
			cifre.push_back(nr);
		}
	}
	LongInt(const LongInt& a)
	{
		cifre = a.cifre;
		isNeg = a.isNeg;
	}
	LongInt& operator =(const LongInt& a)
	{
		cifre = a.cifre;
		isNeg = a.isNeg;
		return *this;
	}
	LongInt operator +(const LongInt& a)
	{
		if (isNeg == a.isNeg)
		{
			LongInt rez(*this);
			for (int i = 0; i < a.cifre.size(); i++)
				if (rez.cifre.size() == i)
					rez.cifre.push_back(a.cifre[i]);
				else
				{
					rez.cifre[i] += a.cifre[i];
					checkBit(rez, i);
				}

			rez.isNeg = isNeg;
			return rez;
		}
		else
			return *this - LongInt(-1) * a;
	}
	void operator +=(const LongInt& a)
	{
		LongInt rez = *this + a;
		*this = rez;
	}
	LongInt operator -(const LongInt& a)
	{
		if (isNeg != a.isNeg)
			return *this + LongInt(-1) * a;

		if ((*this >= a && isNeg == 0) || (*this < a && isNeg == 1))
		{
			LongInt rez(*this);
			for (int i = a.cifre.size() - 1; i >= 0; i--)
			{
				rez.cifre[i] -= a.cifre[i];
				checkBitNeg(rez, i);
			}

			while (rez.cifre.size() > 1 && rez.cifre[rez.cifre.size() - 1] == 0)
				rez.cifre.pop_back();
			if (rez.cifre.size() == 1 && rez.cifre[0] == 0)
				rez.isNeg = 0;

			return rez;
		}
		else
		{
			LongInt rez(a);
			for (int i = cifre.size() - 1; i >= 0; i--)
			{
				rez.cifre[i] -= cifre[i];
				checkBitNeg(rez, i);
			}

			while (rez.cifre.size() > 1 && rez.cifre[rez.cifre.size() - 1] == 0)
				rez.cifre.pop_back();

			return rez;
		}
	}
	void operator -=(const LongInt& a)
	{
		LongInt rez = *this - a;
		*this = rez;
	}
	LongInt operator *(const LongInt& a)
	{
		LongInt rez;
		rez.isNeg = isNeg ^ a.isNeg;
		rez.cifre.assign(cifre.size() + a.cifre.size(), 0);

		for (int i = 0; i < cifre.size(); i++)
			if (cifre[i])
				for (int j = 0; j < a.cifre.size(); j++)
				{
					rez.cifre[i + j] += cifre[i] * a.cifre[j];
					checkBit(rez, i + j);
				}

		while (rez.cifre.size() > 1 && rez.cifre[rez.cifre.size() - 1] == 0)
			rez.cifre.pop_back();
		if (rez.cifre.size() == 1 && rez.cifre[0] == 0)
			rez.isNeg = 0;

		return rez;
	}
	void operator *=(const LongInt& a)
	{
		LongInt rez = *this * a;
		*this = rez;
	}
	bool operator ==(const LongInt& a)
	{
		if (cifre.size() != a.cifre.size() || isNeg != a.isNeg)
			return false;

		for (int i = 0; i < cifre.size(); i++)
			if (cifre[i] != a.cifre[i])
				return false;

		return true;
	}
	bool operator !=(const LongInt& a)
	{
		return !(*this == a);
	}
	bool operator >(const LongInt& a)
	{
		if (isNeg == 0 && a.isNeg == 1)
			return true;
		else if (isNeg == 1 && a.isNeg == 0)
			return false;

		if (cifre.size() > a.cifre.size())
			return !isNeg;
		else if (cifre.size() < a.cifre.size())
			return isNeg;

		for (int i = cifre.size() - 1; i >= 0; i--)
			if (cifre[i] != a.cifre[i])
				return (cifre[i] < a.cifre[i]) ^ !isNeg;

		return false;
	}
	bool operator <(const LongInt& a)
	{
		if (isNeg == 0 && a.isNeg == 1)
			return false;
		else if (isNeg == 1 && a.isNeg == 0)
			return true;

		if (cifre.size() > a.cifre.size())
			return isNeg;
		else if (cifre.size() < a.cifre.size())
			return !isNeg;

		for (int i = cifre.size() - 1; i >= 0; i--)
			if (cifre[i] != a.cifre[i])
				return (cifre[i] < a.cifre[i]) ^ isNeg;

		return false;
	}
	bool operator >=(const LongInt& a)
	{
		return !(*this < a);
	}
	bool operator <=(const LongInt& a)
	{
		return !(*this > a);
	}
	string toString()
	{
		string rez = "";
		if (isNeg)
			rez += "-";
		rez += to_string(cifre[cifre.size() - 1]);

		for (int i = cifre.size() - 2; i >= 0; i--)
			if (cifre[i] == 0)
				rez += string(9, '0');
			else
				rez += string(8 - log10(cifre[i]), '0') + to_string(cifre[i]);

		return rez;
	}
	friend ostream& operator<<(ostream& out, const LongInt& a);
	friend istream& operator>>(istream& in, LongInt& a);
};
