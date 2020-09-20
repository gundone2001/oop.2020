#include <limits>


namespace Prog1 {
	// структура для задания строки матрицы


	struct Unit {
		int index; // Индекс элемента в строке матрицы 
		double data;// Информация 
		Unit* next; // Следующий ненулевой элемент , если нет таких то nullptr 
	};

	struct Line {
		int n; // Текущее количество элементов в данной строке матрицы
		double sum;// Сумма всех элементов в строке 
		Unit* first; // Первый ненулевой элемент , если нет таких то nullptr 
	};

	struct Matrix {
		int Clines;// Максимальное количество строк 
		int Ccolumns;// Максимольное количество элементов в строке
		Line* header; // Массив указателей на строчки 
	};

	

	// шаблон функций ввода одного значения
	template <class T>
	int getNum(T& a)
	{
		
		do {
			std::cin >> a;
			if (!std::cin.good()  ||  std::cin.peek() != '\n')
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Enter a allowed data , please -->";
			}
			else{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
			}
		} while (1);
		return 1;
		
		/*
		std::cin >> a;
		if (!std::cin.good())// обнаружена ошибка ввода или конец файла
		{
			std::cout << "Fuck";
			return -1;
		}
		return 1;
		*/
	}


	template <class T>
	int repeatenter(T& a, const char* msg,T max  , T count )
	{
		const char* pr = "";	
		do {
			std::cout << pr << std::endl;
			std::cout << msg ;
			pr = "You are wrong; repeat please!";
			if (getNum(a) < 0) {
				return -1;
			}

		} while ((a < count) || (a > max ));
		return 1;
	}


	// функции сравнения
    inline int isgreater(double a, double b)
	{
		return a > b;
	}

	inline int isless(double a, double b)
	{
		return a < b;
	}

	// прототипы функций
	void input(Matrix&);// Ввод матрицы 
	void output(const char* msg, Matrix);// Вывод матрицы
	void sortmatrix(Matrix&);//Сортировка матрицы
	void erase(Matrix&);//очищение памяти
	double findindex(Unit* ptr, int j);// Находит индекс в строчке , если находит то возращает значение , если нет то 0 
	void copymatrix(Matrix , Matrix& );//Копирование матрицы
	void bubble(Matrix M, Unit* ptr,int n, int(*f)(double, double));//сортировка пузырьком
	void zeroindex(Matrix M, int n, int(*f)(double, double));//Выставляет правельные индексы
	void print_menu();
	void autotest(Matrix&);//Автозаполнитель матрицы
	void variant(Matrix& M);
	int findSum(Matrix M, Unit** ptr);//Находит строчку с максимальной суммой
}
