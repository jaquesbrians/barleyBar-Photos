#include "SingleWindowLayout.h"

SingleWindowLayout::SingleWindowLayout(int windowWidth, int windowHeight, float windowPositionX, float windowPositionY)
{
	_windowWidth = windowWidth;
	_windowHeight = windowHeight;
	_windowPositionX = windowPositionX;
	_windowPositionY = windowPositionY;
}


float SingleWindowLayout::GetSpriteScale()
{
	return _singlePhotoScale;
}

void SingleWindowLayout::SetInitialSpritePositionAndScale(BarleyPhoto &barleyPhoto)
{
	sf::Vector2u getTextureSize = barleyPhoto.texture.getSize();
	barleyPhoto.textureSize = getTextureSize;
	float textureScaleSizeWidth = ((double)_windowWidth / (double)getTextureSize.x);
	float textureScaleSizeHeight = ((double)_windowHeight / (double)getTextureSize.y);
	float finalScalingValue = std::min(textureScaleSizeWidth, textureScaleSizeHeight);
	finalScalingValue = finalScalingValue * _singlePhotoScale;
	barleyPhoto.barleySprite.setScale(sf::Vector2f(finalScalingValue, finalScalingValue));

	barleyPhoto.spriteWidthPosition = (_windowWidth / 2.0f) - (getTextureSize.x * finalScalingValue / 2.0f) + _windowPositionX;
	barleyPhoto.spriteHeightPosition = (_windowHeight / 2.0f) - (getTextureSize.y * finalScalingValue / 2.0f) + _windowPositionY;
	barleyPhoto.barleySprite.setPosition(sf::Vector2f(barleyPhoto.spriteWidthPosition, barleyPhoto.spriteHeightPosition));
}

void SingleWindowLayout::ApplyMotionToLayout()
{
	
}