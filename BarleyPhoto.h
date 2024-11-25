#pragma once
#include <SFML/Graphics.hpp>

class BarleyPhoto
{
	private:

		std::string _photoLocation;

	public:

		sf::Texture texture;
		sf::Image image;
		sf::Sprite barleySprite;
		sf::Vector2u textureSize;

		sf::Vector2f currentDisplaySize;

		//Trial Variable to get more of a const
		sf::Clock _barleyPhotoClock;

		float spriteWidthPosition = 0;
		float spriteHeightPosition = 0;

		enum PhotoMovementDirection
		{
			MOVE_RIGHT,
			MOVE_LEFT,
		};

		enum PhotoCollision
		{
			DONT_COLLIDE_WITH_PHOTOS,
			COLLIDE_WITH_PHOTOS
		};

		PhotoMovementDirection photoMovementDirection = MOVE_RIGHT;
		PhotoCollision photoCollision = DONT_COLLIDE_WITH_PHOTOS;

		void LoadSprite(std::string);
		void SetSpritePosition(sf::Vector2f panelPositionDirections);

		sf::Clock GetBarleyPhotoClock() { return _barleyPhotoClock; }
};

