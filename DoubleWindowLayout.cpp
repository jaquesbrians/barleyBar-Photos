#include "DoubleWindowLayout.h"

DoubleWindowLayout::DoubleWindowLayout(int windowWidth, int windowHeight, float windowPositionX, float windowPositionY)
{
	_windowWidth = windowWidth;
	_windowHeight = windowHeight;
	_windowPositionX = windowPositionX;
	_windowPositionY = windowPositionY;

	_windowHalfWidth = _windowWidth * 0.5f;
	_windowHalfHeight = _windowHeight * 0.5f;
	_windowHalfPositionX = _windowPositionX * 0.5f;
	_windowHalfPositionY = _windowPositionY * 0.5f;
}

float DoubleWindowLayout::GetSpriteScale()
{
	return _doublePhotoScale;
}

void DoubleWindowLayout::SetInitialSpritePositionAndScale(BarleyPhoto &barleyPhoto)
{
	sf::Vector2u textureSize = barleyPhoto.texture.getSize();

	bool horizontal = textureSize.x > textureSize.y ? true : false;
	float textureScaleSizeWidth = horizontal ? ((double)_windowHalfWidth / (double)textureSize.x) : ((double)_windowHalfWidth / (double)textureSize.x);
	float textureScaleSizeHeight = horizontal ? ((double)_windowHeight / (double)textureSize.y) : ((double)_windowHeight / (double)textureSize.y);
	float finalScalingValue = std::min(textureScaleSizeWidth, textureScaleSizeHeight);
	finalScalingValue = finalScalingValue * .90f;
	barleyPhoto.barleySprite.setScale(sf::Vector2f(finalScalingValue, finalScalingValue));
	sf::Vector2f updatedScaleSize = barleyPhoto.barleySprite.getScale();
	barleyPhoto.currentDisplaySize = sf::Vector2f(textureSize.x * updatedScaleSize.x, textureSize.y * updatedScaleSize.y);


	if (_leftSideOriented)
	{
		barleyPhoto.spriteWidthPosition = (_windowWidth * 0.25f) - (textureSize.x * finalScalingValue * 0.5f) + _windowPositionX;
	}
	else
	{
		barleyPhoto.spriteWidthPosition = (_windowWidth * 0.75f) - (textureSize.x * finalScalingValue * 0.5f) + _windowPositionX;
	}

	barleyPhoto.spriteHeightPosition = (_windowHeight * 0.5f) - (textureSize.y * finalScalingValue * 0.5f) + _windowPositionY;
	
	barleyPhoto.barleySprite.setPosition(sf::Vector2f(barleyPhoto.spriteWidthPosition, barleyPhoto.spriteHeightPosition));
	
	_leftSideOriented = !_leftSideOriented;
}


float DoubleWindowLayout::FindTextureScale(float textureSize, float fillSize)
{
	bool findTextureScale = true;
	float scaleValue = 0.99f;
	while (findTextureScale)
	{
		if ((textureSize * scaleValue) > fillSize)
		{
			scaleValue = scaleValue - 0.01f;
		}
		else
		{
			findTextureScale = false;
		}
	}

	return scaleValue;
}

void DoubleWindowLayout::ApplyMotionToLayout()
{

}