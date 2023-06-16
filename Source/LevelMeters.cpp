/*
  ==============================================================================

    LevelMeters.cpp
    Created: 16 Jun 2023 6:42:59pm
    Author:  arthu

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LevelMeters.h"

//==============================================================================
LevelMeters::LevelMeters(TexturizeAudioProcessor& p) : audioProcessor(p)
{
}

LevelMeters::~LevelMeters()
{
}

void LevelMeters::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    g.setColour(juce::Colours::white.withBrightness(0.4f));
    g.fillRect(bounds);

    g.setColour(juce::Colours::white);
    const auto scaledY = juce::jmap<float>(audioProcessor.getRMSLevel(), -60.f, +6.f, 0.f, static_cast<float>(getHeight()));
    g.fillRect(bounds.removeFromBottom(scaledY));
}

void LevelMeters::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
