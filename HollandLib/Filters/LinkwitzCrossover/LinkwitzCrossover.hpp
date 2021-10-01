//
//  LinkwitzCrossover.hpp
//  DspModules
//
//  Created by Holland Sersen on 8/7/21.
//

#pragma once
#include "../../ObjectTemplates/ObjectDefault.h"
#include <stdio.h>
#include <cmath>

namespace Holland {

namespace Filter {

//Create New Class for Crossover
class LinkwitzCrossover : public ObjectDefault
{
    LinkwitzCrossover(const float freq) {setFreq(freq);};
public:
    void setFreq (const float fc)
    {
        this->Freq = fc;
        
        cookVaribles();
    }
    
    float processHigh (const float currentSample);
    
    float processLow (const float currentSample);
    
private:
    //New set Default
    void setDefault() override;
    
    //New cook Varibles
    void cookVaribles() override;
    
    //Freq Param
    float Freq;
    
    //Init Varibles
    float b1, b2;
    float a0_lp, a1_lp, a2_lp;
    float a0_hp, a1_hp, a2_hp;
    
    //Outputs
    float lp_out, lp_xm0, lp_xm1;
    float hp_out, hp_xm0, hp_xm1;
    
};

}}
