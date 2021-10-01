//
//  SmoothValue.cpp
//  DspModules
//
//  Created by Holland Sersen on 8/5/21.
//

#include "SmoothValue.hpp"

namespace Holland
{

namespace Utilities
{


void SmoothValue::setSlewInSeconds (float slew)
{
    //Set the slewed value in seconds
    float newslew = SAMPLERATE * slew;
    
    //If the value is less than or equal to zero then just make it one to apply no slew
    slewValue = (newslew > 0.0f) ? newslew : 1.0f;
    
}

float SmoothValue::getCurrentValue() 
{
    //Find Current Value and set it to Output
    float output = currentValue;
    
    
    //Find if current Value == target if no then process
    if (targetValue != currentValue)
    {
        //Find increment
        float timeInc = (targetValue - currentValue) / slewValue;
        
        //Add to current Time
        currentValue += timeInc;
        
    }
    
    //Return the output
    return output;
    
}

void SmoothValue::setDefault()
{
    //Set Default Values for Varibles
    targetValue = 0;
    currentValue = 0;
    slewValue = 1;
}


}
}
