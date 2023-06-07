#include "PhotoWindow.h"
#include <list>

PhotoWindow::PhotoWindow()
{
}

PhotoWindow::~PhotoWindow()
{
}

PhotoWindow::PhotoWindow(int photoWindowWidth, int photoWindowHeight, std::string photoWindowName)
{
}

void PhotoWindow::SetUpPhotoWindow(int photoWindowWidth, int photoWindowHeight, std::string photoWindowName)
{
	//renderWindow.create(sf::VideoMode(photoWindowWidth, photoWindowHeight), photoWindowName, sf::Style::Fullscreen);
	renderWindow.create(sf::VideoMode(photoWindowWidth, photoWindowHeight), photoWindowName);
}

void PhotoWindow::DrawCall(sf::Color backgroundColor, std::list<sf::Sprite> drawSprites, std::list<sf::Text> drawTexts)
{
	int i = 0;
	renderWindow.clear(backgroundColor);

	for (std::list<sf::Sprite>::iterator it = drawSprites.begin(); it != drawSprites.end(); it++)
	{
		renderWindow.draw(*it);
	}

	for (std::list<sf::Text>::iterator it = drawTexts.begin(); it != drawTexts.end(); it++)
	{
		renderWindow.draw(*it);
	}

	renderWindow.display();
}