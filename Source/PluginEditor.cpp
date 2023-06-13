/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TexturizeAudioProcessorEditor::TexturizeAudioProcessorEditor(TexturizeAudioProcessor& p)
	: AudioProcessorEditor(&p), mWaveForm(p), audioProcessor(p)
{
	setSize(938, 745);

	mLoadButton.onClick = [this] { audioProcessor.loadFile(); };
	renameLoadButton();
	addAndMakeVisible(&mLoadButton);

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
	mDecaySlider.setRange(0.0f, 3.0f, 0.01f);
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
	mSustainSlider.setRange(0.0f, 1.0f, 0.01f);
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
	mReleaseSlider.setRange(0.0f, 5.0f, 0.01f);
	addAndMakeVisible(mReleaseSlider);
	mReleaseLabel.setFont(fontSize);
	mReleaseLabel.setText("Release", juce::NotificationType::dontSendNotification);
	mReleaseLabel.setJustificationType(juce::Justification::centredTop);
	mReleaseLabel.attachToComponent(&mReleaseSlider, false);

	mReleaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		audioProcessor.getAPVTS(), "RELEASE", mReleaseSlider);


	addAndMakeVisible(mWaveForm);
}

 TexturizeAudioProcessorEditor::~TexturizeAudioProcessorEditor()
{
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

	mWaveForm.setBoundsRelative(0.0f, 0.25f, 0.25f, 0.25f);

	const int dialSize{ 100 };
	mAttackSlider.setBounds(getWidth() / 2, getHeight() / 2, dialSize, dialSize);
	mDecaySlider.setBounds(getWidth() / 2 + dialSize, getHeight() / 2, dialSize, dialSize);
	mSustainSlider.setBounds(getWidth() / 2 + dialSize * 2, getHeight() / 2, dialSize, dialSize);
	mReleaseSlider.setBounds(getWidth() / 2 + dialSize * 3, getHeight() / 2, dialSize, dialSize);
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
