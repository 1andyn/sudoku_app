#include <iostream>
#include <fstream>
#include "cell.h"

int main()
{
	Cell one,
	     two(1),
	     three;

	std::ifstream file("test.txt");
	if(file)
		three.Load(file);

	std::cout << "three equals " << three.GetCellValue() << std::endl;
	
	int *testOne = one.GetGrid();
	int *testTwo = two.GetGrid();

	for(int i = 0; i < 9; i++)
	{
		std::cout << "one equals " << testOne[i] << std::endl;
		std::cout << "two equals " << testTwo[i] << std::endl;
	}
	
	one.Delete(0);
	testOne = one.GetGrid();
	std::cout << "delete test " << testOne[0] << std::endl;
	std::cout << "cell value is " << two.GetCellValue() << std::endl;
	std::cout << "two has a complete grid " << two.IsCompleted() 
		<< std::endl;
	one.ClearGrid();
	for(int i = 0; i < 9; i++)
	{
		std::cout << "one equals " << testOne[i] << std::endl;
	}

	std::cout << "one is not complete " << !one.IsCompleted()
		<< std::endl;
	std::cout << "cell value of one is " << one.GetCellValue()
		<< std::endl;
	
	one.CompleteCell();

	std::cout << "cell value of one is now " << one.GetCellValue()
		<< std::endl;
	
	two.PrintGrid();
	
}
