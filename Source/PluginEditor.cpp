/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TexturizeAudioProcessorEditor::TexturizeAudioProcessorEditor(TexturizeAudioProcessor& p)
	: AudioProcessorEditor(&p), mWaveForm(p), mADSR(p), mVolumeSliders(p), mLevelMeter(p), mFilters(p), audioProcessor(p)
{
	addAndMakeVisible(mWaveForm);
	addAndMakeVisible(mADSR);
	addAndMakeVisible(mVolumeSliders);
	addAndMakeVisible(mLevelMeter);
	addAndMakeVisible(mFilters);

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
	mLevelMeter.setBoundsRelative(0.075f, 0.05f, 0.12f, 0.8f);

	mWaveForm.setBoundsRelative(0.25f, 0.05f, 0.5f, 0.1f);
	mADSR.setBoundsRelative(0.25f, 0.3f, 0.5f, 0.25f);
	mFilters.setBoundsRelative(0.25f, 0.55f, 0.5f, 0.25f);

	mVolumeSliders.setBoundsRelative(0.75f, 0.05f, 0.25f, 0.8f);
}

void TexturizeAudioProcessorEditor::timerCallback()
{
	repaint();
}