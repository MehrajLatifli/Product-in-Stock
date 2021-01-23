#include <iostream>
#include <assert.h>
#include <string.h>
#include <string>

using namespace std;

class Product {
	int product_id;

	char* name;
	char* description;
	double price;
	double discount;
public:
	static int id;

	Product() : name(nullptr), description(nullptr), price(0.0), discount(0.0) {}

	Product(const char* name, const char* description, double price, double discount) {

		this->product_id = ++id;

		setName(name);
		setDescription(description);
		setPrice(price);
		setDiscount(discount);
	}

	Product(const Product& other)
	{
		this->product_id = other.id;

		setName(other.name);
		setDescription(other.description);
		setPrice(other.price);
		setDiscount(other.discount);
	}

	Product& operator=(const Product& other) {

		this->product_id = other.id;

		setName(other.name);
		setDescription(other.description);
		setPrice(other.price);
		setDiscount(other.discount);

		return *this;

	}

	Product(Product&& other) {

		setName(other.name);
		setDescription(other.description);
		setPrice(other.price);
		setDiscount(other.discount);


		delete other.name;
		other.name = nullptr;

		delete other.description;
		other.description = nullptr;

		other.price = 0.0;

		other.discount = 0.0;
	}



	static int getCurrentId() {
		return id;
	}

	void setCurrentId(int id) {
		assert(id > 0);
		this->product_id = ++id;
	}

	char* getName() const {
		return name;
	}

	void setName(const char* name) {
		assert(name != nullptr);
		int l = strlen(name);
		this->name = new char[l + 1];
		strcpy_s(this->name, l + 1, name);
	}

	char* getDescription() const {
		return description;
	}

	void setDescription(const char* description) {
		assert(description != nullptr);
		int l = strlen(description);
		this->description = new char[l + 1];
		strcpy_s(this->description, l + 1, description);
	}

	double getPrice() const {
		return price;
	}

	void setPrice(double price) {
		this->price = price;

	}

	double getDiscount() const {
		return discount;
	}

	void setDiscount(double discount) {
		this->discount = discount;

	}

	void show() {
		cout << " Product ID: \t\t\t" << this->product_id << endl;
		cout << " Product name: \t\t\t" << getName() << endl;
		cout << " Product description: \t\t" << getDescription() << endl;
		cout << " Product price: \t\t" << getPrice() << endl;
		cout << " After Product discount: \t" << getPrice() - (getPrice() * getDiscount() / 100) << endl;
		cout << " ==================================================================== \n";
	}



	friend ostream& operator<<(ostream& out, const Product& product);

	~Product()
	{
		delete[]  name;
		delete[] description;
	}
};

int Product::id = 0;

ostream& operator<<(ostream& out, const Product& product) {

	cout << " Product name: " << product.getName() << endl;
	cout << " Product description: " << product.getDescription() << endl;
	cout << " Product price: " << product.getPrice() << endl;
	cout << " After Product discount: " << product.getPrice() * product.getDiscount() / 100 << endl;
	cout << " ==================================================================== \n";

	return out;
}



class Stock {
	char* address;
	int count;
	Product** products;
public:
	Stock() :address(nullptr), count(0), products(nullptr) {}

	Stock(int count, const char* address, Product** products) {
		setCount(count);
		setAddress(address);
		setProduct(products);
	}
	Stock& operator=(const Stock& other)
	{
		setCount(other.count);
		setAddress(other.address);
		setProduct(other.products);

		return *this;
	}

	char* getAddress() const {
		return address;
	}

	void setAddress(const char* address) {
		assert(address != nullptr);
		int l = strlen(address);
		this->address = new char[l + 1];
		strcpy_s(this->address, l + 1, address);
	}

	int getCount() const {
		return count;
	}

	void setCount(int count) {
		this->count = count;

	}


	Product** getProduct()const {
		return products;
	}

	void setProduct(Product** products) {
		int c = getCount();
		this->products = new Product * [c];
		for (size_t i = 0; i < c; i++)
		{
			this->products[i] = products[i];
		}
	}

	void addProduct(Product*& newProduct) {
		int c = getCount();
		auto newProducts = new Product * [c + 1];
		for (size_t i = 0; i < c; i++)
		{
			newProducts[i] = products[i];
		}
		newProducts[c] = newProduct;
		setCount(c + 1);

		products = newProducts;
		newProducts = nullptr;
	}

	void show() {
		cout << " Stock address: " << getAddress() << endl;
	}

	friend ostream& operator<<(ostream& out, const Stock& Stockother);

	~Stock()
	{
		delete[]  address;

	}
};

ostream& operator<<(ostream& out, const Stock& Stockother) {
	for (size_t i = 0; i < Stockother.getCount(); i++)
	{
		Stockother.products[i]->show();
	}
	return out;
}

void main() {
	Product* p1 = new Product("DELL Alienware 17 R5 AW17R5", "Game notebook", 3500, 20);
	Product* p2 = new Product("SONY BDP-S1500/BMKS1", "Blu-Ray player", 199, 20);
	Product* p3 = new Product("HP 32-inch FHD (2FW77AA)", "Office monitor", 683, 25);
	Product** products = new Product * [2]{ p1, p2 };
	Stock stocks(2, "Ehmedli -> Yeni gunesli", products);
	stocks.addProduct(p3);
	cout << stocks;




}