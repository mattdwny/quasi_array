#include "quasi_array.h"



template <typename T>
quasi_array<T>::quasi_array(size_t minSize = 1)
{	
	lookupTable = (T**) malloc(sizeof(T*));
	nearArray = farArray = lookupTable[0];
	
	size = 0;
	tableSize = 1;
	capacity = chunkSize = minSize;

	maxBit = -1;
}

template <typename T>
quasi_array<T>::~quasi_array()
{	
	for(size_t i = 0; i < tableSize; ++i)
		free lookupTable[i];
	
	free lookupTable;
}

template <typename T>
quasi_array<T>::push_back(size_t minSize = 1)
{	
	if(size == capcity)
	{

	}
	size_t
	farArray[]
	++size;
}

template <typename T>
quasi_array<T>::pop_back(size_t minSize = 1)
{	
	--size;

}

/**
 * deceivingly O(1): probability of finding an element is at best sum ( 1*(1/2) + 2*(1/4) + 3*(1/8) + ... + i*(2^-i) )/n, so 2
 */
template <typename T>
size_t quasi_array<T>::superindexOf(size_t i)
{
	size_t real_i = i/chunkSize;
	size_t iter = maxBit;
	while(iter > 0)
	{
		if(real_i >> iter) return iter;
	}
	if(real_i) return 1;
	return 0;
}

template <typename T>
size_t quasi_array<T>::subindexOf(size_t i)
{
	return subindexOf(i, superindexOf(i));
}

template <typename T>
size_t quasi_array<T>::subindexOf(size_t i, size_t superindex)
{
	return (i/chunkSize) & ~superindex;
}

