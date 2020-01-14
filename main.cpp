#include "RenderWindow.h"
#include "InputComponent.h"
#include "CircleShapeComponent.h"
#include <SFML/Graphics.hpp>

/* Husk å kopier de nødvendige DLL filene inn i mappen .exe filen ligger (prosjektmappa > x64 > debug/release).
* Disse kan hentes fra SFML > Bin mappen.
* openal32.dll må være der, usikker med de andre. 
* https://www.sfml-dev.org/tutorials/2.5/start-vc.php
*/

void manageInput(InputComponent *inComp);

int main()
{
	//Window
	sf::RenderWindow window(sf::VideoMode(1440, 900), "The Gatherer");
	sf::Vector2f windowCenter = sf::Vector2f(window.getSize().x * 0.5f, window.getSize().y * 0.5f);

	// create a view with the rectangular area of the 2D world to show
	float viewSize = 75; // % of how much of the landscape should be visible relative to the window size.
	sf::View playerView(windowCenter, sf::Vector2f(window.getSize().x * (viewSize * 0.01f), window.getSize().y * (viewSize * 0.01f)));
	playerView.setCenter(windowCenter);
	window.setView(playerView);

	RenderWindow mRenderWindow;
	mRenderWindow.init(windowCenter);

	//Input
	InputComponent inputComponent;

	//Deltatime
	sf::Clock deltaClock;
	float deltaTime;

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

		manageInput(&inputComponent);
		mRenderWindow.tick(deltaTime, &inputComponent);


		// Draw calls
		for (auto tile : mRenderWindow.mTiles)
		{
			window.draw(*tile);
		}

		window.draw(*mRenderWindow.mPlayer->mCircleShapeComponent->mShape);

		window.display();
	}

	return 0;
}

void manageInput(InputComponent *inComp)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		inComp->keyW = true;
	}
	else
	{
		inComp->keyW = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		inComp->keyA = true;
	}
	else
	{
		inComp->keyA = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		inComp->keyS = true;
	}
	else
	{
		inComp->keyS = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		inComp->keyD = true;
	}
	else
	{
		inComp->keyD = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		inComp->keySpace = true;
	}
	else
	{
		inComp->keySpace = false;
	}
}