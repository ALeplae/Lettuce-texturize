/*
  ==============================================================================

    DynamicLevel.h
    Created: 18 Jun 2023 9:01:19pm
    Author:  arthu

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class DynamicLevel  : public juce::Component
{
public:
    DynamicLevel(TexturizeAudioProcessor& p);
    ~DynamicLevel() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void DynamicLevel::sliderState(bool state);

private:
    juce::Slider mDynamicLevelSlider;
    juce::ToggleButton mSetDynamicButton;
    juce::Label mDynamicLevelLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mDynamicLevelAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> mSetDynamicAttachment;

    TexturizeAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DynamicLevel)
};
