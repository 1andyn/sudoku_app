#pragma once
#include <iostream>
#include "display.h"
#include "generator.h"
#include "solver.h"

#ifndef SUDOKU_H
#define SUDOKU_H

#define MAX_HINTS 3
#define row_max 9
#define column_max 9

class sudoku
{
public:
	sudoku(void);
	~sudoku(void);
	void start();
	bool is_open();

private:
	// Private Data
	Generator PUZZ_GEN;
	Solver SOLVER;
	display MYGAME;
	int GAMESTATE;
	int HINTCOUNT;
	
	// Enumerations
	enum {_EASY = 0, _MED = 1, _HARD = 2};

	// Call Display Function
	void menu_loop();
	void show_menu();
	void show_game();
	void show_about();
	void show_solver();

	// Puzzle Functions
	void grab_puzzle();

	// void generate_puzzle();
	bool update_play_gamestate();
	bool update_solver_gamestate();
	void check_answers();
	bool puzz_compare();
	void _reset_hint();
	void _regen_puzzle(int diff);

};

#endif