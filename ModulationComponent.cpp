/*
  ==============================================================================

    ModulationComponent.cpp
    Created: 10 Jul 2021 4:56:30pm
    Author:  Holland Sersen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ModulationComponent.h"

//==============================================================================
ModulationComponent::ModulationComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    
    
    floorSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 10, 10);
    floorSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    heightSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 10, 10);
    heightSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    shakeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 10, 10);
    shakeSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    
    addAndMakeVisible (floorSlider);
    addAndMakeVisible (heightSlider);
    addAndMakeVisible (shakeSlider);
    addAndMakeVisible (tempButton);
}

ModulationComponent::~ModulationComponent()
{
}

void ModulationComponent::paint (juce::Graphics& g)
{

}

void ModulationComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    //tempButton.setBounds (getLocalBounds());
    floorSlider.setBounds(0, 0, getWidth() / 3.f, getHeight());
    heightSlider.setBounds(getWidth() / 3.f, 0, getWidth() / 3.f, getHeight());
    shakeSlider.setBounds((getWidth() / 3.f) * 2.f, 0, getWidth() / 3.f, getHeight());
    
}
