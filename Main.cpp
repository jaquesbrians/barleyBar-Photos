#include <SFML/Graphics.hpp>
#include "MarianneManager.h"

using namespace sf;

int main()
{
	MarianneManager* marianneManager = MarianneManager::GetInstance();
	return marianneManager->StartMarianneManager();
}