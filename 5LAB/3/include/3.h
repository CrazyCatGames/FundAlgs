#ifndef INC_3_3_H
#define INC_3_3_H

#include <iostream>
#include <bitset>
#include <stdexcept>
#include <cstddef>

class logical_values_array {
private:
	unsigned int value;

public:
	logical_values_array(unsigned int val = 0);

	unsigned int GetValue() const;
	void SetValue(unsigned int val);

	logical_values_array Inversion() const;
	logical_values_array Conjunction(const logical_values_array& other) const;
	logical_values_array Disjunction(const logical_values_array& other) const;
	logical_values_array Implication(const logical_values_array& other) const;
	logical_values_array Coimplication(const logical_values_array& other) const;
	logical_values_array XOR(const logical_values_array& other) const;
	logical_values_array Equivalence(const logical_values_array& other) const;
	logical_values_array PierceArrow(const logical_values_array& other) const;
	logical_values_array ShefferStroke(const logical_values_array& other) const;

	static bool Equals(const logical_values_array& a, const logical_values_array& b);

	bool GetBit(size_t position) const;

	void ToBinaryString(char* buffer, size_t buffer_size) const;
};

#endif
