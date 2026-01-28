#include "DynamicArray.h"

/// <summary>
/// Initializes the array to a size of 1 with no elements inside.
/// Sets all pointers to the start of the array.
/// </summary>
DynamicArray::DynamicArray()
{
	start_pos = new int[1];
	_size = 1;
	_quantity = 0;
	access_ptr = start_pos;
}

/// <summary>
/// Initializes the array to a user defined size with no elements inside.
/// Sets all pointers to the start of the array.
/// </summary>
/// <param name="size">
/// The size of the array to be created.
/// </param>
DynamicArray::DynamicArray(int size)
{
	start_pos = new int[size];
	_size = size;
	_quantity = 0;
	access_ptr = start_pos;
}

/// <summary>
/// Copy constructor for class
/// </summary>
/// <param name="other">
/// The array you want to copy from for construction
/// </param>
DynamicArray::DynamicArray(const DynamicArray& other)
{
	_size = other._size;
	_quantity = other._quantity;

	start_pos = new int[_size];
	for (int i = 0; i < _quantity; i++) start_pos[i] = other.start_pos[i];

	access_ptr = start_pos;
}

/// <summary>
/// Allows for dynamic arrays to be set equal to each other
/// </summary>
/// <param name="other">
/// The array you are copying from
/// </param>
/// <returns>
/// The copied dynamic array
/// </returns>
DynamicArray& DynamicArray::operator=(const DynamicArray& other)
{
	if (this == &other) return *this;

	delete[] start_pos;
	_size = other._size;
	_quantity = other._quantity;

	start_pos = new int[_size];
	for (int i = 0; i < _quantity; i++) start_pos[i] = other.start_pos[i];

	access_ptr = start_pos;
	return *this;
}

/// <summary>
/// Destructor for the dynamic array.
/// </summary>
DynamicArray::~DynamicArray()
{
	delete[] start_pos;
	start_pos = nullptr;
	access_ptr = nullptr;
	_size = 0;
	_quantity = 0;
}

/// <summary>
/// Increases the size of the array by one.
/// </summary>
void DynamicArray::IncreaseSize()
{
	int* new_array = new int[_size + 1];
	int* new_mov = new_array;
	access_ptr = start_pos;
	int i = 0;

	while (i < _size) {
		*new_mov = *access_ptr;
		new_mov++, access_ptr++, i++;
	}

	delete[] start_pos;
	start_pos = new_array;
	access_ptr = start_pos;

	_size++;
}

/// <summary>
/// Adds the value from the user into the array.
/// Calls upon the increase size function to fix sizing issues (if needed)
/// </summary>
/// <param name="val">
/// The value to be added to the array.
/// </param>
void DynamicArray::PushBack(int val)
{
	if (_quantity >= _size) IncreaseSize();
	*(start_pos + _quantity) = val;
	_quantity++;
}

/// <summary>
/// Removes the last element from the array and decreases the size by 1.
/// </summary>
void DynamicArray::PopBack()
{
	int* new_array = new int[_size - 1];
	int* new_mov = new_array;
	access_ptr = start_pos;
	int i = 0;

	while (i < _size - 1) {
		*new_mov = *access_ptr;
		new_mov++, access_ptr++, i++;
	}

	delete[] start_pos;
	start_pos = new_array;
	access_ptr = start_pos;

	if (_quantity == _size) _quantity--;
	_size--;
}

/// <summary>
/// Allows for the removal of an element at a specific index.
/// </summary>
/// <param name="idx">
/// The index to be removed.
/// </param>
void DynamicArray::Remove(int idx)
{
	int* new_array = new int[_size - 1];
	int* new_mov = new_array;
	access_ptr = start_pos;
	int i = 0;

	while (i < _size) {
		if (i == idx) {
			access_ptr++, i++;
			continue;
		}

		*new_mov = *access_ptr;
		new_mov++, access_ptr++, i++;
	}

	delete[] start_pos;
	start_pos = new_array;
	access_ptr = start_pos;
	_size--, _quantity--;
}

/// <summary>
/// Swaps the values at the two specified indices.
/// </summary>
/// <param name="start_idx">
/// The first element index you want to swap.
/// </param>
/// <param name="end_idx">
/// The second element index you want to swap.
/// </param>
void DynamicArray::SwapIndices(int start_idx, int end_idx)
{
	int* index1 = nullptr;
	int* index2 = nullptr;
	int i = 0;

	access_ptr = start_pos;
	while (true) {
		if (i == start_idx) index1 = access_ptr;
		if (i == end_idx) index2 = access_ptr;

		if (index1 != nullptr && index2 != nullptr) break;
		access_ptr++;
		i++;
	}

	int temp_num = *index1;
	*index1 = *index2;
	*index2 = temp_num;
}

/// <summary>
/// Allows for insertion of a new element at a specific index.
/// </summary>
/// <param name="idx">
/// The index the new element will be in.
/// </param>
/// <param name="val">
/// The value at that new index.
/// </param>
void DynamicArray::Insert(int idx, int val)
{
	int* new_array = new int[_size + 1];
	int* new_mov = new_array;
	access_ptr = start_pos;
	int i = 0;

	while (i < _size) {
		if (i == idx) {
			*new_mov = val;
			new_mov++, i++;
		}
		else {
			*new_mov = *access_ptr;
			new_mov++, access_ptr++, i++;
		}
	}
	*new_mov = *access_ptr;

	delete[] start_pos;
	start_pos = new_array;
	access_ptr = start_pos;
	_size++, _quantity++;
}

/// <summary>
/// Finds and returns the value at the specified index.
/// </summary>
/// <param name="idx">
/// The index to get the value from.
/// </param>
/// <returns>
/// The value at that index.
/// </returns>
int DynamicArray::FindAtIndex(int idx)
{
	return *(start_pos + idx);
}

/// <summary>
/// Replaces the value at a specific index.
/// </summary>
/// <param name="idx">
/// The index to replace.
/// </param>
/// <param name="val">
/// The new value.
/// </param>
void DynamicArray::ReplaceElement(int idx, int val)
{
	*(start_pos + idx) = val;
}

/// <summary>
/// Allows for changing the value at an index using array notation.
/// </summary>
/// <param name="idx">
/// The index of the array to change.
/// </param>
/// <returns>
/// The pointer to the specific element of the array.
/// </returns>
int& DynamicArray::operator[](int idx)
{
	return *(start_pos + idx);
}

/// <summary>
/// Attempts to find the index of a specific value in the array (only first occurence).
/// </summary>
/// <param name="val">
/// The value to be found.
/// </param>
/// <returns>
/// The index of that element in the vector. Returns last index if element not found.
/// </returns>
int DynamicArray::FindElement(int val)
{
	int idx = 0;
	access_ptr = start_pos;

	while (idx < _size) {
		if (*access_ptr == val) break;
		access_ptr++, idx++;
	}

	return idx;
}

/// <summary>
/// Tells user if element is found in array.
/// </summary>
/// <param name="val">
/// Value to find.
/// </param>
/// <returns>
/// True if found, false if not found.
/// </returns>
bool DynamicArray::Contains(int val)
{
	access_ptr = start_pos;
	int i = 0;

	while (i < _size) {
		if (*access_ptr == val) return true;
		access_ptr++, i++;
	}

	return false;
}

/// <summary>
/// Returns the size of the array.
/// </summary>
/// <returns>
/// Size of array.
/// </returns>
int DynamicArray::GetSize()
{
	return _size;
}

/// <summary>
/// Returns the quantity of the array.
/// </summary>
/// <returns>
/// Current quantity of array.
/// </returns>
int DynamicArray::GetQuantity()
{
	return _quantity;
}

/// <summary>
/// Getter method for a specific index pointer
/// </summary>
/// <param name="idx">
/// The index requested
/// </param>
/// <returns>
/// A pointer to an integer
/// </returns>
int* DynamicArray::GetPointer(int idx)
{
	return (start_pos + idx);
}

/// <summary>
/// Determines if the array is empty.
/// </summary>
/// <returns>
/// True if empty, false if not empty.
/// </returns>
bool DynamicArray::IsEmpty()
{
	if (_quantity == 0) return true;
	else return false;
}

/// <summary>
/// Clears the entire array by deleting and reallocating memory.
/// </summary>
void DynamicArray::Clear()
{
	delete[] start_pos;
	start_pos = new int[1], access_ptr = start_pos, _size = 1, _quantity = 0;
}

/// <summary>
/// Prints all the elements in the array.
/// </summary>
void DynamicArray::Print()
{
	for (int i = 0; i < this->GetSize(); i++) printf("Element at Index %d: %d\n", i, this->FindAtIndex(i));
}

/// <summary>
/// Merges the two sides of the array
/// </summary>
/// <param name="left">
/// The lower bound
/// </param>
/// <param name="mid">
/// The middle bound
/// </param>
/// <param name="right">
/// The upper bound
/// </param>
/// <param name="temp">
/// The temp buffer
/// </param>
void DynamicArray::MergeRange(int left, int mid, int right, DynamicArray& temp)
{
	int i = left, j = mid + 1, k = left;

	while (i <= mid && j <= right) {
		if (this->FindAtIndex(i) <= this->FindAtIndex(j)) {
			temp[k] = this->FindAtIndex(i);
			i++;
		}
		else {
			temp[k] = this->FindAtIndex(j);
			j++;
		}
		k++;
	}

	while (i <= mid) {
		temp[k] = this->FindAtIndex(i);
		i++, k++;
	}
	while (j <= right) {
		temp[k] = this->FindAtIndex(j);
		j++, k++;
	}

	for (int l = left; l <= right; l++) {
		this->ReplaceElement(l, temp[l]);
	}
}

/// <summary>
/// Does the merge sort on each side of the array in much quicker time by using a temp buffer
/// </summary>
/// <param name="left">
/// The lower bound of the array
/// </param>
/// <param name="right">
/// The upper bound of the array
/// </param>
/// <param name="temp">
/// The temp buffer
/// </param>
void DynamicArray::MergeSortRange(int left, int right, DynamicArray& temp)
{
	if (left >= right) return;
	int mid = left + (right - left) / 2;

	MergeSortRange(left, mid, temp);
	MergeSortRange(mid + 1, right, temp);
	MergeRange(left, mid, right, temp);
}

/// <summary>
/// Wrapper that the can be called to mergesort an array [time complexity O(n log(n))]
/// </summary>
void DynamicArray::MergeSort()
{
	int n = this->GetQuantity();
	if (n <= 1) return;
	DynamicArray temp(n);
	MergeSortRange(0, n - 1, temp);
}

/// <summary>
/// Sorts the array using an insertion sort [time complexity O(n^2)]
/// </summary>
void DynamicArray::InsertionSort()
{
	if (this->GetQuantity() <= 1) return;
	int i = 1;

	while (i < this->GetQuantity()) {
		for (int x = 1; x <= i; x++) {
			if (this->FindAtIndex(x) < this->FindAtIndex(x - 1)) i = x; break;
		}

		int swap_idx = i;
		while (this->FindAtIndex(swap_idx) < this->FindAtIndex(swap_idx - 1)) {
			this->SwapIndices(swap_idx, swap_idx - 1);
			swap_idx--;
		}
		i++;
	}
}

/// <summary>
/// Sorts through the array, comparing adjacent elements and swapping as necessary [time complexity O(n^2)]
/// </summary>
void DynamicArray::BubbleSort()
{
	if (this->GetQuantity() <= 1) return;
	int swap_count = 0;
	do {
		swap_count = 0;

		for (int i = 1; i < this->GetQuantity(); i++) {
			if (this->FindAtIndex(i) < this->FindAtIndex(i - 1)) {
				this->SwapIndices(i, i - 1);
				swap_count++;
			}
		}
	} while (swap_count >= 1);
}

/// <summary>
/// At each step, finds the smallest remaining unsorted element and puts it into the proper location [time complexity O(n^2)]
/// </summary>
void DynamicArray::SelectionSort()
{
	if (this->GetQuantity() <= 1) return;
	int i = 0;
	while (i < this->GetQuantity()) {
		int smallest_idx = i;
		for (int x = i; x < this->GetQuantity(); x++) {
			if (this->FindAtIndex(x) < this->FindAtIndex(smallest_idx)) smallest_idx = x;
		}

		this->SwapIndices(i, smallest_idx);

		i++, smallest_idx = 0;
	}
}