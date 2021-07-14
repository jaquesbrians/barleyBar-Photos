#include "SingleWindowLayout.h"

SingleWindowLayout::SingleWindowLayout(int windowWidth, int windowHeight)
{
	_windowWidth = windowWidth;
	_windowHeight = windowHeight;
}


float SingleWindowLayout::GetSpriteScale()
{
	return _singlePhotoScale;
}

void SingleWindowLayout::SetInitialSpritePositionAndScale(BarleyPhoto& barleyPhoto)
{
	sf::Vector2u textureSize = barleyPhoto.texture.getSize();
	float textureScaleSizeWidth = ((double)_windowWidth / (double)textureSize.x);
	float textureScaleSizeHeight = ((double)_windowHeight / (double)textureSize.y);
	float finalScalingValue = std::min(textureScaleSizeWidth, textureScaleSizeHeight);
	finalScalingValue = finalScalingValue * _singlePhotoScale;
	barleyPhoto.barleySprite.setScale(sf::Vector2f(finalScalingValue, finalScalingValue));

	barleyPhoto.spriteWidthPosition = (_windowWidth / 2.0f) - (textureSize.x * finalScalingValue / 2.0f);
	barleyPhoto.spriteHeightPosition = (_windowHeight / 2.0f) - (textureSize.y * finalScalingValue / 2.0f);
	barleyPhoto.barleySprite.setPosition(sf::Vector2f(barleyPhoto.spriteWidthPosition, barleyPhoto.spriteHeightPosition));
}

void SingleWindowLayout::ApplyMotionToLayout()
{
	
}