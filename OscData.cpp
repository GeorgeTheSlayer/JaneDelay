/*
  ==============================================================================

    OscData.cpp
    Created: 28 May 2021 8:58:09pm
    Author:  Holland Sersen

  ==============================================================================
*/

#include "OscData.h"

float PhaseOsc::getCurrentSample(float i)
{
    //TODO make COEF Only change when params change
    bool outputTrue = true;
    int currentLine = 1;
    
    if (i <= 0)
    {
        if (X[0] == 0)
            outPut = Yptr[0];
        
        else
        {
            //Else Evaulute based off of value
            m = Yptr[0] / X[0];
            outPut = m * i;
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
                outPut = m * i - b;
                outputTrue = false;
            }
            
            //If not go to next line
            else
                currentLine += 1;
        }
    }
    
    return outPut;

}
    
void PhaseOsc::setWave (const float choice)
{
    
    //Won't work with floats, need to fix
    //SineWave
    if (choice >= 0.0f && choice < 1.0f)
    {
        Yptr = sineWave;
    }

    else if (choice >= 1.0f && choice < 2.0f)
    {
        Yptr = sawWave;
    }
    
    else if (choice >= 3.0f && choice < 4.0f)
    {
        Yptr = squareWave;
    }
    
    else
    {
        Yptr = pulseWave;
    }
    
}

//TODO Fix
void PhaseOsc::setFilter(float filterOne, float filterTwo)
{
    bool notset = true;
    int currentLine = 0;
    
    while (notset)
    {
        //If this Exceeds how many varibles that are in the array then end Function
        if (currentLine > sizeof(X) / sizeof(X[0]))
        {
            notset = false;
        }
        
        //If the Line if is before 0.5 then Apply Filtering
        else if (X[currentLine] < 0.5f)
        {
            Yptr[currentLine] = (Yptr[currentLine] - X[currentLine]) * filterOne + X[currentLine];
            currentLine += 1;
        }
        
        //if the Line is after 0.5 apply filtering
        else if (X[currentLine] > 0.5f)
        {
            Yptr[currentLine] = (Yptr[currentLine] - X[currentLine]) * filterTwo + X[currentLine];
            currentLine += 1;
        }
        
        else if (X[currentLine] == 0.5f)
        {
            Yptr[currentLine] = 0.5f;
            currentLine += 1;
        }
        
    }
    
}
