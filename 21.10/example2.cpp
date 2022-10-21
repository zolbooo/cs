#include <iostream>

using namespace std;

int zero(int x) {
	return 1;
}

int lin(int x) {
	return x;
}

int sqr(int x)
{
	return x * x;
}

int cube(int x)
{
	return x * x * x;
}

typedef int (*f_pointer)(int);
f_pointer fns[] = {zero, lin, sqr, cube};

int main()
{
	setlocale(LC_ALL, "RUS");
	int x = 2;
	for (int i = 0; i < 4; i++) {
		cout << fns[i](x) << endl;
	}
	return 0;
}