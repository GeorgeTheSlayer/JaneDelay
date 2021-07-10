/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JaneAudioProcessorEditor::JaneAudioProcessorEditor (JaneAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), sliderParams(audioProcessor.apvts)
{
    //paramLooks.setVerticalSlider("Dry", drySlider, dryLabel, dryAttachment, "DRY", audioProcessor.apvts);
    setDryWetSlider("Dry", drySlider, dryAttachment, "DRY");
    setDryWetSlider("Wet", wetSlider, wetAttachment, "WET");
    
    addAndMakeVisible(mixComponent);
    addAndMakeVisible(shakeCompoment);
    addAndMakeVisible(sliderParams);
    
    setSize (900, 450);
}

JaneAudioProcessorEditor::~JaneAudioProcessorEditor()
{
}

//==============================================================================
void JaneAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    
    auto textSize = getWidth() / 4;
    auto fontSize = 18;
    
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(juce::Font("Specter", fontSize, juce::Font::plain));
    g.drawFittedText("Jane", (getWidth() / 2) - (textSize / 2), getHeight() / 32, textSize, fontSize, juce::Justification::centredTop, 1, 0.0f);
    
    g.drawFittedText("Holland Audio", (getWidth() / 2) - (textSize / 2), getHeight() - (getHeight() / 16), textSize, fontSize, juce::Justification::centredTop, 1);
    
    //Draw Upper Line
    juce::Path upperLine;
    upperLine.startNewSubPath(juce::Point<float> (getWidth() / 16, getHeight() / 16 + 10.0f));
    upperLine.lineTo(juce::Point<float> (getWidth() - (getWidth() / 16), getHeight() / 16 + 10.0f));
    upperLine.lineTo(juce::Point<float> (getWidth() - (getWidth() / 16), getHeight() / 16 + 12.5f));
    upperLine.lineTo(juce::Point<float> (getWidth() / 16, getHeight() / 16 + 12.5f));
    upperLine.closeSubPath();
    g.fillPath(upperLine);
    
    //Draw Lower Line
    juce::Path lowerLine;
    lowerLine.startNewSubPath(juce::Point<float> (getWidth() / 16, getHeight() - (getHeight() / 16 ) - 10));
    lowerLine.lineTo(juce::Point<float> (getWidth() - (getWidth() / 16), getHeight() - (getHeight() / 16 ) - 10));
    lowerLine.lineTo(juce::Point<float> (getWidth() - (getWidth() / 16), getHeight() - (getHeight() / 16 ) - 7.5));
    lowerLine.lineTo(juce::Point<float> (getWidth() / 16, getHeight() - (getHeight() / 16 ) - 7.5));
    lowerLine.closeSubPath();
    g.fillPath(lowerLine);
    //g.drawText("What", 0, 100, 20, 20, juce::Justification::centred);
}

void JaneAudioProcessorEditor::resized()
{
    //Get Area
    juce::Rectangle<int> totalArea = getLocalBounds();
    auto headerFooterHieght = totalArea.getHeight() / 15.0f;
    auto sideBarWidth = totalArea.getWidth() / 16.0f;
    
    
    juce::FlexBox fullAreaFlexBox;
    
    shakeCompoment.setBounds(0, headerFooterHieght, 450, getHeight() - headerFooterHieght * 2.f);
    sliderParams.setBounds(450, headerFooterHieght, 250, getHeight() - headerFooterHieght * 2.f);
    mixComponent.setBounds (700, headerFooterHieght, getWidth() - 700, getHeight() - headerFooterHieght * 2.f);
    
    //drySlider.setBounds(0, headerFooterHieght, sideBarWidth, getHeight() - (headerFooterHieght * 2.0f));
    //sliderParams.setBounds(sideBarWidth, headerFooterHieght, getWidth() - (sideBarWidth * 2), getHeight() - (headerFooterHieght * 2.0f));
    //wetSlider.setBounds(getWidth() - sideBarWidth, headerFooterHieght, sideBarWidth, getHeight() - (headerFooterHieght * 2.0f));
    
}

void JaneAudioProcessorEditor::setDryWetSlider(const juce::String &name, juce::Slider &Slider, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attach, const juce::String &ID)
{
    //Set Slider Settings
    Slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    Slider.setName(name);
    Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 600.0f / 5.0f, 300.0f / 16.0f - 5.0f);
    Slider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::white);
    Slider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::white);
    Slider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::black);
    
    attach = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>( audioProcessor.apvts, ID, Slider );
    
    addAndMakeVisible(Slider);
    
}
