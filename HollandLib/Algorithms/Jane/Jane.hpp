//
//  Jane.hpp
//  DspModules
//
//  Created by Holland Sersen on 8/8/21.
//

#pragma once
#include "vector"
#include "../../HollandLib.hpp"
#include "../../Utilities/DelayLine/DelayLine.hpp"
#include "../../Utilities/SmoothValue/SmoothValue.hpp"
#include "../../Utilities/Parameter/Parameter.h"
#include "../../Oscillators/PhaseOsc/PhaseOsc.hpp"
#include "../../Utilities/SimpleDecimation/SimpleDecimation.h"
#include "../../Filters/RBJFilters/RBJFilter.hpp"
#include "../../ObjectTemplates/ObjectDefault.h"
#include <JuceHeader.h>

//Modulated Delay Line
namespace Holland {
namespace Algorithms {

class Jane final : public ObjectDefault
{
    
public:
    //Create New Constructors
    Jane() {};
    Jane(float maxdelay) {this->MAXDELAY = maxdelay; delayBuffer.setMaxDelay(MAXDELAY);};
    //~Jane() {};
    
    //Process the input and return output
    float process(float input);
    
    //DO BEFORE INIT
    //Set the Max delay time for the buffer it is not set in the constructor
    inline void setMaxDelay(float maxdelay) {this->MAXDELAY = maxdelay; delayBuffer.setMaxDelay(MAXDELAY);};
    
    Holland::Utilities::ParameterObject<float> FeedBackParam, SpeedParam, JaneParam;
    Holland::Utilities::SmoothParameterObject WidthParam, TimeParam;
    
    
private:
    //Parameter Varibles
    float delayTime = 0.01f;
    float Width = 0.0f;
    float Feedback = 0.0f;
    float oscSpeed = 1.0f;
    
    //Init objects First
    void setDefault() override
    {
        //Init Objects
        delayBuffer.init(AUDIOSPEC);
        lowFreqOsc.init(AUDIOSPEC);
        WidthParam.init(AUDIOSPEC);
        TimeParam.init(AUDIOSPEC);
        FeedBackParam.init(AUDIOSPEC);
        SpeedParam.init(AUDIOSPEC);
        JaneParam.init(AUDIOSPEC);
        
        //Set Default Parameters
        FeedBackParam.setValue(0.5f);
        SpeedParam.setValue(5.0f);
        TimeParam.setValue((int)(0.125f * getSampleRate()));
        WidthParam.setValue(0.75f);
        lowFreqOsc.setFreq(5.0f);
        JaneParam.setValue(1.0f);

        

    }
    
    void cookVaribles() override
    {
        delayTime = TimeParam.getValue();
        Width = WidthParam.getValue();
        Feedback = FeedBackParam.getValue();
        oscSpeed = SpeedParam.getValue();
        
        //set osc speed
        lowFreqOsc.setFreq(oscSpeed);
        
        //Get Osc Out
        float oscOut = lowFreqOsc.getCurrentSample();
        
        //Turn osc into lfo
        float vTime = 0.004f;
        lfoOut = (vTime / 2.0f * (1.0f + oscOut * Width)) * getSampleRate();
    }
    
    //Global Vars
    float MAXDELAY;
    float OUTPUT;
    float alteredFeedback = 0.0f;
    float lfoOut;
    
    Holland::Utilities::DelayLine delayBuffer;
    Holland::Osc::PhaseOsc lowFreqOsc;

};
}}
