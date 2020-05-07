#include "Paddle.hpp"

void Paddle::resetSize(sf::RenderWindow& window)
{
	paddle.setSize(sf::Vector2f(120, 10));
}

void Paddle::initialise(sf::RenderWindow& window)
{
	const int offsetFromScreenBottom = 50;

	paddle.setFillColor(sf::Color::White);
	resetSize(window);
	paddle.setPosition(sf::Vector2f(window.getSize().x / 2 - paddle.getSize().x / 2, window.getSize().y - paddle.getSize().y - offsetFromScreenBottom));
}

void Paddle::reset(sf::RenderWindow& window)
{
	paddle.setPosition(sf::Vector2f(window.getSize().x / 2 - paddle.getSize().x / 2, paddle.getPosition().y));
}

void Paddle::detectIfOffScreen(sf::RenderWindow& window, const float elapsedTime)
{
	bool isPaddleOffLeftSideOfScreen = paddle.getPosition().x < 0 ? true : false;

	if (isPaddleOffLeftSideOfScreen)
	{
		paddle.setPosition(sf::Vector2f(0, paddle.getPosition().y));
	}

	bool isPaddleOffRightSideOfScreen = paddle.getPosition().x + paddle.getSize().x > window.getSize().x ? true : false;

	if (isPaddleOffRightSideOfScreen)
	{
		paddle.setPosition(sf::Vector2f(window.getSize().x - paddle.getSize().x, paddle.getPosition().y));
	}
}

void Paddle::handleMovement(sf::RenderWindow& window, const float elapsedTime)
{
	bool isLeftKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A);

	if (isLeftKeyDown)
	{
		paddle.move(sf::Vector2f(-(paddleSpeed * elapsedTime), 0));
	}

	bool isRightKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	if (isRightKeyDown)
	{
		paddle.move(sf::Vector2f(paddleSpeed * elapsedTime, 0));
	}

	detectIfOffScreen(window, elapsedTime);
}

void Paddle::update(sf::RenderWindow& window, const float elapsedTime)
{
	handleMovement(window, elapsedTime);
}

void Paddle::render(sf::RenderWindow& window)
{
	window.draw(paddle);
}