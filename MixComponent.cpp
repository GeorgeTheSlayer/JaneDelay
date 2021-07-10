/*
  ==============================================================================

    MixComponent.cpp
    Created: 10 Jul 2021 5:00:47pm
    Author:  Holland Sersen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MixComponent.h"

//==============================================================================
MixComponent::MixComponent()
{
    
    //addAndMakeVisible(tempButton);
    drySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    drySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 10, 10);
    wetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 10, 10);
    wetSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    addAndMakeVisible(drySlider);
    addAndMakeVisible(wetSlider);
    
}

MixComponent::~MixComponent()
{
}

void MixComponent::paint (juce::Graphics& g)
{
    
}

void MixComponent::resized()
{
    tempButton.setBounds(getLocalBounds());
    drySlider.setBounds(0, 0, getWidth() / 2, getHeight());
    wetSlider.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());

}
