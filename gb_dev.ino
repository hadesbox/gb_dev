#include <ResponsiveAnalogRead.h>
ResponsiveAnalogRead analog(A12, true);
ResponsiveAnalogRead analog2(A13, true);
ResponsiveAnalogRead CV2(A10, true);
ResponsiveAnalogRead CV1(A11, true);

unsigned int  MemTimeSerial;
bool interface;

#define DEBUG
//
// #include <Bounce.h>
//
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

#include <MIDI.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SH1106.h"
// #include <Adafruit_SH1106.h>

#include "Oled_Screen.h"
//MOSI, CLK,DC,RESET,CS
//  mosi,  clk,  dc,  cs,  reset
// Oled_Screen screen(17, 18, 19, 16, 19);
Oled_Screen screen(17, 18, 19, 16, 19);
// Oled_Screen screen(17, 16, 19, 27, 18);

#include "Parameter.h"
// #include "Scales.h"
#include "names.h"
#include "Predefined_styles.h"

#include "Instrument.h"
#include "BeatCutter.h"
#include "Tracks.h"
#include "Encoders.h"

#include "Presets.h"
byte lazy = 0;
byte lazySteps = 0;
byte lazyEdit = 0;
byte sector = 0;
#include "Buttons.h"


//SD CARD
File root;

//OLED
IntervalTimer UI_timer;
#define UI_RATE  20000

//DEBUG
IntervalTimer DEBUG_timer;
#define DEBUG_RATE   10000000
bool debug;



MIDI_Class MIDI;
//CLOCK
volatile bool clkState = LOW;
volatile bool doReset = false;
volatile byte clkOutState = LOW;
long clkCount = 0;
// byte outPins[]={28,31,26,25,21,22,13,24};
byte outPins[] = {25, 21, 22, 26, 13, 28, 24, 27};



//DEBUG
unsigned long debugtime = 1000000 ;
unsigned long previousMillis = 0;
unsigned long previousMillisPlay = 0;

#define BYTES_VAL_T unsigned int



// Parameter tpm[40];
//
// Gender styles[2];
////




unsigned long bars = 0;
unsigned long beats = 0;
unsigned long ticks = 0;

void setup() {
  Serial.begin(115200);
  SPI.setMOSI(7);
  SPI.setSCK(14);
  // fillMem();


  //CLOCK IN
  NVIC_SET_PRIORITY(IRQ_PORTB, 3); // TR1 = 0 = PTB16
  pinMode(23, INPUT);//CLOCK
  pinMode(31, INPUT);//REset
  //BUTTONS
  pinMode(PLOAD_PIN , OUTPUT);
  pinMode(CE_PIN , OUTPUT);
  pinMode(CLK_PIN , OUTPUT);
  pinMode(DATA_PIN , INPUT);
  pinMode(10, OUTPUT);

  for (int i = 0; i < 9; ++i)
  {
    pinMode(outPins[i], OUTPUT);
  }
  //CLOCK
  for (int i = 0; i < 7; ++i)
  {
    tracks[i]->parameters[7]->modValue = tracks[i]->parameters[7]->value = i + 24;

    // tracks[i]->part_data.channel = 10;
  }
  attachInterrupt(23, blink, FALLING);
  attachInterrupt(31, analogReset, FALLING);

  //
  
  Serial.print("Initializing SD card...");

  screen.init();

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");

    screen.fail();
    return;
  }
  Serial.println("initialization done.");
  readSDStartup();
  loadSDPresets();
  loadSDSnapshots();
  loadSDStyles();
  
  
  initClock();
  MidiSetup();
  initTracks();
  initCutter();

  UI_timer.begin(UI_timerCallback, UI_RATE);
  DEBUG_timer.begin(DEBUG_timerCallback, DEBUG_RATE);

  Serial.println("rfl = " + String(freeRam()));

}

bool editBlink = 0;

void loop()
{
  // delay(100);
  analog.update();
  analog2.update();
  CV1.update();
  CV2.update();
  MidiLoop();
  playSwingNotes();
  buttons();
  clocksKill();
  analogClock();
  if (doReset) {
    HandleStart();
    doReset = false;
  }

  debugIt();
  if (XmapIn != oldXmapIn)
  {
    oldXmapIn = XmapIn;
    guiItemsOn(9);
    guiItemsOn(6);
  }
  if (YmapIn != oldYmapIn)
  {
    oldYmapIn = YmapIn;
    guiItemsOn(9);
    guiItemsOn(6);
  }
  if (interface) {
    if (drawSteps || prevStyle != currentStyle) {
      lazySteps = 0;
      drawSteps = 0;
      prevStyle = currentStyle;
    }
    
    if (mode == PLAY)
    {

     
      if (guiItemsOff(9)) screen.drawAxis(analog.getValue(), analog2.getValue(), 25, 0 );
      if (guiItemsOff(6)) {
        screen.drawParameterH(25, 10, 80, 19, tracks[currentTrack]->parameters[currentEdit]->modValue, tracks[currentTrack]->parameters[currentEdit]->getName());
      }
      if (guiItemsOff(12))
      {

        if (tracks[currentTrack]->isPlaying ) {
          screen.drawParameterIcon(0, 0, currentTrack);
        } else {
          screen.drawParameterIcon(0, 0, currentTrack);
          screen.drawParameterIcon(0, 4, 7);
        }
      }
      if (guiItemsOff(lazy % 5)) {
        screen.drawTextSquare(26 * (lazy % 5), 40 , 24, 9, tracks[currentTrack]->parameters[(lazy % 5)]->getShortName(), String(tracks[currentTrack]->parameters[(lazy % 5)]->modValue));
     
      }
      
      if (guiItemsOff(8)) {
        screen.drawStyle(0, 48, 128, 11, memoryS[currentTrack]->name);


      }

      if (guiItemsOff(7)) {

        screen.drawOneStep(lazySteps, memoryS[currentTrack]->weights[0][lazySteps], 59);


      }
      if (lazySteps < 33) {
        guiItemsOn(7);

      } else {
        lazySteps = 40;
      }

    } else if (mode == LFO) {
      byte wav = tracks[currentTrack]->parameters[currentLFO]->lfo.wave;
      if (guiItemsOff(12))
      {

        if (tracks[currentTrack]->isPlaying ) {
          screen.drawParameterIcon(0, 0, currentTrack);
          screen.drawParameterIcon(9, 4, 13);


        } else {
          screen.drawParameterIcon(0, 0, currentTrack);
          screen.drawParameterIcon(0, 4, 7);
          screen.drawParameterIcon(9, 4, 13);


        }
      }
      if (guiItemsOff(6) ) {

        if (currentEdit != 0)
        {
          screen.drawParameterH(25, 10, 128, 19, *tracks[currentTrack]->parameters[currentLFO]->lfoOptions[currentEdit], tracks[currentTrack]->parameters[currentLFO]->lfo.names[currentEdit] );
        } else {
          byte waveN = *tracks[currentTrack]->parameters[currentLFO]->lfoOptions[currentEdit];
          screen.drawParameterH(25, 10, 128, 19, tracks[currentTrack]->parameters[currentLFO]->lfo.optionsShort[waveN], tracks[currentTrack]->parameters[currentLFO]->lfo.names[currentEdit] );

        }
      }
      if (guiItemsOff(6) == 0)screen.drawLFO(25, 0, 128, 10, tracks[currentTrack]->parameters[currentLFO]->modValue, tracks[currentTrack]->parameters[currentLFO]->getLFO() );

      byte tmpParam[] = {
        tracks[currentTrack]->parameters[currentLFO]->lfo.wave,
        tracks[currentTrack]->parameters[currentLFO]->lfo.division,
        tracks[currentTrack]->parameters[currentLFO]->lfo.amp,
        tracks[currentTrack]->parameters[currentLFO]->lfo.dc,
        tracks[currentTrack]->parameters[currentLFO]->lfo.pwm_option,
      };

      if (guiItemsOff(lazy % 5) )screen.drawTextSquare(26 * (lazy % 5), 40, 24, 9, tracks[currentTrack]->parameters[currentLFO]->lfo.names[lazy % 5], String(tmpParam[lazy % 5]));


    } else if (mode == LFOTRACK) {
      byte wav = tracks[currentTrack]->parameters[currentLFO]->lfo.wave;
      if (guiItemsOff(6) ) {

        if (currentEdit != 0)
        {
          screen.drawParameterH(25, 10, 128, 19, *tracks[currentTrack]->parameters[currentLFO]->lfoOptions[currentEdit], tracks[currentTrack]->parameters[currentLFO]->lfo.names[currentEdit] );
        } else {
          byte waveN = *tracks[currentTrack]->parameters[currentLFO]->lfoOptions[currentEdit];
          screen.drawParameterH(25, 10, 128, 19, tracks[currentTrack]->parameters[currentLFO]->lfo.optionsShort[waveN], tracks[currentTrack]->parameters[currentLFO]->lfo.names[currentEdit] );

        }
      }
      if (guiItemsOff(12))
      {

        if (tracks[currentTrack]->isPlaying ) {
          screen.drawParameterIcon(0, 0, currentTrack);
          screen.drawParameterIcon(0, 12, 14);

          Serial.println("con");

        } else {
          screen.drawParameterIcon(0, 0, currentTrack);
          screen.drawParameterIcon(0, 12, 14);

          screen.drawParameterIcon(0, 4, 7);
          Serial.println("xcon");


        }
      }
      if (guiItemsOff(6) == 0)screen.drawLFO(25, 0, 128, 10, tracks[currentTrack]->parameters[currentLFO]->modValue, tracks[currentTrack]->parameters[currentLFO]->getLFO() );

      byte tmpParam[] = {
        tracks[currentTrack]->parameters[currentLFO]->lfo.wave,
        tracks[currentTrack]->parameters[currentLFO]->lfo.division,
        tracks[currentTrack]->parameters[currentLFO]->lfo.amp,
        tracks[currentTrack]->parameters[currentLFO]->lfo.dc,
        tracks[currentTrack]->parameters[currentLFO]->lfo.pwm_option,
      };
      if (guiItemsOff(lazy % 5) )screen.drawTextSquare(26 * (lazy % 5), 40, 24, 9, tracks[currentTrack]->parameters[currentLFO]->lfo.names[lazy % 5], String(tmpParam[lazy % 5]));


    } else if (mode == FILL) {
      if (guiItemsOff(9)) screen.drawAxis(analog.getValue(), analog2.getValue(), 25, 0 );

      if (guiItemsOff(7))screen.drawParameterIcon(0, 0, 10);
      if (guiItemsOff(6))screen.drawParameterH(25, 10, 128, 19, fillParameters[currentEdit].modValue,  fillParameters[currentEdit].name);
      if (guiItemsOff(lazy % 5))screen.drawTextSquare(26 * (lazy % 5), 40, 24, 9, fillParameters[lazy % 5].shortName, String(fillParameters[lazy % 5].modValue));


    } else if (mode == TRACK) {
      if (guiItemsOff(9)) screen.drawAxis(analog.getValue(), analog2.getValue(), 25, 0 );

      if (guiItemsOff(6) == 0)screen.drawParameterH(25, 10, 80, 19, tracks[currentTrack]->parameters[currentEdit + 5]->modValue, tracks[currentTrack]->parameters[currentEdit + 5]->getName());


      if (guiItemsOff(12))
      {

        if (tracks[currentTrack]->isPlaying ) {
          screen.drawParameterIcon(0, 0, currentTrack);
          screen.drawParameterIcon(0, 12, 14);

          Serial.println("con");

        } else {
          screen.drawParameterIcon(0, 0, currentTrack);
          screen.drawParameterIcon(0, 12, 14);

          screen.drawParameterIcon(0, 4, 7);
          Serial.println("xcon");


        }
      }
      byte tmpParamt[] = {
        tracks[currentTrack]->parameters[5]->modValue,
        tracks[currentTrack]->parameters[6]->modValue,
        tracks[currentTrack]->parameters[7]->modValue,
        tracks[currentTrack]->parameters[8]->modValue,
        tracks[currentTrack]->parameters[9]->modValue,
      };
      char tmpName[5][5] = {"MULT", "STEP", "NOTE", "CHAN", "ALT"};

      if (guiItemsOff(lazy % 5) )screen.drawTextSquare(26 * (lazy % 5), 40, 24, 9, tmpName[lazy % 5], String(tmpParamt[lazy % 5]));

      if (guiItemsOff(6)) {
      }


    } else if (mode == SNAPSHOT) {
      if (guiItemsOff(6)) {
        screen.drawParameterIcon(0, 0, 8);

      };
      guiItemsOn(6);

      if (guiItemsOff(6))screen.drawParameter(25, 0, 65, 28, playingSnapShot + 1, "SNAPSHOT");
      guiItemsOn(6);

      if (guiItemsOff(6))screen.drawParameter(90, 0, 38, 28, nSnapShots, "TOTAL");



    } else if (mode == PRESET) {
      if (guiItemsOff(6))screen.drawParameter(64, 0, 64, 28, allPresets[currentPreset], "LOAD->"  );
      guiItemsOn(6);
      if (guiItemsOff(6))screen.drawParameter(0, 0, 64, 28, presetName, "MEMORY"  );
      if (guiItemsOff(lazy % 5)) {
        screen.drawTextSquare(26 * (lazy % 5), 40 , 24, 9,  "", presetName[lazy % 5]);
      }
      if (guiItemsOff(6)) {
        screen.drawParameterIcon(0, 0, 9);
      };

    } else if (mode == CUT) {
      if (guiItemsOff(9)) screen.drawAxis(analog.getValue(), analog2.getValue(), 25, 0 );
      if (guiItemsOff(7))screen.drawParameterIcon(0, 0, 11);

      if (guiItemsOff(6)) {

        screen.drawParameterH(25, 10, 128, 19, cutParameters[currentEdit]->modValue, cutParameters[currentEdit]->getName());
      }
      if (guiItemsOff(lazy % 5)) {
        screen.drawTextSquare(26 * (lazy % 5), 40 , 24, 9, cutParameters[(lazy % 5)]->getShortName(), String(cutParameters[(lazy % 5)]->modValue));
      }

    } else if (mode == LFOCUT) {

      if (guiItemsOff(12))
      {

        if (tracks[currentTrack]->isPlaying ) {
          screen.drawParameterIcon(0, 0, currentTrack);
          screen.drawParameterIcon(0, 12, 14);

          Serial.println("con");

        } else {
          screen.drawParameterIcon(0, 0, currentTrack);
          screen.drawParameterIcon(0, 12, 14);

          screen.drawParameterIcon(0, 4, 7);
          Serial.println("xcon");


        }
      }
      if (guiItemsOff(6) ) {
        // Serial.println(String(*axisParameters[currentLFO].lfoOptions[currentEdit]));
        if (currentEdit != 0)
        {
          screen.drawParameterH(25, 10, 128, 19, *cutParameters[currentLFO]->lfoOptions[currentEdit], cutParameters[currentLFO]->lfo.names[currentEdit] );

        } else {
          byte waveN = *cutParameters[currentLFO]->lfoOptions[currentEdit];
          screen.drawParameterH(25, 10, 128, 19, cutParameters[currentLFO]->lfo.optionsShort[waveN], cutParameters[currentLFO]->lfo.names[currentEdit] );

        }
      }
      if (guiItemsOff(6) == 0)screen.drawLFO(25, 0, 128, 10, cutParameters[currentLFO]->modValue, cutParameters[currentLFO]->getLFO() );

      byte tmpParam[] = {
        cutParameters[currentLFO]->lfo.wave,
        cutParameters[currentLFO]->lfo.division,
        cutParameters[currentLFO]->lfo.amp,
        cutParameters[currentLFO]->lfo.dc,
        cutParameters[currentLFO]->lfo.pwm_option,
      };
      if (guiItemsOff(lazy % 5) )screen.drawTextSquare(26 * (lazy % 5), 40, 24, 9, cutParameters[currentLFO]->lfo.names[lazy % 5], String(tmpParam[lazy % 5]));
    } else if (mode == AXIS) {
      if (guiItemsOff(9)) screen.drawAxis(analog.getValue(), analog2.getValue(), 25, 0 );
      if (guiItemsOff(7))screen.drawParameterIcon(0, 0, 12);

      if (guiItemsOff(6)) {

        screen.drawParameterH(25, 10, 128, 19, axisParameters[currentEdit].modValue, axisParameters[currentEdit].getName());
      }
      if (guiItemsOff(lazy % 5)) {
        screen.drawTextSquare(26 * (lazy % 5), 40 , 24, 9, axisParameters[(lazy % 5)].getShortName(), String(axisParameters[(lazy % 5)].modValue));
      }

    } else if (mode == LFOAXIS) {
     
      if (guiItemsOff(6) ) {
        if (currentEdit != 0)
        {
          screen.drawParameterH(25, 10, 128, 19, *axisParameters[currentLFO].lfoOptions[currentEdit], axisParameters[currentLFO].lfo.names[currentEdit] );

        } else {
          byte waveN = *axisParameters[currentLFO].lfoOptions[currentEdit];
          screen.drawParameterH(25, 10, 128, 19, axisParameters[currentLFO].lfo.optionsShort[waveN], axisParameters[currentLFO].lfo.names[currentEdit] );

        }
      }
      if (guiItemsOff(6) == 0)screen.drawLFO(25, 0, 128, 10, axisParameters[currentLFO].modValue, axisParameters[currentLFO].getLFO() );

      byte tmpParam[] = {
        axisParameters[currentLFO].lfo.wave,
        axisParameters[currentLFO].lfo.division,
        axisParameters[currentLFO].lfo.amp,
        axisParameters[currentLFO].lfo.dc,
        axisParameters[currentLFO].lfo.pwm_option,
      };
      if (guiItemsOff(lazy % 5) )screen.drawTextSquare(26 * (lazy % 5), 40, 24, 9, axisParameters[currentLFO].lfo.names[lazy % 5], String(tmpParam[lazy % 5]));
     


    } else if (mode == EDIT) {
      // by track
      

      // by style


      if (lazyEdit < 32)
      {
        for (int i = 0; i < 7; ++i)
        {
          screen.drawOneStepEdit(lazyEdit, memoryS[i]->weights[currentCluster][lazyEdit], i * 8 + 9);
          /* code */
        }
        
        lazyEdit++;
      } else {
        guiItemsOff(11);
      }

      if (lazySteps % 8 == 0 )
      {

        editBlink = 1;

      }
      if (lazySteps % 32 == 0) {
        editBlink = 0;


      }
      if (editBlink)
      {
        screen.drawOneStepEditB(cursorX, memoryS[cursorY]->weights[currentCluster][cursorX], cursorY * 8 + 9);
        screen.drawOneStepEdit(prevCursorX, memoryS[prevCursorY]->weights[currentCluster][prevCursorX], prevCursorY * 8 + 9);

      } else {
        screen.drawOneStepEdit(cursorX, memoryS[cursorY]->weights[currentCluster][cursorX], cursorY * 8 + 9);
        screen.drawOneStepEdit(prevCursorX, memoryS[prevCursorY]->weights[currentCluster][prevCursorX], prevCursorY * 8 + 9);


      }


      if (guiItemsOff(10))
      {
        screen.drawStyleEdit(0, 0, 35, 9, String("D:" + String(tracks[0]->parameters[0]->modValue)));
        screen.drawStyleEdit(35, 0, 20, 9, String("C:" + String(currentCluster + 1)));
        screen.drawStyleEdit(55, 0, 128, 9, rythmName);
        // guiItemsOn(11);
      }
      // screen.drawStyle(0, 54, 14, 9, currentCluster);
      // screen.drawStyle(15, 54, 128, 9, memoryS[currentTrack]->name);


    };
    lazy++;
    lazySteps++;

    lazySteps = lazySteps % 32;
    interface = false;
    // lazy=lazy%32;



  }
  // delay(10000);
}

bool guiItemsOff(byte item) {
  bool tmp = guiItems[item];
  guiItems[item] = false;
  return tmp;
}

void guiItemsOn(byte item) {
  guiItems[item] = true;
}

uint32_t freeRam() { // for Teensy 3.0
  uint32_t stackTop;
  uint32_t heapTop;

  // current position of the stack.
  stackTop = (uint32_t) &stackTop;

  // current position of heap.
  void* hTop = malloc(1);
  heapTop = (uint32_t) hTop;
  free(hTop);

  // The difference is the free, available ram.
  return stackTop - heapTop;
}

void UI_timerCallback()
{
  interface = true;
}

void DEBUG_timerCallback()
{
  debug = true;
}

void player(int time) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= time) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    HandleClock();
  }
}
void debugIt() {
  // unsigned long currentMillis = millis();
  // Serial.println("rfl = " + String(currentMillis - previousMillis));

  if (debug) {
    // previousMillis = currentMillis;
    // for(int i=0; i<nStyles; i++){
    //     Serial.println(styles[i].name);
    // }
    // styles[0].printProb();

    Serial.println("rfl = " + String(freeRam()));
    // Serial.println("rfl = " + String(chicago.weights[0][2]));
    // Serial.println("rfl = " + String(tpm[0].name));
    // Serial.println("rfl = " + String(tpm[0].shortName));
  }
  debug = false;



}
void FASTRUN blink() {
  clkState = !clkState;
  // HandleClock();
}
void FASTRUN analogReset() {
  doReset = !doReset;
  // HandleClock();
}
