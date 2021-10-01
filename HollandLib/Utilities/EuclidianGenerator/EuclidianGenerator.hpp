//
//  EuclidianGenerator.hpp
//  DspModules
//
//  Created by Holland Sersen on 8/7/21.
//

#pragma once
#include <vector>
#include "../../ObjectTemplates/ObjectDefault.h"

namespace Holland {

namespace Utilities {

//Creates a vector that createes a Euclidean Rythm
class EuclidianGenerator
{
public:
    //Parameters
    int Steps = 1, Pulses = 0, Rotate = 0;
    
    //Output Vector
    std::vector<bool> outputStep;
    
    //Function to process Gen
    void process()
    {
        //Make sure the Varibles are Reset
        cookVaribles();
        
        //Reset vector
        outputStep.erase(outputStep.begin(), outputStep.end());
        
        //Create bucket
        int bucket = 0;
        
        //Create Temp Vector
        std::vector<bool> pulseOut;
        
        //Set Buckets and stuff
        for (int i = 0; i < Steps; i++)
        {
            //Figure out if step is true or false
            bucket += Pulses;
            
            //If true
            if (bucket >= Steps)
            {
                bucket -= Steps;
                pulseOut.push_back(true);
            }
            
            //If false
            else
            {
                pulseOut.push_back(false);
            }
            
        }
        
        
        //Set the Roatation of the Array
        for (int i = 0; i < Steps; i++)
        {
            //Rotate the pulse out
            bool currentTap = pulseOut[1 +  (int)(std::abs(i + (Steps - Rotate))) % (int)Steps];
            
            //Add it to vector
            outputStep.push_back(currentTap);
        }
        
    }
    
private:
    //Make sure the varibles don't go out of bounds
    void cookVaribles()
    {
        //Make sure the rotation and pulses don't exceed the amount of steps
        Pulses = (Pulses < Steps) ? Pulses : Steps;
        Rotate = (Rotate < Steps) ? Rotate : Steps;
    }
    
};

}
}
