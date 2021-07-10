/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JaneAudioProcessor::JaneAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts (*this, nullptr, "Parameters", createParameters() )
#endif
{
    //SingleDelay Single[kChannels];
}

JaneAudioProcessor::~JaneAudioProcessor()
{
}

//==============================================================================
const juce::String JaneAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JaneAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JaneAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JaneAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JaneAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JaneAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JaneAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JaneAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String JaneAudioProcessor::getProgramName (int index)
{
    return {};
}

void JaneAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void JaneAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    //Give each delay the sample rate
    for (int i = 0; i < kChannels; i++)
    {
        Jane[i].init(sampleRate);
    }
    
}

void JaneAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JaneAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void JaneAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    //Create Left and Right Input Channel
    //TODO have it be settable to either be mono or stero
    for (int channel = 0; channel < getTotalNumInputChannels(); channel++)
    {
        
        //Get Current Sample input
        auto* channeldata = buffer.getWritePointer (channel);
        
        //Set Params
        freq = apvts.getRawParameterValue ("PARAMONE");
        Width = apvts.getRawParameterValue ("PARAMTWO");
        JaneFilter = apvts.getRawParameterValue ("PARAMTHREE");
        delayTime = apvts.getRawParameterValue ("PARAMFOUR");
        feedBack = apvts.getRawParameterValue ("PARAMFIVE");
        
        //Get dry wet Param
        dryMix = apvts.getRawParameterValue ("DRY");
        wetMix = apvts.getRawParameterValue ("WET");
        
        
        Jane[channel].setDelay(*delayTime, *feedBack, *Width, *freq, *JaneFilter);
        Jane[channel].setMix(*dryMix, *wetMix);
        
        
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            float input = channeldata[i];
            
            channeldata[i] = Jane[channel].getOutput(input, 0);
        }
        
        
    }
    
}


//==============================================================================
bool JaneAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* JaneAudioProcessor::createEditor()
{
    return new JaneAudioProcessorEditor (*this);
}

//==============================================================================
void JaneAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    //Get Last State of Parameters
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void JaneAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    
    //Set Parameter State
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (apvts.state.getType()))
            apvts.replaceState (juce::ValueTree::fromXml (*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JaneAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout JaneAudioProcessor::createParameters()
{
    //Create Param vectors
    std::vector <std::unique_ptr < juce::RangedAudioParameter > > params;
    
    //Auto Filled Params
    auto start = 0.01f;
    auto stop = 1.0f;
    auto interval = 0.01f;
    auto init = 0.5f;
    
    //Plugin Params
    params.push_back (std::make_unique<juce::AudioParameterFloat> ("PARAMONE", "paramone", juce::NormalisableRange<float> (start, stop, interval, 1 ), init ) );
    
    params.push_back (std::make_unique<juce::AudioParameterFloat> ("PARAMTWO", "paramtwo", juce::NormalisableRange<float> (0.0f, stop, interval, 1 ), init ) );
    
    params.push_back (std::make_unique<juce::AudioParameterFloat> ("PARAMTHREE", "paramthree", juce::NormalisableRange<float> (0.0f, stop, interval, 1 ), init ) );
    
    params.push_back (std::make_unique<juce::AudioParameterFloat> ("PARAMFOUR", "paramfour", juce::NormalisableRange<float> (0.01f, stop, interval, 1 ), init ) );
    
    params.push_back (std::make_unique<juce::AudioParameterFloat> ("PARAMFIVE", "paramfive", juce::NormalisableRange<float> (0.0f, stop, interval, 1 ), init ) );
    
    //Dry Wet Params
    params.push_back (std::make_unique<juce::AudioParameterFloat> ("DRY", "dry", juce::NormalisableRange<float> (-48.0f, 0.0f, 0.1f, 0.5f ), 0.0f ) );
    
    params.push_back (std::make_unique<juce::AudioParameterFloat> ("WET", "wet", juce::NormalisableRange<float> (-48.0f, 0.0f, 0.1f, 0.5f ), 0.0f ) );
    
    //Return Vector
    return {params.begin(), params.end()};
}
