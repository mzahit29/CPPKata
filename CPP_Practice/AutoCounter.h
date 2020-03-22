#pragma once
#include <set>
#include <iostream>

/*
 * A user type which is used to check that all objects
 * of this type are properly (and only once) deleted
 * This is implemented using a static object of CleanupCheck
 * class. It checks multiple removes, and also checks objects
 * that were not removed. Used with PStash class it is seen
 * that PStash is correctly assuming ownership and deleting the objects
 * as promised.
 */
class AutoCounter
{
	static int count;
	int id;

	class CleanupCheck
	{
		std::set<AutoCounter *>	 trace;

	public:
		void add(AutoCounter *ap)
		{
			trace.insert(ap);
		}
		void remove(AutoCounter *ap)
		{
			std::cout << "Removing AutoCounter: " << ap << std::endl;
			if (trace.erase(ap) != 1)
				std::cerr << "[ERROR:] Autocounter ap "<< ap <<" is already removed!" << std::endl;
		}
		~CleanupCheck()
		{
			std::cout << "~CleanupCheck() => ";
			if (trace.size() != 0)
			{
				std::cerr << "[ERROR:] CleanupCheck trace was not empty. Not all AutoCounter objects were deleted!" 
					<< std::endl;
			}
			else
			{
				std::cout << "[OK]" << std::endl;
			}
		}
	};
	static CleanupCheck verifier;

	AutoCounter() : id(count++)
	{
		verifier.add(this);
		std::cout << "created[" << id << "]" << std::endl;
	}
public:
	// prevent copy construct and assignment
	AutoCounter(const AutoCounter&) = delete;
	void operator=(const AutoCounter&) = delete;

	static AutoCounter* create()
	{
		return new AutoCounter();
	}

	~AutoCounter()
	{
		std::cout << "destroying[" << id << "]" << std::endl;
		verifier.remove(this);
	}
};

