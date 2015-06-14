#include "quasi_array.h"

template <typename T>
quasi_array<T>::quasi_array(size_t minSize = 1)
{	
	lookupTable = (T**) malloc(sizeof(T*));
	nearArray = farArray = lookupTable[0];
	
	size = 0;
	tableSize = 1;
	chunkSize = minSize;
	capacity = minSize;

	maxBit = 0;

	quickIndex = 0;
	endIndex = minSize;
}

template <typename T>
quasi_array<T>::~quasi_array()
{	
	for(size_t i = 0; i < tableSize; ++i)
		free lookupTable[i];
	
	free lookupTable;
}

template <typename T>
T quasi_array<T>::at(size_t i)
{
	size_t superindex = superindex(i);
	return lookupTable[superindex][subindex(i,superindex)];
}

template <typename T>
T* quasi_array<T>::at(size_t i)
{	
	size_t superindex = superindex(i);
	return &lookupTable[superindex][subindex(i,superindex)];
}

template <typename T>
T quasi_array<T>::at(size_t superindex, size_t subindex)
{	
	return lookupTable[superindex][subindex];
}

template <typename T>
T* quasi_array<T>::at(size_t superindex, size_t subindex)
{	
	return &lookupTable[superindex][subindex];
}

template <typename T>
void quasi_array<T>::push_back(size_t minSize = 1)
{	
	if(size == capacity)
	{
		lookupTable = (T**) realloc(lookupTable, tableSize*sizeof(T*));
		lookupTable[tableSize] = farArray = (T*) malloc(capacity*sizeof(T));
		
		++tableSize;
		capacity *= 2;
		quickIndex = 0;
	}
	farArray[quickIndex];
	++quickIndex;
	++size;
}

template <typename T>
T quasi_array<T>::pop_back(size_t minSize = 1)
{	
	if(!empty())
	{
		if(quickIndex > 0)
		{
			lookupTable = (T**) realloc(lookupTable, tableSize*sizeof(T*));
			lookupTable[tableSize] = farArray = (T*) malloc(capacity*sizeof(T));
		
			++tableSize;
			capacity *= 2;
			quickIndex = 0;
		}
		farArray[quickIndex];
		++quickIndex;

		return data;
	}
	return null;
}

template <typename T>
size_t quasi_array<T>::size()
{
	return size;
}

/**
 * deceivingly O(1): iterating until finding an element is (in the best case): sum ( 1*(n/2) + 2*(n/4) + 3*(n/8) + ... + i*(n*2^-i) )/n, so 2
 */
template <typename T>
size_t quasi_array<T>::superindexOf(size_t i)
{
	size_t real_i = i/chunkSize;
	ssize_t iter = maxBit;
	while(iter > 0)
	{
		if(real_i >> iter) return iter;
	}
	return real_i;
}

template <typename T>
size_t quasi_array<T>::subindexOf(size_t i)
{
	return subindexOf(i, superindexOf(i));
}

template <typename T>
size_t quasi_array<T>::subindexOf(size_t i, size_t superindex)
{
	return i & ~superindex;
}