/*
  ==============================================================================

    MixComponent.h
    Created: 10 Jul 2021 5:00:47pm
    Author:  Holland Sersen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class MixComponent  : public juce::Component
{
public:
    MixComponent();
    ~MixComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    
    //Temporary Text Button for Referance
    juce::TextButton tempButton {"Mix"};
    juce::Slider drySlider, wetSlider;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MixComponent)
};
