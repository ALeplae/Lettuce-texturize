/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TexturizeAudioProcessorEditor  : public juce::AudioProcessorEditor, 
                                       public juce::FileDragAndDropTarget,
                                       private juce::Slider::Listener
{
public:
    TexturizeAudioProcessorEditor (TexturizeAudioProcessor&);
    ~TexturizeAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;

private:
    juce::TextButton mLoadButton;
    void loadFile();
    void loadFile(const juce::String& path);

	void renameLoadButton();

    std::vector<float> mAudioPoints;
    bool mShouldBePainting{ false };

    void playButtonClicked();
    void stopButtonClicked();



    std::unique_ptr<juce::AudioFormatReaderSource> playSource;
    
    std::unique_ptr<juce::FileChooser> fileChooser;
    

    juce::TextButton playButton;
    juce::TextButton stopButton;




    //-----------------slider test-------------------
    void sliderValueChanged(juce::Slider* slider) override;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TexturizeAudioProcessor& audioProcessor;

    juce::Slider inputVolume; //[1]

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TexturizeAudioProcessorEditor)
};
