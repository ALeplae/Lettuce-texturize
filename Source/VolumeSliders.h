/*
  ==============================================================================

    VolumeSliders.h
    Created: 15 Jun 2023 7:04:38pm
    Author:  arthu

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"



//==============================================================================
/*
*/
class VolumeSliders  : public juce::Component
{
public:
    VolumeSliders(TexturizeAudioProcessor& p);
    ~VolumeSliders() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    const int textWidth{ 100 };
    const int textHeight{ 50 };
    const int mBorder{ 30 };

    const float mFontSize{ 20.0f };
    juce::Slider mDrySlider, mWetSlider;
    juce::Label mDryLabel, mWetLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mDryAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mWetAttachment;



    TexturizeAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VolumeSliders)
};
