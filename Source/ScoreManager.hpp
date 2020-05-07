#ifndef SCORE_MANAGER_HPP
#define SCORE_MANAGER_HPP

#include "SFML/Graphics.hpp"

#include <string>

class ScoreManager
{
	private:
		sf::Text text;

	public:
		void initialise(sf::RenderWindow& window, sf::Font& font);
		void update(sf::RenderWindow& window);
		void render(sf::RenderWindow& window);

		int score = 0;
		int turn = 3;
		int screen = 1;

		void reset() { score = 0; turn = 3; screen = 1; }
};

#endif