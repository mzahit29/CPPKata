#pragma once
#include "Base.h"
#include <ostream>

class Derived : public Base
{
	int val_derived_{ 100 };
public:

	Derived() { cout << "Derived()" << endl; };

	explicit Derived(const Base& other)
		: Base(other)
	{
		cout << "explicit Derived(const Base& other) : Base(other)" << endl;
	}

	explicit Derived(Base&& other)
		: Base(std::move(other))
	{
		cout << "explicit Derived(Base&& other) : Base(other)" << endl;
	}

	~Derived() { cout << "~Derived()" << endl; }


	Derived(const Derived& other) : Base(other)
	{
		cout << "Derived(const Derived& other)" << endl;
	}

	Derived(Derived&& other) noexcept : Base(std::move(other))
	{
		cout << "Derived(Derived&& other)" << endl;
	}

	Derived& operator=(const Derived& other)
	{
		cout << "Derived& operator=(const Derived& other)" << endl;
		if (this == &other)
			return *this;
		Base::operator =(other);
		return *this;
	}

	Derived& operator=(Derived&& other) noexcept
	{
		cout << "Derived& operator=(Derived&& other)" << endl;
		if (this == &other)
			return *this;
		Base::operator =(std::move(other));
		return *this;
	}

	int operator++()
	{
		Base::operator++();
		return ++val_derived_;
	}

	friend std::ostream& operator<<(std::ostream& os, const Derived& obj)
	{
		os << static_cast<const Base&>(obj);
		os << "Printing Derived - val_derived_: " << obj.val_derived_ << endl;
		return os;
	}

	void g() {}
};
