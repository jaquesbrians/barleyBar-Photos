#pragma once
#include "Panel.h"
namespace Drawable
{
	class Button : public Panel
	{
		private:

			int _defaultButtonWidth = 200;
			int _defaultButtonHeight = 100;

		protected:

			sf::Color _buttonOnColor = sf::Color::Transparent;
			sf::Color _buttonOffColor = sf::Color::Transparent;
			sf::Color _buttonHoverColor = sf::Color::Transparent;
			std::string _buttonString = "BUTTON";

		public:

			Button();
			~Button();
			Button(
				sf::Vector2f size,
				sf::Vector2f position,
				sf::Color baseColor = sf::Color::White,
				sf::Color buttonOnColor = sf::Color::Transparent,
				sf::Color buttonOffColor = sf::Color::Transparent,
				sf::Color buttonHoverColor = sf::Color::Transparent,
				sf::Color buttonTextColor = sf::Color::Black,
				std::string buttonText = "BUTTON");

			bool OnPanelClicked(sf::Vector2i clickPosition);
	};
}

