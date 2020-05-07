#include "LostPopup.hpp"

void LostPopup::initialise(sf::RenderWindow& window, sf::Font& font)
{
	background.setFillColor(sf::Color::Blue);
	background.setSize(sf::Vector2f(window.getSize().x / 1.5, window.getSize().y / 3));
	background.setPosition(sf::Vector2f(window.getSize().x / 2 - background.getSize().x / 2, window.getSize().y / 2 - background.getSize().y / 2));

	lostText.setFont(font);
	lostText.setString("You lost!");
	lostText.setCharacterSize(15);
	lostText.setPosition(sf::Vector2f(background.getPosition().x + background.getSize().x / 2 - lostText.getGlobalBounds().left - lostText.getGlobalBounds().width / 2, background.getPosition().y + background.getSize().y / 3 - lostText.getGlobalBounds().top - lostText.getGlobalBounds().height / 2));

	restartText.setFont(font);
	restartText.setString("Press [BACKSPACE] to restart the game.");
	restartText.setCharacterSize(15);
	restartText.setPosition(sf::Vector2f(background.getPosition().x + background.getSize().x / 2 - restartText.getGlobalBounds().left - restartText.getGlobalBounds().width / 2, background.getPosition().y + background.getSize().y / 3 * 2 - restartText.getGlobalBounds().top - restartText.getGlobalBounds().height / 2));
}

void LostPopup::render(sf::RenderWindow& window)
{
	if (gameLost)
	{
		window.draw(background);

		window.draw(lostText);
		window.draw(restartText);
	}
}