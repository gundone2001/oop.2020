#include <iostream>
#include "Prog1.h"
#include <limits>
#include <time.h>

#define SEED 9

namespace Prog1 {
	
	double MAX = DBL_MAX;
	double MIN = -DBL_MAX;
	void(*fptr[])(Matrix&) = { input ,autotest};

	void print_menu() {
		std::cout << "What do you want to do?" << std::endl;
		std::cout << "0. Manual input " << std::endl;
		std::cout << "1. Auto input" << std::endl;
	}
	
	void variant(Matrix& M)
	{
		int variant;
		if (repeatenter(variant, "Enter variant: --> ", 1, 0) < 0) {
			return;
		}
		fptr[variant](M);
		return;
	}

	void input(Matrix& M)//ввод матрицы
	{
		const char* pr = "";
		Matrix mtrx;
		int countlines, countcolumns;
		if (repeatenter(countlines, "Enter number of lines: --> ", INT_MAX,1) < 0  ) {
			return; 
		}

		try {
			mtrx.header = new Line[countlines];
		}
		catch (std::bad_alloc& ba)
		{
			std::cout << "------ too many rows in matrix: " << ba.what() << std::endl;
			return;
		}
      
		if (repeatenter(countcolumns, "Enter number of columns: --> ", INT_MAX, 1) < 0) {
			return;
		}
		
		for (int i = 0; i < countlines; ++i)
		{
			int nozeroel;
			int index = 0; 
			double Sum = 0;
			double data = 0;
			Unit* last = nullptr;
			Unit* first = nullptr;
			mtrx.header[i].first = first;
			std::cout << "Line №" << (i + 1) << ":";
			if (repeatenter(nozeroel,"Enter chislo nozero elemnt --> ", countcolumns,0) < 0 ) {
				return;
			}
			if (nozeroel == 0){
				last = nullptr;
				first = nullptr;
				Sum = 0;
			}
			else{
				for (int j = 0; j < nozeroel; ++j) {
					Unit* ptr;
					do {
						if (repeatenter(index, "Enter index element: --> ", countcolumns - 1, 0) < 0) {
							return;
						}
					} while (findindex(first, index));
	
					if (repeatenter(data,"Enter data element: --> ",MAX,MIN) < 0) {
						return;
					}

					try {
						ptr = new Unit;
					}
					catch (std::bad_alloc& ba)
					{
						std::cout << "--------Not enough memory  " << ba.what() << std::endl;
						erase(mtrx);
						return;
					}

					Sum = Sum + data;

					ptr->data = data;
					ptr->index = index;
					ptr->next = nullptr;


					if (!first) {
						first = ptr;
						mtrx.header[i].first = first;
					}
					else {
						last->next = ptr;
					}
					last = ptr;
				}
			}
			mtrx.header[i].sum = Sum;
			mtrx.header[i].n = nozeroel;
		}
		M.Ccolumns = countcolumns;
		M.Clines = countlines;
		M.header = mtrx.header;
	}

	double findindex(Unit* ptr, int j)// Находит индекс в строчке , если находит то возращает значение , если нет то 0 
	{
		Unit* tmp = ptr;
		if (tmp == nullptr) {
			return 0;
		}
		do{
			if (tmp->index == j)
			{
				return tmp->data;
			}
			tmp = tmp->next;
		} while (tmp != nullptr);
		return 0;
	}

	void output(const char* msg, Matrix M)//вывод матрицы
	{
		std::cout << msg << std::endl;
		for ( int i = 0; i < M.Clines; ++i) {
			for (int j = 0; j < M.Ccolumns; j++)
			{
				Unit* ptr = M.header[i].first;
				double elem = findindex(ptr, j);
				std::cout << elem << "\t|";
			}
			std::cout << "Sum:" << M.header[i].sum;
			std::cout << std::endl;
		}
	}
	void erase(Matrix& M)//очищение памяти
	{
		M.Ccolumns = 0;
		M.Clines = 0;
		for (int i = 0; i < M.Clines; ++i)
		{
			Unit* ptr = M.header[i].first;
			Unit* tmp = nullptr;
			for (int j = 0; j < M.header[i].n; ++j)
			{
				if (ptr != nullptr) {
					tmp = ptr->next;
				}
				delete ptr;
				ptr = tmp;
				tmp = nullptr;
			}
			std::cout << std::endl;
		}
		delete[] M.header;
		return;
	}
	
	int findSum(Matrix M,Unit** ptr)//Находит строчку с максимальной суммой
	{
		int n = -1;
		double	maxSum = MIN;
		for (int i = 0; i < M.Clines; ++i)
		{
			if (M.header[i].sum > maxSum) {
				maxSum = M.header[i].sum;
				n = i;
				*ptr = M.header[i].first;
			}
		}
		return n;
	}


	void  copymatrix(Matrix Sm, Matrix& Nm)//Копирование матрицы
	{
		Nm.Ccolumns = Sm.Ccolumns;
		Nm.Clines = Sm.Clines;
		
		try
		{
			Nm.header = new Line[Nm.Clines];
		}
		catch (std::bad_alloc& ba)
		{
			std::cout << "------ too many rows in matrix: " << ba.what() << std::endl;
			return;
		}

		for (int i = 0; i < Nm.Clines; ++i)
		{
			Unit* first = nullptr, * last = nullptr, * ptr;
			Nm.header[i].n = Sm.header[i].n;
			Nm.header[i].sum = Sm.header[i].sum;
			Nm.header[i].first = first;
			ptr = Sm.header[i].first;
			for (int j = 0; j < Nm.header[i].n; ++j)
			{
				Unit* tmp;
				try {
					tmp = new Unit;
				}
				catch (std::bad_alloc& ba)
				{
					std::cout << "--------Not enough memory  " << ba.what() << std::endl;
					erase(Nm);
					return;
				}
				tmp->data = ptr->data;
				tmp->index = ptr->index;
				tmp->next = nullptr;
				ptr = ptr->next;

				if (!first) {
					first = tmp;
					Nm.header[i].first = first;
				}
				else {
					last->next = tmp;
				}
				last = tmp;
			}
		}	
	}	
	void sortmatrix(Matrix& M)//Сортировка матрицы
	{
		Unit* ptr = nullptr;
		int n = findSum(M, &ptr);
		double  data = findindex(ptr, 0);
		if (data > 0)
		{
			std::cout << "Max Sum: "<<M.header[n].sum<<" |"<<std::endl;
			std::cout << "Sorted " << n+1 << " line|" << std::endl;
			std::cout << "Sorted  to  up |"<< std::endl;
			bubble(M, ptr,n, isgreater);
			zeroindex(M, n, isgreater);
		}
		if (data <= 0)
		{
			std::cout << "Max Sum: " << M.header[n].sum << " |" << std::endl;
			std::cout << "Sorted " << n+1 << " line|" << std::endl;
			std::cout << "Sorted  to  down  |" << std::endl;
			bubble(M, ptr,n, isless);
			zeroindex(M, n, isless);
		}
	}

	void bubble(Matrix M, Unit* ptr,int n, int(*f)(double, double))//сортировка пузырьком
	{
		Unit * tmp = nullptr;
		for (int i = 0; i < M.header[n].n - 1; i++) {
			ptr = M.header[n].first;
			for (int j = 0; j < M.header[n].n - i - 1; j++) {
				tmp = ptr->next;
				if (f(ptr->data,tmp->data)) {
					double  temp = ptr->data;
					ptr->data = tmp->data;
					tmp->data = temp;
				}
				ptr = ptr->next;
			}
		}
	}

	void zeroindex(Matrix M,int n, int(*f)(double, double))//Выставляет правельные индексы
	{ 
		Unit* ptr;
		ptr = M.header[n].first;
		int zerop = M.Ccolumns - M.header[n].n;
		for (int j = 0; j < M.header[n].n; ++j) {
			if (f(ptr->data, 0)) {
				ptr->index = j + zerop;
			}
			else
			{
				ptr->index = j;
			}
			ptr = ptr->next;
		}
	}
	void autotest(Matrix& SparseMatrix)//Автозаполнитель матрицы
	{
		srand(SEED);
		Matrix Sm;
		int line, column;
		line = rand() % 5 + 4;
		try {
			Sm.header = new Line[line];
		}
		catch (std::bad_alloc& ba)
		{
			std::cout << "------ too many rows in matrix: " << ba.what() << std::endl;
			return;
		}
		std::cout << "Line --> " << line << std::endl;

		column = rand() % 5 + 6;

		std::cout << "Column --> " << column << std::endl;

		for (int i = 0; i < line ; ++i)
		{
			int nozeroel;
			int index = 0;
			double Sum = 0;
			double data = 0;
			Unit* last = nullptr;
			Unit* first = nullptr;
			Sm.header[i].first = first;
			nozeroel = rand() % (column+1)/2;
			if (nozeroel == 0) {
				last = nullptr;
				first = nullptr;
				Sum = 0;
			}
			else {
				for (int j = 0; j < nozeroel; ++j) {
					Unit* ptr;
					do {
						index = rand() % column ;
					} while (findindex(first, index));

					data = (rand()%2000 - 1000)/20.0;	

					try {
						ptr = new Unit;
					}
					catch (std::bad_alloc& ba)
					{
						std::cout << "--------Not enough memory  " << ba.what() << std::endl;
						erase(Sm);
						return;
					}

					Sum = Sum + data;

					ptr->data = data;
					ptr->index = index;
					ptr->next = nullptr;

					if (!first) {
						first = ptr;
						Sm.header[i].first = first;
					}
					else {
						last->next = ptr;
					}
					last = ptr;
				}
			}
			Sm.header[i].sum = Sum;
			Sm.header[i].n = nozeroel;
		}
		SparseMatrix.Ccolumns = column;
		SparseMatrix.Clines = line;
		SparseMatrix.header = Sm.header;
	}
}