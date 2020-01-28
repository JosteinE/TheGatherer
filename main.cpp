#include "RenderWindow.h"

/* Husk å kopier de nødvendige DLL filene inn i mappen .exe filen ligger (prosjektmappa > x64 > debug/release).
* Disse kan hentes fra SFML > Bin mappen.
* openal32.dll må være der, usikker med de andre. 
* https://www.sfml-dev.org/tutorials/2.5/start-vc.php
*/

int main()
{
	// Render window
	RenderWindow mRenderWindow;
	mRenderWindow.init();

	//Delta time
	sf::Clock deltaClock;
	float deltaTime;

	//Render loop
	while (mRenderWindow.mWindow->isOpen())
	{
		sf::Event event;
		while (mRenderWindow.mWindow->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				mRenderWindow.mWindow->close();
				break;
			case sf::Event::KeyPressed:
				mRenderWindow.mInputManager.KeyboardPressed(mRenderWindow.mPlayer->mInputComponent, &event);
				break;
			case sf::Event::KeyReleased:
				mRenderWindow.mInputManager.KeyboardReleased(mRenderWindow.mPlayer->mInputComponent, &event);
				break;
			case sf::Event::MouseButtonPressed:
				mRenderWindow.mInputManager.MousePressed(mRenderWindow.mPlayer->mInputComponent, &event);
				break;
			case sf::Event::MouseButtonReleased:
				mRenderWindow.mInputManager.MouseReleased(mRenderWindow.mPlayer->mInputComponent, &event);
				break;
			case sf::Event::MouseWheelScrolled:
				mRenderWindow.zoomCamera(mRenderWindow.mInputManager.MouseWheel(mRenderWindow.mPlayer->mInputComponent, &event));
				break;
			default:
				break;
			}
		}

		sf::Time dt = deltaClock.restart();
		deltaTime = dt.asSeconds();

		mRenderWindow.tick(deltaTime);
		mRenderWindow.mWindow->display();
	}

	return 0;
}