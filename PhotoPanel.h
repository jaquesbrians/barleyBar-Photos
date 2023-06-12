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
				CYCLE_RIGHT_2,
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
			bool _photosAreMoving = true;

		public:
			PhotoPanel(sf::Vector2f size, sf::Vector2f position, sf::Color color);
			~PhotoPanel();

			void SetUpPhotoPanel();
			void UpdateWindowLayoutMode(WindowLayoutManager::WindowLayoutMode updatedWindowLayoutMode);
			void CyclePhotosByTime(float timeInterval = 3.0f, bool chooseRandom = false, bool chooseLeft = false);
			void StopCyclePhotosByTime();
			void ManuallyCyclePhotos(bool cycleRight = true);
			void RandomlyCyclePhoto();
			void RandomlyCyclePhotoHelper();
			bool GetIsCyclyingByTime() { return _cycleByTime; }
			bool ArePhotosMoving() { return _photosAreMoving; }
			
			virtual void UpdatePanelTimers();
			virtual void UpdateMovingPhotos();
			virtual void DragPanelPosition(sf::Vector2f panelPositionDirections);

			std::list<sf::Sprite> GetPhotoPanelSprites();

		protected:

		private:
			void ResetPanelSprites();
	};

}

