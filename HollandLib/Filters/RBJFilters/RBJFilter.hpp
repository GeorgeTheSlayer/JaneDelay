//
//  RBJFilter.hpp
//  DspModules
//
//  Created by Holland Sersen on 8/6/21.
//


#pragma once
#include <stdio.h>
#include <cmath>
#include "../../ObjectTemplates/FilterObject.h"
#include "../../ObjectTemplates/ObjectDefault.h"

namespace Holland {

namespace Filter {

namespace RBJ {

//Create Class for LowShelfFilter
class LowShelfFilter final: public RBJFilterForm
{
public:
    LowShelfFilter() {};
    LowShelfFilter (float gain, float freq, float S) {setFreq(gain, freq, S);};
    
    void setFreq (float gain, float freq, float S)
    {
        //Set Varibles
        this->Gain = gain;
        this->Freq = freq;
        this->S = S;
        
        //Calculate New vars
        cookVaribles();
    }
    
private:
    void cookVaribles() override;
};

//Create Class for HighShelf Filter
class HighShelfFilter final: public RBJFilterForm
{
public:
    HighShelfFilter() {};
    HighShelfFilter (const float gain, const float freq, const float S) {setFreq(gain, freq, S);};
    
    void setFreq (const float gain, const float freq, const float S)
    {
        //Set Varibles
        this->Gain = gain;
        this->Freq = freq;
        this->S = S;
        
        //Calculate New vars
        cookVaribles();
    }
    
private:
    void cookVaribles() override;
};

//Create Class for Mid Freq
class BellCurveFilter final: public RBJFilterForm
{
public:
    BellCurveFilter() {};
    BellCurveFilter (const float gain, const  float freq, const float BW) {setFreq(gain, freq, BW);};
    
    void setFreq (const float gain, const float freq, const float BW)
    {
        this->Gain = gain;
        this->Freq = freq;
        this->BW = BW;
        
        cookVaribles();
    }
private:
    void cookVaribles() override;
};

//Create Class for LowPass Filter
class LowPassFilter final: public RBJFilterForm
{
public:
    LowPassFilter() {};
    LowPassFilter (const float freq, const float Q) {setFreq(freq, Q);};
    
    void setFreq (const float freq, const float Q)
    {
        this->Freq = freq;
        this->Q = Q;
        
        cookVaribles();
    }
private:
    void cookVaribles() override;
};

//Create Class for HighPass Filter
class HighPassFilter final: public RBJFilterForm
{
public:
    HighPassFilter() {};
    HighPassFilter (float freq, float Q) {setFreq(freq, Q);};
    
    void setFreq (float freq, float Q)
    {
        this->Freq = freq;
        this->Q = Q;
        
        cookVaribles();
    }
private:
    void cookVaribles() override;
};

//Create Class for All Pass Filter
class AllPassFilter final: public RBJFilterForm
{
public:
    AllPassFilter() {};
    AllPassFilter (float freq, float Q) {setFreq(freq, Q);};
    
    void setFreq (float freq, float Q)
    {
        this->Freq = freq;
        this->Q = Q;
        
        cookVaribles();
    }
private:
    void cookVaribles() override;
};

}}}
