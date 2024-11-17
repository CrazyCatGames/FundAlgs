#include "../include/2.h"

Encoder::Encoder(const std::vector<std::byte> &encryption_key) : key(encryption_key) {}

void Encoder::SetKey(const std::vector<std::byte> &new_key) {
	key = new_key;
}

void Encoder::KeyInit(std::vector<std::byte> &S) const {
	size_t key_length = key.size();
	for (size_t i = 0; i < 256; ++i) {
		S[i] = static_cast<std::byte>(i);
	}
	size_t j = 0;
	for (size_t i = 0; i < 256; ++i) {
		j = (j + static_cast<size_t>(S[i]) + static_cast<size_t>(key[i % key_length])) % 256;
		std::swap(S[i], S[j]);
	}
}

void Encoder::ProcessStream(std::ifstream &input, std::ofstream &output) const {
	std::vector<std::byte> S(256);
	KeyInit(S);

	size_t i = 0, j = 0;
	char byte;
	while (input.get(byte)) {
		i = (i + 1) % 256;
		j = (j + static_cast<size_t>(S[i])) % 256;
		std::swap(S[i], S[j]);
		auto k = S[(static_cast<size_t>(S[i]) + static_cast<size_t>(S[j])) % 256];
		char output_byte = byte ^ static_cast<char>(k);
		output.put(output_byte);
	}
}

bool Encoder::Encode(const std::string &input_path, const std::string &output_path, bool encrypt) const {
	std::ifstream input(input_path, std::ios::binary);
	if (!input.is_open()) {
		std::cerr << "Error: Unable to open input file: " << input_path << '\n';
		return false;
	}

	std::ofstream output(output_path, std::ios::binary);
	if (!output.is_open()) {
		std::cerr << "Error: Unable to open output file: " << output_path << '\n';
		return false;
	}

	ProcessStream(input, output);
	return true;
}
