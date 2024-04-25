/*
  ==============================================================================

    DeckGUI.cpp
    Created: 13 Mar 2020 6:44:48pm
    Author:  matthew

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(int _id,DJAudioPlayer* _player, 
                AudioFormatManager & 	formatManagerToUse,
                AudioThumbnailCache & 	cacheToUse
           ) : player(_player), id(_id),
               waveformDisplay(formatManagerToUse, cacheToUse)
{

    

    //Making Buttons visible
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(freezeButton);
    addAndMakeVisible(freezeOffButton);
    addAndMakeVisible(resetButton);
    
    //Label
    addAndMakeVisible(volLabel);
    addAndMakeVisible(speedLabel);
    addAndMakeVisible(wetLabel);
    addAndMakeVisible(dryLabel);
    addAndMakeVisible(rsLabel);
    addAndMakeVisible(widthLabel);
    addAndMakeVisible(dampLabel);

    //Setting default values of the sliders
    double speedDefVal = 1;
    double volDefVal = 1;
    double dryDefVal = 1;

    //Setting the values
    speedSlider.setValue(speedDefVal);
    
    volSlider.setValue(volDefVal);
   
    drySlider.setValue(dryDefVal);
    
   

    //Setting Text to Components
    volLabel.setText("Volume", dontSendNotification);
    volLabel.attachToComponent(&volSlider, false);
    volLabel.setJustificationType(Justification::centred);

    speedLabel.setText("Speed", dontSendNotification);
    speedLabel.attachToComponent(&speedSlider, false);
    speedLabel.setJustificationType(Justification::centredTop);
    
    wetLabel.setText("Wet", dontSendNotification);
    wetLabel.attachToComponent(&wetSlider, false);
    wetLabel.setJustificationType(Justification::centredTop);
    
    dryLabel.setText("Dry", dontSendNotification);
    dryLabel.attachToComponent(&drySlider, false);
    dryLabel.setJustificationType(Justification::centredTop);
    
    dampLabel.setText("Damp", dontSendNotification);
    dampLabel.attachToComponent(&dampSlider, false);
    dampLabel.setJustificationType(Justification::centredTop);
    
    widthLabel.setText("Width", dontSendNotification);
    widthLabel.attachToComponent(&widthSlider, false);
    widthLabel.setJustificationType(Justification::centredTop);

    
    rsLabel.setText("Room Size", dontSendNotification);
    rsLabel.attachToComponent(&rsSlider, false);
    rsLabel.setJustificationType(Justification::centredTop);
    //Making Slider Visible
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    

    //Reverb Slider Visible
    addAndMakeVisible(wetSlider);
    addAndMakeVisible(drySlider);
    addAndMakeVisible(dampSlider);
    addAndMakeVisible(rsSlider);
    addAndMakeVisible(widthSlider);

    //Making Waveform visible
    addAndMakeVisible(waveformDisplay);

    //Button Listener
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    freezeButton.addListener(this);
    freezeOffButton.addListener(this);
    resetButton.addListener(this);

    //Slider Listener
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    //Reverb Listener
    wetSlider.addListener(this);
    drySlider.addListener(this);
    dampSlider.addListener(this);
    rsSlider.addListener(this);
    widthSlider.addListener(this);

    //Setting Rnage of slider
    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 4.0);
    posSlider.setRange(0.0, 1.0);
    //Reverb Range
    wetSlider.setRange(0.0, 1.0);
    dampSlider.setRange(0.0, 1.0);
    rsSlider.setRange(0.0, 1.0);
    drySlider.setRange(0.0, 1.0);
    widthSlider.setRange(0.0, 1.0);

     //Setting Decimal places
    speedSlider.setNumDecimalPlacesToDisplay(2);
    volSlider.setNumDecimalPlacesToDisplay(2);
    wetSlider.setNumDecimalPlacesToDisplay(2);
    drySlider.setNumDecimalPlacesToDisplay(2);
    widthSlider.setNumDecimalPlacesToDisplay(2);
    rsSlider.setNumDecimalPlacesToDisplay(2);
    dampSlider.setNumDecimalPlacesToDisplay(2);
    
    //Slider style

    //Reverb set slider style
    wetSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    drySlider.setSliderStyle(Slider::SliderStyle::Rotary);
    dampSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    widthSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    rsSlider.setSliderStyle(Slider::SliderStyle::Rotary);

   //Normal Sliders
    volSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
    speedSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
    posSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 100, 25);

    //Reverb Sliders
    wetSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
    drySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
    rsSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
    widthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);
    dampSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 25);


    //Setting look and feel for sliders
    volSlider.setLookAndFeel(&otherLookAndFeel);
    speedSlider.setLookAndFeel(&otherLookAndFeel);
    posSlider.setLookAndFeel(&otherLookAndFeel);
    wetSlider.setLookAndFeel(&otherLookAndFeel);
    drySlider.setLookAndFeel(&otherLookAndFeel);
    rsSlider.setLookAndFeel(&otherLookAndFeel);
    widthSlider.setLookAndFeel(&otherLookAndFeel);
    dampSlider.setLookAndFeel(&otherLookAndFeel);


    //Setting look and feel for buttons
    loadButton.setLookAndFeel(&otherLookAndFeel);
    stopButton.setLookAndFeel(&otherLookAndFeel);
    playButton.setLookAndFeel(&otherLookAndFeel);
    freezeButton.setLookAndFeel(&otherLookAndFeel);
    freezeOffButton.setLookAndFeel(&otherLookAndFeel);
    resetButton.setLookAndFeel(&otherLookAndFeel);

    //setting look and feel for labels
    volLabel.setLookAndFeel(&otherLookAndFeel);
    speedLabel.setLookAndFeel(&otherLookAndFeel);
    wetLabel.setLookAndFeel(&otherLookAndFeel);
    dryLabel.setLookAndFeel(&otherLookAndFeel);
    widthLabel.setLookAndFeel(&otherLookAndFeel);
    rsLabel.setLookAndFeel(&otherLookAndFeel);
    dampLabel.setLookAndFeel(&otherLookAndFeel);

    //timer
    startTimer(500);


}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    double rowH = getHeight() / 12;
    g.fillAll (Colours::darkcyan);   // clear the background

    g.setColour (Colours::floralwhite);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::black);
    g.setFont (14.0f);
   /* g.drawText ("DeckGUI", getLocalBounds(),
                Justification::centred, true);  */ // draw some placeholder text
}

void DeckGUI::resized()
{
    //variable to be used to make sure that the  all components are realtive to each other
    double rowH = getHeight() / 19; 

    //Button position
    playButton.setBounds(0, 0, getWidth() / 2, rowH );
    stopButton.setBounds(getWidth()/2, 0, getWidth() / 2, rowH);
    volSlider.setBounds(0, rowH * 2, getWidth()/2, rowH*2);
    speedSlider.setBounds(getWidth() / 2, rowH * 2, getWidth()/2, rowH*2);
    
    //Waveform position
    waveformDisplay.setBounds(0, rowH * 4, getWidth(), rowH * 2);
    posSlider.setBounds(0, rowH * 6, getWidth(), rowH * 2);
   
    //load button position
    loadButton.setBounds(0, rowH * 8, getWidth(), rowH);

    //Reverb slider position
    wetSlider.setBounds(getWidth() * 0.125, rowH * 10, getWidth()/4, rowH*3);
    drySlider.setBounds(getWidth() * 0.625, rowH * 10, getWidth()/4, rowH*3);
    widthSlider.setBounds(getWidth() * 0.125, rowH * 15, getWidth()/4, rowH*3);
    rsSlider.setBounds(getWidth() * 0.625, rowH * 15, getWidth()/4, rowH*3);
    dampSlider.setBounds(getWidth()* 0.375, rowH * 13, getWidth()/4, rowH*3);
    freezeButton.setBounds(0, rowH * 18, getWidth()/3, rowH*1.5);
    freezeOffButton.setBounds(getWidth()/3, rowH * 18, getWidth() / 3, rowH*1.5);
    resetButton.setBounds(getWidth() * 2/3, rowH * 18, getWidth() / 3, rowH * 1.5);

    

}

void DeckGUI::buttonClicked(Button* button)
{
    //Events for buttons
    if (button == &playButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        player->start();
    }
    if (button == &stopButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        player->stop();
        player->setFreeze(false);

    }

     if (button == &freezeButton)
     {
         std::cout << "freezeButton was clicked " << std::endl;
         player->setFreeze(true);
        
         
     }

     if (button == &freezeOffButton)
     {
         std::cout << "freeze1Button was clicked " << std::endl;
         player->setFreeze(false);


     }
    
     if (button == &resetButton)
     {
         std::cout << "resetButton was clicked " << std::endl;
         player->reset();

         //Resetting reverb slider values
         drySlider.setValue(1);
         wetSlider.setValue(0);
         rsSlider.setValue(0);
         widthSlider.setValue(0);
         dampSlider.setValue(0);
         //toggling freeze off
         player->setFreeze(false);
     }

    if (button == &loadButton)
    {
        FileChooser chooser{"Select a file..."};
        if (chooser.browseForFileToOpen())
        {
            loadAudioFile(URL{ chooser.getResult() });
        }
    }
}

void DeckGUI::sliderValueChanged (Slider *slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }

    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    
    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }

    //Slider Reverb setting values
    if (slider == &wetSlider)
    {
        player->setWetLevel(slider->getValue());
    }
    if (slider == &drySlider)
    {
        player->setDryLevel(slider->getValue());
    }
    if (slider == &widthSlider)
    {
        player->setWidth(slider->getValue());
        
    }
    if (slider == &rsSlider)
    {
        player->setRoomSize(slider->getValue());
    }
    if (slider == &dampSlider)
    {
        player->setDamp(slider->getValue());
    }
    
}

bool DeckGUI::isInterestedInFileDrag (const StringArray &files)
{
  std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
  return true; 
}

void DeckGUI::filesDropped (const StringArray &files, int x, int y)
{
  std::cout << "DeckGUI::filesDropped" << std::endl;
  if (files.size() == 1)
  {
    player->loadURL(URL{File{files[0]}});
  }
}

void DeckGUI::timerCallback()
{
    
    waveformDisplay.setPositionRelative(
            player->getPositionRelative());
}

void DeckGUI::loadAudioFile(URL audioURL)
{
    player->loadURL(audioURL);
    waveformDisplay.loadURL(audioURL);
}
 

    

