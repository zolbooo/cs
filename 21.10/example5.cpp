// Compile with C++11!
#include <iostream>
#include <functional>

using namespace std;

void arr_fill(int *arr, int size, function<int(int)> calc_element)
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
	arr_fill(arr, size, [size](int index) -> int
			 { return index * size; });

	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;

	delete[] arr;
	return 0;
}