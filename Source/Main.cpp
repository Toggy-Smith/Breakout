#include "SFML/Graphics.hpp"

#include "Paddle.hpp"
#include "Brick.hpp"
#include "Ball.hpp"

#include "ScoreManager.hpp"

#include "PausePopup.hpp"
#include "LostPopup.hpp"
#include "WonPopup.hpp"

Paddle paddle;

std::vector<Brick> bricks;

Ball ball;

ScoreManager scoreManager;

PausePopup pausePopup;
LostPopup lostPopup;
WonPopup wonPopup;

sf::Font font;

bool gainedFocus = true;

sf::Clock viewShakeClock;
bool isViewShaking = false;

void initialiseBricks(sf::RenderWindow& window)
{
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 10; column++)
		{
			Brick brick;

			brick.initialise(window, column, row);

			bricks.push_back(brick);
		}
	}
}

void initialise(sf::RenderWindow& window)
{
	paddle.initialise(window);

	initialiseBricks(window);

	ball.initialise(window);
	
	font.loadFromFile("assets/FredokaOne-Regular.ttf");

	scoreManager.initialise(window, font);

	pausePopup.initialise(window, font);

	lostPopup.initialise(window, font);

	wonPopup.initialise(window, font);
}

void handleEvents(sf::RenderWindow& window)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (event.type == sf::Event::KeyReleased && gainedFocus)
		{
			if (event.key.code == sf::Keyboard::Space && !lostPopup.gameLost)
			{
				pausePopup.toggle();
			}
			else if (event.key.code == sf::Keyboard::Backspace)
			{
				scoreManager.reset();
				
				for (int i = 0; i < bricks.size(); i++)
				{
					bricks[i].destroyed = false;
				}

				paddle.initialise(window);
				ball.initialise(window);

				lostPopup.gameLost = false;
				wonPopup.gameWon = false;
			}
		}
		else if (event.type == sf::Event::LostFocus)
		{
			gainedFocus = false;
		}
		else if (event.type == sf::Event::GainedFocus)
		{
			gainedFocus = true;
		}
	}
}

void shakeView(sf::RenderWindow& window)
{
	if (!isViewShaking)
	{
		return;
	}

	const int shakeOffset = 5;

	sf::View view;

	if (viewShakeClock.getElapsedTime().asMilliseconds() % 4 == 0)
	{
		view = sf::View(sf::FloatRect(-shakeOffset, 0, window.getSize().x, window.getSize().y));
	}
	else if (viewShakeClock.getElapsedTime().asMilliseconds() % 4 == 1)
	{
		view = sf::View(sf::FloatRect(shakeOffset, 0, window.getSize().x, window.getSize().y));
	}
	else if (viewShakeClock.getElapsedTime().asMilliseconds() % 4 == 2)
	{
		view = sf::View(sf::FloatRect(0, -shakeOffset, window.getSize().x, window.getSize().y));
	}
	else if (viewShakeClock.getElapsedTime().asMilliseconds() % 4 == 3)
	{
		view = sf::View(sf::FloatRect(0, shakeOffset, window.getSize().x, window.getSize().y));
	}

	window.setView(view);

	if (viewShakeClock.getElapsedTime().asSeconds() >= 0.25)
	{
		isViewShaking = false;
	}
}

void update(sf::RenderWindow& window)
{
	static sf::Clock updateClock;

	float elapsedTime = updateClock.getElapsedTime().asSeconds();

	if (!isViewShaking)
	{
		viewShakeClock.restart();
	}
	
	shakeView(window);

	bool isPopupShown = !(pausePopup.isGamePaused() || lostPopup.gameLost || wonPopup.gameWon);

	if (isPopupShown && gainedFocus)
	{
		paddle.update(window, elapsedTime);

		bool allDestroyed = true;

		for (int i = 0; i < bricks.size(); i++)
		{
			bricks[i].update(window, elapsedTime);

			allDestroyed = allDestroyed && bricks[i].destroyed;
		}

		if (allDestroyed)
		{
			for (int i = 0; i < bricks.size(); i++)
			{
				bricks[i].destroyed = false;
			}

			paddle.reset(window);
			ball.reset(window);
			ball.initialise(window);

			if (scoreManager.screen == 2)
			{
				wonPopup.gameWon = true;
			}
			else
			{
				scoreManager.screen++;
			}
		}

		ball.update(window, elapsedTime, bricks, paddle, scoreManager, isViewShaking);

		scoreManager.update(window);
	}

	if (scoreManager.turn == 0)
	{
		lostPopup.gameLost = true;
	}

	updateClock.restart();
}

void render(sf::RenderWindow& window)
{
	window.clear();

	paddle.render(window);

	for (int i = 0; i < bricks.size(); i++)
	{
		bricks[i].render(window);
	}

	ball.render(window);

	scoreManager.render(window);

	pausePopup.render(window);
	lostPopup.render(window);
	wonPopup.render(window);

	window.display();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 800), "Breakout", sf::Style::Close);

	initialise(window);

	while (window.isOpen())
	{
		handleEvents(window);

		update(window);

		render(window);
	}
}