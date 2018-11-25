#pragma once
#ifndef INTEGER_H_
#define INTEGER_H_


#include <memory>
#include <iostream>

using namespace std;

using std::cout;

class Integer_ {
	int *ptr;
public:
	// Default Constructor
	Integer_() { cout << "Integer_()" << endl; ptr = new int{}; };
	// Parameterized Constructor
	explicit Integer_(int x) { std::cout << "Integer_(int)" << endl; ptr = new int(x); }
	// Copy Constructor
	Integer_(const Integer_ & obj) {
		std::cout << "Integer_(const Integer_ & obj)" << endl;
		ptr = new int(obj.GetValue());	// Copy constructor is less efficient, since here we are allocating new memory and copying from obj.
	}
	// Move Constructor
	Integer_(Integer_ && obj) noexcept
	{
		std::cout << "Integer_(Integer_ && obj)" << endl;
		ptr = obj.ptr;
		obj.ptr = nullptr;	// After stealing obj's resource set its pointer to null so that in destructor the memory is not deleted
							// This is very efficient since the data stays where it is on memory (not copied) and not deleted
	}
	// Copy assignment operator
	Integer_ & operator=(const Integer_ & rhs) {
		std::cout << "operator=(const Integer_ & rhs)" << endl;
		if (this != &rhs) {	// Check it is not self assignment
			delete ptr;
			ptr = new int(*rhs.ptr);
		}

		return *this;
	}

	// Move assignment operator
	Integer_ & operator=(Integer_ && rhs) noexcept
	{
		std::cout << "operator=(Integer_ && rhs)" << endl;
		if (this != &rhs) {
			delete ptr;
			ptr = rhs.ptr;
			rhs.ptr = nullptr;
		}

		return *this;
	}

	// Destructor
	~Integer_() { std::cout << "~Integer_()" << endl; delete ptr; }
	void SetValue(int x) {
		if (ptr) {
			*ptr = x;
		}
		else {
			ptr = new int(x);
		}
	}
	int GetValue() const {
		if (ptr) {
			return *ptr;
		}
		else {
			throw std::exception("[ERROR: Empty resource]");
		}
	}

	Integer_ operator+(const Integer_ & rhs) const
	{
		std::cout << "operator+(const Integer_ &)" << endl;
		Integer_ temp(*this);
		*temp.ptr += *rhs.ptr;
		return temp;
	}

	/*explicit*/ operator int() const
	{
		return *ptr;
	}

	friend Integer_ operator+(int x, const Integer_ & rhs) {
		std::cout << "friend operator+(int, const Integer_ &)" << endl;
		return Integer_(x) + rhs;
	}

	friend std::ostream & operator<<(std::ostream & out, const Integer_ & rhs) {
		out << rhs.GetValue();
		return out;
	}

};


inline void ProcessByValue(std::shared_ptr<Integer_> obj) {
	cout << "In Process(std::shared_ptr<Integer_> obj)" << endl;
	cout << *obj << endl;
	cout << "Use count: " << obj.use_count() << endl;	// Prints 2
}

inline void ProcessByRef(std::shared_ptr<Integer_> & obj) {
	cout << "In Process(std::shared_ptr<Integer_> &obj)" << endl;
	cout << *obj << endl;
}

inline void ProcessByRValueRef(std::shared_ptr<Integer_> && obj) {
	cout << "In Process(std::shared_ptr<Integer_> && obj)" << endl;
	cout << *obj << endl;
}




#endif /* INTEGER_H_ */
