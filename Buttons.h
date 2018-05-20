
//BUTTONS
#define PLOAD_PIN 32
#define CE_PIN 33
#define CLK_PIN 30
#define DATA_PIN 29
#define NUMBER_OF_SHIFT_CHIPS   2
#define BUTTON_TIME	2000

#define BUTTON_MENU 1
#define BUTTON_PLUS 0
#define BUTTON_MINUS 2
#define BUTTON_SHIFT 3
#define BUTTON_1 12 
#define BUTTON_2 13
#define BUTTON_3 14
#define BUTTON_4 15
#define BUTTON_5 8
#define BUTTON_6 5
#define BUTTON_7 6
#define BUTTON_A 11 
#define BUTTON_B 10
#define BUTTON_C 9
#define BUTTON_D 4
#define BUTTON_E 7

unsigned int pinValues;
unsigned int oldPinValues;
unsigned long buttonPressedTime=0;
bool modeChange=false;
int XmapIn=-50,YmapIn=50;
float Xmap=0,Ymap=0;
int oldXmapIn=XmapIn, oldYmapIn=YmapIn;
// e1 e2 e3 e4 e5,ICON, PARAMETER, steps, style, map
bool guiItems[]={1,1,1,1,1,1,1,1,1,1,1,1,1};
bool drawSteps=0;
bool doRefresh=false;
byte refreshItem=0;
byte prevCursorX=0;
byte cursorX=0;
byte prevCursorY=0;
byte cursorY=0;
byte nameCursor=0;
byte patternMod=0;
byte shiftMod=0;
bool loadPresetNow=0;
/* Width of data (how many ext lines).
*/
#define DATA_WIDTH   NUMBER_OF_SHIFT_CHIPS * 8

/* Width of pulse to trigger the shift register to read and latch.
*/
#define PULSE_WIDTH_USEC   5

/* Optional delay between shift register reads.
*/
#define POLL_DELAY_MSEC   1

/* You will need to change the "int" to "long" If the
 * NUMBER_OF_SHIFT_CHIPS is higher than 2.
*/
///
bool butValues[16]={0,0,0,0,0,0,0,0,0,0,0,0};


byte currentStyle=1;
byte prevStyle=1;
byte currentLFO=1;
byte currentEdit=0;
bool shift=false;
enum Modes {PLAY, LFO, FILL, TRACK,LFOTRACK, SNAPSHOT, PRESET, CUT, LFOCUT, AXIS, LFOAXIS, EDIT};
Modes mode=PLAY;
Modes prevMode=mode;

void setFillValue(byte encoder){
		long newPos= encoders[encoder]->read();
		if (newPos != positions[encoder]  &&  newPos%4==0 ){
			currentEdit=encoder;
			int increment = checkDirection(positions[encoder], newPos);
			positions[encoder] = newPos;
			int tmp = fillParameters[encoder].getParameterValue(increment);
			guiItems[encoder]=true;
			guiItems[6]=true;			
		}


	}
void setTrackSettingsValue(byte encoder){
		long newPos= encoders[encoder]->read();
		if (newPos != positions[encoder] &&  newPos%4==0  ){
			currentEdit=encoder;
			int increment = checkDirection(positions[encoder], newPos);
			positions[encoder] = newPos;
			int tmp = tracks[currentTrack]->parameters[encoder+5]->getParameterValue(increment);
			guiItems[encoder]=true;
			guiItems[6]=true;
			// Serial.print(String(tmp));
		}
	}

void setAllTrackSettingsValue(byte encoder){
	long newPos= encoders[encoder]->read();
	if (newPos != positions[encoder] &&  newPos%4==0  ){
		currentEdit=encoder;

		int increment = checkDirection(positions[encoder], newPos);
		positions[encoder] = newPos;
		byte temp;
		
		int tmp = tracks[currentTrack]->parameters[encoder+5]->getParameterValue(increment);
			for (int i = 0; i < 7; ++i)
			{
				tracks[i]->parameters[encoder+5]->value = tmp;
				
			}
		
		guiItems[encoder]=true;
		guiItems[6]=true;
	}
}
void setTrackValue(byte encoder){
		long newPos= encoders[encoder]->read();
		if (newPos != positions[encoder] &&  newPos%4==0  ){
			currentEdit=encoder;
			int increment = checkDirection(positions[encoder], newPos);
			positions[encoder] = newPos;
			int tmp = tracks[currentTrack]->parameters[encoder]->getParameterValue(increment);
			guiItems[encoder]=true;
			guiItems[6]=true;
		}


	}
void setAllTrackValues(byte encoder){
			

		long newPos = encoders[encoder]->read();
		if (newPos != positions[encoder] &&  newPos%4==0  ){
			
			currentEdit=encoder;
			int increment = checkDirection(positions[encoder], newPos);
			positions[encoder] = newPos;
			int tmp = tracks[currentTrack]->parameters[encoder]->getParameterValue(increment);
			guiItems[encoder]=true;
			guiItems[6]=true;

			for (int i = 0; i < 7; ++i)
			{


				if (i!=currentTrack)
				{
					tracks[i]->parameters[encoder]->modValue=tracks[i]->parameters[encoder]->value=tmp;
				}
			}

			
		}


	}
	
void setLFOValue(byte encoder){

	long newPos= encoders[encoder]->read();
	if (newPos != positions[encoder] &&  newPos%4==0  ){
		currentEdit=encoder;
		int increment = checkDirection(positions[encoder], newPos);
		positions[encoder] = newPos;
		tracks[currentTrack]->parameters[currentLFO]->getLFOValue(encoder, increment);
		tracks[currentTrack]->parameters[currentLFO]->tickSimple();
		guiItems[encoder]=true;
		guiItems[6]=true;
		
	}


}
void setAllLFOValues(byte encoder){
	currentEdit=encoder;
	
	long newPos= encoders[encoder]->read();
	if (newPos != positions[encoder] &&  newPos%4==0  ){
		int increment = checkDirection(positions[encoder], newPos);
		positions[encoder] = newPos;
		tracks[currentTrack]->parameters[encoder]->getLFOValue(encoder, increment);
		guiItems[encoder]=true;
		guiItems[6]=true;
		for (int i = 0; i < 7; ++i)
		{
			if (i!=currentTrack)
			{
				tracks[i]->parameters[encoder]->lfoOptions[i]=tracks[currentTrack]->parameters[encoder]->lfoOptions[encoder];
			}
			
		}		
		}


}
void setNameValue(byte encoder){
	long newPos= encoders[encoder]->read();
	if (newPos != positions[encoder] &&  newPos%4==0  ){
		int increment = checkDirection(positions[encoder], newPos);
		positions[encoder] = newPos;
		byte temp = sessionName[encoder];
		guiItems[encoder]=true;
		guiItems[6]=true;
		sessionName[encoder]=min(max(temp+=increment, 48),124);
	}
}
void setPresetValue(byte encoder){
	long newPos= encoders[encoder]->read();
	if (newPos != positions[encoder] &&  newPos%4==0  ){
		int increment = checkDirection(positions[encoder], newPos);
		positions[encoder] = newPos;
		byte temp = presetName[encoder];
		guiItems[encoder]=true;
		guiItems[6]=true;
		presetName[encoder]=min(max(temp+=increment, 48),124);
	}
}

void setLFOcutValue(byte encoder){

	long newPos= encoders[encoder]->read();
	if (newPos != positions[encoder] &&  newPos%4==0  ){
		currentEdit=encoder;

		int increment = checkDirection(positions[encoder], newPos);
		positions[encoder] = newPos;

		cutParameters[currentLFO]->getLFOValue(encoder, increment);
		cutParameters[currentLFO]->tickSimple();
		guiItems[encoder]=true;
		guiItems[6]=true;
		
	}
}

void setCutValue(byte encoder){
	long newPos= encoders[encoder]->read();

	if (newPos != positions[encoder] &&  newPos%4==0  ){
		currentEdit=encoder;
		int increment = checkDirection(positions[encoder], newPos);
		positions[encoder] = newPos;
		guiItems[encoder]=true;
		guiItems[6]=true;
		int tmp=cutParameters[encoder]->getParameterValue(increment);
		
	}
}

void setLFOAxisValue(byte encoder){

	long newPos= encoders[encoder]->read();
	if (newPos != positions[encoder] &&  newPos%4==0  ){
		currentEdit=encoder;

		int increment = checkDirection(positions[encoder], newPos);
		positions[encoder] = newPos;

		axisParameters[currentLFO].getLFOValue(encoder, increment);
		axisParameters[currentLFO].tickSimple();
		guiItems[encoder]=true;
		guiItems[6]=true;
		
	}
}
void setAxisValue(byte encoder){
	long newPos= encoders[encoder]->read();

	if (newPos != positions[encoder] &&  newPos%4==0  ){
		currentEdit=encoder;
		int increment = checkDirection(positions[encoder], newPos);
		positions[encoder] = newPos;
		guiItems[encoder]=true;
		guiItems[6]=true;
		int tmp=axisParameters[encoder].getParameterValue(increment);
		
	}
}
void setStep(byte cluster, byte track, byte step, int increment){
	// byte tmp=85;
	if (increment == 1)
	{
		switch(memoryS[track]->weights[cluster][step]){
		case 0:
			memoryS[track]->weights[cluster][step]=85;
		break;
		case 85:
			memoryS[track]->weights[cluster][step]=170;
		break;
		case 170:
			memoryS[track]->weights[cluster][step]=255;
		break;
		case 255:
			memoryS[track]->weights[cluster][step]=0;
		break;
		}
	}else{

		switch(memoryS[track]->weights[cluster][step]){
		case 0:
			memoryS[track]->weights[cluster][step]=255;
		break;
		case 85:
			memoryS[track]->weights[cluster][step]=0;
		break;
		case 170:
			memoryS[track]->weights[cluster][step]=85;
		break;
		case 255:
			memoryS[track]->weights[cluster][step]=170;
		break;
	}
	}
	
}

void patternize(byte inc){
	patternMod+=inc;
	patternMod=patternMod%32;
	for (int i = 0; i < 32; ++i)
	{
		if(i%patternMod==0){ memoryS[cursorY]->weights[currentCluster][i]=255; }else{ memoryS[cursorY]->weights[currentCluster][i]=0; };
	}
}
void shifter(byte inc){
	memcpy(clipboard.weights[1], memoryS[cursorY]->weights[currentCluster], 32);
	for (int i = 0; i < 32; ++i)
	{
		memoryS[cursorY]->weights[currentCluster][i]=clipboard.weights[1][abs(i+(inc))%32];
	}

}

void probabShifter(byte inc){
	
	for (int i = 0; i < 32; ++i)
	{
		if (memoryS[cursorY]->weights[currentCluster][i]>0)
		{
			memoryS[cursorY]->weights[currentCluster][i]=(1+random(3))*85;
		}
		

	}
}
void probabRand(byte inc){
	
	shiftMod+=inc;
	shiftMod=abs(shiftMod%25);
	
	for (int i = 0; i < 16; ++i)
	{	
		byte rnd= random(25);

		if (rnd>shiftMod)
		{
			
			memoryS[cursorY]->weights[currentCluster][i*2]=(random(4))*85;
		}else{
			memoryS[cursorY]->weights[currentCluster][i*2]=0;

		}

	}
}
void setEditValue(byte encoder){
	long newPos = encoders[encoder]->read();
	if (newPos != positions[encoder] &&  newPos%4==0  ){
		currentEdit=encoder;
		int increment = checkDirection(positions[encoder], newPos);
		positions[encoder] = newPos;
		guiItems[encoder]=true;
		switch(encoder){
			case 0:

			if (shift)
			{
				rythmName[nameCursor]+=increment;
				rythmName[nameCursor]=max(65, min(rythmName[nameCursor], 95));
				guiItems[10]=true;

			}else{
				for (int i = 0; i < 7; ++i) {tracks[i]->parameters[0]->getParameterValue(increment); }	
				guiItems[10]=true;

			}
			break;
			case 1:

				if (!shift)
				{
				prevCursorX=cursorX;
				prevCursorY=cursorY;
				cursorX=abs(cursorX+increment)%32;
				}else{
					patternize(increment);
					lazyEdit=0;

				}
			break;
			case 2:
				if (!shift)
				{
				prevCursorX=cursorX;
				prevCursorY=cursorY;
				cursorY=abs(cursorY+increment)%7;
				}else{
					shifter(increment);
					lazyEdit=0;

				}

			break;
			case 3:
				if (!shift)
				{
					setStep(currentCluster, cursorY, cursorX, increment);
				}else{
					probabShifter(increment);
					lazyEdit=0;

				}
			break;	
			case 4:
				if (!shift)
					{
					currentCluster=abs(currentCluster+increment)%9;
					lazyEdit=0;
					guiItems[11]=true;
					guiItems[10]=true;
				}else{

					probabRand(increment);
					lazyEdit=0;

				}

			break;
		}
		
	}
}
void mute(byte track){
	tracks[track]->isPlaying=!tracks[track]->isPlaying;
}
////MODES GUI
void refresh(){

	if (interface && doRefresh)
	{
		guiItems[refreshItem]=true; 
		refreshItem=(refreshItem+1)%9;
	}
	 
	

}
void commonModes(){
	
	if(butValues[BUTTON_SHIFT]){ shift=true; }else{ shift=false; };
	if(butValues[BUTTON_MENU]){  doRefresh=true; guiItems[12]=true; guiItems[9]=true;}else{};
}
void copy(byte cluster, byte track){
 	memcpy(clipboard.weights[0], memoryS[track]->weights[cluster], 32);  
}
void copyAll(byte cluster){
	for (int i = 0; i < 7; ++i){ memcpy(clipboard.weights[i], memoryS[i]->weights[cluster], 32); }
}
void paste(byte cluster, byte track){
 	memcpy(memoryS[track]->weights[cluster], clipboard.weights[0],  32);  
	lazyEdit=0;
}
void pasteAll(byte cluster){
 	for (int i = 0; i < 7; ++i){ memcpy(memoryS[i]->weights[cluster], clipboard.weights[i],  32); }
	lazyEdit=0;

}
void clear( byte cluster){
	for (int t = 0; t < 7; ++t){ for (int i = 0; i < 32; ++i){ memoryS[t]->weights[cluster][i]=0; } }
	screen.clear();
	lazyEdit=0;
	guiItems[10]=true;
	guiItems[11]=true;
 	
}
void save(){
	saveStyle();

}


void editMode(){
	
	
	// //LFO SELECT
	if(butValues[BUTTON_SHIFT]){ shift=true; }else{ shift=false; };
	if(butValues[BUTTON_1]){ if( shift ){ mute( 0 ); }else{  saveStyle();}};
	if(butValues[BUTTON_2]){ if( shift ){ mute( 1 ); }else{  copy(currentCluster, cursorY);}};
	if(butValues[BUTTON_3]){ if( shift ){ mute( 2 ); }else{  paste(currentCluster, cursorY);}};
	if(butValues[BUTTON_4]){ if( shift ){ mute( 3 ); }else{  copyAll(currentCluster);}};
	if(butValues[BUTTON_5]){ if( shift ){ mute( 4 ); }else{  pasteAll(currentCluster);}};
	if(butValues[BUTTON_6]){ if( shift ){ mute( 5 ); }else{  clear(currentCluster);}};
	if(butValues[BUTTON_7]){ if( shift ){ mute( 6 ); }else{  char tmp[18]; strcpy(tmp, lang[random(81)]); strcat(tmp, "-"); strcat(tmp, lang[random(81)]); strncpy(rythmName, tmp, 13); guiItems[10]=true; guiItems[11]=true; }};
	if(butValues[BUTTON_MENU]){ mode=PLAY; };	
	if(butValues[BUTTON_PLUS]){ 
		if (!shift)
		{
			rythmName[nameCursor]++;

		}else{
			nameCursor++;
			nameCursor=nameCursor%12;
		}
		guiItems[10]=true;
		guiItems[11]=true;
	}
	if(butValues[BUTTON_MINUS]){ 
		if (!shift)
		{
			rythmName[nameCursor]--;

		}else{
			nameCursor--;
			nameCursor=abs(nameCursor%12);
			
		}
 		guiItems[10]=true;
		guiItems[11]=true;
		
	};
	
}
void trackMode(){	
	if(butValues[BUTTON_MENU]){ mode=PLAY; };
	if(butValues[BUTTON_1]){ if( shift ){ mute( 0 ); currentTrack=0; guiItems[12]=true;}else{ currentTrack=0; drawSteps=guiItems[8]=guiItems[7]=guiItems[12]=true;}};
	if(butValues[BUTTON_2]){ if( shift ){ mute( 1 ); currentTrack=1; guiItems[12]=true;}else{ currentTrack=1; drawSteps=guiItems[8]=guiItems[7]=guiItems[12]=true;}};
	if(butValues[BUTTON_3]){ if( shift ){ mute( 2 ); currentTrack=2; guiItems[12]=true;}else{ currentTrack=2; drawSteps=guiItems[8]=guiItems[7]=guiItems[12]=true;}};
	if(butValues[BUTTON_4]){ if( shift ){ mute( 3 ); currentTrack=3; guiItems[12]=true;}else{ currentTrack=3;  drawSteps=guiItems[8]=guiItems[7]=guiItems[12]=true;}};
	if(butValues[BUTTON_5]){ if( shift ){ mute( 4 ); currentTrack=4; guiItems[12]=true;}else{ currentTrack=4;  drawSteps=guiItems[8]=guiItems[7]=guiItems[12]=true;}};
	if(butValues[BUTTON_6]){ if( shift ){ mute( 5 ); currentTrack=5; guiItems[12]=true;}else{ currentTrack=5;  drawSteps=guiItems[8]=guiItems[7]=guiItems[12]=true;}};
	if(butValues[BUTTON_7]){ if( shift ){ mute( 6 ); currentTrack=6; guiItems[12]=true;}else{ currentTrack=6;  drawSteps=guiItems[8]=guiItems[7]=guiItems[12]=true;}};
	if(butValues[BUTTON_A]){ mode=LFOTRACK; currentLFO=5; guiItemsOn(9); guiItemsOn(12); };
	if(butValues[BUTTON_B]){ mode=LFOTRACK; currentLFO=6; guiItemsOn(9); guiItemsOn(12); };
	if(butValues[BUTTON_C]){ mode=LFOTRACK; currentLFO=7; guiItemsOn(9); guiItemsOn(12); };	
	if(butValues[BUTTON_D]){ mode=LFOTRACK; currentLFO=8; guiItemsOn(9); guiItemsOn(12); };
	if(butValues[BUTTON_E]){ mode=LFOTRACK; currentLFO=9; guiItemsOn(9); guiItemsOn(12); };
 
}
void cutMode(){
	if(butValues[BUTTON_MENU]){ mode=PLAY; };
	if(butValues[BUTTON_4]){ mode=FILL;  guiItems[12]=true; guiItems[9]=true;};
	if(butValues[BUTTON_2]){ mode=SNAPSHOT; guiItems[12]=true; guiItems[9]=true;};
	if(butValues[BUTTON_5]){ mode=CUT; guiItems[12]=true; guiItems[9]=true;};
	if(butValues[BUTTON_6]){ mode=AXIS; guiItems[12]=true; guiItems[9]=true;};

	if(butValues[BUTTON_A]){mode=LFOCUT;  currentLFO=0;};
	if(butValues[BUTTON_B]){mode=LFOCUT;  currentLFO=1;};
	if(butValues[BUTTON_C]){mode=LFOCUT;  currentLFO=2;};
	if(butValues[BUTTON_D]){mode=LFOCUT;  currentLFO=3;};
	if(butValues[BUTTON_E]){mode=LFOCUT;  currentLFO=4;}; 
}

void playMode(){
	
	if(butValues[BUTTON_PLUS]){ 
		tracks[currentTrack]->style=min(max(tracks[currentTrack]->style+1,0), nStyles-1); 
		prevStyle=currentStyle;
		currentStyle=tracks[currentTrack]->style; 
		loadStyleTrack(currentStyle, currentTrack);
		if (shift)for (int i = 0; i < 7; ++i){ tracks[i]->style = currentStyle; loadStyleTrack(currentStyle, i);};
		guiItems[8]=true;
		guiItems[7]=true;

	}
	if(butValues[BUTTON_MINUS]){ 
		tracks[currentTrack]->style=min(max(tracks[currentTrack]->style-1,0), nStyles-1); 
		prevStyle=currentStyle;
		currentStyle=tracks[currentTrack]->style; 
		loadStyleTrack(currentStyle, currentTrack);
		if (shift)for (int i = 0; i < 7; ++i){ tracks[i]->style = currentStyle; loadStyleTrack(currentStyle, i);};
		guiItems[8]=true;
		guiItems[7]=true;
 		
	};
	//TRACK SELECT
	
		
	if(butValues[BUTTON_1]){ if( shift ){ mute( 0 ); currentTrack=0; guiItems[12]=true;}else{ currentTrack=0; drawSteps=guiItems[8]=guiItems[7]=guiItems[12]=true;}};
	if(butValues[BUTTON_2]){ if( shift ){ mute( 1 ); currentTrack=1; guiItems[12]=true;}else{ currentTrack=1; drawSteps=guiItems[8]=guiItems[7]=guiItems[12]=true;}};
	if(butValues[BUTTON_3]){ if( shift ){ mute( 2 ); currentTrack=2; guiItems[12]=true;}else{ currentTrack=2; drawSteps=guiItems[8]=guiItems[7]=guiItems[12]=true;}};
	if(butValues[BUTTON_4]){ if( shift ){ mute( 3 ); currentTrack=3; guiItems[12]=true;}else{ currentTrack=3;  drawSteps=guiItems[8]=guiItems[7]=guiItems[12]=true;}};
	if(butValues[BUTTON_5]){ if( shift ){ mute( 4 ); currentTrack=4; guiItems[12]=true;}else{ currentTrack=4;  drawSteps=guiItems[8]=guiItems[7]=guiItems[12]=true;}};
	if(butValues[BUTTON_6]){ if( shift ){ mute( 5 ); currentTrack=5; guiItems[12]=true;}else{ currentTrack=5;  drawSteps=guiItems[8]=guiItems[7]=guiItems[12]=true;}};
	if(butValues[BUTTON_7]){ if( shift ){ mute( 6 ); currentTrack=6; guiItems[12]=true;}else{ currentTrack=6;  drawSteps=guiItems[8]=guiItems[7]=guiItems[12]=true;}};
	if(butValues[BUTTON_A]){ mode=LFO; guiItems[12]=true; currentLFO=0;}
	if(butValues[BUTTON_B]){ mode=LFO; guiItems[12]=true; currentLFO=1;};
	if(butValues[BUTTON_C]){ mode=LFO; guiItems[12]=true; currentLFO=2;};
	if(butValues[BUTTON_D]){ mode=LFO; guiItems[12]=true; currentLFO=3;};
	if(butValues[BUTTON_E]){ mode=LFO; guiItems[12]=true; currentLFO=4;};
	if(butValues[BUTTON_MENU] && shift){ mode=FILL;};

	


}
void lfoMode(){

	//ORDER¡¡¡¡ 
	//10, 11, 2,,3
	//9,8,12,1,5, 4
	//15,14,13,0,7,6
	if(butValues[BUTTON_PLUS]){  min(4,currentLFO++) ;};
	if(butValues[BUTTON_MINUS]){ max(0, currentLFO--);};
	if(butValues[BUTTON_MENU]){ mode=PLAY; guiItems[12]=true;};

	if(butValues[BUTTON_A]){   guiItems[12]=true; currentLFO=0;};
	if(butValues[BUTTON_B]){   guiItems[12]=true; currentLFO=1;};
	if(butValues[BUTTON_C]){   guiItems[12]=true; currentLFO=2;};
	if(butValues[BUTTON_D]){   guiItems[12]=true; currentLFO=3;};
	if(butValues[BUTTON_E]){   guiItems[12]=true; currentLFO=4;};
}
void lfoTrackMode(){

	//ORDER¡¡¡¡ 
	//10, 11, 2,,3
	//9,8,12,1,5, 4
	//15,14,13,0,7,6
	if(butValues[BUTTON_MENU]){ mode=TRACK;};
	if(butValues[BUTTON_1]){ if( shift ){ mute( 0 ); currentTrack=0;}else{ currentTrack=0; guiItems[12]=guiItems[8]=guiItems[7]=true;}};
	if(butValues[BUTTON_2]){ if( shift ){ mute( 1 ); currentTrack=1;}else{ currentTrack=1; guiItems[12]=guiItems[8]=guiItems[7]=true;}};
	if(butValues[BUTTON_3]){ if( shift ){ mute( 2 ); currentTrack=2;}else{ currentTrack=2; guiItems[12]=guiItems[8]=guiItems[7]=true;}};
	if(butValues[BUTTON_4]){ if( shift ){ mute( 3 ); currentTrack=3; }else{ currentTrack=3;  guiItems[12]=guiItems[8]=guiItems[7]=true;}};
	if(butValues[BUTTON_5]){ if( shift ){ mute( 4 ); currentTrack=4; }else{ currentTrack=4;  guiItems[12]=guiItems[8]=guiItems[7]=true;}};
	if(butValues[BUTTON_6]){ if( shift ){ mute( 5 ); currentTrack=5; }else{ currentTrack=5;  guiItems[12]=guiItems[8]=guiItems[7]=true;}};
	if(butValues[BUTTON_7]){ if( shift ){ mute( 6 ); currentTrack=6; }else{ currentTrack=6;  guiItems[12]=guiItems[8]=guiItems[7]=true;}};
	if(butValues[BUTTON_A]){  guiItems[12]=true; currentLFO=5; guiItems[12]=true; };
	if(butValues[BUTTON_B]){  guiItems[12]=true; currentLFO=6; guiItems[12]=true; };
	if(butValues[BUTTON_C]){  guiItems[12]=true; currentLFO=7; guiItems[12]=true; };
	if(butValues[BUTTON_D]){  guiItems[12]=true; currentLFO=8; guiItems[12]=true; };
	if(butValues[BUTTON_E]){  guiItems[12]=true; currentLFO=9; guiItems[12]=true; };
}
void fillMode(){
	
	if(butValues[BUTTON_MENU]){ mode=PLAY; };
					
	if(butValues[BUTTON_A]){ mode=EDIT; lazyEdit=0; guiItems[10]=true; guiItems[11]=true;};
	if(butValues[BUTTON_2]){ mode=SNAPSHOT; guiItems[12]=true; guiItems[9]=true;};
	if(butValues[BUTTON_6]){ mode=AXIS; guiItems[12]=true; guiItems[9]=true;};
	if(butValues[BUTTON_3]){ mode=PRESET; guiItems[12]=true; guiItems[9]=true;};
	if(butValues[BUTTON_5]){ mode=CUT; guiItems[12]=true; guiItems[9]=true;};

	if(butValues[BUTTON_PLUS]){ 
		tracks[currentTrack]->style=min(max(tracks[currentTrack]->style+1,0), nStyles-1); 
		prevStyle=currentStyle;
		currentStyle=tracks[currentTrack]->style; 
		if (shift)for (int i = 0; i < 7; ++i){ tracks[i]->style = currentStyle;};	
		guiItems[8]=true;
		guiItems[7]=true;

	}
	if(butValues[BUTTON_MINUS]){ 
		tracks[currentTrack]->style=min(max(tracks[currentTrack]->style-1,0), nStyles-1); 
		prevStyle=currentStyle;
		currentStyle=tracks[currentTrack]->style; 
		if (shift)for (int i = 0; i < 7; ++i){ tracks[i]->style = currentStyle;};
		guiItems[8]=true;
		guiItems[7]=true;

	};

	//ORDER¡¡¡¡ 
	//10, 11, 2,,3
	//9,8,12,1,5, 4
	//15,14,13,0,7,6
	
}
void saveMode(){
	if(butValues[BUTTON_MENU]){  mode=PLAY; };
	if(butValues[BUTTON_4]){ mode=FILL; guiItems[12]=true; guiItems[9]=true;};
	if(butValues[BUTTON_3]){ mode=PRESET; guiItems[12]=true; guiItems[9]=true;};
	if(butValues[BUTTON_5]){ mode=CUT; guiItems[12]=true; guiItems[9]=true;};
	if(butValues[BUTTON_6]){ mode=AXIS; guiItems[12]=true; guiItems[9]=true;};

	if(butValues[BUTTON_PLUS]){  playingSnapShot=min(max(playingSnapShot+1,0),nSnapShots-1); Serial.println(nSnapShots);};
	if(butValues[BUTTON_MINUS]){  playingSnapShot=min(max(playingSnapShot-1,0),nSnapShots-1); Serial.println(nSnapShots);};
	if(butValues[BUTTON_3]){ mode=PRESET;};
	if(butValues[BUTTON_1]){ if(!shift){takeSnapShot(false);}else{takeSnapShot(true);};};

	if(butValues[BUTTON_7]){ readSDSnapShot();};
	
}
void setPreset(byte pr){
  readSDPreset(allPresets[pr]);
  strcpy(presetName, allPresets[pr]);

}

void presetMode(){
	if(butValues[BUTTON_MENU]){ mode=PLAY; };
	if(butValues[BUTTON_4]){ mode=FILL; guiItems[12]=true; guiItems[9]=true;};
	if(butValues[BUTTON_2]){ mode=SNAPSHOT; guiItems[12]=true; guiItems[9]=true;};
	if(butValues[BUTTON_5]){ mode=CUT; guiItems[12]=true; guiItems[9]=true;};
	if(butValues[BUTTON_6]){ mode=AXIS; guiItems[12]=true; guiItems[9]=true;};

	if(butValues[BUTTON_PLUS]){ currentPreset=min(max(currentPreset+1,0),nPresets-1);Serial.println(nPresets-1);};
	if(butValues[BUTTON_MINUS]){ currentPreset=min(max(currentPreset-1,0),nPresets-1);Serial.println(nPresets-1);};

	if(butValues[BUTTON_1]){ savePreset();};
	if(butValues[BUTTON_7]){ setPreset(currentPreset);};
	
	
}
void axisMode(){
	if(butValues[BUTTON_MENU]){ mode=PLAY; };
	if(butValues[BUTTON_4]){ mode=FILL; guiItems[12]=true; guiItems[9]=true;};
	if(butValues[BUTTON_2]){ mode=SNAPSHOT; guiItems[12]=true; guiItems[9]=true;};
	if(butValues[BUTTON_5]){ mode=CUT; guiItems[12]=true; guiItems[9]=true;};

	if(butValues[BUTTON_A]){mode=LFOAXIS;  currentLFO=0;};
	if(butValues[BUTTON_B]){mode=LFOAXIS;  currentLFO=1;};
	if(butValues[BUTTON_C]){mode=LFOAXIS;  currentLFO=2;};
	if(butValues[BUTTON_D]){mode=LFOAXIS;  currentLFO=3;};
	if(butValues[BUTTON_E]){mode=LFOAXIS;  currentLFO=4;};
	// if(butValues[BUTTON_6]){ mode=AXIS;};

	// if(butValues[15]){ mode=SAVE;};
	if(butValues[BUTTON_PLUS]){ 
		tracks[currentTrack]->style=min(max(tracks[currentTrack]->style+1,0), nStyles-1); 
		prevStyle=currentStyle;
		currentStyle=tracks[currentTrack]->style; 
		// Serial.println(tracks[currentTrack]->style);
		if (shift)for (int i = 0; i < 7; ++i){ tracks[i]->style = currentStyle;};	
		guiItems[8]=true;
		guiItems[7]=true;

	}
	if(butValues[BUTTON_MINUS]){ 
		tracks[currentTrack]->style=min(max(tracks[currentTrack]->style-1,0), nStyles-1); 
		prevStyle=currentStyle;
		currentStyle=tracks[currentTrack]->style; 
		if (shift)for (int i = 0; i < 7; ++i){ tracks[i]->style = currentStyle;};
		guiItems[8]=true;
		guiItems[7]=true;

	};

	//10, 11, 2,,3
	//9,8,12,1,5, 4
	//15,14,13,0,7,6
	
	
}

void LFOaxisMode(){
	if(butValues[BUTTON_MENU]){ mode=AXIS; };
	if(butValues[BUTTON_4]){ mode=FILL;};
	if(butValues[BUTTON_2]){ mode=SNAPSHOT;};
	if(butValues[BUTTON_5]){ mode=CUT;};


	if(butValues[BUTTON_A]){mode=LFOAXIS;  currentLFO=0;};
	if(butValues[BUTTON_B]){mode=LFOAXIS;  currentLFO=1;};
	if(butValues[BUTTON_C]){mode=LFOAXIS;  currentLFO=2;};
	if(butValues[BUTTON_D]){mode=LFOAXIS;  currentLFO=3;};
	if(butValues[BUTTON_E]){mode=LFOAXIS;  currentLFO=4;};

	if(butValues[BUTTON_PLUS]){ 
		tracks[currentTrack]->style=min(max(tracks[currentTrack]->style+1,0), nStyles-1); 
		prevStyle=currentStyle;
		currentStyle=tracks[currentTrack]->style; 
		if (shift)for (int i = 0; i < 7; ++i){ tracks[i]->style = currentStyle;};	
		guiItems[8]=true;
		guiItems[7]=true;

	}
	if(butValues[BUTTON_MINUS]){ 
		tracks[currentTrack]->style=min(max(tracks[currentTrack]->style-1,0), nStyles-1); 
		prevStyle=currentStyle;
		currentStyle=tracks[currentTrack]->style; 
		if (shift)for (int i = 0; i < 7; ++i){ tracks[i]->style = currentStyle;};
		guiItems[8]=true;
		guiItems[7]=true;

	};

	// if(butValues[BUTTON_1]){ savePreset();};
	// if(butValues[BUTTON_7]){ setPreset(currentPreset);};
	//10, 11, 2,,3
	//9,8,12,1,5, 4
	//15,14,13,0,7,6
	
	
}

void LFOcutMode(){
	if(butValues[BUTTON_MENU]){ mode=CUT; };
	if(butValues[BUTTON_A]){mode=LFOCUT;  currentLFO=0;};
	if(butValues[BUTTON_B]){mode=LFOCUT;  currentLFO=1;};
	if(butValues[BUTTON_C]){mode=LFOCUT;  currentLFO=2;};
	if(butValues[BUTTON_D]){mode=LFOCUT;  currentLFO=3;};
	if(butValues[BUTTON_E]){mode=LFOCUT;  currentLFO=4;};

	if(butValues[BUTTON_PLUS]){ 
		tracks[currentTrack]->style=min(max(tracks[currentTrack]->style+1,0), nStyles-1); 
		prevStyle=currentStyle;
		currentStyle=tracks[currentTrack]->style; 
		if (shift)for (int i = 0; i < 7; ++i){ tracks[i]->style = currentStyle;};	
		guiItems[8]=true;
		guiItems[7]=true;

	}
	if(butValues[BUTTON_MINUS]){ 
		tracks[currentTrack]->style=min(max(tracks[currentTrack]->style-1,0), nStyles-1); 
		prevStyle=currentStyle;
		currentStyle=tracks[currentTrack]->style; 
		if (shift)for (int i = 0; i < 7; ++i){ tracks[i]->style = currentStyle;};
		guiItems[8]=true;
		guiItems[7]=true;

	};


	
	
}


void updateShifters(){
	// 
	//ORDER¡¡¡¡ 
	//10, 11, 2,,3
	//9,8,12,1,5, 4
	//15,14,13,0,7,6

	if (mode==PLAY)
	{
		commonModes();
		playMode();

	}else if (mode == LFO){
		commonModes();
		lfoMode();

	}else if (mode == FILL){
		// menuModes();
		commonModes();
		fillMode();

	}else if (mode == TRACK){
		// menuModes();
		commonModes();
		trackMode();

	}else if (mode == LFOTRACK){
		// menuModes();
		commonModes();
		lfoTrackMode();

	}else if (mode == SNAPSHOT){
		// menuModes();
		commonModes();
		saveMode();

	}else if (mode == PRESET){
		// menuModes();
		commonModes();
		presetMode();

	}else if (mode == CUT){
		// menuModes();
		commonModes();
		cutMode();

	}else if (mode == LFOCUT){
		// menuModes();
		commonModes();
		LFOcutMode();

	}else if (mode == AXIS){
		// menuModes();
		commonModes();
		axisMode();

	}else if (mode == LFOAXIS){
		// menuModes();
		commonModes();
		LFOaxisMode();

	}else if (mode == EDIT){
		// menuModes();
		// commonModes();
		editMode();
		// LFOaxisMode();

	}

}


void buttonPressed(byte button){
Serial.print("pressed -> ");
Serial.println(button);
Serial.print("M0de -> ");
Serial.println(mode);
	if (button!=BUTTON_PLUS && button!=BUTTON_MINUS && button!=BUTTON_MENU && button!=BUTTON_SHIFT )
	{

		modeChange=true;
		// Serial.print("button");
		// Serial.println(String(button));
		buttonPressedTime=BUTTON_TIME; 
		doRefresh=true;
		
	}

}
void buttonReleased(byte button){
if (button!=BUTTON_PLUS && button!=BUTTON_MINUS && button!=BUTTON_MENU && button!=BUTTON_SHIFT )
	{

	modeChange=false;
	buttonPressedTime=BUTTON_TIME; 
	}
// Serial.println("released -> ");
// Serial.print(button);


}
void display_pin_values()
	{
		for (byte i = 0; i < DATA_WIDTH; i++)
		{
		// Serial.print((pinValues >> i) & 1);

			if ((pinValues >> i) & 1)
				{
					butValues[i]=1;
					buttonPressed(i);
				}else{
					if (butValues[i]==1)
					{
						buttonReleased(i);
					}

					butValues[i]=0;
					}
				// Serial.print(i);
				// Serial.print(" -> ");
				// Serial.print(butValues[i]);
				// Serial.print("\r\n");
		}

		// Serial.print("\r\n");
		// Serial.print(shift);
	}	

unsigned int read_shift_regs()
 	{
 		long bitVal;
 		unsigned int bytesVal = 0;

	  /* Trigger a parallel Load to latch the state of the data lines,
	  */
 		digitalWrite(CE_PIN, HIGH);
 		digitalWrite(PLOAD_PIN, LOW);
 		delayMicroseconds(PULSE_WIDTH_USEC);
 		digitalWrite(PLOAD_PIN, HIGH);
 		digitalWrite(CE_PIN, LOW);

	  /* Loop to read each bit value from the serial out line
	   * of the SN74HC165N.
	  */
	   for (byte i = 0; i < DATA_WIDTH; i++)
	   {
	   	bitVal = digitalRead(DATA_PIN);

		/* Set the corresponding bit in bytesVal.
		*/
	   	bytesVal |= (bitVal << ((DATA_WIDTH - 1) - i));

		/* Pulse the Clock (rising edge shifts the next bit).
		*/
	   	digitalWrite(CLK_PIN, HIGH);
	   	delayMicroseconds(PULSE_WIDTH_USEC);
	   	digitalWrite(CLK_PIN, LOW);
	   }

	   return (bytesVal);
	}

void buttons(){
	pinValues = read_shift_regs();
	XmapIn = map(analog.getValue(),0,1023,-100,100);
	YmapIn = map(analog2.getValue(),0,1023,-100,100);
 	axisParameters[0].setValue(XmapIn);
 	axisParameters[1].setValue(YmapIn);

 	// axisParameters[1].value=XmapIn;
	refresh();
	  /* If there was a chage in state, display which ones changed.
	  */
	// unsigned long currentMillis=millis();	
	if ( modeChange && mode==PLAY)
	{
		buttonPressedTime--;
		if (buttonPressedTime<=1)
		{
			mode=TRACK;
			guiItems[12]=true;
			buttonPressedTime=BUTTON_TIME;
			modeChange=false;
			doRefresh=true;;

			// Serial.println(String("fill"));
			// Serial.println(String(buttonPressedTime));
			// Serial.println(String(modeChange));
		}
		// Serial.println(String(buttonPressedTime));	

		// Serial.println(String((millis() - buttonPressedTime)));
	}

		// buttonPressedTime=millis();

		// Serial.println(String((millis() - buttonPressedTime)));
	
	if (pinValues != oldPinValues)
	{
		// Serial.print("*Pin value change detected*\r\n");
		display_pin_values();
		oldPinValues = pinValues;
		updateShifters();
	}
	if (mode==PLAY)
	{
		for (int i = 0; i < 5; ++i)
		{
			if (!shift)
			{
				setTrackValue(i);
			}else{
				setAllTrackValues(i);
			}
		
		}
	}else if(mode==LFO){

		for (int i = 0; i < 5; ++i)
		{
			if (!shift)
			{
				setLFOValue(i);
			}else{
				setAllLFOValues(i);
			}
		
		}
	}else if(mode==FILL){
			for (int i = 0; i < 5; ++i)
		{
				setFillValue(i);
		}
		
	}else if(mode==TRACK){
			for (int i = 0; i < 5; ++i)
			{
				if (!shift)
				{
					setTrackSettingsValue(i);
				}else{
					setAllTrackSettingsValue(i);
				}
			}
		
	}else if(mode==LFOTRACK){

		for (int i = 0; i < 5; ++i)
		{
			if (!shift)
			{
				setLFOValue(i);
			}else{
				setAllLFOValues(i);
			}
		
		}
	}else if(mode==SNAPSHOT){
			for (int i = 0; i < 5; ++i)
			{
					setNameValue(i);
			}
		
	}else if(mode==PRESET){
			for (int i = 0; i < 5; ++i)
			{
					setPresetValue(i);
			}
		
	}else if(mode==CUT){
			for (int i = 0; i < 5; ++i)
			{
					setCutValue(i);
			}
		
	}else if(mode==AXIS){
			for (int i = 0; i < 4; ++i)
			{
					setAxisValue(i);
			}
		
	}else if(mode==LFOAXIS){
			for (int i = 0; i < 5; ++i)
			{
					setLFOAxisValue(i);
			}
		
	}else if(mode==LFOCUT){
			for (int i = 0; i < 5; ++i)
			{
					setLFOcutValue(i);
			}
		
	}else if(mode==EDIT){
			for (int i = 0; i < 5; ++i)
			{
					setEditValue(i);
			}
		
	}
	
}

 