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
	mDynamicLevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		audioProcessor.getAPVTS(), "DYN_INT", mDynamicLevelSlider);

	mSetDynamicButton.setButtonText("Set dynamic level");
	mSetDynamicButton.onClick = [this] { sliderState(mSetDynamicButton.getToggleState()); };
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
