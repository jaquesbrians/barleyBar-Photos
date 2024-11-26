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
	DissolveEffectTrial();
}

void BarleyPhoto::SetSpritePosition(sf::Vector2f panelPositionDirections)
{
	_barleyPhotoClock.restart().asSeconds();
	sf::Vector2f updateSpritePosition = barleySprite.getPosition();
	updateSpritePosition.x = updateSpritePosition.x + panelPositionDirections.x;
	updateSpritePosition.y = updateSpritePosition.y + panelPositionDirections.y;
	barleySprite.setPosition(updateSpritePosition);
}

void BarleyPhoto::DissolveEffectTrial()
{
	sf::Clock clock;
	float alpha = 1.0f;


	// Update alpha over time
	float deltaTime = clock.restart().asSeconds();
	alpha -= deltaTime * 0.2f; // Decrease alpha (adjust speed as needed)
	if (alpha < 0.0f)
	{
		alpha = 0.0f;
	}

	// Apply the transparency to the sprite
	sf::Color spriteColor = barleySprite.getColor();
	spriteColor.a = static_cast<sf::Uint8>(alpha); // Scale to [0, 255] 
	barleySprite.setColor(spriteColor);
}
