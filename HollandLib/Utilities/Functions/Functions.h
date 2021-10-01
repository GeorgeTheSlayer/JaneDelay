//
//  Functions.h
//  DspModules
//
//  Created by Holland Sersen on 8/5/21.
//

#pragma once
#include <cstdio>
#include <cmath>

namespace Holland {

namespace Utilities {

//Interpolation with Buffer
inline float LinearInterpolation (float *buffer, float bufferSize, float delayInSamples)
{
    //Find Vars for interpolation
    int floor = (int)delayInSamples;
    int round = (int)delayInSamples - 1;

    //Round the Size of the Varible
    if (round < 0)
        round = bufferSize - 1;

    //Find the fractional value
    float frac = delayInSamples - (int)delayInSamples;

    //Get points in delay buffer
    float lower = buffer[floor];
    float upper = buffer[round];

    return (lower * frac) + (upper * (1.0f - frac));
}

//Returns Float
inline float ZeroOneLogScale (float value, float max)
{
    return max * std::log10 (value / 0.1f);
}

//Lorgithmic from Custom Scale
inline float LogScale (float vMin, float vMax, float yMax, float value)
{
    float logMax = std::log10 (vMax / vMin);
    return yMax * std::log10 (value / vMin) / logMax;
}

//Simple Limter so you don't blow your ears out
inline float SimpleLimiter(float input)
{
    //Init out
    float output = 0;

    //If input is greater than threshold Set it to max
    if (input >= 1.0f)
        output = 1.0f;

    else if (input <= -1.0f)
        output = -1.0f;

    else
        output = input;

    return output;

}

inline float SimpleLimiter(float input, float gain)
{
    //Init out
    float output = 0;

    //If input is greater than threshold Set it to max
    if (input >= gain)
        output = gain;

    else if (input <= -gain)
        output = -gain;

    else
        output = input;

    //Get Output
    return output;

}

////Loops through Arrary and reverses the Order of it
template <class T>
inline void reverseArray(T arr[], int start, int end)
{
    //Loop thhrough and reverse arrary
    while (start < end)
    {
        T temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
    
}

//Sets a new value for the entire arrary
template <class T>
inline void setArray(T arr[], T value, int length)
{
    //Loop Through arrary and set new value
    for (int i = 0; i < length; i++)
        arr[i] = value;
    
}

template <class T>
inline int findDivs(T dividen, T divisor)
{
    //Find How many times they divide
    bool answerFound = false;
    
    //Number of divs starting at 1
    int numDivs = 1;
    
    while (answerFound == false)
    {
        //Find ot if it dvides
        dividen = dividen - divisor;
        
        //If the answer iis found then exit
        if (dividen <= 0)
            answerFound = true;
        
        //If not add number of divs
        else
            numDivs++;
    }
    
    return numDivs;
    
}

}}

