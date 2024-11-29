#include "../include/3.h"
#include <bitset>
#include <cstring>
#include <stdexcept>

logical_values_array::logical_values_array(unsigned int val) : value(val) {}

unsigned int logical_values_array::GetValue() const {
	return value;
}

void logical_values_array::SetValue(unsigned int val) {
	value = val;
}

logical_values_array logical_values_array::Inversion() const {
	return {~value};
}

logical_values_array logical_values_array::Conjunction(const logical_values_array& other) const {
	return {value & other.value};
}

logical_values_array logical_values_array::Disjunction(const logical_values_array& other) const {
	return {value | other.value};
}

logical_values_array logical_values_array::Implication(const logical_values_array& other) const {
	return {~value | other.value};
}

logical_values_array logical_values_array::Coimplication(const logical_values_array& other) const {
	return {value & ~other.value};
}

logical_values_array logical_values_array::XOR(const logical_values_array& other) const {
	return {value ^ other.value};
}

logical_values_array logical_values_array::Equivalence(const logical_values_array& other) const {
	return Inversion().XOR(other).Inversion();
}

logical_values_array logical_values_array::PierceArrow(const logical_values_array& other) const {
	return {~(value | other.value)};
}

logical_values_array logical_values_array::ShefferStroke(const logical_values_array& other) const {
	return {~(value & other.value)};
}

bool logical_values_array::Equals(const logical_values_array& a, const logical_values_array& b) {
	return a.value == b.value;
}

bool logical_values_array::GetBit(size_t position) const {
	if (position >= sizeof(unsigned int) * 8) {
		throw std::out_of_range("Bit position out of range");
	}
	return (value >> position) & 1;
}

void logical_values_array::ToBinaryString(char* buffer, size_t buffer_size) const {
	if (buffer_size < sizeof(unsigned int) * 8 + 1) {
		throw std::invalid_argument("Buffer size is too small");
	}
	std::bitset<sizeof(unsigned int) * 8> bits(value);
	std::strncpy(buffer, bits.to_string().c_str(), buffer_size - 1);
	buffer[buffer_size - 1] = '\0';
}
