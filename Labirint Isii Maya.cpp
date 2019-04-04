// ConsoleApplication20.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <ctime>
#include <iostream> 
#include <cstdlib> 
#include <cmath> 
#include <vector> 
#include <stack> 
#include <conio.h> 
#define matrixSize 30 

using namespace std;

char nullchar = 'X';

char getChar(bool top, bool bottom, bool right, bool left) {
	if (top && !right && bottom && !left) return char(179);
	if (top && !right && bottom && left) return char(180);
	if (!top && !right && bottom && left) return char(191);
	if (top && right && !bottom && !left) return char(192);
	if (top && right && !bottom && left) return char(193);
	if (!top && right && bottom && left) return char(194);
	if (top && right && bottom && !left) return char(195);
	if (!top && right && !bottom && left) return char(196);
	if (top && right && bottom && left) return char(197);
	if (top && !right && !bottom && left) return char(217);
	if (!top && right && bottom && !left) return char(218);
	if (!top && right && !bottom && !left) return char(452);
	if (!top && !right && !bottom && left) return char(452);
	if (top && !right && !bottom && !left) return char(179);
	if (!top && !right && bottom && !left) return char(179);
	return nullchar;
}
char getCharAl(char c) {
	if (c == char(179)) { return char(186); }
	if (c == char(180)) { return char(185); }
	if (c == char(191)) { return char(187); }
	if (c == char(192)) { return char(200); }
	if (c == char(193)) { return char(202); }
	if (c == char(194)) { return char(203); }
	if (c == char(195)) { return char(204); }
	if (c == char(196)) { return char(205); }
	if (c == char(197)) { return char(206); }
	if (c == char(217)) { return char(188); }
	if (c == char(218)) { return char(201); }
	if (c == char(452)) { return char(205); }
	return c;
}

class Cell {
	static int count;
public:
	int x, y;
	char c = nullchar;
	bool top = false;
	bool bottom = false;
	bool right = false;
	bool left = false;
	Cell() {
		this->x = count % matrixSize;
		this->y = count / matrixSize;
		count++;
	}
};

int Cell::count = 0;
Cell matrix[matrixSize][matrixSize];
Cell* findNext(Cell* current) {
	vector <Cell*> nexts;
	vector <bool*> connectionsCurrent;
	vector <bool*> connectionsNext;
	int x = current->x;
	int y = current->y;
	if (y - 1 >= 0) {
		if ((matrix[y - 1][x]).c == nullchar) {
			nexts.push_back(&(matrix[y - 1][x]));
			connectionsCurrent.push_back(&(current->top));
			connectionsNext.push_back(&((matrix[y - 1][x]).bottom));
		}
	}
	if (y + 1 < matrixSize) {
		if ((matrix[y + 1][x]).c == nullchar) {
			nexts.push_back(&(matrix[y + 1][x]));
			connectionsCurrent.push_back(&(current->bottom));
			connectionsNext.push_back(&((matrix[y + 1][x]).top));
		}
	}
	if (x - 1 >= 0) {
		if ((matrix[y][x - 1]).c == nullchar) {
			nexts.push_back(&(matrix[y][x - 1]));
			connectionsCurrent.push_back(&(current->left));
			connectionsNext.push_back(&((matrix[y][x - 1]).right));
		}
	}
	if (x + 1 < matrixSize) {
		if ((matrix[y][x + 1]).c == nullchar) {
			nexts.push_back(&(matrix[y][x + 1]));
			connectionsCurrent.push_back(&(current->right));
			connectionsNext.push_back(&((matrix[y][x + 1]).left));
		}
	}
	int n = nexts.size();
	if (n == 0) {
		return current;
	}
	int r = rand() % n;
	Cell*next = nexts.at(r);
	bool*connection = (connectionsCurrent.at(r));
	*connection = true;
	*(connectionsNext.at(r)) = true;
	current->c = getChar(current->top, current->bottom, current->right, current->left);
	return next;
}


int main()
{
	stack <Cell*> backtacker;
	stack <Cell*> ai_backtacker;
	srand(time(0));
	int x = 0;
	int y = 0;
	cout << "Labirinth\n\n";
	Cell* current = &(matrix[y][x]);
	Cell* next = current;
	Cell* copy;
	bool solved = false;
	do {
		do {
			copy = current;
			next = findNext(current);
			current = next;
			if (next == copy) {
				break;
			}
			backtracker.push(copy);
			if (!solved) {
				ai_backtacker.push(copy);
				if (next->x == matrixSize - 1 && next->y == matrixSize - 1) {
					solved = true;
				}
			}
		} while (next != copy);
		backtracker.pop();
		if (!solved) {

			ai_backtracker.pop();
		}
		if (backtracker.size() > 0) {
			current = backtracker.top();
		}
		next->c = getChar(next->top, next->right, next->bottom, next->left);
	} while (backtracker.Size != 0);
	for (int a = 0; a < matrixSize; a++) {
		for (int b = 0; b < matrixSize; b++) {
			cout << (matrix[a][b]).c;
		}
		cout << endl;
	}
	cout << "\n\nSolution\n\nstart(0,0)\nend(" << matrixSize - 1 << "," << matrixSize - 1 << ")\n\nFollow the double lines\n\n";

	while (ai_backtracker.size() != 0) {
		Cell*cl = ai_backtracker.top();
		cl->c = getCharAl((cl->c));
		ai_backtracker.pop();
	}
	(matrix[matrixSize - 1][matrixSize - 1]).c = getCharAl((matrix[matrixSize - 1][matrixSize - 1]).c);
	for (int a = 0; a < matrixSize; a++) {
		for (int b = 0; b < matrixSize; b++) {
			cout << (matrix[a][b]).c;
		}
		cout << endl;
	}


	_getch();
	return 0;
}

