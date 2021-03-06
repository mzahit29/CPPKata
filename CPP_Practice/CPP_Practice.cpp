// CPP_Practice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <queue>
#include "Util.h"
#include <map>
#include "Derived.h"
#include <thread>
#include <mutex>

using namespace std;





void f(const Base& obj)
{
	cout << "f(const Base& obj)" << endl;

	if (const Derived* bp = dynamic_cast<const Derived*>(&obj))
	{
		//Derived new_b(static_cast<const Derived&&>(*bp));
		Derived new_b(std::move(static_cast<const Derived&&>(*bp)));
		//Derived new_b(static_cast<Derived&&>(*bp));
	}

	Derived b1;
	Derived* b1p = &b1;
	Base* a1p = &b1;
	Derived b2{ std::move(b1) };
	Derived b3{ *b1p };
	Derived b4{ std::move(*b1p) };
	Derived b5{ std::move(*a1p) };
	if (Derived* bp = dynamic_cast<Derived*>(a1p))
		Derived b6{std::move(*bp)}; // Triggers move constructor
	if (const Derived* bp = dynamic_cast<const Derived*>(a1p))
		Derived b6{ std::move(*bp) }; // Triggers copy constructor
	if (Derived* const bp = dynamic_cast<Derived*const>(a1p))
		Derived b6{ std::move(*bp) }; // Triggers copy constructor
}

int main()
{
	cout << "main() begin" << endl;

	//// If you have pointer vector you have call delete on each elem
	//cout << "\n\nVector of pointers" << endl;
	//vector<Base*> v;
	//v.push_back(new Derived());

	//for (auto &elm : v)
	//{
	//	delete elm;
	//}

	//// If you have a vector of objects are deleted automatically when function goes out of scope
	//cout << "\n\nVector of objects" << endl;
	//vector<Derived> v_b;
	//v_b.push_back(Derived());

	//// You can not have a vector of references because references are unassignable.


	//queue<int> q;
	//for(auto x : { 1,2,3,4,5,6,7,8,9 })
	//{
	//	q.push(x);
	//}

	//cout << q;




	//// What is the return of pointer assignment
	//int *p;
	//int x{ 77 };
	//cout << "Return value of pointer assignment: " << (p = &x) << endl;
	//cout << "Address in pointer: " << p << endl;



	//vector<int> v{1,2,3,4,5};
	//v.insert(v.begin() + 1, 0);
	//cout << v;



	//map<int, string> m;
	//m[0] = "Superman";
	//m[2] = "Wonder Woman";

	//cout << m;


	//map<int, queue<int>> m2;
	//m2[0].push(2);
	//m2[0].push(311);
	//m2[44].push(69);
	//m2[44].push(21);

	//cout << m2[25];
	//int searc_key{ 25 };
	//if (m2.find(searc_key) != m2.end())
	//{
	//	cout << "Map has data for key " << searc_key << endl;
	//}
	////m2[0] = vector<int>(2);

	//cout << m2;



	//Derived b;
	//Base& a_ref = b;

	//if (typeid(a_ref) == typeid(b)) cout << "a_ref is pointing to derived object" << endl;



	//queue<int> q;
	////q.pop();
	////q.front();



	//map<int, queue<Base*>> m3;
	//m3[0].push(new Base());
	//m3[0].push(new Derived());
	//m3[44].push(new Derived());
	//m3[44].push(new Derived());

	//for (auto & pair : m3)
	//{
	//	queue<Base*> q = pair.second;

	//	while(!q.empty())
	//	{
	//		delete q.front();
	//		q.pop();;
	//	}
	//}


	//map<int, queue<shared_ptr<Base>>> m4;
	//m4[0].push(make_shared<Base>());
	//m4[0].push(make_shared<Derived>());
	//m4[44].push(make_shared<Derived>());
	//m4[44].push(make_shared<Derived>());

	//shared_ptr<Base> ptr(new Derived());
	//shared_ptr<Base> ptr2 = make_shared<Base>();

	//ptr = ptr2;


	//Derived b;
	//f(std::move(b));
	//f(b);

	//queue<shared_ptr<Base>> q;

	//Derived b;
	//q.push(make_shared<Derived>(std::move(b)));
	//q.emplace(make_shared<Derived>(std::move(b)));
	//q.push(make_shared<Derived>(b));

	//int x1 = 10;
	//int x2 = -10;


	//queue<int> q;
	//q.push(4);
	//q.push(12);
	//queue<int> q_copy(q);
	//q.pop();
	//cout << "q contents: " << q << endl;
	//cout << "q_copy contents: " << q_copy << endl;


	//cout << "[BEGIN TEST]: Mutex destruction while mutex is busy_________________" << endl;
	//struct MutexWrapper
	//{
	//	int id_{ 1 };
	//	std::mutex mtx_;
	//	MutexWrapper(int id) : id_(id){}
	//};

	//MutexWrapper* mutex_wrapper_ptr = new MutexWrapper(1);

	//thread t1{ [&mutex_wrapper_ptr] {
	//	cout << "[" << this_thread::get_id() << "]" << " waiting for mutex" << mutex_wrapper_ptr->id_ << endl;
	//	unique_lock<mutex> ul{ mutex_wrapper_ptr->mtx_ };
	//	cout << "[" << this_thread::get_id() << "]"
	//		<< " acquired mtx " << mutex_wrapper_ptr->id_ 
	//		<< " and going to sleep for 3 seconds" << endl;
	//	this_thread::sleep_for(chrono::seconds(3));
	//	cout << "[" << this_thread::get_id() << "]" << "Destroy the mtx_wrapper object while other thread is waiting for that same mutex" << endl;
	//	ul.unlock();
	//	delete mutex_wrapper_ptr;
	//} };
	//this_thread::sleep_for(chrono::microseconds(100));
	//thread t2{[&mutex_wrapper_ptr]{
	//	cout << "[" << this_thread::get_id() << "]" << " waiting for mutex" << mutex_wrapper_ptr->id_ << endl;
	//	lock_guard<mutex> lg{ mutex_wrapper_ptr->mtx_ };
	//	cout << "[" << this_thread::get_id() << "]" << " acquired mtx" << mutex_wrapper_ptr->id_ << endl;
	//} };

	//t1.join();
	//t2.join();
	//cout << "[END TEST]: Mutex destruction while mutex is busy_________________" << endl;


	//cout << "[BEGIN TEST]: Joining an already exited thread_________________" << endl;
	//thread t1{[]{
	//	cout << "Inside t1 thread" << endl;
	//} };

	//this_thread::sleep_for(chrono::seconds(1));

	//t1.join();
	//cout << "[END TEST]: Joining an already exited thread_________________" << endl;


	mutex m;	
	cout << "[BEGIN TEST]: Two threads working one after the other_________________" << endl;
	thread t1{ [&m] {
		const chrono::steady_clock::time_point end_time = chrono::steady_clock::now() + chrono::seconds(30);

		while(chrono::steady_clock::now() < end_time)
		{
			unique_lock<mutex> ul(m);
			cout << "[" << this_thread::get_id() << "] " << "Inside t1 thread" << endl;
			ul.unlock();
			this_thread::sleep_for(chrono::milliseconds(100));
		}
	} };

	thread t2{ [&m] {
		const chrono::steady_clock::time_point end_time = chrono::steady_clock::now() + chrono::seconds(40);

		while (chrono::steady_clock::now() < end_time)
		{
			unique_lock<mutex> ul(m);
			cout << "[" << this_thread::get_id() << "] " << "Inside t2 thread" << endl;
			ul.unlock();
			this_thread::sleep_for(chrono::milliseconds(100));
		}
	} };

	t1.join();
	t2.join();
	cout << "[END TEST]: Joining an already exited thread_________________" << endl;


	cout << "main() end" << endl;
    return 0;
}

