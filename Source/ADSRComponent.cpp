/*
  ==============================================================================

	ADSRComponent.cpp
	Created: 14 Jun 2023 1:20:55am
	Author:  arthu

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ADSRComponent.h"

//==============================================================================
ADSRComponent::ADSRComponent(TexturizeAudioProcessor& p) : audioProcessor(p)
{
	//envelope dials
	const float fontSize{ 20.0f };

	//Att.
	mAttackSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	mAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
	mAttackSlider.setTextValueSuffix("s");
	addAndMakeVisible(mAttackSlider);
	mAttackLabel.setFont(fontSize);
	mAttackLabel.setText("Attack", juce::NotificationType::dontSendNotification);
	mAttackLabel.setJustificationType(juce::Justification::centredTop);
	mAttackLabel.attachToComponent(&mAttackSlider, false);
	mAttackLabel.setColour(juce::Label::textColourId, juce::Colours::black);

	mAttackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		audioProcessor.getAPVTS(), "ATTACK", mAttackSlider);

	//Dec.
	mDecaySlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	mDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
	mDecaySlider.setTextValueSuffix("s");
	addAndMakeVisible(mDecaySlider);
	mDecayLabel.setFont(fontSize);
	mDecayLabel.setText("Decay", juce::NotificationType::dontSendNotification);
	mDecayLabel.setJustificationType(juce::Justification::centredTop);
	mDecayLabel.attachToComponent(&mDecaySlider, false);
	mDecayLabel.setColour(juce::Label::textColourId, juce::Colours::black);

	mDecayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		audioProcessor.getAPVTS(), "DECAY", mDecaySlider);

	//Sus.
	mSustainSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	mSustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
	addAndMakeVisible(mSustainSlider);
	mSustainLabel.setFont(fontSize);
	mSustainLabel.setText("Sustain", juce::NotificationType::dontSendNotification);
	mSustainLabel.setJustificationType(juce::Justification::centredTop);
	mSustainLabel.attachToComponent(&mSustainSlider, false);
	mSustainLabel.setColour(juce::Label::textColourId, juce::Colours::black);

	mSustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		audioProcessor.getAPVTS(), "SUSTAIN", mSustainSlider);

	//Rel.
	mReleaseSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	mReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
	mReleaseSlider.setTextValueSuffix("s");
	addAndMakeVisible(mReleaseSlider);
	mReleaseLabel.setFont(fontSize);
	mReleaseLabel.setText("Release", juce::NotificationType::dontSendNotification);
	mReleaseLabel.setJustificationType(juce::Justification::centredTop);
	mReleaseLabel.attachToComponent(&mReleaseSlider, false);
	mReleaseLabel.setColour(juce::Label::textColourId, juce::Colours::black);

	mReleaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		audioProcessor.getAPVTS(), "RELEASE", mReleaseSlider);

}

ADSRComponent::~ADSRComponent()
{
}

void ADSRComponent::paint(juce::Graphics& g)
{
}

void ADSRComponent::resized()
{
	const int size{ 80 };
	const int border{ 30 };
	mAttackSlider.setBounds(getWidth()/2 - size * 2, getHeight() - size - border, size, size);
	mDecaySlider.setBounds(getWidth() / 2 - size, getHeight() - size - border, size, size);
	mSustainSlider.setBounds(getWidth() / 2, getHeight() - size - border, size, size);
	mReleaseSlider.setBounds(getWidth() / 2 + size, getHeight() - size - border, size, size);
}
