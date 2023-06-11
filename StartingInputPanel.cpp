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
            startingInputPanel->_previewPhotoPanel.StopCyclePhotosByTime();
        }
    }
};

#pragma endregion


Drawable::StartingInputPanel::StartingInputPanel(sf::Vector2f mainPanelSize, sf::Vector2f mainPanelPosition, sf::Color mainPanelColor, 
    int numberOfButtons, ButtonPositions buttonPositions)
    : InputPanel(mainPanelSize, mainPanelPosition, mainPanelColor, numberOfButtons, buttonPositions),
    _previewPhotoPanel(sf::Vector2f(mainPanelSize.x - 300.0f, mainPanelSize.y - 75.0f), 
        sf::Vector2f(mainPanelPosition.x + 260.0f, mainPanelPosition.y + 50.0f), sf::Color(50.0f, 50.0f, 50.0f))
{

    StartingInputPanelButton0* startingInputPanelButton0 = new StartingInputPanelButton0;
    StartingInputPanelButton1* startingInputPanelButton1 = new StartingInputPanelButton1;
    StartingInputPanelButton2* startingInputPanelButton2 = new StartingInputPanelButton2;
    StartingInputPanelButton3* startingInputPanelButton3 = new StartingInputPanelButton3;
    StartingInputPanelButton4* startingInputPanelButton4 = new StartingInputPanelButton4;

    auto buttonIterator = _standardInputButtons.begin();
    buttonIterator->SetButtonFunction(startingInputPanelButton0);
    std::advance(buttonIterator, 1);
    buttonIterator->SetButtonFunction(startingInputPanelButton1);
    std::advance(buttonIterator, 1);
    buttonIterator->SetButtonFunction(startingInputPanelButton2);
    std::advance(buttonIterator, 1);
    buttonIterator->SetButtonFunction(startingInputPanelButton3);
    std::advance(buttonIterator, 1);
    buttonIterator->SetButtonFunction(startingInputPanelButton4);

    startingInputPanelButton0->startingInputPanel = this;
    startingInputPanelButton1->startingInputPanel = this;
    startingInputPanelButton2->startingInputPanel = this;
    startingInputPanelButton3->startingInputPanel = this;
    startingInputPanelButton4->startingInputPanel = this;

    SetUpPreviewPhotoPanel();
    ContainAllPanelSprites();
}


Drawable::StartingInputPanel::~StartingInputPanel()
{
}

void Drawable::StartingInputPanel::SetUpPreviewPhotoPanel()
{
}

void Drawable::StartingInputPanel::ContainAllPanelSprites()
{
    this->InputPanel::ContainAllPanelSprites();

    if (_isHidden == false)
    {
        std::list<sf::Sprite> coyPanelSprites = _previewPhotoPanel.GetPhotoPanelSprites();
        std::list<sf::Sprite>::iterator it;
        for (it = coyPanelSprites.begin();
            it != coyPanelSprites.end(); ++it)
        {
            _panelSprites.push_back(*it);
        }
    }
}

void Drawable::StartingInputPanel::UpdatePanelTimers()
{
    if (_previewPhotoPanel.GetIsCyclyingByTime())
    {
        _previewPhotoPanel.PhotoPanel::UpdatePanelTimers();
        ContainAllPanelSprites();
    }
}

void Drawable::StartingInputPanel::MovePanelPosition(sf::Vector2f panelPositionDirections)
{
    this->InputPanel::MovePanelPosition(panelPositionDirections);
    _previewPhotoPanel.PhotoPanel::MovePanelPosition(panelPositionDirections);
}


// 1.) Make Panel class just a class for show casing a panel (no buttons, ect)
// 2.) Make Input Panel Class a class for a panel with buttons
// 3.) Marianne Math needs to be a singleton
// 4.) Get preievew photo panel to be connected to picture panel permanently.  