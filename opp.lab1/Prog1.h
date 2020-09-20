#include <limits>


namespace Prog1 {
	// ��������� ��� ������� ������ �������


	struct Unit {
		int index; // ������ �������� � ������ ������� 
		double data;// ���������� 
		Unit* next; // ��������� ��������� ������� , ���� ��� ����� �� nullptr 
	};

	struct Line {
		int n; // ������� ���������� ��������� � ������ ������ �������
		double sum;// ����� ���� ��������� � ������ 
		Unit* first; // ������ ��������� ������� , ���� ��� ����� �� nullptr 
	};

	struct Matrix {
		int Clines;// ������������ ���������� ����� 
		int Ccolumns;// ������������ ���������� ��������� � ������
		Line* header; // ������ ���������� �� ������� 
	};

	

	// ������ ������� ����� ������ ��������
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
		if (!std::cin.good())// ���������� ������ ����� ��� ����� �����
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


	// ������� ���������
    inline int isgreater(double a, double b)
	{
		return a > b;
	}

	inline int isless(double a, double b)
	{
		return a < b;
	}

	// ��������� �������
	void input(Matrix&);// ���� ������� 
	void output(const char* msg, Matrix);// ����� �������
	void sortmatrix(Matrix&);//���������� �������
	void erase(Matrix&);//�������� ������
	double findindex(Unit* ptr, int j);// ������� ������ � ������� , ���� ������� �� ��������� �������� , ���� ��� �� 0 
	void copymatrix(Matrix , Matrix& );//����������� �������
	void bubble(Matrix M, Unit* ptr,int n, int(*f)(double, double));//���������� ���������
	void zeroindex(Matrix M, int n, int(*f)(double, double));//���������� ���������� �������
	void print_menu();
	void autotest(Matrix&);//��������������� �������
	void variant(Matrix& M);
	int findSum(Matrix M, Unit** ptr);//������� ������� � ������������ ������
}
