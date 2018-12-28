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
};

template <typename T>
void Util::type_deductor_func(T&& val)
{
	cout << "Inside type_deductor_func before increment val: " << val << endl;
	++val;
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