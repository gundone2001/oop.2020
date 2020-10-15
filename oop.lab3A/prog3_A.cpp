#include <iostream>
#include "../librarylab3/MofINT.h"

int main()
{
	maximka::MofINT a(-1);
	a.output(std::cout);
	maximka::MofINT b(10);
	maximka::MofINT m[] = { a, b };
	int p[] = { 6,5,4,3,2,1 };
	maximka::MofINT k1(6,p);
	maximka::MofINT k2(3, {5,6,1});
	int B = b.getSIZE();
	int A = a.getSIZE();
	int M = m[1].getSIZE();
	std::cout << B << " " << A <<" "<<M<< std::endl;
	k1.output(std::cout);
	k2.output(std::cout);
	maximka::MofINT G;
	G.diff(k1, k2);
	std::cout << G.getSIZE() << std::endl;
	G.output(std::cout);
	G.add(7);
	std::cout << G.getSIZE() << std::endl;
	G.output(std::cout);
	std::cout << G.in(7) << std::endl;
	a.input(std::cin);
	a.output(std::cout);
}
