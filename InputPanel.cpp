#include "InputPanel.h"
#include "WindowManager.h"

Drawable::InputPanel::~InputPanel()
{
}

Drawable::InputPanel::InputPanel()
	:
	_cornerExitButton(_defaultCornerExitButtonSize, sf::Vector2f(0.0f, 0.0f), sf::Color::Red,
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Black, "X")
{
	_panelSize = _defaultInputPanelSize;
	_panelPosition = _defaultInputPanelPosition;
	_panelColor = _defaultInputPanelColor;

	Button button(_defaultStandardInputButtonSize, sf::Vector2f(0.0f, 0.0f), sf::Color::Yellow,
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Black, "Yo");

	_standardInputButtons.push_back(button);

	SetUpPanel();
	InitializeInputPanelSprites();
}

Drawable::InputPanel::InputPanel(sf::Vector2f mainPanelSize, sf::Vector2f mainPanelPosition, sf::Color mainPanelColor, 
	int numberOfButtons, ButtonPositions buttonPositions)
	:
	_cornerExitButton(_defaultCornerExitButtonSize, sf::Vector2f(0.0f, 0.0f), sf::Color::Red,
	sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Black, "X")
{
	_panelSize = mainPanelSize;
	_panelPosition = mainPanelPosition;
	_panelColor = mainPanelColor;
	_defaultButtonPositions = buttonPositions;

	for (int i = 0; i < numberOfButtons; i++)
	{
		Button button(_defaultStandardInputButtonSize, sf::Vector2f(0.0f, 0.0f), sf::Color::Blue,
			sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Red, "Nothing Yet", true);

		_standardInputButtons.push_back(button);
	}

	//Interesting development - figure out a better way to set up buttons due to font's loosing scope.
	//Meaning Maybe create normal buttons and then configure them once they are in the list, instead of SeT Up Panel Twice
	//20230610

	std::list<Button>::iterator it;
	for (it = _standardInputButtons.begin(); it != _standardInputButtons.end(); ++it)
	{
		it->SetUpPanel();
	}

	SetUpPanel();
	InitializeInputPanelSprites();
}

void Drawable::InputPanel::InitializeInputPanelSprites()
{
	SetPanelSpritePosition(_panelPosition);
	SetUpCornerExitButton();
	SetUpStandardInputButtons();

	//ContainAllPanelSprites();
}

void Drawable::InputPanel::ContainAllPanelSprites()
{
	this->Panel::ContainAllPanelSprites();

	if (_isHidden == false)
	{
		_panelSprites.push_back(_cornerExitButton.GetPanelSprite());
		_panelTexts.push_back(_cornerExitButton.GetPanelText());

		std::list<Button>::iterator it;
		for (it = _standardInputButtons.begin(); it != _standardInputButtons.end(); ++it)
		{
			_panelSprites.push_back(it->GetPanelSprite());
			_panelTexts.push_back(it->GetPanelText());
		}
	}
}

void Drawable::InputPanel::UpdatePanelTimers()
{
}

void Drawable::InputPanel::SetUpCornerExitButton()
{
	sf::Vector2f inputPanelPos = GetPanelPosition();
	sf::Vector2f inputPanelSize = GetPanelSize();
	sf::Vector2f cornerButtonSize = _cornerExitButton.GetPanelSize();
	_cornerExitButton.SetPanelSpritePosition(sf::Vector2f(
		(inputPanelPos.x + inputPanelSize.x) - cornerButtonSize.x, 
		inputPanelPos.y));
}

void Drawable::InputPanel::SetUpStandardInputButtons()
{
	sf::Vector2f inputPanelPos = GetPanelPosition();
	sf::Vector2f inputPanelSize = GetPanelSize();
	std::list<Button>::iterator it = _standardInputButtons.begin();
	int currentButtonYPos = inputPanelPos.y + _defaultButtonSpace;
	for (int i = 0; i < _standardInputButtons.size(); i++)
	{
		int advanceIt = i == 0 ? i : 1;
		std::advance(it, advanceIt);
		sf::Vector2f standardButtonSize = it->GetPanelSize();

		float x = 0;
		float y = currentButtonYPos + _defaultButtonSpace;

		if (_defaultButtonPositions == Center)
		{
			x = inputPanelPos.x + (inputPanelSize.x * 0.5f) - (standardButtonSize.x * 0.5f);
		}
		else if (_defaultButtonPositions == Left)
		{
			x = inputPanelPos.x + _defaultButtonSpace * 2;
		}
		else if (_defaultButtonPositions == Right)
		{
			x = inputPanelPos.x + _defaultButtonSpace + (standardButtonSize.x * 0.5f);
		}

		it->SetPanelSpritePosition(sf::Vector2f(x, y));

		currentButtonYPos = currentButtonYPos + _defaultButtonSpace + standardButtonSize.y;
	}
}

std::list<sf::Sprite>& Drawable::InputPanel::GetInputPanelSprites()
{
	ContainAllPanelSprites();
	return _panelSprites;  
}

std::list<sf::Text> Drawable::InputPanel::GetInputPanelTexts()
{
	return _panelTexts;
}

void Drawable::InputPanel::HidePanel(sf::Vector2f hiddenPanelPosition)
{
	_hiddenPanelPosition = hiddenPanelPosition;
	_panelSprite.setPosition(_hiddenPanelPosition);

	sf::Vector2f hiddenPanelScale = WindowManager::GetInstance()->GiveHiddenPanelScale();
	_panelSprite.setScale(hiddenPanelScale);

	float cornerButtonHiddenX = _hiddenPanelPosition.x + (GetPanelSize().x * hiddenPanelScale.x) - _cornerExitButton.GetPanelSize().x;
	_cornerExitButton.SetPanelSpritePosition(sf::Vector2f(cornerButtonHiddenX, _hiddenPanelPosition.y));
	_panelSprites.clear();
	_panelSprites.push_back(_panelSprite);
	_panelSprites.push_back(_cornerExitButton.GetPanelSprite());
}


void Drawable::InputPanel::ShowPanel()
{
	_isHidden = false;
	WindowManager::GetInstance()->HideOrShowAPanel(this, false);
	_panelSprite.setPosition(_panelPosition);
	_panelSprite.setScale(sf::Vector2f(1, 1));
	SetUpCornerExitButton();
	//ContainAllPanelSprites();
}

bool Drawable::InputPanel::OnPanelLeftMouseClickedUp(sf::Vector2i clickPosition)
{
	bool buttonClicked = false;
	
	buttonClicked = _cornerExitButton.OnPanelLeftMouseClickedUp(clickPosition);

	if (buttonClicked)
	{
		if (_isHidden == false)
		{
			_isHidden = true;
			WindowManager::GetInstance()->HideOrShowAPanel(this, true);
			HidePanel(WindowManager::GetInstance()->GiveHiddenPanelPosition(_panelSize));
		}
		else
		{
			ShowPanel();
		}
		return true;
	}


	if (!buttonClicked)
	{
		for (std::list<Button>::iterator it = _standardInputButtons.begin(); it != _standardInputButtons.end(); ++it)
		{
			buttonClicked = it->OnPanelLeftMouseClickedUp(clickPosition);
			if (buttonClicked)
			{
				break;
			}
		}
	}

	if (_marianneMath.IsPointInRectangle(_panelPosition, _panelSize, clickPosition))
	{
		_panelSprite.setColor(_panelColor);
		buttonClicked = true;
	}
	
	//ContainAllPanelSprites();

	return buttonClicked;
}

bool Drawable::InputPanel::OnPanelLeftMouseHoldDown(sf::Vector2i clickPosition, sf::Vector2i previousClickPosition)
{
	if (_isHidden)
	{
		return false;
	}

	bool panelClicked = false;
	panelClicked = _marianneMath.IsPointInRectangle(_panelPosition, _panelSize, clickPosition);

	if (panelClicked && IsPointInInputPanelButtons(clickPosition) == false)
	{
		_panelSprite.setColor(sf::Color::Color::White);
		float x = clickPosition.x - previousClickPosition.x;
		float y = clickPosition.y - previousClickPosition.y;
		sf::Vector2f movePanelDirections(x, y);
		DragPanelPosition(movePanelDirections);
		_cornerExitButton.DragPanelPosition(movePanelDirections);
		std::list<Button>::iterator it;
		for (it = _standardInputButtons.begin(); it != _standardInputButtons.end(); ++it)
		{
			it->DragPanelPosition(movePanelDirections);
		}

		//ContainAllPanelSprites();
		return true;
	}
	return panelClicked;
}

bool Drawable::InputPanel::IsPointInInputPanelButtons(sf::Vector2i clickPosition)
{
	if (_marianneMath.IsPointInRectangle(_cornerExitButton.GetPanelPosition(), _cornerExitButton.GetPanelSize(), clickPosition))
	{
		return true;
	}

	std::list<Button>::iterator it;
	for (it = _standardInputButtons.begin(); it != _standardInputButtons.end(); ++it)
	{
		if (_marianneMath.IsPointInRectangle(it->GetPanelPosition(), it->GetPanelSize(), clickPosition))
		{
			return true;
		}
	}

	return false;
}