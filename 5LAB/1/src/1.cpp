#include "../include/1.h"

binary_int::binary_int(int val) : value(val) {}

int binary_int::Add(int a, int b) {
	while (b != 0) {
		int carry = a & b;
		a = a ^ b;
		b = carry << 1;
	}
	return a;
}

int binary_int::Substract(int a, int b) {
	while (b != 0) {
		int borrow = (~a) & b;
		a = a ^ b;
		b = borrow << 1;
	}
	return a;
}

int binary_int::Multiply(int a, int b) {
	int result = 0;
	while (b != 0) {
		if (b & 1) {
			result = Add(result, a);
		}
		a <<= 1;
		b >>= 1;
	}
	return result;
}

binary_int binary_int::operator-() const {
	return {Add(~value, 1)};
}

binary_int binary_int::operator++(int) {
	binary_int temp = *this;
	value = Add(value, 1);
	return temp;
}

binary_int binary_int::operator++() {
	value = Add(value, 1);
	return *this;
}

binary_int binary_int::operator--(int) {
	binary_int temp = *this;
	value = Substract(value, 1);
	return temp;
}

binary_int binary_int::operator--() {
	value = Substract(value, 1);
	return *this;
}

binary_int& binary_int::operator+=(const binary_int& other) {
	value = Add(value, other.value);
	return *this;
}

binary_int binary_int::operator+(const binary_int& other) const {
	return {Add(value, other.value)};
}

binary_int& binary_int::operator-=(const binary_int& other) {
	value = Substract(value, other.value);
	return *this;
}

binary_int binary_int::operator-(const binary_int& other) const {
	return {Substract(value, other.value)};
}

binary_int& binary_int::operator*=(const binary_int& other) {
	value = Multiply(value, other.value);
	return *this;
}

binary_int binary_int::operator*(const binary_int& other) const {
	return {Multiply(value, other.value)};
}

binary_int& binary_int::operator<<=(int shift) {
	value <<= shift;
	return *this;
}

binary_int binary_int::operator<<(int shift) const {
	return {value << shift};
}

binary_int& binary_int::operator>>=(int shift) {
	value >>= shift;
	return *this;
}

binary_int binary_int::operator>>(int shift) const {
	return {value >> shift};
}

std::ostream& operator<<(std::ostream& os, const binary_int& bi) {
	os << std::bitset<32>(bi.value);
	return os;
}

std::pair<binary_int, binary_int> binary_int::split() const {
	int half_bits = std::numeric_limits<int>::digits >> 1;
	int high_mask = Add((1 << half_bits), Add(~1, 1));
	int low_mask = ~high_mask;

	int high = (value & high_mask);
	int low = (value & low_mask);

	return {binary_int(high), binary_int(low)};
}
