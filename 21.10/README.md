# Указатели на функции

```cpp
#include <iostream>

using namespace std;

int sqr(int x) {
  return x * x;
}

int cube(int x) {
  return x * x * x;
}

int main() {
  setlocale(LC_ALL, "RUS");
}
```

У функции `sqr` и `cube` одинаковые описания кроме имен (возращаемый тип, параметры).

Звездочку у указателя на функцию указываем перед названием переменной и ставим скобки для различия.

```cpp
int (*f_pointer)(int);
```

## Указать тип для указателя на функцию

```cpp
typedef int (*f_pointer)(int);
```

Пример определения переменной ([пример](example1.cpp)):

```cpp
f_pointer f_ptr = sqr;
```

## Лямбда-выражение

Структура: `[](параметры) -> возвращаемый тим { тело функции }`

```cpp
typedef int (*fill_ptr)(int);
```

```cpp
full_ptr fill_fn = [](int index) -> int {
  // Квадрат индекса
  return index * index;
}
```

## Примеры

- [Определение переменной](example1.cpp)
- [Массив функций](example2.cpp)
- [Заполнение массива](example3.cpp)
- [Заполнение массива с лямбда-выражением](example4.cpp)
