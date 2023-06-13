#include <filesystem>
#include <thread>
#include "PhotoPanel.h"

Drawable::PhotoPanel::PhotoPanel(sf::Vector2f size, sf::Vector2f position, sf::Color color)
{
	this->Panel::Panel(size, position, _currentBackGroundColor.RandomColorFadeTimeElapse());
	SetUpPhotoPanel();
}

Drawable::PhotoPanel::~PhotoPanel()
{
}

void Drawable::PhotoPanel::SetUpPhotoPanel()
{
	_windowLayoutManager.windowWidth = GetPanelSize().x;
	_windowLayoutManager.windowHeight = GetPanelSize().y;
	_windowLayoutManager.windowPositionX = GetPanelPosition().x;
	_windowLayoutManager.windowPositionY = GetPanelPosition().y;
	_windowLayoutManager.SetSingleWindowLayout();
	//_windowLayoutManager.SetDoubleWindowLayout();

	int photoIndex = 0;
	for (const auto& entry : std::filesystem::directory_iterator(_directoryPath))
	{
		BarleyPhoto barleyPhoto;
		std::string path_string{ entry.path().u8string() };
		_barleyPhotoMaps.insert(std::pair<int, BarleyPhoto>(photoIndex, barleyPhoto));
		_barleyPhotoMaps[photoIndex].LoadSprite(path_string);
		_allRandomPhotosVector.push_back(photoIndex);
		_remainingRandomPhotosVector.push_back(photoIndex);
		photoIndex++;
	}

	_barleyPhotoMapSize = photoIndex;

	RandomlyCyclePhoto();
}

void Drawable::PhotoPanel::UpdateWindowLayoutMode(WindowLayoutManager::WindowLayoutMode updatedWindowLayoutMode)
{
	_windowLayoutManager.UpdateWindowLayout(updatedWindowLayoutMode);
}


void Drawable::PhotoPanel::CyclePhotosByTime(float timeInterval, bool chooseRandom, bool chooseLeft)
{
	_photoWindowClock.restart();
	_cycleByTime = true;
}

void Drawable::PhotoPanel::StopCyclePhotosByTime()
{
	_cycleByTime = false;
}

void Drawable::PhotoPanel::ManuallyCyclePhotos(bool cycleRight)
{
	_currentBarleyPhotos.clear();

	int numOfPhotosNeeded = _windowLayoutManager.GetNumerOfPhotosPerWindow();

	for (int i = 0; i < numOfPhotosNeeded; i++)
	{
		if (cycleRight)
		{
			_currentBarleyPhotoIndex++;
			_currentBarleyPhotoIndex = _currentBarleyPhotoIndex >= _barleyPhotoMapSize ? 0 : _currentBarleyPhotoIndex;
		}
		else
		{
			_currentBarleyPhotoIndex--;
			_currentBarleyPhotoIndex = _currentBarleyPhotoIndex < 0 ? _barleyPhotoMapSize - 1 : _currentBarleyPhotoIndex;
		}

		_windowLayoutManager.SetPhotoInitialPositionAndScale(_barleyPhotoMaps[_currentBarleyPhotoIndex]);
		_currentBarleyPhotos.push_back(_barleyPhotoMaps[_currentBarleyPhotoIndex]);
	}

	ResetPanelSprites();
}

//Things to do for tomorrow -  20230611
// Start thinking about how to make your photos slowly move during long periods of staying still, like a screen savor.

void Drawable::PhotoPanel::RandomlyCyclePhoto()
{
	_currentBarleyPhotos.clear();

	for (int i = 0; i < _windowLayoutManager.GetNumerOfPhotosPerWindow(); i++)
	{
		RandomlyCyclePhotoHelper();
	}

	ResetPanelSprites();
}

void Drawable::PhotoPanel::RandomlyCyclePhotoHelper()
{
	if (_remainingRandomPhotosVector.size() == 0)
	{
		_remainingRandomPhotosVector = _allRandomPhotosVector;
	}

	srand(time(0));
	int randomIndex = rand() % _remainingRandomPhotosVector.size();
	int selectedPhoto = _remainingRandomPhotosVector[randomIndex];
	_remainingRandomPhotosVector.erase(_remainingRandomPhotosVector.begin() + randomIndex);
	_windowLayoutManager.SetPhotoInitialPositionAndScale(_barleyPhotoMaps[selectedPhoto]);
	_currentBarleyPhotos.push_back(_barleyPhotoMaps[selectedPhoto]);
}


std::list<sf::Sprite> Drawable::PhotoPanel::GetPhotoPanelSprites()
{
	return _panelSprites;
}

void Drawable::PhotoPanel::UpdatePanelTimers()
{
	//this is only happening when a picture switches ???
	_panelSprite.setColor(_currentBackGroundColor.RandomColorFadeTimeElapse());

	if (_cycleByTime == true && _photoWindowClock.getElapsedTime().asSeconds() >= _timeInterval)
	{
		switch (photoCycleStyle)
		{
		case CYCLE_RIGHT:
			ManuallyCyclePhotos();
			break;
		case CYCLE_LEFT:
			ManuallyCyclePhotos(false);
			break;
		case CYCLE_RANDOM:
			RandomlyCyclePhoto();
			break;
		}

		_photoWindowClock.restart();
	}
}

//20230613 - Start doing moving panel the right way and also get it to stop appropriatley against wall

void Drawable::PhotoPanel::UpdateMovingPhotos()
{
	for (int i = 0; i < _currentBarleyPhotos.size(); i++)
	{
		//float positionX = _currentBarleyPhotos[i].spriteWidthPosition++;
		//float positionY = _currentBarleyPhotos[i].spriteHeightPosition;
		//_currentBarleyPhotos[i].SetSpritePosition(sf::Vector2f(1, 0));
		//ResetPanelSprites();

		if (_currentBarleyPhotos[i].barleySprite.getPosition().x + 1 < _panelSize.x - (_currentBarleyPhotos[i].textureSize.x * _currentBarleyPhotos[i].barleySprite.getScale().x))
		{
			//_currentBarleyPhotos[i].SetSpritePosition(sf::Vector2f(_currentBarleyPhotos[i].spriteWidthPosition++, _currentBarleyPhotos[i].spriteHeightPosition));
			float positionX = _currentBarleyPhotos[i].spriteWidthPosition++;
			float positionY = _currentBarleyPhotos[i].spriteHeightPosition;
			_currentBarleyPhotos[i].SetSpritePosition(sf::Vector2f(1, 0));
			ResetPanelSprites();
			//_currentBarleyPhoto.barleySprite.setPosition(Vector2f(_currentBarleyPhoto.spriteWidthPosition++, _currentBarleyPhoto.spriteHeightPosition));
		}
	}
}

//Might want to rename this function/procedure to be DragPanelPosition (since that is what this is doing)?
void Drawable::PhotoPanel::DragPanelPosition(sf::Vector2f panelPositionDirections)
{
	DragPanelPosition(panelPositionDirections);

	for (int i = 0; i < _currentBarleyPhotos.size(); i++)
	{
		_currentBarleyPhotos[i].SetSpritePosition(panelPositionDirections);
	}

	ResetPanelSprites();
}

void Drawable::PhotoPanel::ResetPanelSprites()
{
	_panelSprites.clear();
	_panelSprites.push_back(_panelSprite);

	for (int i = 0; i < _currentBarleyPhotos.size(); i++)
	{
		_panelSprites.push_back(_currentBarleyPhotos[i].barleySprite);
	}
}
