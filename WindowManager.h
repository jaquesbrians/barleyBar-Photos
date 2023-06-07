#pragma once
#include "PhotoWindow.h";
#include "ColorChanger.h";
#include "InputPanel.h"
#include <SFML/Graphics.hpp>

using namespace Drawable;

class WindowManager
{
	private:
		static WindowManager* Instance;
		int _currentPanelIDCount = 0;
		std::map<InputPanel*, int> _hiddenInputPanelsMap;
		sf::Vector2f _hiddenPanelScale = sf::Vector2f(0.10f, 0.05f);
		sf::Vector2f _currentHiddenPanelPosition = sf::Vector2f(0, 0);
		int _currentNumberOfHiddenPanels = 0;
	
		int _windowWidth = 0;
		int _windowHeight = 0;
		sf::Event _event;
		std::string _windowTitle = "Marianne";

		ColorChanger _currentBackGroundColor = sf::Color::White;

		std::list<sf::Sprite> _spriteDrawList;	
		std::list<sf::Text> _textDrawList;
		std::list<InputPanel*> _inputPanels;
		InputPanel* _currentSeletedPanel;

		bool _closeWindow = false;

	public:
		PhotoWindow photoWindow;

	private:
		 InputPanel * CreateNewInputPanel(bool b);

	public:
		static WindowManager* GetInstance();
		void StartWindowManager();
		void UpdateWindowManager();
		void AddSpriteToDrawList(sf::Sprite, int priority);
		void AddTextToDrawList(sf::Text TextToDraw, int priority);
		void AddSpritesToDrawList(std::list<sf::Sprite> drawSprites, int priority);
		void CheckInteractionWithLeftMouseClickUp(sf::Vector2i position);
		void CheckInteractionWithLeftMouseHoldDown(sf::Vector2i position, sf::Vector2i previousPosition);

		int GiveUniquePanelID();

		void HideOrShowAPanel(InputPanel* inputPanel, bool hideAPanel);
		sf::Vector2f GiveHiddenPanelPosition(sf::Vector2f panelSize);
		sf::Vector2f GiveHiddenPanelScale();

		void CloseWindow() { _closeWindow = true; }
};

