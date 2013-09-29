#include <iostream>
#include <fstream>
#include "cell.h"

// Constructors and Destructors
Cell::Cell() :
	_cellValue(0), _gridCount(9)
{
	Initialize();
}

Cell::Cell(int cellValue) :
	_cellValue(cellValue), _gridCount(0)
{
	Initialize();
}

Cell::~Cell()
{
}

void Cell::Load(std::ifstream& in)
// loads a cell value into a cell object
{
	in >> _cellValue;
}

void Cell::Load(int cellValue)
{
	_cellValue = cellValue;
}

int* Cell::GetGrid()
// returns the whole cell Grid
{
	return _cellGrid;
}
	
void Cell::PrintGrid() const
// prints the grid
{
	int j = 0;
	for(int i = 1; i < 4; i++)
	{
		for(j; j < 3*i; j++)
		{
			std::cout << GetGridValue(j) << " ";	
		}
		std::cout << std::endl;
	}
}

int Cell::GetGridValue(int pos) const
// gets the grid value at a given position 
{
	return _cellGrid[pos];
}

int Cell::GetCellValue() const
// gets the cell value of the Cell, 0 if not assigned
{
	return _cellValue;
}

int Cell::GetAmountOfGrid() const
// gets how many grid values are left in the cell
{
	return _gridCount;
}

void Cell::SetGridValue(int pos, int value)
// sets a grid value at a certain position
{
	_cellGrid[pos] = value;
}

void Cell::SetCellValue(int value)
// sets the cell value of the cell and sets the grid count to 0
// also clears out all of the grid values
{
	_cellValue = value;
	ClearGrid();
}

void Cell::Delete(int pos)
// deletes a certain grid value
{
	SetGridValue(pos);	
}

void Cell::Delete(const Cell& cell) 
// deletes all of the grid values from a cell given another cell
{
	for(int i = 0; i < 9; i++)
	{
		if(cell.GetGridValue(i))
		{
			Delete(i);
			_gridCount--;
		}
	}
}

void Cell::ClearGrid()
// deletes all of the grid values from a cell and sets the grid count to 0
{
	for(int i = 0; i < 9; i++)
		Delete(i);
	_gridCount = 0;
}

bool Cell::IsFinishedGrid() const
// checks to see if grid has a cell value or is ready to set a cell value
{
	return GetAmountOfGrid() == 1 || GetAmountOfGrid() == 0;

}

bool Cell::IsPrinted() const
// checks to see if cell has a cell value
{
	return _cellValue;
}

bool Cell::IsCompleted() const
// checks to see if cell is finished, ie has a cell value or finished grid
{
	return GetCellValue() || IsFinishedGrid();
}

bool Cell::HasGridValue(int num) const
// checks to see if a cell has a given grid value
{
	for(int i = 0; i < 9; i++)
		if(GetGridValue(i) == num)
			return true;
	return false;
}

void Cell::CompleteCell()
// if the cell is finished, fills in the corresponding cell value
{
	if(IsFinishedGrid())
	{
		for(int i = 0; i < 9; i++)
		{
			if(GetGridValue(i))
				SetCellValue(i+1);
		}
	}
}

void Cell::Initialize()
// initializes the grid values 1-9, or clears the grid if there is a cell value
{
	_gridCount = 9;
	for(int i = 0; i < 9; i++)
		SetGridValue(i,i+1);
	if(GetCellValue())
	{
		ClearGrid();
	}
}

bool operator==(const Cell& a, const Cell& b)
{
	for(int i = 0; i < 9; i++)	
	{
		if(a._cellGrid[i] != b._cellGrid[i])
			return false;
	}
	return true;
}

std::ostream& operator<<(std::ostream& s, const Cell& cell)
{	
	int j = 0;
	for(int i = 1; i < 4; i++)
	{
		for(j; j < 3*i; j++)
		{
			s << cell.GetGridValue(j) << " ";	
		}
		s << std::endl;
	}
	return s;

}



