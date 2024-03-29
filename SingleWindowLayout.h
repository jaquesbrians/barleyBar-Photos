#pragma once
#include "WindowLayout.h"

class SingleWindowLayout : public WindowLayout
{
	private:

		float _singlePhotoScale = .90f;

	public:

		SingleWindowLayout(int windowWidth, int windowHeight, float windowPositionX, float windowPositionY);

		float GetSpriteScale();

		void SetInitialSpritePositionAndScale(BarleyPhoto &barleyPhoto);

		void ApplyMotionToLayout();
};

