/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TexturizeAudioProcessorEditor::TexturizeAudioProcessorEditor(TexturizeAudioProcessor& p)
	: AudioProcessorEditor(&p), mWaveForm(p), mADSR(p), audioProcessor(p)
{
	setSize(938, 745);

	mLoadButton.onClick = [this] { clickLoadButton(); };
	renameLoadButton();
	addAndMakeVisible(&mLoadButton);

	addAndMakeVisible(mWaveForm);
	addAndMakeVisible(mADSR);

	startTimerHz(30);
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
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..
	mLoadButton.setBounds(100, 10, getWidth() - 200, 30);

	mWaveForm.setBounds(100, 40, getWidth() - 200, 60);
	mADSR.setBoundsRelative(0.0f, 0.5f, 0.25f, 0.25f);
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