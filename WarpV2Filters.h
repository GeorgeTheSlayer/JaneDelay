/*
  ==============================================================================

    WarpV2Filters.h
    Created: 9 Mar 2021 4:22:45pm
    Author:  Holland Sersen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Filter
{
public:
    void prepareToPlay (float sampleRate);
    
    float process (float currentSample);
    
protected:
    //Declare Filter Coeficeints
    //Inputs and Output (Number Describes Sample)
    float x, y, xN1, xN2, yN1, yN2;
    
    //Filter Coeficeints
    float a0, a1, a2, b0, b1, b2;
    
    //Misc Filter Coefcients
    float sampleRate, alpha, w0, Q, A;
    float Gain;
    
};

//Create Class for LowShelfFilter
class LowShelfFilter: public Filter
{
public:
    void setFreq (float gain, float freq, float S);
};

//Create Class for HighShelf Filter
class HighShelfFilter: public Filter
{
public:
    void setFreq (float gain, float freq, float S);
};

//Create Class for Mid Freq
class BellCurveFilter: public Filter
{
public:
    void setFreq(float gain, float freq, float BW);
};

//Create Class for LowPass Filter
class LowPassFilter: public Filter
{
public:
    void setFreq(float freq, float Q);
};

//Create Class for HighPass Filter
class HighPassFilter: public Filter
{
public:
    void setFreq(float freq, float Q);
};

//Create Class for All Pass Filter
class AllPassFilter: public Filter
{
public:
    void setFreq(float freq, float Q);
};

//TODO Create Seperate Form
//Create a Class for Single Pole Smoothing Filter
//Good For Smoothing Params
class SinglePoleLowPassFilter: public Filter
{
public:
    //Value is between 1-0
    //Slews up
    void setValueInX (float value);
    
    //Allows the slew to be set in samples
    void setValueInSamples (float value);
    
    //Alows the value you to be set in seconds
    void setValueInSeconds (float time);
};

class SinglePoleHighPassFilter: public Filter
{
public:
    //Value is between 1-0
    //Slews Down
    void setValueInX (float value);
    
    //Allows the Slew to be set in Samples
    void setValueInSamples (float value);
    
    //Alows the value you to be set in seconds
    void setValueInSeconds (float time);
};

//Create New Class for Crossover
class LinkwitzCrossover
{
public:
    void prepareToPlay(float SR);
    
    void setFreq(float fc);
    
    float processHigh(float currentSample);
    
    float processLow (float currentSample);
    
protected:
    
    //Init Varibles
    float sampleRate;
    float pi, fpi;
    float wc, wc2, wc22;
    float k, k2, k22;
    float wck2, tmpk;
    float b1, b2;
    float a0_lp, a1_lp, a2_lp;
    float a0_hp, a1_hp, a2_hp;
    
    //Outputs
    float lp_out, lp_xm0, lp_xm1;
    float hp_out, hp_xm0, hp_xm1;
    float Input;
    
};
