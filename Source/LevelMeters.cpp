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

    mThresholdAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.getAPVTS(), "THRESHOLD", mThresholdSlider);
}

LevelMeters::~LevelMeters()
{

}

void LevelMeters::paint (juce::Graphics& g)
{
    g.setFont(30.f);
    g.setColour(juce::Colours::white);
    g.drawText("Input", getWidth()/2 -textWidth/2, mBorder/2, textWidth, textHeight, juce::Justification::centred);

    const auto sliderPos = getHeight() - juce::jmap<float>(
        mThresholdSlider.getValue(), -60.f, +6.f, mBorder, static_cast<float>(getHeight() - (mBorder + textHeight)));

    auto bounds = getLocalBounds().toFloat();
    bounds.removeFromRight((getWidth() - mWidth) / 2);
    bounds.removeFromLeft((getWidth() - mWidth) / 2);
    bounds.removeFromTop(mBorder + textHeight);
    bounds.removeFromBottom(mBorder);

    g.setColour(juce::Colours::white.withBrightness(0.4f));
    g.fillRect(bounds);

    const auto scaledY = juce::jmap<float>(
        audioProcessor.getRMSLevel(), -60.f, +6.f, mBorder, static_cast<float>(getHeight() - (mBorder + textHeight)));
    
    if (scaledY <= getHeight() - sliderPos)
    {
        g.setColour(juce::Colours::white);
        bounds.setTop(getHeight() - scaledY);
        g.fillRect(bounds);
    }
    else
    {
        g.setColour(juce::Colours::red);
        bounds.setTop(getHeight() - scaledY);
        g.fillRect(bounds);

        g.setColour(juce::Colours::white);
        bounds.setTop(sliderPos);
        g.fillRect(bounds);
    }

    g.setColour(juce::Colours::black);
    g.drawLine((getWidth() - mWidth) / 2, sliderPos, getWidth()/2 + mWidth/ 2, sliderPos, 2.f);
}

void LevelMeters::resized()
{
    mThresholdSlider.setBounds((getWidth() - mWidth) / 2, mBorder + textHeight, mWidth, getHeight() - (mBorder *2 + textHeight));
}