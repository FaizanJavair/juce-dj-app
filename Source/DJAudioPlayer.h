/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 13 Mar 2020 4:22:22pm
    Author:  matthew

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"



using namespace std;
using namespace juce;

class DJAudioPlayer : public AudioSource{
  public:

    DJAudioPlayer(AudioFormatManager& _formatManager);
    ~DJAudioPlayer();

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //Basic functionality functions
    void loadURL(URL audioURL);
    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double posInSecs);
    void setPositionRelative(double pos);

    //Reverb Functions
    void setWetLevel(float wetVal);
    void setDryLevel(float dryVal);
    void setRoomSize(float rsVal);
    void setWidth(float widthVal);
    void setDamp(float dampVal);
    void setFreeze(bool toggleFreeze);
    void reset();
   
    
  
    double getLengthInSeconds();
   
  
    void start();
    void stop();

  

    /** get the relative position of the playhead */
    double getPositionRelative();

private:
    AudioFormatManager& formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource; 
    ResamplingAudioSource resampleSource{&transportSource, false, 2};

   //Reverb
    ReverbAudioSource reverbSource{ &resampleSource, false };
    Reverb::Parameters revParams;
  
};




