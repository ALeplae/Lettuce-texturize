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

	startTimerHz(30);
	setSize(900, 600);
}

 TexturizeAudioProcessorEditor::~TexturizeAudioProcessorEditor()
{
	 stopTimer();
}

//==============================================================================
void TexturizeAudioProcessorEditor::paint(juce::Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
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