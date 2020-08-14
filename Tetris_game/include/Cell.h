#pragma once
#define CELL_SIZE 30

class Cell
{
public:
	int x;
	int y;
	int cx;
	int cy;
	bool isEmpty;
	bool isBlocked;
	Cell() {};
	Cell(int x, int y);
};
