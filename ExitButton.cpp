#include "ExitButton.h"

Drawable::ExitButton::ExitButton()
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

Drawable::ExitButton::~ExitButton()
{
}

Drawable::ExitButton::ExitButton(
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

bool Drawable::ExitButton::OnPanelLeftMouseClickedUp(sf::Vector2i clickPosition)
{
	if (_marianneMath.IsPointInRectangle(_panelPosition, _panelSize, clickPosition))
	{
		_panelColor = _isHidden ? sf::Color::Red : sf::Color::Green;
		_isHidden = !_isHidden;
		_panelSprite.setColor(_panelColor);
		return true;
	}

	return false;
}

bool Drawable::ExitButton::OnPanelLeftMouseHoldDown(sf::Vector2i clickPosition)
{
	return false;
}
