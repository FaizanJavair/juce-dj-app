/*
  ==============================================================================

    trackFileSystem.cpp
    Created: 15 Feb 2022 1:35:51pm
    Author:  Faizan Javair

  ==============================================================================
*/

#include <JuceHeader.h>
#include "trackFileSystem.h"
#include <filesystem>
//==============================================================================
//Track files system, an object is created whenever this is called and is pushed into a vector
//gets the file, title, and the URL of the track to play it later and load in the player
trackFileSystem::trackFileSystem(juce::File _file) : file(_file),
                                                     title(_file.getFileNameWithoutExtension()),
                                                     URL(juce::URL{ _file })
{
  
}
bool trackFileSystem::operator==(const String& other) const
{
    return title == other;
}



