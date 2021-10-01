//
//  SinglePoleFilters.hpp
//  DspModules
//
//  Created by Holland Sersen on 8/7/21.
//

#pragma once
#include <stdio.h>
#include <cmath>
#include "../../ObjectTemplates/FilterObject.h"

namespace Holland {

namespace Filter {

namespace SinglePole {

class SinglePole : public IIRFilterFormOne
{
public:
    //Value is between 1-0
    //Slews up
    void setValueInX (float value)
    {
        this->Value = value;
        
        cookVaribles();
    };
    
    //Allows the slew to be set in samples
    void setValueInSamples (float value)
    {
        //Put in equation to set the Value in Samples
        float tempValue = std::expf(-1.0f / value);
        
        //Create Equation
        setValueInX (tempValue);
    }
    
    //Alows the value you to be set in seconds
    void setValueInSeconds (float time)
    {
        //Set Samples Equal to time
        //Samples per second 1/fs * time
        float seconds = time * SAMPLERATE;
        
        //Create Filter from sample Value
        setValueInSamples (seconds);
    }
    
protected:
    float Value = 0.0f;
    
};

class LowPass final: public SinglePole
{
public:
    //Value is between 1-0
    //Slews up
    void cookVaribles() override
    {
        //Simple Equation works like Simple RC Filter
        b0 = 1;
        b1 = Value;
        b2 = 0;
        a0 = 1 - Value;
        a1 = 1;
        a2 = 0;
    }
    
};

class HighPass final: public SinglePole
{
public:
    //Value is between 1-0
    //Slews Down
    void cookVaribles() override
    {
        //Simple Equation works like Simple RC Filter
        b0 = 1;
        b1 = Value;
        b2 = 0;
        a0 = (1.0f + Value) / 2.0f;
        a1 = -(1.0f + Value) / 2.0f;
        a2 = 0;
    }
    
};

}}}
