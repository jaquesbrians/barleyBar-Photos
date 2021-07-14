#pragma once
#include "WindowLayout.h"

class DoubleWindowLayout : public WindowLayout
{
	private:

	float _doublePhotoScale = .50f;

	bool _leftSideOriented = true;

	public:

		DoubleWindowLayout(int windowWidth, int windowHeight);
		float GetSpriteScale();
		void SetInitialSpritePositionAndScale(BarleyPhoto& barleyPhoto);
		void ApplyMotionToLayout();
};

