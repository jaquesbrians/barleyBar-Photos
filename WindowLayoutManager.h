#pragma once
#include "WindowLayout.h"
#include "SingleWindowLayout.h"
#include "DoubleWindowLayout.h"
#include "BarleyPhoto.h"
#include <map>

class WindowLayoutManager
{
	public:

		int windowWidth;
		int windowHeight;


		enum WindowLayoutMode
		{
			noWindowLayoutMode = 0,
			singleWindowLayoutMode = 1,
		    doubleWindowLayoutMode = 2,
			multiWindowLayoutMode = 3,
			collageWindowLayoutMode = 4,
			cubeWindowLayoutMode = 5,
		};

		WindowLayoutMode currentWindowLayoutMode = noWindowLayoutMode;

		std::map<int, WindowLayout*> windowLayoutMap;

		void SetSingleWindowLayout();
		void SetDoubleWindowLayout();
		void SetPhotoInitialPositionAndScale(BarleyPhoto& barleyPhoto);
		float GetPhotoScale();
};