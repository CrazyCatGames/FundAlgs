#include "include/7.h"

int main() {
	Warehouse warehouse;

	auto now = std::time(nullptr);

	warehouse += std::make_shared<PerishableProduct>("Milk", 1, 2.0, 10.0, 7, now + 5 * 24 * 60 * 60);
	warehouse += std::make_shared<ElectronicProduct>("Laptop", 2, 2.5, 1100.0, 365, 24, 65.0);
	warehouse += std::make_shared<BuildingMaterial>("Cement", 3, 50.0, 5.0, 30, false);
	warehouse += std::make_shared<PerishableProduct>("Camel milk", 69, 2.0, 20.0, 7, now + 29 * 24 * 60 * 60);

	std::cout << "Initial Inventory:\n";
	warehouse.displayInventory();

	std::cout << warehouse;

	warehouse -= 2;

	std::cout << "Inventory after deleting ID 2:\n";
	warehouse.displayInventory();

	std::cout << "Total Storage Cost: $" << warehouse.calculateTotalStorageCost() << std::endl << std::endl;

	auto expiring = warehouse.getExpiringProducts(20);
	std::cout << "Expiring Products:\n";
	for (const auto& product : expiring) {
		product->displayInfo();
	}

	return 0;
}
