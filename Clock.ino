
unsigned long pulse=1;
byte measure=4;
byte dividedClock[]={0,0,0,0,0,0,0,0};
const byte divisions[]={3,6,12,24,32,64,128};
const byte divisionsAnalog[]={	1,2,4,8,16,24,32};
unsigned long clockDurations[]={0,0,0,0,0,0,0,0,0};
bool clockStates[]={LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,};
int currentTempo=0;	



void initClock(){
	char options[5][NAME_MAX_LENGHT] = {"UP", "DWN", "EUCLID", "BCK", "RND"};
	char optionsShort[5][SHORTNAME_MAX_LENGHT] = {"UP", "DWN", "U&D", "BCK", "RND"};	
	fillParameters[0].init("INTERVAL", "INT", true, options, optionsShort,  32, 1, 65, 1);
	fillParameters[1].init("DURATION", "DUR", true, options, optionsShort,  0, 0, 33, 1);
	fillParameters[2].init("OFFSET", "OFS", true, options, optionsShort,  0, 0, 33, 1);
	fillParameters[3].init("RANDOM", "RND", true, options, optionsShort,  20, 0, 256, 1);
	fillParameters[4].init("SWING", "SWG", true, options, optionsShort,  0, 0, 100, 1);
	axisParameters[0].init("XMAP", "X", true, options, optionsShort,  34, -100, 100, 1);
	axisParameters[1].init("YMAP", "Y", true, options, optionsShort,  34, -100, 100, 1);
	axisParameters[2].init("TEMPO", "TMP", true, options, optionsShort,  130, 0, 200, 1);
	axisParameters[3].init("PLAY", "STR", true, options, optionsShort,  1, 0, 2, 1);
	cutting( 0 );
	currentTempo=130;
}

void tick(){
	
	
	if (axisParameters[0].modValue<0 && axisParameters[1].modValue<0) sector = 1;
	if (axisParameters[0].modValue<0 && axisParameters[1].modValue>0) sector = 2;
	if (axisParameters[0].modValue>=0 && axisParameters[1].modValue>=0) sector = 3;
	if (axisParameters[0].modValue>=0 && axisParameters[1].modValue<=0) sector = 4;
	Xmap=abs(axisParameters[0].modValue*0.01);
	Ymap=abs(axisParameters[1].modValue*0.01);

	
	// swing(dividedClock[tracks[0]->parameters[1]->modValue]%32, 36, 1, 127, 10 , 10);
	
	
	theBrain();

	if (pulse%divisions[0]==0){dividedClock[0]++;};
	if (pulse%divisions[1]==0){dividedClock[1]++;};
	if (pulse%divisions[2]==0){dividedClock[2]++;};
	if (pulse%divisions[3]==0){dividedClock[3]++;};
	if (pulse%divisions[4]==0){dividedClock[4]++;};
	if (pulse%divisions[5]==0){dividedClock[5]++;};
	if (pulse%divisions[6]==0){dividedClock[6]++;};
	if (pulse%divisions[7]==0){dividedClock[7]++;};
	// if (pulse%12==0){dividedClock[2]++;};
	if (pulse%6==0){ticks++;};
	if (pulse%24==0){beats++;};
	if (pulse%(24*measure)==0){
		bars++; 
		// if (loadPresetNow)
		// {
			
		// 	loadPresetNow=false;
		// }
		
	}
	pulse++;
	noteKill();

	
}


void clockOut(byte tr, byte dur){
	clockDurations[tr] = millis()+(dur/2
		);
	clockStates[tr]=HIGH;
	digitalWrite(outPins[tr], clockStates[tr]);

}
void reset(){
 for (int i = 0; i < 8; ++i)
 {
 	dividedClock[i]=0;
 }


}
void clocksKill(){
	unsigned long currentMillis = millis();
	for (int i = 0; i < 7; ++i)
	{
		if (currentMillis  >= clockDurations[i])
		{
			clockStates[i]=LOW;
			digitalWrite(outPins[i], clockStates[i]);
		}
	}

}

void theBrain(){
	
	byte stepCut;
	if((pulse-1)%divisions[ 0 ]==0){
			stepCut = dividedClock[ tracks[0]->parameters[1]->modValue ]%128;

			cut(stepCut);
			for (int i = 0; i < 5; ++i)
			{
				axisParameters[i].tickSimple();
				cutParameters[i]->tickSimple();
			}
			
	}
			

			
	for (int i = 0; i < 7; ++i)
	{	

		byte divPar=tracks[i]->parameters[1]->modValue;	
		byte divParBreak=tracks[i]->parameters[2]->modValue;	
		byte tempDiv;
		byte tempAmount;
		byte cut=0;


			
		byte noFillBars=fillParameters[0].modValue;
		byte fillBars=fillParameters[1].modValue;
		if (beats%noFillBars<(noFillBars-(fillBars)) )
		{
			tempDiv=divPar;
			tempAmount=tracks[i]->parameters[0]->modValue;
		}else{
			tempDiv=divParBreak;
			tempAmount=max(0,(tracks[i]->parameters[0]->modValue/2)-random(0, fillParameters[3].modValue));


		}

		if((pulse-1)%divisions[ tempDiv ]==0){
			
			byte step = dividedClock[ tempDiv ]%32;
			byte stec = dividedClock[ tempDiv ]%128;
			

			
			if(step%2==0){
				
				cut = cutting( stec/2 )*2; 
				
			}else{

				cut+=1;
				
			}
			byte drf;

			if (mode==EDIT)
				{
					if(p_cutOn.modValue==1){
						drf = editFunc(i,  cut);    
					}else{
						drf = editFunc(i,  step);    

					}
				}else{
					if(p_cutOn.modValue==1){
						drf = drumFunc(i, sector, cut);    
					}else{
						drf = drumFunc(i, sector, step);    

					}

				}

			
			if (254-drf < (tempAmount))
			{
					
				
				if (tracks[i]->isPlaying)
				{
					swing(i, beats, tracks[i]->parameters[7]->modValue+(tracks[i]->parameters[5]->modValue*tracks[i]->parameters[6]->modValue), 1, tracks[i]->parameters[3]->modValue, tracks[i]->parameters[4]->modValue*10, tracks[i]->parameters[8]->modValue);
					if( tracks[i]->parameters[9]->value>0)swing(i, beats, tracks[i]->parameters[9]->modValue, 1, tracks[i]->parameters[3]->modValue, tracks[i]->parameters[4]->modValue*10, tracks[i]->parameters[8]->modValue);
					if( tracks[i]->parameters[9]->value>0)swing(i, beats, tracks[i]->parameters[9]->modValue, 1, tracks[i]->parameters[3]->modValue, tracks[i]->parameters[4]->modValue*10, tracks[i]->parameters[8]->modValue+2);
					//ADDING
					// if( tracks[i]->parameters[9]->value>0)swing(i, beats, tracks[i]->parameters[9]->modValue+(tracks[i]->parameters[5]->modValue*tracks[i]->parameters[6]->modValue), 1, tracks[i]->parameters[3]->modValue, tracks[i]->parameters[4]->modValue*10, tracks[i]->parameters[8]->modValue);
					// if( tracks[i]->parameters[9]->value>0)swing(i, beats, tracks[i]->parameters[9]->modValue+(tracks[i]->parameters[5]->modValue*tracks[i]->parameters[6]->modValue), 1, tracks[i]->parameters[3]->modValue, tracks[i]->parameters[4]->modValue*10, tracks[i]->parameters[8]->modValue+2);
					
				}
			}else{


			}
				tracks[i]->tick(pulse,  beats, bars );
		}
			
	}
}
void tickAnalog(){
	
	
	if (axisParameters[0].modValue<0 && axisParameters[1].modValue<0) sector = 1;
	if (axisParameters[0].modValue<0 && axisParameters[1].modValue>0) sector = 2;
	if (axisParameters[0].modValue>=0 && axisParameters[1].modValue>=0) sector = 3;
	if (axisParameters[0].modValue>=0 && axisParameters[1].modValue<=0) sector = 4;
	Xmap=abs(axisParameters[0].modValue*0.01);
	Ymap=abs(axisParameters[1].modValue*0.01);
	
	
	
	theBrainA();
	// ticks++;
	// dividedClock[0]++; 
	if (pulse%1==0){dividedClock[0]++; ticks++;};
	if (pulse%2==0){dividedClock[1]++; };
	if (pulse%4==0){dividedClock[2]++;beats++;};
	if (pulse%8==0)dividedClock[3]++;
	if (pulse%16==0)bars++;
	
	pulse++;
	noteKill();
}

void theBrainA(){
	byte stepCut;
	if((pulse-1)%divisionsAnalog[ 2 ]==0){
			stepCut = dividedClock[ tracks[0]->parameters[1]->modValue  ]%128;
			cut(stepCut);
			for (int i = 0; i < 4; ++i)
			{
				axisParameters[i].tickSimple();
				cutParameters[i]->tickSimple();
			}
			}
	
	for (int i = 0; i < 7; ++i)
	{	
			// Serial.println(pulse);

			byte divPar=tracks[i]->parameters[1]->modValue;	
			byte divParBreak=tracks[i]->parameters[2]->modValue;	
			byte tempDiv;
			byte tempAmount;
			byte cut=0;
			
		byte noFillBars=fillParameters[0].modValue;
		byte fillBars=fillParameters[1].modValue;
		if (beats%noFillBars<(noFillBars-(fillBars)) )
		{
			tempDiv=divPar;
			tempAmount=tracks[i]->parameters[0]->modValue;
		}else{
			tempDiv=divParBreak;
			tempAmount=max(0,(tracks[i]->parameters[0]->modValue/2)-random(0, fillParameters[3].modValue));


		}
		byte step = dividedClock[ tempDiv ]%32;
		byte stec = dividedClock[ tempDiv ]%128;			
	
		
		if(step%2==0){
			
			cut = cutting( stec/2 )*2; 
			
		}else{
 
 			cut+=1;
			
		}
		byte drf;
		if (mode==EDIT)
		{
			if(p_cutOn.modValue<=1){
				drf = editFunc(i,  cut);    
			}else{
				drf = editFunc(i,  step);    

			}
		}else{
			if(p_cutOn.modValue<=1){
				drf = drumFunc(i, sector, cut);    
			}else{
				drf = drumFunc(i, sector, step);    

			}

		}
		
		
		if((pulse)%divisionsAnalog[ tempDiv ]==0){
			// Serial.println("now"+String(pulse%32)+" "+String(pulse)+" "+String( tempDiv *3)+" "+String(dividedClock[ tempDiv ]%32	));
			// usbMIDI.sendNoteOn(36+ tempDiv , 127, 10); usbMIDI.sendNoteOff(36+ tempDiv , 127, 10);

			if (254-drf < (tempAmount))
			{
					
					if (tracks[i]->isPlaying)
				{
					swing(i, beats, tracks[i]->parameters[7]->modValue+(tracks[i]->parameters[5]->modValue*tracks[i]->parameters[6]->modValue), 1, tracks[i]->parameters[3]->modValue, tracks[i]->parameters[4]->modValue*10, tracks[i]->parameters[8]->modValue);
					if( tracks[i]->parameters[9]->value>0)swing(i, beats, tracks[i]->parameters[9]->modValue, 1, tracks[i]->parameters[3]->modValue, tracks[i]->parameters[4]->modValue*10, tracks[i]->parameters[8]->modValue);
					if( tracks[i]->parameters[9]->value>0)swing(i, beats, tracks[i]->parameters[9]->modValue, 1, tracks[i]->parameters[3]->modValue, tracks[i]->parameters[4]->modValue*10, tracks[i]->parameters[8]->modValue+2);
					//ADDING
					// if( tracks[i]->parameters[9]->value>0)swing(i, beats, tracks[i]->parameters[9]->modValue+(tracks[i]->parameters[5]->modValue*tracks[i]->parameters[6]->modValue), 1, tracks[i]->parameters[3]->modValue, tracks[i]->parameters[4]->modValue*10, tracks[i]->parameters[8]->modValue);
					// if( tracks[i]->parameters[9]->value>0)swing(i, beats, tracks[i]->parameters[9]->modValue+(tracks[i]->parameters[5]->modValue*tracks[i]->parameters[6]->modValue), 1, tracks[i]->parameters[3]->modValue, tracks[i]->parameters[4]->modValue*10, tracks[i]->parameters[8]->modValue+2);
					// clockOut(i, tracks[i]->parameters[4]->modValue);
					
				}
				
				// tracks[i]->part_data.sequence[dividedClock[ tempDiv ]%32]=1;
			}else{
				// tracks[i]->part_data.sequence[dividedClock[ tempDiv ]%32%32]=0;


			}
				tracks[i]->tick(pulse,  beats, bars );
		}
			
	}
}

byte getWeight(byte tempStyle, byte variation, byte instrument, byte pos){
	byte temp;
	// temp = internalStyles[ tempStyle ] -> weights[ (instrument*9) + variation][ pos];
	// temp = internalStyles[ tempStyle ] -> weights[ (instrument*9) + variation][ pos];
	return temp;
}
int editFunc(byte track,  byte position){
	return memoryS[track]->weights[ currentCluster ][ position ]; 
}

int drumFunc(byte track, byte sector, byte position){
	int prob=0;
	int prob1=0;
	int prob2=0;
	int prob3=0;
	int prob4=0;
	byte tempStyle=tracks[track]->style;


	switch(sector){
		case 1:
		// tempStyle=tracks[track]->style;
		prob1 = memoryS[track]->weights[ 0 ][ position ];
		prob2 = memoryS[track]->weights[ 1 ][ position ];
		prob3 = memoryS[track]->weights[ 5 ][ position ];
		prob4 = memoryS[track]->weights[ 2 ][ position ];
		prob = ( ( ( prob1*Xmap ) + ( prob2*( 1-Xmap ) ) * Ymap ) ) + ( ( ( prob3*Xmap) + ( prob4 * (1-Xmap ) ) ) * ( 1 - Ymap ) );
		return prob;
		break;
		case 2:
		// tempStyle=tracks[track]->style;
		prob1 = memoryS[track]->weights[ 1 ][ position ];
		prob2 = memoryS[track]->weights[ 2 ][ position ];
		prob3 = memoryS[track]->weights[ 6 ][ position ];
		prob4 = memoryS[track]->weights[ 5 ][ position ];
		prob= ( ( ( prob1*Xmap ) + ( prob2*( 1-Xmap ) ) * Ymap ) ) + ( ( ( prob3*Xmap) + ( prob4 * (1-Xmap ) ) ) * ( 1 - Ymap ) );
		return prob;
		break;
		case 3:
		// tempStyle=tracks[track]->style;
		prob1 = memoryS[track]->weights[ 3 ][ position ];
		prob2 = memoryS[track]->weights[ 4 ][ position ];
		prob3 = memoryS[track]->weights[ 7 ][ position ];
		prob4 = memoryS[track]->weights[ 8 ][ position ];
		prob= ( ( ( prob1*Xmap ) + ( prob2*( 1-Xmap ) ) * Ymap ) ) + ( ( ( prob3*Xmap) + ( prob4 * (1-Xmap ) ) ) * ( Ymap ) );
		return prob;
		break;
		case 4:
		// tempStyle=tracks[track]->style;
		prob1 = memoryS[track]->weights[ 5 ][ position ];
		prob2 = memoryS[track]->weights[ 6 ][ position ];
		prob3 = memoryS[track]->weights[ 8 ][ position ];
		prob4 = memoryS[track]->weights[ 0 ][ position ];
		prob = ( ( ( prob1*Xmap ) + ( prob2*( 1-Xmap ) ) * Ymap ) ) + ( ( ( prob3*Xmap) + ( prob4 * (1-Xmap ) ) ) * ( 1 - Ymap ) );
		return prob;
		break;
		default:
		break;

	};
	return prob;

	
}
unsigned long tempoMillis;
unsigned long tMillis;
