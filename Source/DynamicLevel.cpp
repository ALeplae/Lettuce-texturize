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

	//Att.
	mDynamicLevelSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	mDynamicLevelSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
	addAndMakeVisible(mDynamicLevelSlider);
	mDynamicLevelLabel.setFont(fontSize);
	mDynamicLevelLabel.setText("Intensity", juce::NotificationType::dontSendNotification);
	mDynamicLevelLabel.setJustificationType(juce::Justification::centredTop);
	mDynamicLevelLabel.attachToComponent(&mDynamicLevelSlider, false);
	mDynamicLevelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		audioProcessor.getAPVTS(), "DYN_INT", mDynamicLevelSlider);

	mSetDynamicButton.setButtonText("Dynamic");
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
	const int size{100};
	const int border{ 30 };
	mDynamicLevelSlider.setBounds(0, 100, size, size);

	mSetDynamicButton.setBounds(0, 0, size, size / 2);
}
