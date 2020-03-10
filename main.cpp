#include "RenderWindow.h"

#include "GameStateComponent.h"
#include "GameStateManager.h"

/* Husk å kopier de nødvendige DLL filene inn i mappen .exe filen ligger (prosjektmappa > x64 > debug/release).
* Disse kan hentes fra SFML > Bin mappen.
* openal32.dll må være der, usikker med de andre. 
* https://www.sfml-dev.org/tutorials/2.5/start-vc.php
*/

/* TODAYS PLAN
*	States: Game & Menu(s)
*	Night mode on a timer
*	Player HP, fail state, combat?
*	Multiple lights
*/

int main()
{
	// TEST!
	GameStateComponent mStateComp;
	GameStateManager mStateManager;


	// Render window
	RenderWindow mRenderWindow;
	mRenderWindow.initNewGame();

	//Delta time
	sf::Clock deltaClock;
	float secondTracker = 0.f;

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

				// TEMP
				if (event.key.code == sf::Keyboard::Escape)
					mRenderWindow.mWindow->close();
				else if (event.key.code == sf::Keyboard::E)
				{
					mStateComp.currentState = STATE_PLAY;
					mRenderWindow.initNewGame();
				}
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
		secondTracker += dt.asSeconds();

		if (secondTracker >= 1.f)
		{
			mRenderWindow.addSeconds(3600, dt.asSeconds());
			secondTracker = 0;
		}

		mStateManager.runState(&mRenderWindow, &mStateComp, dt.asSeconds());
		//mRenderWindow.tick(dt.asSeconds());
		mRenderWindow.mWindow->display();
	}

	return 0;
}