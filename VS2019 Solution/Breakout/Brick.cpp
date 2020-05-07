#include "Brick.hpp"

void Brick::initialise(sf::RenderWindow& window, const int column, const int row)
{
	const int numberOfSpaces = numberOfBricksInRow - 2;
	const float spaceAvailableForBricks = window.getSize().x - numberOfSpaces * spaceBetweenBricks;
	const float brickWidth = spaceAvailableForBricks / (float) numberOfBricksInRow;

	if (row == 0 || row == 1)
	{
		brick.setFillColor(sf::Color::Red);

		type = "RED";
	}
	else if (row == 2 || row == 3)
	{
		brick.setFillColor(sf::Color(255, 128, 0));

		type = "ORANGE";
	}
	else if (row == 4 || row == 5)
	{
		brick.setFillColor(sf::Color::Green);

		type = "GREEN";
	}
	else if (row == 6 || row == 7)
	{
		brick.setFillColor(sf::Color::Yellow);

		type = "YELLOW";
	}

	
	brick.setSize(sf::Vector2f(brickWidth, brickHeight));
	brick.setPosition(sf::Vector2f(brickWidth * column + (spaceBetweenBricks - 1) * column, brickHeight * row + (spaceBetweenBricks - 1) * row + verticalOffset));
}

void Brick::update(sf::RenderWindow& window, const float elapsedTime)
{
	///
}

void Brick::render(sf::RenderWindow& window)
{
	if (!destroyed)
	{
		window.draw(brick);
	}
}