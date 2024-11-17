#include "include/4.h"

int main() {
	Complex c1(3, 4);
	Complex c2(5, -5);

	std::cout << "Complex number c1: " << c1 << "\n";
	std::cout << "Complex number c2: " << c2 << "\n";

	std::cout << "Real: " << c1.GetReal() << " Imag: " << c1.GetImag() << "i\n";
	std::cout << "Real: " << c2.GetReal() << " Imag: " << c2.GetImag() << "i\n";

	Complex sum = c1.Add(c2);
	std::cout << "Summary: " << sum << "\n";

	Complex difference = c1.Subtract(c2);
	std::cout << "Difference: " << difference << "\n";

	Complex product = c1.Multiply(c2);
	std::cout << "Product: " << product << "\n";

	try {
		Complex quotient = c1.Divide(c2);
		std::cout << "Quotient: " << quotient << "\n";
	} catch (const std::exception& e) {
		std::cout << "Error: " << e.what() << "\n";
	}

	std::cout << "Modulus " << c1 << ": " << c1.Modulus() << "\n";
	std::cout << "Argument " << c1 << " (in radians): " << c1.Argument() << "\n";

	return 0;
}