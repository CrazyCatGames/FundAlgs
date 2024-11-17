#ifndef INC_1_1_H
#define INC_1_1_H

#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Encoder {
private:
	std::vector<std::byte> key;
	void KeyInit(std::vector<std::byte> &S) const;

	void ProcessStream(std::ifstream &input, std::ofstream &output) const;

public:
	explicit Encoder(const std::vector<std::byte> &encryption_key);

	void SetKey(const std::vector<std::byte> &new_key);

	bool Encode(const std::string &input_path, const std::string &output_path, bool encrypt) const;
};

#endif
