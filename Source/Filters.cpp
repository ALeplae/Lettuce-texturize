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
	mLowPassSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
	addAndMakeVisible(mLowPassSlider);
	mLowPassLabel.setFont(fontSize);
	mLowPassLabel.setText("Lp", juce::NotificationType::dontSendNotification);
	mLowPassLabel.setJustificationType(juce::Justification::centredTop);
	mLowPassLabel.attachToComponent(&mLowPassSlider, false);

	mLowPassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		audioProcessor.getAPVTS(), "LP", mLowPassSlider);

	//High pass
	mHighPassSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
	mHighPassSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 20);
	addAndMakeVisible(mHighPassSlider);
	mHighPassLabel.setFont(fontSize);
	mHighPassLabel.setText("Hp", juce::NotificationType::dontSendNotification);
	mHighPassLabel.setJustificationType(juce::Justification::centredTop);
	mHighPassLabel.attachToComponent(&mHighPassSlider, false);

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
	int size;

	if (getWidth() / 2 < getHeight())
	{
		size = getWidth() / 2;
	}
	else
	{
		size = getHeight();
	}

	
	const int maxSize{ 100 };
	if (size >= maxSize)
	{
		size = maxSize;
	}
	


	const int border{ 30 };
	mLowPassSlider.setBounds(0, border, size, size);
	mHighPassSlider.setBounds(size, border, size, size);
}
