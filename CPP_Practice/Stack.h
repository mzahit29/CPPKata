#pragma once
/*
* Stack.h
*
*  Created on: 6 Haz 2018
*      Author: tr1o5152
*/

#ifndef SRC_STACK_H_
#define SRC_STACK_H_


template <typename T, int size>
class Stack {
	T buffer[size];		// If T is user defined type, then size number of objects will be created, so default constructor will run size times
	int top{ -1 };
public:
	Stack() = default;
	Stack(std::initializer_list<T> & list) {
		for (auto x : list) {
			buffer[++top] = x;
		}
	}
	Stack(const Stack & s) {
		top = s.top;
		for (int i = 0; i < top; ++i) {
			buffer[i] = s.buffer[i];
		}
	}

	T & Top() const {
		if (top > -1) {
			return buffer[top];
		}
	}
	//	void Push(const T & obj) {
	//		buffer[++top] = obj;
	//	}
	void Push(T && obj) {
		buffer[++top] = std::forward<T>(obj);
	}
	void Pop();
	bool IsEmpty() {
		return top == -1;
	}

	const T & operator[](int i) const {
		return buffer[i];
	}

	friend std::ostream & operator<<(std::ostream &out, const Stack &st) {
		for (int i = 0; i <= st.top; ++i) {
			out << st[i] << " ";
		}
		return out;
	}

	static Stack Create();
};

// If you implement it later in the file you have to provide all the template parameters (type and nontype).
template <typename T, int size>
void Stack<T, size>::Pop() {
	--top;
}

template <typename T, int size>
Stack<T, size> Stack<T, size>::Create() {
	return Stack<T, size>();
}


#endif /* SRC_STACK_H_ */
