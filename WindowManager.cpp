#include "WindowManager.h"
#include <SFML/Window.hpp>
#include "StartingInputPanel.h"
#include "TitleScreenInputPanel.h"

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
	Instance = this;

	_windowWidth = sf::VideoMode::getDesktopMode().width;
	_windowHeight = sf::VideoMode::getDesktopMode().height;
	photoWindow.SetUpPhotoWindow(_windowWidth, _windowHeight, _windowTitle);

	//TODO: Not sure what these are for?
	//_inputPanels.push_back(CreateNewInputPanel(false));
	//_inputPanels.push_back(CreateNewInputPanel(true));

	_winSizeWidth = _windowWidth * 0.90f;
	_winSizeHeight = _windowHeight * 0.90f;
	_windowPosWidth = (_windowWidth * 0.5f) - (_winSizeWidth * 0.5f);
	_windowPosHeight = (_windowHeight * 0.5f) - (_winSizeHeight * 0.5f);

	TitleScreenInputPanel* titleScreenInputPanel = new TitleScreenInputPanel(
		sf::Vector2f(_winSizeWidth, _winSizeHeight),
		sf::Vector2f(_windowPosWidth, _windowPosHeight),
		sf::Color(0.0f, 0.0f, 0.0f),
		1, InputPanel::ButtonPositions::Left);

	_inputPanels.push_back(titleScreenInputPanel);

	_currentSeletedPanel = titleScreenInputPanel;

	//DO NOT ERASE UNTIL WE FIGURE OUT HOW TO TRANSITION TO THIS PANEL
	/*StartingInputPanel* startingInputPanel = new StartingInputPanel(
		sf::Vector2f(winSizeWidth, winSizeHeight),
		sf::Vector2f(windowPosWidth, windowPosHeight),
		sf::Color(0.0f, 0.0f, 0.0f),
		6, InputPanel::ButtonPositions::Left);

	_inputPanels.push_back(startingInputPanel);*/
	

	for (std::list<InputPanel*>::iterator it = _inputPanels.begin(); it != _inputPanels.end(); it++)
	{
		(*it)->UpdatePanelTimers();
	}
}

void WindowManager::TrialClearPanels()
{
	_inputPanels.clear();
}

void WindowManager::ShowStartingInputPanel()
{
	_inputPanels.clear();

	StartingInputPanel* startingInputPanel = new StartingInputPanel(
		sf::Vector2f(_winSizeWidth, _winSizeHeight),
		sf::Vector2f(_windowPosWidth, _windowPosHeight),
		sf::Color(0.0f, 0.0f, 0.0f),
		6, InputPanel::ButtonPositions::Left);

	_inputPanels.push_back(startingInputPanel);

	_currentSeletedPanel = startingInputPanel;

	for (std::list<InputPanel*>::iterator it = _inputPanels.begin(); it != _inputPanels.end(); it++)
	{
		(*it)->UpdatePanelTimers();
	}
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

		_spriteDrawList.clear();
		_textDrawList.clear();

		for (std::list<InputPanel*>::iterator it = _inputPanels.begin(); it != _inputPanels.end(); it++)
		{
			(*it)->UpdatePanelTimers();
			AddSpritesToDrawList((*it)->GetInputPanelSprites(), 1);
			AddTextsToDrawList((*it)->GetInputPanelTexts(), 2);
		}

		photoWindow.DrawCall(_currentBackGroundColor.RandomColorFadeTimeElapse(), _spriteDrawList, _textDrawList);
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

void WindowManager::AddSpritesToDrawList2(std::list<sf::Sprite>& drawSprites, int priority)
{
	for (auto& sprite : drawSprites)
	{
		_spriteDrawList.push_back(sprite);
	}
}

void WindowManager::AddTextsToDrawList(std::list<sf::Text> drawTexts, int priority)
{
	for (std::list<sf::Text>::iterator it = drawTexts.begin(); it != drawTexts.end(); it++)
	{
		_textDrawList.push_back(*it);
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

