// --------------------------------------
// Includes
// --------------------------------------
// Libraries
#include <SFML/Graphics.hpp>

// Project Includes
#include "AssetManager.h"
#include "Player.h"


int main()
{
	// --------------------------------------
	// Game Setup
	// --------------------------------------

	// Render Window creation
	sf::RenderWindow gameWindow;
	gameWindow.create(sf::VideoMode::getDesktopMode(), "Canabalt",
		sf::Style::Titlebar | sf::Style::Close);

	// Timer functionality
	sf::Clock gameClock;

	// Create AssetManager
	AssetManager assets;

	// Create player
	Player player;
	player.Spawn();

	//Create Camera
	sf::View camera = gameWindow.getDefaultView();

	// end game setup
	// --------------------------------------


	// --------------------------------------
	// Game Loop
	// --------------------------------------
	while (gameWindow.isOpen())
	{
		// --------------------------------------
		// Input
		// --------------------------------------
		sf::Event event;
		while (gameWindow.pollEvent(event))
		{
			//Pass input to game objects
			player.Input(event);

			if (event.type == sf::Event::Closed)
			{
				gameWindow.close();
			} // End if (closed)
		} // end event polling loop

		// end input
		// --------------------------------------


		// --------------------------------------
		// Update
		// --------------------------------------
		sf::Time frameTime = gameClock.restart();

		player.Update(frameTime);

		//Update camera position
		camera.setCenter(
			player.GetPosition().x + camera.getSize().x * 0.4f,
			camera.getCenter().y
		);

		// end update
		// --------------------------------------



		// --------------------------------------
		// Draw
		// --------------------------------------

		// Clear the window to a single colour
		gameWindow.clear();

		// Draw Everything
		//Draw game world using the camera
		gameWindow.setView(camera);

		player.Draw(gameWindow);

		//Draw the UI to the window
		gameWindow.setView(gameWindow.getDefaultView());



		// Display the window contents to the screen
		gameWindow.display();

		// end draw
		// --------------------------------------

	} // end of the game while loop

	// end game loop
	// --------------------------------------

	// exit point for the program
	return 0;

} // end of the main() function
