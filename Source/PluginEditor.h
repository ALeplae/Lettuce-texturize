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
                                        private juce::Slider::Listener
{
public:
    TexturizeAudioProcessorEditor (TexturizeAudioProcessor&);
    ~TexturizeAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::TextButton mLoadButton;
    void loadFile();







    //-----------------old attempt-------------------

    void playButtonClicked();
    void stopButtonClicked();


    juce::AudioFormatManager mFormatManager;
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
