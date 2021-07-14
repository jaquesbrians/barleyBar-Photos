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

		float spriteWidthPosition = 0;

		float spriteHeightPosition = 0;

		sf::Vector2u textureSize;

		void LoadSprite(std::string);
};

