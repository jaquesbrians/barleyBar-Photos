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
		_windowLayoutManager.SetPhotoInitialPositionAndScale(_barleyPhotoMaps[photoIndex]); 

		photoIndex++;
	}

	_barleyPhotoMapSize = photoIndex;

	//_currentBarleyPhoto = _barleyPhotoMaps[_currentBarleyPhotoIndex];
	//_barleyPhotoMapSize = photoIndex;
	//ResetPanelSprites();

	RandomlyCyclePhoto();
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

	//_currentBarleyPhoto = _barleyPhotoMaps[_currentBarleyPhotoIndex];


	//Things do to for tomorrow
	// Get both single panels and double panels working again.  Has to do with currentBarleyPhoto vs currentBarlyePhotos list
	// figure out why you wanted to not clear this after changing.  Probably a single vs double layout thing. 20230607

	_currentBarleyPhotos.clear(); 

	_currentBarleyPhotos.push_back(_barleyPhotoMaps[_currentBarleyPhotoIndex]);


	ResetPanelSprites();
}

void Drawable::PhotoPanel::RandomlyCyclePhoto()
{
	for (int i = 0; i < _windowLayoutManager.numberOfPhotosPerWindow; i++)
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
	//_currentBarleyPhoto = _barleyPhotoMaps[selectedPhoto];

	_currentBarleyPhotos.push_back(_barleyPhotoMaps[selectedPhoto]);
	//_currentBarleyPhotos.push_back(_barleyPhotoMaps[1]);
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

void Drawable::PhotoPanel::MovePanelPosition(sf::Vector2f panelPositionDirections)
{
	MovePanelPosition(panelPositionDirections);
	//_currentBarleyPhoto.SetSpritePosition(panelPositionDirections);


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
	//_panelSprites.push_back(_currentBarleyPhoto.barleySprite);

	for (int i = 0; i < _currentBarleyPhotos.size(); i++)
	{
		_panelSprites.push_back(_currentBarleyPhotos[i].barleySprite);
	}
}
