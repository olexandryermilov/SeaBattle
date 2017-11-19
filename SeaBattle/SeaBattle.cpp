// SeaBattle.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <conio.h>

#define SIZE 10

using namespace std;

char playerField[SIZE][SIZE], сomputerSeenField[SIZE][SIZE], computerRealField[SIZE][SIZE],tempPlayerField[SIZE][SIZE];

void drawFields() {
	system("cls");
	for (int i = 0; i < SIZE+1; i++) {

		if (i == 0) {
			cout << "   ";
			for (int j= 0; j < SIZE; j++) {
				cout << (char)('A' + j)<< " ";
			}
			cout << "	";
			for (int j = 0; j < SIZE; j++) {
				cout << (char)('A' + j)<< " ";
			}
		}
		else {
			cout << i<<" ";
			if (i != 10)cout << " ";
			for (int j = 0; j < SIZE; j++) {
				cout << playerField[i-1][j] << ' ';
			}
			cout << "	";
			for (int j = 0; j < SIZE; j++) {
				cout << сomputerSeenField[i-1][j]<<' ';
			}
		}
		cout << "\n";
	}
}

void drawComputerRealField() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			cout << computerRealField[i][j]<<' ';
		}
		cout << "\n";
	}
}

void drawTempPlayerField() {
	for (int i = -1; i < SIZE; i++) {
			if (i == -1) {
				for (int j = 0; j < SIZE; j++) {
					cout << (char)(j + 'A')<<' ';
				}
			}
			else {
				cout << i+1 << " ";
				if (i != 9)cout << " ";
				for (int j = 0; j < SIZE; j++) {
					cout << tempPlayerField[i][j]<<' ';
				}
			}
			cout << "\n";
	}
}
void copyPlayerField(bool to) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if(to)tempPlayerField[i][j] = playerField[i][j];
			else playerField[i][j] = tempPlayerField[i][j];
		}
	}
}

bool isInside(int tx, int ty) {
	return !(tx < 0 || tx >= SIZE || ty >= SIZE || ty < 0);
}

bool isGoodPosition(int x, int y, int orientation, int size, char field[][10]) {
	for (int i = 0; i < size; i++) {
		int tx = x + i*(1 - orientation);
		int ty = y + i*orientation;
		if (!isInside(tx, ty))return false;
		if (field[tx][ty] == '*')return false;
		if (orientation==0) {
			if (isInside(tx, ty + 1) && field[tx][ty + 1] == '*') {
				return false;
			}
			if (isInside(tx, ty - 1) && field[tx][ty - 1] == '*') {
				return false;
			}
			if (i == 0) {
				if (isInside(tx-1, ty + 1) && field[tx-1][ty + 1] == '*') {
					return false;
				}
				if (isInside(tx-1, ty - 1) && field[tx-1][ty - 1] == '*') {
					return false;
				}
				if (isInside(tx - 1, ty) && field[tx - 1][ty] == '*') {
					return false;
				}
			}
			if (i == size - 1) {
				if (isInside(tx+1, ty + 1) && field[tx+1][ty + 1] == '*') {
					return false;
				}
				if (isInside(tx+1, ty - 1) && field[tx+1][ty - 1] == '*') {
					return false;
				}
				if (isInside(tx + 1, ty) && field[tx + 1][ty] == '*') {
					return false;
				}
			}
		}
		else {
			if (isInside(tx+1, ty) && field[tx+1][ty] == '*') {
				return false;
			}
			if (isInside(tx-1, ty) && field[tx-1][ty] == '*') {
				return false;
			}
			if (i == 0) {
				if (isInside(tx + 1, ty-1) && field[tx + 1][ty-1] == '*') {
					return false;
				}
				if (isInside(tx - 1, ty-1) && field[tx - 1][ty-1] == '*') {
					return false;
				}
				if (isInside(tx, ty - 1) && field[tx][ty - 1] == '*') {
					return false;
				}
			}
			if (i == size - 1) {
				if (isInside(tx + 1, ty + 1) && field[tx + 1][ty + 1] == '*') {
					return false;
				}
				if (isInside(tx - 1, ty + 1) && field[tx - 1][ty + 1] == '*') {
					return false;
				}
				if (isInside(tx, ty + 1) && field[tx][ty + 1] == '*') {
					return false;
				}
			}
		}
	
	}
	return true;
}

void enterShips() {
	for (int i = 4; i >= 1; i--) {
		for (int j = 1; j <= 4 - i + 1; j++) {
			cout << "Enter ship of size " << i<<"\n";
			int x = 0, y = 0,orientation = 0;
			copyPlayerField(true);
			for (int p = 0; p < i; p++) {
				tempPlayerField[x + p*(1 - orientation)][y + p*orientation] = '*';
			}
			drawTempPlayerField();
			while (true) {
				if (_kbhit()) {
					int keyPressed = _getch();
					switch (keyPressed) {
					case 32:orientation = (1 - orientation); if (y + i >= SIZE)y = SIZE - i; break;//space
					case 72:if(x>0)x--; break;  //up
					case 80:if (x + 1 < SIZE)x++; break; //down
					case 75:if (y > 0)y--; break; //left
					case 77:if (y + i < SIZE||orientation==0)y++; break;
					}
					if (keyPressed == 13) {
						if(!isGoodPosition(x,y,orientation,i,playerField)){
							cout << "Bad position\n";
							continue;
						}
						copyPlayerField(false);
						system("cls");
						break;
					}
					system("cls");
					cout << "Enter ship of size " << i << "\n";
					copyPlayerField(true);
					for (int p = 0; p < i; p++) {
						tempPlayerField[x + p*(1 - orientation)][y + p*orientation] = '*';
					}
					drawTempPlayerField();
				}
			}
		}
	}
}
void initFields() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			playerField[i][j] = '.';
			сomputerSeenField[i][j] = '.';
			computerRealField[i][j] = '.';
		}
	}
}
void setShip(int shipSize) {
	int orientation = rand() % 2;
	int x = rand() % SIZE;
	int y = rand() % SIZE;
	if (!isGoodPosition(x, y, orientation, shipSize, computerRealField)) {
		setShip(shipSize);
		return;
	}
	for (int i = 0; i < shipSize; i++) {
		computerRealField[x+(1-orientation)*i][y + i*orientation] = '*';
	}
}
void initComputerRealField() {
	srand(time(NULL));
	for (int i = 4; i >= 1; i--) {
		for (int j = 1; j <= 4-i+1; j++) {
			setShip(i);
		}
	}
}
int main()
{
	initFields();
	enterShips();
	drawFields();
	initComputerRealField();
	drawComputerRealField();
	system("pause");
    return 0;
}



