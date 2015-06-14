template <typename T>
quasi_array<T>::quasi_array(size_t minSize = 1)
{	
	size = startSize;
	cacheBlockSize = blockSize;
	tableSize = 1;
	lookupTable = (T**) malloc(tableSize * sizeof(T*));
}

//deceivingly O(1)
template <typename T>
size_t quasi_array<T>::superindexOf(size_t i, size_t maxBit = sizeof(size_t)*8-1)
{
	size_t iter = maxBit;
	while(iter)
	{
		if(i >> iter) return iter;
	}
	if(iter) return 1;
	return 0;
}

template <typename T>
size_t quasi_array<T>::subindexOf(size_t i, size_t superindex)
{
	return i >> superindex;
}

