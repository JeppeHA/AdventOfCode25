// AdventOfCodeProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int dial[100];
vector<int> instructions;
int zeroCount = 0;

void initializeDial()
{
    for (int i = 0; i < 100; ++i)
    {
        dial[i] = i;
    }
}

int ConvertToInt(string str) {
    int flip = 1;
    if(str[0] == 'L')
		flip = -1;

	int length = str.length() - 1;
    return stoi(str.substr(1,length)) * flip;
}

void ReadFile() {
    string text;
	ifstream file("PuzzleInput.txt");
    while(getline(file, text)) {
		instructions.push_back(ConvertToInt(text));
	}
}

void TurnDial() {
    int startPos = 50;
    int dialLength = 100;
	int position = startPos;
	int pastDialLength = 0;
    for (int i = 0; i < instructions.size(); i++) {

		position = (((position + instructions[i]) % dialLength) + dialLength) % dialLength;
      
        /*
		position += instructions[i];

        if (position > dialLength) {
            pastDialLength = position - dialLength - 1;
            position = pastDialLength;
        }
        else if(position < 0) {
            pastDialLength = dialLength - abs(position) + 1;
			position = pastDialLength;
        }
        */
		cout << "Current Position: " << position << " rotated by " << instructions[i] << endl;

        if (position == 0) {
			zeroCount++;
        }
    }
}




int main()
{
    initializeDial();
	ReadFile();
	TurnDial();
	cout << "Zero count: " << zeroCount << endl;
	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
