#include "stdafx.h"
#include <fstream> 
#include <iostream> 
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <fstream>
#include <time.h>
using namespace std;

vector<string> cardTop = { "yellow_t", "red_b", "red_b", "green_t", "red_t", "green_t", "blue_t", "red_t", "yellow_b" };
vector<string> cardRight = { "blue_b", "yellow_b", "blue_t", "blue_b", "blue_t", "red_t", "yellow_t", "blue_b", "blue_b" };
vector<string> cardBottom = { "green_b", "green_t", "green_b", "red_t", "green_b", "blue_t", "yellow_b", "green_b", "green_b" };
vector<string> cardLeft = { "red_b", "blue_t", "yellow_t", "yellow_t", "yellow_t", "blue_b", "green_b", "yellow_t", "red_b" };

const int lengthOfSide = 3;
const int numberOfSides = 4;
vector<string> allCards;
bool used[lengthOfSide*lengthOfSide] = { false };
vector<string> allCardsHome;
int grid[lengthOfSide][lengthOfSide];
string nameOfCards[lengthOfSide*lengthOfSide][5];

vector<string> string_split(string s, const char delimiter)
{
	size_t start = 0;
	size_t end = s.find_first_of(delimiter);
	vector<string> output;

	while (end <= string::npos)
	{
		output.emplace_back(s.substr(start, end - start));

		if (end == string::npos)
			break;

		start = end + 1;
		end = s.find_first_of(delimiter, start);
	}
	return output;
}
bool matches(string side1, string side2){
	vector<string> side1split = string_split(side1, '_');
	vector<string> side2split = string_split(side2, '_');
	if (side1split[0] == side2split[0] && side1split[1] != side2split[1]){
		return true;
	}
	else{
		return false;
	}
}
void toggleUsed(int cardID){
	if (used[cardID] == false)
	{
		used[cardID] = true;
	}
	else {
		used[cardID] = false;
	}
}
bool isUsed(int cardID){
	bool output = used[cardID];
	return output;
}
bool isHome(int cardID){
	if (allCardsHome[cardID * numberOfSides] == allCards[cardID * numberOfSides] && allCardsHome[(cardID * numberOfSides) + 1] == allCards[(cardID * numberOfSides) + 1] && allCardsHome[(cardID * numberOfSides) + 2] == allCards[(cardID * numberOfSides) + 2] && allCardsHome[(cardID * numberOfSides) + 3] == allCards[(cardID * numberOfSides) + 3])
	{
		return true;
	}
	else{
		return false;
	}
}
string getTop(int cardID){
	return allCards[(cardID*(numberOfSides))];
}
string getRight(int cardID){
	return allCards[(cardID*(numberOfSides)) + 1];
}
string getBottom(int cardID){
	return allCards[(cardID*(numberOfSides)) + 2];
}
string getLeft(int cardID){
	return allCards[(cardID*(numberOfSides)) + 3];
}

void rotate(int cardID){
		string top = allCards[((cardID)* numberOfSides)];
		string right = allCards[((cardID)* numberOfSides) + 1];
		string bottom = allCards[((cardID)* numberOfSides) + 2];
		string left = allCards[((cardID)* numberOfSides) + 3];
		string temp = top;
		top = left;
		left = bottom;
		bottom = right;
		right = temp;
		allCards[((cardID)* numberOfSides)] = top;
		allCards[((cardID)* numberOfSides) + 1] = right;
		allCards[((cardID)* numberOfSides) + 2] = bottom;
		allCards[((cardID)* numberOfSides) + 3] = left;
}
void print(vector<string> print){
for (size_t i = 0; i < print.size(); i++){
cout << print[i] << endl;
}
}
bool placeCard(int x, int y){
	int pos = (lengthOfSide * y) + x;
	for (unsigned i = 0; i < (lengthOfSide*lengthOfSide); ++i){

		if (!isUsed(i)){
			grid[x][y] = i;
			toggleUsed(i);
		}
		else {
			continue;
		}
		do{
			int nextx = x;
			int nexty = y;
			bool match1 = true;
			bool match2 = true;
			nameOfCards[pos][0] = to_string(i + 1);
			nameOfCards[pos][1] = getTop(i);
			nameOfCards[pos][2] = getRight(i);
			nameOfCards[pos][3] = getBottom(i);
			nameOfCards[pos][4] = getLeft(i);

			if (y > 0)
				match1 = matches(getTop(i), getBottom(grid[x][y - 1]));

			if (x > 0)
				match2 = matches(getLeft(i), getRight(grid[x - 1][y]));

			if (match1 && match2) {
				nextx++;
				if (nextx == lengthOfSide) {
					nexty++;
					if (nexty == lengthOfSide){
						return true;
					}
					else{
						nextx = 0;
					}
				}
				bool next = placeCard(nextx, nexty);
				if (next == true){
					return true;
				}
			}
			rotate(i);
		} while (!isHome(i));
		toggleUsed(i);
	}
	return false;
}

int main()
{
	clock_t t1, t2;
	t1 = clock(); // starts clock
	 
	for (unsigned y = 0; y < lengthOfSide*lengthOfSide; ++y){
		used[y] = false;
	}
	for (unsigned z = 0; z < lengthOfSide*lengthOfSide; ++z){
		allCards.push_back(cardTop[z]);
		allCards.push_back(cardRight[z]);
		allCards.push_back(cardBottom[z]);
		allCards.push_back(cardLeft[z]);
		}
	allCardsHome = allCards;
	bool success = placeCard(0, 0);
	if (!success){
		cout << "ERROR!!!" << endl;
		cin.get();
		return 0;
	}
	else{
		t2 = clock();
		float diff((float)t2 - (float)t1);

		for (unsigned a = 0; a < lengthOfSide*lengthOfSide; ++a){

			cout << nameOfCards[a][0] << "  ";
			cout << "::  ";
			cout << nameOfCards[a][1] << "  ";
			cout << nameOfCards[a][2] << "  ";
			cout << nameOfCards[a][3] << "  ";
			cout << nameOfCards[a][4] << "  ";
			cout << endl;
		}
		cout << "Success" << endl;
		cout << "It Reads from Top, Right, Bottom, Left." << endl;

		float seconds = diff / CLOCKS_PER_SEC;
		cout << "This program only took " << seconds << " Seconds to finish running" << endl;
		cout << "Press Enter to Continue" << endl;
		cin.ignore();
		return 0;

	}
	system("pause");
	return 0;

}