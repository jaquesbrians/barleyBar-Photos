#pragma once
#include "BarleyPhoto.h"

class WindowLayout
{
	protected:

		int _windowWidth;
		int _windowHeight;

		float _windowPositionX = 0.0f;
		float _windowPositionY = 0.0f;

		bool _applyMotionToLayout;

		void TurnOnMotionToLayout();
		void TurnOffMotionToLayout();

	public:

		WindowLayout();
		WindowLayout(int windowWidth, int windowHeight, float windowPositionX, float windowPositionY);

		virtual float GetSpriteScale();
		virtual void SetInitialSpritePositionAndScale(BarleyPhoto &barleyPhoto);
		virtual void ApplyMotionToLayout();
};