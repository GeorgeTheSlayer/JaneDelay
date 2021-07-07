/*
  ==============================================================================

    JaneDelayAlgo.h
    Created: 16 Jun 2021 6:04:46pm
    Author:  Holland Sersen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "WarpV2Filters.h"
#include "OscData.h"
//#include "DspModules.hpp"



class MovingAverageFilter
{
public:
    void init (int numValues);
    float process(float input);
    
private:
    int SIZE;
    float* buffer;
    float numerator = 0;
};


class JaneDelay
{
public:
    //Get Output of delay
    void process (float *inbuffer, int numSamples);
    
    //Read to the delay
    float read (float time);
    
    //Write to Delay
    void write (float input);
    
    //Set the Delay Time
    void setDelay (float time, float feedback, float width, float freq, float filter);
    
    //Set Dry Wet
    void setMix (float dry, float wet);
    
    //INIT Delay
    void init (float sampleRate);
    
    
private:
    
    //Gets the Interpolated Value of the Delay
    float interpolate (float delayInSamples);

    //Delay Line Varibles
    float* delayBuffer = NULL;
    int writePointer = 0;
    float Output = 0.0f;
    float frac;
    float input = 0;
    
    //Sets Size of buffer
    const int MAXDELAY = 3;
    float SIZE;
    
    //Global param varibles
    float Width;
    float FeedBack = 0.0f;
    float SampleRate = 0.0f;
    
    //Modulation Varibles
    float Time = 0.125f;
    float angleDelta;
    float oscAngle = 0.0f;
    
    //Time varibles for smoothing the delay line
    float currentTime;
    float currentWidth;
    
    //Dry Wet Mix
    float dryMix = 1.0f, wetMix = 1.0f;

    
    //Create Supporting Objects
    PhaseOsc Osc;
    //Holland::Utilities::DelayLine DelayLine;
    
};

