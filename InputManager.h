#pragma once
#include <SFML/Graphics.hpp>
#include "WindowManager.h"

class InputManager
{
	private:

		WindowManager* _windowManager;

		bool _leftMousePreviouslyPressed = false;
		bool _leftMouseCurrentlyPressed = false;
		sf::Vector2i _leftMousePreviousPosition = sf::Vector2i(0.0f, 0.0f);

	public:

		void StartInputManager(WindowManager& windowManager);
		void UpdateInputManager();
};

