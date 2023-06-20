#pragma once
#include <unordered_map>
#include "BarleyPhoto.h"

namespace Drawable
{
	class MovingPhotosManager
	{
	private:
		float _panelWalls[4] = { 0, 0, 0, 0 };
		std::unordered_map<int, int> _leftsMap;
		std::unordered_map<int, int> _topsMap;
		std::unordered_map<int, int> _rightsMap;
		std::unordered_map<int, int> _bottomsMap;		

	protected:
	public:

	private:
	protected:
	public:

		void UpdatePanelAndPhotoPositions(sf::Vector2f panelPosition, sf::Vector2f panelSize, std::vector<BarleyPhoto> &currentBarleyPhotos);
		void UpdatePhotoLefts(int photoLeft);
		void UpdatePhotoTops(int photoTop);
		void UpdatePhotoRights(int photoRight);
		void UpdatePhotoBottoms(int photoBottom);
	};
}