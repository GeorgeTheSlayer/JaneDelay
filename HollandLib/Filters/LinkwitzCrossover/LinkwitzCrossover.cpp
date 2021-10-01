//
//  LinkwitzCrossover.cpp
//  DspModules
//
//  Created by Holland Sersen on 8/7/21.
//

#include "LinkwitzCrossover.hpp"

namespace Holland {

namespace Filter {

void LinkwitzCrossover::cookVaribles()
{
    //Create Varibles
    //Wc Varibles
    float fpi = M_PI * Freq;
    float wc = 2.0f * fpi;
    float wc2 = wc * wc;
    float wc22 = 2.0f * wc2;
    
    //K Varibles
    float k = wc / std::tan(fpi / SAMPLERATE);
    float k2 = k * k;
    float k22 = 2.0f * k2;
    float wck2 =  2.0f * wc * k;
    float tmpk = (k2 + wc2 + wck2);
    
    //Normal b Varibles
    b1 = (-1.0f * k22 + wc22) / tmpk;
    b2 = (-1.0f * wck2 + k2 + wc2) / tmpk;
    
    //LP Varibles
    a0_lp = wc2 / tmpk;
    a1_lp = wc22 / tmpk;
    a2_lp = wc2 / tmpk;
    
    //HP Varibles
    a0_hp = k2 / tmpk;
    a1_hp = (-1.0f * k22) / tmpk;
    a2_hp = k2 / tmpk;
    
}

void LinkwitzCrossover::setDefault()
{
    //Set Delayed Samples to 0
    lp_out = 0.0f;
    lp_xm0 = 0.0f;
    lp_xm1 = 0.0f;
    
    hp_out = 0.0f;
    hp_xm0 = 0.0f;
    hp_xm1 = 0.0f;
}

float LinkwitzCrossover::processLow(const float currentSample)
{
    //Process Low Output
    lp_out = a0_lp * currentSample + lp_xm0;
    lp_xm0 = a1_lp * currentSample - b1 * lp_out + lp_xm1;
    lp_xm1 = a2_lp * currentSample - b2 * lp_out;
    
    //Return Output
    return lp_out;
    
}

float LinkwitzCrossover::processHigh(float currentSample)
{
    //Do Calculations
    hp_out = a0_hp * currentSample + hp_xm0;
    hp_xm0 = a1_hp * currentSample - b1 * hp_out + hp_xm1;
    hp_xm1 = a2_hp * currentSample - b2 * hp_out;
    
    //Multiply by -1 to get it into Phase
    return  hp_out * (-1.0f);
    
}

}

}
