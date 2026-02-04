#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include "DynamicArray.h"
#include "LinkedList.h"
using namespace std;

const int N = 10000;

int main(void) {
	srand(time(0));
	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<int> dist(0, 1000);

	chrono::duration<double> quick_duration, merge_duration;

	DynamicArray<int> test_quick;

	for (int i = 0; i < N; i++) {
		int rand_num = dist(eng);
		test_quick.PushBack(rand_num);
	}

	DynamicArray<int> test_merge = test_quick;

	// testing quick sort
	auto quick_start = chrono::high_resolution_clock::now();
	test_quick.QuickSort();
	auto quick_end = chrono::high_resolution_clock::now();

	// testing merge sort
	auto merge_start = chrono::high_resolution_clock::now();
	test_merge.MergeSort();
	auto merge_end = chrono::high_resolution_clock::now();

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

	quick_duration = quick_end - quick_start;
	merge_duration = merge_end - merge_start;

	cout << "N = " << N << endl;
	cout << "QuickSort Time: " << quick_duration.count() << " seconds\n";
	cout << "MergeSort Time: " << merge_duration.count() << " seconds\n";

	return 0;
}