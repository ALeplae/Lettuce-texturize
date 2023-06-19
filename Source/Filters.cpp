/*
  ==============================================================================

    Filters.cpp
    Created: 17 Jun 2023 11:48:08pm
    Author:  arthu

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Filters.h"

//==============================================================================
Filters::Filters(TexturizeAudioProcessor& p) : audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
	//envelope dials
	const float fontSize{ 20.0f };

	//Low pass
	mLowPassSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	mLowPassSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 20);
	mLowPassSlider.setTextValueSuffix("Hz");
	addAndMakeVisible(mLowPassSlider);
	mLowPassLabel.setFont(fontSize);
	mLowPassLabel.setText("Lp", juce::NotificationType::dontSendNotification);
	mLowPassLabel.setJustificationType(juce::Justification::centredTop);
	mLowPassLabel.attachToComponent(&mLowPassSlider, false);
	mLowPassLabel.setColour(juce::Label::textColourId, juce::Colours::black);

	mLowPassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		audioProcessor.getAPVTS(), "LP", mLowPassSlider);

	//High pass
	mHighPassSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	mHighPassSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 20);
	mHighPassSlider.setTextValueSuffix("Hz");
	addAndMakeVisible(mHighPassSlider);
	mHighPassLabel.setFont(fontSize);
	mHighPassLabel.setText("Hp", juce::NotificationType::dontSendNotification);
	mHighPassLabel.setJustificationType(juce::Justification::centredTop);
	mHighPassLabel.attachToComponent(&mHighPassSlider, false);
	mHighPassLabel.setColour(juce::Label::textColourId, juce::Colours::black);

	mHighPassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		audioProcessor.getAPVTS(), "HP", mHighPassSlider);
}

Filters::~Filters()
{
}

void Filters::paint (juce::Graphics& g)
{
}

void Filters::resized()
{
	const int size{ 100 };
	const int border{ 30 };
	mLowPassSlider.setBounds(getWidth() / 3 - size / 2, getHeight() - size, size, size);
	mHighPassSlider.setBounds(getWidth() / 3 * 2 - size / 2, getHeight() - size, size, size);
}
