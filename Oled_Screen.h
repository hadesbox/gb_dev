

#ifndef Oled_Screen_h
#define Oled_Screen_h
#include <Arduino.h> 


class Oled_Screen : public Adafruit_SH1106
{ // Down here where the damned thing belongs
public: 
    bool tempoState;
    Oled_Screen(byte oled_mosi, byte oled_clk, byte oled_dc, byte oled_cs, byte oled_reset);
    void init(); 
    void fail(); 
    void drawTextSquare(byte xpos, byte ypos, byte w, byte h, String title, String text);
    void drawTextSquareInverted(byte xpos, byte ypos, byte w, byte h, String title, String text);
    void drawParameter(byte xpos, byte ypos, byte w, byte h, String title, String text);
    void drawParameterH(byte xpos, byte ypos, byte w, byte h, String title, String text);
    void drawLFO(byte xpos, byte ypos, byte w, byte h, String title, String text);
    void drawStyle(byte xpos, byte ypos, byte w, byte h, String text);
    void drawStyleEdit(byte xpos, byte ypos, byte w, byte h, String text);
    void drawParameterIcon(byte xpos, byte ypos,  byte icon);
    void drawParameterInverted(byte xpos, byte ypos, byte w, byte h, String title, String text);
    void fillBlank(byte xpos, byte ypos, byte w, byte h);
    void drawPixelTempo(byte tickC);
    void drawSector(byte sector);
    
    void drawSnapshot(byte snp);
    void clear();
    void drawOneStep(byte step, byte prob, byte y);
    void drawOneStepEdit(byte step, byte prob, byte y);
    void drawOneStepEditB(byte step, byte prob, byte y);
    void drawAxis(int val, int offset, byte xpos, byte ypos);
    
private:  
    // typedef enum {INTERNAL, MIDI} clock_type; 
    // struct  
    // {   
    //     clock_type clockMode;  
    //     float tempo; 

    //     int globalDivision;
    // }configuration; 

    // Adafruit_SSD1306 disp;
    
};

#endif