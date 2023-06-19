/*
  ==============================================================================

    WaveForm.h
    Created: 13 Jun 2023 6:25:19pm
    Author:  arthu

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class WaveForm : public juce::Component,
                 public juce::FileDragAndDropTarget
{
public:
    WaveForm(TexturizeAudioProcessor& p);
    ~WaveForm() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped(const juce::StringArray& files, int x, int y) override;

    bool mShouldBePainting{ false };

private:
    const int mBorder{ 30 };

    std::unique_ptr<juce::FileChooser> fileChooser;

    juce::TextButton mLoadButton;
    void clickLoadButton();
    void renameLoadButton();

    void loadFile();
    void loadFile(const juce::String& path);

    std::vector<float> mAudioPoints;

    TexturizeAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveForm)
};
