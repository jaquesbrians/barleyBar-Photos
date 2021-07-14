#include "WindowLayout.h"

WindowLayout::WindowLayout(){}


WindowLayout::WindowLayout(int windowWidth, int windowHeight)
{
	_windowWidth = windowWidth;
	_windowHeight = windowHeight;
}

void WindowLayout::TurnOffMotionToLayout()
{
	_applyMotionToLayout = false;
}

float WindowLayout::GetSpriteScale()
{
	return 0.0f;
}

void WindowLayout::SetInitialSpritePositionAndScale(BarleyPhoto& barleyPhoto)
{
}

void WindowLayout::ApplyMotionToLayout()
{
}

void WindowLayout::TurnOnMotionToLayout()
{
	_applyMotionToLayout = true;
}

