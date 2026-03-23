#pragma once
#include <iostream>
#include <random>
#include "LinkedList.h"
using namespace std;

template <typename T>
class DynamicArray
{
private:
	T* start_pos;		// always points to the first index of memory
	int _size;			// the current max size of the array
	int _quantity;		// the number of elements in the current array
	T* access_ptr;		// used to obtain the value at specific indicies

// Internal Functions
	/// <summary>
	/// Merges the two sides of the array
	/// </summary>
	/// <param name="left">The lower bound</param>
	/// <param name="mid">The middle bound</param>
	/// <param name="right">The upper bound</param>
	/// <param name="temp">The temp buffer</param>
	void MergeRange(int left, int mid, int right, DynamicArray<T>& temp) {
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
	/// <param name="left">The lower bound of the array</param>
	/// <param name="right">The upper bound of the array</param>
	/// <param name="temp">The temp buffer</param>
	void MergeSortRange(int left, int right, DynamicArray& temp) {
		if (left >= right) return;
		int mid = left + (right - left) / 2;

		MergeSortRange(left, mid, temp);
		MergeSortRange(mid + 1, right, temp);
		MergeRange(left, mid, right, temp);
	}

	/// <summary>
	/// Does the quick sort on the array, partitioning using the temp array for faster recusion
	/// </summary>
	/// <param name="left">The lower bound of the array</param>
	/// <param name="right">The upper bound of the array</param>
	/// <param name="temp">The temp buffer</param>
	void QuickSortRange(int left, int right, DynamicArray& temp) {
		if (left >= right) return;

		int idx = rand() % (right - left + 1) + left;

		// Indexing and sorting for temp
		int writeL = left, writeR = right, pivot_val = this->FindAtIndex(idx), pivot_count = 0, pivot_idx;
		for (int i = left; i <= right; i++) {
			if (this->FindAtIndex(i) == pivot_val) { pivot_count++; }
		}

		for (int i = left; i <= right; i++) {
			if (i == idx) { continue; }	// skip selected index

			if (this->FindAtIndex(i) < pivot_val) { temp[writeL++] = this->FindAtIndex(i); }
			else if (this->FindAtIndex(i) > pivot_val) { temp[writeR--] = this->FindAtIndex(i); }
		}
		pivot_idx = writeL;
		for (int i = 0; i < pivot_count; i++) { temp[i + pivot_idx] = pivot_val; }

		for (int i = left; i <= right; i++) { this->ReplaceElement(i, temp[i]); }

		QuickSortRange(left, pivot_idx - 1, temp);
		QuickSortRange(pivot_idx + pivot_count, right, temp);
	}

	/// <summary>
	/// Does the sort-and-count on the array in quicker time using temp array
	/// </summary>
	/// <param name="left">The lower bound</param>
	/// <param name="right">The upper bound</param>
	/// <param name="temp">The temp buffer</param>
	/// <returns>A count of inversions</returns>
	int SortAndCountRange(int left, int right, DynamicArray& temp) {
		if (left >= right) { return 0; }
		
		int inversion_a = 0, inversion_b = 0, inversion_m = 0;
		int mid = left + (right - left) / 2;
		inversion_a += SortAndCountRange(left, mid, temp);
		inversion_b += SortAndCountRange(mid + 1, right, temp);
		inversion_m += MergeAndCountRange(left, mid, right, temp);

		return inversion_a + inversion_b + inversion_m;
	}

	/// <summary>
	/// Does the merge-and-count on the array in quicker time using temp array
	/// </summary>
	/// <param name="left">The lower bound</param>
	/// <param name="mid">The middle bound</param>
	/// <param name="right">The upper bound</param>
	/// <param name="temp">The temp buffer</param>
	/// <returns>A count of inversions</returns>
	int MergeAndCountRange(int left, int mid, int right, DynamicArray& temp) {
		int i = left, j = mid + 1, k = left, inversion_count = 0;

		while (i <= mid && j <= right) {
			if (this->FindAtIndex(i) <= this->FindAtIndex(j)) {
				temp[k] = this->FindAtIndex(i);
				i++;
			}
			else {
				temp[k] = this->FindAtIndex(j);
				j++;
				inversion_count += mid - i + 1;
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

		return inversion_count;
	}

	/// <summary>
	/// Does the sort-and-count on the array in quicker time using temp array
	/// </summary>
	/// <param name="left">The lower bound</param>
	/// <param name="right">The upper bound</param>
	/// <param name="temp">The temp buffer</param>
	/// <returns>A count of weighted inversions</returns>
	long long SortAndCountWeightedRange(int left, int right, DynamicArray& temp) {
		if (left >= right) { return 0; }

		long long inversion_a = 0, inversion_b = 0, inversion_m = 0;
		int mid = left + (right - left) / 2;
		inversion_a += SortAndCountWeightedRange(left, mid, temp);
		inversion_b += SortAndCountWeightedRange(mid + 1, right, temp);
		inversion_m += MergeAndCountWeightedRange(left, mid, right, temp);

		return inversion_a + inversion_b + inversion_m;
	}

	/// <summary>
	/// Does the merge-and-count on the array in quicker time using temp array
	/// </summary>
	/// <param name="left">The lower bound</param>
	/// <param name="mid">The middle bound</param>
	/// <param name="right">The upper bound</param>
	/// <param name="temp">The temp buffer</param>
	/// <returns>A count of weighted inversions</returns>
	long long MergeAndCountWeightedRange(int left, int mid, int right, DynamicArray& temp) {
		int i = left, j = mid + 1, k = left;
		long long weighted_inversions = 0;

		long long sumLeft = GetSumOfRange(i, mid);

		while (i <= mid && j <= right) {
			if (this->FindAtIndex(i) <= this->FindAtIndex(j)) {	// if this[i] is smaller than this[j]
				temp[k] = this->FindAtIndex(i);
				sumLeft -= this->FindAtIndex(i);
				i++;
			}
			else {	// this[i] is bigger
				temp[k] = this->FindAtIndex(j);

				T rightVal = this->FindAtIndex(j);
				int count = mid - i + 1;
				weighted_inversions += (long long)count * rightVal + sumLeft;

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

		return weighted_inversions;
	}

	/// <summary>
	/// WIP
	/// Does a quicksort on one side recursively to determine the median value in quicker time with temp buffer
	/// </summary>
	/// <param name="left">The lower bound</param>
	/// <param name="right">The upper bound</param>
	/// <param name="k">The median index</param>
	/// <param name="temp">A temp buffer</param>
	/// <returns>The median value of type T</returns>
	T SelectRandRange(int left, int right, int k, DynamicArray& temp) {
		if (left >= right) return 0;

		int idx = rand() % (right - left + 1) + left;

		int writeL = left, writeR = right, pivot_val = this->FindAtIndex(idx), pivot_count = 0, pivot_idx;
		for (int i = left; i <= right; i++) {
			if (this->FindAtIndex(i) == pivot_val) { pivot_count++; }
		}

		for (int i = left; i <= right; i++) {
			if (i == idx) { continue; }	// skip selected index

			if (this->FindAtIndex(i) < pivot_val) { temp[writeL++] = this->FindAtIndex(i); }
			else if (this->FindAtIndex(i) > pivot_val) { temp[writeR--] = this->FindAtIndex(i); }
		}
		pivot_idx = writeL;
		for (int i = 0; i < pivot_count; i++) { temp[i + pivot_idx] = pivot_val; }

		for (int i = left; i <= right; i++) { this->ReplaceElement(i, temp[i]); }

		if (k < pivot_idx - 1 - left) { return SelectRandRange(left, pivot_idx - 1, k, temp); }
		if (k >= pivot_idx - 1 - left && k < ((pivot_idx - left) + pivot_count)) { return pivot_val; }
		else { return SelectRandRange(pivot_idx + pivot_count, right, k, temp); }
	}

	/// <summary>
	/// Does the sorting and selects the k-th smallest element in the array
	/// </summary>
	/// <param name="left">The lower bound</param>
	/// <param name="right">The upper bound</param>
	/// <param name="k">The rank inside [left..right]</param>
	/// <returns>The median value</returns>
	T SelectRange(int left, int right, int k) {
		int len = right - left + 1;
		if (len <= 5) {
			this->InsertionSortRange(left, right);
			return this->FindAtIndex(left + k);
		}

		int numGroups = ceil(len / 5.0);
		DynamicArray<T> medians(numGroups);

		for (int i = 0; i < numGroups; i++) {
			int g = left + 5 * i;	// start idx
			int ge = min(g + 4, right);	// end idx
			InsertionSortRange(g, ge);

			int mid = g + (ge - g) / 2;
			medians.PushBack(this->FindAtIndex(mid));
		}

		int mCount = medians.GetQuantity();
		T pivot = medians.SelectRange(0, mCount - 1, (mCount - 1) / 2);

		int lt = left, i = left, gt = right;
		while (i <= gt) {
			if (this->FindAtIndex(i) < pivot) {
				this->SwapIndices(i, lt);
				i++, lt++;
			}
			else if (this->FindAtIndex(i) > pivot) {
				this->SwapIndices(i, gt);
				gt--;
			}
			else if (this->FindAtIndex(i) == pivot) { i++; }
		}

		int Lsize = lt - left;
		int Esize = gt - lt + 1;

		if (k < Lsize) { return SelectRange(left, lt - 1, k); }
		else if (k < Lsize + Esize) { return pivot; }
		else {
			int new_k = k - (Lsize + Esize);
			return SelectRange(gt + 1, right, new_k);
		}
	}

	/// <summary>
	/// Sorts the subarray using an insertion sort (why range is used)
	/// [time complexity O(n^2)]
	/// </summary>
	void InsertionSortRange(int left, int right) {
		if (this->GetQuantity() <= 1) return;
		if (left < 0 || right >= _quantity || left >= right) return;
		int i = left + 1;

		while (i <= right) {
			int j = i;
			while (j > left && this->FindAtIndex(j) < this->FindAtIndex(j - 1)) {
				this->SwapIndices(j, j - 1);
				j--;
			}
			i++;
		}
	}

public:
// Basic Class Overhead
	/// <summary>
	/// Initializes the array to a size of 1 with no elements inside.
	/// Sets all pointers to the start of the array.
	/// </summary>
	DynamicArray() {
		start_pos = new T[1], _size = 1, _quantity = 0, access_ptr = start_pos;
	}
	
	/// <summary>
	/// Initializes the array to a user defined size with no elements inside.
	/// Sets all pointers to the start of the array.
	/// </summary>
	/// <param name="size">The size of the array to be created</param>
	DynamicArray(int size) {
		start_pos = new T[size], _size = size, _quantity = 0, access_ptr = start_pos;
	}
	
	/// <summary>
	/// Copy constructor for class
	/// </summary>
	/// <param name="other">The array you want to copy from for construction</param>
	DynamicArray(const DynamicArray<T>& other) {
		_size = other._size;
		_quantity = other._quantity;

		start_pos = new T[_size];
		for (int i = 0; i < _quantity; i++) start_pos[i] = other.start_pos[i];

		access_ptr = start_pos;
	}
	
	/// <summary>
	/// Allows for dynamic arrays to be set equal to each other
	/// </summary>
	/// <param name="other">The array you are copying from</param>
	/// <returns>
	/// The copied dynamic array
	/// </returns>
	DynamicArray& operator=(const DynamicArray<T>& other) {
		if (this == &other) return *this;

		delete[] start_pos;
		_size = other._size;
		_quantity = other._quantity;

		start_pos = new T[_size];
		for (int i = 0; i < _quantity; i++) start_pos[i] = other.start_pos[i];

		access_ptr = start_pos;
		return *this;
	}
	
	/// <summary>
	/// Destructor for the dynamic array.
	/// </summary>
	~DynamicArray() {
		delete[] start_pos;
		start_pos = nullptr;
		access_ptr = nullptr;
		_size = 0;
		_quantity = 0;
	}

// Size Manipulation, Insertion, Removals
	/// <summary>
	/// Increases the size of the array by one.
	/// </summary>
	void IncreaseSize() {
		T* new_array = new T[_size + 1];
		T* new_mov = new_array;
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
	/// Allows for a completely new size to be declared for the array.
	/// Note: Currently does not save elements already in the array, so only use this on an empty array.
	/// </summary>
	/// <param name="size">The new size of the array</param>
	void SetSize(int size) {
		T* new_array = new T[size];
		delete[] start_pos;
		_size = size, start_pos = new_array, access_ptr = start_pos;
	}
	
	/// <summary>
	/// Adds the value from the user into the array.
	/// Calls upon the increase size function to fix sizing issues (if needed)
	/// </summary>
	/// <param name="val">The value to be added to the array</param>
	void PushBack(const T& val) {
		if (_quantity >= _size) IncreaseSize();
		*(start_pos + _quantity) = val;
		_quantity++;
	}
	
	/// <summary>
	/// Removes the last element from the array and decreases the size by 1.
	/// </summary>
	void PopBack() {
		if (this->GetQuantity() == 0) return;
		_quantity--;
		T* new_array = new T[_quantity];
		T* new_mov = new_array;
		access_ptr = start_pos;
		int i = 0;

		while (i < _quantity) {
			*new_mov = *access_ptr;
			new_mov++, access_ptr++, i++;
		}

		delete[] start_pos;
		start_pos = new_array;
		access_ptr = start_pos;

		_size = _quantity;
	}
	
	/// <summary>
	/// Allows for the removal of an element at a specific index.
	/// </summary>
	/// <param name="idx">The index to be removed</param>
	void Remove(int idx) {
		if (this->GetQuantity() == 0 || idx < 0 || idx >= _quantity) return;
		T* new_array = new T[_quantity - 1];
		T* new_mov = new_array;
		access_ptr = start_pos;
		int i = 0;

		while (i < _quantity) {
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
	/// <param name="start_idx">The first element index you want to swap</param>
	/// <param name="end_idx">The second element index you want to swap</param>
	void SwapIndices(int start_idx, int end_idx) {
		if ((start_idx < 0 || start_idx >= this->GetQuantity()) || (end_idx < 0 || end_idx >= this->GetQuantity())) return;
		T* index1 = start_pos + start_idx;
		T* index2 = start_pos + end_idx;

		T temp_num = *index1;
		*index1 = *index2;
		*index2 = temp_num;
	}
	
	/// <summary>
	/// Allows for insertion of a new element at a specific index.
	/// </summary>
	/// <param name="idx">The index the new element will be in</param>
	/// <param name="val">The value at that new index</param>
	void Insert(int idx, const T& val) {
		if (idx < 0 || idx > _quantity) return;

		T* new_array = new T[_quantity + 1];
		T* new_mov = new_array;
		access_ptr = start_pos;
		int i = 0;

		while (i <= idx - 1) {
			*new_mov = *access_ptr;
			access_ptr++, new_mov++, i++;
		}
		*new_mov = val;
		i++, new_mov++;
		while (access_ptr != (start_pos + _quantity)) {
			*new_mov = *access_ptr;
			access_ptr++, new_mov++, i++;
		}

		delete[] start_pos;
		start_pos = new_array;
		access_ptr = start_pos;
		_quantity++;
		_size = _quantity;
	}

// Element Access Operations
	/// <summary>
	/// Finds and returns the value at the specified index.
	/// </summary>
	/// <param name="idx">The index to get the value from</param>
	/// <returns>
	/// The value at that index.
	/// </returns>
	T& FindAtIndex(int idx) {
		return *(start_pos + idx);
	}
	
	/// <summary>
	/// Replaces the value at a specific index.
	/// </summary>
	/// <param name="idx">The index to replace</param>
	/// <param name="val">The new value</param>
	void ReplaceElement(int idx, const T& val) {
		*(start_pos + idx) = val;
	}
	
	/// <summary>
	/// Allows for changing the value at an index using array notation.
	/// </summary>
	/// <param name="idx">The index of the array to change</param>
	/// <returns>
	/// The pointer to the specific element of the array.
	/// </returns>
	T& operator[](int idx) {
		return *(start_pos + idx);
	}

	/// <summary>
	/// Accessor for a constant pointer
	/// </summary>
	/// <param name="idx">The index of the array</param>
	/// <returns>
	/// A constant pointer
	/// </returns>
	const T& operator[](int idx) const {
		return *(start_pos + idx);
	}
	
	/// <summary>
	/// Attempts to find the index of a specific value in the array (only first occurence).
	/// </summary>
	/// <param name="val">The value to be found</param>
	/// <returns>
	/// The index of that element in the vector. Returns last index if element not found.
	/// </returns>
	int FindElement(const T& val) {
		int idx = 0;

		while (idx < _quantity) {
			if (*(start_pos + idx) == val) break;
			idx++;
		}

		return idx;
	}
	
	/// <summary>
	/// Tells user if element is found in array.
	/// </summary>
	/// <param name="val">Value to find</param>
	/// <returns>
	/// True if found, false if not found.
	/// </returns>
	bool Contains(const T& val) {
		int i = 0;

		while (i < _quantity) {
			if (*(start_pos + i) == val) return true;
			i++;
		}

		return false;
	}

	void ReduceQuantity() { _quantity -= 1; }

// Internal Class Data Accessors
	/// <summary>
	/// Returns the size of the array.
	/// </summary>
	/// <returns>
	/// Size of array.
	/// </returns>
	int GetSize() const {
		return _size;
	}
	
	/// <summary>
	/// Returns the quantity of the array.
	/// </summary>
	/// <returns>
	/// Current quantity of array.
	/// </returns>
	int GetQuantity() const {
		return _quantity;
	}
	
	/// <summary>
	/// Getter method for a specific index pointer
	/// </summary>
	/// <param name="idx">The index requested</param>
	/// <returns>
	/// A pointer to a value
	/// </returns>
	T* GetPointer(int idx) {
		return (start_pos + idx);
	}
	
	/// <summary>
	/// Determines if the array is empty.
	/// </summary>
	/// <returns>
	/// True if empty, false if not empty.
	/// </returns>
	bool IsEmpty() {
		if (_quantity == 0) return true;
		else return false;
	}
	
	/// <summary>
	/// Clears the entire array by deleting and reallocating memory.
	/// </summary>
	void Clear() {
		delete[] start_pos;
		start_pos = new T[1], access_ptr = start_pos, _size = 1, _quantity = 0;
	}
	
	/// <summary>
	/// Prints all the elements in the array.
	/// </summary>
	void Print() {
		for (int i = 0; i < this->GetQuantity(); i++) cout << "Element at Index " << i << ": " << FindAtIndex(i) << endl;
	}

	/// <summary>
	/// Counts the number of inversions in the array
	/// </summary>
	/// <returns>The number of inversions</returns>
	int CountInversions() {
		int inversion_count = 0;

		for (int i = 0; i < this->GetQuantity(); i++) {
			for (int j = i; j < this->GetQuantity(); j++) {
				if (this->FindAtIndex(i) > this->FindAtIndex(j)) { inversion_count++; }
			}
		}

		return inversion_count;
	}

	/// <summary>
	/// Returns the sum of elements in a range
	/// </summary>
	/// <param name="start_idx">The lower bound</param>
	/// <param name="end_idx">The upper bound</param>
	/// <returns>A sum of values</returns>
	long long GetSumOfRange(int start_idx, int end_idx) {
		long long sum = 0;
		for (int i = start_idx; i <= end_idx; i++) { sum += this->FindAtIndex(i); }
		return sum;
	}

// Sorting Algorithms
	/// <summary>
	/// Wrapper that the can be called to mergesort an array
	/// [time complexity O(n log(n))]
	/// </summary>
	void MergeSort() {
		int n = this->GetQuantity();
		if (n <= 1) return;
		DynamicArray<T> temp(n);
		MergeSortRange(0, n - 1, temp);
	}

	/// <summary>
	/// Wrapper method for QuickSort
	/// [best-case time complexity O(n log(n))]
	/// [worst-case time complexity O(n^2)]
	/// </summary>
	void QuickSort() {
		int n = this->GetQuantity();
		if (n <= 1) return;
		DynamicArray<T> temp(n);
		QuickSortRange(0, n - 1, temp);
	}
	
	/// <summary>
	/// Sorts the array using an insertion sort
	/// [time complexity O(n^2)]
	/// </summary>
	void InsertionSort() {
		if (this->GetQuantity() <= 1) return;
		int i = 1;

		while (i < this->GetQuantity()) {
			for (int x = 1; x <= i; x++) {
				if (this->FindAtIndex(x) < this->FindAtIndex(x - 1)) { 
					i = x; 
					break; 
				}
			}

			int swap_idx = i;
			while (this->FindAtIndex(swap_idx) < this->FindAtIndex(swap_idx - 1) && swap_idx > 0) {
				this->SwapIndices(swap_idx, swap_idx - 1);
				swap_idx--;
			}
			i++;
		}
	}
	
	/// <summary>
	/// Sorts through the array, comparing adjacent elements and swapping as necessary
	/// [time complexity O(n^2)]
	/// </summary>
	void BubbleSort() {
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
	/// At each step, finds the smallest remaining unsorted element and puts it into the proper location
	/// [time complexity O(n^2)]
	/// </summary>
	void SelectionSort() {
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

	/// <summary>
	/// Method to complete a bucket sort on an array of linked lists.
	/// [best-case time complexity O(n)]
	/// [worst-case time complexity O(n^2)] (occurs when all elements are in one bucket)
	/// </summary>
	/// <param name="buckets">An array of linked lists (type must be double)</param>
	void BucketSort(LinkedList<double>* buckets) {
		for (int i = 0; i < this->GetSize(); i++) {
			if (buckets[i].Size() == 0) { continue; }

			DynamicArray<double> temp(buckets[i].Size());
			Node<double>* p_temp = buckets[i].Head();
			for (int j = 0; j < buckets[i].Size(); j++) {
				temp.PushBack(p_temp->data);
				p_temp = p_temp->next;
			}
			temp.InsertionSort();
			for (int j = 0; j < temp.GetSize(); j++) {
				this->PushBack(temp[j]);
			}
		}
	}

	/// <summary>
	/// Wrapper method for sort-and-count
	/// </summary>
	/// <returns>The number of inversions</returns>
	int SortAndCount() {
		if (this->GetQuantity() <= 1) { return 0; }
		int n = this->GetQuantity();
		DynamicArray<T> temp(n);
		int inversion_count = SortAndCountRange(0, n - 1, temp);
		return inversion_count;
	}

	/// <summary>
	/// Wrapper method for sort-and-count
	/// </summary>
	/// <returns>The number of weighted inversions</returns>
	long long SortAndCountWeighted() {
		if (this->GetQuantity() <= 1) { return 0; }
		int n = this->GetQuantity();
		DynamicArray<T> temp(n);
		long long weighted_inversions = SortAndCountWeightedRange(0, n - 1, temp);
		return weighted_inversions;
	}

	/// <summary>
	/// WIP
	/// Wrapper method for Select-Rand
	/// [time complexity O(n log(n))]
	/// </summary>
	/// <returns>The median value</returns>
	T SelectRand() {
		if (this->GetQuantity() <= 1) { return 0; }
		int n = this->GetQuantity();
		DynamicArray<T> temp(n);
		int k;
		if (n % 2 == 0) { k = (n - 1) / 2; }
		else { k = (n / 2) - 1; }
		T median = SelectRandRange(0, n - 1, k, temp);
		return median;
	}

	/// <summary>
	/// Wrapper method for Select
	/// [time complexity O(n)]
	/// </summary>
	/// <returns>The median value</returns>
	T Select() {
		int k = (_quantity - 1) / 2;
		if (_quantity % 2 == 0) { k = _quantity / 2; }
		if (k < 0 || k >= _quantity) { return T{}; }
		return SelectRange(0, _quantity - 1, k);
	}

	/// <summary>
	/// Sorts an array of times by finishing time (NOTE: Only works if the array is of type Times)
	/// Algorithm type is an Insertion Sort
	/// </summary>
	void SortFinishTimes() {
		if (this->GetQuantity() <= 1) return;
		int i = 1;

		while (i < this->GetQuantity()) {
			for (int x = 1; x <= i; x++) {
				if (this->FindAtIndex(x).finish < this->FindAtIndex(x - 1).finish) {
					i = x;
					break;
				}
			}

			int swap_idx = i;
			while (swap_idx > 0 && this->FindAtIndex(swap_idx).finish < this->FindAtIndex(swap_idx - 1).finish) {
				this->SwapIndices(swap_idx, swap_idx - 1);
				swap_idx--;
			}
			i++;
		}
	}
};