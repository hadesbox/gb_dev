#include <Arduino.h>
#include "Parameter.h"

#define MAX_ARRAY_NOTES 32
class DrumTrack{
private:
	
public:
	Parameter amount;
	Parameter division;
	Parameter breakDivision;
	Parameter velocity;
	Parameter duration;
	Parameter note;
	Parameter step;
	Parameter chan;
	Parameter mult;
	Parameter alt;
	Parameter length;


	byte style=0;

	char name[8];
	char shortName[4];
	bool isPlaying=true;

	Parameter* parameters[10]={&amount,&division,&breakDivision,&velocity,&duration,&mult,&step,&note,&chan,&alt};
	typedef struct
				{ 	
					
					byte channel=1;
					byte note=0;
					byte octave=2;
					byte step=0;
					byte offset=0;
					byte multiplier=8;
				} Data;
	Data part_data;
	DrumTrack() {
		init();
	 }


	void init(){
		//NAME SHORTNAME TYPE(STR or INT) OPTIONS PRESET MIN MAX INCREMENT
		char optionsShort[5][SHORTNAME_MAX_LENGHT] = {"UP", "DWN", "U&D", "BCK", "RND"};
		char options[5][NAME_MAX_LENGHT] = {"UP", "DWN", "E", "BCK", "RND"};
		amount.init("DENSITY", "DNS", true, options, optionsShort,  18, 0, 255, 5);
		division.init("DIVISION", "DIV", true, options, optionsShort,  1, 0, 7, 1);
		breakDivision.init("FILL", "FIL", true, options, optionsShort,  2, 0, 7, 1);
		velocity.init("VELOCITY", "VEL", true, options, optionsShort,  100, 0, 127, 1);
		duration.init("DURATION", "DUR", true, options, optionsShort,  10, 0, 255, 1);
		note.init("NOTE", "NOT", true, options, optionsShort,  0, 0, 255, 1);
		alt.init("ALTNOTE", "ALT", true, options, optionsShort,  0, 0, 255, 1);
		step.init("STP", "STP", true, options, optionsShort,  0, 0, 255, 1);
		chan.init("CHANNEL", "CHN", true, options, optionsShort,  10, 0, 255, 1);
		mult.init("MULTIPLY", "MUL", true, options, optionsShort,  8, 0, 255, 1);
		
		

	}
	Parameter* getParameter( byte param){
		return parameters[param];
	}

	byte getParameterCount(){
		byte max= sizeof(parameters) / sizeof(parameters[ 0 ]);
		return max;
	}

	void tick(long quaver, long beats, long bars){

		
		for (int i = 0; i < 10; ++i)
		{
			parameters[i]->tick(quaver, beats, bars);
		}
	}


	String getName ()
	{
		return name;
	}
	String getShortName ()
	{
		return shortName;
	}

	void getNextStep ()
	{

	}

	void generateSequence(int *parameters, byte *triggers){



	}
	void generateStep(byte step, int *parameters, byte *triggers){



	}
};