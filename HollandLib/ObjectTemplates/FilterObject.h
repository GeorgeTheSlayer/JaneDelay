//
//  FilterObject.h
//  DspModules
//
//  Created by Holland Sersen on 8/7/21.
//

#pragma once
#include "ObjectDefault.h"

namespace Holland {

namespace Filter {


class FilterObject : public ObjectDefault
{
protected:
    //Function to be overridden
    virtual float process (const float currentSample) {return 0.0f;};
    
    void setDefault() override
    {
        //Recursive Varibles
        xN1 = xN2 = 0.0f;
        yN1 = yN2 = 0.0f;
        z1 = z2 = 0.0f;
        
        //Input Vars
        x = 0.0f;
        y = 0.0f;
        
        //Equation Vars
        a0 = a1 = a2 = 0.0f;
        b0 = b1 = b2 = 0.0f;
        
    }
    
    //Input Vars
    float x, y, xN1, xN2, yN1, yN2, z1, z2;
    
    //Filter Coeficeints
    float a0, a1, a2, b0, b1, b2;
    
    //Misc Filter Coefcients
    float Gain, Freq, S, BW, Q;
    
};

class RBJFilterForm : public FilterObject
{
public:
    
    float process (const float currentSample) override
    {
        cookVaribles();
        
    //Make X == Current Sample
    x = currentSample;
    
    //Preform Calculation
    y = (b0/a0) * x + (b1/a0) * xN1 + (b2/a0) * xN2 - (a1/a0) * yN1 - (a2/a0) * yN2;
    
    //Assign past samples
    xN2 = xN1;
    xN1 = x;
    yN2 = yN1;
    yN1 = y;
    
    //Return Output
    return y;
    }
    
};

class IIRFilterFormOne : public FilterObject
{
    
public:
    
    //Processing Current Sample
    float process  (const float currentSample) override
    {
        cookVaribles();
        
        //Make X == Current Sample
        x = currentSample;
        
        //Preform Calculation
        y = x * a0 + z1;
        
        //Assign past samples
        z1 = x * a1 - z2 - b1 * y;
        z2 = x * a2 - b2 * y;
        
        //Return Output
        return y;
    }
    
};
    

}
}
