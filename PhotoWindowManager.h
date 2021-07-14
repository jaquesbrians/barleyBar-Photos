#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include <list>
#include "BarleyPhoto.h"
#include "WindowLayoutManager.h"
#include "ColorChanger.h"
#include "Panel.h"
#include "PhotoWindow.h";

using namespace Drawable;

class PhotoWindowManager
{
	private:

		std::list<sf::Sprite> _spriteDrawList;

		PhotoWindow _photoWindow;

		int _windowWidth;

		int _windowHeight;

		WindowLayoutManager _windowLayoutManager;

		std::string windowTitle = "barleBar Photos";

		std::string _directoryPath = "C:\\Users\\15408\\Desktop\\Guarantees\\";

		std::map<int, BarleyPhoto> _barleyPhotoMaps;

		BarleyPhoto _currentBarleyPhoto;

		int _currentBarleyPhotoIndex = 0;

		int _barleyPhotoMapSize = 0;

		bool _hasLeftKeyPressed = false;

		bool _hasRightKeyPressed = false;

		sf::Event event;

		void TravelRight();
		void TravelLeft();
		void TravelUp();
		void TravelDown();

		enum PhotoMode
		{
			sitStill,
			travelRight,
			travelLeft,
			travelUp,
			travelDown
		};

		PhotoMode photoMode = sitStill;

		ColorChanger _currentBackGroundColor = sf::Color::Red;


	public:

		int StartPhotoWindowManager();
		void PhotoWindowInputUpdate();
};