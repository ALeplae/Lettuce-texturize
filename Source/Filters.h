/*
  ==============================================================================

    Filters.h
    Created: 17 Jun 2023 11:48:08pm
    Author:  arthu

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filters  : public juce::Component
{
public:
    Filters(TexturizeAudioProcessor& p);
    ~Filters() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider mLowPassSlider, mHighPassSlider;
    juce::Label mLowPassLabel, mHighPassLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mLowPassAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mHighPassAttachment;

    TexturizeAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filters)
};
