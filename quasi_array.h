/**
 * Quasi arrays are non-contiguous memory storage containers that uses a look-up table that points to built-in arrays of increasing size.
 * Given arrays of size 1, 1, 2, 4,  8, 16 ... 2^(i) the sum is:
 *						1, 2, 4, 8, 16, 32 ... 2^(i+1) which is a trick used to index into a quasi array.
 * important to define are the superindex(i): the position of the most significant (1) bit in index i or -1 if it does not exist, and
 *						   the subindex(i): i & ~superindex
 * Indexing into an array will take on average O(1) time (Worst case is O(log(n)). Auxiliary space requirement is O(n + lg(n)) due to unused array allocation space and pointers respectively.
 * Practically, quasi arrays are intended to mitigate the side effects of reallocating arrays during resize operations, which makes access time more reliable during runtime applications.
 * Accessing all elements with an iterator includes traversing lg(n) sets of data that have a size of n elements. This means that traversal with an iterator is O(n + lg(n)), so O(n).
 * if iterator traversals happen frequently (>= O(n)/lg(n) times) before arrayification or destruction then the benefit of using quasi arrays is strictly due to runtime guarantees.
 * @author Matthew Russell Downey (MattDwny)
 */

template <typename T>
class quasi_array
{
private:
	T** lookupTable; //an array of pointers to contiguous arrays of object T. lookupTable[0][0] will always return the first element. The array sizes will be cacheBlockSize, cacheBlockSize, 2*cacheBlockSize, 4*cacheBlockSize, 8*cacheBlockSize
	T*  nearArray; //stack optimization
	T*  farArray; //

	size_t size;
	size_t capacity;
	size_t chunkSize;
	size_t tableSize;

	size_t maxBit;

	size_t superindexOf(size_t i);
	size_t subindexOf(size_t i);

public:
	/**
	 * constructors
	 */
	quasi_array();
	quasi_array(size_t minSize);

	/**
	 * destructors
	 */
	~quasi_array();

	/**
	 *  element access
	 */
	T at(size_t i);
	T at(size_t superindex, size_t subindex);
	T operator[]();

	/**
	 * iterators
	 */
	iterator begin();
	const_iterator cbegin();

	iterator end();
	const_iterator cend();

	iterator rbegin();
	const_iterator crbegin();

	iterator rend();
	const_iterator crend();

	/**
	 * capacity
	 */
	size_t size();
	bool empty();
	size_t max_size();
	void reserve();
	size_t capacity();
	void shrink_to_fit();
	void arrayify();

	/**
	 * modifiers
	 */
	void clear();
	void push_back(T& obj);
	T pop_back();
	void insert(iterator pos, T& obj);
	void erase(iterator pos);
}