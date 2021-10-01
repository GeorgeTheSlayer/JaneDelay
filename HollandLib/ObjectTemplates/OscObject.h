//
//  OscObject.h
//  DspModules
//
//  Created by Holland Sersen on 8/7/21.
//

#pragma once
#include "ObjectDefault.h"

namespace Holland {

namespace Osc {

class OscObject : public ObjectDefault
{
public:
    virtual ~OscObject() = default;
    
    virtual const float getCurrentSample()
    {
        float output = process(currentAngle);
        
        cookVaribles();
        
        return output;
        
    }
    
    virtual const void setFreq(float freq)
    {
        this->Freq = freq;
    }
    
protected:
    
    virtual void setDefault() override
    {
        angleDelta = 1.0f / getSampleRate();
        currentAngle = 0.0f;
    }
    
    virtual void cookVaribles() override
    {
        angleDelta = Freq / getSampleRate();
        currentAngle += angleDelta;
        
        if (currentAngle >= 1)
            currentAngle -= 1;
    }
    
    //Where the osc is in time
    float angleDelta, currentAngle;
    float Freq = 1.0f;
    
    virtual float process(const float i) {return 0.0f;}; 
    
};

}
}
