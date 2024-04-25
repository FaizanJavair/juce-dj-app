/*
  ==============================================================================

    DeckGUI.h
    Created: 13 Mar 2020 6:44:48pm
    Author:  matthew

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "OtherLookAndFeel.h"


//==============================================================================
/*
*/
class DeckGUI    : public Component,
                   public Button::Listener, 
                   public Slider::Listener, 
                   public FileDragAndDropTarget, 
                   public Timer
{
public:
    DeckGUI(int _id, DJAudioPlayer* player, 
           AudioFormatManager & 	formatManagerToUse,
           AudioThumbnailCache & 	cacheToUse );
    ~DeckGUI();

    void paint (Graphics&) override;
    void resized() override;

     /** implement Button::Listener */
    void buttonClicked (Button *) override;

    /** implement Slider::Listener */
    void sliderValueChanged (Slider *slider) override;

    bool isInterestedInFileDrag (const StringArray &files) override;
    void filesDropped (const StringArray &files, int x, int y) override; 

    void timerCallback() override; 

    

private:
    //integer to used for id input for the deck
    int id;

    //Initializing the test buttons
    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};
    TextButton freezeOffButton{ "Freeze OFF" };
    TextButton freezeButton{ "Freeze ON" };
    TextButton resetButton{ "Reset Reverb" };
  
    //Initializing the sliders and labels
    Slider volSlider; 
    Label volLabel;

    Slider speedSlider;
    Label speedLabel;

    Slider posSlider;

    Slider wetSlider;
    Label wetLabel;

    Slider drySlider;
    Label dryLabel;

    Slider rsSlider;
    Label rsLabel;

    Slider widthSlider;
    Label widthLabel;

    Slider dampSlider;
    Label dampLabel;

    //Initializing the waverform class to be used 
    WaveformDisplay waveformDisplay;

    //Pointing to the player we are using
    DJAudioPlayer* player; 

    //void function to load the audio files to the deck
    void loadAudioFile(URL audioURL);

    //setting up the loon and feel class for our custom look
    OtherLookAndFeel otherLookAndFeel;

    //adding the playlist as friend class so they both can communicate to access the player and load the music to decks
    friend class PlaylistComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
