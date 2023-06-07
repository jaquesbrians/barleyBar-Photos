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
	sf::Vector2i position = sf::Mouse::getPosition(_windowManager->photoWindow.renderWindow);

	if ((_leftMouseCurrentlyPressed == false && _leftMousePreviouslyPressed == true))
	{
		// Left Mouse Up
		_windowManager->CheckInteractionWithLeftMouseClickUp(position);
	}
	else if ((_leftMouseCurrentlyPressed == true && _leftMousePreviouslyPressed == true))
	{
		// Holding Left Mouse Down
		_windowManager->CheckInteractionWithLeftMouseHoldDown(position, _leftMousePreviousPosition);
	}

	_leftMousePreviouslyPressed = _leftMouseCurrentlyPressed;
	_leftMousePreviousPosition.x = position.x;
	_leftMousePreviousPosition.y = position.y;




	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && _leftMouseButton == false)
	{
		_leftMouseButton = true;
		sf::Vector2i position = sf::Mouse::getPosition(_windowManager->photoWindow.renderWindow);
		_windowManager->CheckInteractionWithLeftMouseClick(position);
	}

	if (sf::Event::MouseButtonReleased && sf::Event::mouseButton == sf::Mouse::Left)
	{

	}*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		_windowManager->CloseWindow();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{	
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
	}
}