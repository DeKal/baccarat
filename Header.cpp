#include "Header.h"
void lable(istream& fin)
{
	ofstream fout;
	fout.open("output.txt");
	while (!fin.eof())
	{
		int  g= 0, h = 1;
		int * a = new int[7];
		for (int i = 0; i < 6; i++)
		{
			int x;
			fin >> x;
			a[i] = x;
		}
		int sum1 = 0, sum2 = 0;
		for (int i = 0; i < 3; i++)
		{
			if (a[g] != -1 && a[g]<10)
				sum1 += a[g];
			g += 2;
		}
		for (int i = 0; i < 3; i++)
		{
			if (a[h] != -1 && a[h]<10)
				sum2 += a[h];
			h += 2;

		}
		int k = sum1 % 10; 
		int l = sum2 % 10;
		if (k > l)
			a[6] = 1;
		else if (k < l)
			a[6] = 2;
		else
			a[6] = 3;
		for (int i = 0; i < 7; i++)
			fout << a[i] << " ";
		fout << endl;
		
	}
	fout.close();
}