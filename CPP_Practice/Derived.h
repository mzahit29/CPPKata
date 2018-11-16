#pragma once
#include "Base.h"

class Derived : public Base
{
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

	void g() {}
};
