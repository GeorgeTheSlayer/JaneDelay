//
//  DecimalToBinary.cpp
//  DspModules
//
//  Created by Holland Sersen on 8/8/21.
//

#include "DecimalToBinary.hpp"
namespace Holland {
namespace Utilities {

void DecimalToBinary::setDefault()
{
    //Create a new buffer
    bit = new int [bitDepth];
    
    //Set bit buffer to be equal to bit depth adn be equal to zero
    isBitInverted = new bool [bitDepth];
    isBitMuted = new bool [bitDepth];
    
}


float DecimalToBinary::processInput(float input)
{
    //Init Varibles
    bool isNegative = false;
    quantizedOutput = 0.0f;
    
    //Make input only be as high as the highest possible input
    int quantIn = round(input * (pow(2, bitDepth) - 1));
    
    //Find if the Value is negative or not
    if (quantIn < 0)
    {
        isNegative = true;
        quantIn *= -1;
        bit[bitDepth + 1] = 1;
    }
    else
        bit[bitDepth + 1] = 0;
    
    for (int i = 0; i < bitDepth; i++)
    {
        //Remander of Input
        if (quantIn % 2 == 1)
            bit[i] = 1;
        else
            bit[i] = 0;
        
        if (isBitInverted[i] == true)
        {
            if (bit[i] == 1)
                bit[i] = 0;
            else
                bit[i] = 1;
        }
        
        if (isBitMuted[i] == true)
            bit[i] = 0;
        
        //Get New output
        quantizedOutput += pow(2, i) * bit[i];
        
        //Get Next Value
        quantIn = floor(quantIn / 2);
        
    }
    
    //If the output was negtiave make it negative again
    if (isNegative == true)
        quantizedOutput *= -1.0f;
    
    //Get the new quantized output
    quantizedOutput /= pow(2, bitDepth) - 1;
    
    //Put the bits in the right order
    //Bit 0 decides if it is negative or positve
    Holland::Utilities::reverseArray(bit, 0, bitDepth);
    
    return quantizedOutput;
    
}


}}
