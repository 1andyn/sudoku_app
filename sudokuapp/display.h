#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Graphics.hpp> //Main Graphics Library
#include <vector>
#include "common.h"

//constants to prevent magic numbers
const static int BUTTON_X = 300; // Size of Buttons Horizontally
const static int BUTTON_Y = 80; // Size of Buttons Vertically (in Pixels)
const static int puzzle_row_max = 9; // Number of values per row
const static int puzzle_col_max = 9; // Number of values per column
const static float initial_x = 98; // Starting coordinate to draw numbers 
const static float initial_y = 40;  // Starting Y coordinate to draw numbers
const static float x_increments = 48; // Distance between numbers in boxes horizontally
const static float y_increments = 48; // Distance between numbers in boxes vertically
const static int max_puzzle_size = 81; // Maximum number of elements in entire puzzle
const static int init_cursor_index = 40; // Initial starting point for highlighted number
const static int cursor_max = 80; // Maximum cursor value for selecting box
const static int cursor_min = 0; // Minimum Cursor value for selecting box
const static int cursor_y_increments = 9; // Cursor increments going up and down
const static int small_button_x = 148; // Smaller button Dimensions
const static int small_button_y = 48; // Smaller button Dimensions
const static int game_res = 600; // MYGAME window resoluton 600 x 600
const static int disp_bit = 32; // color bits (32)

//typedef std::vector<std::vector<int>> Puzzle; //2D vector is defined as Puzzle

class display
{
public:
	display();
	~display(void);
	
	// Primary FUNCTIONS
	void show(); // main void function which displays everything else
	bool game_is_running(); // returns status of window

	//MAIN FUNCTIONS
	void intro_disp(); // function that shows logo

	//INTERACTION FUNCTIONS
	void update_mouse(); // update mouse coordinate when called
	int menu_buttons(); // handle button presses in main menu
	int play_buttons(Puzzle &main, Puzzle &sol); // handle play presses while playing game
	int solver_buttons(Puzzle &main);
	bool about_button(); // handle button presses in about menu
	void highlight_num(int direction); // highlights number that is selected
	void get_key_press(sf::Event interaction, Puzzle &main); // handles user input

	//RENDER FUNCTIONS
	void draw_help_text(int MYGAMEstate); // draws top helper text
	void draw_menu(); // draws sprites for main menu
	void draw_about(); // draws sprites for about menu
	void draw_game(); // draws sprites for MYGAME menu
	void draw_solver(); // draws sprites for SOLVER menu
	void draw_unum(int x, Puzzle &main); // draw updated number
	void draw_nums(Puzzle &main); // draws numbers on play screen
	void window_display(); // calls window to output whatever is in buffer
	void window_clear(); // clear window's uffer
	int update_gs(); // updates DISPLAY gamestate
	
	//PUZZLE FUNCTIONS
	void load_puzzle(Puzzle &main); // loads puzzle into game
	void load_puzzle(int x); // overloaded load puzzle to load empty puzzle
	void generate_text(Puzzle &main); // populates numbers vector
	void clear_puzzles(); // clears puzzles
	int get_zero(); // returns number of ZEROS left on puzzle
	void _match_parent_gs(int gs); // match parent gamestate
	void _give_up(Puzzle &sol); // give up game
	void _reveal_hint(Puzzle &main, Puzzle &sol); // reveals a hint
	Puzzle return_copy(); // returns puzzle copy

	// PUBLIC ENUMS
	enum {WAIT, PLAYING, WIN, LOSE_CONT, GIVEUP};
	enum {EXIT, NOTHING, HINT, GIVE, EASY, MED, HARD, SOLVE};
	enum {PLAY = 1, ABOUT, SOLVER};

private:
	// MAIN DATA
	sf::RenderWindow Window; // Main render window

	// VISUAL DATA
	std::vector<sf::Texture*> TEXTURES; // Texture Container
	std::vector<sf::Sprite*> SPRITES; // Sprite Container
	std::vector<sf::Text> text_container; // container the numbers in TEXT format for display
	std::vector<sf::Text*> text_info; // container for help tool tip pop ups
	sf::Font default_font; // Default Font Storage

	// NUMERICAL DATA
	Puzzle PUZZLE_COPY; // Can't modify original puzzle
	sf::Vector2i mouse_coord; // Two Interger Vector for Mouse Coordinates
	int cursor_coord; // Selected Number Index
	int zero_count; // How many empty boxes are left
	int display_game_state; // Display's Game State

	// Enumerations
	enum {COPY, ORIGIN};
	enum {LEFT, RIGHT, UP, DOWN};

	//VISUAL FUNCTIONS
	bool mouse_over_big(int sprite);		
	bool mouse_over_small(int sprite);
	bool button_clicked(sf::Event occur);

	//PUZZLE ACQUISITION FUNCTIONS
	int value_at_cursor(int puzzle, Puzzle &main); // calculates value at cursor
	int cursor_row(); // returns value of row at cursor
	int cursor_column(); // returns value of colum at cursor
	int value_at_index(int x, Puzzle &main); // calculates value at a certain index
	void debug_show_puzzles(Puzzle &main, Puzzle &sol); // shows debug puzzles
	void _give_text(); // updates text when using give up

};

#endif


