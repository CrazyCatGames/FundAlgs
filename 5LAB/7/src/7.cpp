#include "../include/7.h"

Product::Product(const std::string& name, int id, double weight, double price, int shelfLife)
	: name(name), id(id), weight(weight), price(price), shelfLife(shelfLife) {}

Product::Product(const Product& other)
	: name(other.name), id(other.id), weight(other.weight), price(other.price), shelfLife(other.shelfLife) {}

Product& Product::operator=(const Product& other) {
	if (this != &other) {
		name = other.name;
		id = other.id;
		weight = other.weight;
		price = other.price;
		shelfLife = other.shelfLife;
	}
	return *this;
}

PerishableProduct::PerishableProduct(const std::string& name, int id, double weight, double price, int shelfLife, std::time_t expirationDate)
	: Product(name, id, weight, price, shelfLife), expirationDate(expirationDate) {}

double PerishableProduct::calculateStorageFee() const {
	std::time_t now = std::time(nullptr);
	double daysToExpire = std::difftime(expirationDate, now) / (24 * 60 * 60);
	return weight * (daysToExpire < 7 ? 1.3 : 1.0);
}

void PerishableProduct::displayInfo() const {
	std::cout << "Perishable Product - Name: " << name
			  << ", ID: " << id
			  << ", Weight: " << weight
			  << ", Price: $" << price
			  << ", Expiration Date: " << std::asctime(std::localtime(&expirationDate));
}

ElectronicProduct::ElectronicProduct(const std::string& name, int id, double weight, double price, int shelfLife, int warrantyPeriod, double powerRating)
	: Product(name, id, weight, price, shelfLife), warrantyPeriod(warrantyPeriod), powerRating(powerRating) {}

double ElectronicProduct::calculateStorageFee() const {
	return weight;
}

void ElectronicProduct::displayInfo() const {
	std::cout << "Electronic Product - Name: " << name
			  << ", ID: " << id
			  << ", Weight: " << weight
			  << ", Price: $" << price
			  << ", Warranty: " << warrantyPeriod << " months"
			  << ", Power: " << powerRating << "W\n";
}

BuildingMaterial::BuildingMaterial(const std::string& name, int id, double weight, double price, int shelfLife, bool flammability)
	: Product(name, id, weight, price, shelfLife), flammability(flammability) {}

double BuildingMaterial::calculateStorageFee() const {
	return weight * (flammability ? 2.0 : 1.0);
}

void BuildingMaterial::displayInfo() const {
	std::cout << "Building Material - Name: " << name
			  << ", ID: " << id
			  << ", Weight: " << weight
			  << ", Price: $" << price
			  << ", Flammability: " << (flammability ? "Yes" : "No") << "\n";
}

Warehouse& Warehouse::operator+=(std::shared_ptr<Product> product) {
	inventory.push_back(product);
	return *this;
}

Warehouse& Warehouse::operator-=(int productId) {
	for (const auto& product : inventory) {
		if (product->getId() == productId) {
			inventory.erase(inventory.begin() + 1);
			break;
		}
	}
	return *this;
}

std::shared_ptr<Product> Warehouse::operator[](int productId) {
	for (const auto& product : inventory) {
		if (product->getId() == productId) {
			return product;
		}
	}
	return nullptr;
}

std::ostream& operator<<(std::ostream& os, const Warehouse& warehouse) {
	os << "Warehouse Inventory:\n";
	for (const auto& product : warehouse.inventory) {
		product->displayInfo();
	}
	os << std::endl;
	return os;
}

void Warehouse::displayInventory() const {
	std::vector<std::shared_ptr<Product>> perishables;
	std::vector<std::shared_ptr<Product>> electronics;
	std::vector<std::shared_ptr<Product>> materials;

	for (const auto& product : inventory) {
		if (dynamic_cast<PerishableProduct*>(product.get())) {
			perishables.push_back(product);
		} else if (dynamic_cast<ElectronicProduct*>(product.get())) {
			electronics.push_back(product);
		} else if (dynamic_cast<BuildingMaterial*>(product.get())) {
			materials.push_back(product);
		}
	}

	std::cout << "Perishable Products:\n";
	for (const auto& product : perishables) {
		product->displayInfo();
	}
	std::cout << "------------------------\n";

	std::cout << "\nElectronic Products:\n";
	for (const auto& product : electronics) {
		product->displayInfo();
	}
	std::cout << "------------------------\n";

	std::cout << "\nBuilding Materials:\n";
	for (const auto& product : materials) {
		product->displayInfo();
	}
	std::cout << "------------------------\n";

	std::cout << std::endl;
}

double Warehouse::calculateTotalStorageCost() const {
	double totalCost = 0;
	for (const auto& product : inventory) {
		totalCost += product->calculateStorageFee();
	}
	return totalCost;
}

std::vector<std::shared_ptr<Product>> Warehouse::getExpiringProducts(int days) const {
	std::vector<std::shared_ptr<Product>> expiring;
	std::time_t now = std::time(nullptr);
	for (const auto& product : inventory) {
		auto perishable = std::dynamic_pointer_cast<PerishableProduct>(product);
		if (perishable) {
			double remainingDays = std::difftime(perishable->getExpirationDate(), now) / (24 * 60 * 60);
			if (remainingDays <= days) {
				expiring.push_back(perishable);
			}
		}
	}
	return expiring;
}
