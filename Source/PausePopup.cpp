#include "PausePopup.hpp"

void PausePopup::initialise(sf::RenderWindow& window, sf::Font& font)
{
	background.setFillColor(sf::Color::Blue);
	background.setSize(sf::Vector2f(window.getSize().x / 1.5, window.getSize().y / 3));
	background.setPosition(sf::Vector2f(window.getSize().x / 2 - background.getSize().x / 2, window.getSize().y / 2 - background.getSize().y / 2));

	pauseText.setFont(font);
	pauseText.setString("Press [SPACEBAR] to pause the game.");
	pauseText.setCharacterSize(15);
	pauseText.setPosition(sf::Vector2f(background.getPosition().x + background.getSize().x / 2 - pauseText.getGlobalBounds().left - pauseText.getGlobalBounds().width / 2, background.getPosition().y + background.getSize().y / 3 - pauseText.getGlobalBounds().top - pauseText.getGlobalBounds().height / 2));

	restartText.setFont(font);
	restartText.setString("Press [BACKSPACE] to restart the game.");
	restartText.setCharacterSize(15);
	restartText.setPosition(sf::Vector2f(background.getPosition().x + background.getSize().x / 2 - restartText.getGlobalBounds().left - restartText.getGlobalBounds().width / 2, background.getPosition().y + background.getSize().y / 3 * 2 - restartText.getGlobalBounds().top - restartText.getGlobalBounds().height / 2));
}

void PausePopup::render(sf::RenderWindow& window)
{
	if (gamePaused)
	{
		window.draw(background);

		window.draw(pauseText);
		window.draw(restartText);
	}
}