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
    const float mBorder{ 30.0f };


    juce::Slider mThresholdSlider;
    juce::Label mThresholdLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mThresholdAttachment;

    TexturizeAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LevelMeters)
};
