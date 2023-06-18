/*
  ==============================================================================

    DynamicLevel.h
    Created: 18 Jun 2023 9:01:19pm
    Author:  arthu

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DynamicLevel  : public juce::Component
{
public:
    DynamicLevel();
    ~DynamicLevel() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DynamicLevel)
};
