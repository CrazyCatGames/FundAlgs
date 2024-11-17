#include "include/2.h"


int main() {
	std::vector<std::byte> key = {std::byte{1}, std::byte{2}, std::byte{3}, std::byte{4}, std::byte{5}};

	Encoder enc(key);

	std::string input_file = R"(input.txt)";
	std::string encrypted_file = R"(encrypted.bin)";
	if (enc.Encode(input_file, encrypted_file, true)) {
		std::cout << "File encrypted successfully: " << encrypted_file << '\n';
	}

	std::vector<std::byte> new_key = {std::byte{6}, std::byte{7}, std::byte{8}, std::byte{9}, std::byte{10}};
	enc.SetKey(new_key);

	std::string encrypted_file_new = R"(encrypted_new.bin)";
	if (enc.Encode(input_file, encrypted_file_new, true)) {
		std::cout << "File encrypted successfully with new key: " << encrypted_file_new << '\n';
	}

	std::string decrypted_file_new = R"(output_new.txt)";
	if (enc.Encode(encrypted_file_new, decrypted_file_new, false)) {
		std::cout << "File decrypted successfully with new key: " << decrypted_file_new << '\n';
	}

	enc.SetKey(key);

	std::string decrypted_file = R"(output.txt)";
	if (enc.Encode(encrypted_file, decrypted_file, false)) {
		std::cout << "File decrypted successfully: " << decrypted_file << '\n';
	}
	return 0;
}
