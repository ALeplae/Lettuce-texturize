/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TexturizeAudioProcessorEditor::TexturizeAudioProcessorEditor (TexturizeAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // editor's size
    setSize (200, 200);

    //slider object parameters
    inputVolume.setSliderStyle(juce::Slider::LinearBarVertical);
    inputVolume.setRange(0.0, 1.2, 0.1);
    inputVolume.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    inputVolume.setPopupDisplayEnabled(true, false, this);
    inputVolume.setTextValueSuffix(" Volume");
    inputVolume.setValue(1.0);

    //adding slider to editor
    addAndMakeVisible(&inputVolume);

    //adding listener to the slider
    inputVolume.addListener(this);
}

TexturizeAudioProcessorEditor::~TexturizeAudioProcessorEditor()
{
}

//==============================================================================
void TexturizeAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colours::white);

    g.setColour (juce::Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Midi volume", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void TexturizeAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    inputVolume.setBounds(40, 30, 20, getHeight() - 60);
}

void TexturizeAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    audioProcessor.inputVel = inputVolume.getValue();
}