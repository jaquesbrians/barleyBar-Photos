#include "BarleyPhoto.h"
#include <SFML/Graphics.hpp>

void BarleyPhoto::LoadSprite(std::string photoPathWay)
{
	/*if (!texture.loadFromFile(photoPathWay, sf::IntRect()))
	{
		//Debug or Exit
	}*/



	//sf::Image image;
	image.loadFromFile(photoPathWay);
	texture.loadFromImage(image, sf::IntRect());

	texture.setSmooth(true);
	sf::Sprite sprite(texture);
	barleySprite = sprite;
}

void BarleyPhoto::SetSpritePosition(sf::Vector2f panelPositionDirections)
{

	sf::Clock clock;

	float deltaTime = clock.restart().asSeconds();

	sf::Vector2f updateSpritePosition = barleySprite.getPosition();
	updateSpritePosition.x = updateSpritePosition.x + panelPositionDirections.x;
	updateSpritePosition.y = updateSpritePosition.y + panelPositionDirections.y;
	barleySprite.setPosition(updateSpritePosition);

	sf::Vector2f speed(100.f, 50.f);


	// Move the sprite
	//barleySprite.move(updateSpritePosition * deltaTime);



}
