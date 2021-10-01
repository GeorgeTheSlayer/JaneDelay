//
//  PhaseOsc.hpp
//  DspModules
//
//  Created by Holland Sersen on 8/7/21.
//

#pragma once
#include "../../ObjectTemplates/OscObject.h"
#include "../../Utilities/Parameter/Parameter.h"
#include <cmath>

namespace Holland {

namespace Osc {

class PhaseOsc : public OscObject
{
public:
    //Set which wave is being used
    //void setWave(float wave);
    
    //Function to be able to add in your own waveforms
    //void addWave();
    const float getCurrentSample() override;
    
private:
    float process(float i) override;
    
    void setDefault() override
    {
        angleDelta = 0.0f;
        currentAngle = 0.0f;
        setFreq(1.0f);
        //setWave(1.0f);
    }
    
    void setY (float array[]);
    
    //Set Default array
    float X[6] = {0.00f, 0.1f, 0.25f, 0.5f, 0.75f, 1.00f};
    float Y[6] = {0.00f, 0.1f, 0.25f, 0.5f, 0.75f, 1.00f};
    
    //Waveforms
    float sineWave[6] = {0.00f, 0.1f, 0.25f, 0.5f, 0.75f, 1.00f};
    float sawWave[6] = {0.00f, 0.00f, 0.1f, 0.5f, 0.9f, 1.00f};
    float sawPulse[6] = {0.00f, 0.25f, 0.25f, 0.5f, 0.75f, 1.00f };
    float pulseWave[6] = {0.00f, 0.45f, 0.5f, 0.5f, 0.75f, 1.00f};
    
    //Pointer value that is used to refer to current buffer
    float *Yptr = sineWave;
    
    //Varibles for processing Osc
    //float m;
    //float b;
};

}
}
