#include "MovingPhotosManager.h"
//panel Left = panelPositionX;
//panel top = panelPositionY;
//panel right =  panelPositionX + panelSizeX
//panel bottom = panelPositionY + panelSizeY;

//picture left = spriteWidthPosition;
//picture top = spriteHeightPosition;
//picture right = spriteWidthPosition + photoDisplaySize.x;
//picture bottom = spriteHeightPosition + photoDisplaySize.y


void Drawable::MovingPhotosManager::UpdatePanelAndPhotoPositions(sf::Vector2f panelPosition, sf::Vector2f panelSize, std::vector<BarleyPhoto> currentBarleyPhotos)
{
	_panelWalls[0] = panelPosition.x;
	_panelWalls[1] = panelPosition.y;
	_panelWalls[2] = panelPosition.x + panelSize.x;
	_panelWalls[3] = panelPosition.y + panelSize.y;

	_leftsMap.clear();
	_topsMap.clear();
	_rightsMap.clear();
	_bottomsMap.clear();

	//20230617 - fingure how to parse the panel sides appropratley and then move them around together (must optomize)

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

	//Now that they are in there what should happen next ???
	//Check with what direction they should be moving in?
	//Are they individually moving ???
	//Are they moving in unision ???
	//Are they allowed to overlap ???
}

void Drawable::MovingPhotosManager::UpdatePhotoLefts(float photoLeft)
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

void Drawable::MovingPhotosManager::UpdatePhotoTops(float photoTop)
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

void Drawable::MovingPhotosManager::UpdatePhotoRights(float photoRight)
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

void Drawable::MovingPhotosManager::UpdatePhotoBottoms(float photoBottom)
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


