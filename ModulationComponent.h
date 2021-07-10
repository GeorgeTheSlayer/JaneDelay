/*
  ==============================================================================

    ModulationComponent.h
    Created: 10 Jul 2021 4:56:30pm
    Author:  Holland Sersen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ModulationComponent  : public juce::Component
{
public:
    ModulationComponent();
    ~ModulationComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider floorSlider, heightSlider, shakeSlider;
    
    //Temporary Button for sizing
    juce::TextButton tempButton {"Modulation"};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulationComponent)
};
