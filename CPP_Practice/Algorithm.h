#pragma once
#include "stdafx.h"
#include <queue>
#include "Derived.h"

/* Algo is a class which has a Q member to read input from
 * Q is a container class for a std::queue of Derived pointers (smart pointers)
 * On Algo.push(D) you call Q.push(D)
 * Q.push(D) calls Q.q_.push(D) here you allocate memory and add the pointer of that
 * memory to queue.
 * On ~Algo() it calls the destructor of shared_ptr object queue_
 * Which calls destructor of std::queue object q_
 * Which calls destructors of all shared_ptr objects inside the queue
 * Which call the destructor of the contained object Derived
*/
class Q
{
	queue<shared_ptr<Derived>> q_{};
public:
	void push(Derived& obj)
	{
		q_.push(make_shared<Derived>(obj));
	}
	void push(Derived&& obj)
	{
		q_.push(make_shared<Derived>(std::forward<Derived>(obj))); // Forward r-valueness, if not forwarded, it will be a named r-value which is an l-value
	}
};
class Alg
{
	// Don't forget to allocate an object for the shared_ptr!
	shared_ptr<Q> queue_ = make_shared<Q>();
public:
	void push(Derived& d)
	{
		queue_->push(d);
	}
	void push(Derived&& d)
	{
		queue_->push(std::forward<Derived>(d)); // Forward r-valueness, if not forwarded, it will be a named r-value which is an l-value
	}
};

/*
 * Same classes above but their PERFECT FORWARDING versions
 */
class Q_prf
{
	std::queue<shared_ptr<Derived>> q_;
public:
	template <typename T>
	void push(T&& obj)
	{
		// Note the make_shared< Derived > not < T >
		q_.push(make_shared<Derived>(std::forward<T>(obj)));
	}
};
class Alg_prf
{
	// Don't forget to allocate an object for the shared_ptr!
	shared_ptr<Q_prf> queue_ = make_shared<Q_prf>();
public:
	template <typename T>
	void push(T&& obj)
	{
		queue_->push(std::forward<T>(obj));
	}
};