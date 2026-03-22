#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "CustomHeap.h"
using namespace std;

const int N = 10000;

struct Times {
	int start;
	int finish;
	int original_index;
};

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

	// testing Select for median
	DynamicArray<int> median_array(10);
	// TEST 1: All Equal Vals
	for (int i = 0; i < 10; i++) { median_array.PushBack(1); }
	cout << "Quantity before Select: " << median_array.GetQuantity() << endl;
	int median = median_array.Select();
	cout << "\nExpected Median for Test 1: 1\n";
	cout << "Actual: " << median << endl;

	// TEST 2: Already Sorted
	median_array.Clear();
	for (int i = 0; i < 10; i++) { median_array.PushBack(i); }
	median = median_array.Select();
	cout << "Expected Median for Test 2: 5\n";
	cout << "Actual: " << median << endl;

	// TEST 3: Reverse Sorted
	median_array.Clear();
	for (int i = 9; i >= 0; i--) { median_array.PushBack(i); }
	median = median_array.Select();
	cout << "Expected for Test 3: 5\n";
	cout << "Actual: " << median << endl;

	// TEST 4: Many Duplicates (median should still be stable)
	median_array.Clear();
	// 10 elements total: sorted would be [1,1,2,2,2,2,3,3,3,3]
	// With your expected convention (n=10 -> median reported as 5), the value should be 2.
	int dupVals[10] = { 2, 1, 3, 2, 3, 1, 2, 3, 2, 3 };
	for (int i = 0; i < 10; i++) { median_array.PushBack(dupVals[i]); }
	median = median_array.Select();
	cout << "Expected Median for Test 4: 2\n";
	cout << "Actual: " << median << endl;

	// TEST 5: Even-Length Median Convention (make it very obvious)
	median_array.Clear();
	// Sorted: [0,1,2,3,4,5,6,7,8,9]
	// Your earlier tests expect 5 for n=10 (upper median). Keep that consistent.
	for (int i = 0; i < 10; i++) { median_array.PushBack(i); }
	median = median_array.Select();
	cout << "Expected Median for Test 5 (even-n convention): 5\n";
	cout << "Actual: " << median << endl;

	// TEST 6: Large Random Array (sanity + performance; verify by sorting a copy)
	median_array.Clear();
	const int N = 100000; // bump to 1'000'000 if you want stress testing
	std::mt19937 rng(12345);
	std::uniform_int_distribution<int> dist_2(-1000000, 1000000);

	for (int i = 0; i < N; i++) { median_array.PushBack(dist_2(rng)); }

	// Make a copy before calling Select(), since Select likely mutates the array
	DynamicArray<int> copy_for_check = median_array;

	median = median_array.Select(); // your Select() returns the median
	cout << "Median for Test 6 (Large Random): " << median << endl;

	// Verify by sorting the copy and checking the expected median element.
	// Note: based on your convention, expect the element at index N/2 (upper median for even N).
	copy_for_check.MergeSort();
	int expectedMedian = copy_for_check[N / 2];
	cout << "Expected Median for Test 6 (via sorting check): " << expectedMedian << endl;
	cout << "Actual: " << median << endl;

	// TEST 7: Repeated Calls / Mutation Check (Select may reorder; median should remain same)
	median_array.Clear();
	int vals7[10] = { 9, 0, 8, 1, 7, 2, 6, 3, 5, 4 };
	for (int i = 0; i < 10; i++) { median_array.PushBack(vals7[i]); }

	int median1 = median_array.Select();
	int median2 = median_array.Select(); // if Select mutates, this still should return same median value
	cout << "Expected Median for Test 7: 5\n";
	cout << "Actual (first call): " << median1 << endl;
	cout << "Actual (second call): " << median2 << endl;

	return 0;
}