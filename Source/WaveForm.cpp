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
	
}

WaveForm::~WaveForm()
{
}

void WaveForm::paint (juce::Graphics& g)
{
	g.fillAll(juce::Colours::cadetblue.darker());

	auto waveform = audioProcessor.getWaveForm();

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

		p.startNewSubPath(0, getHeight() / 2);

		//scale on y axis
		for (int sample = 0; sample < mAudioPoints.size(); ++sample)
		{
			auto point = juce::jmap<float>(mAudioPoints[sample], -1.0f, 1.0f, 0, getHeight());
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
}

void WaveForm::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

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
			/*
			auto myFile = std::make_unique<juce::File>(file);
			mFileName = myFile->getFileNameWithoutExtension();
			*/

			audioProcessor.loadFile(file);
			DBG("file is loaded");
		}
	}
	repaint();
}