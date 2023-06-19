/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TexturizeAudioProcessorEditor::TexturizeAudioProcessorEditor(TexturizeAudioProcessor& p)
	: AudioProcessorEditor(&p), mWaveForm(p), mADSR(p), mVolumeSliders(p), 
	mPanner(p), mLevelMeter(p), mFilters(p), mDynamicLevel(p), audioProcessor(p)
{

	addAndMakeVisible(mWaveForm);
	addAndMakeVisible(mADSR);
	addAndMakeVisible(mVolumeSliders);
	addAndMakeVisible(mLevelMeter);
	addAndMakeVisible(mFilters);
	addAndMakeVisible(mPanner);
	addAndMakeVisible(mDynamicLevel);

	getLookAndFeel().setColour(juce::Slider::backgroundColourId, juce::Colours::black.withAlpha(0.2f));
	getLookAndFeel().setColour(juce::Slider::trackColourId, juce::Colours::black.withAlpha(0.2f));
	getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colour::fromFloatRGBA(0.39f, 0.65f, 1.f, 1.0f));
	getLookAndFeel().setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
	getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::black);
	getLookAndFeel().setColour(juce::TextButton::buttonColourId, juce::Colours::white);
	getLookAndFeel().setColour(juce::TextButton::textColourOffId, juce::Colours::black);


	startTimerHz(30);
	setSize(900, 600);
}

 TexturizeAudioProcessorEditor::~TexturizeAudioProcessorEditor()
{
	 stopTimer();

	 setLookAndFeel(nullptr);
}

//==============================================================================
void TexturizeAudioProcessorEditor::paint(juce::Graphics& g)
{
	g.fillAll(juce::Colours::white);

	g.setColour(juce::Colour::fromFloatRGBA(0.39f, 0.65f, 1.f, 1.f));
	g.drawLine(getWidth() * 0.25f, getHeight() * 0.3f + border, getWidth() * 0.25f, getHeight() - border, 2.0f);
	g.drawLine(getWidth() * 0.75f, getHeight() * 0.3f + border, getWidth() * 0.75f, getHeight() - border, 2.0f);
}

void TexturizeAudioProcessorEditor::resized()
{
	mLevelMeter.setBoundsRelative(0.f, 0.f, 0.25f, 1.f);

	mWaveForm.setBoundsRelative(0.25f, 0.f, 0.5f, 0.3f);
	mDynamicLevel.setBoundsRelative(0.5f, 0.3f, 0.25f, 0.45f);
	mFilters.setBoundsRelative(0.25f, 0.3f, 0.25f, 0.225f);
	mPanner.setBoundsRelative(0.25f, 0.525f, 0.25f, 0.225f);
	mADSR.setBoundsRelative(0.25f, 0.75f, 0.5f, 0.25f);

	mVolumeSliders.setBoundsRelative(0.75f, 0.f, 0.25f, 1.f);
}

void TexturizeAudioProcessorEditor::timerCallback()
{
	repaint();
}