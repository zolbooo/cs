#include <iostream>

using namespace std;

int sqr(int x)
{
	return x * x;
}

int cube(int x)
{
	return x * x * x;
}

typedef int (*f_pointer)(int);

int main()
{
	setlocale(LC_ALL, "RUS");
	f_pointer f_ptr = sqr;
	int x = 2;
	cout << f_ptr(x) << endl;
	f_ptr = cube;
	cout << f_ptr(x) << endl;
	return 0;
}