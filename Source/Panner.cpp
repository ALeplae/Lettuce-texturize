/*
  ==============================================================================

    Panner.cpp
    Created: 18 Jun 2023 5:24:07pm
    Author:  arthu

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Panner.h"

//==============================================================================
Panner::Panner(TexturizeAudioProcessor& p) : audioProcessor(p)
{
    const float fontSize{ 20.0f };

    //Low pass
    mPannerSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    mPannerSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
    addAndMakeVisible(mPannerSlider);
    mPannerLabel.setFont(fontSize);
    mPannerLabel.setText("Pan", juce::NotificationType::dontSendNotification);
    mPannerLabel.setJustificationType(juce::Justification::centredTop);
    mPannerLabel.attachToComponent(&mPannerSlider, false);
    mPannerLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    mPannerAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.getAPVTS(), "PAN", mPannerSlider);
}

Panner::~Panner()
{
}

void Panner::paint (juce::Graphics& g)
{
}

void Panner::resized()
{
    const int size{ 100 };
    const int border{ 30 };

    mPannerSlider.setBounds(getWidth()/2 - size/2, getHeight() - size, size, size);
}
