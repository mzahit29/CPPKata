#pragma once
#include <iostream>

using namespace std;

class Base
{
public:
	Base() { std::cout << "Base()" << endl; }
	virtual ~Base() { cout << "~Base()" << endl; }

	Base(const Base& other)
	{
		cout << "Base(const A& other)" << endl;
	}
	Base(Base&& other) noexcept
	{
		cout << "Base(A&& other)" << endl;
	}
	Base& operator=(const Base& other)
	{
		cout << "Base& operator=(const A& other)" << endl;
		if (this == &other)
			return *this;
		return *this;
	}
	Base& operator=(Base&& other) noexcept
	{
		cout << "Base& operator=(A&& other)" << endl;
		if (this == &other)
			return *this;
		return *this;
	}
	void f() {}
	virtual void x() {}
};


