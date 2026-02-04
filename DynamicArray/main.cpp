#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include "DynamicArray.h"
#include "LinkedList.h"
using namespace std;

const int N = 100000;

int main(void) {
	random_device rd;
	mt19937 eng(rd());
	uniform_real_distribution<double> uni_dist(0.0, 1.0);
	normal_distribution<double> gaus_dist(0.5, 0.01);

	LinkedList<double>* buckets = new LinkedList<double>[N];
	for (int i = 0; i < N; i++) {
		double num = gaus_dist(eng);
		if (num < 0) { num = 0.0; }
		if (num >= 1) { num = 0.99999f; }
		int idx = static_cast<int>(floor(N * num));
		buckets[idx].PushBack(num);
	}
	DynamicArray<double> output(N);

	auto start = chrono::high_resolution_clock::now();
	output.BucketSort(buckets);
	auto end = chrono::high_resolution_clock::now();

	cout << "Confirming Sorted Order: (If no message pops up, order is correct)\n";
	for (int i = 1; i < output.GetQuantity(); i++) {
		if (output[i] < output[i - 1]) {
			cerr << "Incorrect Placement Found!" << endl;
			cerr << "Larger Value (Index): " << output[i] << "\t(" << i << ")\n";
			cerr << "Smaller Value (Index): " << output[i - 1] << "\t(" << i - 1 << ")\n";
		}
	}

	delete[] buckets;
	output.~DynamicArray();

	chrono::duration<double> duration = end - start;

	cout << "N = " << N << endl;
	cout << "Bucket Sort Runtime: " << duration.count() << " seconds" << endl;

	return 0;
}