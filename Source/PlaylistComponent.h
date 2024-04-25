/*
  ==============================================================================

    PlaylistComponent.h
    Created: 11 Feb 2022 3:19:16pm
    Author:  Faizan Javair

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "trackFileSystem.h"
#include "OtherLookAndFeel.h"

using namespace juce;
using namespace std;

//==============================================================================
/*
*/
class PlaylistComponent : public juce::Component,
                            public TableListBoxModel,
                            public TextEditor::Listener,
                            public Button::Listener
{
public:
    PlaylistComponent(DJAudioPlayer* _playerData, DeckGUI* _deckGUI1, DeckGUI* _deckGUI2);
    ~PlaylistComponent() override;


    void paint (juce::Graphics&) override;
    void resized() override;

    int getNumRows() override;

    void paintRowBackground(Graphics&, 
                            int rowNumber, 
                            int width, 
                            int height, 
                            bool rowIsSelected) override;
    void paintCell(Graphics&,
        int rowNumber,
        int columnId,
        int width,
        int height,
        bool rowIsSelected) override; 

    Component* refreshComponentForCell(int rowNumber,
                                    int columnId,
                                    bool isRowSelected,
                                    Component* existingComponentToUpdate) override;
    void buttonClicked(Button* button) override;

   

    
private:
    //vector to store tracks
    vector <trackFileSystem> tracksPresent;
    //Table list component for playlist
    TableListBox tableComponent;
    //Load files buttons
    TextButton loadButton{"LOAD IN PLAYLIST"};
    TextButton loadInDeck1{ "PLAY ON DECK ONE" };
    TextButton loadInDeck2{ "PLAY ON DECK TWO" };
    TextEditor SearchPlaylist;

    DJAudioPlayer* playerData;
    DeckGUI* deckGUI1;
    DeckGUI* deckGUI2;
    
   
    //Fucntions to make the playlist work

    //Loadind the files in playlist
    void loadInPlaylist();

    //searching the playlist
    void PlaylistSearch(juce::String searchText);

    //saving the files in the playlist
    void savingInPlaylist();

    //Deleting the files in the playlist
    void delPlaylist(int id);

    //checks if the file is present in the playlist or not
    bool presentInFile(String fileNameWithoutExtension);

    //checks playlists, and returns the row number
    int checkPlaylist(String searchText);

    //loads in the file to appropriate deck
    void loadInPlayer(DeckGUI* deckGUI);

    //gets the length of the file
    String getLength(juce::URL audioURL);
    //converts the time in seconds
    String timeConversion(double sec);

    //sets up look and feel for playlist
    OtherLookAndFeel otherLookAndFeel;

    //loads the playlist with files in csv when opened again
    void loadingPlaylist();
  
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
