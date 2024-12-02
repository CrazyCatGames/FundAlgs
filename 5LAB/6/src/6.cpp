#include "../include/6.h"

vector::iterator::iterator(double *ptr) : _ptr{ptr} {}

double const &vector::iterator::operator*() const { return *_ptr; }
double &vector::iterator::operator*() { return *_ptr; }

vector::iterator &vector::iterator::operator++() {
	_ptr++;
	return *this;
}

vector::iterator vector::iterator::operator++(int) {
	iterator tmp = *this;
	++(*this);
	return tmp;
}

vector::iterator &vector::iterator::operator--() {
	_ptr--;
	return *this;
}

vector::iterator vector::iterator::operator--(int) {
	iterator tmp = *this;
	--(*this);
	return tmp;
}

vector::iterator vector::iterator::operator+(size_t shift) const { return {_ptr + shift}; }
vector::iterator &vector::iterator::operator+=(size_t shift) {
	_ptr += shift;
	return *this;
}

vector::iterator vector::iterator::operator-(size_t shift) const { return {_ptr - shift}; }
vector::iterator &vector::iterator::operator-=(size_t shift) {
	_ptr -= shift;
	return *this;
}

double *vector::iterator::operator->() { return _ptr; }
double const *vector::iterator::operator->() const { return _ptr; }

double &vector::iterator::operator[](size_t shift) { return *(_ptr + shift); }
double vector::iterator::operator[](size_t shift) const { return *(_ptr + shift); }


size_t vector::iterator::operator-(const iterator &iter) const { return _ptr - iter._ptr; }
bool vector::iterator::operator==(const iterator &iter) const { return _ptr == iter._ptr; }
bool vector::iterator::operator!=(const iterator &iter) const { return _ptr != iter._ptr; }
bool vector::iterator::operator>(const iterator &iter) const { return _ptr > iter._ptr; }
bool vector::iterator::operator>=(const iterator &iter) const { return _ptr >= iter._ptr; }
bool vector::iterator::operator<(const iterator &iter) const { return _ptr < iter._ptr; }
bool vector::iterator::operator<=(const iterator &iter) const { return _ptr <= iter._ptr; }

vector::vector(size_t count_elements, double default_value) : array{new double[count_elements]}, _size(count_elements), _capacity(count_elements) {
	std::fill_n(array, count_elements, default_value);
}

vector::vector(size_t count_elements) : vector(count_elements, 0.0) {}

template<typename Iterator>
vector::vector(Iterator const begin, Iterator const end) {
	auto distance = end - begin;
	array = new double[distance];
	_capacity = _size = distance;
	std::copy(begin, end, array);
}

vector::vector(std::initializer_list<double> list) : _capacity{list.size()}, _size(list.size()), array{new double[list.size()]} {
	std::copy(list.begin(), list.end(), array);
}

vector::vector(const vector &v) : vector(v.begin(), v.end()) {}

vector &vector::operator=(vector const &v) {
	if (this != &v) {
		_resize(v._size);
		std::copy(v.array, v.array + v._size, array);
		_size = v._size;
	}
	return *this;
}

vector::~vector() { delete[] array; }

void vector::_resize(size_t new_capacity) {
	double *resize;
	resize = new double[new_capacity];
	unsigned long long count = std::min(_size, new_capacity);
	std::copy(array, array + count, resize);
	delete[] array;
	array = resize;
	_capacity = new_capacity;
	_size = count;
}


double &vector::at(size_t index) {
	if (index < 0 || index >= _size) throw std::range_error("Out of range");
	return array[index];
}

double const &vector::at(size_t index) const {
	if (index < 0 || index >= _size) throw std::range_error("Out of range");
	return array[index];
}

double &vector::front() {
	if (_size == 0) throw std::range_error("Out of range");
	return array[0];
}

double const &vector::front() const {
	if (_size == 0) throw std::range_error("Out of range");
	return array[0];
}

double &vector::back() {
	if (_size == 0) throw std::range_error("Out of range");
	return array[_size - 1];
}

double const &vector::back() const {
	if (_size == 0) throw std::range_error("Out of range");
	return array[_size - 1];
}

double *vector::data() { return array; }

double const *vector::data() const { return array; }

bool vector::empty() const { return !_size; }

size_t vector::size() const { return _size; }

void vector::reserve(size_t num) {
	if (num > _capacity) _resize(num);
}

size_t vector::capacity() const { return _capacity; }

void vector::shrink_to_fit() {
	if (_capacity > _size) _resize(_size);
}

void vector::clear() { _size = 0; }

void vector::insert(size_t index, double elem) {
	if (index > _size) throw std::range_error("Out of range");

	if (_size >= _capacity) _resize(_capacity * 2);

	++_size;
	for (size_t i = _size - 1; i > index; --i) {
		array[i] = array[i - 1];
	}
	array[index] = elem;
}

void vector::erase(size_t index) {
	if (index >= _size) return;

	for (size_t i = index; i < _size - 1; ++i) {
		array[i] = array[i + 1];
	}

	--_size;
}

void vector::push_back(double element) {
	if (_size >= _capacity) _resize(_capacity * 2);
	array[_size++] = element;
}

void vector::pop_back() {
	if (_size > 0) --_size;
}

void vector::resize(size_t size, double elem) {
	size_t old_size = _size;
	_resize(size);
	if (size > old_size) std::fill(array + old_size, array + size, elem);

	_size = size;
}

int vector::operator<=>(vector const &v) const {
	for (size_t i = 0; i < std::min(_size, v._size); ++i) {
		if (array[i] < v.array[i]) return -1;
		if (array[i] > v.array[i]) return 1;
	}
	if (_size < v._size) return -1;
	if (_size > v._size) return 1;
	return 0;
}

bool vector::operator==(vector const &v) const {
	if (_size != v._size) return false;
	return std::equal(array, array + _size, v.array);
}

vector::iterator vector::begin() { return {array}; }
vector::iterator vector::end() { return {array + _size}; }
const vector::iterator vector::begin() const { return iterator(array); }
const vector::iterator vector::end() const { return iterator(array + _size); }
