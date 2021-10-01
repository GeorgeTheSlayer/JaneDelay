//
//  Parameter.h
//  DspModules
//
//  Created by Holland Sersen on 8/11/21.
//

#pragma once
#include "../SmoothValue/SmoothValue.hpp"
#include "../../ObjectTemplates/ObjectDefault.h"

namespace Holland {
namespace Utilities {


template <class T>
class ParameterObject : public ObjectDefault
{
protected:
    inline void setDefault() override {};
    inline void cookVaribles() override {};

    T Value;
    T MaxValue, MinValue;
    
public:
    
    virtual inline void setValue(T value)
    {
        this->Value = value;
    }
    
    virtual inline T getValue() const
    {
        return this->Value;
    }

};

struct SmoothParameterObject final : public ParameterObject<float>
{
    inline void setValue(float value) override
    {
        valueSmoothed.targetValue = value;
    } 
    
    inline void setSlew(int samples)
    {
        valueSmoothed.slewValue = samples;
    }
    
    inline float getValue()
    {
        return valueSmoothed.getCurrentValue();
    }
    
private:
    inline void setDefault() override
    {
        //ObjectList.push_back(valueSmoothed);
        valueSmoothed.init(SAMPLERATE);
    }

    inline void cookVaribles() override {};

    SmoothValue valueSmoothed;
    
};

}}
