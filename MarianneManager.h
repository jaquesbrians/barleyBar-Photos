#pragma once
#include <SFML/Graphics.hpp>
#include "PhotoWindowManager.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "Panel.h"

class MarianneManager
{
	private:

		static MarianneManager* Instance;

		WindowManager _windowManager;
		InputManager _inputManager;

		void StartAllManagers();
		void UpdateAllManagers();

	public:

		bool runMarianneManager = true;

		int StartMarianneManager();
		static MarianneManager* GetInstance();
};

