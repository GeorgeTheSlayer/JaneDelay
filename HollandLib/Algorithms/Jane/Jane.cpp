//
//  Jane.cpp
//  DspModules
//
//  Created by Holland Sersen on 8/8/21.
//
//Varible Delay Line with Modulation

#include "Jane.hpp"

namespace Holland {
namespace Algorithms {

//TODO: Add some sort of filters in the feedback path. Maybe have the Cuttoff be set to some sort of ratio to the decimation effect?
float Jane::process(float input)
{
    cookVaribles();
    
    //Write to delay line
    delayBuffer.write(input + OUTPUT * Feedback);
    
    //Read from delay line
    OUTPUT = delayBuffer.read(delayTime + lfoOut + 1.0f);
    
    
    //Return output from delay
    return OUTPUT;
    
}

}}
