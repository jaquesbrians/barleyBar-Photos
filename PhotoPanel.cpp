#include <filesystem>
#include <thread>
#include "PhotoPanel.h"

Drawable::PhotoPanel::PhotoPanel(sf::Vector2f size, sf::Vector2f position, sf::Color color)
{
	this->Panel::Panel(size, position, _currentBackGroundColor.RandomColorFadeTimeElapse());
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


	//We'll probably want to put the loading of all the images in to some sort of master place instead of individual photo panels
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

	_photosClock.restart();
	_photoWindowClock.restart();
}

void Drawable::PhotoPanel::UpdateWindowLayoutMode(WindowLayoutManager::WindowLayoutMode updatedWindowLayoutMode)
{
	_windowLayoutManager.UpdateWindowLayout(updatedWindowLayoutMode);
}

void Drawable::PhotoPanel::CyclePhotosByTime(float timeInterval, bool chooseRandom, bool chooseLeft)
{
	_timeInterval = timeInterval;
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

	for (int i = 0; i < _currentBarleyPhotos.size(); i++)
	{
		_currentBarleyPhotos[i].photoAlphaSetting = BarleyPhoto::PhotoAlphaSetting::ALPHA_FADE_IN;
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

//Look up how to do checkable flags (see reasons why to use and see if they are better than bools?)
void Drawable::PhotoPanel::UpdatePanelTimers()
{
	_panelSprite.setColor(_currentBackGroundColor.RandomColorFadeTimeElapse());

	double deltaTime = _photoWindowClock.getElapsedTime().asSeconds();

	//if (((_timeInterval - 1) - deltaTime) <= 3.0 && _currentBarleyPhotos[i].photoAlphaSetting != BarleyPhoto::PhotoAlphaSetting::ALPHA_FADE_OUT)
	//{
	for (int i = 0; i < _currentBarleyPhotos.size(); i++)
	{
		if (_timeInterval - 3.0 <= deltaTime && _currentBarleyPhotos[i].photoAlphaSetting != BarleyPhoto::PhotoAlphaSetting::ALPHA_FADE_OUT)
		{
			_currentBarleyPhotos[i].photoAlphaSetting = BarleyPhoto::PhotoAlphaSetting::ALPHA_FADE_OUT;
			//_photoWindowClock.restart();
		}
	}
	//}

	//For Tomorrow include these statements in the above for loop wheneverthing is set and done with current bug.  
	for (int i = 0; i < _currentBarleyPhotos.size(); i++)
	{
		if (_currentBarleyPhotos[i].photoAlphaSetting == BarleyPhoto::PhotoAlphaSetting::ALPHA_FADE_IN)
		{
			_currentBarleyPhotos[i].BarleyPhotoFader(deltaTime);
		}
		else if (_currentBarleyPhotos[i].photoAlphaSetting == BarleyPhoto::PhotoAlphaSetting::ALPHA_FADE_OUT)
		{
			//_currentBarleyPhotos[i].BarleyPhotoFader(deltaTime - int(deltaTime));
			_currentBarleyPhotos[i].BarleyPhotoFader(deltaTime - 7.0);
			//_currentBarleyPhotos[i].BarleyPhotoFader(_windDown);
			_windDown--;
		}
	}


	if (_cycleByTime == true && deltaTime >= _timeInterval)
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

	ResetPanelSprites(); // toggle this off to change it only when you tap.
}

void Drawable::PhotoPanel::UpdateMovingPhotos()
{
		_movingPhotosManager.UpdatePanelAndPhotoPositions(GetPanelPosition(), GetPanelSize(),_currentBarleyPhotos);
		ResetPanelSprites();
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

std::list<sf::Sprite> Drawable::PhotoPanel::GetPhotoPanelSprites()
{
	return _panelSprites;
}

std::vector<BarleyPhoto>& Drawable::PhotoPanel::GetCurrentBarleyPhotos()
{
	return _currentBarleyPhotos;
}
