#define VOICE_COUNT 80 


byte NOTE_ON[VOICE_COUNT]={0};
byte NOTE_ON_MIDI[VOICE_COUNT]={0};
byte NOTE_ON_TRIGGER[VOICE_COUNT]={0};
unsigned long NOTE_ON_SWING[VOICE_COUNT]={0};
byte NOTE_CHAN[VOICE_COUNT]={0};
byte NOTE_VEL[VOICE_COUNT]={0};
unsigned long NOTE_OFF[VOICE_COUNT]={0};
unsigned long NOTE_OFF_MIDI[VOICE_COUNT]={0};
byte swingAmount = 0 ;

void playNote(byte trigger, byte pitch, byte velocity, int duration, byte chan)
{
	unsigned long time = millis();	

// find an empty note slot
boolean found_slot = false;
for (byte i=0;i<VOICE_COUNT;i++){
	if (NOTE_VEL[i] == 0){
		NOTE_ON[i] = pitch;
		NOTE_ON_TRIGGER[i] = trigger;
		NOTE_VEL[i] = 1+velocity;
		NOTE_OFF[i] = time+duration;
		NOTE_CHAN[i] = chan;
		found_slot = true;
		break;
	}
}

if (found_slot == false){

}
else{
	MIDI.sendNoteOn(pitch, velocity, chan);
	usbMIDI.sendNoteOn(pitch, velocity, chan);

	clockOut(trigger, duration);
};
}
void playNoteMIDI(byte trigger, int duration)
{
	clockOut(trigger, duration);
	
}

void swingNote(byte trigger, byte pitch, byte velocity, int duration, byte chan)
{
	unsigned long time = millis();
// find an empty note slot
	boolean found_slot = false;
	for (byte i=0;i<VOICE_COUNT;i++){
		if (NOTE_VEL[i] == 0){
			NOTE_ON[i] = pitch;
			NOTE_ON_TRIGGER[i] = trigger;
			NOTE_VEL[i] = 1+velocity;
			NOTE_ON_SWING[i] = time+swingAmount;
			NOTE_OFF[i] = time+swingAmount+duration;
			NOTE_CHAN[i] = chan;
			found_slot = true;
			break;
		}
}


}

void swing(byte trigger, byte step, byte note, byte octave, byte vel, int duration, byte chan){
	swingAmount = fillParameters[4].modValue*2;
	

	
	if(swingAmount>0){
		if (step%2!=0)
		{
			

			swingNote(trigger, quantize(note, octave),vel,duration,chan);

		}else {

			playNote(trigger, quantize(note, octave),vel,duration,chan);


		}

	}else{
		playNote(trigger, quantize(note, octave),vel,duration,chan);

	}

	}
void swingClock(byte trigger, byte step, byte note, byte octave, byte vel, int duration, byte chan){
	swingAmount = fillParameters[4].modValue*2;
	

	
	if(swingAmount>0){
		if (step%2!=0)
		{
			

			swingNote(trigger, quantize(note, octave),vel,duration,chan);

		}else {

			playNote(trigger, quantize(note, octave),vel,duration,chan);


		}

	}else{
		playNote(trigger, quantize(note, octave),vel,duration,chan);

	}

	}

void noteKill()
{
unsigned long time=millis();
for (int i=0;i<VOICE_COUNT;i++){
	if (NOTE_VEL[i]>0 && NOTE_OFF[i]<time ){  // if note value>0 and note off time < time
		byte pitch = NOTE_ON[i];
		byte velocity = 0;
		MIDI.sendNoteOff(pitch, velocity, NOTE_CHAN[i]);
		usbMIDI.sendNoteOff(pitch, velocity, NOTE_CHAN[i]);
		NOTE_VEL[i]=0; //wipe NOTE_ON entry to signal no active note
	}
}
}
void playSwingNotes(){

			// Serial.print(VOICE_COUNT);
			unsigned long time=millis();
			for (byte i=0;i<VOICE_COUNT;i++){
			    if (time >=  NOTE_ON_SWING[i] && NOTE_ON_SWING[i]>0  ){  // if note value>0 and note off time < time
					
					clockOut(NOTE_ON_TRIGGER[i], NOTE_OFF[i]);
			    	MIDI.sendNoteOn(NOTE_ON[i], NOTE_VEL[i], NOTE_CHAN[i]);
			    	usbMIDI.sendNoteOn(NOTE_ON[i], NOTE_VEL[i], NOTE_CHAN[i]);
			    	NOTE_ON_SWING[i]=0;
			    }
			}
		}

byte quantize(byte note,byte octave)
{
	return octave*12+note;
}