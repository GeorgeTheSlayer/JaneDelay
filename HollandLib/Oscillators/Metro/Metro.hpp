//
//  Metro.hpp
//  DspModules
//
//  Created by Holland Sersen on 8/7/21.
//

#pragma once
#include "../../ObjectTemplates/OscObject.h"

namespace Holland {

namespace Osc {

class Metro : public OscObject
{
public:
    //TODO Set Freq in Seconds
    
    bool getTrigger() const
    {
        return Trigger;
    }
    
private:
    
    void cookVaribles() override
    {
        currentAngle += angleDelta;
        
        if (currentAngle >= 1)
        {
            currentAngle -= 1;
            Trigger = true;
        }
        
        else
        {
            Trigger = false;
        }
        
    }
    
    void setDefault() override
    {
        angleDelta = 1.0f / SAMPLERATE;
        Trigger = false;
    }
    
    bool Trigger = false;
    
};

}
}
