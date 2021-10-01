//
//  Clid.cpp
//  DspModules
//
//  Created by Holland Sersen on 8/11/21.
//

#include "Clid.hpp"

namespace Holland {
namespace Algorithms {

float Clid::process(float input)
{
    cookVaribles();
    
    return binaryGen.processInput(input);
    
}

}}
