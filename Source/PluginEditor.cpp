/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PianoRoll1AudioProcessorEditor::PianoRoll1AudioProcessorEditor (PianoRoll1AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), midiLabel("0"), pianoRoll(&p.presets), volumePanel(&p.presets)
{    
    setVisible(true);
    setResizable(true, true);
    isChildOfBeatCanvas = false;
    
    currentPreset = 1;
    currentTrack = 1;
    currentBeat = 0.0f;
    currentNumOfBeats = 4;
    previousVal = -1.0f;
    beatIndex = 0;
    sixteenthCounter = 3;
    tripletCounter = 2;
    previousOrder = {0};
    arpeggioDirection = "Ascending";
    
    presets = &pianoRoll.presets;
    playPosition = "";
    generateButton.setButtonText("Generate");
    
    //Setup Note Name in the top right corner of window==========================
    noteName = "";
    pianoRoll.noteName = &noteName; //Allow piano roll to edit this value.
    noteName.addListener(this);
    
    //Slider look and feels======================================================
    getLookAndFeel().setColour(Slider::thumbColourId, whiteBlue);
    getLookAndFeel().setColour(Slider::textBoxOutlineColourId, Colours::black);
    getLookAndFeel().setColour(Slider::textBoxTextColourId, Colours::black);
    getLookAndFeel().setColour(Slider::trackColourId, whiteBlue);
    getLookAndFeel().setColour(Slider::backgroundColourId, Colours::black);
    getLookAndFeel().setColour(TextButton::buttonColourId, pianoRoll.greyOff);
    getLookAndFeel().setColour(TextButton::textColourOffId, Colours::black);
    
    
    //Add and make visibles======================================================
    addAndMakeVisible(&pianoRoll);
    addAndMakeVisible(&volumePanel);
    addAndMakeVisible(&playCursorWindow);
    addAndMakeVisible(&midiLabel);
    addAndMakeVisible(&presetSlider);
    addAndMakeVisible(&trackSlider);
    addAndMakeVisible(&beatSlider);
    addAndMakeVisible(&rootMenu);
    addAndMakeVisible(&scaleMenu);
    addAndMakeVisible(&generateButton);
    addAndMakeVisible(&monoPolyMenu);
    addAndMakeVisible(&generatorMenu);
    addAndMakeVisible(&arpDirectionMenu);
    addAndMakeVisible(&arpSlider);
    arpDirectionMenu.setVisible(false);
    
    //addAndMakeVisible(&noteLabel);
    
    getTopLevelComponent()->setName("foo");
    
    //Setup Sliders===============================================================
    presetSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState,PRESET_ID,presetSlider);
    
    trackSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState,TRACK_ID,trackSlider);
    
    beatSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState,BEATS_ID,beatSlider);
    
    presetSlider.setRange(1,numOfPresets,(int)1);
    trackSlider.setRange(1,numOfTracks,(int)1);
    beatSlider.setRange(1,maxBeats,(int)1);
    
    presetSlider.setTextBoxStyle(Slider::TextBoxLeft, true, getParentWidth()*0.025, getParentHeight()*topBorder*0.333);
    trackSlider.setTextBoxStyle(Slider::TextBoxLeft, true, getParentWidth()*0.025, getParentHeight()*topBorder*0.333);
    beatSlider.setTextBoxStyle(Slider::TextBoxLeft, true, getParentWidth()*0.025, getParentHeight()*topBorder*0.333);
    
    arpSlider.setSliderStyle(juce::Slider::ThreeValueHorizontal);
    
    
    //Add Listeners===============================================================
    processor.treeState.addParameterListener(PRESET_ID, this); //Adds listener to preset slider tree value.
    processor.treeState.addParameterListener(TRACK_ID, this); //Adds listener to track slider tree value.
    processor.treeState.addParameterListener(BEATS_ID, this); //Adds listener to track slider tree value.
    presetSlider.addMouseListener(this, true);
    beatSlider.addMouseListener(this, true);
    generateButton.addListener(this);
    
    processor.playPosition.addListener(this); //The original way to update playhead,
    //processor.playPositionToSendPlayheadUpdate.addListener(this);
    setWantsKeyboardFocus(true);
    addKeyListener(this);
    
    presetSlider.setValue(processor.currentPreset);
    trackSlider.setValue(processor.currentTrack);
    beatSlider.setValue(processor.presets[currentPreset]->numOfBeats);
    
    
    //Setup Dropdown Menus======================================================
    for(int i=0;i<12;i++){
        rootMenu.addItem(theory.setClassToPitchName[i], i+1);
    }
    std::for_each(theory.modeMap.begin(), theory.modeMap.end(), [this](std::pair<String, Array<int>> mode){
        scaleMenu.addItem(mode.first, scaleMenu.getNumItems()+1);
    });
    monoPolyMenu.addItem("mono", 1);
    monoPolyMenu.addItem("poly", 2);
    generatorMenu.addItem("random", 3);
    generatorMenu.addItem("arp16th", 4);
    generatorMenu.addItem("arp16th Broken", 5);
    generatorMenu.addItem("arp8th", 6);
    generatorMenu.addItem("arp8th Broken", 7);
    generatorMenu.addItem("arpTriplet", 8);
    generatorMenu.addItem("arpTriplet Broken", 9);
    arpDirectionMenu.addItem("ascend", 1);
    arpDirectionMenu.addItem("descend", 2);
    arpDirectionMenu.addItem("expand", 3);
    arpDirectionMenu.addItem("seq1", 4);
    arpDirectionMenu.addItem("seq2", 5);
    arpDirectionMenu.addItem("seq3", 6);
    arpDirectionMenu.addItem("seq4", 7);
    arpDirectionMenu.addItem("seq4", 8);
    arpDirectionMenu.addItem("seq5", 9);
    
    //Dropdown look&feel and onChange============================================
    getLookAndFeel().setColour(ComboBox::backgroundColourId, pianoRoll.greyOff);
    getLookAndFeel().setColour(ComboBox::outlineColourId, Colours::black);
    getLookAndFeel().setColour(ComboBox::textColourId, Colours::black);
    getLookAndFeel().setColour(ComboBox::arrowColourId, Colours::black);
    
    rootMenu.setSelectedItemIndex(0, NotificationType::dontSendNotification);
    scaleMenu.setText("Major", NotificationType::dontSendNotification);
    generatorMenu.setText("random", NotificationType::dontSendNotification);
    arpDirectionMenu.setText("ascend", NotificationType::dontSendNotification);
    monoPolyMenu.setSelectedItemIndex(0);
    rootMenu.onChange = [this] { rootMenuChanged(); };
    scaleMenu.onChange = [this] { scaleMenuChanged(); };
    monoPolyMenu.onChange = [this] { monoPolyMenuChanged(); };
    generatorMenu.onChange = [this]{ generatorMenuChanged(); };
    arpDirectionMenu.onChange = [this]{ arpDirectionMenuChanged(); };
    
    //OSC MESSAGES=================================================================
    if (! connect(6448)){}; //Connect to OSC messages from Max.
    addListener(this, "/juce");
    
    Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
    int monitorWidth = r.getWidth();
    int monitorHeight = r.getHeight();
    
    /*  //THIS WILL SAVE ALL VALUES TO VALUE TREE========TODO
    for (int preset=1;preset<=numOfPresets;preset++){
        for (int track=1;track<=numOfTracks;track++){
            for (int sixteenth=0;sixteenth<maxBeats*4;sixteenth++){
                processor.treeState.state.addChild(ValueTree(), <#int index#>, nullptr);
            }
        }
    }
     
    */
    
    presetToBeUpdated = 0;
    beatsToBeUpdated = 0;
    setSize (monitorWidth*0.85, monitorHeight*0.85);
    noteLabel.setText("foo", dontSendNotification);
    noteLabel.setColour(Label::backgroundColourId, pianoRoll.greyOff);
    
}

PianoRoll1AudioProcessorEditor::~PianoRoll1AudioProcessorEditor()
{    
    processor.treeState.removeParameterListener(PRESET_ID, this);
    processor.treeState.removeParameterListener(TRACK_ID, this);
    processor.treeState.removeParameterListener(BEATS_ID, this);
    processor.playPosition.removeListener(this);
    juce::OSCReceiver::removeListener(this);
}



//==============================================================================
void PianoRoll1AudioProcessorEditor::paint (Graphics& g)
{
    float width = getWidth();
    float height = getHeight();
    float yBorder = getHeight()*0.01;

    //g.fillAll(Colour(156,168,152));
    g.fillAll(greyOff);
    
    tripletSwitches.clear();
    
    if(tripletButtons){
        //int numOfBeats = pianoRoll.presets[currentPreset]->numOfBeats;
        int numOfBeats = processor.presets[currentPreset]->numOfBeats;
        float beatWidth = (width / ((float)numOfBeats) );
        float ellipseWidth = beatWidth*0.333;
        float ellipseHeight = height * topBorder * 0.225;
        float x;
        float y = height * topBorder * 0.66;

        for(int beat=0; beat<numOfBeats;beat++){
            x = beat * beatWidth + beatWidth*0.333;
            
            //if(pianoRoll.presets[currentPreset]->tracks[currentTrack]->beatSwitch[beat] == 0){
            if(processor.presets[currentPreset]->tracks[currentTrack]->beatSwitch[beat] == 0){
                g.setColour(Colour(156,168,152)); //If not a triplet
            }else{g.setColour(Colours::limegreen);} //If a triplet.
            g.fillEllipse(x, y, ellipseWidth, ellipseHeight);
            g.setColour(Colours::black);
            g.drawEllipse(x, y, ellipseWidth, ellipseHeight, 1.);
            
            tripletSwitches.add(Array<float>{x+(ellipseWidth/2), y + (ellipseHeight/2)});
        }
        
    }
    
    if(tripletToggleHeight){
        float y = height*topBorder;
        float bottom = y + (tripletToggleHeight*height);
        int numOfBeats = pianoRoll.presets[currentPreset]->numOfBeats;
        float beatWidth = (width / ((float)numOfBeats) );
        float beatHeight = height * tripletToggleHeight;
        float x;
        int lineWidth;
        
        g.setColour(Colours::black);
        g.drawLine(0.0f, y, width, y, 3); //Top Line
        
        for(int beat=0; beat<=numOfBeats;beat++){
            x = beat * beatWidth;
            
            g.drawLine(x, y, x, bottom, 3);
            g. drawText("3", x, y, beatWidth, beatHeight, Justification::centred);
        }
    }
    
    if(textColumnWidth> 0.){
        float x = textColumnWidth * 0.25 * width;
    
        Path myPath;
        myPath.addRoundedRectangle(x, height*0.034f, textColumnWidth*0.5f*width, height*0.04f, 5.f, 1.f);
        myPath.closeSubPath();
        g.setColour(whiteBlue);
        g.fillPath(myPath);
    
    
        myPath.startNewSubPath(0., 0.);
        myPath.addRoundedRectangle(x, height*0.134f, textColumnWidth*0.5f*width, height*0.04f, 5.f, 1.f);
        myPath.closeSubPath();
        g.setColour(whiteBlue);
        g.fillPath(myPath);
    
    
        g.setColour(Colours::black);
        g.drawRoundedRectangle(x, height*0.034f, textColumnWidth*0.5f*width, height*0.04f, 5.f, 1.f);
    
        g.setColour(Colours::black);
        g.drawRoundedRectangle(x, height*0.134f, textColumnWidth*0.5f*width, height*0.04f, 5.f, 1.f);
    
    
        g.setFont(15);
        g.drawText("Preset", 0., yBorder, width*textColumnWidth, height*0.01, Justification::centred);
        g.drawText((String)currentPreset, 0., height*0.05, width*textColumnWidth, height*0.01, Justification::centred);
    }
    
    if(topBorder){
        //PRESET SLIDER "PRESET" LABEL
        float sliderWidth = presetSlider.getWidth();
        float sliderHeight = presetSlider.getHeight();
        float textWidth = presetSlider.getWidth() - presetSlider.getTextBoxWidth();
        float textHeight = presetSlider.getHeight();
        //float x = presetSlider.getX();
        float x = presetSlider.getX() + (sliderWidth * presetSlider.getTextBoxWidth()/sliderWidth);
        float y = presetSlider.getY()-  (topBorder*height*0.2);
        g.setFont(textHeight * 0.333);
        g.setColour(Colours::black);
        g.drawText("PRESET", x, y, textWidth, textHeight, Justification::centred);
        
        float spacing = sliderSpacing*width;
        
        //TRACK SLIDER "TRACK" LABEL
        g.drawText("TRACK", x+spacing, y, textWidth, textHeight, Justification::centred);
        
        //BEAT SLIDER "BEAT" LABEL
        g.drawText("BEATS", x+(spacing*2), y, textWidth, textHeight, Justification::centred);
        
    }
    
    //String playTime = (String) processor.lastPosInfo.ppqPosition;
    
    //g.drawText(playPosition, (sliderSpacing*3*width), topBorder/6, width/10, height/10, Justification::centred);
    
    
    g.setColour(Colours::black);
    g.setFont((height + width) / 80);
    
    float noteNameX = 0.91*width; // X Position of displayed note name.
    float noteNameY = height*0.004;
    float noteNameHeight = height * topBorder * 0.25;
    
    if(isChildOfBeatCanvas == false){
        g.drawText(noteName.getValue().toString(), noteNameX, noteNameY, width/10, noteNameHeight, Justification::centred);
        g.drawRoundedRectangle(noteNameX + (0.015*width), noteNameY, width/10 - (0.03*width), noteNameHeight, 10.0f, 1.0f);
    }
    
}



//==============================================================================

    
    
void PianoRoll1AudioProcessorEditor::resized()
{
    pianoRoll.setBoundsRelative(textColumnWidth, topBorder+tripletToggleHeight, 1.-textColumnWidth, 0.8-topBorder-tripletToggleHeight);
    volumePanel.setBoundsRelative(textColumnWidth, 0.8, 1.-textColumnWidth, 0.2);
    playCursorWindow.setBoundsRelative(0.0f, 0.0f+topBorder, 1., 1.);
    
    
    if(topBorder){
        float halfTopBorder = topBorder/2;
        float panelX = 0.726;
        float panelY = topBorder * 0.05;
        float smallInput = 0.06f;
        float largeInput = 0.09;
        float inputHeight = topBorder * 0.225;
        float inputRow = inputHeight*1.1f;
        float rowTwo = panelY + inputRow;
        float rowThree = rowTwo + inputRow;
        float spacing = 0.001;
        
        presetSlider.setBoundsRelative(0.01f, topBorder/8, 0.2f, halfTopBorder);
        trackSlider.setBoundsRelative(0.01f+sliderSpacing, topBorder/8, 0.2f, halfTopBorder);
        beatSlider.setBoundsRelative(0.01f+(sliderSpacing*2), topBorder/8, 0.2f, halfTopBorder);
        
        if (isChildOfBeatCanvas == false){
            //Row 1
            rootMenu.setBoundsRelative(panelX, panelY, smallInput-spacing, inputHeight);
            monoPolyMenu.setBoundsRelative(panelX+smallInput, panelY, smallInput-spacing, inputHeight);
            generateButton.setBoundsRelative(panelX + (smallInput*2), panelY, smallInput-spacing, inputHeight);
            //Row 2
            scaleMenu.setBoundsRelative(panelX, rowTwo, largeInput-spacing, inputHeight);
            generatorMenu.setBoundsRelative(panelX+largeInput, rowTwo, largeInput-spacing, inputHeight);
            arpDirectionMenu.setBoundsRelative(panelX + (largeInput*2), rowTwo, largeInput-spacing, inputHeight);
            //Row3
            //arpSlider.setBoundsRelative(panelX, rowThree, largeInput*2, topBorder/5);
        }
        
    }
   /*
    if(topBorder){
        auto r = getLocalBounds();
        
        auto topWindowHeight = getHeight()*topBorder;
        
        auto topWindow = r.removeFromTop(topWindowHeight);
        
        presetSlider.setBounds(topWindow.removeFromLeft(200));
        
    }
     */
}
    


//==============================================================================
    


void PianoRoll1AudioProcessorEditor::oscMessageReceived(const juce::OSCMessage &Message){
    //First value is an integer.
    if (Message.size() > 0 && Message[0].isInt32()){
        
        OwnedArray<int> theArray;
        repaint();
        
    }
    
    //"Function" calls.
    if (Message.size() > 0 && Message[0].isString()){
        
        //setPreset(int preset)
        if(Message[0].getString() == "setPreset"){
            int preset = Message[1].getInt32();
            currentPreset = preset;
            pianoRoll.currentPreset = preset;
            volumePanel.currentPreset = preset;
            repaint();
        }
        
        //updateNote(int col, int pitch, int beatSwitch)
        else if(Message[0].getString() == "updateNote"){
            int col = Message[1].getInt32();
            int pitch = Message[2].getInt32();
            int beatSwitch = Message[3].getInt32();
            pianoRoll.updateNote(col, pitch, beatSwitch);
            volumePanel.updateNote(col, pitch, beatSwitch);
        }
        
        //void PianoRoll::updateBeatSwitch(int beat)
        else if(Message[0].getString() == "updateBeatSwitch"){
            pianoRoll.updateBeatSwitch(Message[1].getInt32(), Message[2].getInt32());
            volumePanel.updateBeatSwitch(Message[1].getInt32(), Message[2].getInt32());
        }
        
        else if(Message[0].getString() == "updateVolume"){
            int col = Message[1].getInt32();
            int vol = Message[2].getInt32();
            int beatSwitch = Message[3].getInt32();
            //TODO
        }
        
        else if(Message[0].getString() == "updateNumOfBeats"){
            int beats = Message[1].getInt32();
            int preset;
            if (Message.size() == 3){preset = Message[2].getInt32();}
            else{preset = currentPreset;}
            pianoRoll.updateNumOfBeats(beats, preset);
            volumePanel.updateNumOfBeats(beats, preset);
        }
        
        if(Message[0].getString() == "playCursor"){
            playCursorWindow.setPlayCursor(Message[1].getFloat32());
        }
        
        if(Message[0].getString() == "changeRhythmDiv"){
            int track = Message[1].getInt32();
            int beat = Message[2].getInt32();
            int beatSwitch = Message[3].getInt32();
            pianoRoll.changeRhythmDiv(track, beat, beatSwitch);
            volumePanel.changeRhythmDiv(track, beat, beatSwitch);
        }
        
        if(Message[0].getString() == "currentPreset"){
            int preset = Message[1].getInt32();
            currentPreset = preset;
            pianoRoll.updatePreset(preset);
            volumePanel.updatePreset(preset);
        }
        if(Message[0].getString() == "currentTrack"){
            int track = Message[1].getInt32();
            currentTrack = track;
            trackSlider.setValue(currentTrack); //Automatically updates pianoroll and vol panel.
            repaint();
        }
        
        //void PianoRollComponent::noteOnOff(int track, int div, int note, int onOff)
        if(Message[0].getString() == "noteOnOff"){
            int track = Message[1].getInt32();
            int div = Message[2].getInt32();
            int note = Message[3].getInt32();
            int onOff = Message[4].getInt32();
            pianoRoll.noteOnOff(track, div, note, onOff);
            volumePanel.noteOnOff(track, div, note, onOff);
        }
        
        //void PianoRollComponent::copyPreset(int presetSource, int presetReplaced)
        if(Message[0].getString() == "copyPresets"){
            int presetSource = Message[1].getInt32();
            int presetReplaced = Message[2].getInt32();
            pianoRoll.copyPreset(presetSource, presetReplaced);
            volumePanel.copyPreset(presetSource, presetReplaced);
            currentPreset = presetReplaced;
            repaint();
        }
        
        if(Message[0].getString() == "isChildOfBeatCanvas"){
            isChildOfBeatCanvas = true;
            pianoRoll.isChildOfBeatCanvas = true;
            pianoRoll.repaint();
            repaint();
        }
        
        
        repaint();
    }
    
    
    
}

void PianoRoll1AudioProcessorEditor::setMidiDisplay(int midi){
    midiLabel.setName((String) midi);
}

float PianoRoll1AudioProcessorEditor::dbToVolume(float db){
    return powf(10.0f, 0.05f * db);
}

float PianoRoll1AudioProcessorEditor::volumeToDB(float vol){
    return 20.0f * log10f(vol);
}

void PianoRoll1AudioProcessorEditor::playNote(int pitch, int volume){
    Array<int> toPlay;
    toPlay.add(pitch);
    toPlay.add(volume);
    processor.midiStream.add(toPlay);
}




void PianoRoll1AudioProcessorEditor::parameterChanged(const juce::String &parameterID, const float newValue){
    if(parameterID == PRESET_ID){
        const int preset = newValue;
        String monoPoly;
        processor.currentPreset = preset;
        pianoRoll.updatePreset(preset);
        volumePanel.updatePreset(preset);
        processor.presets[preset]->isMono ? monoPoly="mono": monoPoly="poly";
        monoPolyMenu.setText(monoPoly);
        repaint();
        
        currentPreset = preset;
        //currentNumOfBeats = pianoRoll.presets[currentPreset]->numOfBeats;
        currentNumOfBeats = processor.presets[currentPreset]->numOfBeats;
        beatSlider.setValue(currentNumOfBeats);
        presetToBeUpdated = preset;
        rootMenu.setSelectedItemIndex(processor.presets[currentPreset]->root, NotificationType::dontSendNotification);
        scaleMenu.setText(processor.presets[processor.currentPreset]->currentMode, NotificationType::dontSendNotification);
        generatorMenu.setText(processor.presets[processor.currentPreset]->generatorType, NotificationType::dontSendNotification);
        arpDirectionMenu.setText(processor.presets[processor.currentPreset]->arpType, NotificationType::dontSendNotification);
        //pianoRoll.changeBeatCanvasPreset(preset);
        
    }
    
    if(parameterID == TRACK_ID){
        currentTrack = newValue;
        
        const int track = newValue;
        pianoRoll.updateTrack(track);
        volumePanel.updateTrack(track);
        processor.currentTrack = track;
        repaint();
    }
    
    if(parameterID == BEATS_ID){
        currentNumOfBeats = newValue;
        
        const int numOfBeats = newValue;
        processor.presets[currentPreset]->numOfBeats = numOfBeats;
        pianoRoll.updateNumOfBeats(numOfBeats);
        volumePanel.updateNumOfBeats(numOfBeats);
        repaint();
        
        beatsToBeUpdated = numOfBeats;
        //pianoRoll.changeBeatCanvasBeats(numOfBeats);
    }
    
}





//COMMUNICATE TO BEAT CANVAS THAT PARAMETERS HAVE CHANGED==================================

void PianoRoll1AudioProcessorEditor::mouseUp(const juce::MouseEvent &event){
    if (presetToBeUpdated > 0){
        pianoRoll.changeBeatCanvasPreset(presetToBeUpdated);
        presetToBeUpdated = 0;
    }
    if(beatsToBeUpdated > 0){
        pianoRoll.changeBeatCanvasBeats(beatsToBeUpdated);
        beatsToBeUpdated = 0;
    }
    
    for(int i=0;i<beatsClicked.size();i++){
        int beatNum = beatsClicked[i];
        //int tripVal = pianoRoll.presets[currentPreset]->tracks[currentTrack]->beatSwitch[beatNum];
        //pianoRoll.changeBeatCanvasTriplet(beatNum, tripVal);
        int tripVal = processor.presets[currentPreset]->tracks[currentTrack]->beatSwitch[beatNum];
        pianoRoll.changeBeatCanvasTriplet(beatNum, tripVal);
    }
    beatsClicked.clear();
}


//FLIP TRIPLET SWITCHES=========================================================//


void PianoRoll1AudioProcessorEditor::mouseDown(const juce::MouseEvent &event){
    if (presetSlider.isMouseButtonDown() != true && beatSlider.isMouseButtonDown() != true){
    
        float x = getMouseXYRelative().getX();
        float y = getMouseXYRelative().getY();
        float width = getWidth();
        float height = getHeight();
        
        for(int beat=0; beat<tripletSwitches.size(); beat++){
            float difX = fabsf( x - tripletSwitches[beat][0] );
            float difY = fabsf( y - tripletSwitches[beat][1] );
            
            if (beatsClicked.contains(beat) == false){ //If hasn't already been clicked or dragged over.
                if(difX < width/20 && difY < height/20){ //If close enough to the beat switch.
                    //if(pianoRoll.presets[currentPreset]->tracks[currentTrack]->beatSwitch[beat] == 0){
                    if(processor.presets[currentPreset]->tracks[currentTrack]->beatSwitch[beat] == 0){
                        processor.presets[currentPreset]->tracks[currentTrack]->beatSwitch.set(beat, 1);
                        pianoRoll.presets[currentPreset]->tracks[currentTrack]->beatSwitch.set(beat, 1);
                        volumePanel.presets[currentPreset]->tracks[currentTrack]->beatSwitch.set(beat, 1);
                    }else{
                        processor.presets[currentPreset]->tracks[currentTrack]->beatSwitch.set(beat, 0);
                        pianoRoll.presets[currentPreset]->tracks[currentTrack]->beatSwitch.set(beat, 0);
                        volumePanel.presets[currentPreset]->tracks[currentTrack]->beatSwitch.set(beat, 0);
                    }
                    
                    beatsClicked.add(beat);
                }
            }
        }
        
        repaint();
        volumePanel.repaint();
    }
}

void PianoRoll1AudioProcessorEditor::mouseDrag(const juce::MouseEvent &event){
    mouseDown(event);
}


void PianoRoll1AudioProcessorEditor::sliderValueChanged(juce::Slider *slider){
    
}




void PianoRoll1AudioProcessorEditor::valueChanged(juce::Value &value){
    if(value.refersToSameSourceAs(processor.playPosition)){
        auto val = value.getValue();
        float floatVal = val.toString().getFloatValue();
        playCursorWindow.setPlayCursor(floatVal);
    }else if(value.refersToSameSourceAs(noteName)){
        repaint();
    }
    
}



void PianoRoll1AudioProcessorEditor::prepToPlayNote(const int note, const int div){
    
    
    if (div == 4){
        //playPosition = std::to_string(note);
        //playPosition = std::to_string(valDecimals);
        //int sixteenth = beatIndex*4 + (valDecimals*4);
        
        if (pianoRoll.presets[currentPreset]->tracks[currentTrack]->beatSwitch[beatIndex] == 0){
            int pitch = pianoRoll.presets[currentPreset]->tracks[currentTrack]->sixteenths[note];
            
            if (pitch > 0){
                int vol = volumePanel.presets[currentPreset]->tracks[currentTrack]->sixteenthVols[note];
                //playPosition = std::to_string(pitch) + " " + std::to_string(vol);
                playNote(pitch, vol);
            }
        }
    }
    else if(div == 3){
        if (pianoRoll.presets[currentPreset]->tracks[currentTrack]->beatSwitch[beatIndex] == 1){
            int pitch = pianoRoll.presets[currentPreset]->tracks[currentTrack]->triplets[note];
            
            if (pitch > 0){
                int vol = volumePanel.presets[currentPreset]->tracks[currentTrack]->tripletVols[note];
                //playPosition = std::to_string(pitch) + " " + std::to_string(vol);
                playNote(pitch, vol);
            }
        }
        
    }
}


bool PianoRoll1AudioProcessorEditor::keyPressed(const juce::KeyPress &key, juce::Component *originatingComponent){
    int keyCode = key.getKeyCode();
    pianoRoll.stuff = (String) keyCode;
    int newPreset;
    if(keyCode >= 49 && keyCode < 58){
        newPreset = keyCode - 48;
        presetSlider.setValue(newPreset);
    }else if(keyCode == 32){ //Spacebar
        pianoRoll.spacebar();
    }else if(keyCode == 63232){ //Up Arrow
        processor.octaveShift(1);
        pianoRoll.repaint();
    }else if(keyCode == 63233){ //Down Arrow
        processor.octaveShift(-1);
        pianoRoll.repaint();
    }
    pianoRoll.repaint();
}

void PianoRoll1AudioProcessorEditor::rootMenuChanged(){
    processor.root = rootMenu.getSelectedItemIndex();
    processor.presets[currentPreset]->root = rootMenu.getSelectedItemIndex();
    scaleMenuChanged();
}

void PianoRoll1AudioProcessorEditor::scaleMenuChanged(){
    String scaleName = scaleMenu.getText();
    Array<int> scaleRef = theory.modeMap[scaleName];
    int root = processor.root;
    
    processor.scale.clear();
    for(int i=0;i<scaleRef.size();i++){
        processor.scale.add((scaleRef[i] + root) % 12);
    }
    processor.presets[currentPreset]->currentMode = scaleName;
    
    buttonClicked(&generateButton);
}

void PianoRoll1AudioProcessorEditor::monoPolyMenuChanged(){
    String monoPoly = monoPolyMenu.getText();
    bool isMono;
    monoPoly == "mono" ? isMono=true: isMono=false;
    processor.presets[processor.currentPreset]->isMono = isMono;
    repaint();
    pianoRoll.repaint();
    volumePanel.repaint();
}

void PianoRoll1AudioProcessorEditor::generatorMenuChanged(){
    generatorMenu.getText() == "random" ? arpDirectionMenu.setVisible(false): arpDirectionMenu.setVisible(true);
    processor.presets[processor.currentPreset]->generatorType = generatorMenu.getText();
    
    buttonClicked(&generateButton);
}

void PianoRoll1AudioProcessorEditor::arpDirectionMenuChanged(){
    //buttonClicked(&generateButton);
    processor.presets[processor.currentPreset]->arpType = arpDirectionMenu.getText();
    buttonClicked(&generateButton);
}

void PianoRoll1AudioProcessorEditor::buttonClicked(Button*){
    currentPreset = processor.currentPreset;
    String generatorType = generatorMenu.getText();
    int currentOctaveShift = processor.presets[currentPreset]->tracks[currentTrack]->octaveShift;
    if(generatorType == "random"){
        for(int sixteenth=0;sixteenth<processor.presets[currentPreset]->numOfBeats * 4;sixteenth++){
            if (random.nextInt(100) > 60 || //40 percent chance of a note.
                processor.presets[currentPreset]->tracks[processor.currentTrack]->sixteenths[sixteenth] > 0
                ){
                int pitchClass = processor.scale[random.nextInt(processor.scale.size())];
                int octave = 12 * (4 + random.nextInt(2) + currentOctaveShift);
                processor.presets[currentPreset]->tracks[processor.currentTrack]->sixteenths.set(sixteenth, pitchClass+octave);
            }
        }
    }else if(generatorType == "arp16th" || generatorType == "arp8th"){
        Array<int> currentScale = theory.modeMap[processor.presets[currentPreset]->currentMode];
        //pianoRoll.stuff = (String) currentScale[2];
        int scaleSize = currentScale.size();
        int root = processor.presets[currentPreset]->root;
        int arpOctave = 4 + currentOctaveShift; //How many extra octaves before arpeggio
        int rhythmDiv;
            if(generatorType == "arp16th"){rhythmDiv=4;}
            else if(generatorType == "arp8th"){rhythmDiv=2;}
            else{rhythmDiv=4;}
        
        for(int sixteenth=0;sixteenth<(processor.presets[currentPreset]->numOfBeats) * rhythmDiv;sixteenth++){;
            int note;
            note = currentScale[sixteenth%scaleSize] + root + (arpOctave*12);

            processor.presets[currentPreset]->tracks[processor.currentTrack]->sixteenths.set(sixteenth * (4/rhythmDiv), note);
            if(generatorType == "arp8th"){
                processor.presets[currentPreset]->tracks[processor.currentTrack]->sixteenths.set(sixteenth * (4/rhythmDiv)+1, 0);
            }
        }
    }else if(generatorType == "arpTriplet"){
        Array<int> currentScale = theory.modeMap[processor.presets[currentPreset]->currentMode];
        pianoRoll.stuff = (String) currentScale[2];
        int root = processor.presets[currentPreset]->root;
        int arpOctave = 4 + currentOctaveShift; //How many extra octaves before arpeggio
        
        for(int triplet=0;triplet<currentNumOfBeats*3;triplet++){;
            int note = currentScale[triplet%currentScale.size()] + root + (arpOctave*12);
            processor.presets[currentPreset]->tracks[processor.currentTrack]->triplets.set(triplet, note);
        }
        for(int beat=0;beat<processor.presets[currentPreset]->numOfBeats;beat++){
            processor.presets[currentPreset]->tracks[currentTrack]->beatSwitch.set(beat, 1);
        }
        repaint();
    }else if(generatorType == "arp16th Broken"){
        Array<int> currentScale = theory.modeMap[processor.presets[currentPreset]->currentMode];
        std::vector<int> shuffledScale = brokenArpeggio(currentScale);
        auto scaleSize = shuffledScale.size();
        
        for(int sixteenth=0;sixteenth<currentNumOfBeats*4;sixteenth++){;
            int note = shuffledScale[sixteenth%scaleSize];
            processor.presets[currentPreset]->tracks[processor.currentTrack]->sixteenths.set(sixteenth, note);
        }
        for(int beat=0;beat<processor.presets[currentPreset]->numOfBeats;beat++){
            processor.presets[currentPreset]->tracks[currentTrack]->beatSwitch.set(beat, 0);
        }
    }else if(generatorType == "arp8th Broken"){
        Array<int> currentScale = theory.modeMap[processor.presets[currentPreset]->currentMode];
        std::vector<int> shuffledScale = brokenArpeggio(currentScale);
        auto scaleSize = shuffledScale.size();
        
        for(int eighth=0;eighth<currentNumOfBeats*2;eighth++){;
            int note = shuffledScale[eighth%scaleSize];
            processor.presets[currentPreset]->tracks[processor.currentTrack]->sixteenths.set(eighth*2, note);
            processor.presets[currentPreset]->tracks[processor.currentTrack]->sixteenths.set(eighth*2+1, 0);
        }
        for(int beat=0;beat<processor.presets[currentPreset]->numOfBeats;beat++){
            processor.presets[currentPreset]->tracks[currentTrack]->beatSwitch.set(beat, 0);
        }
    }else if(generatorType == "arpTriplet Broken"){
        Array<int> currentScale = theory.modeMap[processor.presets[currentPreset]->currentMode];
        std::vector<int> shuffledScale = brokenArpeggio(currentScale);
        auto scaleSize = shuffledScale.size();
        
        for(int triplet=0;triplet<currentNumOfBeats*3;triplet++){;
            int note = shuffledScale[triplet%scaleSize];
            processor.presets[currentPreset]->tracks[processor.currentTrack]->triplets.set(triplet, note);
        }
        for(int beat=0;beat<processor.presets[currentPreset]->numOfBeats;beat++){
            processor.presets[currentPreset]->tracks[currentTrack]->beatSwitch.set(beat, 1);
        }
    }
    
    repaint();
    pianoRoll.repaint();
}

std::vector<int> PianoRoll1AudioProcessorEditor::brokenArpeggio(Array<int> currentScale){
    int scaleSize = currentScale.size();
    int root = processor.presets[currentPreset]->root;
    int currentOctaveShift = processor.presets[currentPreset]->tracks[currentTrack]->octaveShift;
    int arpOctave = random.nextInt(2)+3 + currentOctaveShift; //How many extra octaves before arpeggio
    String arpType = processor.presets[currentPreset]->arpType;
    
    std::vector<int> order;
    std::vector<int> shuffledScale;
    for(int i=0;i<scaleSize;i++){order.push_back(i);} //Fills "order" with values 0->scaleSize
    
    //Random Shuffle
    if (arpType == "ascend" || arpType == "descend"){
        auto rng = std::default_random_engine {}; //Setup randomizer.
        auto numOfShuffles = random.nextInt(14); //Random number of shuffles.
        
        do{
            for (int i=0;i<numOfShuffles;i++){
                std::shuffle(std::begin(order), std::end(order), rng); //Shuffle the order of notes.
            }
        }while(order == previousOrder); //Always change to a different order.
    }else if(arpType == "seq1"){
        //order.push_back({scaleSize+1});
        //currentScale.add(currentScale[0]+12); //Add octave note
        //currentScale.add(currentScale[1]+12); //Add ninth
        
        for(int i=0;i<order.size();i++){
            int indexOffset = 0;
            if(i % 2 == 0 && i != 0){ //If even number other than 0.
                order.insert(order.begin() + i-1 + indexOffset, order[i+indexOffset]);
                indexOffset++;
            }
        }
    }else if(arpType == "seq2"){
        order.push_back({scaleSize});
        order.push_back({scaleSize+1});
        currentScale.add(currentScale[0]+12); //Add octave note
        currentScale.add(currentScale[1]+12); //Add ninth
        
        for(int i=0;i<order.size();i++){
            int indexOffset = 0;
            if(i % 2 == 0 && i != 0){ //If even number other than 0.
                order.insert(order.begin() + i-1 + indexOffset, order[i+indexOffset]);
                indexOffset++;
            }
        }
        order.pop_back(); //Remove last element.
    }
    else if(arpType == "seq3"){
        order.push_back({scaleSize});
        order.push_back({scaleSize+1});
        currentScale.add(currentScale[0]+12); //Add octave note
        currentScale.add(currentScale[1]+12); //Add ninth
        
        std::vector<int> newOrder;
        
        for(int i=0;i<order.size()-2;i++){
            newOrder.push_back({order[i]});
            newOrder.push_back({order[i+1]});
            newOrder.push_back({order[i+2]});
        }
        order = newOrder;
    }
    
    
    for(int i=0;i<order.size();i++){
        int val = currentScale[order[i]]; //Determine pitch.
        shuffledScale.push_back(val + root + (arpOctave*12)); //Fill new shuffled scale with pitch.
        
        if(i>0){
            if(arpType == "ascend"){
                while(shuffledScale[i]<shuffledScale[i-1]){
                    shuffledScale[i] += 12;
                }
            }else if(arpType == "descend"){
                while(shuffledScale[i]>shuffledScale[i-1]){
                    shuffledScale[i] -= 12;
                }
                int octaveDisplacement = (shuffledScale.size() / 4) + 1;
                
                for (int i=0;i<shuffledScale.size();i++){
                    shuffledScale[i] += 12*octaveDisplacement;
                }
            }
        }
    }
    previousOrder = order;
    return shuffledScale;
}

