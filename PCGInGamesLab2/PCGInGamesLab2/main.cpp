

/*
	Genes:
	Free space
	Wall
	Starting point
	Exit
	Monster
	Treasure
*/
/*
	Fitness function???
	rooms? 
	4 walls 
	an exit

	float freeRatio = freeTiles / totalTiles;
	fitness += 1.0f - abs(freeRatio - 0.45f);

	fitness += reachableFreeTiles / totalFreeTiles;


*/

#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

int dungeon[50][50] = { 0 };
int population[5][2500] = { 0 };


// ---------------- POPULATION ----------------

void PopulateFirstGenes() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 2500; j++) {
            population[i][j] = rand() % 2; // 0 = free, 1 = wall
        }
    }
}

void PrintGenebool(int n) {
    for (int i = 0; i < 100; i++) {
        cout << population[n][i];
    }
    cout << endl;
}


// ---------------- DUNGEON ----------------

char DungeonTile(int n) {
    if (n == 0) return ' ';
    if (n == 1) return '*';
    return 'x';
}

void SetDungeon(int genes[2500]) {
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            dungeon[i][j] = genes[i * 50 + j];
        }
    }
}

void PrintDungeon() {
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            cout << DungeonTile(dungeon[i][j]);
        }
        cout << endl;
    }
}


// ---------------- BFS FLOOD FILL ----------------

bool FindStartingTile(int& sx, int& sy) {
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            if (dungeon[i][j] == 0) {
                sx = i;
                sy = j;
                return true;
            }
        }
    }
    return false;
}

int FloodFillBFS(int startX, int startY) {
    bool visited[50][50] = { false };

    int dx[4] = { 1, -1, 0, 0 };
    int dy[4] = { 0, 0, 1, -1 };

    queue<pair<int, int>> q;
    q.push({ startX, startY });
    visited[startX][startY] = true;

    int connectedCount = 1;

    while (!q.empty()) {
        
        pair<int, int> p = q.front();
        q.pop();

        int x = p.first;
        int y = p.second;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx >= 50 || ny < 0 || ny >= 50)
                continue;

            if (visited[nx][ny])
                continue;

            if (dungeon[nx][ny] != 0)
                continue;

            visited[nx][ny] = true;
            q.push({ nx, ny });
            connectedCount++;
        }
    }

    return connectedCount;
}


// ---------------- MAIN ----------------

int main() {
    srand((unsigned int)time(nullptr));

    PopulateFirstGenes();
    SetDungeon(population[0]);
    PrintDungeon();

    int startX, startY;
    if (FindStartingTile(startX, startY)) {
        int connected = FloodFillBFS(startX, startY);
        cout << "\nConnected free tiles: " << connected << endl;
    }
    else {
        cout << "\nNo free tiles found.\n";
    }

    return 0;
}