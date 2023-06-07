#include "WindowLayoutManager.h"

void WindowLayoutManager::SetPhotoInitialPositionAndScale(BarleyPhoto &barleyPhoto)
{
	windowLayoutMap[currentWindowLayoutMode]->SetInitialSpritePositionAndScale(barleyPhoto);
}

float WindowLayoutManager::GetPhotoScale()
{
	return windowLayoutMap[currentWindowLayoutMode]->GetSpriteScale();
}

#pragma region SetCurrentLayoutRegion

void WindowLayoutManager::SetSingleWindowLayout()
{
	currentWindowLayoutMode = singleWindowLayoutMode;
	numberOfPhotosPerWindow = 1;

	if (windowLayoutMap.count(currentWindowLayoutMode) == false)
	{
		SingleWindowLayout* singleWindowTrial = new SingleWindowLayout(windowWidth, windowHeight, windowPositionX, windowPositionY);
		windowLayoutMap.insert(std::pair<int, WindowLayout*>(currentWindowLayoutMode, singleWindowTrial));
	}
}

void WindowLayoutManager::SetDoubleWindowLayout()
{
	currentWindowLayoutMode = doubleWindowLayoutMode;
	numberOfPhotosPerWindow = 2;

	if (windowLayoutMap.count(currentWindowLayoutMode) == false)
	{
		DoubleWindowLayout* doubleWindowLayout = new DoubleWindowLayout(windowWidth, windowHeight, windowPositionX, windowPositionY);
		windowLayoutMap.insert(std::pair<int, WindowLayout*>(currentWindowLayoutMode, doubleWindowLayout));
	}
}

#pragma endRegion



