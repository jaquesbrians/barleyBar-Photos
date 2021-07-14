#pragma once
#include <SFML/Graphics.hpp>
#include <list>

class PhotoWindow
{
	private:

	public:

		sf::RenderWindow renderWindow;

		PhotoWindow();
		~PhotoWindow();
		PhotoWindow(int photoWindowWidth, int photoWindowHeight, std::string photoWindowName);
		void SetUpPhotoWindow(int photoWindowWidth, int photoWindowHeight, std::string photoWindowName);
		void DrawCall(sf::Color backgroundColor, std::list<sf::Sprite> drawSprites, std::list<sf::Text> drawTexts);
};

