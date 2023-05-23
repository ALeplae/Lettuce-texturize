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
	
	// editor's size
	setSize(938, 745);

	mLoadButton.onClick = [this] { loadFile(); };
	renameLoadButton();
	//addAndMakeVisible(&mLoadButton);

	playButton.onClick = [this] { playButtonClicked(); };
	playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
	playButton.setEnabled(true);
	//addAndMakeVisible(&playButton);

	stopButton.onClick = [this] { stopButtonClicked(); };
	stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
	stopButton.setEnabled(false);
	//addAndMakeVisible(&stopButton);



	//slider object parameters
	inputVolume.setSliderStyle(juce::Slider::LinearVertical);
	inputVolume.setRange(0.0, 1.2, 0.01);
	inputVolume.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
	inputVolume.setPopupDisplayEnabled(true, false, this);
	inputVolume.setTextValueSuffix(" Volume");
	inputVolume.setValue(1.0);

	//adding slider to editor
	//addAndMakeVisible(&inputVolume);

	//adding listener to the slider
	inputVolume.addListener(this);
	
}

TexturizeAudioProcessorEditor::~TexturizeAudioProcessorEditor()
{
}

//==============================================================================
void TexturizeAudioProcessorEditor::paint(juce::Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	//g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

	g.fillAll(juce::Colours::black);
	g.setColour(juce::Colours::white);

	if (mShouldBePainting) 
	{
		juce::Path p;
		p.clear();

		//int waveformWidth{ 200 };
		//int waveformHeight{ 100 };

		auto waveform = audioProcessor.getWaveForm();
		auto ratio = waveform.getNumSamples() / getWidth();
		auto buffer = waveform.getReadPointer(0);

		//scale audio file to window on x axis
		for (int sample = 0; sample < waveform.getNumSamples(); sample += ratio)
		{
			mAudioPoints.push_back (buffer[sample]);
		}

		p.startNewSubPath(0, getHeight() / 2);

		//scale on y axis
		for (int sample = 0; sample < mAudioPoints.size(); ++sample)
		{
			auto point = juce::jmap<float> (mAudioPoints[sample], -1.0f, 1.0f, getHeight(), 0);
			p.lineTo(sample, point);
		}

		g.strokePath(p, juce::PathStrokeType(2));

		mShouldBePainting = false;
	}


	/*
	//g.fillAll(juce::Colours::dimgrey);

	g.setColour(juce::Colours::white);
	g.setFont(15.0f);
	g.drawFittedText("Lettuce texturize", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
	*/
}

void TexturizeAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..
	mLoadButton.setBounds(100, 10, getWidth() - 200, 30);
	playButton.setBounds(100, 50, 50, 30);
	stopButton.setBounds(150, 50, 50, 30);

	inputVolume.setBounds(40, 30, 20, getHeight() - 60);

}

void TexturizeAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
	audioProcessor.inputVel = inputVolume.getValue();
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
			mShouldBePainting = true;
		}
	}
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
