#include "include/6.h"

int main() {
	vector v(5, 1.0);
	std::cout << "Initial vector (5 elements, all 1.0): ";
	for (auto it = v.begin(); it != v.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;


	v.push_back(3.0);
	v.push_back(4.0);
	std::cout << "After inserting 3.0 and 4.0: ";
	for (auto it = v.begin(); it != v.end(); ++it){
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	v.pop_back();
	std::cout << "After deleting last element: ";
	for (auto it = v.begin(); it != v.end(); ++it){
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	v.insert(2, 9.0);
	std::cout << "After insert 9.0 on position 2: ";
	for (auto it = v.begin(); it != v.end(); ++it){
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	v.erase(3);
	std::cout << "After deleting element with index 3: ";
	for (auto it = v.begin(); it != v.end(); ++it){
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	v.resize(8, 2.0);
	std::cout << "After resize to 8 with value 2.0: ";
	for (auto it = v.begin(); it != v.end(); ++it){
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	try{
		std::cout << "Element at index 4: " << v.at(4) << std::endl;
		std::cout << "Element at index 10 (error): " << v.at(10) << std::endl;
	}
	catch (const std::range_error &e){
		std::cout << "Error: " << e.what() << std::endl;
	}

	vector v2{5, 1.0};
	std::cout << "Vector v2 (5 elements, all 1.0) ";
	for (auto it = v2.begin(); it != v2.end(); ++it){
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	if (v == v2){
		std::cout << "Vectors v and v2 equal!" << std::endl;
	}
	else{
		std::cout << "Vectors v and v2 not equal!" << std::endl;
	}

	auto it = v.begin();
	std::cout << "First element as iterator: " << *it << std::endl;
	++it;
	std::cout << "Second element as iterator: " << *it << std::endl;

	return 0;
}
