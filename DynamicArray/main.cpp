#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>  // std::sort

#include "DynamicArray.h"

// -----------------------------
// Minimal test utilities
// -----------------------------
static int g_failCount = 0;

void fail(const std::string& msg) {
    std::cerr << "[FAIL] " << msg << "\n";
    g_failCount++;
}
void pass(const std::string& msg) {
    std::cout << "[PASS] " << msg << "\n";
}

template <typename A, typename B>
void assert_eq(const A& actual, const B& expected, const std::string& msg) {
    if (!(actual == expected)) {
        std::ostringstream oss;
        oss << msg << " (expected: " << expected << ", got: " << actual << ")";
        fail(oss.str());
    }
}

template <typename T>
DynamicArray<T> make_dynamic_array(const std::vector<T>& v) {
    DynamicArray<T> a;
    for (const auto& x : v) a.PushBack(x);
    return a;
}

template <typename T>
bool equals_sorted_result(DynamicArray<T>& a, const std::vector<T>& expectedSorted, std::string& why) {
    if (a.GetQuantity() != (int)expectedSorted.size()) {
        std::ostringstream oss;
        oss << "quantity mismatch (expected " << expectedSorted.size()
            << ", got " << a.GetQuantity() << ")";
        why = oss.str();
        return false;
    }

    for (int i = 0; i < (int)expectedSorted.size(); i++) {
        // Use operator[] (present in your header)
        T got = a[i];
        if (!(got == expectedSorted[i])) {
            std::ostringstream oss;
            oss << "element mismatch at index " << i;
            why = oss.str();
            return false;
        }
    }
    return true;
}

// -----------------------------
// Sort runner wrappers
// -----------------------------
template <typename T>
void run_one_sort_case(const std::string& sortName,
    void (DynamicArray<T>::* sortFn)(),
    const std::vector<T>& input,
    const std::string& caseName) {

    // Build expected reference
    std::vector<T> expected = input;
    std::sort(expected.begin(), expected.end());

    // Build your dynamic array and sort
    DynamicArray<T> a = make_dynamic_array(input);
    (a.*sortFn)();

    std::string why;
    if (!equals_sorted_result(a, expected, why)) {
        std::ostringstream oss;
        oss << sortName << " | " << caseName << " | " << why;
        fail(oss.str());
        return;
    }

    pass(sortName + " | " + caseName);
}

template <typename T>
void run_all_sorts_on_case(const std::vector<T>& input, const std::string& caseName) {
    run_one_sort_case<T>("MergeSort", &DynamicArray<T>::MergeSort, input, caseName);
    run_one_sort_case<T>("InsertionSort", &DynamicArray<T>::InsertionSort, input, caseName);
    run_one_sort_case<T>("BubbleSort", &DynamicArray<T>::BubbleSort, input, caseName);
    run_one_sort_case<T>("SelectionSort", &DynamicArray<T>::SelectionSort, input, caseName);
}

// -----------------------------
// Test data sets
// -----------------------------
std::vector<int> ints_empty() { return {}; }
std::vector<int> ints_one() { return { 42 }; }
std::vector<int> ints_sorted() { return { -5, -1, 0, 2, 9, 13 }; }
std::vector<int> ints_reverse() { return { 13, 9, 2, 0, -1, -5 }; }
std::vector<int> ints_duplicates() { return { 5, 1, 3, 3, 2, 5, 1, 0, 0, -1, -1 }; }
std::vector<int> ints_randomish() { return { 7, -3, 12, 0, 12, 4, -9, 1, 1, 8, -3, 6 }; }

std::vector<std::string> strs_empty() { return {}; }
std::vector<std::string> strs_one() { return { "one" }; }
std::vector<std::string> strs_sorted() { return { "a", "b", "c", "d" }; }
std::vector<std::string> strs_reverse() { return { "delta", "charlie", "bravo", "alpha" }; }
std::vector<std::string> strs_duplicates() { return { "cat", "apple", "cat", "banana", "apple", "dog" }; }
std::vector<std::string> strs_randomish() { return { "z", "aa", "a", "aaa", "ab", "b", "ba", "a" }; }

// Custom struct test (ensures non-trivial type works)
// NOTE: Your MergeSort uses <=, so we define both < and <=.
struct Item {
    int key;
    std::string name;

    bool operator<(const Item& other) const { return key < other.key; }
    bool operator<=(const Item& other) const { return key <= other.key; }
    bool operator==(const Item& other) const { return key == other.key && name == other.name; }
};

std::vector<Item> items_mixed() {
    return {
        {3, "c"},
        {1, "a"},
        {2, "b"},
        {2, "b2"},
        {5, "e"},
        {4, "d"},
        {1, "a2"}
    };
}

// We need std::sort reference for Item: sort by key then name to match your comparison behavior.
// Your sorts use only key comparisons (< / <=) as defined above (by key only).
// That means items with same key may reorder differently depending on algorithm stability.
// So we should compare ONLY by key ordering, not by exact pair ordering.
//
// We'll do a key-sorted check instead of full equality for Item.
bool is_sorted_by_key(const DynamicArray<Item>& a) {
    if (a.GetQuantity() <= 1) return true;
    for (int i = 1; i < a.GetQuantity(); i++) {
        if (a[i].key < a[i - 1].key) return false;
    }
    return true;
}

void test_all_sorts_items_case(const std::vector<Item>& input, const std::string& caseName) {
    {
        DynamicArray<Item> a = make_dynamic_array(input);
        a.MergeSort();
        if (!is_sorted_by_key(a)) fail("MergeSort | " + caseName + " | not sorted by key");
        else pass("MergeSort | " + caseName);
    }
    {
        DynamicArray<Item> a = make_dynamic_array(input);
        a.InsertionSort();
        if (!is_sorted_by_key(a)) fail("InsertionSort | " + caseName + " | not sorted by key");
        else pass("InsertionSort | " + caseName);
    }
    {
        DynamicArray<Item> a = make_dynamic_array(input);
        a.BubbleSort();
        if (!is_sorted_by_key(a)) fail("BubbleSort | " + caseName + " | not sorted by key");
        else pass("BubbleSort | " + caseName);
    }
    {
        DynamicArray<Item> a = make_dynamic_array(input);
        a.SelectionSort();
        if (!is_sorted_by_key(a)) fail("SelectionSort | " + caseName + " | not sorted by key");
        else pass("SelectionSort | " + caseName);
    }
}

// -----------------------------
// Main test runner
// -----------------------------
int main() {
    // ---- int cases ----
    run_all_sorts_on_case<int>(ints_empty(), "int: empty");
    run_all_sorts_on_case<int>(ints_one(), "int: one");
    run_all_sorts_on_case<int>(ints_sorted(), "int: already sorted");
    run_all_sorts_on_case<int>(ints_reverse(), "int: reverse sorted");
    run_all_sorts_on_case<int>(ints_duplicates(), "int: duplicates");
    run_all_sorts_on_case<int>(ints_randomish(), "int: random-ish");

    // ---- string cases ----
    run_all_sorts_on_case<std::string>(strs_empty(), "string: empty");
    run_all_sorts_on_case<std::string>(strs_one(), "string: one");
    run_all_sorts_on_case<std::string>(strs_sorted(), "string: already sorted");
    run_all_sorts_on_case<std::string>(strs_reverse(), "string: reverse sorted");
    run_all_sorts_on_case<std::string>(strs_duplicates(), "string: duplicates");
    run_all_sorts_on_case<std::string>(strs_randomish(), "string: random-ish");

    // ---- struct case (checks ordering by key; avoids stability assumptions) ----
    test_all_sorts_items_case(items_mixed(), "Item: mixed keys + duplicates");

    if (g_failCount == 0) {
        std::cout << "\nALL SORT TESTS PASSED\n";
        return 0;
    }
    else {
        std::cout << "\nSORT TESTS FAILED. Count: " << g_failCount << "\n";
        return 1;
    }
}
