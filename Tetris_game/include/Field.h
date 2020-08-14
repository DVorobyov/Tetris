#pragma once
#include "Cell.h"
#define NUMBER 20

class Field
{
public:
	Cell ***cell;
	Field();
	void delete_cells(int &score);
};