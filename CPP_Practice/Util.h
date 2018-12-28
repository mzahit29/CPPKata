#pragma once
#include <ostream>
#include <queue>
#include <map>
#include <string>

using namespace std;

class Util
{
public:
	Util() = default;
	~Util() = default;

	// When it appears in a type - deducing context, T&& acquires a special meaning.
	// When func is instantiated, T depends on whether the argument passed to func 
	// is an lvalue or an rvalue. If it's an lvalue of type U, T is deduced to U&. 
	// If it's an rvalue, T is deduced to U
	template<typename T>
	static void type_deductor_func(T&& val); // T&& val is NOT! an r-value reference.

	template<typename T>
	static bool is_l_value(T&)
	{
		cout << "\tL-value g(T&) called, therefore parameter must be l-value" << endl;
		return true;
	}

	template<typename T>
	static bool is_l_value(T&&)
	{
		cout << "\tR-value g(T&&) called, therefore parameter must be r-value" << endl;
		return false;
	}
};

/*
 * This function is a wrapper that forwards the val perfectly (not losing r-value or l-valueness of parameter)
 * to the wrapped function which is is_l_value in this case
 */
template <typename T>
void Util::type_deductor_func(T&& val)
{
	cout << "Inside type_deductor_func before increment val: " << val << endl;
	++val;
	// This WON'T WORK!
	//g(val); // This will only trigger g(T&) because val is an l-value and inside g() T is deduced to T& 
	//		// so g(T&&) becomes g(T& &&) which is g(T&) according to reference collapsing rule
	//		// Therefore always g(T&) will be triggered.
	
	// This WILL WORK
	if (is_l_value(std::forward<T>(val)))  // Forwarding the r-value or l-value ness of val to g.
	{
		cout << "\tParameter val is an l-value" << endl;
	}
	else
	{
		cout << "\tParameter val is an r-value" << endl;
	}

	cout << "Inside type_deductor_func after increment val: " << val << endl;
}


template <typename T>
std::ostream& operator<<(std::ostream& out, std::queue<T> obj)
{
	while (!obj.empty())
	{
		out << obj.front() << " ";
		obj.pop();
	}

	return out << endl;
}


template <typename T>
std::ostream& operator<<(std::ostream& out, std::vector<T> obj)
{
	for (const auto & x : obj)
	{
		out << x << " ";
	}

	return out << endl;
}


template <typename K, typename T>
std::ostream& operator<<(std::ostream& out, std::map<K, T> obj)
{
	for (const auto & x : obj)
	{
		out << x.second << " ";
	}

	return out << endl;
}