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
    g.setColour(juce::Colours::black);
    g.drawText("Input", getWidth()/2 -textWidth/2, mBorder/2, textWidth, textHeight, juce::Justification::centred);

    const auto sliderPos = getHeight() - juce::jmap<float>(
        mThresholdSlider.getValue(), -60.f, +6.f, mBorder, static_cast<float>(getHeight() - (mBorder + textHeight)));

    auto bounds = getLocalBounds().toFloat();
    bounds.removeFromRight((getWidth() - mWidth) / 2);
    bounds.removeFromLeft((getWidth() - mWidth) / 2);
    bounds.removeFromTop(mBorder + textHeight);
    bounds.removeFromBottom(mBorder);

    const auto scaledY = juce::jmap<float>(
        audioProcessor.getRMSLevel(), -60.f, +6.f, mBorder, static_cast<float>(getHeight() - (mBorder + textHeight)));
    
    g.setColour(juce::Colour::fromFloatRGBA(0.39f, 0.65f, 1.f, 1.f));
    g.drawRect(bounds, 5.f);

    if (scaledY <= getHeight() - sliderPos)
    {
        g.setColour(juce::Colour::fromFloatRGBA(0.39f, 0.65f, 1.f, 0.5f));
        bounds.setTop(getHeight() - scaledY);
        g.fillRect(bounds);
    }
    else
    {
        g.setColour(juce::Colours::red.withAlpha(0.5f));
        bounds.setTop(getHeight() - scaledY);
        bounds.setBottom(sliderPos);
        g.fillRect(bounds);

        g.setColour(juce::Colour::fromFloatRGBA(0.39f, 0.65f, 1.f, 0.5f));
        bounds.setBottom(getHeight() - mBorder);
        bounds.setTop(sliderPos);
        g.fillRect(bounds);
    }
    
    g.setColour(juce::Colour::fromFloatRGBA(0.39f, 0.65f, 1.f, 1.f));

    const float knobWidth{120.f};
    const float knobHeight{20.f};
    g.fillRoundedRectangle((getWidth() -knobWidth) / 2, sliderPos - knobHeight / 2, knobWidth, knobHeight, 3.f);
}

void LevelMeters::resized()
{
    mThresholdSlider.setBounds((getWidth() - mWidth) / 2, mBorder + textHeight, mWidth, getHeight() - (mBorder *2 + textHeight));
}