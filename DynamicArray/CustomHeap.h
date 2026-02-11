#pragma once
#include "DynamicArray.h"

template <typename T>
class CustomHeap {
private:
	DynamicArray<T> heap;

	/// <summary>
	/// Helper function to find the index of the parent node
	/// </summary>
	/// <param name="i">The current node index</param>
	/// <returns>The index of the node's parent</returns>
	int FindParent(int i) { return static_cast<int>(floor((i - 1) / 2)); }

	/// <summary>
	/// Helper function to find the index of the left child node
	/// </summary>
	/// <param name="i">The current node index</param>
	/// <returns>The index of the node's left child</returns>
	int FindLeftChild(int i) { return (2 * i + 1); }

	/// <summary>
	/// Helper function to find the index of the right child node
	/// </summary>
	/// <param name="i">The current node index</param>
	/// <returns>The index of the node's right child</returns>
	int FindRightChild(int i) { return (2 * i + 2); }
public:
	/// <summary>
	/// Default constructor
	/// </summary>
	CustomHeap() {}

	CustomHeap(int size) {
		heap.SetSize(size);
	}

	/// <summary>
	/// Function to build the heap structure from a DynamicArray
	/// </summary>
	/// <param name="vals">A DynamicArray of values</param>
	void BuildHeap(DynamicArray<T>& vals) {
		if (vals.GetQuantity() <= 1) { return; }
		int n = vals.GetQuantity();

		for (int i = 0; i < n; i++) {
			this->AddKey(vals[i]);
		}
	}

	/// <summary>
	/// Function to add a new value to the heap strucutre
	/// </summary>
	/// <param name="val">The value to be added</param>
	void AddKey(const T& val) {
		heap.PushBack(val);
		this->HeapifyUp(heap.GetQuantity() - 1);
	}

	/// <summary>
	/// Function that can move a smaller child node to the parent node index
	/// </summary>
	/// <param name="i">The index of the node</param>
	void HeapifyUp(int i) {
		while (i > 0 && heap[i] < heap[this->FindParent(i)]) {
			heap.SwapIndices(i, this->FindParent(i));
			i = this->FindParent(i);
		}
	}

	/// <summary>
	/// Function that can move larger values down the heap strucutre
	/// </summary>
	/// <param name="i">The index of the node</param>
	void HeapifyDown(int i) {
		int n = heap.GetQuantity() - 1;
		while ((this->FindLeftChild(i) <= n && heap[i] > heap[this->FindLeftChild(i)]) ||
			(this->FindRightChild(i) <= n && heap[i] > heap[this->FindRightChild(i)])) {
			int left_child_idx = this->FindLeftChild(i), right_child_idx = this->FindRightChild(i);
			int j;

			if (right_child_idx > n || heap[left_child_idx] < heap[right_child_idx]) { j = left_child_idx; }
			else { j = right_child_idx; }
			heap.SwapIndices(i, j);
			i = j;
		}
	}

	/// <summary>
	/// Extracts the smallest element and reconfigures the heap structure
	/// </summary>
	/// <returns>The removed value</returns>
	T ExtractMin() {
		T min = heap[0];
		heap[0] = heap[heap.GetQuantity() - 1];
		heap.ReduceQuantity();
		HeapifyDown(0);
		return min;
	}

	/// <summary>
	/// Sorts the heap and removes each element in the sorted order which is then stored in the DynamicArray parameter
	/// </summary>
	/// <param name="vals">The DynamicArray that the values will be sorted into</param>
	void HeapSort(DynamicArray<T>& vals) {
		this->BuildHeap(vals);
		int n = vals.GetQuantity();

		for (int i = 0; i < n; i++) {
			vals[i] = this->ExtractMin();
		}
	}
};