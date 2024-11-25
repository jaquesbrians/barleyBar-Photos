#include "MovingPhotosManager.h"
//panel Left = panelPositionX;
//panel top = panelPositionY;
//panel right =  panelPositionX + panelSizeX
//panel bottom = panelPositionY + panelSizeY;

//picture left = spriteWidthPosition;
//picture top = spriteHeightPosition;
//picture right = spriteWidthPosition + photoDisplaySize.x;
//picture bottom = spriteHeightPosition + photoDisplaySize.y


void Drawable::MovingPhotosManager::UpdatePanelAndPhotoPositions(sf::Vector2f panelPosition, sf::Vector2f panelSize, std::vector<BarleyPhoto> &currentBarleyPhotos)
{
	_panelWalls[0] = panelPosition.x;
	_panelWalls[1] = panelPosition.y;
	_panelWalls[2] = panelPosition.x + panelSize.x;
	_panelWalls[3] = panelPosition.y + panelSize.y;

	_leftsMap.clear();
	_topsMap.clear();
	_rightsMap.clear();
	_bottomsMap.clear();

	//20230620 - Try to think of a better way to get them bouncing (as far as code cleanliness and logic goes) and adding moving up and down 

	for (int i = 0; i < currentBarleyPhotos.size(); i++)
	{
		float photoLeft = currentBarleyPhotos[i].spriteWidthPosition;
		float photoTop = currentBarleyPhotos[i].spriteHeightPosition;
		float photoRight = currentBarleyPhotos[i].spriteWidthPosition + currentBarleyPhotos[i].currentDisplaySize.x;
		float photoBottom = currentBarleyPhotos[i].spriteHeightPosition + currentBarleyPhotos[i].currentDisplaySize.y;

		UpdatePhotoLefts(photoLeft);
		UpdatePhotoTops(photoTop);
		UpdatePhotoRights(photoRight);
		UpdatePhotoBottoms(photoBottom);
	}

	for (int i = 0; i < currentBarleyPhotos.size(); i++)
	{
		if (currentBarleyPhotos[i].photoMovementDirection == BarleyPhoto::PhotoMovementDirection::MOVE_RIGHT)
		{

			float photoRight = currentBarleyPhotos[i].spriteWidthPosition + currentBarleyPhotos[i].currentDisplaySize.x;

			if (_leftsMap.count(photoRight) > 0)
			{
				currentBarleyPhotos[i].photoMovementDirection = BarleyPhoto::PhotoMovementDirection::MOVE_LEFT;
				continue;
			}

			if (currentBarleyPhotos[i].spriteWidthPosition + currentBarleyPhotos[i].currentDisplaySize.x + 1 < _panelWalls[2])
			{
				// cool typewriter affect going on here by accident 20241124
				//currentBarleyPhotos[i].spriteWidthPosition = currentBarleyPhotos[i].spriteWidthPosition + 0.1f;
				//currentBarleyPhotos[i].SetSpritePosition(sf::Vector2f(.1f, 0));


				float deltaTime = currentBarleyPhotos[i].GetBarleyPhotoClock().restart().asSeconds();
				float speed = 100.0f * deltaTime;

				currentBarleyPhotos[i].spriteWidthPosition = currentBarleyPhotos[i].spriteWidthPosition + speed;
				currentBarleyPhotos[i].SetSpritePosition(sf::Vector2f(speed, 0));
				continue;
			}
			else
			{
				currentBarleyPhotos[i].photoMovementDirection = BarleyPhoto::PhotoMovementDirection::MOVE_LEFT;
				continue;
			}
		}
		
		if (currentBarleyPhotos[i].photoMovementDirection == BarleyPhoto::PhotoMovementDirection::MOVE_LEFT)
		{

			float photoLeft = currentBarleyPhotos[i].spriteWidthPosition;

			if (_rightsMap.count(photoLeft) > 0)
			{
				currentBarleyPhotos[i].photoMovementDirection = BarleyPhoto::PhotoMovementDirection::MOVE_RIGHT;
				continue;
			}


			if (currentBarleyPhotos[i].spriteWidthPosition - 1 > _panelWalls[0])
			{
				currentBarleyPhotos[i].spriteWidthPosition--;
				currentBarleyPhotos[i].SetSpritePosition(sf::Vector2f(-1, 0));
				continue;
			}
			else
			{
				currentBarleyPhotos[i].photoMovementDirection = BarleyPhoto::PhotoMovementDirection::MOVE_RIGHT;
			}
		}
	}

	//Now that they are in there what should happen next ???
	//Check with what direction they should be moving in?
	//Are they individually moving ???
	//Are they moving in unision ???
	//Are they allowed to overlap ???
}

void Drawable::MovingPhotosManager::UpdatePhotoLefts(int photoLeft)
{
	if (_leftsMap.count(photoLeft) > 0)
	{
		float leftsMapValue = _leftsMap[photoLeft];
		leftsMapValue++;
		_leftsMap[photoLeft] = leftsMapValue;
	}
	else
	{
		_leftsMap.emplace(photoLeft, 1);
	}
}

void Drawable::MovingPhotosManager::UpdatePhotoTops(int photoTop)
{
	if (_topsMap.count(photoTop) > 0)
	{
		float topsMapValue = _topsMap[photoTop];
		topsMapValue++;
		_topsMap[photoTop] = topsMapValue;
	}
	else
	{
		_topsMap.emplace(photoTop, 1);
	}
}

void Drawable::MovingPhotosManager::UpdatePhotoRights(int photoRight)
{
	if (_rightsMap.count(photoRight) > 0)
	{
		float rightsMapValue = _rightsMap[photoRight];
		rightsMapValue++;
		_rightsMap[photoRight] = rightsMapValue;
	}
	else
	{
		_rightsMap.emplace(photoRight, 1);
	}
}

void Drawable::MovingPhotosManager::UpdatePhotoBottoms(int photoBottom)
{
	if (_bottomsMap.count(photoBottom) > 0)
	{
		float bottomsMapValue = _bottomsMap[photoBottom];
		bottomsMapValue++;
		_bottomsMap[photoBottom] = bottomsMapValue;
	}
	else
	{
		_bottomsMap.emplace(photoBottom, 1);
	}
}


