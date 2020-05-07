#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "SFML/Graphics.hpp"

class Paddle
{
	private:
		sf::RectangleShape paddle;

		void detectIfOffScreen(sf::RenderWindow& window, const float elapsedTime);

		const float paddleSpeed = 1500.0f;

		void handleMovement(sf::RenderWindow& window, const float elapsedTime);

	public:
		void resetSize(sf::RenderWindow& window);
		void initialise(sf::RenderWindow& window);
		void reset(sf::RenderWindow& window);
		void update(sf::RenderWindow& window, const float elapsedTime);
		void render(sf::RenderWindow& window);
		
		sf::FloatRect getBounds() const { return paddle.getGlobalBounds(); }

		void shrink() { paddle.setSize(sf::Vector2f(80, 10)); }
};

#endif