/*
==============================================================================

DJAudioPlayer.cpp
Created: 13 Mar 2020 4:22:22pm
Author:  matthew

==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager) 
: formatManager(_formatManager)
{
    
}
DJAudioPlayer::~DJAudioPlayer()
{
   //Setting up the reverb initial values
    revParams.roomSize = 0;
    revParams.damping = 0;
    revParams.wetLevel = 0;
    revParams.dryLevel = 1;
    reverbSource.setParameters(revParams);
}

void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate) 
{
    //preparing reverb, resample and transport souce to play the audio
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    reverbSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}
void DJAudioPlayer::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{  
    //Reverb source gets the next audio block
    reverbSource.getNextAudioBlock(bufferToFill);
    
}
void DJAudioPlayer::releaseResources()
{
    //Releases all of the resources from all 
    transportSource.releaseResources();
    reverbSource.releaseResources();
    resampleSource.releaseResources();
}

void DJAudioPlayer::loadURL(URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file!
    {       
        std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource (reader, 
true)); 
        
            transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
            readerSource.reset(newSource.release());
        
        
                  
    }
}
//Setting gain function called in deckgui
void DJAudioPlayer::setGain(double gain)
{
    if (gain < 0 || gain > 1.0)
    {
        std::cout << "DJAudioPlayer::setGain gain should be between 0 and 1" << std::endl;
    }
    else {
        transportSource.setGain(gain);
    }
   
}
//setting speed function, called in deckgui
void DJAudioPlayer::setSpeed(double ratio)
{
  if (ratio < 0 || ratio > 4.0)
    {
        std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 100" << std::endl;
    }
    else {
        resampleSource.setResamplingRatio(ratio);
    }
}
//postion function called in deckgui by timer function
void DJAudioPlayer::setPosition(double posInSecs)
{
    transportSource.setPosition(posInSecs);
}
//sets relative position
void DJAudioPlayer::setPositionRelative(double pos)
{
     if (pos < 0 || pos > 1.0)
    {
        std::cout << "DJAudioPlayer::setPositionRelative pos should be between 0 and 1" << std::endl;
    }
    else {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}

//baisc start and stop functionality
void DJAudioPlayer::start()
{
    transportSource.start();
}
void DJAudioPlayer::stop()
{
  transportSource.stop();
}

double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}
//gets length in seconds of the the audio being played
double DJAudioPlayer::getLengthInSeconds()
{
    return transportSource.getLengthInSeconds();
}

//setting wet level, called in deckGUI
void DJAudioPlayer::setWetLevel(float wetVal)
{
    if (wetVal < 0 || wetVal > 1.0)
    {
        std::cout << "DJAudioPlayer::setWetLevel pos should be between 0 and 1" << std::endl;
    }
    else {
        revParams.wetLevel = wetVal;
        reverbSource.setParameters(revParams);
    }
}
//setting dry level, called in deckGUI
void DJAudioPlayer::setDryLevel(float dryVal)
{
    if (dryVal < 0 || dryVal > 1.0)
    {
        std::cout << "DJAudioPlayer::setWetLevel pos should be between 0 and 1" << std::endl;
    }
    else {
        revParams.dryLevel = dryVal;
        reverbSource.setParameters(revParams);
    }
}
//setting roomsize, called in deckGUI
void DJAudioPlayer::setRoomSize(float rsVal)
{
    if (rsVal < 0 || rsVal > 1.0)
    {
        std::cout << "DJAudioPlayer::setWetLevel pos should be between 0 and 1" << std::endl;
    }
    else {
        revParams.roomSize = rsVal;
        reverbSource.setParameters(revParams);
    }
}
//setting width, called in deckGUI
void DJAudioPlayer::setWidth(float widthVal)
{
    if (widthVal < 0 || widthVal > 1.0)
    {
        std::cout << "DJAudioPlayer::setWetLevel pos should be between 0 and 1" << std::endl;
    }
    else {
        revParams.width = widthVal;
        reverbSource.setParameters(revParams);
    }
}
//setting damp level, called in deckGUI
void DJAudioPlayer::setDamp(float dampVal)
{
    if (dampVal < 0 || dampVal > 1.0)
    {
        std::cout << "DJAudioPlayer::setWetLevel pos should be between 0 and 1" << std::endl;
    }
    else {
        revParams.damping = dampVal;
        reverbSource.setParameters(revParams);
    }
}
//toggling freeze, called in deckGUI
void DJAudioPlayer::setFreeze(bool toggleFreeze)
{
    //Toggles the Freeze Mode
    if (toggleFreeze)
    {
        revParams.freezeMode = 1;
        reverbSource.setParameters(revParams);
    }
    else
    {
        revParams.freezeMode = 0;
        reverbSource.setParameters(revParams);
    }
    
}
void DJAudioPlayer::reset()
{
    
    //Toggles the Reset Reverb
   
        revParams.roomSize = 0;
        revParams.damping = 0;
        revParams.wetLevel = 0;
        revParams.dryLevel = 1;
        reverbSource.setParameters(revParams);
    

}



