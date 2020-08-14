#include "Figure.h"

Figure::Figure(const Field &field)
{
	int number = rand();
	if (number % 4 == 0)
	{
		// The array of cells related to the figure is filled with pointers to the cells of the field in the form of a square
		cell[0] = field.cell[0][0];
		cell[0]->isEmpty = false;
		cell[1] = field.cell[1][0];
		cell[1]->isEmpty = false;
		cell[2] = field.cell[0][1];
		cell[2]->isEmpty = false;
		cell[3] = field.cell[1][1];
		cell[3]->isEmpty = false;
	}
	else if (number % 4 == 1)
	{
		// The array of cells related to the figure is filled with pointers to the cells of the field in the form of a ltter ã
		cell[0] = field.cell[0][0];
		cell[0]->isEmpty = false;
		cell[1] = field.cell[1][0];
		cell[1]->isEmpty = false;
		cell[2] = field.cell[0][1];
		cell[2]->isEmpty = false;
		cell[3] = field.cell[0][2];
		cell[3]->isEmpty = false;
	}
	else if (number % 4 == 2)
	{
		// The array of cells related to the figure is filled with pointers to the cells of the field in the form of a stiñk
		cell[0] = field.cell[0][0];
		cell[0]->isEmpty = false;
		cell[1] = field.cell[1][0];
		cell[1]->isEmpty = false;
		cell[2] = field.cell[2][0];
		cell[2]->isEmpty = false;
		cell[3] = field.cell[3][0];
		cell[3]->isEmpty = false;
	}
	else if (number % 4 == 3)
	{
		// The array of cells related to the figure is filled with pointers to the cells of the field in the form of a mirrored ltter ã
		cell[0] = field.cell[0][0];
		cell[0]->isEmpty = false;
		cell[1] = field.cell[1][0];
		cell[1]->isEmpty = false;
		cell[2] = field.cell[1][1];
		cell[2]->isEmpty = false;
		cell[3] = field.cell[1][2];
		cell[3]->isEmpty = false;
	}

}
void Figure::rotate(const Field &field)
{
	bool end = false;
	for (int i = 0; i < number_cell; i++)
	{
		// Check if cell is still inside the field and is not on the other figure
		bool is_part = false;
		if ((cell[0]->x - (cell[0]->y - cell[i]->y) > NUMBER - 1) || (cell[0]->x - (cell[0]->y - cell[i]->y) < 0) || (cell[0]->y + (cell[0]->x - cell[i]->x) > NUMBER - 1) || (cell[0]->y + (cell[0]->x - cell[i]->x) < 0))
		{
			end = true;

		}
		else
		{
			for (int j = 0; j < number_cell; j++)
			{
				if (field.cell[cell[0]->x - (cell[0]->y - cell[i]->y)][cell[0]->y + (cell[0]->x - cell[i]->x)] == cell[j])
				{
					is_part = true;
				}
			}
			if ((!field.cell[cell[0]->x - (cell[0]->y - cell[i]->y)][cell[0]->y + (cell[0]->x - cell[i]->x)]->isEmpty) && (!is_part))
			{
				end = true;
			}
		}
	}
	if (!end)
	{
		// Changes cells for the new ones and clear old cells
		Cell *new_cells[N];
		for (int i = 0; i < number_cell; i++)
		{
			new_cells[i] = field.cell[cell[0]->x - (cell[0]->y - cell[i]->y)][cell[0]->y + (cell[0]->x - cell[i]->x)];
			cell[i]->isEmpty = true;
		}
		for (int i = 0; i < number_cell; i++)
		{
			cell[i] = new_cells[i];
			cell[i]->isEmpty = false;
		}
	}
}
void Figure::move_down(const Field &field)
{
	// Check if cell is still inside the field and is not on the other figure
	bool end = false;
	for (int i = 0; i < number_cell; i++)
	{
		bool is_part_y = false;
		for (int j = 0; j < number_cell; j++)
		{
			if (field.cell[this->cell[i]->x][this->cell[i]->y + 1] == cell[j])
			{
				is_part_y = true;
			}
		}
		if (((cell[i]->y == NUMBER - 1)) || ((!field.cell[this->cell[i]->x][this->cell[i]->y + 1]->isEmpty) && (!is_part_y)))
		{
			end = true;
		}
	}
	if (!end)
	{
		// // Changes cells for the new ones and clear old cells
		Cell *new_cells[N];
		for (int i = 0; i < number_cell; i++)
		{
			new_cells[i] = field.cell[this->cell[i]->x][this->cell[i]->y + 1];
			cell[i]->isEmpty = true;
		}
		for (int i = 0; i < number_cell; i++)
		{
			cell[i] = new_cells[i];
			cell[i]->isEmpty = false;
		}
	}
}
void Figure::move_right(const Field &field)
{
	// Check if cell is still inside the field and is not on the other figure
	bool end = false;
	for (int i = 0; i < number_cell; i++)
	{
		bool is_part_x = false;
		bool is_part_y = false;
		for (int j = 0; j < number_cell; j++)
		{
			if ((this->cell[i]->x != NUMBER - 1) && (field.cell[this->cell[i]->x + 1][this->cell[i]->y] == cell[j]))
			{
				is_part_x = true;
			}
		}
		for (int j = 0; j < number_cell; j++)
		{
			if (field.cell[this->cell[i]->x][this->cell[i]->y + 1] == cell[j])
			{
				is_part_y = true;
			}
		}
		if ((cell[i]->x == NUMBER - 1) || ((cell[i]->y == NUMBER - 1)) || ((!field.cell[this->cell[i]->x + 1][this->cell[i]->y]->isEmpty) && (!is_part_x)) || ((!field.cell[this->cell[i]->x][this->cell[i]->y + 1]->isEmpty) && (!is_part_y)))
		{
			end = true;
		}
	}
	if (!end)
	{
		// Changes cells for the new ones and clear old cells
		Cell *new_cells[N];
		for (int i = 0; i < number_cell; i++)
		{
			new_cells[i] = field.cell[this->cell[i]->x + 1][this->cell[i]->y];
			cell[i]->isEmpty = true;
		}
		for (int i = 0; i < number_cell; i++)
		{
			cell[i] = new_cells[i];
			cell[i]->isEmpty = false;
		}
	}
}
void Figure::move_left(const Field &field)
{
	// Check if cell is still inside the field and is not on the other figure
	bool end = false;
	for (int i = 0; i < number_cell; i++)
	{
		bool is_part_x = false;
		bool is_part_y = false;
		for (int j = 0; j < number_cell; j++)
		{
			if ((this->cell[i]->x != 0) && (field.cell[this->cell[i]->x - 1][this->cell[i]->y] == cell[j]))
			{
				is_part_x = true;
			}
		}
		for (int j = 0; j < number_cell; j++)
		{
			if (field.cell[this->cell[i]->x][this->cell[i]->y + 1] == cell[j])
			{
				is_part_y = true;
			}
		}
		if ((cell[i]->x == 0) || ((cell[i]->y == NUMBER - 1)) || ((!field.cell[this->cell[i]->x - 1][this->cell[i]->y]->isEmpty) && (!is_part_x)) || ((!field.cell[this->cell[i]->x][this->cell[i]->y + 1]->isEmpty) && (!is_part_y)))
		{
			end = true;
		}
	}
	if (!end)
	{
		// Changes cells for the new ones and clear old cells
		Cell *new_cells[N];
		for (int i = 0; i < number_cell; i++)
		{
			new_cells[i] = field.cell[this->cell[i]->x - 1][this->cell[i]->y];
			cell[i]->isEmpty = true;
		}
		for (int i = 0; i < number_cell; i++)
		{
			cell[i] = new_cells[i];
			cell[i]->isEmpty = false;
		}
	}
}