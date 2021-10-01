//
//  RBJFilter.cpp
//  DspModules
//
//  Created by Holland Sersen on 8/6/21.
//

#include "RBJFilter.hpp"


namespace Holland
{
namespace Filter
{
namespace RBJ
{

void LowShelfFilter::cookVaribles()
{
    //Low Shelf Filter Equations
    float w0 = 2 * 3.14 * Freq / SAMPLERATE;
    float A = std::pow(10, Gain/40);
    float alpha = std::sin(w0)/2 * std::sqrt((A + 1/A) * (1/S - 1) + 2);
    float beta = 2 * std::sqrt(A) * alpha;
    
    b0 =   A*( (A + 1) - (A - 1) * std::cos(w0) + beta);
    b1 = 2*A*( (A - 1) - (A + 1) * std::cos(w0)       );
    b2 =   A*( (A + 1) - (A - 1) * std::cos(w0) - beta);
    a0 =       (A + 1) + (A - 1) * std::cos(w0) + beta ;
    a1 =  -2*( (A - 1) + (A + 1) * std::cos(w0)       );
    a2 =       (A + 1) + (A - 1) * std::cos(w0) - beta ;
    
}

void HighShelfFilter::cookVaribles()
{
    //High Shelf Filter
    float w0 = 2 * 3.14 * Freq / SAMPLERATE;
    float A = std::pow(10, Gain/40);
    float alpha = std::sin(w0)/2 * std::sqrt((A + 1/A) * (1/S - 1) + 2);
    float beta = 2 * std::sqrt(A) * alpha;
    
    b0 =   A*( (A + 1) + (A - 1) * std::cos(w0) + beta);
    b1 =-2*A*( (A - 1) + (A + 1) * cos(w0) );
    b2 =   A*( (A + 1) + (A - 1) * cos(w0) - beta);
    a0 =       (A + 1) - (A - 1) * cos(w0) + beta ;
    a1 =   2*( (A - 1) - (A + 1) * cos(w0) );
    a2 =       (A + 1) - (A - 1) * cos(w0) - beta ;

}

void BellCurveFilter::cookVaribles()
{
    //Peaking Eq
    float w0 = 2 * 3.14 * Freq / SAMPLERATE;
    float A = std::pow(10, Gain / 40);
    float alpha = sin(w0) * sinh(0.693147 / 2 * BW * w0/sin(w0));
    
    b0 =  1 + alpha*A;
    b1 = -2*cos(w0);
    b2 =  1 + alpha;
    a0 =  1 + alpha;
    a1 = -2*cos(w0);
    a2 =  1 - alpha;
    
}

void LowPassFilter::cookVaribles()
{
    //Create Coeficents
    float w0 = 2 * 3.14 * Freq / SAMPLERATE;
    float alpha = sin(w0) / (2 * Q);
    
    b0 =  (1 - cos(w0))/2;
    b1 =   1 - cos(w0);
    b2 =  (1 - cos(w0))/2;
    a0 =   1 + alpha;
    a1 = -2 * cos(w0);
    a2 =  1 - alpha;
}

void HighPassFilter::cookVaribles()
{
    //Create Coeficents
    float w0 = 2 * 3.14 * Freq / SAMPLERATE;
    float alpha = sin(w0) / (2*Q);
    
    b0 =  (1 + cos(w0))/2;
    b1 = -(1 + cos(w0));
    b2 =  (1 + cos(w0))/2;
    a0 =   1 + alpha;
    a1 =  -2*cos(w0);
    a2 =   1 - alpha;
}

void AllPassFilter::cookVaribles()
{
    //Create Coeficents
    float w0 = 2 * 3.14 * Freq / SAMPLERATE;
    float alpha = sin(w0) / (2*Q);
    
    b0 = 1 - alpha;
    b1 = -2*cos(w0);
    b2 = 1 + alpha;
    a0 = 1 + alpha;
    a1 = -2*cos(w0);
    a2 = 1 - alpha;
}


}
}
}
