/*
  ==============================================================================

    SimpleDecimation.h
    Created: 20 Sep 2021 10:32:06am
    Author:  Holland Sersen

  ==============================================================================
*/

#pragma once
//Why this Complies when this is not right I have no idea.
//TODO: Fix
#include "../../ObjectTemplates/ObjectDefault.h"
#include "../Functions/Functions.h"

namespace Holland {
namespace Utilities {

//Decimation filter
class SimpleDecimation : public ObjectDefault
{
public:
    //Allows the setting of sample rates
    //TODO: Allow Specific Sample rate to be set
    inline void setSampleRate(float newRate) {this->newRate = newRate;}
    
    //Set stages
    //TODO: remove once done with testing. Make it only work by changing the sample rate
    inline void setSamples(const int mthsample) {this->mthSample = mthsample;}
    
    //Process Input
    float process(const float input)
    {
        //Create Temp Output
        float output = 0.0f;
        
        //if this the sample to keep then output it
        if (keepSample == mthSample)
        {
            output = prevSample = input;
            keepSample = 0;
        }
        
        //If this is not the sample to keep do not output
        else
        {
            output = prevSample;
            keepSample++;
        }
        
        return output;
    }
    
private:
    
    inline void setDefault() override
    {
        keepSample = 0;
        mthSample = 4;
    };
    
    void cookVaribles() override {};
    
    float newRate;
    int keepSample;
    int mthSample;
    float prevSample = 0.0f;
    
};

}}
