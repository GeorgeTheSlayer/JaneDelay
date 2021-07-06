/*
  ==============================================================================

    WarpV2Filters.cpp
    Created: 9 Mar 2021 4:22:45pm
    Author:  Holland Sersen

  ==============================================================================
*/

#include "WarpV2Filters.h"
#include "math.h"


void Filter::prepareToPlay(float SR)
{
    sampleRate = SR;
    xN1 = 0.0f;
    xN2 = 0.0f;
    yN1 = 0.0f;
    yN2 = 0.0f;
}

float Filter::process(float currentSample)
{
    //Make X == Current Sample
    x = currentSample;
    
    //Preform Calculation
    y = (b0/a0) * x + (b1/a0) * xN1 + (b2/a0) * xN2 - (a1/a0) * yN1 - (a2/a0) * yN2;
    
    //Assign past samples
    xN2 = xN1;
    xN1 = x;
    yN2 = yN1;
    yN1 = y;
    
    //Return Output
    return y;
}

void LowShelfFilter::setFreq(float gain, float freq, float S)
{

    //Low Shelf Filter Equations
    w0 = 2 * 3.14 * freq / sampleRate;
    A = std::pow(10, gain/40);
    alpha = sin(w0)/2 * sqrt((A + 1/A) * (1/S - 1) + 2);
    float beta = 2 * sqrt(A) * alpha;
    
    b0 =   A*( (A + 1) - (A - 1) * cos(w0) + beta);
    b1 = 2*A*( (A - 1) - (A + 1) * cos(w0)       );
    b2 =   A*( (A + 1) - (A - 1) * cos(w0) - beta);
    a0 =       (A + 1) + (A - 1) * cos(w0) + beta ;
    a1 =  -2*( (A - 1) + (A + 1) * cos(w0)       );
    a2 =       (A + 1) + (A - 1) * cos(w0) - beta ;
}

void HighShelfFilter::setFreq(float gain, float freq, float S)
{
    //High Shelf Filter
    w0 = 2 * 3.14 * freq / sampleRate;
    A = std::pow(10, gain/40);
    alpha = sin(w0)/2 * sqrt((A + 1/A) * (1/S - 1) + 2);
    float beta = 2 * sqrt(A) * alpha;
    
    b0 =   A*( (A + 1) + (A - 1) * cos(w0) + beta);
    b1 =-2*A*( (A - 1) + (A + 1) * cos(w0) );
    b2 =   A*( (A + 1) + (A - 1) * cos(w0) - beta);
    a0 =       (A + 1) - (A - 1) * cos(w0) + beta ;
    a1 =   2*( (A - 1) - (A + 1) * cos(w0) );
    a2 =       (A + 1) - (A - 1) * cos(w0) - beta ;

}

void BellCurveFilter::setFreq(float gain, float freq, float BW)
{
    Gain = gain;
    //Peaking Eq
    w0 = 2 * 3.14 * freq / sampleRate;
    A = std::pow(10, gain/40);
    alpha = sin(w0) * sinh(0.693147 / 2 * BW * w0/sin(w0));
    
    b0 =  1 + alpha*A;
    b1 = -2*cos(w0);
    b2 =  1 + alpha;
    a0 =  1 + alpha;
    a1 = -2*cos(w0);
    a2 =  1 - alpha;
    
}

void LowPassFilter::setFreq(float freq, float Q)
{
    //Create Coeficents
    w0 = 2 * 3.14 * freq / sampleRate;
    alpha = sin(w0) / (2*Q);
    
    b0 =  (1 - cos(w0))/2;
    b1 =   1 - cos(w0);
    b2 =  (1 - cos(w0))/2;
    a0 =   1 + alpha;
    a1 = -2 * cos(w0);
    a2 =  1 - alpha;
}

void HighPassFilter::setFreq(float freq, float Q)
{
    //Create Coeficents
    w0 = 2 * 3.14 * freq / sampleRate;
    alpha = sin(w0) / (2*Q);
    
    b0 =  (1 + cos(w0))/2;
    b1 = -(1 + cos(w0));
    b2 =  (1 + cos(w0))/2;
    a0 =   1 + alpha;
    a1 =  -2*cos(w0);
    a2 =   1 - alpha;
}

void AllPassFilter::setFreq(float freq, float Q = 1)
{
    //Create Coeficents
    w0 = 2 * 3.14 * freq / sampleRate;
    alpha = sin(w0) / (2*Q);
    
    b0 = 1 - alpha;
    b1 = -2*cos(w0);
    b2 = 1 + alpha;
    a0 = 1 + alpha;
    a1 = -2*cos(w0);
    a2 = 1 - alpha;
}

void LinkwitzCrossover::prepareToPlay(float SR)
{
    //Init Filter
    sampleRate = SR;
    
    //Set Delayed Samples to 0
    lp_out = 0.0f;
    lp_xm0 = 0.0f;
    lp_xm1 = 0.0f;
    
    hp_out = 0.0f;
    hp_xm0 = 0.0f;
    hp_xm1 = 0.0f;
}

void LinkwitzCrossover::setFreq(float fc)
{
    //Create Varibles
    //Wc Varibles
    pi = 3.14f;
    fpi = pi * fc;
    wc = 2.0f * fpi;
    wc2 = wc * wc;
    wc22 = 2.0f * wc2;
    
    //K Varibles
    k = wc/tan(fpi / sampleRate);
    k2 = k*k;
    k22 = 2.0f * k2;
    wck2 =  2.0f * wc * k;
    tmpk = (k2 + wc2 + wck2);
    
    //Normal b Varibles
    b1 = ((-1.0f) * k22 + wc22)/tmpk;
    b2 = ((-1.0f) * wck2 + k2 + wc2)/tmpk;
    
    //LP Varibles
    a0_lp = (wc2)/tmpk;
    a1_lp = (wc22)/tmpk;
    a2_lp = (wc2)/tmpk;
    
    //HP Varibles
    a0_hp = (k2)/tmpk;
    a1_hp = ((-1.0f) * k22)/tmpk;
    a2_hp = (k2)/tmpk;
}

float LinkwitzCrossover::processLow(float currentSample)
{
    //Process Low Output
    lp_out = a0_lp * Input + lp_xm0;
    lp_xm0 = a1_lp * Input - b1 * lp_out + lp_xm1;
    lp_xm1 = a2_lp * Input - b2 * lp_out;
    
    //Retturn Output
    return lp_out;
    
}

float LinkwitzCrossover::processHigh(float currentSample)
{
    //Make currentSample == Input
    Input = currentSample;
    
    //Do Calculations
    hp_out = a0_hp * Input + hp_xm0;
    hp_xm0 = a1_hp * Input - b1 * hp_out + hp_xm1;
    hp_xm1 = a2_hp * Input - b2 * hp_out;
    
    //Multiply by -1 to get it into Phase
    return  hp_out * (-1.0f);
}

void SinglePoleLowPassFilter::setValueInX (float value)
{
    //Simple Equation works like Simple RC Filter
    b0 = 1;
    b1 = value;
    b2 = 0;
    a0 = 1 - value;
    a1 = 1;
    a2 = 0;
    
}

void SinglePoleLowPassFilter::setValueInSamples (float value)
{
    //Put in equation to set the Value in Samples
    float tempValue = std::expf(-1.0f / value);
    
    //Create Equation
    setValueInX(tempValue);
}

void SinglePoleLowPassFilter::setValueInSeconds (float time)
{
    //Set Samples Equal to time
    //Samples per second 1/fs * time
    float seconds = time * sampleRate;
    
    //Create Filter from sample Value
    setValueInSamples(seconds);
}

//TODO FIX
void SinglePoleHighPassFilter::setValueInX (float value)
{
    //Simple Equation works like Simple RC Filter
    b0 = 1;
    b1 = value;
    b2 = 0;
    a0 = (1.0f + value) / 2.0f;
    a1 = -(1.0f + value) / 2.0f;
    a2 = 0;
    
}

void SinglePoleHighPassFilter::setValueInSamples (float value)
{
    //Put in equation to set the Value in Samples
    float tempValue = std::expf(-1.0f / value);
    
    //Create Equation
    setValueInX(tempValue);
}

void SinglePoleHighPassFilter::setValueInSeconds (float time)
{
    //Set Samples Equal to time
    //Samples per second 1/fs * time
    float seconds = time * sampleRate;
    
    //Create Filter from sample Value
    setValueInSamples(seconds);
}
