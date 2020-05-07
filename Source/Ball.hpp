#ifndef BALL_HPP
#define BALL_HPP

#include "SFML/Graphics.hpp"

#include "Brick.hpp"
#include "Paddle.hpp"
#include "ScoreManager.hpp"

class Ball
{
	private:
		sf::CircleShape ball;

		const int ballRadius = 10;

		sf::Vector2f velocity;

		float initialVelocity;

		float additionalVelocity = -50.0f;

		bool redAlreadyHit;
		bool orangeAlreadyHit;
		int hits;

		void checkBrickCollision(sf::RenderWindow& window, std::vector<Brick>& bricks, ScoreManager& scoreManager, Paddle& paddle);
		void checkWallCollision(sf::RenderWindow& window);
		void checkPaddleCollision(sf::RenderWindow& window, Paddle& paddle);
		void checkMissedShot(sf::RenderWindow& window, Paddle& paddle, ScoreManager& scoreManager, bool& isViewShaking);

	public:
		void reset(sf::RenderWindow& window);
		void initialise(sf::RenderWindow& window);
		void update(sf::RenderWindow& window, const float elapsedTime, std::vector<Brick>& bricks, Paddle& paddle, ScoreManager& scoreManager, bool& isViewShaking);
		void render(sf::RenderWindow& window);
};

#endif