/*
  ==============================================================================

    ParamComponent.cpp
    Created: 27 Jun 2021 8:30:02am
    Author:  Holland Sersen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ParamComponent.h"

//==============================================================================

void RotarySliderLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&)
{
    auto radius = (float) juce::jmin (width / 2, height / 2) - 4.0f;
    auto centreX = (float) x + (float) width  * 0.5f;
    auto centreY = (float) y + (float) height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    
    int fadedWhiteRGB[3] = {224, 225, 228};
    auto fadedWhite = juce::Colour::fromRGB(fadedWhiteRGB[0], fadedWhiteRGB[1], fadedWhiteRGB[2]);
    int matteCharcoalRGB[3] = {59, 66, 72};
    auto matteCharcoal = juce::Colour::fromRGB(matteCharcoalRGB[0], matteCharcoalRGB[1], matteCharcoalRGB[2]);
    
    // fill
    g.setColour (fadedWhite);
    g.fillEllipse (rx, ry, rw, rw);

    // outline
    g.setColour (matteCharcoal);
    g.drawEllipse (rx, ry, rw, rw, 10.0f);

    juce::Path p;
    //auto pointerLength = radius * 0.33f;
    auto pointerLength = radius * 0.35f;
    auto pointerThickness = 10.0f;
    p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform (juce::AffineTransform::rotation (angle).translated (centreX, centreY));
    
    g.setColour (matteCharcoal);
    g.fillPath (p);
    
}

void ParamAesthetic::setRotarySlider(const juce::String &name, juce::Slider &slider, juce::Label &label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> &attach, const juce::String &ID, juce::AudioProcessorValueTreeState &apvts)
{
    //Set Slider Looks
    slider.setName(name);
    slider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 600.0f / 5.0f, 300.0f / 16.0f - 5.0f);
    slider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::black);
    slider.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::white);
    slider.setLookAndFeel(&lookAndFeel);
    
    //Set Label Looks
    label.setText(name, juce::NotificationType::dontSendNotification);
    label.setFont(juce::Font("Spectral", 300.0f / 16.f - 5.0f, juce::Font::plain));
    label.setJustificationType(juce::Justification::centred);
    label.setColour(juce::Label::textColourId, juce::Colours::white);
    
    attach = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>( apvts, ID, slider );
    
    
    addAndMakeVisible(slider); 
    addAndMakeVisible(label);
}

void ParamAesthetic::setVerticalSlider(const juce::String &name, juce::Slider &slider, juce::Label &label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> &attach, const juce::String &ID, juce::AudioProcessorValueTreeState &apvts)
{
    //Set Slider Looks
    slider.setName(name);
    slider.setSliderStyle(juce::Slider::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 600.0f / 5.0f, 300.0f / 16.0f - 5.0f);
    slider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::black);
    slider.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::white);
    slider.setLookAndFeel(&lookAndFeel);
    
    //Set Label Looks
    label.setText(name, juce::NotificationType::dontSendNotification);
    label.setFont(juce::Font("Spectral", 300.0f / 16.f - 5.0f, juce::Font::plain));
    label.setJustificationType(juce::Justification::centred);
    label.setColour(juce::Label::textColourId, juce::Colours::white);
    
    attach = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>( apvts, ID, slider );
    
    
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
    
}

ParamComponent::ParamComponent(juce::AudioProcessorValueTreeState& apvts) 
{
    //Set Slider and Labels params and link to Audio Parameters
    setSlider("Speed", paramOneSlider, paramOneLabel, paramOneAttachment, "PARAMONE", apvts);
    setSlider("Width", paramTwoSlider, paramTwoLabel, paramTwoAttachment, "PARAMTWO", apvts);
    setSlider("Jane", paramThreeSlider, paramThreeLabel, paramThreeAttachment, "PARAMTHREE", apvts);
    setSlider("Time", paramFourSlider, paramFourLabel, paramFourAttachment, "PARAMFOUR", apvts);
    setSlider("FeedBack", paramFiveSlider, paramFiveLabel, paramFiveAttachment, "PARAMFIVE", apvts);
    addAndMakeVisible(tempButton);
}

ParamComponent::~ParamComponent()
{
}

void ParamComponent::paint (juce::Graphics& g)
{
    
}

void ParamComponent::resized()
{
    
    //Get Area
    juce::Rectangle<int> totalArea = getLocalBounds();
    
    //Create Flex Boxes
    juce::FlexBox sliderFlex, labelFlex;
    
    setFlexBox(sliderFlex);
    setFlexBox(labelFlex);
    
    auto width = getWidth() / 5.0f;
    auto sliderHieght = totalArea.getHeight() * (15.0f / 16.0f);
    auto labelHieght = totalArea.getHeight() * (1.0f / 16.0f);
    
    //Create Areas
    juce::Rectangle<int> labelArea = juce::Rectangle<int>(0, 0, getWidth(), labelHieght);
    juce::Rectangle<int> sliderArea = juce::Rectangle<int>(0, labelHieght, getWidth(), sliderHieght);

    
    //Add Items to Arrays
    //Sliders
    juce::Array<juce::FlexItem> sliderArray;
    sliderArray.add(juce::FlexItem(width, sliderHieght, paramOneSlider));
    sliderArray.add(juce::FlexItem(width, sliderHieght, paramTwoSlider));
    sliderArray.add(juce::FlexItem(width, sliderHieght, paramThreeSlider));
    sliderArray.add(juce::FlexItem(width, sliderHieght, paramFourSlider));
    sliderArray.add(juce::FlexItem(width, sliderHieght, paramFiveSlider));
    
    //Labels
    juce::Array<juce::FlexItem> labelArray;
    labelArray.add(juce::FlexItem(width, labelHieght, paramOneLabel));
    labelArray.add(juce::FlexItem(width, labelHieght, paramTwoLabel));
    labelArray.add(juce::FlexItem(width, labelHieght, paramThreeLabel));
    labelArray.add(juce::FlexItem(width, labelHieght, paramFourLabel));
    labelArray.add(juce::FlexItem(width, labelHieght, paramFiveLabel));
    
    //Create Layout Changes
    //Slider
    sliderFlex.items = sliderArray; 
    sliderFlex.performLayout(sliderArea);
    
    //Labels
    labelFlex.items = labelArray;
    labelFlex.performLayout(labelArea);
    //tempButton.setBounds(getLocalBounds());
    
    
}

void ParamComponent::setSlider(const juce::String &name, juce::Slider &slider, juce::Label &label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attach, const juce::String& ID, juce::AudioProcessorValueTreeState& apvts)
{
    //Set Slider Looks
    slider.setName(name);
    slider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 600.0f / 5.0f, 300.0f / 16.0f - 5.0f);
    slider.setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::black);
    slider.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::white);
    slider.setLookAndFeel(&lookAndFeel);
    
    //Set Label Looks
    label.setText(name, juce::NotificationType::dontSendNotification);
    label.setFont(juce::Font("Spectral", 300.0f / 16.f - 5.0f, juce::Font::plain));
    label.setJustificationType(juce::Justification::centred);
    label.setColour(juce::Label::textColourId, juce::Colours::white);
    
    attach = std::make_unique <juce::AudioProcessorValueTreeState::SliderAttachment>( apvts, ID, slider );
    
    
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
}

void ParamComponent::setFlexBox(juce::FlexBox &flexBox)
{
    //Set Knob Flex Box Params
    flexBox.flexDirection = juce::FlexBox::Direction::row;
    flexBox.flexWrap = juce::FlexBox::Wrap::wrap;
    flexBox.alignContent = juce::FlexBox::AlignContent::spaceBetween;
}
