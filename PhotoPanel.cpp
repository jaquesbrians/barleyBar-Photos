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

	if (_fade == 0)
	{
		_fade = 1;
		_photoWindowClock.restart();
	}




	double deltaTime = _photoWindowClock.getElapsedTime().asSeconds();


	for (int i = 0; i < _currentBarleyPhotos.size(); i++)
	{
		_currentBarleyPhotos[i].DissolveEffectTrial(deltaTime);
	}

	

	/*float elapsedTime = clock.getElapsedTime().asSeconds();

	if (fading) {
		// Calculate alpha based on elapsed time
		float alpha = (elapsedTime / fadeDuration) * 255.0f;

		// Clamp alpha to [0, 255]
		if (alpha > 255.0f) {
			alpha = 255.0f;
			fading = false; // Stop fading once fully visible
		}

		// Set the sprite's color with the updated alpha
		sf::Color color = sprite.getColor();
		color.a = static_cast<sf::Uint8>(alpha);
		sprite.setColor(color);
	}*/


	//This one sort of works
	/*
	if (_fade == 0)
	{
		_fade = 1;
		_photoWindowClock.restart();
	}
	
	double seconds = _photoWindowClock.getElapsedTime().asSeconds();
	double whole = 1000;
	double number = 255;
	double percentage = (seconds / whole) * 100;
	double result = (number * percentage) / 100;

	for (int i = 0; i < _currentBarleyPhotos.size(); i++)
	{
		_currentBarleyPhotos[i].DissolveEffectTrial(result);
	}*/


	ResetPanelSprites(); // toggle this to change it only when you tap.  


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
