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
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

WaveForm::~WaveForm()
{
}

void WaveForm::paint (juce::Graphics& g)
{
	g.fillAll(juce::Colours::cadetblue.darker());

	if (mShouldBePainting)
	{
		juce::Path p;
		mAudioPoints.clear();

		auto waveform = audioProcessor.getWaveForm();
		auto ratio = waveform.getNumSamples() / getWidth();
		auto buffer = waveform.getReadPointer(0);

		//scale audio file to window on x axis
		for (int sample = 0; sample < waveform.getNumSamples(); sample += ratio)
		{
			mAudioPoints.push_back(buffer[sample]);
		}

		p.startNewSubPath(0, getHeight()/2);

		//scale on y axis
		for (int sample = 0; sample < mAudioPoints.size(); ++sample)
		{
			auto point = juce::jmap<float>(mAudioPoints[sample], -1.0f, 1.0f, getHeight() / 2, -getHeight() / 2);
			p.lineTo(sample, point);
		}

		g.strokePath(p, juce::PathStrokeType(2));
		p.closeSubPath();

		mShouldBePainting = false;
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
			audioProcessor.loadFile(file);
			DBG("file is loaded");

			mShouldBePainting = true;
			repaint();
		}
	}
}