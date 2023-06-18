/*
  ==============================================================================

    VolumeSliders.cpp
    Created: 15 Jun 2023 7:04:38pm
    Author:  arthu

  ==============================================================================
*/

#include <JuceHeader.h>
#include "VolumeSliders.h"

//==============================================================================
VolumeSliders::VolumeSliders(TexturizeAudioProcessor& p) : audioProcessor(p)
{
    //dry slider
    mDrySlider.setSliderStyle(juce::Slider::LinearVertical);
    mDrySlider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(mDrySlider);
    mDryLabel.setFont(mFontSize);
    mDryLabel.setText("Dry", juce::NotificationType::dontSendNotification);
    mDryLabel.setJustificationType(juce::Justification::centredTop);
    mDryLabel.attachToComponent(&mDrySlider, false);

    mDryAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.getAPVTS(), "DRY", mDrySlider);
    

    //wet slider
    mWetSlider.setSliderStyle(juce::Slider::LinearVertical);
    mWetSlider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    addAndMakeVisible(mWetSlider);
    mWetLabel.setFont(mFontSize);
    mWetLabel.setText("Wet", juce::NotificationType::dontSendNotification);
    mWetLabel.setJustificationType(juce::Justification::centredTop);
    mWetLabel.attachToComponent(&mWetSlider, false);

    mWetAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.getAPVTS(), "WET", mWetSlider);
}

VolumeSliders::~VolumeSliders()
{
}

void VolumeSliders::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::green);
}

void VolumeSliders::resized()
{
    /*
    mDrySlider.setBounds(0, mFontSize + 10, 100, getHeight() - mFontSize);
    mWetSlider.setBounds(getWidth() - 100, mFontSize + 10, 100, getHeight() - mFontSize);
    */
}