/*
  ==============================================================================

    trackFileSystem.h
    Created: 15 Feb 2022 1:35:51pm
    Author:  Faizan Javair

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace juce;

//==============================================================================
/*
*/
class trackFileSystem 
{
    public:
        trackFileSystem(File _file);
        File file;
        URL URL;
        String title;
        String length;

        bool operator==(const String& other) const;
    
   
};
