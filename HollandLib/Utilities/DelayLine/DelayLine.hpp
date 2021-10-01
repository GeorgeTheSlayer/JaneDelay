//
//  DelayLine.hpp
//  DspModules
//
//  Created by Holland Sersen on 8/5/21.
//

#pragma once
#include <cstdio>
#include <iostream>
#include "../Functions/Functions.h"
#include "../../ObjectTemplates/ObjectDefault.h"

namespace Holland {

namespace Utilities {

class DelayLine final : public ObjectDefault
{
public:
    explicit DelayLine(float maxdelay) {MAXDELAY = maxdelay; };
    DelayLine() {}
    
    //read from the delay line
    float read (float time)
    {
        //Get the position of the read pointer
        float readPointer = (float)writePointer - time;

        //If the Read pointer is greater than the size of the buffer Subtract size of buffer
        if (readPointer >= SIZE)
            readPointer -= SIZE;

        //If the read pointer is less than the size of the buffer. then make it positive
        if (readPointer < 0)
            readPointer += SIZE;


        //TODO allow the interpolation method to be set
        return LinearInterpolation (delayBuffer, SIZE, readPointer);
    }
    
    //Write to the delay Line
    void write (float input)
    {
        //Move Cursor
        writePointer++;

        //Make sure the Cursor is valid
        if (writePointer >= SIZE)
            writePointer -= SIZE;

        //Write to Cursor
        delayBuffer[writePointer] = input;

    }
    
    //Write at point
    void writeAtPoint (float input, float time)
    {
        //Find point to write
        int writePoint = writePointer - time;

        //Make sure point is valid
        if (writePoint >= SIZE)
            writePoint -= SIZE;


        if (writePoint < 0)
            writePoint += SIZE;

        //Write to point
        delayBuffer[writePoint] = input;

    }
    
    inline void setMaxDelay(float maxdelay) {this->MAXDELAY = maxdelay;};

    
    //Init the delay line with the sample rate
    //void init (float samplerate, float maxseconds);
    
    
private:
    //Create New Set Default Function
    void setDefault() override
    {
        //Set the Size of the buffer
        SIZE = SAMPLERATE * MAXDELAY;

        //TODO: Turn Pointer into Dedicated Vector
        //Create the Delay Buffer
        delayBuffer = new float[SIZE];

        //Make the ENTIRE buffer == 0
        std::memset(delayBuffer, 0, SIZE);

        //Set Defaults
        writePointer = 0;

    }
    
    //Create COok Function
    inline void cookVaribles() override
    {

    }
    
    //Delay Line Varibles
    float* delayBuffer;
    int writePointer = 0;
    float Output = 0.0f;
    
    //Make sure that if delay was just init only do once
    
    //TODO Make max delay initiable
    //Sets Size of buffer
    float MAXDELAY;
    float SampleRate;
    float SIZE;
    
};

}}
