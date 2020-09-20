#include <iostream>
#include "Prog1.h"

using namespace Prog1;

//основная функция
int main()
{
	Matrix SparseMatrix = { 0,0,nullptr };
	Matrix ResMarix = { 0,0,nullptr };

	print_menu();

	variant(SparseMatrix);

	if (!(SparseMatrix.header))
	{
		std::cout << "incorrect data" << std::endl;
		return 1;
	}
	copymatrix(SparseMatrix, ResMarix);// Создание второго массива

	sortmatrix(ResMarix);//сортировка по условию

	output("Sourced matrix",SparseMatrix);// Вывод матрицы 
	output("Sorted matrix",ResMarix);// Вывод матрицы

	erase(SparseMatrix);// Освобождение памяти 
	erase(ResMarix);// Освобождение памяти 
	return 0;
}


