#pragma once
#include "Panel.h"
#include "Button.h"
#include "ExitButton.h"
#include <list>
namespace Drawable
{
	class InputPanel : public Panel
	{
		typedef void (*ScriptFunction)(void); // function pointer type
		typedef std::map<Drawable::Button, ScriptFunction> ButtonFunctionMap;

		private :

			sf::Vector2f _defaultInputPanelSize = sf::Vector2f(500.0f, 500.0f);
			sf::Vector2f _defaultCornerExitButtonSize = sf::Vector2f(30.0f, 30.0f);
			sf::Vector2f _defaultStandardInputButtonSize = sf::Vector2f(200.0f, 75.0f);
			sf::Vector2f _defaultInputPanelPosition = sf::Vector2f(0.0f, 0.0f);
			sf::Color _defaultInputPanelColor = sf::Color::Blue;
			std::list<sf::Sprite> _inputPanelSprites;
			std::list<Button> _standardInputButtons;
			ExitButton _cornerExitButton;
			int _defaultButtonSpace = 10;

			ButtonFunctionMap _buttonFunctionMap;

			//m.emplace("blah", &some_function);

			/*typedef void (*pfunc)(std::string);
			std::map<std::string, pfunc> _buttonDelegatesMap;
			funcMap["f1"] = f1; //and so forth

			pfunc f = funcMap[commandType];
			(*f)(commandParam);*/

		protected:

			void ContainAllPanelSprites();

		public :

			InputPanel();
			~InputPanel();
			InputPanel(sf::Vector2f mainPanelsize, sf::Vector2f manPanelPosition, sf::Color mainPanelColor, int numberOfButtons = 1);

			void InitializeInputPanelSprites();
			void SetUpCornerExitButton();
			void SetUpStandardInputButtons();
			std::list<sf::Sprite> GetInputPanelSprites();

			bool OnPanelClicked(sf::Vector2i clickPosition);

			static void ButtonOneOperation();
	};
}

