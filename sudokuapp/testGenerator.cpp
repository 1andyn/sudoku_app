#include <iostream>
#include "generator.h"

int main()
{
	Generator sudoku("easy.txt", "medium.txt", "hard.txt");
	std::cout << "EASY TEMPLATE PUZZLE" << std::endl;
	sudoku.PrintTemplatePuzzle(Generator::EASY);

	std::cout << "MEDIUM TEMPLATE PUZZLE" << std::endl;
	sudoku.PrintTemplatePuzzle(Generator::MEDIUM);

	std::cout << "HARD TEMPLATE PUZZLE" << std::endl;
	sudoku.PrintTemplatePuzzle(Generator::HARD);
	std::cout << std::endl;

	std::cout << "CURRENT MIXED PUZZLE" << std::endl;
	sudoku.GeneratePuzzle(Generator::EASY);	
	std::cout << sudoku;

	sudoku.GeneratePuzzle(Generator::HARD);
	std::cout << sudoku;

}
