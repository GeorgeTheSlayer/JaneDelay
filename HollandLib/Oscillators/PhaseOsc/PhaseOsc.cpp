//
//  PhaseOsc.cpp
//  DspModules
//
//  Created by Holland Sersen on 8/7/21.
//

#include "PhaseOsc.hpp"

namespace Holland{
namespace Osc{


float PhaseOsc::process(float i)
{
    //TODO make COEF Only change when params change
    bool outputTrue = true;
    int currentLine = 1;
    float output = 0.0f;
    float b = 0.0f;
    float m = 0.0f;
    
    if (i <= 0)
    {
        //if the first point is == 0 then return zero
        if (X[0] == 0)
        {
            output = Yptr[0];
        }
        
        //Else Evaulute based off of value
        else
        {
            m = Yptr[0] / X[0];
            output = m * i;
        }
    }
    
    else
    {
        while (outputTrue)
        {
            //If this is the line then Calculate
            if (i <= X[currentLine] && i > X[currentLine - 1])
            {
                m = (Yptr[currentLine] - Yptr[currentLine - 1]) / (X[currentLine] - X[currentLine - 1]);
                b = m * X[currentLine] - Yptr[currentLine];
                
                //Get Line
                output = m * i - b;
                outputTrue = false;
            }
            
            //If not go to next line
            else
                currentLine += 1;
        }
    }
    
    //Return the output
    return sin(output * 2.0f * M_PI);
    
}

//Return Output of Osc
const float PhaseOsc::getCurrentSample()
{
    //Get current Angle
    cookVaribles();
    
    //Get Processed Angle
    return process(currentAngle);
}

}}
