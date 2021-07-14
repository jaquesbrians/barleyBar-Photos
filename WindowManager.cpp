#include "WindowManager.h"
#include <SFML/Window.hpp>

WindowManager* WindowManager::Instance = NULL;

WindowManager* WindowManager::GetInstance()
{
	if (Instance == NULL)
	{
		Instance = new WindowManager();
	}
	return(Instance);
}

void WindowManager::StartWindowManager()
{
	_windowWidth = sf::VideoMode::getDesktopMode().width;
	_windowHeight = sf::VideoMode::getDesktopMode().height;
	photoWindow.SetUpPhotoWindow(_windowWidth, _windowHeight, _windowTitle);

	_inputPanels.push_back(CreateNewInputPanel(false));
	_inputPanels.push_back(CreateNewInputPanel(true));
	int i = 0;
}

InputPanel * WindowManager::CreateNewInputPanel(bool b)
{
	if (b)
	{
		InputPanel* inputPanel = new InputPanel();
		return inputPanel;
	}

	int winSizeWidth = 500;
	int winSizeHeight = 600;
	int windowPosWidth = (_windowWidth * 0.5f) - (winSizeWidth * 0.5f);
	int windowPosHeight = (_windowHeight * 0.5f) - (winSizeHeight * 0.5f);
	
	InputPanel* inputPanel = new InputPanel(
		sf::Vector2f(winSizeWidth, winSizeHeight), 
		sf::Vector2f(windowPosWidth, windowPosHeight),
		sf::Color::Black, 
		3);
	return inputPanel;
}

void WindowManager::UpdateWindowManager()
{
	if (photoWindow.renderWindow.isOpen())
	{
		if (photoWindow.renderWindow.pollEvent(_event) && _event.type == sf::Event::Closed)
		{
			photoWindow.renderWindow.close();
		}

		for (std::list<InputPanel*>::iterator it = _inputPanels.begin(); it != _inputPanels.end(); it++)
		{
			AddSpritesToDrawList((*it)->GetInputPanelSprites(), 1);
		}

		photoWindow.DrawCall(_currentBackGroundColor.RandomColorFadeTimeElapse(), _spriteDrawList, _textDrawList);
		_spriteDrawList.clear();
	}
}

void WindowManager::CheckInteractionWithLeftMouseClick(sf::Vector2i position)
{
	for (std::list<InputPanel*>::iterator it = _inputPanels.begin(); it != _inputPanels.end(); it++)
	{
		(*it)->OnPanelClicked(position);
	}
}

void WindowManager::AddSpriteToDrawList(sf::Sprite spriteToDraw, int priority)
{
	_spriteDrawList.push_back(spriteToDraw);
}

void WindowManager::AddTextToDrawList(sf::Text textToDraw, int priority)
{
	_textDrawList.push_back(textToDraw);
}

void WindowManager::AddSpritesToDrawList(std::list<sf::Sprite> drawSprites, int priority)
{
	for (std::list<sf::Sprite>::iterator it = drawSprites.begin(); it != drawSprites.end(); it++)
	{
		_spriteDrawList.push_back(*it);
	}
}