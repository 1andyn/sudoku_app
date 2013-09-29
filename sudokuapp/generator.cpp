#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "generator.h"

using namespace std;

Generator::Generator(string easy, string medium, string hard)
{
	Initialize(easy, medium, hard);
}

Generator::~Generator()
{
}

void Generator::Clear_Puzzles()
{
	for(int i = 0; i < BOARD_HEIGHT; i++)
	{
		for(int j = 0; j < BOARD_WIDTH; j++)
		{
			_cSolved[i][j] = NULL;
			_cUnsolved[i][j] = NULL;
		}
	}
}


void Generator::GeneratePuzzle(int difficulty)
// randomly generates a puzzle given a difficulty (EASY, MEDIUM, HARD)
// takes a template puzzle and performs transformations to it
{
	srand(time(NULL));
	for(int i = 0; i < BOARD_HEIGHT; i++)
	{
		for(int j = 0; j < BOARD_WIDTH; j++)
		{
			_cSolved[i][j] = _tSolved[i][j][difficulty];
			_cUnsolved[i][j] = _tUnsolved[i][j][difficulty];
		}
	}

	for(int i = 0; i < 10000; i++)
	{		
		int random = rand()%9;
		if(random == 2 || random == 5 || random == 8)
		{
			SwitchColumns(random, random - rand()%2);
			SwitchRows(random, random - rand()%2);
		}
		else if(random == 1 || random == 4 || random == 7)
		{
			SwitchColumns(random, random + 1);
			SwitchRows(random, random + 1);
		}
		else
		{
			SwitchColumns(random, random + rand()%2);
			SwitchRows(random, random + rand()%2);
		}
		SwitchNums(rand()%10, rand()%10);
		SwitchSquareColumns(rand()%3, rand()%3);
		SwitchSquareRows(rand()%3, rand()%3);
	}

}

void Generator::PrintTemplatePuzzle(int difficulty)
// prints out a template puzzle of a given difficulty (EASY, MEDIUM, HARD)
// prints out the solved and unsolved versions
{
	cout << "Solved Puzzle" << endl;
	for(int i = 0; i < BOARD_HEIGHT; i++)
	{
		for(int j = 0; j < BOARD_WIDTH; j++)
		{
			cout << _tSolved[j][i][difficulty] << " ";
		}
		cout << endl;
	}

	cout << "Unsolved Puzzle" << endl;
	for(int i = 0; i < BOARD_HEIGHT; i++)
	{
		for(int j = 0; j < BOARD_WIDTH; j++)
		{
			cout << _tUnsolved[j][i][difficulty] << " ";
		}
		cout << endl;
	}
}

Puzzle Generator::GetSolved() 
{
	return _cSolved;
}

Puzzle Generator::GetUnsolved()
{
	return _cUnsolved;
}

ostream& operator<< (ostream& out, Generator& gen)
// prints out the current randomly generated puzzle
// prints out solved and unsolved versions
{
	out << "Solved Puzzle" << endl;	
	for(int i = 0; i < Generator::BOARD_HEIGHT; i++)
	{
		for(int j = 0; j < Generator::BOARD_WIDTH; j++)
		{
			out << gen._cSolved[j][i] << " ";
		}
		out << endl;
	}
	out << "UnSolved Puzzle" << endl;
	for(int i = 0; i < Generator::BOARD_HEIGHT; i++)
	{
		for(int j = 0; j < Generator::BOARD_WIDTH; j++)
		{
			out << gen._cUnsolved[j][i] << " ";
		}
		out << endl;
	}
	return out;
}

// private functions

void Generator::SwitchRows(int row1, int row2)
// switches any two rows
{
	// if not in bounds or same rows
	if(row1 < 0 || row1 > 8 || row2 < 0 || row2 > 8 || row1 == row2)
		return;

	int tempSolved[BOARD_WIDTH] = {0};
	int tempUnsolved[BOARD_WIDTH] = {0};
	for(int i = 0; i < BOARD_WIDTH; i++)
	{
		tempSolved[i] = _cSolved[i][row1];
		tempUnsolved[i] = _cUnsolved[i][row1];
		_cSolved[i][row1] = _cSolved[i][row2];
		_cUnsolved[i][row1] = _cUnsolved[i][row2];
	}

	for(int i = 0; i < BOARD_WIDTH; i++)
	{
		_cSolved[i][row2] = tempSolved[i];
		_cUnsolved[i][row2] = tempUnsolved[i];
	}
	
}

void Generator::SwitchColumns(int col1, int col2)
// switches any two columns
{
	// if not in bounds or same cols
	if(col1 < 0 || col1 > 8 || col2 < 0 || col2 > 8 || col1 == col2)
		return;

	int tempSolved[BOARD_HEIGHT] = {0};
	int tempUnsolved[BOARD_HEIGHT] = {0};
	for(int i = 0; i < BOARD_HEIGHT; i++)
	{
		tempSolved[i] = _cSolved[col1][i];
		tempUnsolved[i] = _cUnsolved[col1][i];
		_cSolved[col1][i] = _cSolved[col2][i];
		_cUnsolved[col1][i] = _cUnsolved[col2][i];
	}

	for(int i = 0; i < BOARD_HEIGHT; i++)
	{
		_cSolved[col2][i] = tempSolved[i];
		_cUnsolved[col2][i] = tempUnsolved[i];
	}
	
}

void Generator::SwitchSquares(int squareX1, int squareY1, int squareX2,
			      int squareY2)
// switches any two squres in the sudoku grid
{
	int tempSolved[SQUARE_HEIGHT][SQUARE_WIDTH] = {0};
	int tempUnsolved[SQUARE_HEIGHT][SQUARE_WIDTH] = {0};
	int x1 = SquareCoord(squareX1), x2 = SquareCoord(squareX2);	
	int y1 = SquareCoord(squareY1), y2 = SquareCoord(squareY2);

	for(int i = 0; i < SQUARE_HEIGHT; i++)
		for(int j = 0; j < SQUARE_WIDTH; j++)
		{
			tempSolved[i][j] = _cSolved[i+x1][j+y1];
			tempUnsolved[i][j] = _cUnsolved[i+x1][j+y1];
			_cSolved[i+x1][j+y1] = _cSolved[i+x2][j+y2];
			_cUnsolved[i+x1][j+y1] = _cUnsolved[i+x2][j+y2];
		}
	for(int i = 0; i < SQUARE_HEIGHT; i++)
		for(int j = 0; j < SQUARE_WIDTH; j++)
		{
			_cSolved[i+x2][j+y2] = tempSolved[i][j];
			_cUnsolved[i+x2][j+y2] = tempUnsolved[i][j];
		}
}

void Generator::SwitchSquareRows(int square1, int square2)
// switches any row of squares with another row of squares
{
	// if not in bounds or same squares
	if(square1 < 0 || square1 > 2 || square2 < 0 || square2 > 2 ||
	   square1 == square2)
		return;

	int startRow1 = SquareCoord(square1),
	    startRow2 = SquareCoord(square2);
	
	for(int i = 0; i < 3; i++)
	{
		SwitchRows(startRow1 + i, startRow2 + i);
	}

}

void Generator::SwitchSquareColumns(int square1, int square2)
// switch any column of squares with another column of squares
{
	// if not in bounds or same squares
	if(square1 < 0 || square1 > 2 || square2 < 0 || square2 > 2 ||
	   square1 == square2)
		return;

	int startCol1 = SquareCoord(square1),
	    startCol2 = SquareCoord(square2);
	
	for(int i = 0; i < 3; i++)
	{
		SwitchColumns(startCol1 + i, startCol2 + i);
	}

}

void Generator::Transpose()
{
}

void Generator::SwitchNums(int num1, int num2)
// switches any two given numbers with eachother
{
	if(num1 == num2 || num1 < 1 || num1 > 9 || num2 < 1 || num2 > 9)
		return;
	// switch all num1 and num2
	for(int i = 0; i < BOARD_HEIGHT; i++)
	{
		for(int j = 0; j < BOARD_WIDTH; j++)
		{
			if(_cSolved[j][i] == num1)
			{
				_cSolved[j][i] = num2;
				if(_cUnsolved[j][i])
				{
					_cUnsolved[j][i] = num2;
				}
			}

			else if(_cSolved[j][i] == num2)
			{
				_cSolved[j][i] = num1;
				if(_cUnsolved[j][i])
				{
					_cUnsolved[j][i] = num1;
				}
			}
		}
	}
}

int Generator::SquareCoord(int pos)
// given a square coord, returns what position in the grid
// that square belongs to
{
	switch(pos)
	{
		case 0: return 0;
			break;
		case 1: return 3;
			break;
		case 2: return 6;
			break;
		default: return ERROR;
	}
}

void Generator::InitSize()
// initialize the the board size
{
	_tSolved.resize(BOARD_HEIGHT);
	_tUnsolved.resize(BOARD_HEIGHT);
	_cSolved.resize(BOARD_HEIGHT);
	_cUnsolved.resize(BOARD_HEIGHT);
	for(int i = 0; i < BOARD_HEIGHT; i++)
	{
		_cSolved[i].resize(BOARD_WIDTH);
		_cUnsolved[i].resize(BOARD_WIDTH);
		_tSolved[i].resize(BOARD_WIDTH);
		_tUnsolved[i].resize(BOARD_WIDTH);
		for(int j = 0; j < BOARD_WIDTH; j++)
		{
			_tSolved[i][j].resize(DIFFICULTY);
			_tUnsolved[i][j].resize(DIFFICULTY);
		}
	}


}

void Generator::InitBoard(string easy, string medium, string hard)
// initializes the template puzzles
{	
	ifstream easyPuzzle(easy.c_str());
	ifstream mediumPuzzle(medium.c_str());
	ifstream hardPuzzle(hard.c_str());

	if(easyPuzzle)
	{
		for(int i = 0; i < BOARD_HEIGHT; i++)
			for(int j = 0; j < BOARD_WIDTH; j++)
				easyPuzzle >> _tUnsolved[j][i][EASY];

		for(int i = 0; i < BOARD_HEIGHT; i++)
			for(int j = 0; j < BOARD_WIDTH; j++)
				easyPuzzle >> _tSolved[j][i][EASY];
	}
	if(mediumPuzzle)
	{
		for(int i = 0; i < BOARD_HEIGHT; i++)
			for(int j = 0; j < BOARD_WIDTH; j++)
				mediumPuzzle >> _tUnsolved[j][i][MEDIUM];

		for(int i = 0; i < BOARD_HEIGHT; i++)
			for(int j = 0; j < BOARD_WIDTH; j++)
				mediumPuzzle >> _tSolved[j][i][MEDIUM];
	}

	if(hardPuzzle)
	{
		for(int i = 0; i < BOARD_HEIGHT; i++)
			for(int j = 0; j < BOARD_WIDTH; j++)
				hardPuzzle >> _tUnsolved[j][i][HARD];

		for(int i = 0; i < BOARD_HEIGHT; i++)
			for(int j = 0; j < BOARD_WIDTH; j++)
				hardPuzzle >> _tSolved[j][i][HARD];
	}


}

void Generator::Initialize(string easy, string medium, string hard)
{
	InitSize();
	InitBoard(easy, medium, hard);

}


