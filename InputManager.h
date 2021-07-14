#pragma once
#include <SFML/Graphics.hpp>
#include "WindowManager.h"

class InputManager
{
	private:

		WindowManager* _windowManager;

		bool _leftMousePreviouslyPressed = false;
		bool _leftMouseCurrentlyPressed = false;

	public:

		void StartInputManager(WindowManager& windowManager);
		void UpdateInputManager();
};

