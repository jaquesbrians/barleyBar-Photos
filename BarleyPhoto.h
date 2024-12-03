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
		sf::Clock _barleyPhotoClock;

		float spriteWidthPosition = 0;
		float spriteHeightPosition = 0;


		bool trialfadeout = false;

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

		enum PhotoAlphaSetting
		{
			ALPHA_ZERO,
			FULL_ALPHA,
			ALPHA_FADE_IN,
			ALPHA_FADE_OUT
		};
		

		PhotoMovementDirection photoMovementDirection = MOVE_RIGHT;
		PhotoCollision photoCollision = DONT_COLLIDE_WITH_PHOTOS;
		PhotoAlphaSetting photoAlphaSetting = ALPHA_ZERO;

		void LoadSprite(std::string);
		void SetSpritePosition(sf::Vector2f panelPositionDirections);
		void BarleyPhotoFader(double deltaTime);

		sf::Clock GetBarleyPhotoClock() { return _barleyPhotoClock; }
};

