// AdventOfCodeProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <sstream>


using namespace std;


vector<string> Ids;
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

void ReadDay2File() {
    string text;
    ifstream file("Ids.txt");
    char del = ',';
    while (getline(file, text, del)) {
        Ids.push_back(text);
    }

    for (int i = 0; i < Ids.size(); i++)
    {
       // cout << Ids[i] << endl;
    }
}

bool CheckIfInvalid(int num) {
    unordered_set<char> seen;
    string s = to_string(num);

    for (char c : s) {
        if (seen.count(c)) {
            return false;   
        }
        seen.insert(c);
    }
    return true;  
}


void CountInvalidIds() {
    int numOfInvalids = 0;

    for (string line : Ids) {
        vector<vector<string>> idPairs;  

        stringstream ss(line);
        string segment;
        while (getline(ss, segment, ',')) {
            segment.erase(remove_if(segment.begin(), segment.end(), ::isspace), segment.end());

            int pos = segment.find('-');
            if (pos == string::npos) continue;

            string left = segment.substr(0, pos);
            string right = segment.substr(pos + 1);

            idPairs.push_back({ left, right });
        }
        
        for (auto& p : idPairs) {
            int L = stoi(p[0]);
            int R = stoi(p[1]);
            if (p[0].length() % 2 != 0 && p[1].length() % 2 != 0)
                continue;

            for (int i = L; i <= R; i++) {
                if (!CheckIfInvalid(i)) {  
                    numOfInvalids++;
                }
            }
        }
    }

    cout << "Invalid count: " << numOfInvalids << endl;
}




void TurnDial() {
    int startPos = 50;
    int dialLength = 100;
	int position = startPos;
	int pastDialLength = 0;
    for (int i = 0; i < instructions.size(); i++) {

		position = (((position + instructions[i]) % dialLength) + dialLength) % dialLength;

		cout << "Current Position: " << position << " rotated by " << instructions[i] << endl;

        if (position == 0) {
			zeroCount++;
        }
    }
}




int main()
{
    ReadDay2File();
    CountInvalidIds();
}
