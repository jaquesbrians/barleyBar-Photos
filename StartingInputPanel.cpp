#include "StartingInputPanel.h"

#pragma region ButtonFunction

class StartingInputPanelButton0 : public ButtonFunction
{
    public:
    Drawable::StartingInputPanel* startingInputPanel;
    public : void Execute()
    {
        if (startingInputPanel)
        {
            startingInputPanel->_previewPhotoPanel.ManuallyCyclePhotos();
        }
    }
};
 
class StartingInputPanelButton1 : public ButtonFunction
{
    public:
    Drawable::StartingInputPanel* startingInputPanel;
    public: void Execute()
    {
        if (startingInputPanel)
        {
            startingInputPanel->_previewPhotoPanel.ManuallyCyclePhotos(false);
        }
    }
};

class StartingInputPanelButton2 : public ButtonFunction
{
    public:
    Drawable::StartingInputPanel* startingInputPanel;
    public: void Execute()
    {
        if (startingInputPanel)
        {
            startingInputPanel->_previewPhotoPanel.CyclePhotosByTime();
        }
    }
};

class StartingInputPanelButton3 : public ButtonFunction
{
    public:
    Drawable::StartingInputPanel* startingInputPanel;
    public: void Execute()
    {
        if (startingInputPanel)
        {
            startingInputPanel->_previewPhotoPanel.StopCyclePhotosByTime();
        }
    }
};

class StartingInputPanelButton4 : public ButtonFunction
{
    public:
    Drawable::StartingInputPanel* startingInputPanel;
    public: void Execute()
    {
        if (startingInputPanel)
        {
            startingInputPanel->_previewPhotoPanel.UpdateWindowLayoutMode(WindowLayoutManager::WindowLayoutMode::singleWindowLayoutMode);
        }
    }
};

class StartingInputPanelButton5 : public ButtonFunction
{
    public:
    Drawable::StartingInputPanel* startingInputPanel;
    public: void Execute()
    {
        if (startingInputPanel)
        {
            startingInputPanel->_previewPhotoPanel.UpdateWindowLayoutMode(WindowLayoutManager::WindowLayoutMode::doubleWindowLayoutMode);
        }
    }
};

#pragma endregion


Drawable::StartingInputPanel::StartingInputPanel(sf::Vector2f mainPanelSize, sf::Vector2f mainPanelPosition, sf::Color mainPanelColor, 
    int numberOfButtons, ButtonPositions buttonPositions, PhotoPanel * photoPanel)
    : InputPanel(mainPanelSize, mainPanelPosition, mainPanelColor, numberOfButtons, buttonPositions),
    _previewPhotoPanel(sf::Vector2f(mainPanelSize.x - 300.0f, mainPanelSize.y - 75.0f), 
        sf::Vector2f(mainPanelPosition.x + 260.0f, mainPanelPosition.y + 50.0f), sf::Color(150.0f, 150.0f, 150.0f))
{

    StartingInputPanelButton0* startingInputPanelButton0 = new StartingInputPanelButton0;
    StartingInputPanelButton1* startingInputPanelButton1 = new StartingInputPanelButton1;
    StartingInputPanelButton2* startingInputPanelButton2 = new StartingInputPanelButton2;
    StartingInputPanelButton3* startingInputPanelButton3 = new StartingInputPanelButton3;
    StartingInputPanelButton4* startingInputPanelButton4 = new StartingInputPanelButton4;
    StartingInputPanelButton5* startingInputPanelButton5 = new StartingInputPanelButton5;

    auto buttonIterator = _standardInputButtons.begin();
    buttonIterator->SetButtonFunction(startingInputPanelButton0, "Forward");
    std::advance(buttonIterator, 1);
    buttonIterator->SetButtonFunction(startingInputPanelButton1, "Backward");
    std::advance(buttonIterator, 1);
    buttonIterator->SetButtonFunction(startingInputPanelButton2, "Auto");
    std::advance(buttonIterator, 1);
    buttonIterator->SetButtonFunction(startingInputPanelButton3, "Stop Auto");
    std::advance(buttonIterator, 1);
    buttonIterator->SetButtonFunction(startingInputPanelButton4, "Single");
    std::advance(buttonIterator, 1);
    buttonIterator->SetButtonFunction(startingInputPanelButton5, "Double");

    startingInputPanelButton0->startingInputPanel = this;
    startingInputPanelButton1->startingInputPanel = this;
    startingInputPanelButton2->startingInputPanel = this;
    startingInputPanelButton3->startingInputPanel = this;
    startingInputPanelButton4->startingInputPanel = this;
    startingInputPanelButton5->startingInputPanel = this;

    ContainAllPanelSprites();
    SetUpPreviewPhotoPanel(photoPanel);
}


Drawable::StartingInputPanel::~StartingInputPanel()
{
}

//Things for tomorrow 20241130
//also ensure the cycle right is working as intended (I think the random choice thing might have a bug)

void Drawable::StartingInputPanel::SetUpPreviewPhotoPanel(PhotoPanel* photoPanel)
{
    _previewPhotoPanel.SetUpPhotoPanel(photoPanel);
    std::vector<BarleyPhoto>& currentBarleyPhotos = _previewPhotoPanel.GetCurrentBarleyPhotos();
    for (int i = 0; i < currentBarleyPhotos.size(); i++)
    {
        currentBarleyPhotos[i].photoAlphaSetting = BarleyPhoto::PhotoAlphaSetting::ALPHA_FADE_IN;
    }

    _previewPhotoPanel.photoCycleStyle = PhotoPanel::PhotoCycleStyle::CYCLE_RANDOM;
    _previewPhotoPanel.CyclePhotosByTime(10.0f);
}

void Drawable::StartingInputPanel::ContainAllPanelSprites()
{
    this->InputPanel::ContainAllPanelSprites();

    if (_isHidden == false)
    {
        std::list<sf::Sprite> copyPanelSprites = _previewPhotoPanel.GetPhotoPanelSprites();
        std::list<sf::Sprite>::iterator it;
        for (it = copyPanelSprites.begin();
            it != copyPanelSprites.end(); ++it)
        {
            _panelSprites.push_back(*it);
        }
    }
}

void Drawable::StartingInputPanel::UpdatePanelTimers()
{
    _previewPhotoPanel.PhotoPanel::UpdatePanelTimers();
    ContainAllPanelSprites();

   /* if (_previewPhotoPanel.GetIsCyclyingByTime())
    {
        _previewPhotoPanel.PhotoPanel::UpdatePanelTimers();
        ContainAllPanelSprites();
    }*/

    if (_previewPhotoPanel.ArePhotosMoving())
    {
        //_previewPhotoPanel.PhotoPanel::UpdateMovingPhotos();
        //ContainAllPanelSprites();
    }
}

void Drawable::StartingInputPanel::DragPanelPosition(sf::Vector2f panelPositionDirections)
{
    this->InputPanel::DragPanelPosition(panelPositionDirections);
    _previewPhotoPanel.PhotoPanel::DragPanelPosition(panelPositionDirections);
}


// 1.) Make Panel class just a class for show casing a panel (no buttons, ect)
// 2.) Make Input Panel Class a class for a panel with buttons
// 3.) Marianne Math needs to be a singleton
// 4.) Get preievew photo panel to be connected to picture panel permanently.  