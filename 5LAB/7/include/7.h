#ifndef INC_7_7_H
#define INC_7_7_H

#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include <iostream>
#include <algorithm>

class Product {
protected:
	std::string name;
	unsigned int id;
	double weight;
	double price;
	int shelfLife;

public:
	Product(const std::string& name, int id, double weight, double price, int shelfLife);
	Product(const Product& other);
	Product& operator=(const Product& other);
	virtual ~Product() = default;

	virtual double calculateStorageFee() const = 0;
	virtual void displayInfo() const = 0;

	int getId() const { return id; }
	std::string getName() const { return name; }
};

class PerishableProduct : public Product {
	std::time_t expirationDate;

public:
	PerishableProduct(const std::string& name, int id, double weight, double price, int shelfLife, std::time_t expirationDate);
	double calculateStorageFee() const override;
	void displayInfo() const override;

	std::time_t getExpirationDate() const { return expirationDate; }
};

class ElectronicProduct : public Product {
	int warrantyPeriod;
	double powerRating;

public:
	ElectronicProduct(const std::string& name, int id, double weight, double price, int shelfLife, int warrantyPeriod, double powerRating);
	double calculateStorageFee() const override;
	void displayInfo() const override;
};

class BuildingMaterial : public Product {
	bool flammability;

public:
	BuildingMaterial(const std::string& name, int id, double weight, double price, int shelfLife, bool flammability);
	double calculateStorageFee() const override;
	void displayInfo() const override;
};

class Warehouse {
	std::vector<std::shared_ptr<Product>> inventory;

public:
	Warehouse& operator+=(std::shared_ptr<Product> product);
	Warehouse& operator-=(int productId);
	std::shared_ptr<Product> operator[](int productId);

	void displayInventory() const;
	double calculateTotalStorageCost() const;
	std::vector<std::shared_ptr<Product>> getExpiringProducts(int days) const;

	friend std::ostream& operator<<(std::ostream& os, const Warehouse& warehouse);
};

#endif
