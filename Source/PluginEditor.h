/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "WaveForm.h"
#include "ADSRComponent.h"
#include "VolumeSliders.h"
#include "LevelMeters.h"
#include "Filters.h"


//==============================================================================
/**
*/
class TexturizeAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                       public juce::Timer
{
public:
    TexturizeAudioProcessorEditor (TexturizeAudioProcessor&);
    ~TexturizeAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void timerCallback() override;

     
private:
    WaveForm mWaveForm;
    ADSRComponent mADSR;
    VolumeSliders mVolumeSliders;
    LevelMeters mLevelMeter;
    Filters mFilters;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TexturizeAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TexturizeAudioProcessorEditor)
};
 