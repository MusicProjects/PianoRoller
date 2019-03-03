/*
  ==============================================================================

    VolumePanel.h
    Created: 2 Jan 2019 12:47:35pm
    Author:  Adam Shield

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Setup.h"



class VolumePanel : public PianoRollComponent
{
public:

    
    
    VolumePanel(OwnedArray<Preset> * processorPresetLocation);
    ~VolumePanel();
    
    void paint (Graphics&) override;
    void resized() override;

    void mouseDown(const MouseEvent& event) override;
    void mouseDrag (const MouseEvent& event) override;
    
    String stuff;

    
private:
    
    
    
    
    
};