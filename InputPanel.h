#pragma once

#ifndef __INPUTPANEL_H_INCLUDED_
#define __INPUTPANEL_H_INCLUDED_

#include "Panel.h"
#include "Button.h"
#include "ExitButton.h"
#include "ButtonFunction.h"
#include <list>
namespace Drawable
{
	class InputPanel : public Panel
	{
		public:

			enum ButtonPositions { Left, Center, Right };

		protected :
			ButtonPositions _defaultButtonPositions = Center;
			sf::Vector2f _defaultInputPanelSize = sf::Vector2f(500.0f, 500.0f);
			sf::Vector2f _defaultCornerExitButtonSize = sf::Vector2f(30.0f, 30.0f);
			sf::Vector2f _defaultStandardInputButtonSize = sf::Vector2f(200.0f, 75.0f);
			sf::Vector2f _defaultInputPanelPosition = sf::Vector2f(0.0f, 0.0f);
			sf::Color _defaultInputPanelColor = sf::Color::Blue;
			std::list<Button> _standardInputButtons;
			std::map<Button*, ButtonFunction> _buttonFunctionMap;
			ExitButton _cornerExitButton;
			int _defaultButtonSpace = 10;

		private:

		protected:
			bool IsPointInInputPanelButtons(sf::Vector2i clickPosition);

		public:
			InputPanel();
			~InputPanel();
			InputPanel(sf::Vector2f mainPanelsize, sf::Vector2f manPanelPosition, sf::Color mainPanelColor, int numberOfButtons = 1, ButtonPositions buttonPositions = Center);

			virtual void ContainAllPanelSprites();
			virtual void UpdatePanelTimers();

			void InitializeInputPanelSprites();
			void SetUpCornerExitButton();
			void SetUpStandardInputButtons();
			std::list<sf::Sprite>& GetInputPanelSprites();
			std::list<sf::Text> GetInputPanelTexts();

			void HidePanel(sf::Vector2f hiddenPanelPosition);
			void ShowPanel();

			bool OnPanelLeftMouseClickedUp(sf::Vector2i clickPosition);
			bool OnPanelLeftMouseHoldDown(sf::Vector2i clickPosition, sf::Vector2i previousClickPosition);
	};

	
}

#endif // !__INPUTPANEL_H_INCLUDED_

