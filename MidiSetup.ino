
#define USB_MIDI  //uncomment for usb midi
unsigned long previousMillisClk = 0;
unsigned long previousMillisAnalogClkReset = 0;
bool isAnalogClock=false;
void MidiLoop(){
	
	MIDI.read();
	// #ifdef USB_MIDI
	usbMIDI.read();
	// #endif
}
void MidiSetup()
{
	MIDI.begin(MIDI_CHANNEL_OMNI);
  	MIDI.setHandleClock(RealTimeSystemClassic);
  // #ifdef USB_MIDI
  usbMIDI.setHandleRealTimeSystem(RealTimeSystem);
	// #endif

  usbMIDI.setHandleNoteOn(HandleNoteOn);
  usbMIDI.setHandleNoteOff(HandleNoteOff);
  // usbMIDI.setHandleStart(HandleStart);
  // usbMIDI.setHandleStop(HandleReset);
  // usbMIDI.setHandleSongPosition(HandlePos);

  MIDI.setHandleNoteOn(HandleNoteOn);
  MIDI.setHandleNoteOff(HandleNoteOff);
  MIDI.setHandleStart(HandleStart);
  MIDI.setHandleStop(HandleReset);
  MIDI.setHandleSongPosition(HandlePos);
}
void RealTimeSystem(byte realtimebyte) {
	// Serial.print("ofwfewefwfpj");

	if (realtimebyte == 248) {
		HandleClock();
		previousMillisAnalogClkReset=millis();

	}

	// if(counter == 12) { digitalWrite(11, LOW); } }

	if (realtimebyte == 250 || realtimebyte == 251) {
		HandleStart();
	}

	if (realtimebyte == 252) {
		HandleReset();
	}

}
void RealTimeSystemClassic() {
	// Serial.print("ofwfewefwfpj");

	if (MIDI.getType() == 248) {
		HandleClock();
		previousMillisAnalogClkReset=millis();

	}

	// if(counter == 12) { digitalWrite(11, LOW); } }

	if (MIDI.getType() == 250 || MIDI.getType() == 251) {
		HandleStart();
	}

	if (MIDI.getType() == 252) {
		HandleReset();
	}

}
void playMidiNote(byte channel, byte note, byte velocity){

for (int i = 0; i < 7; ++i)
  {
  	if ( note==tracks[i]->parameters[7]->modValue && channel==tracks[i]->parameters[8]->modValue )
  	{
  		playNoteMIDI(i,  tracks[i]->parameters[4]->modValue);
  	}
    
    // tracks[i]->part_data.channel = 10;
  }

}
void HandleNoteOn(byte channel, byte note, byte velocity) {
	playMidiNote(channel, note, velocity);
	// Do whatever you want when you receive a Note On.
	// digitalWrite(8, HIGH);


	// Try to keep your callbacks short (no delays ect) as the contrary would slow down the loop()
	// and have a bad impact on real-time performance.
}
void HandlePos(unsigned int beatsin) {
	Serial.print(beatsin);
	beats=beatsin;
	// Do whatever you want when you receive a Note On.
	// digitalWrite(8, HIGH);


	// Try to keep your callbacks short (no delays ect) as the contrary would slow down the loop()
	// and have a bad impact on real-time performance.
}

void HandleNoteOff(byte channel, byte note, byte velocity) {
	// Serial.print("noteof");

	// Do whatever you want when you receive a Note On.
	// digitalWrite(8, LOW);


	// Try to keep your callbacks short (no delays ect) as the contrary would slow down the loop()
	// and have a bad impact on real-time performance.
}

void HandleClock() {
	 unsigned long currentMillis = millis();
	// clkState=HIGH;
	// global.control.showPixelTempo();
	// if (clkCount%6==0)
	//   {
	//    clkOutState=HIGH; 
	//   }
	//   clkCount++;
	
	// global.midiClockTick(false);
	// Serial.println("clkCount");
	// Serial.println(String(pulse)+" pulse");
	// Serial.println(String(quaver)+" quaver");
	// Serial.println(String(stepCount)+" stepCount");
	MIDI.sendRealTime(Clock);	
	tick();
	if ( pulse%(cutParameters[0]->modValue*3)==0 )
  	{

    	clkOutState=HIGH;
    	// clkState=HIGH;
    	digitalWrite(27, HIGH);
    	previousMillisClk=currentMillis+50	;

    // clkOutState=LOW;
  	}


}
void analogClock(){
  unsigned long currentMillis = millis();

if (clkState==HIGH)
  { 
  	// Serial.println("clo");
    clkOutState=HIGH;
    // previousMillisClk=currentMillis+100;
    clkState=LOW;
    HandleAnalogClock();
  }
  if (clkOutState && currentMillis>=previousMillisClk)
  {
  	// Serial.println(previousMillisClk);
  	// previousMillisClk=currentMillis-1;
  	clkOutState=LOW;
    digitalWrite(27, LOW);

  	/* code */
  }
  //  if (clkOutState==HIGH && pulse%cutParameters[0]->modValue==0 )
  // {

  //   previousMillisClk=millis()+1800;
  //   // digitalWrite(27, HIGH);
  //   // clkOutState=LOW;
  // }

  // global.displayControl();

  // control();
  // Serial.println(currentMillis - previousMillisClk);
  // Serial.println("down¡¡");
   // Serial.println(currentMillis);
     // Serial.println(previousMillisClk);
  // if(currentMillis - previousMillisClk >=100) {
  //    // previousMillisClk = currentMillis;
  //    Serial.println("down¡¡");
  //    // Serial.println(currentMillis);
  //    // Serial.println(previousMillisClk);
  //   // clkOutState=LOW;

  // }

}

void HandleAnalogClock() {
	// global.control.showPixelTempo();

	// clkOutState=HIGH; 
	previousMillisAnalogClkReset=millis();
	tickAnalog();
	// clkCount++;

}

void HandleReset() {
	bars=0;
	ticks=0;
	beats=0;
	pulse=1;
	reset();
	// global.reset();
	// Serial.println("reset");



}
void HandleStart() {
	// reseto();
	bars=0;
	ticks=0;
	beats=0;
	pulse=1;
	reset();
  	unsigned long currentMillis = millis();

	clkOutState=HIGH;
    	// clkState=HIGH;
    	digitalWrite(27, HIGH);
    	previousMillisClk=currentMillis+50	;
	// Serial.println("start1");


	// timer.midiClockTick();

}