#include "sudoku.h"
#include "generator.h"
#include "display.h"

using namespace std;

sudoku::sudoku(void) : PUZZ_GEN("easy.txt", "medium.txt", "hard.txt")
{
	GAMESTATE = display::WAIT;
	HINTCOUNT = 0;
}


sudoku::~sudoku(void)
{
}

bool sudoku::is_open(void)
{
	return MYGAME.game_is_running();
}

void sudoku::start(void)
{
	menu_loop();
}

void sudoku::menu_loop(void)
{
	MYGAME.intro_disp();
	{
		while(MYGAME.game_is_running())
		{
			show_menu();
		}
	}
}

void sudoku::show_menu(void)
{
	MYGAME.draw_menu();
	MYGAME.window_display();
	
	switch(MYGAME.menu_buttons())
	{
	case display::PLAY: 
		show_game();
		break;
	case display::ABOUT: 
		show_about();
		break;
	case display::SOLVER: 
		show_solver();
		break;
	}
}

void sudoku::show_game(void)
{
	GAMESTATE = display::WAIT;
	PUZZ_GEN.Clear_Puzzles();
	MYGAME.load_puzzle(0); //LOAD BLANK PUZZLE
	MYGAME.generate_text(PUZZ_GEN.GetUnsolved());

	bool USR_EXIT = false;
	while(!USR_EXIT)
	{
		check_answers();
		MYGAME.draw_game();
		MYGAME.draw_help_text(GAMESTATE);
		MYGAME.draw_nums(PUZZ_GEN.GetUnsolved());
		MYGAME.window_display();
		USR_EXIT = update_play_gamestate();
	}
}

void sudoku::show_solver(void)
{
	GAMESTATE = display::WAIT;
	SOLVER.ClearPuzzle();
	MYGAME.clear_puzzles();
	MYGAME.load_puzzle(0);
	MYGAME.generate_text(PUZZ_GEN.GetUnsolved());

	bool USR_EXIT = false;
	while(!USR_EXIT)
	{
		MYGAME.draw_solver();
		MYGAME.draw_nums(PUZZ_GEN.GetUnsolved());
		MYGAME.window_display();
		USR_EXIT = update_solver_gamestate();
	}

}

void sudoku::show_about(void)
{
	MYGAME.draw_about();
	while(MYGAME.about_button())
	{
		MYGAME.draw_about();
		MYGAME.window_display();
	}
}

bool sudoku::update_play_gamestate()
{
	GAMESTATE = MYGAME.update_gs(); //Match Display's GameState
	switch(MYGAME.play_buttons(PUZZ_GEN.GetUnsolved(), PUZZ_GEN.GetSolved()))
	{
	case display::EXIT: 
		SOLVER.ClearPuzzle();
		return true;
	case display::HINT:
		if(HINTCOUNT < MAX_HINTS && (GAMESTATE == display::LOSE_CONT || GAMESTATE == display::PLAYING))
		{
			HINTCOUNT++;
			MYGAME._reveal_hint(PUZZ_GEN.GetUnsolved(), PUZZ_GEN.GetSolved());
		}
		break;
	case display::GIVE: 
		if(GAMESTATE == display::PLAYING || GAMESTATE == display::LOSE_CONT)
		{
			GAMESTATE = display::GIVEUP;
			MYGAME._match_parent_gs(GAMESTATE);
			MYGAME._give_up(PUZZ_GEN.GetSolved());
		}
		break;
	case display::EASY:
		_regen_puzzle(_EASY);
		_reset_hint();			
		break;
	case display::MED:
		_regen_puzzle(_MED);
		_reset_hint();		
		break;
	case display::HARD:
		_regen_puzzle(_HARD);
		_reset_hint();		
		break;
	}
	return false;
}

bool sudoku::update_solver_gamestate()
{
	switch(MYGAME.solver_buttons(PUZZ_GEN.GetUnsolved()))
	{
	case display::EXIT:
		return true;
		break;
	case display::SOLVE:
		SOLVER.Load(MYGAME.return_copy());
		SOLVER.SolvePuzzle();
		MYGAME.load_puzzle(SOLVER.GetPuzzle());
		MYGAME.generate_text(SOLVER.GetPuzzle());
		std::cout << SOLVER;
	}
	return false;
}

void sudoku::check_answers(void)
{
	if(MYGAME.get_zero() == 0 && GAMESTATE != display::WIN && GAMESTATE != display::GIVEUP) //STOP CHECKING WHEN GAMEOVER
	{
		if(puzz_compare())
		{
			GAMESTATE = display::WIN;
		}
		else
		{
			GAMESTATE = display::LOSE_CONT;
		}
		MYGAME._match_parent_gs(GAMESTATE);
	}
}

bool sudoku::puzz_compare(void)
{
		for (int r = 0; r < row_max; r++)
		{
			for(int c = 0; c < column_max; c++)
			{
				if(PUZZ_GEN.GetSolved()[r][c] != MYGAME.return_copy()[r][c])
				{
					return false; //FALSE ONCE FIRST INCORRECT ELEMENT IS FOUND
				}
			}
		}

		return true;
}

void sudoku::_reset_hint(void)
{
	HINTCOUNT = 0;
}

void sudoku::_regen_puzzle(int diff)
{
		PUZZ_GEN.GeneratePuzzle(diff);
		MYGAME.load_puzzle(PUZZ_GEN.GetUnsolved());
		MYGAME.generate_text(PUZZ_GEN.GetUnsolved());
}