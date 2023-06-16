#pragma once
#include <unordered_map>
class MovingPhotosManager
{
	private:
		float _panelWalls[4] = { 0, 0, 0, 0 };
		std::unordered_map<float, int> _topsMap;
		std::unordered_map<float, int> _rightsMap;
		std::unordered_map<float, int> _bottomsMap;
		std::unordered_map<float, int> _leftMap;

	protected:
	public:

	private:
	protected:
	public:
		//20230616 - Start on this class with passing in the currentphotos on the photo panel and putting their respective sides in the above maps so they
			//can be tested against each other for physics calculations.  Maybe Marianne Math should be used or added to?
};

