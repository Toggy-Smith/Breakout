#ifndef PAUSE_POPUP_HPP
#define PAUSE_POPUP_HPP

#include "SFML/Graphics.hpp"

class PausePopup
{
	private:
		sf::RectangleShape background;

		bool gamePaused = true;

		sf::Text pauseText, restartText;

	public:
		void initialise(sf::RenderWindow& window, sf::Font& font);
		void render(sf::RenderWindow& window);
		void toggle() { gamePaused = !gamePaused; };
		bool isGamePaused() const { return gamePaused; }
};

#endif