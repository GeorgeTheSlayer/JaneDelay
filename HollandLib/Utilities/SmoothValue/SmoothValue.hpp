//
//  SmoothValue.hpp
//  DspModules
//
//  Created by Holland Sersen on 8/5/21.
//

#pragma once

#include <cstdio>
#include "../../ObjectTemplates/ObjectDefault.h"

namespace Holland {

namespace Utilities {
    
//Smothes Value based off of sample rate
class SmoothValue : public ObjectDefault
{
public:
    //Param Varibles
    float targetValue{};
    float slewValue{};
    
    //Set how long it will take to smooth out in seconds
    void setSlewInSeconds (float slew);
    
    //Get the Current Value of the Smoothed value
    float getCurrentValue();
    
private:
    void setDefault() override;
    void cookVaribles() override {};
    float currentValue{};
    
};

}}
