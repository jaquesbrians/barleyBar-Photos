#include "DoubleWindowLayout.h"

DoubleWindowLayout::DoubleWindowLayout(int windowWidth, int windowHeight)
{
	_windowWidth = windowWidth;
	_windowHeight = windowHeight;
}

float DoubleWindowLayout::GetSpriteScale()
{
	return _doublePhotoScale;
}

void DoubleWindowLayout::SetInitialSpritePositionAndScale(BarleyPhoto& barleyPhoto)
{
	sf::Vector2u textureSize = barleyPhoto.texture.getSize();
	float textureScaleSizeWidth = ((double)_windowWidth / (double)textureSize.x);
	float textureScaleSizeHeight = ((double)_windowHeight / (double)textureSize.y);
	float finalScalingValue = std::min(textureScaleSizeWidth, textureScaleSizeHeight);
	finalScalingValue = finalScalingValue * _doublePhotoScale;
	barleyPhoto.barleySprite.setScale(sf::Vector2f(finalScalingValue, finalScalingValue));

	if (_leftSideOriented)
	{
		barleyPhoto.spriteWidthPosition = (_windowWidth * 0.25f) - (textureSize.x * finalScalingValue * 0.5f);		
	}
	else
	{
		barleyPhoto.spriteWidthPosition = (_windowWidth * 0.75f) - (textureSize.x * finalScalingValue * 0.5f);
	}

	barleyPhoto.spriteHeightPosition = (_windowHeight * 0.5f) - (textureSize.y * finalScalingValue * 0.5f);
	barleyPhoto.barleySprite.setPosition(sf::Vector2f(barleyPhoto.spriteWidthPosition, barleyPhoto.spriteHeightPosition));
	_leftSideOriented = !_leftSideOriented;
	
}

void DoubleWindowLayout::ApplyMotionToLayout()
{

}