#include "MarianneMath.h"

bool Math::MarianneMath::IsPointInRectangle(sf::Vector2f rectPosition, sf::Vector2f rectSize, sf::Vector2i pointPosition)
{
	float minX = rectPosition.x;
	float maxX = rectPosition.x + rectSize.x;
	float minY = rectPosition.y;
	float maxY = rectPosition.y + rectSize.y;
	return pointPosition.x > minX && pointPosition.x < maxX && pointPosition.y > minY && pointPosition.y < maxY;
}