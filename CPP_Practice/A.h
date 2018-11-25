#pragma once
#include <iostream>

using namespace std;

class A {
public:
	~A() {
		cout << "~A()" << endl;
	}

	void f(int &&) & {
		cout << "f(int &&) &" << endl;
	}
	void f(int &&) && {
		cout << "f(int &&) &&" << endl;
	}


	A && g() && {
		cout << "g() && " << endl;
		return std::move(*this);	// this becomes l-value inside the function (discard qualifiers), therefore to pass it as r-value we need to use std::move
	}
	A & g() & {
		cout << "g() & " << endl;
		return *this;
	}

	template <typename T1>
	A & h(T1 && obj) & {
		cout << "h(" << typeid(obj).name() << ") &" << endl;
		return *this;
	}

	template <typename T1>
	A && h(T1 && obj) && {
		cout << "h(" << typeid(obj).name() << ") &&" << endl;
		return std::move(*this);
	}

};