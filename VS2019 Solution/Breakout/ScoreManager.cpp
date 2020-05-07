#include "ScoreManager.hpp"

void ScoreManager::initialise(sf::RenderWindow& window, sf::Font& font)
{
	text.setFont(font);
	text.setCharacterSize(30);
}

void ScoreManager::update(sf::RenderWindow& window)
{
	text.setString("Points: " + std::to_string(score) + "   Turn: " + std::to_string(turn) + "   Screen: " + std::to_string(screen));
	text.setPosition(sf::Vector2f(window.getSize().x / 2 - text.getLocalBounds().left - text.getLocalBounds().width / 2, 40 - text.getLocalBounds().top - text.getLocalBounds().height / 2));
}

void ScoreManager::render(sf::RenderWindow& window)
{
	window.draw(text);
}