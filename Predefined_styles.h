const byte totalStyles = 15;



typedef struct
{
	char name[17];
	byte weights[9][32];
} StyleM;

StyleM k;
StyleM s;
StyleM c;
StyleM h1;
StyleM h2;
StyleM t1;
StyleM t2;


StyleM *memoryS[7]={&k,&s,&c,&h1,&h2,&t1,&t2};
StyleM clipboard;

typedef struct
{
	char name[17];
	char path[13];
} StyleName;

StyleName StyleNames[255];






void printMemory(byte track){
	for (int a = 0; a < 9; ++a)
	{
		Serial.println(String(a));
		for (int i = 0; i < 32; ++i)
		{
			Serial.print(String(memoryS[track]->weights[a][i]));
			Serial.print(", ");
		}
		Serial.println(" ");
	}

}
void printAllMemory(){
	
	for (int t = 0; t < 8; ++t)
	{
	

		for (int a = 0; a < 9; ++a)
		{
	

			for (int i = 0; i < 32; ++i)
			{
	
	
			}
		}
	}
	

}



void compress(){
	byte value;
	byte count=0;
	char test[32]="";
	for (int t = 0; t < 7; ++t)
	{
		for (int c = 0; c < 9; ++c)
		{
			strcat(test,"%");
			
			for (int i = 0; i < 32; ++i)
			{
				 byte step=memoryS[t]->weights[c][i];
				 if (step==value)
				 {
				 	count++;
				 }else{
				 	char buffer[2];         //the ASCII of the integer will be stored in this char array
					itoa(count,buffer,10); //(integer, yourBuffer, base)	
				 	

				 	
				 }
			}
		}
	}

	Serial.print(test);

}
void decompress( char* localString, byte track, byte array) {

	char result[64]="";
	byte value;
	byte step = 0;
	// bool addInt=0;
	byte cntInt=1;
	char number[4]="";
	strcpy(number, '\0');

	int num;
  	// Serial.println(localString);

	for (int i = 0; i < strlen(localString); ++i)
	{
		// Serial.print(",");
		if (localString[i] == 'a') {
			value = 0;
			strcpy(result, "");
			memoryS[track]->weights[array][step]=value;
			step++;
		} else if (localString[i] == 'b') {
			value = 85;
			strcpy(result, "");
			memoryS[track]->weights[array][step]=value;
			step++;
		} else if (localString[i] == 'c') {
			value = 170;
			strcpy(result, "");
			memoryS[track]->weights[array][step]=value;
			step++;
		} else if (localString[i] == 'd') {
			value = 255;
			strcpy(result, "");
			memoryS[track]->weights[array][step]=value;
			step++;
		} else {
 			char ts = localString[i];
 			char ts2 = localString[i+1];

			strcat(result, &ts);
			if (!isdigit(ts2))
			{
				for (int i = 0; i < byte(String(result).toInt())-1; ++i)
				{
					memoryS[track]->weights[array][step]=value;
					step++;
				}
			}
			
		}
		
	}
	
}


void decompressStyle( byte style ) {
	for (int t = 0; t < 7; ++t)
	{
		for (int i = 0; i < 9; ++i)
		{
	  
		}
	}


}
