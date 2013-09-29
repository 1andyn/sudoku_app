#include <iostream>
#include <fstream>
#include <string>
#include "cell.h"
#include "solver.h"

Solver::Solver(std::string filename) :
	_filename(filename)
{
	std::ifstream file(filename.c_str());		
	if(file)
	{
		Load(file);
		InitializeAll();
	}

}

Solver::Solver()
{
	_sentPuzzle.resize(9);
	for(int i = 0; i < 9; i++)
		_sentPuzzle[i].resize(9);
}

Solver::~Solver()
{
}

void Solver::Load(std::ifstream& in)
// loads in all of the cell values into the puzzle
{
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
			_puzzle[j][i].Load(in);
}

void Solver::Load(Puzzle userPuzzle)
{
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
			_puzzle[j][i].Load(userPuzzle[i][j]);
	InitializeAll();
}

void Solver::PrintPuzzle() const
// prints the puzzle
{
	for(int i = 0; i < 9; i++)
		PrintRow(i);
}

void Solver::PrintRow(int row) const
// given a certain row, print out all the cell values in the row
{
	for(int i = 0; i < 9; i++)
	{
		std::cout << GetPuzzleCell(i, row).GetCellValue() << " ";
	}
	std::cout << std::endl;
}

std::ostream& operator<<(std::ostream& s, const Solver& solver)
{
	for(int j = 0; j < 9; j++)
	{
		for(int i = 0; i < 9; i++)
		{
			s << solver.GetPuzzleCell(i, j).GetCellValue() << " ";
		}
		s << std::endl;
	}

	return s;
}

void Solver::SolvePuzzle()
{
	for(int i = 0; i < 30; i++)
	{
		EraseAllCells();
		FillFinishedCells();	
		SolveAll();
	}
}

void Solver::ClearPuzzle()
{
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
		{
			_puzzle[j][i].SetCellValue(0);
			_sentPuzzle[j][i] = 0;
		}
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
		{
			_puzzle[j][i].Initialize();
		}
}

const Cell& Solver::GetPuzzleCell(int xPos, int yPos) const
{
	return _puzzle[xPos][yPos];
}

Puzzle Solver::GetPuzzle()
{
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
		{
			_sentPuzzle[i][j] = GetPuzzleCell(j, i).GetCellValue();
		}
	return _sentPuzzle;

}

Cell& Solver::GetPuzzleCellRef(int xPos, int yPos)
{
	return _puzzle[xPos][yPos];
}

void Solver::EraseRow(int xPos, int yPos)
// delete cell value from all cells in row
{
	// get cell value
	int cellValue = GetPuzzleCell(xPos, yPos).GetCellValue();
	// for all cells in row
	for(int i = 0; i < 9; i++)
		// delete cell value from grid
		GetPuzzleCellRef(i, yPos).Delete(cellValue-1);

}

void Solver::EraseColumn(int xPos, int yPos)
// erase cell value from all cells in column
{
	// get cell value
	int cellValue = GetPuzzleCell(xPos, yPos).GetCellValue();
	// for all cells in column
	for(int i = 0; i < 9; i++)
		// delete cell value from grid
		GetPuzzleCellRef(xPos, i).Delete(cellValue-1);
}

void Solver::EraseSquare(int xPos, int yPos)
// erase cell value from all cells in square
{

	// find which sqaure the cell is in
	int xSquare = SquareStart(xPos),
	    ySquare = SquareStart(yPos);

	if(xSquare != -1 && ySquare != -1)
	{
		// get cell value
		int cellValue = GetPuzzleCell(xPos, yPos).GetCellValue();
		// for all values in square
		for(int i = xSquare; i < xSquare+3; i++)
			for(int j = ySquare; j < ySquare+3; j++)
				// delete the cell value from grid
				GetPuzzleCellRef(i, j).Delete(cellValue-1);
	}
}

void Solver::EraseAll(int xPos, int yPos)
// erase a cell value from square, row, and column
{
	EraseSquare(xPos, yPos);
	EraseColumn(xPos, yPos);
	EraseRow(xPos, yPos);
}

void Solver::EraseAllCells()
// erase sqaure, row, and column for all cell values
{
	int count = 0;
	// for every cell in puzzle
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			// if cell is filled in
			if(GetPuzzleCell(j, i).GetCellValue())
			{
				// erase that value from column, row,
				// and sqaure
				EraseAll(j, i);
			}
		}
	}

}

void Solver::UC_Row(int row, int num)
// given: a row, and a certain value
// Finds if there is only one cell with that value in the row and fills
// in that value, deletes that value from other cells, and fills in 
// all finished cells
{
	int count = 0,
	    xPos = 0;
	// for all cells in a row
	for(int i = 0; i < 9; i++)
	{
		// if its not filled in and has a specific value
		if(!GetPuzzleCell(i, row).GetCellValue() &&
		   GetPuzzleCell(i, row).HasGridValue(num))
		{
			count++;
			xPos = i;
		}
	}

	// if only one cell has that value
	if(count == 1)
	{
		// Fill in that cells value
		GetPuzzleCellRef(xPos, row).SetCellValue(num);
		// erase that value from the square, column, and row
		EraseAll(xPos, row);
		// find any cells with only one grid value and fill them in
		FillFinishedCells();

	}
		   
}

void Solver::UC_Column(int column, int num)
// given: a column, and a certain value
// Finds if there is only one cell with that value in the column and fills
// in that value, deletes that value from other cells, and fills in 
// all finished cells
{
	int count = 0,
	    yPos = 0;
	// for all values in the column
	for(int i = 0; i < 9; i++)
	{
		// if not filled in and if grid has given cell value
		if(!GetPuzzleCell(column, i).GetCellValue() &&
		   GetPuzzleCell(column, i).HasGridValue(num))
		{
		   	count++;
			yPos = i;
		}
	}

	// if only one cell in the column has that cell value
	if(count == 1)
	{
		// set the cell value to the given cell value
		GetPuzzleCellRef(column, yPos).SetCellValue(num);
		// erase that value from the sqaure, column, and row
		EraseAll(column, yPos);
		// fill in any finished cells
		FillFinishedCells();
	}
}

void Solver::UC_Square(int squareX, int squareY, int num)
// given: a square, and a certain value
// Finds if there is only one cell with that value in the square and fills
// in that value, deletes that value from other cells, and fills in 
// all finished cells
{
	int count = 0,
	    xPos = 0,
	    yPos = 0;
	// for all values in the square
	for(int i = squareX; i < squareX+3; i++)
	{
		for(int j = squareY; j < squareY+3; j++)
		{
			// if not filled in and if grid has given cell value
			if(!GetPuzzleCell(i, j).GetCellValue() &&
			   GetPuzzleCell(i, j).HasGridValue(num))
			{
				count++;
				xPos = i;
				yPos = j;
			}
		}
	}
	// if only one cell in the square has that cell value
	if(count == 1)
	{
		// fill in that cell 
		GetPuzzleCellRef(xPos, yPos).SetCellValue(num);
		// erase value from column, row, and square
		EraseAll(xPos, yPos);
		// fill in any finished cells
		FillFinishedCells();
	}
			
}

void Solver::UniqueCandidateAll()
// applies the unique candidate algorithm to all rows, columns, and squares
{
	int xSquare = 0,
	    ySquare = 0;
	// for all columns, rows, and squares
	for(int i = 0; i < 9; i++)
	{
		// for all possible cell values
		for(int j = 1; j < 10; j++)
		{
			UC_Column(i, j);
			UC_Row(i, j);
			UC_Square(xSquare, ySquare, j);
		}
		ySquare += 3;
		if((i+1) % 3 == 0)
		{
			ySquare = 0;
			xSquare += 3;
		}
	}
}


void Solver::SolveAll()
// does all of the algorithms to all of the squares, columns, and rows
{
	BlockColumnRowAll();
	UniqueCandidateAll();
	NakedSubsetAll();
}


void Solver::NS_Row(int xPos, int yPos)
// given:: a certain cell to look at
// looks to see if there are exactly the same number of cells as there are
// grid values of the given cell.  It also looks to see if those cells have
// the exact same grid values as the given cell.  If all of those are true
// then it removes the grid values of the given cell from all the other cells
// that don't have the same grid as the given cell
{
	int count = 0;
	int gridPos[9][9] = {0};
	gridPos[xPos][yPos] = 1;
	// for all elements in the row
	for(int i = 0; i < 9; i++)
	{
		// if the two cells have the same grid values
		if(GetPuzzleCell(xPos, yPos) == GetPuzzleCell(i, yPos))
		{
			// count up and remember the position
			gridPos[i][yPos] = 1;	
			count++;
		}
	}
	// if the amount of cells is the same as the grid value of the given
	// cell
	if(count == GetPuzzleCell(xPos, yPos).GetAmountOfGrid())
	{
		std::cout << "row" << std::endl;
		// for all rows
		for(int i = 0; i < 9; i++)
		{
			// remove the grid values of the given cell from
			// all cells that aren't the same as the given cell
			if(!gridPos[i][yPos])
				GetPuzzleCellRef(i, yPos).Delete(GetPuzzleCell
								(xPos, yPos));
		}
	}
	FillFinishedCells();
}

void Solver::NS_Column(int xPos, int yPos)
// given:: a certain cell to look at
// looks to see if there are exactly the same number of cells as there are
// grid values of the given cell.  It also looks to see if those cells have
// the exact same grid values as the given cell.  If all of those are true
// then it removes the grid values of the given cell from all the other cells
// that don't have the same grid as the given cell

{
	int count = 0;
	int gridPos[9][9] = {0};
	gridPos[xPos][yPos] = 1;
	// for all columns
	for(int i = 0; i < 9; i++)
	{
		// if the two cells have the same grid values
		if(GetPuzzleCell(xPos, yPos) == GetPuzzleCell(xPos, i))
		{
			// count up and remember the position
			gridPos[xPos][i] = 1;
			count++;
		}
	}
	// if the amount of cells is the same as the grid value of the given
	// cell
	if(count == GetPuzzleCell(xPos, yPos).GetAmountOfGrid())
	{
		std::cout << "column" << std::endl;
		// for all columns
		for(int i = 0; i < 9; i++)
		{
			// remove the grid values of the given cell from
			// all cells that aren't the same as the given cell
			if(!gridPos[xPos][i])
				GetPuzzleCellRef(xPos, i).Delete(GetPuzzleCell
								(xPos, yPos));
		}
	}
	FillFinishedCells();
}

void Solver::NS_Square(int xPos, int yPos)
// given:: a certain cell to look at
// looks to see if there are exactly the same number of cells as there are
// grid values of the given cell.  It also looks to see if those cells have
// the exact same grid values as the given cell.  If all of those are true
// then it removes the grid values of the given cell from all the other cells
// that don't have the same grid as the given cell
{
	int count = 0,
	    xSquare = SquareStart(xPos),
	    ySquare = SquareStart(yPos);
	int gridPos[9][9] = {0};
	gridPos[xPos][yPos] = 1;
	// for all squares
	for(int i = xSquare; i < xSquare+3; i++)
	{
		for(int j = ySquare; j < ySquare+3; j++)
		{
			// if the two cells have the same grid values
			if(GetPuzzleCell(xPos, yPos) == GetPuzzleCell(i, j))
			{
				// count up and remember the position
				gridPos[i][j] = 1;
				count++;	
			}
		}
	}
	// if the amount of cells is the same as the grid value of the given
	// cell
	if(count == GetPuzzleCell(xPos, yPos).GetAmountOfGrid())
	{
		std::cout << "square" << std::endl;	
		// for all squares
		for(int i = xSquare; i < xSquare+3; i++)
		{
			for(int j = ySquare; j < ySquare+3; j++)
			{
				// remove all grid values of the given cell
				// from all the cell that aren't the same as
				// the given cell
				if(!gridPos[i][j])
					GetPuzzleCellRef(i, j).Delete
						(GetPuzzleCell(xPos, yPos));
			}
		}
	}
}


void Solver::NakedSubsetAll()
// does the naked subset algorithm to all columns, rows, and squares
{
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			NS_Row(j, i);
			NS_Column(i, j);
			NS_Square(i, j);
		}
	}
}

void Solver::BlockColumn(int squareX, int squareY)
// given: a block to look at
// if a specific column has a number and all of the corners of the given square
// are filled with values that are not that number. Remove that number from
// the middle row of the given square
{
   squareX = SquareStart(squareX);		
   squareY = SquareStart(squareY);
   // if corners of the square are filled
   if(CornersFilled(squareX, squareY))
   {
   	// for all values in the middle column of the square
	for(int i = 0; i < 9; i++)
	{
	   // if the the cell in the middle column of the square is not in
	   // the square
	   if(i != squareY && i != squareY+1 && i != squareY+2) 
	   {
	      int columnValue = GetPuzzleCell(squareX+1, i).GetCellValue();
	      // if cell has a value and its not in the square
	      if(!InSquare(squareX, squareY, columnValue) && columnValue)
	      {
	      	 // for all values in the middle row of the square
	         for(int j = 0; j < 9; j++)
		 {
		    // if the cell in the middle row of the square is not in
		    // the square
		    if(j != squareX && j != squareX+1 && j != squareX+2)
		    {
		       // delete that value from the cell
		       GetPuzzleCellRef(j, squareY+1).Delete(columnValue-1);
		       std::cout << "deleting row" << std::endl;
		    }
		 }
	      }
	   }
	}

       FillFinishedCells();
   }
}

void Solver::BlockRow(int squareX, int squareY)
// given: a block to look at
// if a specific row has a number and all of the corners of the given square
// are filled with values that are not that number. Remove that number from
// the middle column of the given square
{   
   squareX = SquareStart(squareX);		
   squareY = SquareStart(squareY);
   // if the corners of the square are filled
   if(CornersFilled(squareX, squareY))
   {
   	// for all values in the middle row of the square
	for(int i = 0; i < 9; i++)
	{
	   // if the the cell in the middle row of the square is not in
	   // the square
	   if(i != squareX && i != squareX+1 && i != squareX+2) 
	   {
	      int rowValue = GetPuzzleCell(i, squareY+1).GetCellValue();
	      // if cell has a value and its not in the square
	      if(!InSquare(squareX, squareY, rowValue) && rowValue)
	      {
	         // for all values in the middle columns of the square
	         for(int j = 0; j < 9; j++)
		 {
		    // if the cell in the middle column of the square is not
		    // in the square
		    if(j != squareY && j != squareY+1 && j!= squareY+2)
		    {
		       // delete that value from the cell 
		       GetPuzzleCellRef(squareX+1, j).Delete(rowValue-1);
		       std::cout << "deleting column" << std::endl;
		    }
		 }
	      }
	   }
	}

       FillFinishedCells();
   }
}

void Solver::BlockColumnRowAll()
{
	// do block and column/row interaction alg to all blocks
	for(int i = 0; i < 9; i+=3)
		for(int j = 0; j < 9; j+=3)
		{
			BlockColumn(i, j);
			BlockRow(i, j);
		}
}

bool Solver::CornersFilled(int squareX, int squareY) const
{
	squareX = SquareStart(squareX);
	squareY = SquareStart(squareY);
	// for corner cells of a square block
	for(int i = 0; i < 3; i+=2)	
	{
		for(int j = 0; j < 3; j+=2)
		{
			// if a given cell is not filled in
			if(!GetPuzzleCell(squareX+i, squareY+j).GetCellValue())
				return false;
		}
	}
	// corners of a given square are filled
	return true;
}

bool Solver::InSquare(int xPos, int yPos, int num) const
// looks to see if a certain cell number is in a given square
{
	int squareX = SquareStart(xPos),
	    squareY = SquareStart(yPos);
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(num == GetPuzzleCell(squareX+i, squareY+j).
				GetCellValue())
			{
				return true;
			}
		}
	}
	return false;
}

/*
void Solver::DeleteRow(int row, int num)
{
	for(int i = 0; i < 9; i++)
		GetPuzzleCellRef(i, row).Delete(num-1);
}

void Solver::DeleteColumn(int column, int num)
{
	for(int i = 0; i < 9; i++)
		GetPuzzleCellRef(column, i).Delete(num-1);
}

void Solver::DeleteSquare(int xPos, int yPos, int num)
{
	int xSquare = SquareStart(xPos),
	    ySquare = SquareStart(yPos);
	
	for(int i = xSquare; i < xSquare+3; i++)
		for(int j = ySquare; j < ySquare+3; j++)
			GetPuzzleCellRef(i, j).Delete(num-1);
}
*/


int Solver::SquareStart(int pos) const
// finds the coordinate of the upper left hand corner of a square
// given: a x or y value
{
	int square = pos/3;
	switch(square)
	{
		case 0: return 0;
			break;
		case 1: return 3;
			break;
		case 2: return 6;
			break;
		default: return -1;
	}
}

void Solver::FillFinishedCells()
// assigns cell values to all of the cells that are finished
{
	int count = 0;
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
			GetPuzzleCellRef(j, i).CompleteCell();
	EraseAllCells();
}

bool Solver::IsStuck() const
// checks to see if the algorithms are working on the sudoku
{
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
		{
			if(GetPuzzleCell(j, i).IsFinishedGrid() &&
			   GetPuzzleCell(j, i).GetCellValue())
				return false;
		}
	return true;
}


bool Solver::IsSolved() const
// check to see if the sudoku puzzle is fully solved
{
	bool solved = true;
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
			if(GetPuzzleCell(i, j).GetCellValue() == 0)
				solved = false;
	return solved;
			
		
}

void Solver::InitializeAll()
// intializes all of the cells
{
	for(int i = 0; i < 9; i++)
		for(int j = 0; j < 9; j++)
			GetPuzzleCellRef(i, j).Initialize();
}



