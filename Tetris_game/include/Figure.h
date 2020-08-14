#pragma once
#include <cstdlib>
#include "Cell.h"
#include "Field.h"
#include <ctime>
#define N 4

class Figure
{
public:
	int number_cell = N;
	Cell *cell[N];
	Figure(const Field &field);
	void move_right(const Field &field);
	void move_left(const Field &field);
	void move_down(const Field &field);
	void rotate(const Field &field);
	
};