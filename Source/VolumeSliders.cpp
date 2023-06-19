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
    mDrySlider.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 50, 20);
    mDrySlider.setTextValueSuffix("dB");
    addAndMakeVisible(mDrySlider);
    mDryLabel.setFont(mFontSize);
    mDryLabel.setText("Dry", juce::NotificationType::dontSendNotification);
    mDryLabel.setJustificationType(juce::Justification::centredTop);
    mDryLabel.attachToComponent(&mDrySlider, false);

    mDryAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.getAPVTS(), "DRY", mDrySlider);
    

    //wet slider
    mWetSlider.setSliderStyle(juce::Slider::LinearVertical);
    mWetSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 50, 20);
    mWetSlider.setTextValueSuffix("dB");
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
    g.setFont(30.f);
    g.setColour(juce::Colours::white);
    g.drawText("Output", getWidth() / 2 - textWidth / 2, mBorder / 2, textWidth, textHeight, juce::Justification::centred);
}

void VolumeSliders::resized()
{
    int width{ 50 };
    mDrySlider.setBounds(getWidth() / 3 - width / 2, 
        mFontSize + mBorder + textHeight, width, getHeight() - (mFontSize + mBorder * 2 + textHeight));
    mWetSlider.setBounds(getWidth() / 3 * 2 - width / 2,
        mFontSize + mBorder + textHeight, width, getHeight() - (mFontSize + mBorder * 2 + textHeight));
}