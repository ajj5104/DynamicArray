#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "CustomHeap.h"
#include "Times.h"
using namespace std;

const int N = 10000;

int main(void) {
	srand(time(0));
	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<int> dist(0, 1000);

	chrono::duration<double> quick_duration, merge_duration, heap_duration, sort_and_count_duration;

	DynamicArray<int> test_quick;

	for (int i = 0; i < N; i++) {
		int rand_num = dist(eng);
		test_quick.PushBack(rand_num);
	}

	DynamicArray<int> test_merge = test_quick;
	CustomHeap<int> test_heap(N);
	DynamicArray<int> heap_array = test_quick;
	DynamicArray<int> test_inversion = test_quick;

	// testing quick sort
	auto quick_start = chrono::high_resolution_clock::now();
	test_quick.QuickSort();
	auto quick_end = chrono::high_resolution_clock::now();

	// testing merge sort
	auto merge_start = chrono::high_resolution_clock::now();
	test_merge.MergeSort();
	auto merge_end = chrono::high_resolution_clock::now();

	// testing heap sort
	test_heap.BuildHeap(heap_array);
	auto heap_start = chrono::high_resolution_clock::now();
	test_heap.HeapSort(heap_array);
	auto heap_end = chrono::high_resolution_clock::now();

	// Results and Confirmation
	for (int i = 1; i < test_quick.GetQuantity(); i++) {
		if (test_quick[i] < test_quick[i - 1]) {
			cerr << "QuickSort was out of order in some spot!\n";
			break;
		}
	}
	for (int i = 1; i < test_merge.GetQuantity(); i++) {
		if (test_merge[i] < test_merge[i - 1]) {
			cerr << "MergeSort was out of order in some spot!\n";
			break;
		}
	}
	for (int i = 1; i < heap_array.GetQuantity(); i++) {
		if (heap_array[i] < heap_array[i - 1]) {
			cerr << "HeapSort was out of order in some spot!\n";
			break;
		}
	}

	// test inversion counter
	int inv = test_inversion.CountInversions();
	cout << "Inversions: " << inv << endl;

	// test sort-and-count (should have 22 inversions)
	auto sort_and_count_start = chrono::high_resolution_clock::now();
	int sort_inv = test_inversion.SortAndCount();
	auto sort_and_count_end = chrono::high_resolution_clock::now();
	for (int i = 1; i < test_inversion.GetQuantity(); i++) {
		if (test_inversion[i] < test_inversion[i - 1]) {
			cerr << "Sort-and-Count was out of order in some spot!\n";
			break;
		}
	}
	cout << "Inversions: " << sort_inv << endl;

	quick_duration = quick_end - quick_start;
	merge_duration = merge_end - merge_start;
	heap_duration = heap_end - heap_start;
	sort_and_count_duration = sort_and_count_end - sort_and_count_start;

	cout << "\nN = " << N << endl;
	cout << "QuickSort Time: " << quick_duration.count() << " seconds\n";
	cout << "MergeSort Time: " << merge_duration.count() << " seconds\n";
	cout << "HeapSort Time: " << heap_duration.count() << " seconds\n";
	cout << "Sort-and-Count Time: " << sort_and_count_duration.count() << " seconds\n";

	// testing weighted inversion counts
	DynamicArray<int> test_weight;
	test_weight.PushBack(7);
	test_weight.PushBack(3);
	test_weight.PushBack(8);
	test_weight.PushBack(1);
	test_weight.PushBack(5);

	int weighted_inversions = test_weight.SortAndCountWeighted();

	cout << "\nExpected Weight: 56\n";
	cout << "Actual Weight: " << weighted_inversions << endl;

	return 0;
}