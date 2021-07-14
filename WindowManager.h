#pragma once
#include "PhotoWindow.h";
#include "ColorChanger.h";
#include "InputPanel.h"

using namespace Drawable;

class WindowManager
{
	private:

		static WindowManager* Instance;

		int _windowWidth = 0;
		int _windowHeight = 0;
		sf::Event _event;
		std::string _windowTitle = "Marianne";
		ColorChanger _currentBackGroundColor = sf::Color::Red;
		std::list<sf::Sprite> _spriteDrawList;	
		std::list<sf::Text> _textDrawList;

		std::list<InputPanel*> _inputPanels;

		 InputPanel * CreateNewInputPanel(bool b);

	public:

		static WindowManager* GetInstance();

		PhotoWindow photoWindow;

		void StartWindowManager();
		void UpdateWindowManager();
		void AddSpriteToDrawList(sf::Sprite, int priority);
		void AddTextToDrawList(sf::Text TextToDraw, int priority);

		void AddSpritesToDrawList(std::list<sf::Sprite> drawSprites, int priority);

		void CheckInteractionWithLeftMouseClick(sf::Vector2i position);
};

