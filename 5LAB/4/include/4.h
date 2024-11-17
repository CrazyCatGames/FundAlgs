#ifndef INC_4_4_H
#define INC_4_4_H

#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

class Complex {
private:
	double real;
	double imag;

public:
	Complex(double r = 0, double i = 0);

	double GetReal() const;
	double GetImag() const;

	Complex Add(const Complex& other) const;
	Complex Subtract(const Complex& other) const;
	Complex Multiply(const Complex& other) const;
	Complex Divide(const Complex& other) const;

	double Modulus() const;
	double Argument() const;

	friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};


#endif
