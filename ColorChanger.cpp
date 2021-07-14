#include "ColorChanger.h"

ColorChanger::ColorChanger(){}

ColorChanger::ColorChanger(sf::Color startingColor)
{
	_currentColorChangerColor = startingColor;
	_newColorChangerColor = sf::Color::Color(rand() % 256, rand() % 256, rand() % 256);
}

sf::Color ColorChanger::ChosenColorFadeTimeElapse(sf::Color newColor)
{
	if ((_colorClock.getElapsedTime().asSeconds() >= _colorFloatingTime))
	{
		if (_currentColorChangerColor == newColor)
		{
			return _currentColorChangerColor;
		}

		if (_newColorChangerColor != newColor)
		{
			_newColorChangerColor = newColor;
		}

		_currentColorChangerColor.r = SignedCheckForColorComponentFadeDirection(_currentColorChangerColor.r, _newColorChangerColor.r);
		_currentColorChangerColor.g = SignedCheckForColorComponentFadeDirection(_currentColorChangerColor.g, _newColorChangerColor.g);
		_currentColorChangerColor.b = SignedCheckForColorComponentFadeDirection(_currentColorChangerColor.b, _newColorChangerColor.b);
		_currentColorChangerColor.a = SignedCheckForColorComponentFadeDirection(_currentColorChangerColor.a, _newColorChangerColor.a);
		_colorClock.restart();
	}

	return _currentColorChangerColor;
}

sf::Color ColorChanger::RandomColorFadeTimeElapse(bool randomAlphaBool)
{
	if ((_colorClock.getElapsedTime().asSeconds() >= _colorFloatingTime))
	{
		if (_currentColorChangerColor == _newColorChangerColor)
		{
			sf::Uint8 randomAlpha = randomAlphaBool ? rand() % 256 : 255;
			_newColorChangerColor = sf::Color::Color(rand() % 256, rand() % 256, rand() % 256, randomAlpha);
		}

		if ((_colorClock.getElapsedTime().asSeconds() >= _colorFloatingTime))
		{
			_currentColorChangerColor.r = SignedCheckForColorComponentFadeDirection(_currentColorChangerColor.r, _newColorChangerColor.r);
			_currentColorChangerColor.g = SignedCheckForColorComponentFadeDirection(_currentColorChangerColor.g, _newColorChangerColor.g);
			_currentColorChangerColor.b = SignedCheckForColorComponentFadeDirection(_currentColorChangerColor.b, _newColorChangerColor.b);
			_currentColorChangerColor.a = SignedCheckForColorComponentFadeDirection(_currentColorChangerColor.a, _newColorChangerColor.a);
			_colorClock.restart();
		}
	}

	return _currentColorChangerColor;
}

sf::Color ColorChanger::ColorFadeToBlack()
{
	if (_currentColorChangerColor == sf::Color::Black)
	{
		return _currentColorChangerColor;
	}

	if ((_colorClock.getElapsedTime().asSeconds() >= _colorFloatingTime))
	{
		_currentColorChangerColor.r = (_currentColorChangerColor.r == 0) ? 0 : _currentColorChangerColor.r - 1;
		_currentColorChangerColor.g = (_currentColorChangerColor.g == 0) ? 0 : _currentColorChangerColor.g - 1;
		_currentColorChangerColor.b = (_currentColorChangerColor.b == 0) ? 0 : _currentColorChangerColor.b - 1;
		_currentColorChangerColor.a = (_currentColorChangerColor.a == 0) ? 0 : _currentColorChangerColor.a - 1;
		_colorClock.restart();
	}

	return _currentColorChangerColor;
}

sf::Color ColorChanger::ColorFadeToWhite()
{
	if (_currentColorChangerColor == sf::Color::White)
	{
		return _currentColorChangerColor;
	}

	if ((_colorClock.getElapsedTime().asSeconds() >= _colorFloatingTime))
	{
		_currentColorChangerColor.r = (_currentColorChangerColor.r == 255) ? 255 : _currentColorChangerColor.r + 1;
		_currentColorChangerColor.g = (_currentColorChangerColor.g == 255) ? 255 : _currentColorChangerColor.g + 1;
		_currentColorChangerColor.b = (_currentColorChangerColor.b == 255) ? 255 : _currentColorChangerColor.b + 1;
		_currentColorChangerColor.a = (_currentColorChangerColor.a == 255) ? 255 : _currentColorChangerColor.a + 1;
		_colorClock.restart();
	}

	return _currentColorChangerColor;
}

sf::Uint8 ColorChanger::SignedCheckForColorComponentFadeDirection(sf::Uint8 currentColorChangerComponent, sf::Uint8 newColorChangerComponent)
{
	int delta = currentColorChangerComponent - newColorChangerComponent;
	if (delta != 0)
	{
		currentColorChangerComponent = (delta < 0) ? currentColorChangerComponent + 1 : currentColorChangerComponent - 1;
	}

	return currentColorChangerComponent;
}

sf::Color ColorChanger::GetCurrentColorChangerColor()
{
	return _currentColorChangerColor;
}