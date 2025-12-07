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



static inline string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
}

void ReadDay2File() {
    string text;
    ifstream file("Ids.txt");
    char del = ',';
    while (getline(file, text, del)) {
        Ids.push_back(trim(text));
    }
}


bool isDoubleString(long long n) {
    string s = to_string(n);
    int len = s.size();
    if (len % 2 != 0) return false;

    int half = len / 2;
    return s.substr(0, half) == s.substr(half, half);
}





int main()
{
    ReadDay2File();

    long long totalSum = 0;

    for (auto& range : Ids) {
        if (range.empty()) continue;

        auto dashPos = range.find('-');
        if (dashPos == string::npos) continue;

        long long L = stoll(range.substr(0, dashPos));
        long long R = stoll(range.substr(dashPos + 1));

        for (long long x = L; x <= R; ++x) {
            if (isDoubleString(x)) {
                totalSum += x;
            }
        }
    }

    cout << totalSum << "\n";
    return 0;
}
