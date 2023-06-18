/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class TexturizeAudioProcessor : public juce::AudioProcessor,
								public juce::ValueTree::Listener
#if JucePlugin_Enable_ARA
	, public juce::AudioProcessorARAExtension
#endif
{
public:
	float inputVel;
	//==============================================================================
	TexturizeAudioProcessor();
	~TexturizeAudioProcessor() override;

	//==============================================================================
	void prepareToPlay(double sampleRate, int samplesPerBlock) override;
	void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
	bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

	void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

	//==============================================================================
	juce::AudioProcessorEditor* createEditor() override;
	bool hasEditor() const override;

	//==============================================================================
	const juce::String getName() const override;

	bool acceptsMidi() const override;
	bool producesMidi() const override;
	bool isMidiEffect() const override;
	double getTailLengthSeconds() const override;

	//==============================================================================
	int getNumPrograms() override;
	int getCurrentProgram() override;
	void setCurrentProgram(int index) override;
	const juce::String getProgramName(int index) override;
	void changeProgramName(int index, const juce::String& newName) override;

	//==============================================================================
	void getStateInformation(juce::MemoryBlock& destData) override;
	void setStateInformation(const void* data, int sizeInBytes) override;

	void fileSetup(juce::File result);
	juce::File root, savedFile;

	int getNumSamplerSounds() { return mSampler.getNumSounds(); }
	juce::AudioBuffer<float>& getWaveForm() { return mWaveForm; }

	juce::ADSR::Parameters& getADSRParams() { return mADSRParams; }
	juce::AudioProcessorValueTreeState& getAPVTS() { return mAPVTS; }
	std::atomic<bool>& isNotePlayed() { return mIsNotePlayed; }
	std::atomic<int>& getSampleCount() { return mSampleCount; }

	float& getRMSLevel() { return mRMSLevel; }

private:
	juce::Synthesiser mSampler;
	const int mNumVoices{ 3 };
	juce::AudioBuffer<float> mWaveForm;

	juce::ADSR::Parameters mADSRParams;

	juce::AudioFormatManager mFormatManager;
	juce::AudioFormatReader* mFormatReader{ nullptr };

	juce::AudioProcessorValueTreeState mAPVTS;
	juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
	void valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& poperty) override;

	juce::AudioBuffer<float> mSynthBuffer;

	void updateADSR();

	void updateFilters();

	void updateVolume();
	float mDryVolume, mWetVolume;

	void updatePan();
	float mPanAmount;

	float mRMSLevel, mTotalRMS;

	float mSampleRate;
	float mLpCutoffFrequency, mHpCutoffFrequency;
	juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> lowPassFilter, highPassFilter;

	std::atomic<bool> mShouldUpdate{ false };
	std::atomic<bool> mIsNotePlayed{ false };
	std::atomic<int> mSampleCount{ 0 };
	std::atomic<float> mMidiNoteHz{ 0.0f };
	
	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TexturizeAudioProcessor)
};