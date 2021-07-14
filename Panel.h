#pragma once
#include <SFML/Graphics.hpp>
#include "MarianneMath.h"

namespace Drawable
{
	class Panel 
	{
		private:

			std::string _fontDirectoryPath = "C:\\Users\\15408\\Desktop\\MarianneFonts\\arial.ttf";

			int _trialToggle = false;

		protected:

			Math::MarianneMath _marianneMath;
			sf::Uint8* _panelPixels;
			sf::Vector2f _panelPosition;
			sf::Vector2f _panelSize;
			sf::Sprite _panelSprite;
			sf::Texture _panelTexture;
			sf::Color _panelColor;
			sf::Text _panelText;
			sf::Font _panelFontArial;
			std::string _panelString;
			sf::Color _panelTextColor = sf::Color::Black;

			void SetUpPanel();

		public: 

			Panel();
			Panel(sf::Vector2f size, sf::Vector2f position, sf::Color color);
			~Panel();

			void SetPanelSpritePosition(sf::Vector2f newSpritePosition);

			sf::Vector2f GetPanelPosition() { return _panelPosition; }
			sf::Vector2f GetPanelSize() { return _panelSize; }
			sf::Sprite GetPanelSprite() { return _panelSprite; }
			sf::Color GetPanelColor() { return _panelColor; }
			sf::Text GetPanelText() { return _panelText; }

			void SetPanelPosition(sf::Vector2f newPanelPosition) { _panelPosition = newPanelPosition; }
			void SetPanelSize(sf::Vector2f newPanelSize) { _panelSize = newPanelSize; }
			void SetPanelSprite(sf::Sprite newSprite) { _panelSprite = newSprite; }
			void SetPanelColor(sf::Color newPanelColor) { _panelColor = newPanelColor; }
			void SetPanelText(sf::Text newPanelText) { _panelText = newPanelText; }	

			bool OnPanelClicked(sf::Vector2i clickPosition);
	};
}

