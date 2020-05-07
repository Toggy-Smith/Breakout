#ifndef BRICK_HPP
#define BRICK_HPP

#include "SFML/Graphics.hpp"

#include <string>

class Brick
{
	private:
		sf::RectangleShape brick;

		const int spaceBetweenBricks = 10;
		const int numberOfBricksInRow = 10;

		const int brickHeight = 15;
		const int verticalOffset = 80;

		std::string type;

	public:
		void initialise(sf::RenderWindow& window, const int column, const int row);
		void update(sf::RenderWindow& window, const float elapsedTime);
		void render(sf::RenderWindow& window);

		bool destroyed = false;

		sf::FloatRect getBounds() const { return brick.getGlobalBounds(); }
		
		const std::string& getType() const
		{
			return type;
		}
};

#endif