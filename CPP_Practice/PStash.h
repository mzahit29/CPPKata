#pragma once

/*
 * A templated stash for keeping the pointers of any type
 * It takes the ownership of object's that are added,
 * meaning deletes them when this stash is destroyed
 */
template <typename T, int incr = 10>
class PStash
{
	int quantity;
	int next;
	T** storage;
	void inflate(int increase = incr);
public:
	PStash() : quantity(0), next(0), storage(0) {}
	~PStash();

	int add(T* element);
	T* operator[](int index) const; // Fetch
	T* remove(int index);
	int count() const { return next; }
};

template <typename T, int incr>
int PStash<T, incr>::add(T* element)
{
	if (next >= quantity)
		inflate(incr);

	storage[next++] = element;
	return next - 1;
}

template <typename T, int incr>
void PStash<T, incr>::inflate(int increase)
{
	const int psz = sizeof(T*);

	T** st = new T*[quantity + increase];
	memset(st, 0, (quantity + increase) * psz);
	memcpy(st, storage, quantity * psz);
	quantity += increase;
	delete[] storage;
	storage = st;
}

template <typename T, int incr>
PStash<T, incr>::~PStash()
{
	for (int i = 0; i < next; ++i)
	{
		delete storage[i];
		storage[i] = 0;
	}

	delete[] storage;
}

template <typename T, int incr>
T* PStash<T, incr>::operator[](int index) const
{
	if (index >= next) return 0;

	return storage[index];
}

template <typename T, int incr>
T* PStash<T, incr>::remove(int index)
{
	if (index >= next) return 0;

	T* v = operator[](index);

	if (v) storage[index] = 0;

	return v;
}
