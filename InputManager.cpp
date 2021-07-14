#include "InputManager.h"
#include <SFML/Graphics.hpp>
#include "PhotoWindow.h"


void InputManager::StartInputManager(WindowManager& windowManager)
{
	_windowManager = &windowManager;
}


void InputManager::UpdateInputManager()
{

	_leftMouseCurrentlyPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	if ((_leftMouseCurrentlyPressed && _leftMousePreviouslyPressed == false))
	{
		sf::Vector2i position = sf::Mouse::getPosition(_windowManager->photoWindow.renderWindow);
		_windowManager->CheckInteractionWithLeftMouseClick(position);
	}

	_leftMousePreviouslyPressed = _leftMouseCurrentlyPressed;



	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _leftMouseButton == false)
	{
		_leftMouseButton = true;
		sf::Vector2i position = sf::Mouse::getPosition(_windowManager->photoWindow.renderWindow);
		_windowManager->CheckInteractionWithLeftMouseClick(position);
	}

	if (sf::Event::MouseButtonReleased && sf::Event::mouseButton == sf::Mouse::Left)
	{

	}*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{	
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
	}
}