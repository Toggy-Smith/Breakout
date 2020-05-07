#ifndef LOST_POPUP_HPP
#define LOST_POPUP_HPP

#include "SFML/Graphics.hpp"

class LostPopup
{
	private:
		sf::RectangleShape background;

		sf::Text lostText, restartText;

	public:
		void initialise(sf::RenderWindow& window, sf::Font& font);
		void render(sf::RenderWindow& window);
		
		bool gameLost = false;
};

#endif