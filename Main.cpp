// --------------------------------------
// Includes
// --------------------------------------
// Libraries
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <vector>

// Project Includes
#include "AssetManager.h"
#include "Player.h"
#include "Platform.h"



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

	// Seed random number genrator
	srand(time(NULL));

	// Create player
	Player player;
	player.Spawn();

	//Create Camera
	sf::View camera = gameWindow.getDefaultView();

	//Create Platform
	std::vector<Platform> platforms;
	for (int i = 0; i < 5; ++i)
	{
		platforms.push_back(Platform());
		platforms.back().Spawn();
	}

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

		//Collision Detection
		std::vector<sf::FloatRect> platformCollider;
		for (auto it = platforms.begin(), it != platforms.end(); ++it)
		{
			platformColliders.push_back(it->GetCollider());
		}
		player.HandleCollison(platforms.GetCollider());

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
		for (auto it = platforms.begin(), it != platforms.end(); ++it)
		{
			it->Draw(gameWindow);
		}

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
