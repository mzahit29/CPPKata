/*
 * IntegerPtr.h
 *
 *  Created on: 30 May 2018
 *      Author: tr1o5152
 */

#ifndef INTEGERPTR_H_
#define INTEGERPTR_H_

using namespace std;

class IntegerPtr {
	Integer *ptr;
public:
	// Default constructor
	IntegerPtr() : ptr(nullptr) {
		cout << "IntegerPtr()" << endl;
	}
	// Copy constructor
	IntegerPtr(IntegerPtr & obj) {
		cout << "IntegerPtr(const IntegerPtr & obj)" << endl;
		ptr = obj.ptr;
		obj.ptr = nullptr;
	}
	// Copy assignment operator
	IntegerPtr & operator=(IntegerPtr & rhs) {
		cout << "operator=(IntegerPtr & rhs)" << endl;
		// Avoid self assignment
		if (this != &rhs)
		{
			ptr = rhs.ptr;
			rhs.ptr = nullptr;
		}

		return *this;
	}
	// Move constructor
	IntegerPtr(IntegerPtr && obj) {
		cout << "IntegerPtr(IntegerPtr && obj)" << endl;
		ptr = obj.ptr;
		obj.ptr = nullptr;
	}
	// Move assignment operator
	IntegerPtr & operator=(IntegerPtr && rhs) {
		cout << "operator=(IntegerPtr & rhs)" << endl;
		// Avoid self assignment
		if (this != &rhs)
		{
			ptr = rhs.ptr;
			rhs.ptr = nullptr;
		}
		return *this;
	}
	~IntegerPtr() {
		cout << "~IntegerPtr()" << endl;
		delete ptr;
	}
	IntegerPtr(Integer *i_ptr) : ptr(i_ptr) {
		cout << "IntegerPtr(Integer *i_ptr)" << endl;
	}

	Integer * operator->() {
		return ptr;
	}

	Integer & operator*() {
		return *ptr;
	}


};



#endif /* INTEGERPTR_H_ */
