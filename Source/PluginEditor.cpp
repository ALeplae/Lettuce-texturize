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
	mLoadButton.onClick = [this] { clickLoadButton(); };
	renameLoadButton();
	addAndMakeVisible(&mLoadButton);

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
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
	g.setColour(juce::Colours::white);
}

void TexturizeAudioProcessorEditor::resized()
{
	//mLoadButton.setBounds(100, 10, getWidth() - 200, 30);

	//mWaveForm.setBounds(100, 40, getWidth() - 200, 60);
	//mADSR.setBoundsRelative(0.0f, 0.5f, 0.25f, 0.25f);
	//mVolumeSliders.setBoundsRelative(0.5f, 0.5f, 0.2f, 0.5f);
	mLevelMeter.setBounds(100, 100, 15, 200);
}

void TexturizeAudioProcessorEditor::clickLoadButton()
{
	audioProcessor.loadFile();
	mWaveForm.mShouldBePainting = true;
}

void TexturizeAudioProcessorEditor::renameLoadButton()
{
	if (audioProcessor.savedFile.getFileName() != "")
	{
		mLoadButton.setButtonText(audioProcessor.savedFile.getFileName());
	}
	else
	{
		mLoadButton.setButtonText("please load an mp3, WAV or AIF file");
	}
}

void TexturizeAudioProcessorEditor::timerCallback()
{

	repaint();
} 