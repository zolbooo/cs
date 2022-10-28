# Шаблоны

```cpp
#include <iostream>

using namespace std;

template<typename T>
T func(T x) {
  return x * x;
}

int main() {
  setlocale(LC_ALL, "RUS");
  cout << func(3) << endl;
  cout << func(3.5) << endl;
  cout << func<char>(10) << endl;
  return 0;
}
```

## Структуры

В структурах можно хранить любые типы данных.

```cpp
struct my_struct {
  int a;
  double x;
  char s[10];
};
```
