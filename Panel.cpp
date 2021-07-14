#include "Panel.h"
Drawable::Panel::Panel()
{
}

Drawable::Panel::~Panel()
{
	delete[] _panelPixels;
}

Drawable::Panel::Panel(sf::Vector2f size, sf::Vector2f position, sf::Color color)
{
	_panelSize = size;
	_panelPosition = position;
	_panelColor = color;
	SetUpPanel();
}

void Drawable::Panel::SetUpPanel()
{
	_panelPixels = new sf::Uint8[_panelSize.x * _panelSize.y * 4];

	unsigned long int PanelSizeProduct = _panelSize.x * _panelSize.y;

	for (int x = 0; x < (PanelSizeProduct); x += _panelSize.y)
	{
		for (int y = 0; y < _panelSize.y; y++)
		{
			_panelPixels[(y + x) * 4] = 255;
			_panelPixels[(y + x) * 4 + 1] = 255;
			_panelPixels[(y + x) * 4 + 2] = 255;
			_panelPixels[(y + x) * 4 + 3] = 255;
		}
	}

	_panelTexture.create(_panelSize.x, _panelSize.y);
	_panelTexture.update(_panelPixels);
	_panelSprite.setTexture(_panelTexture);
	_panelSprite.setColor(_panelColor);
	_panelSprite.setPosition(_panelPosition);


	if (!_panelString.empty())
	{
		_panelFontArial.loadFromFile(_fontDirectoryPath);
		_panelText.setString(_panelString);
		_panelText.setFont(_panelFontArial);
		_panelText.setFillColor(_panelTextColor);

		float textWidth = _panelText.getLocalBounds().width;
		float textHeight = _panelText.getLocalBounds().height;

		_panelText.setPosition(
			(_panelSize.x * 0.5f) - (textWidth * 0.5f) + _panelPosition.x
			, (_panelSize.y * 0.5f) - (textHeight * 0.5f) + _panelPosition.y);
		_panelText.setStyle(sf::Text::Bold);
	}
}

void Drawable::Panel::SetPanelSpritePosition(sf::Vector2f newSpritePosition)
{
	_panelPosition = newSpritePosition;
	_panelSprite.setPosition(newSpritePosition);
}

bool Drawable::Panel::OnPanelClicked(sf::Vector2i clickPosition)
{
	if (_marianneMath.IsPointInRectangle(_panelPosition, _panelSize, clickPosition))
	{
		_panelColor = _trialToggle ? sf::Color::Color::Green : sf::Color::Color::Magenta;
		_trialToggle = !_trialToggle;
		_panelSprite.setColor(_panelColor);
		return true;
	}
	return false;
}

