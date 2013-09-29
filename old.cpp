//Deprecated Code
		////------------------Background Setup
		//using namespace std;
		//cout << "You are in the main menu." << endl;

		////------------------Background Setup
		//sf::Texture bg; //Create Texture object for Manoa Logo
	
		//if(!bg.loadFromFile("media/mainmenu.tga")) //Load Texture from media folder
		//{
		//	cout << "WARNING: Could not load/find Background image!" << endl;
		//}

		////Change Texture into Sprite
		//sf::Sprite bgSprite;
		//bgSprite.setTexture(bg);

		////------------------Buttons Setup
		////PLAY BUTTON----------------------------------
		//sf::Texture play; //Create Texture object for Play Button
		//sf::Texture playp; //Texture for mouse over play Button
	
		//if(!play.loadFromFile("media/play.png")) //Load Texture from media folder
		//{
		//	cout << "WARNING: Could not load/find play button!" << endl;
		//}

		//if(!playp.loadFromFile("media/playp.png")) //Load Texture from media folder
		//{
		//	cout << "WARNING: Could not load/find play button!" << endl;
		//}

		////Change Texture into Sprite
		//sf::Sprite b_play;
		//b_play.setTexture(play);
		//b_play.setPosition(150, 320); //Move to Bottom Position

		//
		////ABOUT BUTTON----------------------------------
		//sf::Texture about; //Create Texture object for About Button
		//sf::Texture aboutp; //Texture for mouse over about Button
	
		//if(!about.loadFromFile("media/about.png")) //Load Texture from media folder
		//{
		//	cout << "WARNING: Could not load/find Background image!" << endl;
		//}

		//if(!aboutp.loadFromFile("media/aboutp.png")) //Load Texture from media folder
		//{
		//	cout << "WARNING: Could not load/find play button!" << endl;
		//}

		////Change Texture into Sprite
		//sf::Sprite b_about;
		//b_about.setTexture(about);
		//b_about.setPosition(150,390); //Move to Bottom Position


		////EXIT BUTTON----------------------------------
		//sf::Texture t_exit; //Create Texture object for Exit Button
		//sf::Texture t_exitp; //Textur for mouse over exit button
	
		//if(!t_exit.loadFromFile("media/exit.png")) //Load Texture from media folder
		//{
		//	cout << "WARNING: Could not load/find Background image!" << endl;
		//}

		//if(!t_exitp.loadFromFile("media/exitp.png")) //Load Texture from media folder
		//{
		//	cout << "WARNING: Could not load/find play button!" << endl;
		//}

		////Change Texture into Sprite
		//sf::Sprite b_exit;
		//b_exit.setTexture(t_exit);
		//b_exit.setPosition(150, 460); //Move to Bottom Position
		////------------------Buttons Setup

	//sf::Text test;
	//test.setFont(font);
	//test.setString("1");
	//test.setPosition(100,40);

	//sf::Text test2;
	//test2.setFont(font);
	//test2.setString("9");
	//test2.setPosition(100,90);

	//sf::Text test3;
	//test3.setFont(font);
	//test3.setString("8");
	//test3.setPosition(145,90);


//old method of detecting keypress
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	// {
	//	cout << "Left Key is DOWN" << endl;
	//	return 0;
	// }
	//
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	// {
	//	cout << "Right Key is DOWN" << endl;
	//	return 1;
	// }

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	// {
	//	cout << "Up Key is DOWN" << endl;
	//	return 2;
	// }

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	// {
	//	cout << "Down Key is DOWN" << endl;
	//	return 3;
	// }

	//sf::Text loading;
	//loading.setFont(default_font);
	//loading.setColor(sf::Color::White);
	//loading.setString("Loading Media files..");
	////loading.setPosition(bottom_x, bottom_y);
	//window.draw(loading);
	//window.display();

	//sf::RenderWindow Window;
	//Window.create(sf::VideoMode(600, 600, 32), "Sudoku Puzzle Application", sf::Style::Close);

	////Window Settings
	//Window.setFramerateLimit(30); //Set Application to Render at 60FPS Max
	//Window.setKeyRepeatEnabled(false);

	//Create Puzzle Display Object
	//puzzle_display MAIN(Window);

	//while(Window.isOpen())
	//{
	//	//Close program if program is closed via X Box from OS
	//	sf::Event Event;
	//	while(Window.pollEvent(Event))
	//	{
	//		if(Event.type == sf::Event::Closed)
	//		{
	//			Window.close();
	//		}
	//	}
	//	//Close program if program is closed via X Box from OS
	//	MAIN.intro_disp(Window);
	//}
