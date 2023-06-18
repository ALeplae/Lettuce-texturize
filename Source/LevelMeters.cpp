/*
  ==============================================================================

    LevelMeters.cpp
    Created: 16 Jun 2023 6:42:59pm
    Author:  arthu

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LevelMeters.h"

//==============================================================================
LevelMeters::LevelMeters(TexturizeAudioProcessor& p) : audioProcessor(p)
{
    const float fontSize{ 20.0f };
    //dry slider
    mThresholdSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    mThresholdSlider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 40, 20);
    mThresholdSlider.setAlpha(0.0f);
    addAndMakeVisible(mThresholdSlider);
    mThresholdLabel.setFont(fontSize);
    mThresholdLabel.setText("Threshold", juce::NotificationType::dontSendNotification);
    mThresholdLabel.setJustificationType(juce::Justification::centredTop);
    mThresholdLabel.attachToComponent(&mThresholdSlider, false);

    mThresholdAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.getAPVTS(), "THRESHOLD", mThresholdSlider);
}

LevelMeters::~LevelMeters()
{

}

void LevelMeters::paint (juce::Graphics& g)
{
    const auto sliderPos = getHeight() - juce::jmap<float>(
        mThresholdSlider.getValue(), -60.f, +6.f, 0.f, static_cast<float>(getHeight() - mBorder));

    auto bounds = getLocalBounds().toFloat();
    bounds.removeFromRight(mBorder);
    bounds.removeFromTop(mBorder);

    g.setColour(juce::Colours::white.withBrightness(0.4f));
    g.fillRect(bounds);

    const auto scaledY = juce::jmap<float>(audioProcessor.getRMSLevel(), -60.f, +6.f, 0.f, static_cast<float>(getHeight() - mBorder));
    
    if (scaledY <= getHeight() - sliderPos)
    {
        g.setColour(juce::Colours::white);
        g.fillRect(bounds.removeFromBottom(scaledY));
    }
    else
    {
        g.setColour(juce::Colours::red);
        g.fillRect(bounds.removeFromBottom(scaledY));

        bounds = getLocalBounds().toFloat();
        bounds.removeFromRight(mBorder);
        bounds.removeFromTop(mBorder);

        g.setColour(juce::Colours::white);
        g.fillRect(bounds.removeFromBottom(getHeight() - sliderPos));
    }

    g.setColour(juce::Colours::black);
    g.drawLine(0, sliderPos, getWidth() - mBorder, sliderPos);




    g.fillAll(juce::Colours::red);
}

void LevelMeters::resized()
{
    /*
    mThresholdSlider.setBounds(0, mBorder, getWidth() - mBorder, getHeight() - mBorder);
    */
}
