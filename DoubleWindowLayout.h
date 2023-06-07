#pragma once
#include "WindowLayout.h"

class DoubleWindowLayout : public WindowLayout
{
	private:

	float _doublePhotoScale = .50f;

	float _windowHalfWidth = 0.0f;
	float _windowHalfHeight = 0.0f;
	float _windowHalfPositionX = 0.0f;
	float _windowHalfPositionY = 0.0f;

	bool _leftSideOriented = true;

	public:

		DoubleWindowLayout(int windowWidth, int windowHeight, float windowPositionX, float windowPositionY);
		float GetSpriteScale();
		void SetInitialSpritePositionAndScale(BarleyPhoto &barleyPhoto);
		void ApplyMotionToLayout();

	private :
		float FindTextureScale(float textureSize, float fillSize);
};

