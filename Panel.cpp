#include "Panel.h"
#include "WindowManager.h"
Drawable::Panel::Panel()
{
}

Drawable::Panel::~Panel()
{
	delete[] _panelPixels;
}

Drawable::Panel::Panel(sf::Vector2f size, sf::Vector2f position, sf::Color color)
{
	
	//_panelID = windowManager.GiveUniquePanelID();
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
		//this font directory needs to be more top level, instead of in each panel.
		_panelFontArial.loadFromFile(_fontDirectoryPath);
		_panelText.setString(_panelString);
		_panelText.setFont(_panelFontArial);
		_panelText.setFillColor(_panelTextColor);
		_panelText.setStyle(sf::Text::Bold);

		float textWidth = _panelText.getLocalBounds().width;
		float textHeight = _panelText.getLocalBounds().height;

		_textPosition.x = (_panelSize.x * 0.5f) - (textWidth * 0.5f) + _panelPosition.x;
		_textPosition.y = (_panelSize.y * 0.5f) - (textHeight * 0.5f) + _panelPosition.y;
		_panelText.setPosition(_textPosition);
	}
}

void Drawable::Panel::UpdatePanelText(std::string updatedPanelString)
{
	_panelString = updatedPanelString;
	_panelText.setString(_panelString);
	UpdateTextPosition();
}


void Drawable::Panel::UpdateTextPosition()
{
	float textWidth = _panelText.getLocalBounds().width;
	float textHeight = _panelText.getLocalBounds().height;

	_textPosition.x = (_panelSize.x * 0.5f) - (textWidth * 0.5f) + _panelPosition.x;
	_textPosition.y = (_panelSize.y * 0.5f) - (textHeight * 0.5f) + _panelPosition.y;
	_panelText.setPosition(_textPosition);
}

void Drawable::Panel::SetPanelSpritePosition(sf::Vector2f newSpritePosition)
{
	_panelPosition = newSpritePosition;
	_panelSprite.setPosition(newSpritePosition);
	UpdateTextPosition();
}

void Drawable::Panel::MovePanelPosition(sf::Vector2f panelPositionDirections)
{
	_panelPosition.x = _panelPosition.x + panelPositionDirections.x;
	_panelPosition.y = _panelPosition.y + panelPositionDirections.y;
	_panelSprite.setPosition(_panelPosition);
	UpdateTextPosition();
}

void Drawable::Panel::UpdatePanelTimers()
{
}


bool Drawable::Panel::OnPanelLeftMouseClickedUp(sf::Vector2i clickPosition)
{
	if (_marianneMath.IsPointInRectangle(_panelPosition, _panelSize, clickPosition))
	{	
		return true;
	}
	return false;
}

bool Drawable::Panel::OnPanelLeftMouseHoldDown(sf::Vector2i clickPosition)
{
	if (_marianneMath.IsPointInRectangle(_panelPosition, _panelSize, clickPosition))
	{
		_panelSprite.setColor(sf::Color::Color::Yellow);
		return true;
	}
	return false;
}

void Drawable::Panel::HidePanel()
{
}

void Drawable::Panel::ShowPanel()
{
}

void Drawable::Panel::ContainAllPanelSprites()
{
	if (_isHidden == false)
	{
		_panelSprites.clear();
		_panelSprites.push_back(_panelSprite);

		_panelTexts.clear();
		_panelTexts.push_back(_panelText);
	}
}

