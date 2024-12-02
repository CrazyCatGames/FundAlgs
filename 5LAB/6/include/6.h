#ifndef INC_6_6_H
#define INC_6_6_H

#include <algorithm>
#include <compare>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <stdexcept>

class vector final {
private:
	double *array;
	size_t _capacity, _size;

	void _resize(size_t new_capacity);

public:
	class iterator final {
	private:
		double *_ptr;

	public:
		iterator(double *ptr);
		double const &operator*() const;
		double &operator*();
		iterator &operator++();
		iterator operator++(int);
		iterator &operator--();
		iterator operator--(int);
		iterator operator+(size_t shift) const;
		iterator &operator+=(size_t shift);
		iterator operator-(size_t shift) const;
		iterator &operator-=(size_t shift);
		double *operator->();
		double const *operator->() const;
		double &operator[](size_t shift);
		double operator[](size_t shift) const;
		size_t operator-(const iterator &iter) const;
		bool operator==(const iterator &iter) const;
		bool operator!=(const iterator &iter) const;
		bool operator>(const iterator &iter) const;
		bool operator>=(const iterator &iter) const;
		bool operator<(const iterator &iter) const;
		bool operator<=(const iterator &iter) const;
	};

	vector(size_t count_elements, double default_value);
	vector(size_t count_elements);

	template<typename Iterator>
	vector(Iterator begin, Iterator end);

	vector(std::initializer_list<double> list);
	vector(const vector &v);

	vector &operator=(vector const &v);

	~vector();

	double &at(size_t index);
	double const &at(size_t index) const;
	double &front();
	double const &front() const;
	double &back();
	double const &back() const;
	double *data();
	double const *data() const;
	bool empty() const;
	size_t size() const;
	void reserve(size_t num);
	size_t capacity() const;
	void shrink_to_fit();
	void clear();
	void insert(size_t index, double elem);
	void erase(size_t index);
	void push_back(double elem);
	void pop_back();
	void resize(size_t size, double elem);
	bool operator==(vector const &v) const;
	int operator<=>(vector const &v) const;

	iterator begin();
	iterator end();
	const iterator begin() const;
	const iterator end() const;
};

#endif
