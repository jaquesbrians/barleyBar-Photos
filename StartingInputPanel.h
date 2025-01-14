#pragma once
#include "InputPanel.h"
#include "PhotoPanel.h"
namespace Drawable
{
	class StartingInputPanel : public InputPanel
	{
		public:
			PhotoPanel _previewPhotoPanel;

		protected:
			void SetUpPreviewPhotoPanel(PhotoPanel* photoPanel = nullptr);

		public:
			StartingInputPanel(sf::Vector2f mainPanelsize, sf::Vector2f manPanelPosition, sf::Color mainPanelColor, 
				int numberOfButtons = 1, ButtonPositions buttonPositions = Center, PhotoPanel* photoPanel = nullptr);
			~StartingInputPanel();

			virtual void ContainAllPanelSprites();
			virtual void UpdatePanelTimers();
			virtual void DragPanelPosition(sf::Vector2f panelPositionDirections);
	};
}
