#include "Ball.hpp"

void Ball::reset(sf::RenderWindow& window)
{
	initialVelocity = -500.0f;
}

void Ball::initialise(sf::RenderWindow& window)
{
	reset(window);

	velocity = sf::Vector2f(0.0f, initialVelocity);

	ball.setRadius(ballRadius);
	ball.setPosition(sf::Vector2f(window.getSize().x / 2 - ballRadius, window.getSize().y / 8 * 7 - ballRadius));

	redAlreadyHit = false;
	orangeAlreadyHit = false;
	hits = 0;
}

void Ball::checkBrickCollision(sf::RenderWindow& window, std::vector<Brick>& bricks, ScoreManager& scoreManager, Paddle& paddle)
{
	for (int i = 0; i < bricks.size(); i++)
	{
		if (!bricks[i].destroyed)
		{
			sf::FloatRect brickBoundingBox = bricks[i].getBounds();

			bool isCollision = ball.getGlobalBounds().intersects(brickBoundingBox);

			if (isCollision)
			{
				bricks[i].destroyed = true;

				if (bricks[i].getType() == "YELLOW")
				{
					scoreManager.score++;
				}
				else if (bricks[i].getType() == "GREEN")
				{
					scoreManager.score += 3;
				}
				else if (bricks[i].getType() == "ORANGE")
				{
					scoreManager.score += 5;

					if (!orangeAlreadyHit)
					{
						orangeAlreadyHit = true;

						initialVelocity += additionalVelocity;

						if (velocity.y < 0)
						{
							velocity.y += additionalVelocity;
						}
						else
						{
							velocity.y -= additionalVelocity;
						}
					}
				}
				else if (bricks[i].getType() == "RED")
				{
					scoreManager.score += 7;

					if (!redAlreadyHit)
					{
						redAlreadyHit = true;

						initialVelocity += additionalVelocity;

						if (velocity.y < 0)
						{
							velocity.y += additionalVelocity;
						}
						else
						{
							velocity.y -= additionalVelocity;
						}
					}

					paddle.shrink();
				}

				hits++;

				if (hits == 4)
				{
					initialVelocity += additionalVelocity;

					if (velocity.y < 0)
					{
						velocity.y += additionalVelocity;
					}
					else
					{
						velocity.y -= additionalVelocity;
					}
				}
				else if (hits == 12)
				{
					initialVelocity += additionalVelocity;

					if (velocity.y < 0)
					{
						velocity.y += additionalVelocity;
					}
					else
					{
						velocity.y -= additionalVelocity;
					}
				}

				sf::FloatRect leftBoundingBox(brickBoundingBox.left - 2, brickBoundingBox.top + 4, 2, brickBoundingBox.height - 8);
				sf::FloatRect rightBoundingBox(brickBoundingBox.left + brickBoundingBox.width - 2, brickBoundingBox.top + 4, 2, brickBoundingBox.height - 8);

				bool isCollisionWithBrickSide = ball.getGlobalBounds().intersects(leftBoundingBox) || ball.getGlobalBounds().intersects(rightBoundingBox);

				if (isCollisionWithBrickSide)
				{
					velocity.x = -velocity.x;
				}
				else
				{
					velocity.y = -velocity.y;
				}

				break;
			}
		}
	}
}

void Ball::checkWallCollision(sf::RenderWindow& window)
{
	bool isCollidingWithLeftWall = ball.getPosition().x < 0;

	if (isCollidingWithLeftWall)
	{
		velocity.x = -velocity.x;

		ball.setPosition(sf::Vector2f(0, ball.getPosition().y));
	}

	bool isCollidingWithRightWall = ball.getPosition().x + ball.getRadius() * 2 > window.getSize().x;

	if (isCollidingWithRightWall)
	{
		velocity.x = -velocity.x;

		ball.setPosition(sf::Vector2f(window.getSize().x - ball.getRadius() * 2, ball.getPosition().y));
	}

	bool isCollidingWithTopWall = ball.getPosition().y < 0;

	if (isCollidingWithTopWall)
	{
		velocity.y = -velocity.y;

		ball.setPosition(sf::Vector2f(ball.getPosition().x, 0));
	}
}

void Ball::checkPaddleCollision(sf::RenderWindow& window, Paddle& paddle)
{
	float horizontalOffset = (ball.getPosition().x + ball.getRadius()) - (paddle.getBounds().left + paddle.getBounds().width / 2);

	if (ball.getGlobalBounds().intersects(paddle.getBounds()))
	{
		if (horizontalOffset > 0)
		{
			velocity.x = 200.0f;
		}
		else
		{
			velocity.x = -200.0f;
		}

		velocity.x += 200.0f * (horizontalOffset / 50);
		velocity.y = -velocity.y;

		ball.setPosition(sf::Vector2f(ball.getPosition().x, paddle.getBounds().top - ball.getRadius() * 2));
	}
}

void Ball::checkMissedShot(sf::RenderWindow& window, Paddle& paddle, ScoreManager& scoreManager, bool& isViewShaking)
{
	if (ball.getPosition().y + ball.getRadius() * 2 > window.getSize().y)
	{
		scoreManager.turn--;

		initialise(window);

		isViewShaking = true;

		paddle.reset(window);
	}
}

void Ball::update(sf::RenderWindow& window, const float elapsedTime, std::vector<Brick>& bricks, Paddle& paddle, ScoreManager& scoreManager, bool& isViewShaking)
{
	ball.move(velocity * elapsedTime);

	checkBrickCollision(window, bricks, scoreManager, paddle);
	checkWallCollision(window);
	checkPaddleCollision(window, paddle);
	checkMissedShot(window, paddle, scoreManager, isViewShaking);
}

void Ball::render(sf::RenderWindow& window)
{
	window.draw(ball);
}