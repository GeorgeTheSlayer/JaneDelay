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
    
    //Init Delay Line
    DelayLine.init(SampleRate, MAXDELAY);
    
    //Init Smooth valeus
    float slewRate = 0.25f;
    timeValueSmoothed.init (SampleRate);
    timeValueSmoothed.setSlewInSeconds (slewRate);
    widthValueSmoothed.init(SampleRate);
    widthValueSmoothed.setSlewInSeconds(slewRate);
    
    //Create Specs
    specs.SampleRate = SampleRate;
    
    notchOne.prepareToPlay(sampleRate);
    notchOne.setFreq(440.0f, 3.14 / sqrt(2));
    
    //Set Object Defaults
    Osc.init (sampleRate);
    Osc.setWave (1.5f);
    Osc.setFreq (0.5f);
    
    setClid(4, 3, 2);
    
    //Set Varible Defaults
    currentWidth = 0.0f;
    writePointer = 0;
    setDelay (0.5f, 0.0f, 0.0f, 0.1f, 0.0f);
    setMix (0.0f, 0.0f);
}

void JaneDelay::setDelay (float time, float feedback, float width, float freq, float filter)
{
    //Set Modulation Amount for the LFO
    Width = width;
    
    //Set the Feedback Amount for the LFO
    FeedBack = feedback * 0.5f;
    
    //Set the Freq of the LFO
    Osc.setFreq (freq * 5.0f);
    
    //Set the Delay time to delta
    Time = (int)((time * 0.25f) * SampleRate);
    
    //Set the Filter for the Osc
    //Osc.setFilter(filter, filter);
    Osc.setWave(filter * 3.9f);
    
    //If delta is greater than the Size of buffer truncate
    if (Time >= SIZE)
        Time = SIZE - 1;
    
}

void JaneDelay::setMix (float dry, float wet)
{
    //Set Dry wet Mix
    dryMix = juce::Decibels::decibelsToGain(dry);
    wetMix = juce::Decibels::decibelsToGain(wet);
}

//TODO don't have it's own for loop
//Give input to osc
void JaneDelay::process (float *inbuffer, int numSamples)
{
    
    for (int i = 0; i < numSamples; i++)
    {
        //Create Local Input Varible
        float input = inbuffer[i];
        
        //Write to delay
        DelayLine.write(input + Output * FeedBack);
        
        //Set target to be smoothed
        widthValueSmoothed.setTarget(Width);
        
        //Process Osc
        float oscOut = std::sin(Osc.getCurrentSample() * 2.0f * juce::MathConstants<float>::pi);
        //float lfo = ((oscOut) * widthValueSmoothed.getCurrentValue() * 0.0025f) * SampleRate;
        float lfo = ((oscOut + 1.0f) * widthValueSmoothed.getCurrentValue() * 0.0025f) * SampleRate;
        
        //Set Smootedh Value
        timeValueSmoothed.setTarget(Time);
        
        //Read from delay Line
        Output = DelayLine.read(timeValueSmoothed.getCurrentValue() + lfo + 1.0f);
        
        //Create Dry Wet Mix
        //float audioMix = input * dryMix + Output * wetMix;
        float audioMix = Output * wetMix;
        
        inbuffer[i] = audioMix;
        
    }
    
}


//float JaneDelay::getOutput(float currentSample, float externalOsc)
//{
//    //Create Local Varible for input
//    float input = currentSample;
//
//    //Write to delay
//    DelayLine.write(input + Output * FeedBack);
//
//    //Set target to be smoothed
//    widthValueSmoothed.setTarget(Width);
//
//    //Process Osc
//    float oscOut = std::sin(Osc.getCurrentSample() * 2.0f * juce::MathConstants<float>::pi);
//    //float oscOut = Osc.getCurrentSample();
//    float lfo = ((oscOut + 1.0f) * widthValueSmoothed.getCurrentValue() * 0.0025f) * SampleRate;
//
//    //Set Smootedh Value
//    timeValueSmoothed.setTarget(Time);
//
//    //Read from delay Line
//    Output = DelayLine.read(timeValueSmoothed.getCurrentValue() + lfo + 1.0f);
//
//    //Create Dry Wet Mix
//    float audioMix = input * dryMix + Output * wetMix;
//
//    return audioMix;
//
//
//}


float JaneDelay::getOutput(float currentSample, float externalOsc)
{
    //Create Local Varible for input
    float input = currentSample;
    
    //Write to delay
    DelayLine.write(input + Output * FeedBack);
    
    //Reset output
    Output = 0;
    
    //Mix of taps to output
    float tapOut;
    
    //Get Outputs of taps
    for (int i = 0; i < tapVector.size(); i++)
    {
        //if the current Tap is true
        if (tapVector[i] == true)
        {
            //Write First
            tapOut = DelayLine.read(Time * i);
            DelayLine.writeAtPoint(tapOut * FeedBack, Time * i + 1);
            Output += tapOut;
        }
        
    }
    
    return Output;
    
}

void JaneDelay::setClid(int steps, int pulses, int rotate)
{
    //Set Vars
    Steps = (steps < 8) ? steps : 8;
    Pulses = (pulses < Steps) ? pulses : Steps;
    Rotate = (rotate < Steps) ? rotate : Steps;
    
    //Reset vector
    tapVector.erase(tapVector.begin(), tapVector.end());
    
    //Create bucket
    int bucket = 0;
    
    //Create Temp Vector
    std::vector<bool> pulseOut;
    
    //Set Buckets and stuff
    for (int i = 0; i < Steps; i++)
    {
        //Figure out if step is true or false
        bucket += Pulses;
        
        //If true
        if (bucket >= Steps)
        {
            bucket -= Steps;
            pulseOut.push_back(true);
            
        }
        
        //If false
        else
        {
            pulseOut.push_back(false);
        }
        
    }
    
    
    //Set the Roatation of the Array
    for (int i = 0; i < Steps; i++)
    {
        //Rotate the pulse out
        bool currentTap = pulseOut[1 +  (int)(std::abs(i + (Steps - Rotate))) % (int)Steps];
        
        //Add it to vector
        tapVector.push_back(currentTap);
    }
    
    
}

//TODO Create WRITE AT POINT
//Write to the delay line

//Read the Delay

//Write to each point whenever it reads without changing the delay line state

//Repeat step two and three until delay is done
