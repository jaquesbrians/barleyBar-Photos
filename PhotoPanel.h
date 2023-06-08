#pragma once
#include "Panel.h"
#include "ColorChanger.h";
#include "BarleyPhoto.h"
#include "WindowLayoutManager.h"
namespace Drawable
{
	class PhotoPanel : public Panel
	{
		public:

			std::vector<BarleyPhoto> _currentBarleyPhotos;
			ColorChanger _currentBackGroundColor = sf::Color::White;

			enum PhotoCycleStyle
			{
				CYCLE_RIGHT,
				CYCLE_LEFT,
				CYCLE_RANDOM,
			};

			PhotoCycleStyle photoCycleStyle = CYCLE_RANDOM;

		protected:

		private:
			WindowLayoutManager _windowLayoutManager;
			std::string _directoryPath = "C:\\Users\\15408\\Desktop\\Guarantees\\";
			std::map<int, BarleyPhoto> _barleyPhotoMaps;
			std::vector<unsigned int> _allRandomPhotosVector;
			std::vector<unsigned int> _remainingRandomPhotosVector;
			sf::Clock _photoWindowClock;
			float _timeInterval = 2.0f;
			int _barleyPhotoMapSize = 0;
			int _currentBarleyPhotoIndex = 0;
			bool _cycleByTime = false;

		public:
			PhotoPanel(sf::Vector2f size, sf::Vector2f position, sf::Color color);
			~PhotoPanel();

			void SetUpPhotoPanel();
			void CyclePhotosByTime(float timeInterval = 3.0f, bool chooseRandom = false, bool chooseLeft = false);
			void StopCyclePhotosByTime();
			void ManuallyCyclePhotos(bool cycleRight = true);
			void RandomlyCyclePhoto();
			void RandomlyCyclePhotoHelper();
			bool GetIsCyclyingByTime() { return _cycleByTime; }
			
			virtual void UpdatePanelTimers();
			virtual void MovePanelPosition(sf::Vector2f panelPositionDirections);

			std::list<sf::Sprite> GetPhotoPanelSprites();

		protected:

		private:
			void ResetPanelSprites();
	};

}

