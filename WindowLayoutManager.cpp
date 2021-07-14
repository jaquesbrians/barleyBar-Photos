#include "WindowLayoutManager.h"

void WindowLayoutManager::SetPhotoInitialPositionAndScale(BarleyPhoto& barleyPhoto)
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

	if (windowLayoutMap.count(currentWindowLayoutMode) == false)
	{
		SingleWindowLayout* singleWindowTrial = new SingleWindowLayout(windowWidth, windowHeight);
		windowLayoutMap.insert(std::pair<int, WindowLayout*>(currentWindowLayoutMode, singleWindowTrial));
	}
}

void WindowLayoutManager::SetDoubleWindowLayout()
{
	currentWindowLayoutMode = doubleWindowLayoutMode;

	if (windowLayoutMap.count(currentWindowLayoutMode) == false)
	{
		DoubleWindowLayout* doubleWindowLayout = new DoubleWindowLayout(windowWidth, windowHeight);
		windowLayoutMap.insert(std::pair<int, WindowLayout*>(currentWindowLayoutMode, doubleWindowLayout));
	}
}

#pragma endRegion



