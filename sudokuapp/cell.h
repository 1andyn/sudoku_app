#ifndef CELL_H
#define CELL_H

// A cell class consists of grid values 1-9. They are all of the possible values
// that a single sudoku cell can have.  If the cell is filled in, it will have
// a non-zero cell value and the grid will be cleared.

#include <iostream>

class Cell
{
public:
	Cell();
	Cell(int cellValue);
	~Cell();

	void Initialize();
	void Load(std::ifstream& in);
	void Load(int cellValue);

	void PrintGrid() const;

	int* GetGrid();	
	int GetGridValue(int pos) const;
	int GetCellValue() const;
	int GetAmountOfGrid() const;

	void SetGridValue(int pos, int value = 0);
	void SetCellValue(int value);

	void Delete(int pos);
	void Delete(const Cell& cell);
	void ClearGrid();
	void CompleteCell();

	bool IsCompleted() const;
	bool IsPrinted() const;
	bool HasGridValue(int num) const;
	bool IsFinishedGrid() const;

	friend bool operator== (const Cell& a, const Cell& b);
	friend std::ostream& operator<< (std::ostream& s, const Cell& celL);
	
private:

	int _cellGrid[9];
	int _cellValue;
	int _gridCount;

};

#endif
