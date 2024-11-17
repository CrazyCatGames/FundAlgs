#include "include/1.h"


int main() {
	binary_int a(15), b(4);
	std::cout << "a = " << a << ", b = " << b << std::endl;
	binary_int c = a + b;
	std::cout << "a + b = " << c << std::endl;
	a += b;
	std::cout << "a += b: " << a << std::endl << std::endl;


	std::cout << "a = " << a << ", b = " << b << std::endl;
	binary_int z = a - b;
	std::cout << "a - b = " << z << std::endl;
	a -= b;
	std::cout << "a -= b: " << a << std::endl << std::endl;


	std::cout << "a = " << a << ", b = " << b << std::endl;
	binary_int d = a * b;
	std::cout << "a * b = " << d << std::endl;
	a *= b;
	std::cout << "a *= b: " << a << std::endl << std::endl;



	std::cout << "a = " << a << std::endl;
	std::cout << "-a = " << -a << std::endl << std::endl;


	std::cout << "a++ = " << a++  << ", a = " << a << std::endl;
	std::cout << "++a = " << ++a << " , a = " << a << std::endl << std::endl;


	std::cout << "a-- = " << a--  << ", a = " << a << std::endl;
	std::cout << "--a = " << --a << " , a = " << a << std::endl << std::endl;

	std::cout << "a = " << a << std::endl;
	binary_int q = a << 2;
	std::cout << "a << 2 = " << q << std::endl;
	a <<= 2;
	std::cout << "a <<= 2: " << a << std::endl << std::endl;


	std::cout << "a = " << a << std::endl;
	binary_int w = a >> 2;
	std::cout << "a >> 2 = " << w << std::endl;
	a >>= 2;
	std::cout << "a >>= 2: " << a << std::endl << std::endl;


	binary_int V(999999999);
	std::cout << "V = " << V << std::endl;
	std::pair<binary_int, binary_int> result = V.split();
	std::cout << "Old high half: " << result.first << ", low half: " << result.second << std::endl;

	return 0;
}