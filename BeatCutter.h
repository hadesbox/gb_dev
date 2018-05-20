// BASED ON https://composerprogrammer.com/research/acmethodsforbbsci.pdf
Parameter p_outClockDiv;
Parameter p_cutOn;
Parameter p_maxPhraselength;
Parameter p_repeatChance;
Parameter p_maxRepeats;

Parameter* cutParameters[5]={&p_outClockDiv,&p_cutOn, &p_maxPhraselength, &p_repeatChance, &p_maxRepeats};

byte subDiv = 16;

float unitsInCut=1;

int unitsLeft=0;
int unitsDone=0;
int totalUnits=0;
int barsNow;
int repeats=0;
int repeatsDone=0;
int segs[MAX_ARRAY_NOTES*4];
int indx[MAX_ARRAY_NOTES*4];
int dindx[MAX_ARRAY_NOTES*4];

int segsCount=0;
int indxCount=1;
int dindxCount=0;
int dindxTotal=0;

void cutter(){
	segsCount=0;
	indxCount=1;
	dindxCount=0;
	barsNow=(random(1, p_maxPhraselength.modValue));
	totalUnits=(barsNow*subDiv);
	unitsDone=0;
	repeats=0;
	repeatsDone=0;
	int index=0;
	indx[0]=0;
	while(unitsDone<totalUnits){

		unitsLeft = (totalUnits - unitsDone);

		if(repeatsDone==repeats){
			repeatsDone=0;
			byte randN=(random(1,100));
			

			if((unitsLeft<(subDiv)) && (randN < p_repeatChance.modValue )){
				unitsInCut=1;
				repeats=unitsLeft;
			} else {
				float temp;
				float max;
				temp=(subDiv/2);
				if(int(temp) % 2==0){
					max=((temp-1)/2);
				} else {
					max=((temp-2)/2);
				}
				unitsInCut = (random(0.0,max*10.0)/10.0f);
	       		unitsInCut = int(2 * unitsInCut + 1);
				while(unitsInCut>unitsLeft){
					unitsInCut=unitsInCut-2;
					unitsInCut=abs(unitsInCut);
				}
				repeats=int(random(1, p_maxRepeats.modValue));
				if(repeats*unitsInCut>unitsLeft){
					unitsInCut=unitsLeft;
					repeats=1;

				}
			}

			index += int(unitsInCut);
			index=index%subDiv;

		}

		if (unitsInCut>0)
		{
			segs[segsCount]=((unitsInCut));
			segsCount++;
			indx[indxCount]=index;
			indxCount++;	
		}
		
		unitsDone=(unitsDone+unitsInCut);
		repeatsDone++;

	}

	byte ctr=0;

	for(byte s=0; s<segsCount; s++){
		for(byte i=0; i<segs[s]; i++){
			ctr=indx[s];
			dindx[dindxCount] = (((i+ctr)%subDiv));
			dindxCount++;

		}
	}

	dindxTotal = dindxCount;
}
void initCutter(){

	char options[5][NAME_MAX_LENGHT] = {"UP", "DWN", "E", "BCK", "RND"};
	char optionsShort[5][SHORTNAME_MAX_LENGHT] = {"UP", "DWN", "U&D", "BCK", "RND"};
	p_outClockDiv.init("CLKDIV", "CDV", true, options, optionsShort,  4, 1, 129, 1);
	p_cutOn.init("ON", "ON", true, options, optionsShort,  0, 0, 2, 1);
	p_maxPhraselength.init("LENGTH", "MXP", true, options, optionsShort,  1, 1, 17, 1);
	p_repeatChance.init("CHANCE", "RPT", true, options, optionsShort,  1, 0, 99, 1);
	p_maxRepeats.init("REPEAT", "MXR", true, options, optionsShort,  1, 1, 8, 1);
	cutter();

}
void cut(byte step){
	if (int(step)%(dindxTotal)==0)
	{ 
		cutter();
	}
}
byte cutting(byte step){
		return dindx[(step)%dindxTotal];
}