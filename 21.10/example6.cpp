#include <iostream>
using namespace std;

template <typename T>
T sqr(T n)
{
	return n * n;
}

int main()
{
	cout << sqr(3) << ' ' << sqr(3.14) << endl;

	int n;
	cin >> n;
	cout << sqr(n) << endl;

	float x;
	cin >> x;
	cout << sqr(x) << endl;

	double z;
	cin >> z;
	cout << sqr(z) << endl;
	return 0;
}