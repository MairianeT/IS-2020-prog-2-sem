#include "polynomial.h"
#include <iostream>
#include <sstream>
#include <math.h>


Polynomial::Polynomial()
{
	jun_deg = 0;
	sen_deg = 0;
	n = 0;
	coefficients = new int[1];
	coefficients[0] = 0;
}

Polynomial::Polynomial(int jd, int sd, int coef[])
{
	sen_deg = sd;
	jun_deg = jd;
	if (sd == jd && sd == 0) n = 0;
	n = sd - jd + 1;
	coefficients = new int[n];
	for (int i = 0; i < n; i++)
	{
		coefficients[i] = coef[i];
	}
}

Polynomial:: ~Polynomial()
{
	delete[] coefficients;
}

Polynomial::Polynomial(const Polynomial& poly)
{
	jun_deg = poly.jun_deg;
	sen_deg = poly.sen_deg;
	n = sen_deg - jun_deg + 1;
	if (sen_deg == jun_deg && sen_deg == 0) n = 0;
	coefficients = new int[n];
	for (int i = 0; i < n; i++)
	{
		coefficients[i] = poly.coefficients[i];
	}
}

Polynomial& Polynomial::operator=(const Polynomial& poly)
{
	if (&poly == this)
		return *this;
	delete[] coefficients;
	jun_deg = poly.jun_deg;
	sen_deg = poly.sen_deg;
	n = sen_deg - jun_deg + 1;
	if (sen_deg == jun_deg && sen_deg == 0) n = 0;
	coefficients = new int[n];
	for (int i = 0; i < n; i++)
	{
		coefficients[i] = poly.coefficients[i];
	}
	return *this;
}

Polynomial Polynomial::zero_check()
{
	int i = n - 1;
	while (coefficients[i] == 0 && i >= 0)
	{
		i--;
	}
	if (i < 0) 
	{
		return Polynomial();
	}
	else
	{
		Polynomial res(jun_deg, sen_deg, coefficients);
		res.sen_deg = res.jun_deg + i;
		i = 0;
		while (res.coefficients[i] == 0)
		{
			i++;
		}
		res.jun_deg += i;
		res.n = res.sen_deg - res.jun_deg + 1;
		int* a = new int[res.n];
		for (int j = 0; j < res.n; j++)
		{
			a[j] = res.coefficients[j + i];
		}
		delete[] res.coefficients;
		//todo res.coefficients = a
		res.coefficients = new int[res.n];
		for (int j = 0; j < res.n; j++)
		{
			res.coefficients[j] = a[j];
		}
		delete[] a;
		return res;
	}
}

//todo get O(n)
double Polynomial::get(int value)
{
	double res = 0;
	for (int i = 0; i < n; i++)
	{
		res += coefficients[i] * pow(value, jun_deg + i);
	}
	return res;
}

int Polynomial::operator[](int index) const
{
	int t = 0;
	if (index < jun_deg || index > sen_deg)
		return t;
	else
		return coefficients[index - jun_deg];
}

int& Polynomial::operator[](int index)
{
	if (index < jun_deg)
	{
		int* a = new int[n];
		for (int i = 0; i < n; i++)
			a[i] = coefficients[i];
		delete[] coefficients;
		coefficients = new int[sen_deg - index + 1];
		for (int i = 0; i < sen_deg - index + 1; i++)
			if (i < jun_deg - index)
				coefficients[i] = 0;
			else
				coefficients[i] = a[i - jun_deg + index];
		jun_deg = index;
		n = sen_deg - jun_deg + 1;
		delete[] a;
		return coefficients[0];
	}
	if (index > sen_deg)
	{
		int* a = new int[n];
		for (int i = 0; i < n; i++)
			a[i] = coefficients[i];
		delete[] coefficients;
		coefficients = new int[index - jun_deg + 1];
		for (int i = 0; i < index - jun_deg + 1; i++)
			if (i >= n)
				coefficients[i] = 0;
			else
				coefficients[i] = a[i];
		sen_deg = index;
		n = sen_deg - jun_deg + 1;
		delete[] a;
		return coefficients[sen_deg - jun_deg];
	}
	return coefficients[index - jun_deg];
}

Polynomial Polynomial::operator-=(const Polynomial& r_poly)
{
	return *this + (r_poly * -1);
}

Polynomial Polynomial::operator+=(const Polynomial& r_poly)
{
	if (n == 0)
		return r_poly;
	if (r_poly.n == 0)
		return *this;

	int a_jd, a_sd;

	if (jun_deg < r_poly.jun_deg)
		a_jd = jun_deg;
	else
		a_jd = r_poly.jun_deg;

	if (r_poly.sen_deg < sen_deg)
		a_sd = sen_deg;
	else
		a_sd = r_poly.sen_deg;

	int* a = new int[a_sd - a_jd + 1];
	for (int i = 0; i < a_sd - a_jd + 1; i++)
		a[i] = 0;

	for (int i = 0; i < r_poly.n; i++) {
		a[r_poly.jun_deg - a_jd + i] += r_poly.coefficients[i];
	}
	for (int i = 0; i < n; i++) {
		a[jun_deg - a_jd + i] += coefficients[i];
	}
	jun_deg = a_jd;
	sen_deg = a_sd;
	n = a_sd - a_jd + 1;
	delete[] coefficients;
	coefficients = new int[n];
	for (int i = 0; i < n; i++)
		coefficients[i] = a[i];
	delete[] a;
	*this = zero_check();

	return *this;
}

Polynomial Polynomial::operator*=(const Polynomial& r_poly)
{
	if (n == 0 || r_poly.n == 0) return Polynomial();

	jun_deg += r_poly.jun_deg;
	sen_deg += r_poly.sen_deg;
	int a_n = sen_deg - jun_deg + 1;

	int* a = new int[a_n];
	for (int i = 0; i < a_n; i++)
		a[i] = 0;
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < r_poly.n; j++) {
			a[i + j] += r_poly.coefficients[j] * coefficients[i];
		}
	delete[] coefficients;
	//todo coeefcs = a
	n = a_n;
	coefficients = new int[n];
	for (int i = 0; i < n; i++)
	{
		coefficients[i] = a[i];
	}
	delete[] a;
	return *this;
}

Polynomial Polynomial::operator*=(int value)
{
	if (value == 0) return Polynomial();

	for (int i = 0; i < n; i++)
	{
		coefficients[i] *= value;
	}
	return *this;
}

Polynomial Polynomial::operator/=(int value)
{
	for (int i = 0; i < n; i++) {
		coefficients[i] /= value;
	}
	*this = zero_check();
	return *this;
}

bool operator==(const Polynomial& l_poly, const Polynomial& r_poly)
{
	Polynomial l_res(l_poly.jun_deg, l_poly.sen_deg, l_poly.coefficients);
	Polynomial r_res(r_poly.jun_deg, r_poly.sen_deg, r_poly.coefficients);
	r_res = r_res.zero_check();
	l_res = l_res.zero_check();
	if (l_res.jun_deg != r_res.jun_deg || l_res.sen_deg != r_res.sen_deg)
		return false;
	for (int i = 0; i < l_res.n; i++) {
		if (l_res.coefficients[i] != r_res.coefficients[i])
			return false;
	}
	return true;
}

bool operator!=(const Polynomial& l_poly, const Polynomial& r_poly)
{
	return !(l_poly == r_poly);
}

Polynomial operator*(int value, const Polynomial& poly)
{
	Polynomial res = poly;
	res *= value;
	return res;
}

Polynomial operator*(const Polynomial& poly, int value)
{
	return value * poly;
}

Polynomial operator*(const Polynomial& l_poly, const Polynomial& r_poly)
{
	Polynomial res = l_poly;
	res *= r_poly;
	return res;
}

Polynomial operator/(const Polynomial& poly, int value)
{
	Polynomial res = poly;
	res /= value;
	return res;
}

Polynomial operator+(const Polynomial& l_poly, const Polynomial& r_poly)
{
	if (l_poly.n == 0)
		return r_poly;
	if (r_poly.n == 0)
		return l_poly;

	Polynomial res = l_poly;
	res += r_poly;

	return res;
}

//todo without creating new object
Polynomial operator-(const Polynomial& l_poly, const Polynomial& r_poly)
{
	return (l_poly + (-1 * r_poly));
}

Polynomial operator-(const Polynomial& poly)
{
	return (-1 * poly);
}



std::ostream& operator<< (std::ostream& stream, const Polynomial& poly)
{
	if (poly.n == 0)
		stream << "0" ;
	else
	{
		for (int i = poly.n - 1; i >= 0; i--)
		{
			if (poly.coefficients[i] != 0)
			{
				if (i == poly.n - 1)
					if (poly.coefficients[i] == -1)
						if (i + poly.jun_deg == 0)
							stream << "-1";
						else
							stream << "-";
					else
					{
						if (poly.coefficients[i] == 1 && i + poly.jun_deg == 0)
							stream << "1";
						else
							if (poly.coefficients[i] != 1)
								stream << poly.coefficients[i];
					}
				else
					if (poly.coefficients[i] < 0)
						if (poly.coefficients[i] == -1)
							if (i + poly.jun_deg == 0)
								stream << "-1";
							else
								stream << "-";
						else
							stream << poly.coefficients[i];
					else
						if (poly.coefficients[i] == 1)
							if (poly.jun_deg + i == 0)
								stream << "+1";
							else
								stream << "+";
						else
							if (poly.coefficients[i] != 0)
								stream << "+" << poly.coefficients[i];

				if (poly.jun_deg + i == 1)
					stream << "x";
				else if (poly.jun_deg + i != 0)
					stream << "x^" << poly.jun_deg + i;
			}
		}
	}
	return stream;
}

std::istream& operator>> (std::istream& stream, Polynomial& poly)
{
	stream >> poly.jun_deg >> poly.sen_deg;
	for (int i = 0; i < poly.jun_deg - poly.sen_deg + 1; i++)
	{
		stream >> poly.coefficients[i];
	}

	return stream;
}

