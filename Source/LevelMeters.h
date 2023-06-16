/*
  ==============================================================================

    LevelMeters.h
    Created: 16 Jun 2023 6:42:59pm
    Author:  arthu

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class LevelMeters  : public juce::Component
{
public:
    LevelMeters(TexturizeAudioProcessor& p);
    ~LevelMeters() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider mThreshHoldSlider

    TexturizeAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LevelMeters)
};
