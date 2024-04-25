/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 11 Feb 2022 3:19:16pm
    Author:  Faizan Javair

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

using namespace juce;
using namespace std;

//==============================================================================
PlaylistComponent::PlaylistComponent(DJAudioPlayer* _playerData, DeckGUI* _deckGUI1, DeckGUI* _deckGUI2)
    : playerData(_playerData), deckGUI1(_deckGUI1), deckGUI2(_deckGUI2)
                                    
{

    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
   
    

    //Setting up the header for table
    tableComponent.getHeader().addColumn("Track title", 1, 400);
    tableComponent.getHeader().addColumn("Length", 2, 200);
    tableComponent.getHeader().addColumn("", 3, 200);

    //Loading our playlist
    loadingPlaylist();

    //setting up our table use just like buttons and sliders
    tableComponent.setModel(this);
    addAndMakeVisible(tableComponent);

    //Making buttons visible
    addAndMakeVisible(loadButton);
    addAndMakeVisible(loadInDeck1);
    addAndMakeVisible(loadInDeck2);
    addAndMakeVisible(SearchPlaylist);

    //Adding button listener
    SearchPlaylist.addListener(this);
    loadButton.addListener(this);
    loadInDeck1.addListener(this);
    loadInDeck2.addListener(this);

    //Setting button look and feel
    loadInDeck1.setColour(TextButton::buttonColourId, Colours::beige);
    loadInDeck2.setColour(TextButton::buttonColourId, Colours::beige);
    loadButton.setColour(TextButton::buttonColourId, Colours::beige);

  

    //Setting button text color when off
    loadButton.setColour(TextButton::textColourOffId, Colours::lightcoral);
    loadInDeck1.setColour(TextButton::textColourOffId, Colours::lightcoral);
    loadInDeck2.setColour(TextButton::textColourOffId, Colours::lightcoral);

    //setting table look and feel
    tableComponent.setLookAndFeel(&otherLookAndFeel);
    
    //Search box look and feel
    SearchPlaylist.setLookAndFeel(&otherLookAndFeel);
    //Search box text color and getting the text from the playlist and searching the playlist
    SearchPlaylist.setTextToShowWhenEmpty("Search Your Music Here....", Colours::beige);
    SearchPlaylist.onReturnKey = [this] { PlaylistSearch(SearchPlaylist.getText()); };

}

PlaylistComponent::~PlaylistComponent()
{
    //Upon the destructor is called, the playlist is saved in a CSV file to be used later after reopening
    savingInPlaylist();
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    loadButton.setBounds(0 , getHeight() * 0.25, getWidth() / 4, getHeight() * 0.25);
    SearchPlaylist.setBounds(0, 0, getWidth() /4 , getHeight() * 0.25);

    loadInDeck1.setBounds(0, getHeight()*0.5, getWidth() / 4, getHeight() * 0.25);
    loadInDeck2.setBounds(0, getHeight() * 0.75, getWidth() / 4, getHeight() * 0.25);

    tableComponent.setBounds(getWidth() /4, 0, getWidth() * 3/4, getHeight());
}

int PlaylistComponent::getNumRows()
{
    return tracksPresent.size();
}

void PlaylistComponent::paintRowBackground(Graphics& g,
    int rowNumber,
    int width,
    int height,
    bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(Colours::lightcoral);
    }
    else
    {
        g.fillAll(Colours::mediumaquamarine);
    }

}
void PlaylistComponent::paintCell(Graphics& g,
    int rowNumber,
    int columnId,
    int width,
    int height,
    bool rowIsSelected)
{   
    g.setColour(Colours::beige);
    if (rowNumber < getNumRows())
    {
        if (columnId == 1)
        {
            g.drawText(tracksPresent[rowNumber].title,
                2,
                0,
                width - 4,
                height,
                Justification::centredLeft,
                true
            );
        }
        if (columnId == 2)
        {
            g.drawText(tracksPresent[rowNumber].length,
                2,
                0,
                width - 4,
                height,
                Justification::centred,
                true
            );
        }
    }
  
}
Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
                                                    int columnId,
                                                    bool isRowSelected,
                                                    Component* existingComponentToUpdate)
{
    if (columnId == 3)
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton* btn = new TextButton{ "REMOVE" };
            String id{std::to_string(rowNumber)};
            btn->setComponentID(id);

            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
}
void PlaylistComponent::buttonClicked(juce::Button* button)
{
    if (button == &loadButton)
    {
        loadInPlaylist();
        tableComponent.updateContent();
    }
    else if (button == &loadInDeck1)
    {
        
        loadInPlayer(deckGUI1);
    }
    else if (button == &loadInDeck2)
    {
       
        loadInPlayer(deckGUI2);
    }
    else
    {
        int id = std::stoi(button->getComponentID().toStdString());
        delPlaylist(id);
        tableComponent.updateContent();
    }
}

//Loading file in the playlist
void PlaylistComponent::loadInPlaylist()
{
  
    //initialize file chooser
    FileChooser chooser{ "Select files" };
    //checks if multiple files are chosen
    if (chooser.browseForMultipleFilesToOpen())
    {
        //if so, then the choser fetches the files
        for (const File& file : chooser.getResults())
        {
            //gets file name without extension
            String fileNameWithoutExtension{ file.getFileNameWithoutExtension() };
            if (!presentInFile(fileNameWithoutExtension)) // if not already loaded
            {
                //Makes a new object with file, loads the URL, and pushes the track into the vector of tracks in the playlist
                trackFileSystem newTrack{ file };
                URL audioURL{ file };
                //gets the lenght of the audioURL
                newTrack.length = getLength(audioURL);
                //pushing to vector of files in playlist
                tracksPresent.push_back(newTrack);
                DBG("Track is loaded: " << newTrack.title);
            }
            else // display info message
            {
                //If file is already loaded then alret message is shown
                AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::InfoIcon,
                    "This track is",
                    fileNameWithoutExtension + " already loaded - Please choose a different one",
                    "Done",
                    nullptr
                );
            }
        }
    }
}

bool PlaylistComponent::presentInFile(String fileNameWithoutExtension)
{
    //searches if the file is present in the playlist or not
    return (find(tracksPresent.begin(), tracksPresent.end(), fileNameWithoutExtension) != tracksPresent.end());
}
//===============================================================================
// Loading and Deleting files
//Loading the file in our decks to play
void PlaylistComponent::loadInPlayer(DeckGUI* deckGUI)
{
    //Loads the track selected to the appropriate deck
    int selectedRow{ tableComponent.getSelectedRow() };
    if (selectedRow != -1)
    {

        deckGUI->loadAudioFile(tracksPresent[selectedRow].URL);
    }
    else
    {
        //
        AlertWindow::showMessageBox(AlertWindow::AlertIconType::InfoIcon,
            "Error: ",
            "Select an appropriate track from the playlist to load",
            "Done",
            nullptr
        );
    }
}
void PlaylistComponent::delPlaylist(int id)
{
    //delete's the track by using the id and the normal c++ erase method from the filesystem created
    tracksPresent.erase(tracksPresent.begin() + id);
}

//===============================================================================
// Searching Playlist functions working together
//Searching playlist for the text input
void PlaylistComponent::PlaylistSearch(String searchText)
{
    //checks if the input in non empty
    if (searchText != "")
    {
        //assigns the integer
        int rowNumber = checkPlaylist(searchText);
        //selects row if match is found
        tableComponent.selectRow(rowNumber);
    }
    else
    {
        //deselects all the rows if no match is found
        tableComponent.deselectAllRows();
    }
}
int PlaylistComponent::checkPlaylist(String searchText)
{
    // finds the tracks you want to play by using the text from search as input and checking the file for a match
    auto it = find_if(tracksPresent.begin(), tracksPresent.end(),
        [&searchText](const trackFileSystem& obj) {return obj.title.contains(searchText); });
    int i = -1;
    //checks where the track is present in the playlist
    if (it != tracksPresent.end())
    {
        i = distance(tracksPresent.begin(), it);
    }
    //returns the position of the appropriate row number
    return i;
}

//===============================================================================
//Time Conversion + Display on Playlist
String PlaylistComponent::getLength(juce::URL audioURL)
{
    //gets the length of the file loaded
    playerData->loadURL(audioURL);
    //saves the value in seconds to a variable
    double seconds{ playerData->getLengthInSeconds()};
    //converts the values into minutes by calling the timeConversion function
    String minutes{ timeConversion(seconds) };
    return minutes;
}
//Converts the time into minutes and then is used to display the track time
String PlaylistComponent::timeConversion(double sec)
{
    //gets the values of seconds and rounds it
    int roundT{ int(std::round(sec)) };
    //uses the rounded value into string and gets the time in minutes
    String minutes{ to_string(roundT / 60) };
    //uses the rounded value to take out the seconds after the minute has passed
    String seconds{ to_string(roundT % 60) };

    // conditional statement to check if the time is lesser than 2 seconds
    if (seconds.length() < 2) 
    {
        //add '0' to seconds until seconds is length 2
        seconds = seconds.paddedLeft('0', 2);
    }
    //Returns the time in minutes and seconds, then used to display in playlist
    return String{ minutes + ":" + seconds };
}

//===============================================================================
//Saving current playlist and loading it again when app is opened again
void PlaylistComponent::savingInPlaylist()
{
    // creating a csv file to save the playlist to use later
    ofstream myPlaylist("playlist.csv");

    // saving the playlist to a csv file to use later
    for (trackFileSystem& t : tracksPresent)
    {
        myPlaylist << t.file.getFullPathName() << "," << t.length << "\n";
    }
}

void PlaylistComponent::loadingPlaylist()
{
    // inputing from the saved playlist
    ifstream myPlaylist("playlist.csv");
    string filePath;
    string length;

    // Reading the data by going through each line of the file
    if (myPlaylist.is_open())
    {
        //Reads the data of the csv file and inputs it into the vector again
        while (getline(myPlaylist, filePath, ',')) {
            File file{ filePath };
            trackFileSystem newTrack{ file };

            getline(myPlaylist, length);
            newTrack.length = length;
            tracksPresent.push_back(newTrack);
        }
    }
    //closes the playlist in the end
    myPlaylist.close();
}

//===============================================================================
