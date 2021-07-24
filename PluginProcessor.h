/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "JaneDelayAlgo.h"
#include "DspModules.hpp"
//#include "SimpleDelay.h"

//==============================================================================
/**
*/
class JaneAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    JaneAudioProcessor();
    ~JaneAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

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
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts;
    
private:
    
    static const int kChannels = 2;
    static const int numFlangers = 4;
    JaneDelay Jane[kChannels][numFlangers];
    
    std::atomic<float>* delayTime  = nullptr;
    std::atomic<float>* feedBack  = nullptr;
    std::atomic<float>* JaneFilter  = nullptr;
    std::atomic<float>* freq  = nullptr;
    std::atomic<float>* Width  = nullptr;
    
    std::atomic<float>* dryMix  = nullptr;
    std::atomic<float>* wetMix  = nullptr;
    
    
    
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> delaySmooth;
    
    //Create Audio Process Tree
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JaneAudioProcessor)
};
