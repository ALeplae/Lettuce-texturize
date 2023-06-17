/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TexturizeAudioProcessorEditor::TexturizeAudioProcessorEditor(TexturizeAudioProcessor& p)
	: AudioProcessorEditor(&p), mWaveForm(p), mADSR(p), mVolumeSliders(p), mLevelMeter(p), audioProcessor(p)
{
	addAndMakeVisible(mWaveForm);
	addAndMakeVisible(mADSR);
	addAndMakeVisible(mVolumeSliders);
	addAndMakeVisible(mLevelMeter);

	startTimerHz(30);
	setSize(938, 745);
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
	mWaveForm.setBounds(100, 40, getWidth() - 200, 60);
	mADSR.setBoundsRelative(0.0f, 0.5f, 0.25f, 0.25f);
	mVolumeSliders.setBoundsRelative(0.5f, 0.5f, 0.2f, 0.5f);
	mLevelMeter.setBounds(100, 100, 100, 200);
}

void TexturizeAudioProcessorEditor::timerCallback()
{
	repaint();
} 