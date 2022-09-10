#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<time.h>
#include<string>

using namespace std;

#define MAX_ROW_SIZE 100
#define MAX_COLUMN_SIZE 100

void initializeMaze(int maze[MAX_ROW_SIZE][MAX_COLUMN_SIZE], int rowSize, int columnSize);
void printeMaze(int maze[MAX_ROW_SIZE][MAX_COLUMN_SIZE], int rowSize, int columnSize);
void generateGamePoint(int maze[MAX_ROW_SIZE][MAX_COLUMN_SIZE], int rowSize, int columnSize);
void fillMaze(int maze[MAX_ROW_SIZE][MAX_COLUMN_SIZE], int rowSize, int columnSize);
void play(int maze[MAX_ROW_SIZE][MAX_COLUMN_SIZE], int rowSize, int columnSize);
bool checkMove(int maze[MAX_ROW_SIZE][MAX_COLUMN_SIZE], int rowSize, int columnSize, int x, int y);
bool sign(int maze[MAX_ROW_SIZE][MAX_COLUMN_SIZE], int x, int y);
void printInfo();

int main() {
	bool isLegal = false;
	int count = 0;
	int maze[MAX_ROW_SIZE][MAX_COLUMN_SIZE];
	srand(time(NULL));
	int rowSize, columnSize;


	cout << "Enter row size : ";
	cin >> rowSize;
	cout << "Enter col size : ";
	cin >> columnSize;
	cout << endl;

	if (rowSize < 10 || columnSize < 10 || rowSize>100 || columnSize>100)
	{
		cout << "ERROR !! Enter greater than 10 and less than 100 " << endl;
	}
	else
	{
		printInfo();
		initializeMaze(maze, rowSize, columnSize);
		play(maze, rowSize, columnSize);
	}
	cout << endl << endl;
	system("pasue");
	return 0;
}

void initializeMaze(int maze[MAX_ROW_SIZE][MAX_COLUMN_SIZE], int rowSize, int columnSize) {
	for (int i = 0; i < rowSize; i++)
		for (int j = 0; j < columnSize; j++)
			maze[i][j] = 5;

	generateGamePoint(maze, rowSize, columnSize);
}

void generateGamePoint(int maze[MAX_ROW_SIZE][MAX_COLUMN_SIZE], int rowSize, int columnSize) {

	int i = 0;
	int j = 0;
	maze[i][j] = 0;
	while (i < rowSize - 1) {
		int value = rand() % 3;


		int legalPoint = rand() % 2;

		if (value == 0 && j > 0) {
			maze[i][j - 1] = legalPoint;
			j--;
		}
		else if (value == 1 && j < columnSize - 1) {
			maze[i][j + 1] = legalPoint;
			j++;
		}
		else if (value == 2) {
			maze[i + 1][j] = legalPoint;
			i++;
		}
	}

	fillMaze(maze, rowSize, columnSize);
}

void fillMaze(int maze[MAX_ROW_SIZE][MAX_COLUMN_SIZE], int rowSize, int columnSize) {

	int upper = 3, lower = 0;

	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < columnSize; j++) {
			if (maze[i][j] == 5)
			{
				maze[i][j] = rand() % (upper - lower + 1) + lower;
			}
		}
	}
}

void printeMaze(int maze[MAX_ROW_SIZE][MAX_COLUMN_SIZE], int rowSize, int columnSize) {
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < columnSize; j++) {
			if (maze[i][j] == 0) {
				cout << "_  ";
			}
			else if (maze[i][j] == 1) {
				cout << "0  ";
			}
			else if (maze[i][j] == 2) {
				cout << "|  ";
			}
			else if (maze[i][j] == 3) {
				cout << "$  ";
			}
			else if (maze[i][j] == 6) {
				cout << "*  ";
			}
		}
		cout << endl << endl;
	}

}

void play(int maze[MAX_ROW_SIZE][MAX_COLUMN_SIZE], int rowSize, int columnSize) {

	int x = 0; int y = 0;
	int x_new = 0; int y_new = 0;
	int goldCount = 0;
	char enter;
	ofstream outFile;

	outFile.open("results.txt");

	outFile << "X" << "\t" << "Y" << endl;
	outFile << x << "\t" << y << endl;

	while (true) {

		x_new = x;
		y_new = y;

		printeMaze(maze, rowSize, columnSize);

		cout << endl << "Please move :";
		cin >> enter;

		if (enter == 119) {						//W
			x_new--;
		}
		else if (enter == 97) {					//A
			y_new--;
		}
		else if (enter == 100) {				//D
			y_new++;
		}
		else if (enter == 115) {				//S
			x_new++;
		}
		else {
			cout << "YOU ENTERED AN UNDEFINED LETTER !!! PLEASE RE-ENTER LETTER" << endl;
			continue;
		}

		if (maze[x_new][y_new] == 3) {
			cout << endl << "Oopss!!! You have reached monster. Please try again!!" << endl;
			break;
		}

		if (checkMove(maze, rowSize, columnSize, x_new, y_new)) {
			goldCount += sign(maze, x, y);
			maze[x][y] = 6;

			x = x_new;
			y = y_new;

			goldCount += sign(maze, x, y);

			outFile << x << "\t" << y << endl;
		}

		if (x == rowSize - 1) {
			goldCount += sign(maze, x, y);
			printeMaze(maze, rowSize, columnSize);
			cout << endl << "--------------------------------------------------------------------" << endl;
			cout << endl << "---------------Congratulations!! You won the game:))----------------" << endl;
			cout << endl << "--------------------------------------------------------------------" << endl;
			cout << endl << "You collected " << goldCount << " gold. ";
			cout << endl;
			break;
		}
	}
	outFile.close();
}

bool checkMove(int maze[MAX_ROW_SIZE][MAX_COLUMN_SIZE], int rowSize, int columnSize, int x, int y) {
	if (x >= 0 && x < rowSize  && y >= 0 && y < columnSize && maze[x][y] != 2 && maze[x][y] != 3) {
		return true;
	}
	cout << "You cannot move there!! Please click new move. " << endl;
	return false;
}

bool sign(int maze[MAX_ROW_SIZE][MAX_COLUMN_SIZE], int x, int y) {
	bool isGold = false;

	if (maze[x][y] == 1) {
		isGold = true;
	}

	maze[x][y] = 6;

	return isGold;
}

void printInfo() {
	cout << "If you want to move up, click w  " << endl;
	cout << "If you want to move left, click a  " << endl;
	cout << "If you want to move right, click d  " << endl;
	cout << "If you want to move down, click s  " << endl << endl;
	cout << "'_' is road  " << endl;
	cout << "'0' is gold  " << endl;
	cout << "'|' is wall  " << endl;
	cout << "'$' is monster  " << endl << endl;
	cout << "The game starts at point 0,0" << endl << endl;

}

