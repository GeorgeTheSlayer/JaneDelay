//
//  MovingAverageFilter.h
//  DspModules
//
//  Created by Holland Sersen on 8/5/21.
//

#pragma once
#include "../../ObjectTemplates/ObjectDefault.h"

namespace Holland
{

namespace Utilities
{

//Simple Filter Class
//Used to get rid of Noise in a signal
//Good for Time Domain Processing
struct MovingAverageFilter
{
    explicit MovingAverageFilter(int numValues)
    {
        SIZE = numValues;
        buffer = new float [SIZE];
        memset(buffer, 0, sizeof (buffer) * SIZE);
    };

    //Process the Filter
    //Takes the average of multiple samples
    float process (float input)
    {
        //Reset Numerator
        numerator = 0;

        //Move over all Values
        for (int i = 1; i < SIZE; i++)
            buffer[SIZE - i] = buffer[SIZE - i - 1];

        //Set first Value to Input
        buffer[0] = input;

        //Add all values of the buffer
        for (int i = 0; i < SIZE; i++)
            numerator += buffer[i];

        //Return Average
        return numerator / SIZE;
    }
    
private:
    //How many samples it should average
    int SIZE;
    
    //Creates a Simple Array For the buffer. Allocated with Size
    float* buffer;
    
    //The Numerator of the Equation
    float numerator = 0;
    
};
}
}
