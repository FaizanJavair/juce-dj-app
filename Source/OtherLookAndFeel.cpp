/*
  ==============================================================================

    OtherLookAndFeel.cpp
    Created: 19 Feb 2022 7:23:11pm
    Author:  Faizan Javair

  ==============================================================================
*/

#include "OtherLookAndFeel.h"
using namespace juce;

OtherLookAndFeel::OtherLookAndFeel()
{
    //For Rotary Slider
    setColour(Slider::rotarySliderOutlineColourId, Colours::beige);
    setColour(Slider::rotarySliderFillColourId, Colours::peachpuff);
    setColour(Slider::thumbColourId, Colours::aquamarine);
    setColour(Slider::textBoxOutlineColourId, Colours::beige);
    setColour(Slider::textBoxTextColourId, Colours::lightcoral);
    setColour(Slider::textBoxHighlightColourId, Colours::beige);

    //for traditional Slider
    setColour(Slider::trackColourId, Colours::beige);
    setColour(Slider::backgroundColourId, Colours::peachpuff);

    //for Search Playlist
    setColour(TextEditor::backgroundColourId, Colours::lightcoral);

    //For Table Box
    setColour(TableListBox::backgroundColourId, Colours::mediumaquamarine);
    setColour(TableListBox::outlineColourId, Colours::lightcoral);
    setColour(TableListBox::textColourId, Colours::beige);
    setColour(TableHeaderComponent::backgroundColourId, Colours::beige);
    setColour(TableHeaderComponent::textColourId, Colours::lightcoral);
   
    //For Buttons
    setColour(TextButton::buttonColourId, Colours::lightcoral);
    setColour(TextButton::textColourOffId, Colours::peachpuff);
    setColour(TextButton::textColourOnId, Colours::beige);

    //For Labels
    setColour(Label::textColourId, Colours::peachpuff);
    


}
