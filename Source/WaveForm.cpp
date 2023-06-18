/*
  ==============================================================================

    WaveForm.cpp
    Created: 13 Jun 2023 6:25:19pm
    Author:  arthu

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveForm.h"

//==============================================================================
WaveForm::WaveForm(TexturizeAudioProcessor& p) : audioProcessor (p)
{
	mLoadButton.onClick = [this] { clickLoadButton(); };
	renameLoadButton();
	addAndMakeVisible(&mLoadButton);
}

WaveForm::~WaveForm()
{
}

void WaveForm::paint (juce::Graphics& g)
{
	auto waveform = audioProcessor.getWaveForm();

	const int waveFormHeight{ getHeight() / 5 * 3 };
	const int waveFormYPos{ getHeight() / 5 * 2 };

	g.fillAll(juce::Colours::cadetblue.darker());
	//g.fillRect(0, waveFormYPos, getWidth(), waveFormHeight);


	if (waveform.getNumSamples() > 0)
	{

		juce::Path p;
		mAudioPoints.clear();


		auto ratio = waveform.getNumSamples() / getWidth();
		auto buffer = waveform.getReadPointer(0);

		//scale audio file to window on x axis
		for (int sample = 0; sample < waveform.getNumSamples(); sample += ratio)
		{
			mAudioPoints.push_back(buffer[sample]);
		}

		p.startNewSubPath(0, waveFormYPos + waveFormHeight / 2);

		//scale on y axis
		for (int sample = 0; sample < mAudioPoints.size(); ++sample)
		{
			auto point = juce::jmap<float>(mAudioPoints[sample], -1.0f, 1.0f, waveFormYPos, waveFormHeight + waveFormYPos);
			p.lineTo(sample, point);
		}

		g.strokePath(p, juce::PathStrokeType(2));
		p.closeSubPath();

		auto playHeadPosition = juce::jmap<int> (audioProcessor.getSampleCount(), 0, 
			audioProcessor.getWaveForm().getNumSamples(), 0, getWidth());

		g.setColour(juce::Colours::white);
		g.drawLine(playHeadPosition, 0, playHeadPosition, getHeight(), 2.0f);
		g.setColour(juce::Colours::black.withAlpha (0.2f));
		g.fillRect(0, 0, playHeadPosition, getHeight());
	}

	g.fillAll(juce::Colours::blue);
}

void WaveForm::resized()
{
	/*
	mLoadButton.setBounds(0, 0, getWidth(), getHeight()/5*2);
	*/
}

void WaveForm::clickLoadButton()
{
	loadFile();
	mShouldBePainting = true;
}

void WaveForm::renameLoadButton()
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

bool WaveForm::isInterestedInFileDrag(const juce::StringArray& files)
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

void WaveForm::filesDropped(const juce::StringArray& files, int x, int y)
{
	for (auto file : files)
	{
		if (isInterestedInFileDrag(file))
		{
			loadFile(file);
		}
	}
	repaint();
}

void WaveForm::loadFile()
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

void WaveForm::loadFile(const juce::String& path)
{
	auto file = juce::File(path);
	audioProcessor.fileSetup(file);
	audioProcessor.root = file.getParentDirectory().getFullPathName();
	audioProcessor.savedFile = file;
	renameLoadButton();
}