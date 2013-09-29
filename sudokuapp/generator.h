#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include <iostream>
#include <fstream>
#include "common.h"

#define DIFFICULTY 4
#define ERROR -1

using namespace std;

class Generator
{
public:
	Generator(string easy, string medium, string hard);
	~Generator();

	enum {BOARD_WIDTH = 9, BOARD_HEIGHT = 9, SQUARE_HEIGHT = 3,
	      SQUARE_WIDTH = 3};

	enum {EASY, MEDIUM, HARD};

	void GeneratePuzzle(int difficulty = EASY);
	void PrintTemplatePuzzle(int difficulty);
	void Clear_Puzzles();
	Puzzle GetSolved(); 
	Puzzle GetUnsolved();

	friend ostream& operator<< (ostream& out, Generator& gen);

private:
	void SwitchRows(int row1, int row2);
	void SwitchColumns(int col1, int col2);

	void SwitchSquareRows(int square1, int square2);
	void SwitchSquareColumns(int square1, int square2);
	
	void SwitchSquares(int squareX1, int squareY1, int squareX2,
			   int squareY2);
	void Transpose();
	void SwitchNums(int num1, int num2);

	int SquareCoord(int pos);

	void Initialize(string easy, string medium, string hard);
	void InitSize();
	void InitBoard(string easy, string medium, string hard);


	// template puzzles
	TemplatePuzzle _tSolved;
	TemplatePuzzle _tUnsolved;

	// current puzzles
	Puzzle _cSolved;
	Puzzle _cUnsolved;

};

#endif


