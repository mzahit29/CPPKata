#pragma once
#include <iostream>
#include <ostream>

using namespace std;

class Base
{
	int val_base_{};
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

	int operator++()
	{
		return ++val_base_;
	}

	friend std::ostream& operator<<(std::ostream& os, const Base& obj)
	{
		os << "Printing Base part - val_base_: " << obj.val_base_;
		return os;
	}

	void f() {}
	virtual void x() {}
};


