#include "include/3.h"


int main() {
	logical_values_array a(0b1011);
	a.SetValue(0b1010);
	logical_values_array b(0b1100);

	std::cout << "Value of a: " << a.GetValue() << std::endl;

	std::cout << "Inversion of a: " << a.Inversion().GetValue() << std::endl;
	std::cout << "Conjunction of a and b: " << a.Conjunction(b).GetValue() << std::endl;
	std::cout << "Disjunction of a and b: " << a.Disjunction(b).GetValue() << std::endl;
	std::cout << "Implication of a to b: " << a.Implication(b).GetValue() << std::endl;
	std::cout << "Coimplication of a to b: " << a.Coimplication(b).GetValue() << std::endl;
	std::cout << "Equivalence of a to b: " << a.Equivalence(b).GetValue() << std::endl;
	std::cout << "Pierce arrow of a and b: " << a.PierceArrow(b).GetValue() << std::endl;
	std::cout << "Sheffer stroke of a and b: " << a.ShefferStroke(b).GetValue() << std::endl;

	std::cout << "Bit 2 of a: " << a.GetBit(2) << std::endl;

	std::cout << "Are a and b equal? " << (logical_values_array::Equals(a, b) ? "Yes" : "No") << std::endl;

	char *binary = new char[33];
	a.ToBinaryString(binary, 33 * sizeof(char));
	std::cout << "Binary representation of a: " << binary << std::endl;
	delete[] binary;
	return 0;
}
