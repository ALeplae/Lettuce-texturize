/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TexturizeAudioProcessorEditor::TexturizeAudioProcessorEditor(TexturizeAudioProcessor& p)
	: AudioProcessorEditor(&p), audioProcessor(p), playButton("play"), stopButton("stop")
{
	setSize(938, 745);

	mLoadButton.onClick = [this] { loadFile(); };
	renameLoadButton();
	addAndMakeVisible(&mLoadButton);

	playButton.onClick = [this] { playButtonClicked(); };
	playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
	playButton.setEnabled(true);
	addAndMakeVisible(&playButton);

	stopButton.onClick = [this] { stopButtonClicked(); };
	stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
	stopButton.setEnabled(false);
	addAndMakeVisible(&stopButton);

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

	if (mShouldBePainting)
	{
		juce::Path p;
		mAudioPoints.clear();

		int waveformWidth{ mLoadButton.getWidth() - playButton.getWidth() - stopButton.getWidth() };
		int waveformHeight{ playButton.getHeight() * 2 };
		int waveformXPos{ stopButton.getX() + stopButton.getWidth() };
		int waveformYPos{ getHeight() / 2 };

		p = paintWaveform(p, waveformXPos, waveformYPos, waveformWidth, waveformHeight);

		g.strokePath(p, juce::PathStrokeType(1));
		p.closeSubPath();

		mShouldBePainting = false;
	}
}

void TexturizeAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..
	mLoadButton.setBounds(100, 10, getWidth() - 200, 30);
	playButton.setBounds(100, 50, 50, 30);
	stopButton.setBounds(150, 50, 50, 30);

	
	const int dialSize{ 100 };
	mAttackSlider.setBounds(getWidth() / 2, getHeight() / 2, dialSize, dialSize);
	mDecaySlider.setBounds(getWidth() / 2 + dialSize, getHeight() / 2, dialSize, dialSize);
	mSustainSlider.setBounds(getWidth() / 2 + dialSize * 2, getHeight() / 2, dialSize, dialSize);
	mReleaseSlider.setBounds(getWidth() / 2 + dialSize * 3, getHeight() / 2, dialSize, dialSize);
}

void TexturizeAudioProcessorEditor::loadFile()
{
	//choose a file
	fileChooser = std::make_unique<juce::FileChooser>("Choose a WAV, mp3 or AIF file",
		audioProcessor.root,
		"*");
	const auto fileChooserFlags = juce::FileBrowserComponent::openMode |
		juce::FileBrowserComponent::canSelectFiles |
		juce::FileBrowserComponent::canSelectDirectories;
	fileChooser->launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
		{
			juce::File result(chooser.getResult());

			//if chosen right:
			if (result.getFileExtension() == ".mp3" || result.getFileExtension() == ".wav" || result.getFileExtension() == ".aif" || result.getFileExtension() == ".aiff")
			{
				audioProcessor.root = result.getParentDirectory().getFullPathName();
				audioProcessor.savedFile = result;
				renameLoadButton();

				audioProcessor.fileSetup(result);

				mShouldBePainting = true;
				repaint();
			}
			else
			{
				DBG("you messed up choosing a file :(");
			}
		});


}

void TexturizeAudioProcessorEditor::loadFile(const juce::String& path)
{
	auto file = juce::File(path);
	audioProcessor.fileSetup(file);
	audioProcessor.root = file.getParentDirectory().getFullPathName();
	audioProcessor.savedFile = file;
	renameLoadButton();
}

bool TexturizeAudioProcessorEditor::isInterestedInFileDrag(const juce::StringArray& files)
{
	for (auto file : files)
	{
		if (file.contains(".mp3") || file.contains(".wav") || file.contains(".aif") || file.contains(".aiff"))
		{
			return true;
		}
	}

	return false;
}

void TexturizeAudioProcessorEditor::filesDropped(const juce::StringArray& files, int x, int y)
{
	for (auto file : files)
	{
		if (isInterestedInFileDrag(file))
		{
			loadFile(file);
			DBG("file is loaded");

			mShouldBePainting = true;
			repaint();
		}
	}
}

juce::Path TexturizeAudioProcessorEditor::paintWaveform(juce::Path p, int x, int y, int width, int height)
{
	auto waveform = audioProcessor.getWaveForm();
	auto ratio = waveform.getNumSamples() / width;
	auto buffer = waveform.getReadPointer(0);

	//scale audio file to window on x axis
	for (int sample = 0; sample < waveform.getNumSamples(); sample += ratio)
	{
		mAudioPoints.push_back(buffer[sample]);
	}

	p.startNewSubPath(x, y);

	//scale on y axis
	for (int sample = 0; sample < mAudioPoints.size(); ++sample)
	{
		auto point = juce::jmap<float>(mAudioPoints[sample], -1.0f, 1.0f, height, -height);
		p.lineTo(sample, point + y);
	}

	return p;
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

void TexturizeAudioProcessorEditor::playButtonClicked()
{

}

void TexturizeAudioProcessorEditor::stopButtonClicked()
{

}
