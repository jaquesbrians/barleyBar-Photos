#pragma once
#include <SFML/Graphics.hpp>
#include "MarianneMath.h"
#include <list>

namespace Drawable
{
	class Panel 
	{
		protected:
			
			std::string _fontDirectoryPath = "C:\\Users\\15408\\Desktop\\PhotoProject\\MarianneFonts\\arial.ttf";

			std::list<sf::Sprite> _panelSprites;
			std::list<sf::Text> _panelTexts;

			Math::MarianneMath _marianneMath;

			sf::Uint8* _panelPixels;
			sf::Vector2f _panelPosition;
			sf::Vector2f _textPosition;
			sf::Vector2f _hiddenPanelPosition;
			sf::Vector2f _panelSize;
			sf::Sprite _panelSprite;
			sf::Texture _panelTexture;
			sf::Color _panelColor;
			sf::Text _panelText;
			sf::Font _panelFontArial;
			std::string _panelString = "Hello";
			sf::Color _panelTextColor = sf::Color::Black;
			int _panelID = -1;
			bool _isHidden = false;

		protected:

		public: 

			Panel();
			Panel(sf::Vector2f size, sf::Vector2f position, sf::Color color);
			~Panel();

			virtual void ContainAllPanelSprites();
			virtual void MovePanelPosition(sf::Vector2f panelPositionDirections);
			virtual void UpdatePanelTimers();

			void SetUpPanel();
			void SetPanelSpritePosition(sf::Vector2f newSpritePosition);
			void UpdatePanelText(std::string updatedPanelString);
			void UpdateTextPosition();

			sf::Vector2f GetPanelPosition() { return _panelPosition; }
			sf::Vector2f GetHiddenPanelPosition() { return _hiddenPanelPosition; }
			sf::Vector2f GetPanelSize() { return _panelSize; }
			sf::Sprite GetPanelSprite() { return _panelSprite; }
			sf::Color GetPanelColor() { return _panelColor; }
			sf::Text GetPanelText() { return _panelText; }

			void SetPanelPosition(sf::Vector2f newPanelPosition) { _panelPosition = newPanelPosition; }
			void SetPanelSize(sf::Vector2f newPanelSize) { _panelSize = newPanelSize; }
			void SetPanelSprite(sf::Sprite newSprite) { _panelSprite = newSprite; }
			void SetPanelColor(sf::Color newPanelColor) { _panelColor = newPanelColor; }
			void SetPanelText(sf::Text newPanelText) { _panelText = newPanelText; }	

			void HidePanel();
			void ShowPanel();

			bool OnPanelLeftMouseClickedUp(sf::Vector2i clickPosition);
			bool OnPanelLeftMouseHoldDown(sf::Vector2i clickPosition);
	};
}

