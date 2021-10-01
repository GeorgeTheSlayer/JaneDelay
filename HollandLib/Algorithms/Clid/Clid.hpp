//
//  Clid.hpp
//  DspModules
//
//  Created by Holland Sersen on 8/11/21.
//

//Euclidian Blit Crusher Effect
//Allows for muting and inverting of Bits

#pragma once
#include "../../HollandLib.hpp"
#include "../../ObjectTemplates/ObjectDefault.h"
#include "../../Utilities/Functions/Functions.h"

namespace Holland {
namespace Algorithms {

//TODO: Debug. This algorithm is prone to crashing. It also runs very slowly

class Clid : public ObjectDefault 
{
public:
//    //New contructors
//    Clid(int numbits) {bitDepth = numbits;}
//    Clid() {};
    
    //Set the bitdepth
    inline void setBits(int numbits)
    {
        bitDepth = numbits;
    }
    
    //Process the Audio
    float process(float input);
    
    Holland::Utilities::ParameterObject<int> stepParam, rotateParam, pulseParam;
    
private:
    
    int bitDepth = 8, Mode = 1;
    void cookVaribles() override
    {
        //Get the pulse output
        euclidGen.Pulses = pulseParam.getValue();
        euclidGen.Steps = stepParam.getValue();
        euclidGen.Rotate = rotateParam.getValue();
        
        //Update Euclid
        euclidGen.process();
        
        for (int i = 0; i < bitDepth; i++)
        {
            bool tempOut = euclidGen.outputStep[i];
            
            if (Mode == 1)
                binaryGen.setInvertedBit(i, tempOut);
            else
                binaryGen.setMutedBit(i, tempOut);
        }
        
    }
    
    void setDefault() override
    {
        //Init Objects
        binaryGen.setBitDepth(bitDepth);
        binaryGen.init(AUDIOSPEC);
        stepParam.init(AUDIOSPEC);
        rotateParam.init(AUDIOSPEC);
        pulseParam.init(AUDIOSPEC);
        
        //Set Param Default
        stepParam.setValue(1);
        rotateParam.setValue(0);
        pulseParam.setValue(0);
        
    }
    
    Holland::Utilities::EuclidianGenerator euclidGen;
    Holland::Utilities::DecimalToBinary binaryGen;
    
};


}}
