#include "InputPanel.h"

Drawable::InputPanel::~InputPanel()
{
}

Drawable::InputPanel::InputPanel()
	:
	_cornerExitButton(_defaultCornerExitButtonSize, sf::Vector2f(0.0f, 0.0f), sf::Color::Green,
		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Black, "Yo")
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

Drawable::InputPanel::InputPanel(sf::Vector2f mainPanelSize, sf::Vector2f mainPanelPosition, sf::Color mainPanelColor, int numberOfButtons)
	:
	_cornerExitButton(_defaultCornerExitButtonSize, sf::Vector2f(0.0f, 0.0f), sf::Color::Green,
	sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Black, "Yo")
{
	_panelSize = mainPanelSize;
	_panelPosition = mainPanelPosition;
	_panelColor = mainPanelColor;

	for (int i = 0; i < numberOfButtons; i++)
	{
		Button button(_defaultStandardInputButtonSize, sf::Vector2f(0.0f, 0.0f), sf::Color::Blue,
			sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Black, "Yo");

		_standardInputButtons.push_back(button);
	}

	SetUpPanel();
	InitializeInputPanelSprites();
}

void Drawable::InputPanel::InitializeInputPanelSprites()
{
	int i = _standardInputButtons.size();
	SetPanelSpritePosition(_panelPosition);
	SetUpCornerExitButton();
	SetUpStandardInputButtons();

	ContainAllPanelSprites();
}

void Drawable::InputPanel::ContainAllPanelSprites()
{
	_inputPanelSprites.clear();

	_inputPanelSprites.push_back(_panelSprite);
	_inputPanelSprites.push_back(_cornerExitButton.GetPanelSprite());
	std::list<Button>::iterator it;
	for (it = _standardInputButtons.begin(); it != _standardInputButtons.end(); ++it) 
	{
		_inputPanelSprites.push_back(it->GetPanelSprite());
	}

	//_inputPanelSprites.push_back(GetPanelText());
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
	int currentButtonYPos = inputPanelPos.y;
	for (int i = 0; i < _standardInputButtons.size(); i++)
	{
		int advanceIt = i == 0 ? i : 1;
		std::advance(it, advanceIt);
		sf::Vector2f standardButtonSize = it->GetPanelSize();
		it->SetPanelSpritePosition(sf::Vector2f(
			(inputPanelPos.x + (inputPanelSize.x * 0.5f)) - (standardButtonSize.x * 0.5f),
			(currentButtonYPos + _defaultButtonSpace)));
		currentButtonYPos = currentButtonYPos + _defaultButtonSpace + standardButtonSize.y;
	}

	//it = _standardInputButtons.begin();
	//_buttonFunctionMap.emplace(it, &Drawable::InputPanel::ButtonOneOperation);
	//https://stackoverflow.com/questions/26123838/c-mapstring-function
}

std::list<sf::Sprite> Drawable::InputPanel::GetInputPanelSprites()
{
	return _inputPanelSprites;
}

bool Drawable::InputPanel::OnPanelClicked(sf::Vector2i clickPosition)
{
	bool buttonClicked = false;
	
	buttonClicked = _cornerExitButton.OnPanelClicked(clickPosition);

	//pfunc f = funcMap[commandType];
	//(*f)(commandParam); */

	//Button::iterator it

	
	std::list<Button>::iterator it = _standardInputButtons.begin();
	if (it->OnPanelClicked(clickPosition))
	{
		//ScriptFunction scriptFunction = _buttonFunctionMap[*it];
		//(*scriptFunction);
	}


	if (!buttonClicked)
	{
		for (std::list<Button>::iterator it = _standardInputButtons.begin(); it != _standardInputButtons.end(); ++it)
		{
			buttonClicked = it->OnPanelClicked(clickPosition);
			if (buttonClicked)
			{
				break;
			}
		}
	}

	if (!buttonClicked)
	{
		buttonClicked = Panel::OnPanelClicked(clickPosition);
	}
	
	ContainAllPanelSprites();

	return buttonClicked;
}

void Drawable::InputPanel::ButtonOneOperation()
{

	int i = 5;
	//_panelColor = sf::Color::Color::Red;
	//_panelColor = sf::Color::Color(rand() % 256, rand() % 256, rand() % 256, 255);
	//_panelSprite.setColor(_panelColor);
}