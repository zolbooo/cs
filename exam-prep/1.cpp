/*
 * Дана матрица некоторого числового типа размера M × N. [✅]
 * Найти количество ее диагоналей, параллельной главной, элементы
 * которых упорядочены по возрастанию, если перебирать сверху вниз. [✅]
 * Элементы матрицы считать из бинарного файла. [-]
 * Для выполнения операций с матрицей создать шаблонные функции. [🫡]
 * Протестировать их работу на матрицах как минимум 2х типов разных размеров (например, char и float). [✅]
 */
#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
T **generate_matrix(size_t m, size_t n)
{
	auto result = new T *[m];	// Создаем массив указателей, т.е. строк матрицы
	for (int i = 0; i < m; i++) // Для каждой строки
	{
		result[i] = new T[n]; // Создаем ячейки в каждой строке
		for (int j = 0; j < n; j++)
		{
			result[i][j] = rand() % 21 - 10; // Заполняем случайными значениями из [-10; 10]
		}
	}

	cout << "Сгенерирована матрица:" << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << result[i][j] << '\t';
		}
		cout << endl;
	}
	return result;
}
template <typename T>
T **read_matrix(size_t m, size_t n)
{
	auto result = new T *[m];	// Создаем массив указателей, т.е. строк матрицы
	for (int i = 0; i < m; i++) // Для каждой строки
	{
		result[i] = new T[n]; // Создаем ячейки в каждой строке
		for (int j = 0; j < n; j++)
		{
			cin >> result[i][j]; // Читаем крч
		}
	}
	return result;
}

// Очистить выделеннную память от матрицы, наверное.
template <typename T>
void dealloc_matrix(T **matrix, int m)
{
	// Очистить строки
	for (int i = 0; i < m; i++)
	{
		delete[] matrix[i];
	}
	// А потом удалить саму матрицу 🦉
	delete[] matrix;
}

// Задача записи в файл тривиальна и оставлена для написания читателю 😂

template <typename T>
bool is_diagonal_ascending(T **matrix, int m, int n, int start_i, int start_j)
{
	int i = start_i;
	int j = start_j;
	/*
	 * Бежим по диагонали, сохраняя значения в last_value
	 * Если находим инверсию, возращаем афдыу (false) 😂
	 */
	int last_value = matrix[i][j];
	while (i < m && j < n)
	{
		if (matrix[i][j] < last_value)
		{
			// [2, 1]
			// [1, 1]
			// Пример, если бежим по главной диагонали, то в случае matrix[1][1] < matrix[0][0] = last_value
			return false;
		}
		last_value = matrix[i][j];
		i += 1;
		j += 1;
	}
	// Если мы здесь, то инверсий
	return true;
}

template <typename T>
size_t solve(T **matrix, size_t m, size_t n)
{
	size_t result = 0;
	/*
	 * Теперь нужно пробежаться по всем диагоналям параллельной главной.
	 * Берем все угловые элементы, то есть [0][0...n - 1] и [1...m - 1][0]
	 *			_ _ _ _
	 *			_ * * *
	 *			_ * * *
	 * 			_ * * *
	 */
	for (int j = 0; j < n; j++)
	{
		result += is_diagonal_ascending(matrix, m, n, 0, j);
	}
	for (int i = 1; i < m; i++)
	{
		result += is_diagonal_ascending(matrix, m, n, i, 0);
	}
	return result;
}

template <typename T>
size_t solve_with_input(int input_choice, size_t m, size_t n)
{
	T **matrix;
	if (input_choice == 1)
	{
		matrix = generate_matrix<T>(m, n);
	}
	else
	{
		matrix = read_matrix<T>(m, n);
	}
	auto result = solve<T>(matrix, m, n);
	// Обязательно, а то настучат тапками по пальцам ‼
	dealloc_matrix(matrix, m);
	return result;
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "RUS");

	cout << "1. Сгенерировать массив" << endl;
	cout << "2. Считать массив" << endl;
	int input_choice = 0;
	do
	{
		cin >> input_choice;
		if (input_choice != 1 && input_choice != 2) // Проверяем что наш "умный" пользователь ввел
		{
			cout << "Неправильный выбор" << endl; // Гуляй, мальчик
		}
	} while (input_choice != 1 && input_choice != 2);

	cout << "Выберите тип:" << endl;
	cout << "1. char" << endl;
	cout << "2. int" << endl;
	// Добавить типов по вкусу
	int type = 0;
	do
	{
		cin >> type;
		if (type != 1 && type != 2) // Проверяем что наш "умный" пользователь ввел
		{
			cout << "Неправильный выбор" << endl; // Гуляй, мальчик
		}
	} while (type != 1 && type != 2);

	cout << "Введите размер матрицы" << endl;
	size_t m, n;
	cin >> m >> n;

	size_t result;
	if (type == 1)
	{
		result = solve_with_input<char>(input_choice, m, n);
	}
	else if (type == 2)
	{
		result = solve_with_input<int>(input_choice, m, n);
	}
	cout << "Результат: " << result << endl;
	return 0;
}