/*
  ==============================================================================

    JaneDelayAlgo.cpp
    Created: 16 Jun 2021 6:04:46pm
    Author:  Holland Sersen

  ==============================================================================
*/

#include "JaneDelayAlgo.h"

//Init Before Software Starts
void JaneDelay::init(float sampleRate)
{
    //Set the sample Rate
    SampleRate = sampleRate;
    
    //Set the Max delay Size
    SIZE = MAXDELAY * sampleRate * 1;
    
    //DelayLine.init(sampleRate, MAXDELAY);
    
    
    //if the delay buffer exist then delete it
    if (delayBuffer)
        delete [] delayBuffer;
    
    //Create the Delay Buffer
    delayBuffer = new float[SIZE];
    
    if (delayBuffer)
    memset(delayBuffer, 0, SIZE);
    
    //Set Object Defaults
    Osc.setWave(1.5f);
    
    currentWidth = 0.0f;
    writePointer = 0;
    setDelay(0.5f, 0.0f, 0.0f, 0.1f, 0.0f);
    setMix(0.0f, 0.0f);
}

void JaneDelay::setDelay(float time, float feedback, float width, float freq, float filter)
{
    //Set Modulation Amount for the LFO
    Width = width;
    
    //Set the Feedback Amount for the LFO
    FeedBack = feedback;
    
    //Set the Freq of the LFO
    angleDelta = (freq * 5.0f) / SampleRate;
    
    //Set the Delay time to delta
    Time = (int)(time * SampleRate);
    
    //Set the Filter for the Osc
    //Osc.setFilter(filter, filter);
    Osc.setWave(filter * 3.9f);
    
    //If delta is greater than the Size of buffer truncate
    if (Time >= SIZE)
        Time = SIZE - 1;
    
}

void JaneDelay::setMix(float dry, float wet)
{
    //Set Dry wet Mix
    dryMix = juce::Decibels::decibelsToGain(dry);
    wetMix = juce::Decibels::decibelsToGain(wet);
}


void JaneDelay::process(float *inbuffer, int numSamples)
{
    
    for (int i = 0; i < numSamples; i++)
    {
        //Create Local Input Varible
        float input = inbuffer[i];
        
        //Write to delay
        write(input + Output * FeedBack);
        //DelayLine.write(input);
        
        float localTargetWidth = Width;
        
        //Create slew with change in the delay time
        if (localTargetWidth != currentWidth)
        {
            float timeInc = (localTargetWidth - currentWidth) / (SampleRate / 4.0f);
            currentWidth += timeInc;
        }
        
        //Process Osc
        float oscOut = std::sin(Osc.getCurrentSample(oscAngle) * 2.0f * juce::MathConstants<float>::pi);
        float lfo = ((oscOut + 1.0f) * currentWidth * 0.0025f) * SampleRate;
        
        //Set Osc for Next Sample
        oscAngle += angleDelta;
        
        //If the Osc is greater than one then reset the phase
        if (oscAngle >= 1)
            oscAngle -= 1;
        
        //Create a local varible for what the target should be
        float localTargetTime = Time;
        
        //Create slew with change in the delay time
        if (localTargetTime != currentTime)
        {
            float timeInc = (localTargetTime - currentTime) / (SampleRate / 4.0f);
            currentTime += timeInc;
        }
        
        //Read from delay Line
        Output = read(currentTime + lfo + 1.0f);
        //Output = DelayLine.read(currentTime + lfo + 1.0f);
        
        //Create Dry Wet Mix
        float audioMix = input * dryMix + Output * wetMix;
        
        inbuffer[i] = audioMix;
        
    }
    
}

float JaneDelay::read(float time)
{
    
    //Get the position of the read pointer
    float readPointer = (float)writePointer - time;
    
    //If the Readpointer is greater than the size of the buffer Subtract size of buffer
    if (readPointer >= SIZE)
        readPointer -= SIZE;
    
    //If the readpointer is less than the size of the buffer then make it positive
    if (readPointer < 0)
        readPointer += SIZE;
    
    return interpolate(readPointer);
}

void JaneDelay::write(float input)
{
    //Move Cursor
    writePointer++;
    
    //Make sure the Curosr is valid
    if (writePointer >= SIZE)
        writePointer -= SIZE;
    
    //Write to Cursor
    delayBuffer[writePointer] = input;
}

float JaneDelay::interpolate(float delayInSamples)
{
    
    //Find Vars for interpolation
    int floor = (int)delayInSamples;
    int round = (int)delayInSamples - 1;
    
    //Round the Size of the Varible
    if (round < 0)
        round = SIZE - 1;
    
    //Find the fractional value
    float frac = delayInSamples - (int)delayInSamples;
    
    //Get points in delay buffer
    float lower = delayBuffer[floor];
    float upper = delayBuffer[round];
    
    return (lower * frac) + (upper * (1.0f - frac));
}

void MovingAverageFilter::init(int numValues)
{
    SIZE = numValues;
    buffer = new float [SIZE];
    
}

float MovingAverageFilter::process(float input)
{
    //Reset Numerator
    numerator = 0;
    
    for (int i = 0; i < SIZE; i++)
    {
        if (i == 0)
            buffer[i] = input;
        
        else
            buffer[i] = buffer[i - 1];
        
        //Add all values of the buffer
        numerator += buffer[i];
    }
    
    return numerator / SIZE;
}
