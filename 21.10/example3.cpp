#include <iostream>
#include <ctime>

using namespace std;

void zero_fill(int *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = 0;
	}
}

void rand_fill(int *arr, int size)
{
	srand(time(nullptr) + rand());
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand();
	}
}

void manual_fill(int *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		cin >> arr[i];
	}
}

typedef void (*fill_ptr)(int *, int);

int main()
{
	fill_ptr do_fill;

	int size;
	cin >> size;

	cout << "Select action:" << endl;
	cout << "1. Zero fill" << endl;
	cout << "2. Random fill" << endl;
	cout << "3. Manual fill" << endl;
	int command;
	cin >> command;
	switch (command)
	{
	case 1:
		do_fill = zero_fill;
		break;
	case 2:
		do_fill = rand_fill;
		break;
	case 3:
		do_fill = manual_fill;
		break;
	default:
		cout << "Unknown action" << endl;
		return 1;
	}

	int *arr = new int[size];
	do_fill(arr, size);

	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;

	delete[] arr;
	return 0;
}