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
};

