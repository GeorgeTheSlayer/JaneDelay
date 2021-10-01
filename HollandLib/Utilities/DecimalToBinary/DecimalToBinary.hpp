//
//  DecimalToBinary.hpp
//  DspModules
//
//  Created by Holland Sersen on 8/8/21.
//

#pragma once
#include <vector>
#include <math.h>
#include <algorithm> 
#include "../../ObjectTemplates/ObjectDefault.h"
#include "../Functions/Functions.h"

namespace Holland {
namespace Utilities { 


struct DecimalToBinary : public ObjectDefault
{
    
    //Set Bit Depth
    inline void setBitDepth(int bitdepth) {this->bitDepth = bitdepth;};

    
    //Change input into Binary
    float processInput(float input);
    
    //Return bit
    int getBit(int bitNum) const { return bit[bitNum]; }
    
    //Invert bit
    void invertBit(int bitNum) { isBitInverted[bitNum] = true; }
    void uninvertBit(int bitNum) {isBitInverted[bitNum] = false; }
    void setInvertedBit(int bitNum, bool setBit) {isBitInverted[bitNum] = setBit;};
    
    //Mute the Bits
    void muteBit(int bitNum) { isBitMuted[bitNum] = true; }
    void unmuteBit(int bitNum) { isBitMuted[bitNum] = false; }
    void setMutedBit(int bitNum, bool setBit) {isBitMuted[bitNum] = setBit;};
    
    //Reset bits
    void resetBit(int bitNum) { isBitMuted[bitNum] = false; isBitInverted[bitNum] = false;  }
    
    //set everying back to zero
    void reset()
    {
        Holland::Utilities::setArray(isBitInverted, false, bitDepth);
        Holland::Utilities::setArray(isBitMuted, false, bitDepth);
    }
    
private:
   inline void cookVaribles() override {};

    //Num of Bits to remember
    int bitDepth;
    
    //Set Defaults
    void setDefault() override;
    
    //Output
    float quantizedOutput = 0.0f;
    
    //Create an array of bits to read and write to
    //std::vector<int> bit;
    int* bit;
    
    //Truth Table
    bool* isBitInverted;
    
    bool* isBitMuted;
    
};

}}
