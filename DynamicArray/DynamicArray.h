#pragma once
#include <iostream>
using namespace std;

class DynamicArray
{
private:
	int* start_pos;		// always points to the first index of memory
	int _size;			// the current max size of the array
	int _quantity;		// the number of elements in the current array
	int* access_ptr;	// used to obtain the value at specific indicies

	// Internal Functions
	void MergeRange(int left, int mid, int right, DynamicArray& temp);
	void MergeSortRange(int left, int right, DynamicArray& temp);

public:
	// Basic Class Overhead
	DynamicArray();
	DynamicArray(int size);
	DynamicArray(const DynamicArray& other);
	DynamicArray& operator=(const DynamicArray& other);
	~DynamicArray();

	// Size Manipulation, Insertion, Removals
	void IncreaseSize();
	void PushBack(int val);
	void PopBack();
	void Remove(int idx);
	void SwapIndices(int start_idx, int end_idx);
	void Insert(int idx, int val);

	// Element Access Operations
	int FindAtIndex(int idx);
	void ReplaceElement(int idx, int val);
	int& operator[](int idx);
	int FindElement(int val);
	bool Contains(int val);

	// Internal Class Data Accessors
	int GetSize();
	int GetQuantity();
	int* GetPointer(int idx);
	bool IsEmpty();
	void Clear();
	void Print();

	// Sorting Algorithms
	void MergeSort();
	void InsertionSort();
	void BubbleSort();
	void SelectionSort();
	void QuickSort();
};