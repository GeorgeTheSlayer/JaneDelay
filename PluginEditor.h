/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ParamComponent.h"
#include "MixComponent.h"
#include "ModulationComponent.h"

//==============================================================================
/**
*/
class JaneAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    JaneAudioProcessorEditor (JaneAudioProcessor&);
    ~JaneAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void setDryWetSlider(const juce::String &name, juce::Slider &Slider, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attach, const juce::String &ID);
    
private:
    
    juce::Slider drySlider, wetSlider;
    juce::Label dryLabel, wetLabel;
    
    JaneAudioProcessor& audioProcessor;
    
    ParamComponent sliderParams;
    ModulationComponent shakeCompoment;
    MixComponent mixComponent;
    ParamAesthetic paramLooks;
    
    //Slider Attachment
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> dryAttachment, wetAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JaneAudioProcessorEditor)
};
