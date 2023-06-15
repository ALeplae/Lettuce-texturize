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
	addAndMakeVisible(mAttackSlider);
	mAttackLabel.setFont(fontSize);
	mAttackLabel.setText("Attack", juce::NotificationType::dontSendNotification);
	mAttackLabel.setJustificationType(juce::Justification::centredTop);
	mAttackLabel.attachToComponent(&mAttackSlider, false);

	mAttackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		audioProcessor.getAPVTS(), "ATTACK", mAttackSlider);

	//Dec.
	mDecaySlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	mDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
	addAndMakeVisible(mDecaySlider);
	mDecayLabel.setFont(fontSize);
	mDecayLabel.setText("Decay", juce::NotificationType::dontSendNotification);
	mDecayLabel.setJustificationType(juce::Justification::centredTop);
	mDecayLabel.attachToComponent(&mDecaySlider, false);

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

	mSustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		audioProcessor.getAPVTS(), "SUSTAIN", mSustainSlider);

	//Rel.
	mReleaseSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	mReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
	addAndMakeVisible(mReleaseSlider);
	mReleaseLabel.setFont(fontSize);
	mReleaseLabel.setText("Release", juce::NotificationType::dontSendNotification);
	mReleaseLabel.setJustificationType(juce::Justification::centredTop);
	mReleaseLabel.attachToComponent(&mReleaseSlider, false);

	mReleaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		audioProcessor.getAPVTS(), "RELEASE", mReleaseSlider);
}

ADSRComponent::~ADSRComponent()
{
}

void ADSRComponent::paint (juce::Graphics& g)
{
	g.fillAll(juce::Colours::black);
}

void ADSRComponent::resized()
{
	const int dialSize{ 100 };

	mAttackSlider.setBounds(0, getHeight() / 2, dialSize, dialSize);
	mDecaySlider.setBounds(dialSize, getHeight() / 2, dialSize, dialSize);
	mSustainSlider.setBounds(dialSize * 2, getHeight() / 2, dialSize, dialSize);
	mReleaseSlider.setBounds(dialSize * 3, getHeight() / 2, dialSize, dialSize);
}
