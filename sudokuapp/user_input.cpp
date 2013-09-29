#include "display.h"
#include <SFML/Graphics.hpp> //Main Graphics Library
#include <iostream> //Iostream for Debug Purposes
#include <vector> //Vector container for storing values
#include <sstream> //Library for converting integers to strings


void display::update_mouse()
{
	mouse_coord = sf::Mouse::getPosition(Window);
}

bool display::about_button()
{
	using namespace std;
	update_mouse();

	if(mouse_over_big(9)) //Check if Mouse coordinates are within HITBOX of Play Button
	{
		SPRITES[9]->setTexture(*TEXTURES[16]);
		Window.draw(*SPRITES[9]);
		
		sf::Event mouse_event;
		Window.pollEvent(mouse_event);
		if(button_clicked(mouse_event))
		{
			cout << "Exiting about menu..." << endl;
			return EXIT;
		}				
	}
	else
	{
		SPRITES[9]->setTexture(*TEXTURES[15]);
	}
	return NOTHING;
}

int display::menu_buttons()
{
	sf::Event occur;
	Window.pollEvent(occur);
	
	using namespace std;
	update_mouse();

	if(mouse_over_big(1)) //Check if Mouse coordinates are within HITBOX of Play Button
	{
			SPRITES[1]->setTexture(*TEXTURES[2]);
			Window.draw(*SPRITES[1]);

			if(button_clicked(occur))
			{
				cout << "Play button was pressed!" << endl;
				return PLAY;
			}		
	}
	else
	{
		SPRITES[1]->setTexture(*TEXTURES[1]); //Set Original Texture
	}

	if(mouse_over_big(2))//Check if Mouse coordinates are within HITBOX of aout Button
	{
			SPRITES[2]->setTexture(*TEXTURES[4]);
			Window.draw(*SPRITES[2]);

			if(button_clicked(occur))
			{
				cout << "About button was pressed!" << endl;
				return ABOUT;
			}
					
	}
	else
	{
		SPRITES[2]->setTexture(*TEXTURES[3]); //Set Original Texture
	}

	if(mouse_over_big(13)) //Check if Mouse coordinates are within HITBOX of Solver Button
	{
			SPRITES[13]->setTexture(*TEXTURES[24]);
			Window.draw(*SPRITES[13]);

			if(button_clicked(occur))
			{
				cout << "Solver button was pressed!" << endl;
				return SOLVER;
			}		
	}
	else
	{
		SPRITES[13]->setTexture(*TEXTURES[23]); //Set Original Texture
	}
	if(mouse_over_big(3)) //Check if Mouse coordinates are within HITBOX of exit Button
	{
			SPRITES[3]->setTexture(*TEXTURES[6]);
			Window.draw(*SPRITES[3]);

			if(button_clicked(occur))
			{
				cout << "Exiting..." << endl;
				Window.close();
			}
	}
	else
	{
		SPRITES[3]->setTexture(*TEXTURES[5]); //Set Original Texture
	}

	return WAIT;
}

int display::solver_buttons(Puzzle &main)
{
	display_game_state = PLAYING;
	sf::Event interaction;
	Window.pollEvent(interaction);
	update_mouse();

	using namespace std;

	get_key_press(interaction, main);

	if(mouse_over_small(14)) //Check if Mouse coordinates are within HITBOX of Play Button
	{
			SPRITES[14]->setTexture(*TEXTURES[26]); //update button
			Window.draw(*SPRITES[14]); //update button
			Window.pollEvent(interaction);
			if(button_clicked(interaction))
			{
				cout << "Solve Button was clicked!" << endl;
				return SOLVE;
			}

	}
	else
	{
			SPRITES[14]->setTexture(*TEXTURES[25]);
	}

	if(mouse_over_small(7)) //Check if Mouse coordinates are within HITBOX of exit Button
	{
			SPRITES[7]->setTexture(*TEXTURES[13]); //Redraw new Menu Button
			Window.draw(*SPRITES[7]);
			Window.pollEvent(interaction);
			if(button_clicked(interaction))
			{
				display_game_state = WAIT;
				cout << "Menu button was clicked!" << endl;
				return EXIT;
			}
	}
	else
	{
			SPRITES[7]->setTexture(*TEXTURES[12]);
	}

	return NOTHING;
}

int display::play_buttons(Puzzle &main, Puzzle &sol)
{	
	sf::Event interaction;
	Window.pollEvent(interaction);
	update_mouse();

	using namespace std;

	get_key_press(interaction, main);

	// DEBUG CHEAT BUTTON
	if ((interaction.type == sf::Event::KeyPressed) && (interaction.key.code == sf::Keyboard::S))
	{
			debug_show_puzzles(main, sol);
	}
	// DEBUG CHEAT BUTTON

	if(mouse_over_small(5)) //Check if Mouse coordinates are within HITBOX of Play Button
	{
			SPRITES[5]->setTexture(*TEXTURES[9]); //update button
			Window.draw(*SPRITES[5]); //update button
			Window.pollEvent(interaction);
			if(button_clicked(interaction))
			{
				cout << "Hint Button was clicked!" << endl;
				return HINT;
			}

	}
	else
	{
			SPRITES[5]->setTexture(*TEXTURES[8]);
	}

	if(mouse_over_small(6)) //Check if Mouse coordinates are within HITBOX of aout Button
	{
			SPRITES[6]->setTexture(*TEXTURES[11]);
			Window.draw(*SPRITES[6]);
			
			Window.pollEvent(interaction);
			if(button_clicked(interaction))
			{
				cout << "Give up button was clicked!" << endl;
				return GIVE;
			}
			

	}
	else
	{
			SPRITES[6]->setTexture(*TEXTURES[10]);
	}

	if(mouse_over_small(7)) //Check if Mouse coordinates are within HITBOX of exit Button
	{
			SPRITES[7]->setTexture(*TEXTURES[13]); //Redraw new Menu Button
			Window.draw(*SPRITES[7]);
			Window.pollEvent(interaction);
			if(button_clicked(interaction))
			{
				display_game_state = WAIT;
				cout << "Menu button was clicked!" << endl;
				return EXIT;
			}
			
	}
	else
	{
			SPRITES[7]->setTexture(*TEXTURES[12]);
	}

	if(mouse_over_small(10)) //Check if Mouse coordinates are within HITBOX of exit Button
	{
			SPRITES[10]->setTexture(*TEXTURES[18]); //Redraw new Menu Button
			Window.draw(*SPRITES[10]);
			Window.pollEvent(interaction);
			if(button_clicked(interaction))
			{
				cout << "Easy Button was clicked!" << endl;
				display_game_state = PLAYING;
				return EASY;
			}

	}
	else
	{
			SPRITES[10]->setTexture(*TEXTURES[17]);
	}

	if(mouse_over_small(11)) //Check if Mouse coordinates are within HITBOX of exit Button
	{	
			SPRITES[11]->setTexture(*TEXTURES[20]); //Redraw new Menu Button
			Window.draw(*SPRITES[11]);
			Window.pollEvent(interaction);
			if(button_clicked(interaction))
			{
				cout << "Medium Button was clicked!" << endl;
				display_game_state = PLAYING;
				return MED;
			}

	}
	else
	{
			SPRITES[11]->setTexture(*TEXTURES[19]);
	}

	if(mouse_over_small(12)) //Check if Mouse coordinates are within HITBOX of exit Button
	{
			SPRITES[12]->setTexture(*TEXTURES[22]); //Redraw new Menu Button
			Window.draw(*SPRITES[12]);
			Window.pollEvent(interaction);
			if(button_clicked(interaction))
			{
				cout << "Hard Button was Clicked" << endl;
				display_game_state = PLAYING;
				return HARD;
			}
	}
	else
	{
			SPRITES[12]->setTexture(*TEXTURES[21]);
	}

	return NOTHING;
}

void display::highlight_num(int direction)
{
	enum{LEFT, RIGHT,UP,DOWN};
	using namespace std;

	if(direction == LEFT)
	{
		if(cursor_coord != cursor_min)
		{
			--cursor_coord;
		}
	}
	else if(direction == RIGHT)
	{
		if(cursor_coord != cursor_max)
		{
			++cursor_coord;
		}
	}
	else if(direction == UP)
	{
		if(cursor_coord - cursor_y_increments >= cursor_min)
		{
			cursor_coord -= cursor_y_increments;
		}
	}
	else if(direction == DOWN)
	{
		if(cursor_coord + cursor_y_increments <= cursor_max)
		{
			cursor_coord += cursor_y_increments;
		}
	}
}

void display::get_key_press(sf::Event interaction, Puzzle &main)
{
	if(display_game_state == PLAYING || display_game_state == LOSE_CONT)
	{
		using namespace std;
		if (interaction.type == sf::Event::KeyPressed) 
		{
			if (interaction.key.code == sf::Keyboard::Left)
			 {
				highlight_num(LEFT);
			 }
			else if(interaction.key.code == sf::Keyboard::Right)
			 {
				highlight_num(RIGHT);
			 }
			else if (interaction.key.code == sf::Keyboard::Up)
			 {
				highlight_num(UP);
			 }
			else if (interaction.key.code == sf::Keyboard::Down)
			 {
				highlight_num(DOWN);
			 }
			else if (interaction.key.code == sf::Keyboard::Num0)
			{
				draw_unum(0, main);
			}
			else if (interaction.key.code == sf::Keyboard::Num1)
			 {
				draw_unum(1, main);
			 }
			else if (interaction.key.code == sf::Keyboard::Num2)
			 {
				draw_unum(2, main);
			 }
			else if (interaction.key.code == sf::Keyboard::Num3)
			 {
				draw_unum(3, main);
			 }
			else if (interaction.key.code == sf::Keyboard::Num4)
			 {
				draw_unum(4, main);
			 }
			else if (interaction.key.code == sf::Keyboard::Num5)
			 {
				draw_unum(5, main);
			 }
			else if (interaction.key.code == sf::Keyboard::Num6)
			 {
				draw_unum(6, main);
			 }
			else if (interaction.key.code == sf::Keyboard::Num7)
			 {
				draw_unum(7, main);
			 }
			else if (interaction.key.code == sf::Keyboard::Num8)
			 {
				draw_unum(8, main);
			 }
			else if (interaction.key.code == sf::Keyboard::Num9)
			 {
				draw_unum(9, main);
			 }
		}
	}


}

void display::debug_show_puzzles(Puzzle &main, Puzzle &sol)
{
	using namespace std;
	cout << "Outputting Official Puzzle" << endl;
	for (int r = 0; r < puzzle_row_max; r++)
	{
		for(int c = 0; c < puzzle_col_max; c++)
		{
			cout << main[r][c] << " ";
		}
		cout << endl;
	}
	cout << "Outtputting Puzzle Copy" << endl;
	for (int r = 0; r < puzzle_row_max; r++)
	{
		for(int c = 0; c < puzzle_col_max; c++)
		{
			cout << PUZZLE_COPY[r][c] << " ";
		}
		cout << endl;
	}
	cout << "Outtputting Puzzle Solution" << endl;
	for (int r = 0; r < puzzle_row_max; r++)
	{
		for(int c = 0; c < puzzle_col_max; c++)
		{
			cout << sol[r][c] << " ";
		}
		cout << endl;
	}

}
