#include "../include/4.h"


Complex::Complex(double r, double i) : real(r), imag(i) {}

double Complex::GetReal() const { return real; }
double Complex::GetImag() const { return imag; }

Complex Complex::Add(const Complex& other) const {
	return {real + other.real, imag + other.imag};
}

Complex Complex::Subtract(const Complex& other) const {
	return {real - other.real, imag - other.imag};
}

Complex Complex::Multiply(const Complex& other) const {
	return {
			real * other.real - imag * other.imag,
			real * other.imag + imag * other.real};
}

Complex Complex::Divide(const Complex& other) const {
	double denominator = other.real * other.real + other.imag * other.imag;
	if (denominator == 0) {
		throw std::logic_error("Division by zero");
	}
	return {
			(real * other.real + imag * other.imag) / denominator,
			(imag * other.real - real * other.imag) / denominator};
}

double Complex::Modulus() const {
	return std::sqrt(real * real + imag * imag);
}

double Complex::Argument() const {
	return std::atan2(imag, real);
}

std::ostream& operator<<(std::ostream& os, const Complex& c) {
	os << std::fixed << std::setprecision(3)
	   << c.GetReal() << (c.GetImag() >= 0 ? " + " : " - ") << std::abs(c.GetImag()) << "i";
	return os;
}
