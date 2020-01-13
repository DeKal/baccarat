#include "Header.h"
void main()
{
	ifstream fin;
	fin.open("text.txt");
	lable(fin);
	fin.close();
}