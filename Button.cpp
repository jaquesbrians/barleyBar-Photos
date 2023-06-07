#include "Button.h"

Drawable::Button::Button()
{
	_panelSize = sf::Vector2f(_defaultButtonWidth, _defaultButtonHeight);
	_panelPosition = sf::Vector2f(0, 0);

	_panelColor = sf::Color::White;
	_panelString = _buttonString;

	_buttonOnColor = sf::Color::Transparent;
	_buttonOffColor = sf::Color::Transparent;
	_buttonHoverColor = sf::Color::Transparent;

	SetUpPanel();
}

Drawable::Button::~Button()
{
}

Drawable::Button::Button(
	sf::Vector2f size, 
	sf::Vector2f position, 
	sf::Color baseColor,
	sf::Color buttonOnColor,
	sf::Color buttonOffColor,
	sf::Color buttonHoverColor,
	sf::Color buttonTextColor,
	std::string buttonText)
{
	_panelSize = size;
	_panelPosition = position;
	_panelColor = baseColor;
	_buttonOnColor = buttonOnColor;
	_buttonOffColor = buttonOffColor;
	_buttonHoverColor = buttonHoverColor;
	_buttonString = buttonText;
	_panelString = _buttonString;

	SetUpPanel();
}

bool Drawable::Button::OnPanelLeftMouseClickedUp(sf::Vector2i clickPosition)
{
	if (_marianneMath.IsPointInRectangle(_panelPosition, _panelSize, clickPosition))
	{
		//_panelColor = _trialToggle ? sf::Color::Color::Green : sf::Color::Color::Magenta;
		//_trialToggle = !_trialToggle;
		_panelColor = sf::Color::Color(rand() % 256, rand() % 256, rand() % 256, 255);
		_panelSprite.setColor(_panelColor);

		if (_buttonFunction)
		{
			_buttonFunction->Execute();
		}

		return true;
	}
	return false;
}