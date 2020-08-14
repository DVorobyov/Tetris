#include "Cell.h"

Cell::Cell(int x, int y)
{
	this->x = x;
	this->y = y;
	this->cx = x * CELL_SIZE;
	this->cy = y * CELL_SIZE;
	this->isEmpty = true;
	this->isBlocked = false;
}