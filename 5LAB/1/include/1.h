#ifndef INC_1_1_H
#define INC_1_1_H

#include <bitset>
#include <climits>
#include <iostream>
#include <limits>

class binary_int {
private:
	int value;

	static int Add(int a, int b);
	static int Substract(int a, int b);
	static int Multiply(int a, int b);

public:
	binary_int(int val = 0);
	~binary_int() = default;

	binary_int operator-() const;
	binary_int operator++(int);
	binary_int operator++();
	binary_int operator--(int);
	binary_int operator--();
	binary_int& operator+=(const binary_int& other);
	binary_int operator+(const binary_int& other) const;
	binary_int& operator-=(const binary_int& other);
	binary_int operator-(const binary_int& other) const;
	binary_int& operator*=(const binary_int& other);
	binary_int operator*(const binary_int& other) const;
	binary_int& operator<<=(int shift);
	binary_int operator<<(int shift) const;
	binary_int& operator>>=(int shift);
	binary_int operator>>(int shift) const;

	friend std::ostream& operator<<(std::ostream& os, const binary_int& bi);

	std::pair<binary_int, binary_int> split() const;
};


#endif
