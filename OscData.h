/*
  ==============================================================================

    OscData.h
    Created: 28 May 2021 8:58:09pm
    Author:  Holland Sersen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

//Actual Osc doing work
class PhaseOsc
{
public:
    
    //Output Function
    float getCurrentSample (float i);
    
    //For Osc Sync
    float resetPhase();
    
    //Set WaveShape / WaveShaper
    void setWave (const float choice);
    
    //Set First Part of Filter
    void setFilter (float filterOne, float filterTwo);
    
    //0 - 1 filter Param
    float filter = 0.0f;
private:
    
    void setY (float array[]);
    
    float X[5] = {0.00f, 0.25f, 0.5f, 0.75f, 1.00f};
    float Y[5] = {0.00f, 0.25f, 0.5f, 0.75f, 1.00f};
    
    //Waveforms
    float sineWave[5] = {0.00f, 0.25f, 0.5f, 0.75f, 1.00f};
    float sawWave[5] = {0.00f, 0.1f, 0.5f, 0.9f, 1.00f};
    float squareWave[5] = {0.00f, 0.25f, 0.5f, 0.75f, 1.00f};
    float pulseWave[5] = {0.00f, 0.25f, 0.5f, 0.75f, 1.00f};
    float *Yptr = sineWave;
    
    int waveInt = 0;
    
    float realY1 = 0.0f, realY2 = 0.0f;
    
    float m;
    float b;
    float outPut;
    
    bool startup = false;
};

