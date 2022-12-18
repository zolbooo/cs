#include <functional>
#include <iostream>

using namespace std;

// typedef bool(*comparator_t)(int, int);

bool comparator_less(int a, int b) {
	return a <= b;
}
bool comparator_greater(int a, int b) {
	return a > b;
}
bool comparator_abs_less(int a, int b) {
	return abs(a) <= abs(b);
}

int *bubble_sort(int *arr, int size, function<bool(int, int)> comparator) {
	for (int i = size - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (!comparator(arr[j], arr[j + 1])) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

int main() {
	/*
	if (arr[i] > arr[j]) {
		swap(arr[i], arr[j]);
	}
	*/
	/*
	if (!comparator(arr[i], arr[j])) {
		swap(arr[i], arr[j]);
	}
	*/
	int a, b;
	cin >> a >> b;
	cout << comparator_less(a, b) << endl;
	cout << comparator_greater(a, b) << endl;
	cout << comparator_abs_less(a, b) << endl;
	// bubble_sort(arr, n, comparator_less);
	// bubble_sort(arr, n, comparator_greater);
	// bubble_sort(arr, n, comparator_abs_less);
	return 0;
}
