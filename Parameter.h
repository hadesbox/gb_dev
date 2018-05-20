#ifndef Parameter_h
#define Parameter_h
#include <Arduino.h>
// #include "LfoWaves.h"



#define NAME_MAX_LENGHT 9
#define SHORTNAME_MAX_LENGHT 4
class Parameter {


protected:

public:
	const byte sineWave[128]={127,133,140,146,152,158,164,170,176,182,187,193,198,203,208,213,217,222,226,230,233,236,240,242,245,247,249,251,252,253,255,255,255,255,253,252,251,250,248,246,244,241,238,235,231,228,224,219,215,210,206,200,195,190,184,179,173,167,161,155,149,142,136,130,124,117,111,105,99,93,87,81,75,69,64,58,53,48,43,39,34,30,26,22,19,16,13,10,8,6,4,3,2,1,0,0,0,1,1,2,4,5,7,9,12,15,18,21,25,28,33,37,41,46,51,56,62,67,73,78,84,90,96,102,109,115,121,127};

	char name[NAME_MAX_LENGHT];
	char shortName[SHORTNAME_MAX_LENGHT];
	boolean type = true;
	byte preset = 0;
	int value = 0;
	int modValue = 0;
	int min = 0;
	int max = 0;
	int lfoVal=0;
	byte increment = 0;
	char optionsNames[5][NAME_MAX_LENGHT];  
	char optionsShortNames[5][SHORTNAME_MAX_LENGHT];  
	typedef struct
	{ 	
		const byte divisions[16]={1,2,3,4,5,6,7,8,16,32,64,128};
		const char optionsShort[7][SHORTNAME_MAX_LENGHT] = {"SIN", "SAW", "SQR", "TRI", "RND","CV1","CV2"};
		const char options[7][NAME_MAX_LENGHT] = {"SINE", "SAW", "SQUARE", "TRIANGLE", "RANDOM","CV1","CV2"};
		const char names[7][SHORTNAME_MAX_LENGHT] = {"WAV", "SPD", "AMP", "OFS", "PWM"};
		const byte maxs[7]={6,16,100,128,128};
		const byte presets[7]={0,0,30,0,64};
		// const byte mins[5]={0,0,0,0,0};
		byte currentPosition=0;
		byte count=0;
		byte wave=1;
		byte division=1;
		byte amp=0;
		byte dc=0;
		byte pwm_option=64;
		int maxValue=0;
		int minValue=0;
		bool direction=1;
		bool isPlaying=true;
	} LFO;
	LFO lfo;
	byte *lfoOptions[5]={&lfo.wave,&lfo.division,&lfo.amp,&lfo.dc,&lfo.pwm_option};


	Parameter()
	{
	}
    ///NAME SHORTNAME TYPE(STR or INT) OPTIONS PRESET MIN MAX INCREMENT
	void init(char na[], char sNa[], bool ty, char (*opt)[NAME_MAX_LENGHT], char (*optShort)[SHORTNAME_MAX_LENGHT], byte pst, int mn , int mx, byte inc)
	{

		strcpy(name, na);
		strcpy(shortName, sNa);

		type = ty;

		preset = pst;
		value = pst;
		modValue = pst;
		max = mx;
		min = mn;
		increment = inc;


		if (!ty) {
			for (byte i = 0; i < max; i++) {
				strcpy(optionsNames[i], opt[i]);
				strcpy(optionsShortNames[i], opt[i]);

			};

		}
		setLFO(0, 0, 0, 0, 64);



	}
	void testPar(){
		for (byte i = 0; i < max; i++) {
			Serial.println(optionsNames[i]);
			Serial.println(optionsShortNames[i]);
		};
	}
	void reset(){
		lfo.currentPosition=0;

	}
	void setLFO(byte waveIn, byte divIn, byte ampIn, byte dcIn, byte pwmIn ){
		lfo.wave=waveIn;
		lfo.division=divIn;
		lfo.amp=ampIn;
		lfo.dc=dcIn;
		lfo.pwm_option=pwmIn;
	}
	String getLFO(){

		String tmpStr=String(shortName)+" "+String(modValue)+" "+String(value)+">"+String(lfo.maxValue);
		// String tmpStr=String(lfo.currentPosition)+" "+String(modValue)+" "+String(value)+">"+String(lfo.maxValue);
		return tmpStr;
	}
	
	int applyLFO(byte pos){
		int temp;
		int rest=0;
		
		float tempMax;
		float tempF;
		float tmpO;
		int mid;
		int valr;
		byte sqpos=0;
		bool triggered=0;
		lfo.currentPosition+=(128-lfo.divisions[lfo.division]);
		lfo.currentPosition=lfo.currentPosition%128;
		switch(lfo.wave){
			//SINE
			case 0:
			
			mid = (max-min);
			tempF = lfo.amp*0.01 ;
			tmpO = (float(sineWave[(lfo.currentPosition+lfo.pwm_option)%128])/255)*tempF;
			lfoVal= ((tmpO)*(mid));
			// tempMax = (mid) * tempF;

			// lfoVal=( int(map((tmpO*tempF), 0, 1, -mid/2, mid/2 ) ));

			// if (String(name)=="DIVISION")
			// {
			
			// Serial.println("------"+String(name)+"-----");

			// Serial.print("tempF ");
			// Serial.println(tempF);
			// Serial.print("tmpO ");
			// Serial.println(tmpO);
			// Serial.print("lfo.currentPosition ");
			// Serial.println(lfo.currentPosition);
			// Serial.print("sineWave ");
			// Serial.println(sineWave[(pos+lfo.pwm_option)%128]);
			// // Serial.print("tempMax ");
			// // Serial.println(tempMax);
			// // Serial.print("- tempMax ");
			// // Serial.println(-tempMax);
			// Serial.print("min ");
			// Serial.println(min);
			// Serial.print("max/2 ");
			// Serial.println(max/2);
			// // lfoVal=( int(map(sineWave[(pos+lfo.pwm_option)%128], 0, 255, -tmpO, tmpO )  ) );
			// Serial.print("lfoVal ");
			// Serial.println(lfoVal);
			// Serial.println("-----------");
			// Serial.println("-----------");
			// }
			break;
			//SAW
			case 1:
			// tempMax = map(lfo.amp, 0, 100, min, max/2) ;
			// lfoVal=( int(map(pos*2, 0, 255, -tempMax, tempMax ) ));
			mid = (max-min);
			tempF = lfo.amp*0.01 ;
			tmpO = (float(lfo.currentPosition*2)/255)*tempF;
			lfoVal= ((tmpO)*(mid));
			break;
			//SQUARE
			case 2:
			if((lfo.currentPosition)>lfo.pwm_option)sqpos=1;
			if((lfo.currentPosition)<lfo.pwm_option)sqpos=0;
			mid = (max-min);
			tempF = lfo.amp*0.01 ;
			tmpO = (sqpos)*tempF;
			lfoVal= ((tmpO)*(mid));
			// if(lfo.pwm_option>126 || lfo.pwm_option<1)lfo.direction=!lfo.direction;
			// tempMax = map( lfo.amp, 0, 100, min, max/2 ) ;
			// if (pos<lfo.pwm_option)
			// {
			// 	lfoVal=( int(map(0, 0, 255, -tempMax, tempMax ) ));
			// }else{
			// 	lfoVal=( int(map(255, 0, 255, -tempMax, tempMax ) ));
			// }
			break;
			//TRI
			case 3:
			if((lfo.currentPosition)>lfo.pwm_option)sqpos=1;
			if((lfo.currentPosition)<lfo.pwm_option)sqpos=0;
			mid = (max-min);
			tempF = lfo.amp*0.01;

			if (sqpos==0)
			{
				tmpO = (float(lfo.currentPosition*2)/255)*tempF;
				lfoVal= ((tmpO)*(mid/2));
				
			}else{

				tmpO = (float(lfo.currentPosition*2)/255)*tempF;
				lfoVal= ((tmpO)*(mid/2));

			}
						
			// mid = (max-min);
			// tempF = lfo.amp*0.01 ;
			// // tempMax = map(lfo.amp, 0, 100, min, max/2) ;
			// if (pos<lfo.pwm_option)
			// {
			// 	tmpO = (float(pos)/128)*tempF;

			// }else{
			// 	tmpO = (lfo.pwm_option-(float(pos))/128)*tempF;
				
			// }
			// lfoVal= ((tmpO)*(mid));

			break;
			//RANDOM
			case 4:
			mid = (max-min);

			// if((lfo.currentPosition)>lfo.pwm_option)sqpos=1;
			// if((lfo.currentPosition)<lfo.pwm_option){sqpos=0; triggered=0;};
			tempF = lfo.amp*0.01;

			if (pos%lfo.divisions[16-lfo.division]==0)
			{
				tmpO = (float(random(0,255))/255)*tempF;
				lfoVal= ((tmpO)*(mid));
			}
			
			
			// tempMax = map(lfo.amp, 0, 100, min, max/2) ;
			// if((pos)>=lfo.pwm_option ){sqpos=1;}else{sqpos=0;};
			// if (lfo.count==pos)
			// {
			// 	triggered=0;
			// 	// Serial.print("triggered NO");
			// }
			// mid = (max-min);
			// tempF = lfo.amp*0.01 ;
			// tmpO = (float(random(0,255))/255)*tempF;
			// if ( pos>lfo.pwm_option && triggered!=1)
			// {
			// 	lfoVal= ((tmpO)*(mid));
			// 	Serial.print("now");
			// 	Serial.println(lfoVal);
			// 	triggered=1;
			// 	/* code */
			// }
			// Serial.print("tempF");
			// Serial.println(tempF);
			// Serial.print("pos");
			// Serial.println(pos);
			
			// Serial.print("lfo.pwm_option");
			// Serial.println(lfo.pwm_option);
			
			// if (pos*2>lfo.pwm_option )
			// { 
			// 	sqpos=1;
				

			// }else{
			// 	sqpos=0;

			// }
			// if (sqpos==0)
			// {
			// 	triggered=0;
				
			// }
			// if (!triggered && sqpos<0)
			// {
			// 	lfoVal= ((tmpO)*(mid/2));
			// 	triggered=1;
			// }
			
			
			break;
			//CV1
			case 5:
			mid = (max-min);
			
			valr = CV1.getValue();
			tmpO = map(valr, 0, 1023, 0, lfo.amp );
			tempF = lfo.amp*0.01 ;
			// Serial.println(valr);
			Serial.println(tmpO);
			lfoVal= ((tmpO*0.01)*(mid));
			// Serial.println(lfoVal);

			break;
			//CV2
			case 6:
			mid = (max-min);
			
			valr = CV2.getValue();
			tmpO = map(valr, 0, 1023, 0, lfo.amp );
			tempF = lfo.amp*0.01 ;
			// Serial.println(valr);
			Serial.println(tmpO);
			lfoVal= ((tmpO*0.01)*(mid));
			// Serial.println(lfoVal);
			// Serial.println(valr);
			// Serial.println(tmpO*tempF);
			break;

		}
		if (lfo.amp>0)
		{
			modValue = (value+(lfoVal) ) + lfo.dc;
			modValue=max(min, modValue);
			modValue=min(max, modValue);
			//FOR INTERFACE 
			lfo.minValue = max(min,(value)+lfo.dc);
			lfo.minValue = min(max,(value)+lfo.dc);
			lfo.maxValue = min(max, (value+(mid*(tempF)))+lfo.dc);
			lfo.maxValue = max(min, (value+(mid*(tempF)))+lfo.dc);
			// lfo.maxValue = (value+tempMax)+lfo.dc;	

			// Serial.println("name ->"+String(name));
			// Serial.println("lfoVal ->"+String(lfoVal));
			// Serial.println("tempMax ->"+String(tempMax));
			// Serial.println("min ->"+String(min));
			// Serial.println("max ->"+String(max));
			// Serial.println("lfo.minValue ->"+String(lfo.minValue));
			// Serial.println("lfo.maxValue  ->"+String(lfo.maxValue ));
			// Serial.println("dc ->"+String(lfo.dc));
			// Serial.println("modValue ->"+String(modValue));

		}else{
			modValue=value;
		}
		
			// Serial.println("lfo 0 ->"+String(lfo.amp));
			// Serial.println("lmax0 ->"+String(tempMax));
			// Serial.println("modValue ->"+String(modValue));
			// Serial.println("pos ->"+String(pos));

	}
	void tickSimple(){
		// lfo.currentPosition+=lfo.divisions[lfo.division];
		// lfo.currentPosition=lfo.currentPosition%128;
		// Serial.println("simpel");
		// lfo.count=(lfo.count+1)%128;
		lfo.count++;
		lfo.count=lfo.count%128;
		applyLFO(lfo.count);
		
	}
	void tick(long quaver, long beats, long bars){
		// if (quaver%lfo.divisions[lfo.division]==0)
		// {
		// 		// lfo.currentPosition++;
		// 		// lfo.currentPosition=lfo.currentPosition%128;
		// 		// Serial.println("value  "+String(modValue));


		// }
				// Serial.println("sine "+String(sineWave[pos]));
				// Serial.println("lfo "+String(lfoVal));
				// Serial.println("rest "+String(rest));
				// Serial.println("curpos - ");
				// Serial.print(lfo.currentPosition);
				// Serial.println("");
			// lfo.currentPosition+=lfo.divisions[lfo.division]%128;
		// lfo.currentPosition+=lfo.divisions[lfo.division];
		// lfo.currentPosition=lfo.currentPosition%128;
		lfo.count++;
		lfo.count=lfo.count%128;
		applyLFO(lfo.count);

		

		
	}
	String getName ()
	{
		return name;
	}
	String getShortName ()
	{
		return shortName;
	}
	void setValue(int val){

		value = val;
		// modValue = 	value;


	}
	// int getValue(){

	// 	value = modValue;

	// }
	int getParameterValue(int incrementIn){
		value = min(max((value+(incrementIn * increment)), min), max-1);
		modValue = 	value;
		return modValue;

	}
	void getLFOValue(byte nlfo, int incrementIn){
		// Serial.println(name);
		*lfoOptions[nlfo] = min(max((*lfoOptions[nlfo]+(incrementIn )), 0), lfo.maxs[nlfo]);

	}
	bool getType ()
	{
		return type;
	}


	virtual const String classname() {
		return "parameter";
	}


};
#endif
