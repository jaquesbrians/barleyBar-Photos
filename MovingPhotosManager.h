#pragma once
#include <unordered_map>
#include "BarleyPhoto.h"

namespace Drawable
{
	class MovingPhotosManager
	{
	private:
		float _panelWalls[4] = { 0, 0, 0, 0 };
		std::unordered_map<float, int> _leftsMap;
		std::unordered_map<float, int> _topsMap;
		std::unordered_map<float, int> _rightsMap;
		std::unordered_map<float, int> _bottomsMap;		

	protected:
	public:

	private:
	protected:
	public:

		void UpdatePanelAndPhotoPositions(sf::Vector2f panelPosition, sf::Vector2f panelSize, std::vector<BarleyPhoto> &currentBarleyPhotos);
		void UpdatePhotoLefts(float photoLeft);
		void UpdatePhotoTops(float photoTop);
		void UpdatePhotoRights(float photoRight);
		void UpdatePhotoBottoms(float photoBottom);
	};
}