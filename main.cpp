#include <SFML/Graphics.hpp>

/* Husk å kopier de nødvendige DLL filene inn i mappen .exe filen ligger (prosjektmappa > x64 > debug/release).
* Disse kan hentes fra SFML > Bin mappen.
* openal32.dll må være der, usikker med de andre. 
* https://www.sfml-dev.org/tutorials/2.5/start-vc.php
*/

int main()
{
	//Window
	sf::RenderWindow window(sf::VideoMode(1440, 900), "The Gatherer");
	sf::Vector2f windowCenter = sf::Vector2f(window.getSize().x * 0.5f, window.getSize().y * 0.5f);

	// create a view with the rectangular area of the 2D world to show
	float viewSize = 75; // % of the map
	sf::View playerView(windowCenter, sf::Vector2f(window.getSize().x * (viewSize * 0.01f), window.getSize().y * (viewSize * 0.01f)));
	playerView.setCenter(windowCenter);
	window.setView(playerView);

	//Deltatime
	sf::Clock deltaClock;
	float deltaTime;

	//Character
	float playerSize = 25.f;
	float playerSpeed = 250.f;
	float playerRunSpeed = 500.f;
	bool bRunning{ false };
	sf::CircleShape player(playerSize);
	player.setFillColor(sf::Color::Blue);
	player.setPosition(windowCenter);

	//Map
	sf::Vector2f tileSize(75.f, 75.f);
	sf::Vector2u tileSetSize(50, 50);
	sf::Vector2u tileSpacing(2, 2);

	std::vector<sf::RectangleShape*> mTiles;
	sf::RectangleShape* tile{ nullptr };
	for (int x = (tileSetSize.x * -0.5f); x < (tileSetSize.x * 0.5f); x++)
	{
		for (int y = (tileSetSize.y * -0.5f); y < (tileSetSize.y * 0.5f); y++)
		{
			tile = new sf::RectangleShape(tileSize);
			tile->setFillColor(sf::Color::Green);
			tile->setPosition(sf::Vector2f(windowCenter.x + (tile->getSize().x * x * tileSpacing.x), windowCenter.y + (tile->getSize().y * y * tileSpacing.y)));
			mTiles.push_back(tile);
		}
	}

	//Render loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Time dt = deltaClock.restart();
		deltaTime = dt.asSeconds();

		sf::Vector2f movementVector;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			// W key is pressed: move our character forward
			movementVector.y -= 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			// A key is pressed: move our character left
			movementVector.x -= 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			// S key is pressed: move our character backward
			movementVector.y += 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			// D key is pressed: move our character to the right
			movementVector.x += 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			bRunning = true;
		}
		else
		{
			bRunning = false;
		}

		if (bRunning)
		{
			player.move(movementVector * playerRunSpeed * deltaTime);
		}
		else
		{
			player.move(movementVector * playerSpeed * deltaTime);
		}
		playerView.setCenter(player.getPosition());
		window.setView(playerView);


		window.clear();
		for (auto tile : mTiles)
		{
			window.draw(*tile);
		}
		window.draw(player);
		window.display();
	}

	return 0;
}