#ifndef SOLVER_H
#define SOLVER_H
#include <iostream>
#include <fstream>
#include <string>
#include "cell.h"
#include "common.h"

class Solver
{
public:
	Solver(std::string filename);
	Solver();
	~Solver();

	void Load(std::ifstream& in);
	void Load(Puzzle userPuzzle);

	void SolvePuzzle();
	void ClearPuzzle();
	const Cell& GetPuzzleCell(int xPos, int yPos) const;
	Puzzle GetPuzzle();

	void PrintPuzzle() const;
	friend std::ostream& operator<<(std::ostream& s, const Solver& solver);

private:
	void PrintRow(int row) const;

	Cell& GetPuzzleCellRef(int xPos, int yPos);
	int SquareStart(int pos) const;
	bool CornersFilled(int squareX, int squareY) const;
	bool InSquare(int xPos, int yPos, int num) const;

	void EraseRow(int xPos, int yPos);
	void EraseColumn(int xPos, int yPos);
	void EraseSquare(int xPos, int yPos);
	void EraseAll(int xPos, int yPos);

/*
	void DeleteRow(int row, int num);
	void DeleteColumn(int column, int num);
	void DeleteSquare(int xPos, int yPos, int num);
*/

	void UniqueCandidateAll();
	void UC_Row(int row, int num);
	void UC_Column(int column, int num);
	void UC_Square(int squareX, int squareY, int num);

	void NakedSubsetAll();
	void NS_Row(int xPos, int yPos);
	void NS_Column(int xPos, int yPos);
	void NS_Square(int xPos, int yPos);

	void BlockColumnRowAll();
	void BlockColumn(int squareX, int squareY);
	void BlockRow(int squareX, int squareY);

	void FillFinishedCells(); // assigns cell value to finished cells
	void EraseAllCells();
	void SolveAll();
	bool IsSolved() const;
	bool IsStuck() const;

	void InitializeAll();

	Cell _puzzle[9][9];
	Puzzle _sentPuzzle;
	std::string _filename;
};

#endif
