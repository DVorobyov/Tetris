#include "Field.h"

Field::Field()
{
	this->cell = new Cell**[NUMBER]();
	for (int i = 0; i < NUMBER; i++)
	{
		this->cell[i] = new Cell*[NUMBER]();
	}
	for (int i = 0; i < NUMBER; i++)
	{
		for (int j = 0; j < NUMBER; j++)
		{
			Cell *new_cell = new Cell(i, j);
			this->cell[i][j] = new_cell;
			new_cell = nullptr;
		}
	}
}
void Field::delete_cells(int &score)
{
	for (int i = 0; i < NUMBER; i++)
	{
		int full = 0;
		// Count filled cells in line
		for (int j = 0; j < NUMBER; j++)
		{
			if ((!cell[j][i]->isEmpty) && (cell[j][i]->isBlocked))
			{
				full++;
			}
		}
		// Delete line if line is full, add score
		if (full == NUMBER)
		{
			for (int j = 0; j < NUMBER; j++)
			{
				cell[j][i]->isEmpty = true;
				cell[j][i]->isBlocked = false;
			}
			score += 5;
			// Move other cells down
			for (int t = i; t > 3; t--)
			{
				for (int j = 0; j < NUMBER; j++)
				{
					cell[j][t]->isEmpty = cell[j][t - 1]->isEmpty;
					cell[j][t]->isBlocked = cell[j][t - 1]->isBlocked;
					cell[j][t - 1]->isEmpty = true;
					cell[t][t - 1]->isBlocked = true;
				}
			}
		}
	}
}