/*-------------------Tep Dobry EE205 Spring 2013-----------------
-------------------------Team 6 Rotation 4-----------------------
----------------------SUDOKU PUZZLE APPLICATION------------------
--Members: Andy Ng, Jason Tanabe, Matthew Shinsato, Tyler Isono--
----------------------------------------------------------------*/

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <SFML/Graphics.hpp> //Main Graphics Library
#include <iostream> //Console Debugging Purposes
#include "sudoku.h"

int main()
{
	//this code will probably be placed into a Sudoku Class
	//display MAIN;

	sudoku sudo;

	//while(MAIN.MYGAME_is_running())
	while(sudo.is_open())
	{
		sudo.start();
	}

	return EXIT_SUCCESS;
}