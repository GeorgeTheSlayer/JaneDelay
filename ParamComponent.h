/*
  ==============================================================================

    ParamComponent.h
    Created: 27 Jun 2021 8:30:02am
    Author:  Holland Sersen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/


class RotarySliderLookAndFeel : public juce::LookAndFeel_V4
{
public:
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override;
    
    
};

class ParamComponent  : public juce::Component
{
public:
    ParamComponent(juce::AudioProcessorValueTreeState& apvts);
    ~ParamComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void setSlider(const juce::String &name, juce::Slider &slider, juce::Label &label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attach, const juce::String& ID, juce::AudioProcessorValueTreeState& apvts);
    
    void setFlexBox(juce::FlexBox &flexBox);

private:
    //Look and Feel for each slider
    RotarySliderLookAndFeel lookAndFeel;
    
    juce::TextButton tempButton {"Params"};
    
    //Sliders themseleves
    juce::Slider paramOneSlider, paramTwoSlider, paramThreeSlider, paramFourSlider, paramFiveSlider;
    
    //Slider Lables
    juce::Label paramOneLabel, paramTwoLabel, paramThreeLabel, paramFourLabel, paramFiveLabel;
    
    //Slider Attachment
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> paramOneAttachment, paramTwoAttachment, paramThreeAttachment, paramFourAttachment, paramFiveAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParamComponent)
};

class ParamAesthetic : public juce::Component
{
public:
    void setRotarySlider(const juce::String &name, juce::Slider &slider, juce::Label &label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attach, const juce::String& ID, juce::AudioProcessorValueTreeState& apvts);
    
    void setVerticalSlider(const juce::String &name, juce::Slider &slider, juce::Label &label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attach, const juce::String& ID, juce::AudioProcessorValueTreeState& apvts);
    
private:
    RotarySliderLookAndFeel lookAndFeel;
};
