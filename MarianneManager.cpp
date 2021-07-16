#include "MarianneManager.h"
#include "Button.h"
#include "InputPanel.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string> 


MarianneManager* MarianneManager::Instance = NULL;

MarianneManager* MarianneManager::GetInstance()
{
	if (Instance == NULL) 
	{
		Instance = new MarianneManager();
	}
	return(Instance);
}

int MarianneManager::StartMarianneManager()
{
	//Trial Commit 2021
	StartAllManagers();

	while (runMarianneManager)
	{
		UpdateAllManagers();
	}

	return 0;
}


void MarianneManager::StartAllManagers()
{
	std::ifstream sfile(_marianneManagerFilesToLoadPath);







	_windowManager.StartWindowManager();

	_inputManager.StartInputManager(_windowManager);
}

void MarianneManager::UpdateAllManagers()
{

	//Do this by passing the windowManager into the Input Manager at startup. 

	//also you need to build your list class cause iterating over a list is terrible in C++;

	_inputManager.UpdateInputManager();
	_windowManager.UpdateWindowManager();
}

//Button button(sf::Vector2f(200, 200), sf::Vector2f(500, 500), sf::Color::Green);
	//_windowManager.AddSpriteToDrawList(button.GetPanelSprite(), 1);  
	//_windowManager.AddSpriteToDrawList(button.GetPanelText(), 1);
	//_windowManager.AddSpriteToDrawList(inputPanel.GetPanelSprite(), 1);
	//_windowManager.AddSpriteToDrawList(inputPanel.standardInputButton.GetPanelSprite(), 1);

	//InputPanel inputPanel;

	//_windowManager.AddSpritesToDrawList(inputPanel.GetInputPanelSprites(), 1);