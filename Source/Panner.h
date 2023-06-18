/*
  ==============================================================================

    Panner.h
    Created: 18 Jun 2023 5:24:07pm
    Author:  arthu

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Panner  : public juce::Component
{
public:
    Panner(TexturizeAudioProcessor& p);
    ~Panner() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider mPannerSlider;
    juce::Label mPannerLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mPannerAttachment;

    TexturizeAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Panner)
};
