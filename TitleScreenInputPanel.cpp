#include "TitleScreenInputPanel.h"

//TODO: January 2, 2025
// 1.) Figure out what we can take from TitleScreenInputPanel and StartingInputPanel and put into Input Panel proper
// 2.) Clean up TitleScreenInputPanel to have correct Button Function names
// 3.) Figure out where we will be loading the StartingInputPanel (It's gonna be called from the Button on TitleScreenInputPanel).
// 4.) So that seems like we'll need some sort of Input Panel Manager Class probably.  

#pragma region ButtonFunction

class StartingInputPanelButton0 : public ButtonFunction
{
public:
    Drawable::TitleScreenInputPanel* startingInputPanel;
public: void Execute()
{
    if (startingInputPanel)
    {
        startingInputPanel->_previewPhotoPanel.ManuallyCyclePhotos();
    }
}
};

#pragma endregion


Drawable::TitleScreenInputPanel::TitleScreenInputPanel(sf::Vector2f mainPanelSize, sf::Vector2f mainPanelPosition, sf::Color mainPanelColor,
    int numberOfButtons, ButtonPositions buttonPositions)
    : InputPanel(mainPanelSize, mainPanelPosition, mainPanelColor, numberOfButtons, buttonPositions),
    _previewPhotoPanel(sf::Vector2f(mainPanelSize.x - 300.0f, mainPanelSize.y - 75.0f),
        sf::Vector2f(mainPanelPosition.x + 260.0f, mainPanelPosition.y + 50.0f), sf::Color(150.0f, 150.0f, 150.0f))
{

    StartingInputPanelButton0* startingInputPanelButton0 = new StartingInputPanelButton0;

    auto buttonIterator = _standardInputButtons.begin();
    buttonIterator->SetButtonFunction(startingInputPanelButton0, "Forward");
    std::advance(buttonIterator, 1);

    startingInputPanelButton0->startingInputPanel = this;

    ContainAllPanelSprites();
    SetUpPreviewPhotoPanel();
}


Drawable::TitleScreenInputPanel::~TitleScreenInputPanel()
{
}

//Things for tomorrow 20241130
//also ensure the cycle right is working as intended (I think the random choice thing might have a bug)

void Drawable::TitleScreenInputPanel::SetUpPreviewPhotoPanel()
{
    _previewPhotoPanel.SetUpPhotoPanel();
    std::vector<BarleyPhoto>& currentBarleyPhotos = _previewPhotoPanel.GetCurrentBarleyPhotos();
    for (int i = 0; i < currentBarleyPhotos.size(); i++)
    {
        currentBarleyPhotos[i].photoAlphaSetting = BarleyPhoto::PhotoAlphaSetting::ALPHA_FADE_IN;
    }

    _previewPhotoPanel.photoCycleStyle = PhotoPanel::PhotoCycleStyle::CYCLE_RANDOM;
    _previewPhotoPanel.CyclePhotosByTime(10.0f);
}

void Drawable::TitleScreenInputPanel::ContainAllPanelSprites()
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

void Drawable::TitleScreenInputPanel::UpdatePanelTimers()
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

void Drawable::TitleScreenInputPanel::DragPanelPosition(sf::Vector2f panelPositionDirections)
{
    this->InputPanel::DragPanelPosition(panelPositionDirections);
    _previewPhotoPanel.PhotoPanel::DragPanelPosition(panelPositionDirections);
}


// 1.) Make Panel class just a class for show casing a panel (no buttons, ect)
// 2.) Make Input Panel Class a class for a panel with buttons
// 3.) Marianne Math needs to be a singleton
// 4.) Get preievew photo panel to be connected to picture panel permanently.  