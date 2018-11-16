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

};


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