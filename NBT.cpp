#include <iostream>
using namespace std;
#include <fstream>

ifstream fin;
ofstream fout;

void main()
{
	int win_case;
	double pro;
	double pro_sum[4];
	pro_sum[0] = 0;
	pro_sum[1] = 0;
	pro_sum[2] = 0;
	pro_sum[3] = 0;
	fin.open("input.txt");
	int count = 1;
	do
	{
		for (int i = 0; i < 6; ++i)
		{
			fin >> pro;
		}
		fin >> win_case;
		fin >> pro;
		pro_sum[0] += pro;
		pro_sum[win_case] += pro;

		if (count == 20000)
		{
			cout << "Total : " << pro_sum[0] << endl;
			cout << "Player : " << pro_sum[1] << endl;
			cout << "Banker : " << pro_sum[2] << endl;
			cout << "Tie : " << pro_sum[3] << endl;
			cout << endl;
			count = 0;
		}
		++count;
	} while (!fin.eof());
	fin.close();

	for (int i = 0; i < 4; ++i)
	{
		cout << pro_sum[i] << endl;
	}

	fout.open("output.txt");
	fout << "Total : " << pro_sum[0] << endl;
	fout << "Player : " << pro_sum[1] << endl;
	fout << "Banker : " << pro_sum[2] << endl;
	fout << "Tie : " << pro_sum[3] << endl;
	fout.close();
}