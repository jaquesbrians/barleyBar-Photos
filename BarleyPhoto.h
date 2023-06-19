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

		float spriteWidthPosition = 0;
		float spriteHeightPosition = 0;

		enum PhotoMovementDirection
		{
			MOVE_RIGHT,
			MOVE_LEFT,
		};
		PhotoMovementDirection photoMovementDirection = MOVE_RIGHT;

		void LoadSprite(std::string);
		void SetSpritePosition(sf::Vector2f panelPositionDirections);
};

