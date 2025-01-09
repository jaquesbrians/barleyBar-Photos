#include "TitleScreenInputPanel.h"
#include "WindowManager.h"

//TODO: January 2, 2025
// 1.) Figure out what we can take from TitleScreenInputPanel and StartingInputPanel and put into Input Panel proper
// 2.) Get the Switching working from the Window Manager class (Title Screen to Starting Input)
// 3.) Input Manager class is going to be WindowManager (and we'll need to figure out how to use that correctly.
// 4.) Figure out who is controlling when the switch should happen with the renderer between the two input panels
// 5.) Figure out why TitlScreen Input Panel's button's don't have any button feedback.  
// 6.) And this is a big one.  The PhotoPanel does not need to get registered twice with each panel.  There could be a group shared
// version.  That is why there is a delay between title screen and starting screen I believe.  Look at Set Up Photo Panel.cpp
#pragma region ButtonFunction

class TitleScreenInputPanelButton0 : public ButtonFunction
{
public:
    Drawable::TitleScreenInputPanel* titleScreenInputPanel;
public: void Execute()
{
    WindowManager::GetInstance()->ShowStartingInputPanel(&titleScreenInputPanel->_previewPhotoPanel);

    //Not sure if we want to destory this or keep it hidden
    if (titleScreenInputPanel)
    {
        delete titleScreenInputPanel;
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

    TitleScreenInputPanelButton0* titleScreenInputPanelButton0 = new TitleScreenInputPanelButton0;

    auto buttonIterator = _standardInputButtons.begin();
    buttonIterator->SetButtonFunction(titleScreenInputPanelButton0, "Start");
    std::advance(buttonIterator, 1);

    titleScreenInputPanelButton0->titleScreenInputPanel = this;

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