#define _CRT_SECURE_NO_WARNINGS
#define MODE 1
//Mode 1 is check cards
//mode 0 is generating cards
//mode 3 to sum of percentage
#define FILEDATA "test.txt"
#include <stdio.h>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
ifstream fin;
ofstream fout;

//Variables
int ORISPACE = 416;
int DECK[13] = { 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32 };
const int case2[] = { 0, 1, 8, 9 };
const int case3[] = { 0, 1, 2, 3, 8, 9 };
const int case4[] = { -1, 0, 1, 2, 3, 4, 5, 8, 9 };
static FILE *fp;

void restoreDECK(int* turn){
	int card;
	for (int i = 0; i < 6; i++)
	{
		card = turn[i];
		if (card != -1)
		{
			DECK[card - 1]++;
		}
	}
	ORISPACE = 416;
}

void probAll(int* turns){
	
	double tmp1=1, tmp2=1;
	int card;
	for (int j = 0; j < 6; j++)
	{
		card = turns[j];
		if (turns[j] != -1)
		{
			tmp1 *= DECK[card - 1];
			tmp2 *= ORISPACE--;
			DECK[card - 1]--;
		}
	}
	double prob = tmp1 / tmp2;
	fprintf(fp, "%e ", prob);
	restoreDECK(turns);
}

const int N = 6;
int ValueOf(int x){
	if (x >= 10) return 0;
	else return x;
}
int isIn(int x, const int*a, int size){
	for (int i = 0; i < size; i++)
	if (x == a[i]) return true;
	return false;
}

void OutputWin(int* a){
	int  g = 0, h = 1;
	int sum1 = 0, sum2 = 0;
	for (int i = 0; i < 3; i++)
	{
		if (a[g] < 10 && a[g] != -1)
			sum1 += a[g];
		g += 2;
	}
	for (int i = 0; i < 3; i++)
	{
		if (a[h]<10 && a[h] != -1)
			sum2 += a[h];
		h += 2;

	}
	int k = sum1 % 10;
	int l = sum2 % 10;

	int kq;
	if (k > l)
		kq = 1;//Player wins
	else if (k < l)
		kq = 2;//Banker wins
	else kq = 3;
	fprintf(fp, "%d ", kq);
}

void output(int* a){
	if (MODE == 0){
		for (int i = 0; i < 6; ++i)
		fprintf(fp, "%d ", a[i]);
	}
	OutputWin(a);
	probAll(a);
	fprintf(fp, "\n");
}
void GenerateCards(int* a, int n){
	if (n == 4){
		int firstPlayerTwocard = ValueOf(ValueOf(a[0]) + ValueOf(a[2]));
		int firstBankerTwocard = ValueOf(ValueOf(a[1]) + ValueOf(a[3]));
		bool tmp1 = 0, tmp2 = 0;
		if (7 < firstPlayerTwocard) tmp1 = 1;
		if (7 < firstBankerTwocard) tmp2 = 1;
		if (tmp1||tmp2){
			a[4] = -1;
			a[5] = -1;
			output(a);
			return;
		}
		else if ( (!tmp1) && 5 < firstPlayerTwocard){
			a[4] = -1;
			++n;
		}
	}
	if (n == 5){
		int firstTwocard = ValueOf(ValueOf(a[1]) + ValueOf(a[3]));
		if (   (firstTwocard == 3 && a[4] == 8  )
			|| (firstTwocard == 4 && isIn(ValueOf(a[4]), case2, 4))
			|| (firstTwocard == 5 && isIn(ValueOf(a[4]), case3, 6))
			|| (firstTwocard == 6 && isIn(ValueOf(a[4]), case4, 9)))
		{	
			a[5] = -1;
			output(a);
			return;
		}
	}
	if (n >= N) {
		output(a);
		return;
	}
	for (int i = 1; i <= 13; ++i){
		a[n] = i;
		++n;
		GenerateCards(a, n);
		--n;
	}
}

void CheckCards(int* a, int n){
	FILE *fp = fopen(FILEDATA, "r");
	int itmp;
	double ftmp;
	static int maxtrix[10][11];
	while (!feof(fp)){
		for (int i = 0; i < 6; ++i)
			fscanf(fp, "%d", &a[i]);
		fscanf(fp, "%d", &itmp);
		fscanf(fp, "%lf", &ftmp);
		int tmp = ValueOf(ValueOf(a[1]) + ValueOf(a[3]));
		maxtrix[tmp][ValueOf(a[4]) + 1] |= (a[5]>-1);
	}

	for (int i = 0; i < 10; ++i){
		for (int j = 0; j <= 10; ++j)
			printf("%d   ", maxtrix[i][j]);
		printf("\n");
	}
	fclose(fp);
}
void FinalPercentage();
int main(){

	if (MODE == 0){
		int * a = new int[6];
		fp = fopen(FILEDATA, "w+");
		GenerateCards(a, 0);
		fclose(fp);
		cout << "Generate Done!" << endl;
		delete[] a;
	}
	else if (MODE == 1) {
		int * a = new int[6];
		CheckCards(a, 0);
		delete[] a;
	}
	else{
		int * a = new int[6];
		fp = fopen(FILEDATA, "w+");
		GenerateCards(a, 0);
		fclose(fp);
		FinalPercentage();
		cout << "Done!" << endl;
		delete[] a;
	}
	return 0;
}

void FinalPercentage()
{
	int win_case;
	double pro;
	double pro_sum[4] = { 0, 0, 0, 0 };
	fp = fopen(FILEDATA, "r");
	while (!feof(fp)){
		fscanf(fp, "%d", &win_case);
		fscanf(fp, "%lf", &pro);
		pro_sum[win_case] += pro;
	}
	fclose(fp);

	fout.open("output.txt");
	fout << "Player : " << pro_sum[1] * 100 << endl;
	fout << "Banker : " << pro_sum[2] * 100 << endl;
	fout << "Tie : " << pro_sum[3] * 100 << endl;
	fout.close();
}