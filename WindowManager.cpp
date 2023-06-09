#include "WindowManager.h"
#include <SFML/Window.hpp>
#include "StartingInputPanel.h"

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

	//_inputPanels.push_back(CreateNewInputPanel(false));
	//_inputPanels.push_back(CreateNewInputPanel(true));

	int winSizeWidth = _windowWidth * 0.90f;
	int winSizeHeight = _windowHeight * 0.90f;
	int windowPosWidth = (_windowWidth * 0.5f) - (winSizeWidth * 0.5f);
	int windowPosHeight = (_windowHeight * 0.5f) - (winSizeHeight * 0.5f);

	StartingInputPanel* startingInputPanel = new StartingInputPanel(
		sf::Vector2f(winSizeWidth, winSizeHeight),
		sf::Vector2f(windowPosWidth, windowPosHeight),
		sf::Color(0.0f, 0.0f, 0.0f),
		11, InputPanel::ButtonPositions::Left);

	/*PicturePanel* picturePanel2 = new PicturePanel(
		sf::Vector2f(winSizeWidth, winSizeHeight),
		sf::Vector2f(windowPosWidth + 50, windowPosHeight + 50),
		sf::Color::Cyan,
		1, InputPanel::ButtonPositions::Center);*/

	_inputPanels.push_back(startingInputPanel);
	//_inputPanels.push_back(picturePanel2);
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
		if (photoWindow.renderWindow.pollEvent(_event) && _event.type == sf::Event::Closed || _closeWindow == true)
		{
			photoWindow.renderWindow.close();
		}

		//this is where i need to concentrate on how  we should contain all panel sprites ???

		for (std::list<InputPanel*>::iterator it = _inputPanels.begin(); it != _inputPanels.end(); it++)
		{
			AddSpritesToDrawList((*it)->GetInputPanelSprites(), 1);
			AddTextToDrawList((*it)->GetPanelText(), 2);
			(*it)->UpdatePanelTimers();
		}

		photoWindow.DrawCall(_currentBackGroundColor.RandomColorFadeTimeElapse(), _spriteDrawList, _textDrawList);
		_spriteDrawList.clear();
		_textDrawList.clear();
	}
}

void WindowManager::CheckInteractionWithLeftMouseClickUp(sf::Vector2i position)
{
	_currentSeletedPanel = NULL;

	for (std::list<InputPanel*>::reverse_iterator it = _inputPanels.rbegin(); it != _inputPanels.rend(); ++it)
	{
		if ((*it)->OnPanelLeftMouseClickedUp(position))
		{
			break;
		}
	}
}


//you are working on how to calculate z depth for two panels being on top of each other
void WindowManager::CheckInteractionWithLeftMouseHoldDown(sf::Vector2i position, sf::Vector2i previousPosition)
{
	if (_currentSeletedPanel)
	{
		if (_currentSeletedPanel->OnPanelLeftMouseHoldDown(position, previousPosition))
		{
			return;
		}
	}

	for (std::list<InputPanel*>::reverse_iterator it = _inputPanels.rbegin(); it != _inputPanels.rend(); ++it)
	{
		//need to replace this with new panel hold up functionality
		if ((*it)->OnPanelLeftMouseHoldDown(position, previousPosition))
		{
			_currentSeletedPanel = *it;
			break;
		}
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

int WindowManager::GiveUniquePanelID()
{
	_currentPanelIDCount++;
	return _currentPanelIDCount;
}

void WindowManager::HideOrShowAPanel(InputPanel* inputPanel, bool hideAPanel)
{
	if (hideAPanel)
	{
		_currentNumberOfHiddenPanels++;
		_hiddenInputPanelsMap.insert(std::pair<InputPanel*, int>(inputPanel, _currentNumberOfHiddenPanels));
		return;
	}
	
	int panelIndex = _hiddenInputPanelsMap[inputPanel];
	_hiddenInputPanelsMap.erase(inputPanel);

	if (_currentNumberOfHiddenPanels <= 1)
	{
		_currentHiddenPanelPosition = sf::Vector2f(0, 0);
		_currentNumberOfHiddenPanels = 0;
		return;
	}
	else
	{
		_currentHiddenPanelPosition = inputPanel->GetHiddenPanelPosition();

		if (panelIndex != _currentNumberOfHiddenPanels)
		{
			panelIndex++;
			for (int i = panelIndex; i <= _currentNumberOfHiddenPanels; i++)
			{
				for (auto it = _hiddenInputPanelsMap.begin(); it != _hiddenInputPanelsMap.end(); ++it)
				{
					if (it->second == i)
					{
						sf::Vector2f nextHiddenPosition = it->first->GetHiddenPanelPosition();
						it->first->HidePanel(_currentHiddenPanelPosition);
						it->second = (i - 1);
						_currentHiddenPanelPosition = nextHiddenPosition;
					}
				}
			}
		}
	}
	_currentNumberOfHiddenPanels--;
}

sf::Vector2f WindowManager::GiveHiddenPanelPosition(sf::Vector2f panelSize)
{
	sf::Vector2f hiddenPanelPosition = _currentHiddenPanelPosition;

	float extendedLength = _hiddenPanelScale.x * panelSize.x;
	_currentHiddenPanelPosition.x = _currentHiddenPanelPosition.x + extendedLength;
	if ((_currentHiddenPanelPosition.x + extendedLength) > sf::VideoMode::getDesktopMode().width)
	{
		_currentHiddenPanelPosition.x = 0;
		_currentHiddenPanelPosition.y = _currentHiddenPanelPosition.y + (_hiddenPanelScale.y * panelSize.y);
	}

	return hiddenPanelPosition;
}

sf::Vector2f WindowManager::GiveHiddenPanelScale()
{
	return _hiddenPanelScale;
}

