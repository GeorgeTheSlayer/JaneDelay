//
//  ObjectDefault.h
//  DspModules
//
//  Created by Holland Sersen on 8/5/21.
//

#pragma once
#include <vector>


namespace Holland
{

//Give information on the hardware speccs adn give it to any object to init
class SystemSpecs
{
public:
    
    void setSpecs(float samplerate, float samplesperblock)
    {
        this->SAMPLERATE = samplerate;
        this->SAMPLESPERBLOCK = samplesperblock;
        this->NUMCHANNELS = 2;

    }
    
    void setSpecs(float samplerate, float samplesperblock, int numchannel)
    {
        this->SAMPLERATE = samplerate;
        this->SAMPLESPERBLOCK = samplesperblock;
        this->NUMCHANNELS = numchannel;
    }
    
    //Getters for Sample Rate
    float getSampleRate() const {return SAMPLERATE;};
    float getSamplesPerBlock() const {return SAMPLESPERBLOCK;}
    int getNumSamples() const {return NUMCHANNELS;};
    
private:
    //Sample Rate of System
    float SAMPLERATE;
    
    //How many samples per block
    float SAMPLESPERBLOCK;
    
    //How many channels in the system
    int NUMCHANNELS;
};

//Default Class
class ObjectDefault
{
public:
    virtual ~ObjectDefault() = default;
    
    //Init Object and give it its sample rate
    void init (const float samplerate)
    {
        this->SAMPLERATE = samplerate;
        AUDIOSPEC.setSpecs(SAMPLERATE, 0, 0);
        setDefault();
    }
    
    void init (const float samplerate, const float samplesperblock)
    {
        this->SAMPLERATE = samplerate;
        this->SAMPLESPERBLOCK = samplesperblock;
        AUDIOSPEC.setSpecs(SAMPLERATE, SAMPLESPERBLOCK, NUMCHANNELS);
        setDefault();
    }
    
    void init (const float samplerate, const float samplesperblock, const int numchannels)
    {
        this->SAMPLERATE = samplerate;
        this->SAMPLESPERBLOCK = samplesperblock;
        this->NUMCHANNELS = numchannels;
        AUDIOSPEC.setSpecs(SAMPLERATE, SAMPLESPERBLOCK, NUMCHANNELS);
        setDefault();
    }
    
    void init (const SystemSpecs& spec)
    {
        this->SAMPLERATE = spec.getSampleRate();
        this->SAMPLESPERBLOCK = spec.getSamplesPerBlock();
        this->NUMCHANNELS = spec.getNumSamples();
        AUDIOSPEC = spec;
        setDefault();
    }
    
    //Get the Sample Rate of the Object
    inline float getSampleRate() const { return SAMPLERATE; }
    
    //Get Samples per Block
    inline float getSamplesPerBlock() const { return SAMPLESPERBLOCK; }
    
    //Get num channels
    inline int getNumChannels() const { return NUMCHANNELS; }
    
protected:
    
    //Set Default for object
    //Override in new class
    virtual void setDefault() = 0;
    
    //Cook the varibles
    virtual void cookVaribles() = 0;

    //Set the Sample Rate for the plugin
    float SAMPLERATE;
    
    //How many samples per block
    float SAMPLESPERBLOCK;
    
    //How many channels in the system
    int NUMCHANNELS;

    //Create System Specs object to be copied
    SystemSpecs AUDIOSPEC;
};

}
