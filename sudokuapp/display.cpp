#include "display.h"
#include <SFML/Graphics.hpp> //Main Graphics Library
#include <iostream> //Iostream for Debug Purposes
#include <vector> //Vector container for storing values
#include <sstream> //Library for converting integers to strings

/* --------Texture Organization-------------- 
0. Main Menu Background BG Texture 
1. Play Button Texture 
2. Moused Over Play Texture 
3. About Button Texture 
4. Moused Over Button Texture 
5. Exit Button Texture 
6. Moused over Button Texture 
7. Play Background Texture 
8. Hint Texture 
9. Moused Over Hint Texture 
10. Give Up Texture 
11. Moused Over Give Up Texture 
12. Return to Main Menu Texture 
13. Moused Over Return Texture 
14. About Display Texture 
15. About Return Button Texture 
16. About Return Buttom Mouse over texture 
17. Easy Normal Texture 
18. Easy Selected Texture  
19. Medium Normal Texture  
20. Medium Selected Texture  
21. Hard Normal Texture 
22. Hard Selected Texture 
23. Solver Button Normal Texture
24. Solver Button Selected Texture
25. Solve Normal Texture
26. Solve Selected Texture
-----------Texture Organization------------*/

/* --------Sprite Organization-------------- 
0. Menu Background 
1. Play Button 
2. About Button 
3. Exit Button 
4. Play Background 
5. Hint Button 
6. Give Up Button 
7. Return to Main Menu Button
8. About Display Sprite  
9. About Return Button 
10. Easy Button 
11. Medium Button 
12. Hard button 
13. Solver Button
14. Solve Button
-----------Sprite Organization------------*/

/*-------------Text Help Setup
0. Wait warning
1. Congratulations Message
2. Incorrect input warning cont
3. Give up Message
4. Helper Interaction Message
------------------------------------------*/

using namespace std;
display::display()
{
	using namespace std;

	//Setting up the Render Window
	Window.create(sf::VideoMode(game_res, game_res, disp_bit), "Sudoku Puzzle Application", sf::Style::Close);
	Window.setFramerateLimit(30); //Set Application to Render at 30FPS Max
	Window.setKeyRepeatEnabled(false);
	cout << "Window settings have been set.." << endl;

	//Setting Up Font
	default_font.loadFromFile("media/arial.ttf"); //Setting Font

	display_game_state = WAIT;

	//Setting Cursor Value for MYGAME
	cursor_coord = init_cursor_index;
	cout << "Initialized Cursor Coordinates" << endl;
			
	//------------------Background Setup
	TEXTURES.push_back(new sf::Texture()); //Insert BG Texture into TEXTURE CONTAINER (0)
	TEXTURES.back()->loadFromFile("media/mainmenu.png"); //Load Texture from media folder
	SPRITES.push_back(new sf::Sprite(*TEXTURES[0])); //Insert BG Sprite into SPRITE CONTAINER (0S)
	//------------------Background Setup
	cout << "Loaded Logo Main Menu Background" << endl;
	//-----------------DEBUG OUTPUT

	//------------------Buttons Setup
	//PLAY BUTTON----------------------------------
	TEXTURES.push_back(new sf::Texture()); //(1)
	TEXTURES.back()->loadFromFile("media/play.png"); //Load Texture from media folder
	TEXTURES.push_back(new sf::Texture()); //(2)
	TEXTURES.back()->loadFromFile("media/playp.png"); //Load Texture from media folder
	SPRITES.push_back(new sf::Sprite(*TEXTURES[1])); //(1S);
	SPRITES.back()->setPosition(150, 250); //Move to Bottom Position
	//PLAY BUTTON----------------------------------

	//ABOUT BUTTON----------------------------------
	TEXTURES.push_back(new sf::Texture()); //(3)
	TEXTURES.back()->loadFromFile("media/about.png"); //Load Texture from media folder
	TEXTURES.push_back(new sf::Texture()); //(4)
	TEXTURES.back()->loadFromFile("media/aboutp.png"); //Load Texture from media folder
	SPRITES.push_back(new sf::Sprite(*TEXTURES[3]));//(2S)
	SPRITES.back()->setPosition(150,390); //Move to Bottom Position
	//ABOUT BUTTON----------------------------------

	//EXIT BUTTON----------------------------------
	TEXTURES.push_back(new sf::Texture());  //(5)
	TEXTURES.back()->loadFromFile("media/exit.png"); //Load Texture from media folder
	TEXTURES.push_back(new sf::Texture());  //(6)
	TEXTURES.back()->loadFromFile("media/exitp.png"); //Load Texture from media folder	
	SPRITES.push_back(new sf::Sprite(*TEXTURES[5]));//(3S)
	SPRITES.back()->setPosition(150, 460); //Move to Bottom Position
	//------------------Buttons Setup
	cout << "Loaded Logo Main Menu Buttons" << endl;
	//------------------DEBUG OUTPUT

	//------------------Background Setup
	TEXTURES.push_back(new sf::Texture()); //(7)
	TEXTURES.back()->loadFromFile("media/playbgn.png"); //Load Texture from media folder
	SPRITES.push_back(new sf::Sprite(*TEXTURES[7]));//(4S)
	//------------------Background Setup
	cout << "Loaded Play Screen Background" << endl;
	//------------------DEBUG OUTPUT

	//-----------------Play Buttons SETUP
	//-----------------Hint Button
	TEXTURES.push_back(new sf::Texture());  //(8)
	TEXTURES.back()->loadFromFile("media/hint.png"); //Load Texture from media folder
	TEXTURES.push_back(new sf::Texture());  //(9)
	TEXTURES.back()->loadFromFile("media/hintp.png"); //Load Texture from media folder
	SPRITES.push_back(new sf::Sprite(*TEXTURES[8]));//(5S)
	SPRITES.back()->setPosition(50, 490); //Move to Bottom Left
	//---------------Hint Button

	//-----------------GIVEUP Button
	TEXTURES.push_back(new sf::Texture());  //(10)
	TEXTURES.back()->loadFromFile("media/giveup.png"); //Load Texture from media folder
	TEXTURES.push_back(new sf::Texture());  //(11)
	TEXTURES.back()->loadFromFile("media/giveupp.png"); //Load Texture from media folder
	SPRITES.push_back(new sf::Sprite(*TEXTURES[10]));//(6S)
	SPRITES.back()->setPosition(230, 490); //Move to Bottom Left
	//---------------GIVEUP Button

	//-----------------MM Button
	TEXTURES.push_back(new sf::Texture());  //(12)
	TEXTURES.back()->loadFromFile("media/smenu.png"); //Load Texture from media folder
	TEXTURES.push_back(new sf::Texture());  //(13)
	TEXTURES.back()->loadFromFile("media/smenup.png"); //Load Texture from media folder
	SPRITES.push_back(new sf::Sprite(*TEXTURES[12]));//(7S)
	SPRITES.back()->setPosition(400, 490); //Move to Bottom Left
	//---------------MM Button
	cout << "Loaded Play Screen Buttons" << endl;
	//--------------DEBUG OUTPUT

	//------------------Background Setup
	TEXTURES.push_back(new sf::Texture()); //(14)
	TEXTURES.back()->loadFromFile("media/aboutbg.png"); //Load Texture from media folder
	SPRITES.push_back(new sf::Sprite(*TEXTURES[14]));//(8S)
	//------------------Background Setup
	cout << "Loaded About Screen Background" << endl;
	//------------------

	//-----------------AR Button
	TEXTURES.push_back(new sf::Texture());  //(15)
	TEXTURES.back()->loadFromFile("media/mm.png"); //Load Texture from media folder
	TEXTURES.push_back(new sf::Texture());  //(16)
	TEXTURES.back()->loadFromFile("media/mmo.png"); //Load Texture from media folder
	SPRITES.push_back(new sf::Sprite(*TEXTURES[15]));//(9S)
	SPRITES.back()->setPosition(140, 440); //Move to Bottom Left
	//---------------MM Button

	//-----------------New Buttons
	//-----------------Easy Button
	TEXTURES.push_back(new sf::Texture());  //(17)
	TEXTURES.back()->loadFromFile("media/easy.png"); //Load Texture from media folder
	TEXTURES.push_back(new sf::Texture());  //(18)
	TEXTURES.back()->loadFromFile("media/seasy.png"); //Load Texture from media folder
	SPRITES.push_back(new sf::Sprite(*TEXTURES[17]));//(10S)
	SPRITES.back()->setPosition(50, 530); //Move to Bottom Left
	//-----------------Easy Button

	//-----------------Med Button
	TEXTURES.push_back(new sf::Texture());  //(19)
	TEXTURES.back()->loadFromFile("media/med.png"); //Load Texture from media folder
	TEXTURES.push_back(new sf::Texture());  //(20)
	TEXTURES.back()->loadFromFile("media/smed.png"); //Load Texture from media folder
	SPRITES.push_back(new sf::Sprite(*TEXTURES[19]));//(11S)
	SPRITES.back()->setPosition(230, 530); //Move to Bottom Left
	//-----------------Med Button

	//-----------------Hard Button
	TEXTURES.push_back(new sf::Texture());  //(21)
	TEXTURES.back()->loadFromFile("media/hard.png"); //Load Texture from media folder
	TEXTURES.push_back(new sf::Texture());  //(22)
	TEXTURES.back()->loadFromFile("media/shard.png"); //Load Texture from media folder
	SPRITES.push_back(new sf::Sprite(*TEXTURES[21]));//(12S)
	SPRITES.back()->setPosition(400, 530); //Move to Bottom Left
	//-----------------Hard Button
	//---------------New Buttons

	cout << "Loaded About Screen Buttons" << endl;
	cout << "Loading Complete." << endl;

	//-----------------TEXT HELP SETUP
	text_info.push_back(new sf::Text());
	text_info.back()->setFont(default_font);
	text_info.back()->setString("Press Easy, Medium or Hard to Start.");
	text_info.back()->setPosition(180, 10);
	text_info.back()->setColor(sf::Color::Black);
	text_info.back()->setScale(.5,.5);
	text_info.push_back(new sf::Text());
	text_info.back()->setFont(default_font);
	text_info.back()->setString("Congratulations, you have solved the puzzle!");
	text_info.back()->setPosition(150, 10);
	text_info.back()->setColor(sf::Color::Magenta);
	text_info.back()->setScale(.5,.5);
	text_info.push_back(new sf::Text());
	text_info.back()->setFont(default_font);
	text_info.back()->setString("One or more of your inputs are incorrect!");
	text_info.back()->setPosition(160, 10);
	text_info.back()->setColor(sf::Color::Red);
	text_info.back()->setScale(.5,.5);
	text_info.push_back(new sf::Text());
	text_info.back()->setFont(default_font);
	text_info.back()->setString("You have given up on the puzzle!");
	text_info.back()->setPosition(180, 10);
	text_info.back()->setColor(sf::Color::Red);
	text_info.back()->setScale(.5,.5);
	text_info.push_back(new sf::Text());
	text_info.back()->setFont(default_font);
	text_info.back()->setString("Use Arrow Keys to Navigate and 1,2,3,4,5,6,7,8,9 Keys to change numbers");
	text_info.back()->setPosition(50, 10);
	text_info.back()->setColor(sf::Color::Black);
	text_info.back()->setScale(.5,.5);
	//----------------Text Help Setup
	
	//------------------Buttons Setup
	//SOlVER BUTTON----------------------------------
	TEXTURES.push_back(new sf::Texture()); //(23)
	TEXTURES.back()->loadFromFile("media/solver.png"); //Load Texture from media folder
	TEXTURES.push_back(new sf::Texture()); //(24)
	TEXTURES.back()->loadFromFile("media/solverp.png"); //Load Texture from media folder
	SPRITES.push_back(new sf::Sprite(*TEXTURES[23])); //(13S);
	SPRITES.back()->setPosition(150, 320); //Move to Bottom Position
	//SOLVER BUTTON----------------------------------
	//-----------------Solve Button
	TEXTURES.push_back(new sf::Texture());  //(25)
	TEXTURES.back()->loadFromFile("media/solve.png"); //Load Texture from media folder
	TEXTURES.push_back(new sf::Texture());  //(26)
	TEXTURES.back()->loadFromFile("media/solvep.png"); //Load Texture from media folder
	SPRITES.push_back(new sf::Sprite(*TEXTURES[25]));//(14S)
	SPRITES.back()->setPosition(50, 490); //Move to Bottom Left
	//-----------------Solve Button
}

void display::intro_disp()
{
	using namespace std; //Namespace for IOSTREAM Function

	sf::Texture Logo; //Create Texture object for Manoa Logo
	Logo.loadFromFile("media/mano.png"); //Load Texture from media folder
	sf::Sprite LogoSprite(Logo); //Change Texture into Sprite

	Window.draw(LogoSprite); //Draw logo
	Window.display(); //Show Current Display
	
	sf::Clock logo_clock; //Create Clock for logo
	sf::Time timer = logo_clock.getElapsedTime(); //Time Object for Comparison
	sf::Time tr_sec = sf::seconds(2); //Show Manoa Logo for 3 Seconds

	cout << "Waiting two seconds.." << endl;
	while(timer < tr_sec)
	{
		timer = logo_clock.getElapsedTime(); //Waiting 2 Seconds
	}
	Window.clear(); //Clear Display
	cout << "Intro Complete." << endl;
}


display::~display(void)
{
}

void display::draw_menu()
{
	for(int x = 0; x <= 3; x++)
	{
		Window.draw(*SPRITES[x]); //Draw Sprites for Main Menu
	}
	Window.draw(*SPRITES[13]);
}

bool display::game_is_running()
{
	return (Window.isOpen());
}


void display::draw_about()
{
	Window.draw(*SPRITES[8]);
	Window.draw(*SPRITES[9]);
}


void display :: draw_game()
{
	//main buttons
	for (int x = 4; x <= 7; x++)
	{
		Window.draw(*SPRITES[x]); //Draw sprites
	}
	//new buttons
	for(int x = 10; x <= 12; x++)
	{
		Window.draw(*SPRITES[x]);
	}
}

void display :: draw_solver()
{
	Window.draw(*SPRITES[4]);
	Window.draw(*SPRITES[7]);
	Window.draw(*SPRITES[14]);
}

void display::load_puzzle(int x)
{
	PUZZLE_COPY.clear();//CLEAR VECTOR COPY BEFORE PUSHING NEW VALUE

	for (int r = 0; r < puzzle_row_max; ++r)
	{
		std::vector<int> column_vec;
		for(int c = 0; c < puzzle_col_max; ++c)
		{
			column_vec.push_back(0);
		}
		PUZZLE_COPY.push_back(column_vec);
	}

}

void display::load_puzzle(Puzzle &main)
{
	PUZZLE_COPY.clear();//CLEAR VECTOR COPY BEFORE PUSHING NEW VALUE

	for (int r = 0; r < puzzle_row_max; r++)
	{
		std::vector<int> column_vec;
		for(int c = 0; c < puzzle_col_max; c++)
		{
			column_vec.push_back(main[r][c]);
		}
		PUZZLE_COPY.push_back(column_vec);
	}

}

void display::draw_nums(Puzzle &main)
{
		for(int x = 0; x < max_puzzle_size; x++)
		{
			if(value_at_index(x, main) == 0)
			{
				text_container[x].setColor(sf::Color::Red);
			}
			else {text_container[x].setColor(sf::Color::Black);}
			text_container[x].setFont(default_font);
			Window.draw(text_container[x]);
		}
			text_container[cursor_coord].setColor(sf::Color::Green);
			Window.draw(text_container[cursor_coord]);
}

void display::generate_text(Puzzle &main)
{
	text_container.clear(); //Clear Text Container before Inserting Elements 
	
	//Debug outputs
	using namespace std;
	cout << "Generating Puzzle..." << endl;
	zero_count = 0;
	//Debugo outputs
	
	//Create Temporary Text Class
	sf::Text temp;
	for (int r = 0; r < puzzle_row_max; r++)
	{
		for(int c = 0; c < puzzle_col_max; c++)
		{
			int number = main[r][c];

			std::stringstream mystringstream;
			mystringstream << number;

			std::string mystring = mystringstream.str();

			if(number == 0)
			{
				mystring = "*";
				zero_count++;
			}
			temp.setString(mystring);
			temp.setPosition(initial_x + (x_increments * c),initial_y + (y_increments * r));
			text_container.push_back(temp); //Put text into Numbers
		}
	}

}

void display::draw_unum(int x, Puzzle &main)
{
	if(value_at_cursor(ORIGIN, main) == 0)
	{
		if(value_at_cursor(COPY, main) == 0)
		{
			zero_count--;
		}

		if(x == 0)
		{
			zero_count++;
		}

		PUZZLE_COPY[cursor_column()][cursor_row()] = x; //Update Copy of Puzzle to user's input value
		
		sf::Text temp;
	
		std::stringstream mystringstream;
		mystringstream << x;
	
		std::string mystring = mystringstream.str();
		temp.setString(mystring);
		temp.setPosition(text_container[cursor_coord].getPosition());
		temp.setColor(sf::Color::Green);
		text_container[cursor_coord] = temp;
	
		Window.draw(text_container[cursor_coord]);
	}
}

int display::value_at_cursor(int puzzle, Puzzle &main)
{
	if(puzzle == ORIGIN)
	{
		return main[cursor_column()][cursor_row()];
	}
	else {return PUZZLE_COPY[cursor_column()][cursor_row()];}
}

int display::value_at_index(int x, Puzzle &main)
{
	return main[x/9][x%9];
}

int display::cursor_row()
{
	return cursor_coord%9;
}

int display::cursor_column()
{
	return cursor_coord/9;
}

void display::draw_help_text(int gs)
{
	//When in play MYGAMEstate there should be no text that is drawn
	switch(gs)
	{
	case WAIT: 
		Window.draw(*text_info[0]); //default is 0, change value for debugging
		break;
	case WIN:
		Window.draw(*text_info[1]);
		break;
	case LOSE_CONT:
		Window.draw(*text_info[2]);
		break;
	case GIVEUP:
		Window.draw(*text_info[3]);
		break;
	case PLAYING:
		Window.draw(*text_info[4]);
		break;
	}
}

void display::window_display()
{
	Window.display();
}

int display::update_gs()
{
	return display_game_state;
}

void display::clear_puzzles()
{
	PUZZLE_COPY.clear();
}

void display::window_clear()
{
	Window.clear();
}

int display::get_zero()
{
	return zero_count;
}

Puzzle display::return_copy()
{
	return PUZZLE_COPY;
}

void display::_match_parent_gs(int gs)
{
	display_game_state = gs;
}

void display::_give_up(Puzzle &sol)
{
	for (int r = 0; r < puzzle_row_max; r++)
	{
		for(int c = 0; c < puzzle_col_max; c++)
		{
			PUZZLE_COPY[r][c] = sol[r][c];
		}
	}
	_give_text();
}


void display::_give_text()
{
	text_container.clear(); //Clear Text Container before Inserting Elements 

	cout << "Changing Copy" << endl;
	zero_count = 0;
	//Create Temporary Text Class
	sf::Text temp;
	for (int r = 0; r < puzzle_row_max; r++)
	{
		for(int c = 0; c < puzzle_col_max; c++)
		{
			int number = PUZZLE_COPY[r][c];
			std::stringstream mystringstream;
			mystringstream << number;
			std::string mystring = mystringstream.str();
			temp.setString(mystring);
			temp.setPosition(initial_x + (x_increments * c),initial_y + (y_increments * r));
			text_container.push_back(temp); //Put text into Numbers
		}
	}

}

void display :: _reveal_hint(Puzzle &main, Puzzle &sol)
{
	using namespace std;
	
	int RAND_VAL_Y = (rand() % 9); // COLUMN
	int RAND_VAL_X = (rand() % 9); // ROW

	sf::Text TEMP; // Temporary String Object

	bool NOT_REVEALED = 1;
	while(NOT_REVEALED)
	{
		if(main[RAND_VAL_X][RAND_VAL_Y] == 0)
		{
			int NUMBER = sol[RAND_VAL_X][RAND_VAL_Y]; // Number that is converted into string

			stringstream STRING_NUM;
			STRING_NUM << NUMBER; // Insert Number into String Stream
			string NEW_STRING = STRING_NUM.str(); // String is equal to String Stream
			
			TEMP.setString(NEW_STRING); // Set string for new String Object
			TEMP.setPosition(initial_x + (x_increments * RAND_VAL_Y),initial_y + (y_increments * RAND_VAL_X));

			text_container[(RAND_VAL_X*9)+RAND_VAL_Y] = TEMP;
			
			if(PUZZLE_COPY[RAND_VAL_X][RAND_VAL_Y] == 0)
			{
				--zero_count; // Reduce Zero Count if value was originally Blank 
			}
			
			PUZZLE_COPY[RAND_VAL_X][RAND_VAL_Y] = NUMBER; // Update Puzzle Copy
			
			NOT_REVEALED = 0;

		}
		else
		{
			// Generate new Random Values
			RAND_VAL_X = (rand() % 9);
			RAND_VAL_Y = (rand() % 9);
		}
	}

}

bool display::mouse_over_big(int sprite)
{
	return (mouse_coord.x > SPRITES[sprite]->getPosition().x
			&& mouse_coord.x < SPRITES[sprite]->getPosition().x + BUTTON_X 
			&& mouse_coord.y > SPRITES[sprite]->getPosition().y 
			&& mouse_coord.y < SPRITES[sprite]->getPosition().y  + BUTTON_Y);

}

bool display::mouse_over_small(int sprite)
{
	return (mouse_coord.x > SPRITES[sprite]->getPosition().x
		   && mouse_coord.x < SPRITES[sprite]->getPosition().x + small_button_x
		   && mouse_coord.y > SPRITES[sprite]->getPosition().y 
		   && mouse_coord.y < SPRITES[sprite]->getPosition().y  + small_button_y);
}

bool display::button_clicked(sf::Event mouse_event)
{
	return (mouse_event.type == sf::Event::MouseButtonReleased && mouse_event.mouseButton.button == sf::Mouse::Left);
}