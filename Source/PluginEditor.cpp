/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TexturizeAudioProcessorEditor::TexturizeAudioProcessorEditor(TexturizeAudioProcessor& p)
	: AudioProcessorEditor(&p), audioProcessor(p), searchButton("very cool button :)")
{
	// editor's size
	setSize(938, 745);

	searchButton.onClick = [this] { openButtonClicked(); };

	addAndMakeVisible(&searchButton);

	formatManager.registerBasicFormats();


	//slider object parameters
	inputVolume.setSliderStyle(juce::Slider::LinearVertical);
	inputVolume.setRange(0.0, 1.2, 0.01);
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
void TexturizeAudioProcessorEditor::paint(juce::Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

	//g.fillAll(juce::Colours::dimgrey);

	g.setColour(juce::Colours::white);
	g.setFont(15.0f);
	g.drawFittedText("Lettuce texturize", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void TexturizeAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..
	searchButton.setBounds(100, 10, getWidth() - 200, 30);
	inputVolume.setBounds(40, 30, 20, getHeight() - 60);
}

void TexturizeAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
	audioProcessor.inputVel = inputVolume.getValue();
}

void TexturizeAudioProcessorEditor::openButtonClicked()
{
	//choose a file
	fileChooser = std::make_unique<juce::FileChooser>("Choose a WAV, mp3 or AIFF file",
		audioProcessor.root,
		"*");
	const auto fileChooserFlags = juce::FileBrowserComponent::openMode |
		juce::FileBrowserComponent::canSelectFiles |
		juce::FileBrowserComponent::canSelectDirectories;
	fileChooser->launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
		{
			juce::File result(chooser.getResult());

			//if chosen right:
			if (result.getFileExtension() == ".mp3" || result.getFileExtension() == ".wav" || result.getFileExtension() == ".aiff")
			{
				audioProcessor.savedFile = result;
				audioProcessor.root = result.getParentDirectory().getFullPathName();

				//read file
				juce::AudioFormatReader* reader = formatManager.createReaderFor(audioProcessor.savedFile);

				//get ready to play
				std::unique_ptr<juce::AudioFormatReaderSource> tempSource(new juce::AudioFormatReaderSource(reader, true));

				playSource.reset(tempSource.release());

				DBG(reader->getFormatName());
			}
			else
			{
				DBG("you fucked up choosing a file :(");
			}
		});
}