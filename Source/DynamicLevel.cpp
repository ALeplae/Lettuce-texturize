/*
  ==============================================================================

    DynamicLevel.cpp
    Created: 18 Jun 2023 9:01:19pm
    Author:  arthu

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DynamicLevel.h"

//==============================================================================
DynamicLevel::DynamicLevel(TexturizeAudioProcessor& p) : audioProcessor(p)
{
	const float fontSize{ 20.0f };

	mDynamicLevelSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	mDynamicLevelSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
	mDynamicLevelSlider.setEnabled(false);
	addAndMakeVisible(mDynamicLevelSlider);
	mDynamicLevelLabel.setFont(fontSize);
	mDynamicLevelLabel.setText("Intensity", juce::NotificationType::dontSendNotification);
	mDynamicLevelLabel.setJustificationType(juce::Justification::centredTop);
	mDynamicLevelLabel.attachToComponent(&mDynamicLevelSlider, false);
	mDynamicLevelLabel.setColour(juce::Label::textColourId, juce::Colours::black);

	mDynamicLevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		audioProcessor.getAPVTS(), "DYN_INT", mDynamicLevelSlider);

	mSetDynamicButton.setButtonText("Set dynamic level");
	mSetDynamicButton.onClick = [this] { sliderState(mSetDynamicButton.getToggleState()); };
	mSetDynamicButton.setColour(juce::ToggleButton::textColourId, juce::Colours::black);
	mSetDynamicButton.setColour(juce::ToggleButton::tickColourId, juce::Colour::fromFloatRGBA(0.39f, 0.65f, 1.f, 1.0f));
	mSetDynamicButton.setColour(juce::ToggleButton::tickDisabledColourId, juce::Colours::black);
	addAndMakeVisible(mSetDynamicButton);
	mSetDynamicAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
		audioProcessor.getAPVTS(), "DYN_SET", mSetDynamicButton);
}

DynamicLevel::~DynamicLevel()
{
}

void DynamicLevel::paint (juce::Graphics& g)
{
}

void DynamicLevel::resized()
{
	const int border{ 30 };
	const int sliderSize{175};
	mDynamicLevelSlider.setBounds(getWidth() / 2 - sliderSize / 2, getHeight() - sliderSize - border / 2, sliderSize, sliderSize);

	const int buttonWidth{ getWidth() - border};
	mSetDynamicButton.setBounds(border/2, border / 2, buttonWidth, 30);
}

void DynamicLevel::sliderState(bool state)
{
	mDynamicLevelSlider.setEnabled(state);
}
