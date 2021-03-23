#ifndef POLYNOMIAL_H 
#define POLYNOMIAL_H
#include <sstream>

class Polynomial
{
private:
	int sen_deg;
	int jun_deg;
	int n;
	int* coefficients;

public:
	Polynomial();
	Polynomial(int sd, int jd, int coef[]);
	virtual ~Polynomial();
	Polynomial(const Polynomial& poly);
	Polynomial& operator=(const Polynomial& poly);

	friend bool operator==(const Polynomial& l_poly, const Polynomial& r_poly);
	friend bool operator!=(const Polynomial& l_poly, const Polynomial& r_poly);

	Polynomial zero_check();
	double get(int value);
	int& operator[](int index) const;
	int& operator[](int index);

	friend Polynomial operator* (int value, const Polynomial& poly);
	friend Polynomial operator* (const Polynomial& poly, int value);
	friend Polynomial operator* (const Polynomial& l_poly, const Polynomial& r_poly);
	friend Polynomial operator/ (const Polynomial& poly, int value);
	friend Polynomial operator+ (const Polynomial& l_poly, const Polynomial& r_poly);
	friend Polynomial operator- (const Polynomial& l_poly, const Polynomial& r_poly);
	friend Polynomial operator- (const Polynomial& poly);

	Polynomial operator-=(const Polynomial& r_poly);
	Polynomial operator+=(const Polynomial& r_poly);
	Polynomial operator*=(const Polynomial& r_poly);
	Polynomial operator*=(int value);
	Polynomial operator/=(int value);

	friend std::ostream& operator<< (std::ostream& stream, const Polynomial& poly);
	friend std::istream& operator>> (std::istream& stream, Polynomial& poly);
};


#endif

