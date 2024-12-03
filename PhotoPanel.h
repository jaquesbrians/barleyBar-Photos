#pragma once
#include "Panel.h"
#include "ColorChanger.h";
#include "BarleyPhoto.h"
#include "MovingPhotosManager.h"
#include "WindowLayoutManager.h"
namespace Drawable
{
	class PhotoPanel : public Panel
	{
		private:
			WindowLayoutManager _windowLayoutManager;
			ColorChanger _currentBackGroundColor = sf::Color::White;
			MovingPhotosManager _movingPhotosManager;
			std::vector<BarleyPhoto> _currentBarleyPhotos;
			std::string _directoryPath = "C:\\Users\\jaque\\OneDrive\\Desktop\\TrialPhotosForBarleyPhotos";
			std::map<int, BarleyPhoto> _barleyPhotoMaps;
			std::vector<unsigned int> _allRandomPhotosVector;
			std::vector<unsigned int> _remainingRandomPhotosVector;
			sf::Clock _photoWindowClock;
			sf::Clock _photosClock;
			float _timeInterval = 6.0f;
			int _barleyPhotoMapSize = 0;
			int _currentBarleyPhotoIndex = 0;


			bool _cycleByTime = false;
			bool _photosAreMoving = true;

			//temp trial bool
			bool _moveRight = true;
			double _windDown = 255.0f;

		protected:

		public:
			enum PhotoCycleStyle
			{
				CYCLE_RIGHT,
				CYCLE_RIGHT_2,
				CYCLE_LEFT,
				CYCLE_RANDOM,
			};
			PhotoCycleStyle photoCycleStyle = CYCLE_RANDOM;

		
		private:
			void ResetPanelSprites();

		protected:

		public:
			PhotoPanel(sf::Vector2f size, sf::Vector2f position, sf::Color color);
			~PhotoPanel();
			void SetUpPhotoPanel();
			void UpdateWindowLayoutMode(WindowLayoutManager::WindowLayoutMode updatedWindowLayoutMode);
			void CyclePhotosByTime(float timeInterval = 6.0f, bool chooseRandom = false, bool chooseLeft = false);
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
			std::vector<BarleyPhoto>& GetCurrentBarleyPhotos();
	};
}

