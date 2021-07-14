#pragma once
#include "BarleyPhoto.h"

class WindowLayout
{
	protected:

		bool _applyMotionToLayout;

		int _windowWidth;

		int _windowHeight;

		void TurnOnMotionToLayout();
		void TurnOffMotionToLayout();

	public:

		WindowLayout();
		WindowLayout(int windowWidth, int windowHeight);

		virtual float GetSpriteScale();
		virtual void SetInitialSpritePositionAndScale(BarleyPhoto& barleyPhoto);
		virtual void ApplyMotionToLayout();
};