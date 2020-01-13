#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/* Global Declaration */
//Struct
struct Turn{
	int draws[7];
};


//Variables
int ORISPACE = 416;
int DECK[13] = { 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32 };

//Functions
double probAtOnce(int card);
void restoreDECK(Turn* turn);
void probAll(double* probArray, vector<Turn*> &turns);
void saveToFile(ofstream &fout,double* probArray, vector<Turn*> turns);
bool input(ifstream &fin, vector<Turn*> &turns);
void free(vector<Turn*> &turns);


void main(){
	vector <Turn*> inputDraw;
	double* probArray;
	ifstream fin;
	fin.open("input.txt");
	ofstream fout;
	fout.open("output.txt");
	bool eof = false;
	
	while (eof == false)
	{
		probArray = new double[10000];
		eof = input(fin, inputDraw);
		probAll(probArray, inputDraw);
		saveToFile(fout, probArray, inputDraw);
		delete[]probArray;
		free(inputDraw);
		inputDraw.clear();
	}

	fin.close();
	fout.close();
}

double probAtOnce(int card)
{
	return (card==-1)?1:(DECK[card - 1]*1.0 / ORISPACE);
}

void restoreDECK(Turn* turn){
	int card;
	for (int i = 0; i < 6; i++)
	{
		card = turn->draws[i];
		if (card != -1)
		{
			DECK[card - 1]++;
		}
	}
	ORISPACE = 416;
}

bool input(ifstream& fin,vector<Turn*> &inputDraw )
{
	if (!fin) return true;
	int j = 0;
	int k;
	Turn* newTurn=nullptr;
	while (!fin.eof())
	{
		newTurn = new Turn;
		for (int i = 0; i < 7; i++ )
		{
			fin >> k;
			newTurn->draws[i] = k;
		}
		inputDraw.push_back(newTurn);
		cout << "Turn " << j + 1 << endl;
		if (j == 9999) return false;
		j++;
	}
	return true;
}

void probAll(double* probArray, vector <Turn*> &turns){
	double prob;
	int card;
	for (int i = 0; i < turns.size(); i++)
	{
		prob = 1;
		for (int j = 0; j < 6; j++)
		{
			card = turns[i]->draws[j];
			prob *= probAtOnce(card);
			if (card != -1)
			{
				ORISPACE = ORISPACE-1;
				DECK[card-1]--;
			}
		}
		probArray[i] = prob;
		restoreDECK(turns[i]);
	}
}

void saveToFile(ofstream &fout, double* probArray, vector<Turn*> turns)
{
	for (int i = 0; i < turns.size(); i++)
	{
		for (int j = 0; j < 7; j++)
		{
			fout << turns[i]->draws[j]	<< "\t";
		}
		fout << probArray[i] << endl;
	}
}

void free(vector<Turn*> &turns){
	for (int i = turns.size() - 1; i >= 0; i--)
	{
		delete[]turns[i];
	}
}