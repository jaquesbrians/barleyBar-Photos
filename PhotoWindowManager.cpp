#include "PhotoWindowManager.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <filesystem>
#include <SFML/Window.hpp>
#include "PhotoCombiner.h"

using namespace Drawable;
using namespace sf;

int PhotoWindowManager::StartPhotoWindowManager()
{
	_windowWidth = VideoMode::getDesktopMode().width;
	_windowHeight = VideoMode::getDesktopMode().height;
	_windowLayoutManager.windowWidth = _windowWidth;
	_windowLayoutManager.windowHeight = _windowHeight;
	_windowLayoutManager.SetSingleWindowLayout();
    //_windowLayoutManager.SetDoubleWindowLayout();

	_photoWindow.SetUpPhotoWindow(_windowWidth, _windowHeight, windowTitle);

	int photoIndex = 0;
	for (const auto& entry : std::filesystem::directory_iterator(_directoryPath))
	{
		BarleyPhoto barleyPhoto;
		std::string path_string{ entry.path().u8string() };
		_barleyPhotoMaps.insert(std::pair<int, BarleyPhoto>(photoIndex, barleyPhoto));
		_barleyPhotoMaps[photoIndex].LoadSprite(path_string);
		_windowLayoutManager.SetPhotoInitialPositionAndScale(_barleyPhotoMaps[photoIndex]);
		photoIndex++;
	}

	_currentBarleyPhoto = _barleyPhotoMaps[_currentBarleyPhotoIndex];
	_barleyPhotoMapSize = photoIndex;

	//panel for debug menus
	sf::Color color = sf::Color::Color(100, 200, 300, 75);
	Panel firstPanel(sf::Vector2f(_windowWidth * .25f, _windowHeight), sf::Vector2f(0, 0), color);

	sf::Clock clock;

	while (_photoWindow.renderWindow.isOpen())
	{
		while (_photoWindow.renderWindow.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				_photoWindow.renderWindow.close();
			}
		}

		if ((clock.getElapsedTime().asSeconds() >= 5.0f))
		{
			_currentBarleyPhotoIndex++;
			if (_currentBarleyPhotoIndex >= _barleyPhotoMapSize)
			{
				_currentBarleyPhotoIndex = 0;
			}
			_currentBarleyPhoto = _barleyPhotoMaps[_currentBarleyPhotoIndex];
			clock.restart();
		}

		PhotoWindowInputUpdate();
	
		switch (photoMode)
		{
		case sitStill:
			break;
		case travelRight:
			TravelRight();
			break;
		case travelLeft:
			TravelLeft();
			break;
		case travelUp:
			TravelUp();
			break;
		case travelDown:
			TravelDown();
			break;
		}

		_photoWindow.renderWindow.clear(_currentBackGroundColor.RandomColorFadeTimeElapse());
		_spriteDrawList.push_back(_currentBarleyPhoto.barleySprite);
		_spriteDrawList.push_back(firstPanel.GetPanelSprite());
		//_photoWindow.DrawCall(_currentBackGroundColor.RandomColorFadeTimeElapse(), _spriteDrawList);
		_spriteDrawList.clear();
		//_photoWindow.photoWindow.clear(_currentBackGroundColor.RandomColorFadeTimeElapse());
		//_photoWindow.photoWindow.draw(_currentBarleyPhoto.barleySprite);
		//_photoWindow.photoWindow.draw(testPanel.GetPanelSprite());
		//_photoWindow.photoWindow.display();
	}

	return 0;
}

#pragma region Photo_Input
void PhotoWindowManager::PhotoWindowInputUpdate()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		//photoMode = travelRight;
		photoMode = travelUp;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		//photoMode = travelLeft;
		photoMode = travelDown;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (_hasLeftKeyPressed == false)
		{
			_hasLeftKeyPressed = true;
			_currentBarleyPhotoIndex--;

			if (_currentBarleyPhotoIndex < 0)
			{
				_currentBarleyPhotoIndex = _barleyPhotoMapSize - 1;
			}

			_currentBarleyPhoto = _barleyPhotoMaps[_currentBarleyPhotoIndex];
		}
	}
	else
	{
		_hasLeftKeyPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (_hasRightKeyPressed == false)
		{
			_hasRightKeyPressed = true;
			_currentBarleyPhotoIndex++;
			if (_currentBarleyPhotoIndex >= _barleyPhotoMapSize)
			{
				_currentBarleyPhotoIndex = 0;
			}
			_currentBarleyPhoto = _barleyPhotoMaps[_currentBarleyPhotoIndex];
		}
	}
	else
	{
		_hasRightKeyPressed = false;
	}
}
#pragma endregion Photo_Input

#pragma region Photo_Movement
void PhotoWindowManager::TravelRight()
{
	if (_currentBarleyPhoto.spriteWidthPosition + 1 < _windowWidth - (_currentBarleyPhoto.textureSize.x * _currentBarleyPhoto.barleySprite.getScale().x))
	{
		_currentBarleyPhoto.barleySprite.setPosition(Vector2f(_currentBarleyPhoto.spriteWidthPosition++, _currentBarleyPhoto.spriteHeightPosition));
	}
	else
	{
		photoMode = travelLeft;
	}
}

void PhotoWindowManager::TravelLeft()
{
	if (_currentBarleyPhoto.spriteWidthPosition - 1 > 0)
	{
		_currentBarleyPhoto.barleySprite.setPosition(Vector2f(_currentBarleyPhoto.spriteWidthPosition--, _currentBarleyPhoto.spriteHeightPosition));
	}
	else
	{
		photoMode = travelRight;
	}
}

void PhotoWindowManager::TravelUp()
{
	if (_currentBarleyPhoto.spriteHeightPosition - 1 > 0)
	{
		_currentBarleyPhoto.barleySprite.setPosition(Vector2f(_currentBarleyPhoto.spriteWidthPosition, _currentBarleyPhoto.spriteHeightPosition--));
	}
	else
	{
		photoMode = travelDown;
	}
}

void PhotoWindowManager::TravelDown()
{
	if (_currentBarleyPhoto.spriteHeightPosition + 1 < _windowHeight - (_currentBarleyPhoto.textureSize.y * _currentBarleyPhoto.barleySprite.getScale().y))
	{
		_currentBarleyPhoto.barleySprite.setPosition(Vector2f(_currentBarleyPhoto.spriteWidthPosition, _currentBarleyPhoto.spriteHeightPosition++));
	}
	else
	{
		photoMode = travelUp;
	}
}
#pragma endregion Photo_Movement