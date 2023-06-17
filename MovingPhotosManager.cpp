#include "MovingPhotosManager.h"

//float _panelWalls[4] = { 0, 0, 0, 0 };
//std::unordered_map<float, int> _leftMap;
//std::unordered_map<float, int> _topsMap;
//std::unordered_map<float, int> _rightsMap;
//std::unordered_map<float, int> _bottomsMap;


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

	for (int i = 0; i < currentBarleyPhotos.size(); i++)
	{
		//_leftsMap.emplace

		//if (_leftsMap.find)


	}

}
