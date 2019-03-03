/*
  ==============================================================================

    Theory.h
    Created: 18 Jan 2019 1:13:06pm
    Author:  Adam Shield

  ==============================================================================
*/


#ifndef MUSIC_THEORY_HEADER
#define MUSIC_THEORY_HEADER
#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include <map>
#include <iostream>

namespace Theory{
    
    struct Mode{
        Array<int> mode;
        Array<int> enharmIndex;
        Array<int> intervals;
        Mode(const Array<int> Array1, const Array<int> Array2, const Array<int> Array3){
            mode = Array1;
            enharmIndex = Array2;
            intervals = Array3;
        }
        Mode(){}
        
        Array<int> getMode(){ return mode; }
        Array<int> getEnharmIndex(){ return enharmIndex; }
        Array<int> getIntervals(){ return intervals; }
    };
    
    
    struct Scale : public Mode{
        Scale(const Array<int> Array1, const Array<int> Array2, const Array<int> Array3) : Mode(Array1, Array2, Array3)
        {
        }
    };
    
    struct Chord : public Mode{
        Chord(const Array<int> Array1, const Array<int> Array2, const Array<int> Array3) : Mode(Array1, Array2, Array3)
        {
        }
    };
    
    /*
     * Scales are built using Arrays of
     *      1. Their pitch classes.
     *      2. Their "enharmonic index" (i.e. which note deviates from the major scale)
     *      3. Their intervals (which degrees of the diatonic scale do they draw from)
     *
     */
    namespace Scales{
        /*
        inline Array<int>   major =      {0,2,4,5,7,9,11},
                            natMinor =   {0,2,3,5,7,8,10},
                            harmMinor =  {0,2,3,5,7,8,11},
                            melMinor =   {0,2,3,5,7,9,11},
                            locrian =    {0,1,3,5,6,8,1},
                            dorian =     {0,2,3,5,7,8,10},
                            phrygian =   {0,1,3,5,7,8,10},
                            lydian =     {0,2,4,6,7,9,11},
                            mixolydian = {0,2,4,5,7,9,10},
                            wholeTone =  {0,2,4,6,8,10},
                            pentaMaj =   {0,2,4,7,9},
                            pentaMin =   {0,3,5,7,10},
                            pentaMajB =  {0,2,3,4,7,9},
                            pentaMinB =  {0,3,5,6,7,10},
                            dimWholeHalf={0,2,3,5,6,8,9,11},
                            dimHalfWhole={0,1,3,4,6,7,9,10},
                            hungarMinor= {0,2,3,6,7,8,11},
                            phrygDom =   {0,1,4,5,7,8,10},
                            lydDom =     {0,2,4,6,7,9,10},
                            yo =         {0,2,5,7,9},
                            insen =      {0,1,5,7,10},
                            bebopDom =   {0,2,4,5,7,9,10,11},
                            bebopMaj =   {0,2,4,5,7,8,9,11};
        */
        
        //TODO
        
                                       //---mode-----------------enharmIndex-------intervals-------//
        inline Scale        major =      { {0,2,4,5,7,9,11},    {0,0,0,0,0,0,0},  {1,2,3,4,5,6,7} },
                            natMinor =   { {0,2,3,5,7,8,10},    {0,0,2,0,0,2,2},  {1,2,3,4,5,6,7} },
                            harmMinor =  { {0,2,3,5,7,8,11},    {0,0,2,0,0,2,0},  {1,2,3,4,5,6,7} },
                            melMinor =   { {0,2,3,5,7,9,11},    {0,0,2,0,0,0,0},  {1,2,3,4,5,6,7} },
                            locrian =    { {0,1,3,5,6,8,1},     {0,2,2,0,2,2,2},  {1,2,3,4,5,6,7} },
                            dorian =     { {0,2,3,5,7,8,10},    {0,2,2,0,0,2,2},  {1,2,3,4,5,6,7} },
                            phrygian =   { {0,1,3,5,7,8,10},    {0,2,2,0,0,2,2},  {1,2,3,4,5,6,7} },
                            lydian =     { {0,2,4,6,7,9,11},    {0,0,0,1,0,0,0},  {1,2,3,4,5,6,7} },
                            mixolydian = { {0,2,4,5,7,9,10},    {0,2,2,0,2,2,2},  {1,2,3,4,5,6,7} },
                            wholeTone =  { {0,2,4,6,8,10},      {0,0,0,1,1,1},    {1,2,3,4,5,6} },
                            pentaMaj =   { {0,2,4,7,9},         {0,0,0,0,0},      {1,2,3,5,6} },
                            pentaMin =   { {0,3,5,7,10},        {0,2,0,0,2},      {1,3,4,5,7} },
                            pentaMajB =  { {0,2,3,4,7,9},       {0,0,2,0,0,0},    {1,2,3,3,5,6} },
                            pentaMinB =  { {0,3,5,6,7,10},      {0,2,0,2,0,2},    {1,3,4,5,5,7} },
                            dimWholeHalf={ {0,2,3,5,6,8,9,11},  {0,0,2,0,2,2,0,0},{1,2,3,4,5,6,6,7} },
                            dimHalfWhole={ {0,1,3,4,6,7,9,10},  {0,2,2,2,2,0,0,2},{1,2,3,4,5,5,6,7} },
                            phrygDom =   { {0,1,4,5,7,8,10},    {0,2,0,0,0,2,2},  {1,2,3,4,5,6,7} },
                            lydDom =     { {0,2,4,6,7,9,10},    {0,0,0,1,0,0,2},  {1,2,3,4,5,6,7} },
                            yo =         { {0,2,5,7,9},         {0,0,0,0,2},      {1,2,4,5,6} },
                            insen =      { {0,1,5,7,10},        {0,2,0,0,2},      {1,2,4,5,7} },
                            hungarMinor= { {0,2,3,6,7,8,11},    {0,0,2,1,0,2,0},  {1,2,3,4,5,6,7} },
                            bebopDom =   { {0,2,4,5,7,9,10,11}, {0,0,0,0,0,0,2,0},{1,2,3,4,5,6,7,7} },
                            bebopMaj =   { {0,2,4,5,7,8,9,11},  {0,0,0,0,0,1,0,0},{1,2,3,4,5,5,6,7} };
        
         
        
    };
    
    
    namespace Chords{
        /*
        inline Array<int>   majChord =       {0,4,7},
                            minChord =       {0,3,7},
                            augChord =       {0,4,8},
                            dimChord =       {0,3,6},
                            seventhChord =   {0,4,7,10},
                            min7Chord =      {0,3,7,10},
                            min7b5Chord =    {0,3,6,10},
                            dim7Chord =      {0,3,6,9},
                            maj7Chord =      {0,4,7,11},
                            minMaj7Chord =   {0,3,7,11},
                            ninthChord =     {0,2,4,7,10},
                            min9Chord =      {0,2,3,7,10},
                            min7b9Chord =    {0,1,3,7,10},
                            maj9Chord =      {0,2,4,7,11},
                            add9Chord =      {0,2,4,7},
                            minAdd9Chord =   {0,2,3,7},
                            sevenSharp9Chord={0,3,4,7,10},
                            sus2Chord =      {0,2,7},
                            sus4Chord =      {0,5,7},
                            powerChord =     {0,7},
                            sixthChord =     {0,4,7,9},
                            minSixthChord =  {0,3,7,8},
                            sixNineChord =   {0,2,4,7,9},
                            thirteenthChord= {0,4,7,9,10},
                            min13thChord =   {0,3,7,8,10},
                            maj13thChord =   {0,4,7,9,11},
                            eleventhChord =  {0,4,5,7,10},
                            sharp11Chord =   {0,4,6,7,10},
                            minSharp11Chord= {0,3,6,7,10},
                            min7Flat5Flat9Chord={0,1,3,10},
                            aug7thChord =    {0,4,8,10},
                            petrushka =      {0,1,4,6,7,10},
                            farben =         {0,4,8,9,11};
         */
        
        inline Chord    majChord =          { {0,4,7},      {0,0,0},        {1,3,5} },
                        minChord =          { {0,3,7},      {0,1,0},        {1,3,5} },
                        augChord =          { {0,4,8},      {0,0,2},        {1,3,5} },
                        dimChord =          { {0,3,6},      {0,1,1},        {1,3,5} },
                        seventhChord =      { {0,4,7,10},   {0,0,0,2},      {1,3,5,7} },
                        min7Chord =         { {0,3,7,10},   {0,2,0,2},      {1,3,5,7} },
                        min7b5Chord =       { {0,3,6,10},   {0,2,2,2},      {1,3,5,7} },
                        dim7Chord =         { {0,3,6,9},    {0,2,2,4},      {1,3,5,7} },
                        maj7Chord =         { {0,4,7,11},   {0,0,0},        {1,3,5,7} },
                        minMaj7Chord =      { {0,3,7,11},   {0,2,0,0},      {1,3,5,7} },
                        ninthChord =        { {0,2,4,7,10}, {0,0,0,2,0},    {1,3,5,7,2} },
                        min9Chord =         { {0,2,3,7,10}, {0,2,0,2,0},    {1,3,5,7,2} },
                        min7b9Chord=        { {0,1,3,7,10}, {0,2,0,2,2},    {1,3,5,7,2} },
                        maj9Chord =         { {0,2,4,7,11}, {0,0,0,0,0},    {1,3,5,7,2} },
                        add9Chord =         { {0,2,4,7},    {0,0,0,0},      {1,3,5,} },
                        minAdd9Chord =      { {0,2,3,7},    {0,2,0,0},      {1,3,5,} },
                        sevenSharp9Chord=   { {0,3,4,7,10}, {0,0,0,2,1},    {1,3,5,7,} },
                        min7Flat5Flat9Chord={ {0,1,3,6,10}, {0,2,2,2,2},    {1,3,5,7,} },
                        sus2Chord =         { {0,2,7},      {0,0,0},        {1,2,} },
                        sus4Chord =         { {0,5,7},      {0,0,0},        {1,4,} },
                        powerChord =        { {0,7},        {0,0},          {1,5} },
                        sixthChord =        { {0,4,7,9},    {0,0,0,0},      {1,3,5,6} },
                        minSixthChord =     { {0,3,7,8},    {0,0,0,2},      {1,3,5,6} },
                        sixNineChord =      { {0,2,4,7,9},  {0,0,0,0,0},    {1,3,5,6,2} },
                        eleventhChord =     { {0,4,5,7,10}, {0,0,0,2,0},    {1,3,5,7,4} },
                        sharp11Chord =      { {0,4,6,7,10}, {0,0,0,2,1},    {1,3,5,7,4} },
                        minSharp11Chord =   { {0,3,6,7,10}, {0,2,0,2,1},    {1,3,5,7,4} },
                        thirteenthChord =   { {0,4,7,9,10}, {0,0,0,2,0},    {1,3,5,7,6} },
                        min13thChord =      { {0,3,7,8,10}, {0,2,0,2,2},    {1,3,5,7,6} },
                        maj13thChord =      { {0,4,7,9,11}, {0,0,0,0,0},    {1,3,5,7,6} },
                        aug7thChord =       { {0,4,8,10},   {0,0,1,0},      {1,3,5,7} },
                        petrushka=          {{0,1,4,6,7,10},{0,0,0,1,1,1},  {1,3,5,4,6,} },
                        farben =            { {0,4,8,9,11}, {0,1,0,0,0},    {1,5,7,3,6} };
         
    };
    
    
    
    const String setClassToPitchName[12] = {"C","C#/Db","D","D#/Eb","E","F","F#/Gb","G","G#/Ab","A","A#/Bb", "B"};
    
    

    inline std::map<String, Mode> modeMap = {
        //Scales
        {"Major", Scales::major},
        {"Natural Minor", Scales::natMinor},
        {"Harmonic Minor", Scales::harmMinor},
        {"Melodic Minor", Scales::melMinor},
        {"Locrian", Scales::locrian},
        {"Dorian", Scales::dorian},
        {"Phrygian", Scales::phrygian},
        {"Lydian", Scales::lydian},
        {"Mixolydian", Scales::mixolydian},
        {"WholeTone", Scales::wholeTone},
        {"Pentatonic Major", Scales::pentaMaj},
        {"Pentatonic Minor", Scales::pentaMin},
        {"Pentatonic Maj Blues", Scales::pentaMajB},
        {"Pentatonic Min Blues", Scales::pentaMinB},
        {"Diminished Whole-Half", Scales::dimWholeHalf},
        {"Diminished Half-Whole", Scales::dimHalfWhole},
        {"Hangarian Minor", Scales::hungarMinor},
        {"Phrygian Dominant", Scales::phrygDom},
        {"Lydian Dominant",Scales::lydDom},
        {"Yo (Japanese)", Scales::yo},
        {"Insen (Japanese)", Scales::insen},
        {"Bebop Dominant", Scales::bebopDom},
        {"Bebop Major", Scales::bebopMaj},
        //Chords
        {"Maj (Chord)", Chords::majChord},
        {"min (Chord)", Chords::minChord},
        {"Aug (Chord)", Chords::augChord},
        {"dim (Chord)", Chords::dimChord},
        {"7th (Chord)", Chords::seventhChord},
        {"min7 (Chord)", Chords::min7Chord},
        {"m7b5 (Chord)", Chords::min7b5Chord},
        {"dim7 (Chord)", Chords::dim7Chord},
        {"Maj7 (Chord)", Chords::maj7Chord},
        {"minMaj7 (Chord)", Chords::minMaj7Chord},
        {"9th (Chord)", Chords::ninthChord},
        {"m9 (Chord)", Chords::min9Chord},
        {"m7b9 (Chord)", Chords::min7b9Chord},
        {"Maj9 (Chord)", Chords::maj9Chord},
        {"add9 (Chord)", Chords::add9Chord},
        {"minAdd9 (Chord)", Chords::minAdd9Chord},
        {"7#9 (Chord)", Chords::sevenSharp9Chord},
        {"sus2 (Chord)", Chords::sus2Chord},
        {"sus4 (Chord)", Chords::sus4Chord},
        {"Power Chord", Chords::powerChord},
        {"6th (Chord)", Chords::sixthChord},
        {"m6 (Chord)", Chords::minSixthChord},
        {"6/9 (Chord)", Chords::sixNineChord},
        {"13th (Chord)", Chords::thirteenthChord},
        {"m13 (Chord)", Chords::min13thChord},
        {"Maj13 (Chord)", Chords::maj13thChord},
        {"11th (Chord)", Chords::eleventhChord},
        {"#11 (Chord)", Chords::sharp11Chord},
        {"m#11 (Chord)", Chords::minSharp11Chord},
        {"m7b5b9 (Chord)", Chords::min7Flat5Flat9Chord},
        {"aug7 (Chord)", Chords::aug7thChord},
        {"Petrushka (Chord)", Chords::petrushka},
        {"Farben (Chord)", Chords::farben}
         

    }; //TODO, change everything to scales

    
    const std::map<int, Array<String>> diatonicNoteNames = {
        {0,{"C♭♭","C♭","C", "C♯","Cx"}},
        {1,{"D♭♭","D♭","D","D♯","Dx"}},
        {2,{"E♭♭","E♭","E", "E♯","Ex"}},
        {3,{"F♭♭","F♭","F", "F♯","Fx"}},
        {4,{"G♭♭","G♭","G", "G♯","Gx"}},
        {5,{"A♭♭","A♭","A", "A♯","Ax"}},
        {6,{"B♭♭","B♭","B", "B♯","Bx"}}
    };

        
    const std::map<int, Array<int>> circleOfFifths = {
    
        {0,{0,0,0,0,0,0,0}}, //C
        {1,{1,1,1,1,1,1,1}}, //C#
        {2,{1,0,0,1,0,0,0}}, //D
        {3,{2,1,1,2,1,1,1}}, //D#
        {4,{1,1,0,1,1,0,0}}, //E
        {5,{0,0,0,0,0,0,-1}}, //F
        {6,{1,1,1,1,1,1,0}}, //F#
        {7,{0,0,0,1,0,0,0}}, //G
        {8,{1,1,1,2,1,1,1}}, //G#
        {9,{1,0,0,1,1,0,0}}, //A
        {10,{2,1,1,2,2,1,1}}, //A#
        {11,{1,1,0,1,1,1,0}}, //B
        {11,{0,-1,-1,0,0,-1,-1}}, //Db
        {11,{0,0,-1,0,0,-1,-1}}, //Eb
        {11,{-1,-1,-1,0,-1,-1,-1}}, //Gb
        {11,{0,-1,-1,0,0,-1,-1}}, //Ab
        {11,{0,0,-1,0,0,0,-1}} //Bb
    };
    
    inline std::map<int, int> setClassToDiatonic{
        {0,0},
        {1,0},
        {2,1},
        {3,1},
        {4,2},
        {5,3},
        {6,3},
        {7,4},
        {8,4},
        {9,5},
        {10,5},
        {11,6}
    };
    
};



enum Clef{
    TREBLE,
    BASS,
    TREBLE_8VA,
    TREBLE_15MA
};


enum Accidental{
    SHARP,
    FLAT,
    DOUBLE_SHARP,
    DOUBLE_FLAT,
    NO_PREFERENCE
};


struct NoteHead{
    uint8 notePitch;
    Accidental noteAccidental;
    
    NoteHead(uint8 pitch, Accidental accidental){
        notePitch = pitch;
        noteAccidental = accidental;
    }
    NoteHead(uint8 pitch){ //Overloaded
        NoteHead(pitch, Accidental::NO_PREFERENCE);
    }
    
    uint8 getNotePitch(){return notePitch;}
    Accidental getNoteAccidental(){return noteAccidental;}
};

/*
static const Font& getOpus()
{
    static Font opus (Font (Typeface::createSystemTypefaceFor (BinaryData::OpusStd_otf,
                                                               BinaryData::OpusStd_otfSize)));
    return opus;
}
 */
//inline static Font opus = Typeface::createSystemTypefaceFor (BinaryData::OpusStd_otf,
                                                           //BinaryData::OpusStd_otfSize);

class OpusLookAndFeel : public LookAndFeel_V4
{
public:
    Typeface::Ptr getTypefaceForFont(const Font& f) override{
        static Typeface::Ptr myFont = Typeface::createSystemTypefaceFor(BinaryData::OpusStd_otf,
                                                                        BinaryData::OpusStd_otfSize);
        return myFont;
    }
    
    static const Font& getOpus()
    {
        static Font opus (Font (Typeface::createSystemTypefaceFor (BinaryData::OpusStd_otf,
                                                                   BinaryData::OpusStd_otfSize)));
        return opus;
    }
    
    OpusLookAndFeel()
    {
        setDefaultSansSerifTypeface(Typeface::createSystemTypefaceFor(BinaryData::OpusStd_otf,
                                                                      BinaryData::OpusStd_otfSize));
    }
    
    /*
     Typeface::Ptr getTypefaceForFont(const Font& f) override{
     static Typeface::Ptr myFont = Typeface::createSystemTypefaceFor(BinaryData::OpusStd_otf,
     BinaryData::OpusStd_otfSize);
     return myFont;
     }
     */
    //static Typeface::Ptr opus (Font (Typeface::createSystemTypefaceFor (BinaryData::OpusStd_otf,
    //BinaryData::OpusStd_otfSize)));
};



class Staff : public Component{
public:
    Clef clef = TREBLE;
    std::vector<NoteHead> notes;
    OpusLookAndFeel opusLookAndFeel;
     
    Staff(){
        notes.push_back(NoteHead{65});
    }
    
    void paint (Graphics& g) override{
        const float numOfLines = 10.0f;
        const float height = getHeight();
        const float width = getWidth();
        const float lineSpacing = height/numOfLines;
        const float noteSpacing = width / 20.0f;
        const float clefSpacing = height * 0.45;
        const float noteHeight = height*0.1;
        const float noteWidth = noteHeight*1.5f;
        const uint8 bottomNote = [this]()->uint8{
            uint8 returnVal;
            if(clef == TREBLE){
                returnVal = 60;
            }else{
                returnVal = 0;
            }
            return returnVal;
        }();
        
        
        g.setColour(Colours::black);
        for(int line=3; line<9;line++){
            float yPos = line*lineSpacing;
            g.drawLine(0.0f, yPos, width, yPos);
        }
        for(int note=0; note<notes.size();note++){
            uint8 myNotePitch = notes[note].getNotePitch();
            int diatonicPitch = Theory::setClassToDiatonic[myNotePitch%12];
            float yPos = height - ( (lineSpacing/2) * (diatonicPitch+3) );
            float ledgerLineX = clefSpacing - noteWidth/2;
            float ledgerLineY = yPos+(lineSpacing/2);
            
            g.fillEllipse(clefSpacing, yPos, noteWidth, noteHeight);
            
            if(diatonicPitch==0) g.drawLine(ledgerLineX, ledgerLineY, ledgerLineX + noteWidth*2, ledgerLineY);
        }
        

        g.setFont(opusLookAndFeel.getOpus());
        g.setFont(height*0.76);
        g.drawText("&", 0, height*0.11, width, height, Justification::left);
        
    }
    
    
    
private:
    
    
    
};




#endif /* MUSIC_THEORY_HEADER */


