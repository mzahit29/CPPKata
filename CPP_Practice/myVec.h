/*
 * myVec.h
 *
 *  Created on: 24 May 2018
 *      Author: tr1o5152
 */

#ifndef MYVEC_H_
#define MYVEC_H_

template<class T>
class myVec {
private:
	T *data;
	int pos;
	int size;
public:
	class iterator;
	class reverse_iterator;

public:
	myVec() : myVec(512) {
	}
	myVec(int sz) {
		size = sz;
		data = new T[size];
		pos = 0;
	}
	virtual ~myVec() {
		delete[] data;
	}

	void add(T val) {
		if (pos < size) {
			data[pos++] = val;
		}
	}
	iterator begin() {
		return iterator(0, *this);
	}

	iterator end() {
		return iterator(size, *this);
	}

	reverse_iterator r_begin() {
		return reverse_iterator(size - 1, *this);
	}

	reverse_iterator r_end() {
		return reverse_iterator(-1, *this);
	}
};

template<class T>
class myVec<T>::iterator {
private:
	int pos;
	myVec &m;
public:
	iterator(int ps, myVec &mv) : pos(ps), m(mv) {

	}
	T operator*() {
		return m.data[pos];
	}
	void operator++(int) {
		pos++;
	}
	void operator++() {
		pos++;
	}

	bool operator!=(iterator rhs) {
		return pos != rhs.pos;
	}
};

template<class T>
class myVec<T>::reverse_iterator {
private:
	int pos;
	myVec &m;
public:
	reverse_iterator(int ps, myVec &mv) : pos(ps), m(mv) {

	}

	T operator*() {
		return m.data[pos];
	}
	void operator++(int) {
		// Decrement first
		pos--;
	}
	void operator++() {
		pos--;
	}


	bool operator!=(reverse_iterator rhs) {
		return pos != rhs.pos;
	}
};

#endif /* MYVEC_H_ */
