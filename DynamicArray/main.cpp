#include <iostream>
#include "DynamicArray.h"
using namespace std;

int main(void) {
	// testing merge sort
	DynamicArray test;
	cout << "Merge Sort Test:\n";
	test.PushBack(5);
	test.PushBack(3);
	test.PushBack(4);
	test.PushBack(1);
	test.PushBack(2);
	test.Print();

	test.MergeSort();
	cout << '\n';
	test.Print();
	cout << '\n';

	// testing insertion sort
	test.Clear();
	cout << "Insertion Sort Test:\n";
	test.PushBack(5);
	test.PushBack(3);
	test.PushBack(4);
	test.PushBack(1);
	test.PushBack(2);
	test.Print();

	test.InsertionSort();
	cout << '\n';
	test.Print();
	cout << '\n';

	// testing bubble sort
	test.Clear();
	cout << "Bubble Sort Test:\n";
	test.PushBack(5);
	test.PushBack(3);
	test.PushBack(4);
	test.PushBack(1);
	test.PushBack(2);
	test.Print();

	test.BubbleSort();
	cout << '\n';
	test.Print();
	cout << '\n';

	test.~DynamicArray();

	return 0;
}