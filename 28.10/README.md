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

В структуре нельзя объявлять поля собственного типа, но указатели добавлять можно.

Нельзя:

```cpp
struct my_struct {
  my_struct next;
};
```

Можно:

```cpp
struct my_struct {
  my_struct *next;
};
```

### Union

```cpp
union my_inion {
  long long x;
  double z;
};
```
