#ifndef WON_POPUP_HPP
#define WON_POPUP_HPP

#include "SFML/Graphics.hpp"

class WonPopup
{
	private:
		sf::RectangleShape background;

		sf::Text wonText, restartText;

	public:
		void initialise(sf::RenderWindow& window, sf::Font& font);
		void render(sf::RenderWindow& window);

		bool gameWon = false;
};

#endif