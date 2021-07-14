#pragma once
#include <SFML/Graphics.hpp>

class ColorChanger
{
	private:
		sf::Color _currentColorChangerColor;
		sf::Color _newColorChangerColor;
		sf::Clock _colorClock;
		//float _colorFloatingTime = 0.00005f;
		float _colorFloatingTime = 0.05f;
		bool _currentlyChangingColors = false;

		sf::Uint8 SignedCheckForColorComponentFadeDirection(sf::Uint8 currentColorChangerComponent, sf::Uint8 newColorChangerComponent);
	
	public:
		ColorChanger();
		ColorChanger(sf::Color startingColor);
		sf::Color ChosenColorFadeTimeElapse(sf::Color newColor);
		sf::Color RandomColorFadeTimeElapse(bool randomAlphaBool = false);
		sf::Color ColorFadeToBlack();
		sf::Color ColorFadeToWhite();
		sf::Color GetCurrentColorChangerColor();
};

