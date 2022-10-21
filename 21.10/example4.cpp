// Compile with C++11!
#include <iostream>

using namespace std;

typedef int (*fill_fn)(int);
void arr_fill(int *arr, int size, fill_fn calc_element)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = calc_element(i);
	}
}

int main()
{
	int size;
	cin >> size;

	int *arr = new int[size];
	arr_fill(arr, size, [](int index) -> int
			 { return index * index; });

	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;

	delete[] arr;
	return 0;
}