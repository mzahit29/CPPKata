#pragma once
/*
* StackV2.h
*
*  Created on: 6 Haz 2018
*      Author: tr1o5152
*/

#ifndef SRC_STACKV2_H_
#define SRC_STACKV2_H_

#include <iostream>
#include <vector>

using namespace std;

template <typename T, int size = 8>
class StackV2 {
	std::vector<T> data;
public:
	// Default Constructor
	StackV2() {
		cout << "StackV2()" << endl;
		data.reserve(size);
		cout << "Vector initial capacity: " << data.capacity() << endl;
	}
	// Copy Constructor
	StackV2(const StackV2 & obj) {
		cout << "StackV2(const StackV2 & obj)" << endl;
		data.reserve(obj.data.size());
		for (auto &x : obj.data) {
			this->data.push_back(x);
		}
	}
	// Move Constructor
	StackV2(StackV2 && obj) {
		cout << "StackV2(StackV2 && obj)" << endl;
		//		data = obj.data;  // WRONG: This will trigger copy constructor for all elements of the vector.
		//		std::swap(data, obj.data);  // OK: EITHER use C++03 method which std::swap
		data = std::move(obj.data); // OK: C++11 method, converts obj.data to r-value reference which triggers the move assignment operator for vector<T>
	}
	// Copy Assignment Operator
	StackV2 & operator=(const StackV2 & obj) {
		cout << "operator=(const StackV2 & obj)" << endl;
		data.reserve(obj.data.size());
		// METHOD 1:
		//		for (int i = 0; i < obj.data.size(); ++i) {
		//			data.push_back(obj.data[i]);
		//		}
		// METHOD 2:
		//		for (auto &x: obj.data) {
		//			data.pushback(x);
		//		}
		// METHOD 3:
		typename std::vector<T>::const_iterator itSource = obj.data.cbegin();
		while (itSource != obj.data.cend()) {
			data.push_back(*itSource);

			++itSource;
		}

		return *this;
	}
	// Move Assignment Operator
	StackV2 & operator=(StackV2 && obj) {
		cout << "operator=(StackV2 && obj)" << endl;
		//		data = obj.data;		// WRONG: Triggers copy constructor because obj is a named r-value
		//		std::swap(data, obj.data);	// OK: EITHER use C++03 method which std::swap
		data = std::move(obj.data);  // OK: C++11 method

		return *this;
	}
	// BONUS: Initializer list constructor
	StackV2(const std::initializer_list<T> & list) {
		for (auto x : list) {
			data.push_back(x);
		}
	}
	~StackV2() {
		cout << "~StackV2()" << endl;
	}

	//  This is not required: member template covers it
	//	void Push(const T & obj) {
	//		cout << "Push(const T & obj)" << endl;
	//		data.push_back(obj);
	//	}

	// This member template covers both r-value and l-value references with the (T1 && obj) parameter, no need for void Push(const T & obj)
	template <typename T1>
	StackV2 && Push(T1 && obj) && {
		cout << "Push(" << typeid(obj).name() << " obj) &&" << endl;
		data.push_back(std::forward<T1>(obj));

		return std::move(*this);
	}
	template <typename T1>
	StackV2 & Push(T1 && obj) & {
		cout << "Push(" << typeid(obj).name() << " obj) &" << endl;
		data.push_back(std::forward<T1>(obj));

		return *this;
	}

	T & Top() {
		return *(data.end() - 1);
	}

	T Pop();

	friend std::ostream & operator<<(std::ostream &out, const StackV2 & obj) {
		out << "Stack Size: " << obj.data.size() << endl;
		out << "Stack Capacity: " << obj.data.capacity() << endl;
		out << "Stack Elements: ";
		for (auto &x : obj.data) {
			out << x << " ";
		}
		out << endl;

		return out;
	}

	static StackV2 Create();

};

template <typename T, int size = 8>
T StackV2<T, size>::Pop() {
	T obj = std::move(*(data.end() - 1));
	data.erase(data.end() - 1);
	return obj;
}

template <typename T, int size = 8>
StackV2<T, size> StackV2<T, size>::Create() {
	return StackV2<T, size>();
}

#endif /* SRC_STACKV2_H_ */