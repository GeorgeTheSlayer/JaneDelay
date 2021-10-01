//
//  DCBlocker.h
//  DspModules
//
//  Created by Holland Sersen on 8/8/21.
//

#pragma once

namespace Holland {
namespace Utilities {

//DC Blocking Filter, used to get rid of any DC/Non Alternativng Signal
class DCBlocker
{
public:
    //MARK: - Process the filter
    float process (float input)
    {
        //BiQuad Equation
        float output = input - x1 + 0.995f * y1;
        
        //Set New Past Varibles
        x1 = input;
        y1 = output;
        
        //Get Output
        return output;
    }
    
private:
    
    //Needed Varibles
    float x1 = 0, y1 = 0;
};

}
}
