File settingsFile;
File presetFile;
File snapshotFile;
File styleFile;
File startUpFile;
File sessionDir;

//PRESETS IN SD CARD
int snapShot=0;
byte nSnapShots=0;
byte playingSnapShot=0;
char sessionName[6]={'D','E','F','L','T'};
byte currentPreset=0;
char presetName[6]={'D','E','F','L','T'};
char rythmName[13]={'N','A','M','E','I','T','O','R','L','O','S','E'};
char allPresets[32][6];
char allStyles[7][32];
char tmpChar[64];
char character;
byte nPresets=0;
byte nStyles = 0;
String temp;
Parameter fillParameters[]={Parameter(),Parameter(),Parameter(),Parameter(),Parameter()};
Parameter axisParameters[]={Parameter(),Parameter(),Parameter(),Parameter(),Parameter()};


void saveTrackPresets(char data){
	File settingsFile = SD.open("TRACK/default.txt");
	settingsFile.print(data);

}
void initSession(char bane[]) {
		strcpy(sessionName, bane);
		temp = String("/SESSIONS/" + String(bane) )	;
		char charBuf[temp.length() + 1];
		temp.toCharArray(charBuf, temp.length() + 1);
		SD.mkdir(charBuf);
		SD.remove("startUp.txt");
		startUpFile = SD.open("startUp.txt", FILE_WRITE);
		startUpFile.print(sessionName);
		startUpFile.print("\n");
		startUpFile.print(presetName);
		startUpFile.print("\n");
		startUpFile.print(snapShot);
		startUpFile.close();
		Serial.println("DIRECTORY "+String(sessionName)+" created");
		Serial.println("startUp.txt created");
		snapShot = 0;     
}

void savePreset(){
	String temp = String("/" + String("PRESETS") + "/" + String(presetName) + ".txt");
	// Serial.println(temp);
	char charBuf[temp.length() + 1];
	temp.toCharArray(charBuf, temp.length() + 1);
	SD.remove(charBuf);
	presetFile=SD.open(charBuf, FILE_WRITE);
	for(int i=0; i<7; i++){	
	    // presetFile.print(tracks[i]->parameters[5]->value);
	    // presetFile.print('#');
	    // presetFile.print(tracks[i]->parameters[6]->value);
	    // presetFile.print('#');
	    Serial.print("trak"+String(i)+" note -> ");
	    Serial.print(String(tracks[i]->parameters[7]->value));
	    Serial.print(" chan -> ");
	    Serial.println(String(tracks[i]->parameters[8]->value));

	    presetFile.print(tracks[i]->parameters[7]->value);
	    presetFile.print('#');
	    presetFile.print(tracks[i]->parameters[8]->value);
	    presetFile.print('#'); 
	    // presetFile.print(tracks[i]->parameters[9]->value);
	    // presetFile.print('#');
	    presetFile.print('-');
	}
	    presetFile.print('$');

	strcpy(allPresets[nPresets],presetName);
  	nPresets++;
	presetFile.close();
}

void takeSnapShot(bool isReplace){
	if (!isReplace)
	{
  		playingSnapShot=nSnapShots;		
		snapShot=nSnapShots++;

		
	}else{

		snapShot=playingSnapShot;

	}
	String temp = String("/" + String("SESSIONS") + "/" + String("DEFLT") + "/" + String(snapShot) + ".txt");
	// Serial.println(temp);
	char charBuf[temp.length() + 1];
	temp.toCharArray(charBuf, temp.length() + 1);
	SD.remove(charBuf);

	presetFile=SD.open(charBuf, FILE_WRITE);
	for(int i=0; i<7; i++){
		for(int p=0; p<10; p++){
			presetFile.print(tracks[i]->parameters[p]->value);
			presetFile.print('+');
			presetFile.print(tracks[i]->parameters[p]->lfo.wave);
			presetFile.print('#');
			presetFile.print(tracks[i]->parameters[p]->lfo.division);
			presetFile.print('#');
			presetFile.print(tracks[i]->parameters[p]->lfo.amp);
			presetFile.print('#');
			presetFile.print(tracks[i]->parameters[p]->lfo.dc);
			presetFile.print('#'); 
			presetFile.print(tracks[i]->parameters[p]->lfo.pwm_option);
			presetFile.print('#');
			presetFile.print(tracks[i]->style);
			presetFile.print('<');	
		}
		presetFile.print('|');	

	   
	}

	presetFile.print('>');	
	for(int p=0; p<5; p++){
			presetFile.print(fillParameters[p].value);
			presetFile.print('*');
		}
	presetFile.print('&');	
	for(int p=0; p<3; p++){
			presetFile.print(axisParameters[p].value);
			presetFile.print('?');
			presetFile.print(axisParameters[p].lfo.wave);
			presetFile.print('!');
			presetFile.print(axisParameters[p].lfo.division);
			presetFile.print('!');
			presetFile.print(axisParameters[p].lfo.amp);
			presetFile.print('!');
			presetFile.print(axisParameters[p].lfo.dc);
			presetFile.print('!'); 
			presetFile.print(axisParameters[p].lfo.pwm_option);
			presetFile.print('!');
		}
	
	presetFile.print('&');	
	for(int p=0; p<5; p++){
			presetFile.print(cutParameters[p]->value);
			presetFile.print('@'); 
			presetFile.print(cutParameters[p]->lfo.wave);
			presetFile.print('/');
			presetFile.print(cutParameters[p]->lfo.division);
			presetFile.print('/');
			presetFile.print(cutParameters[p]->lfo.amp);
			presetFile.print('/');
			presetFile.print(cutParameters[p]->lfo.dc);
			presetFile.print('/'); 
			presetFile.print(cutParameters[p]->lfo.pwm_option);
			presetFile.print('/');
		}
	
	presetFile.print('$');	
	presetFile.close();
}

void loadSDSnapshots(){
	String temp = String("/" + String("SESSIONS") + "/" + String("DEFLT"));

	char charBuf[temp.length() + 1];
	temp.toCharArray(charBuf, temp.length() + 1);
	snapshotFile = SD.open(charBuf);

	while (true) {
		File entry =  snapshotFile.openNextFile();
		if (! entry) {
			// no more files
			Serial.println("**no more snapShot**");
			break;
		}
		Serial.print(entry.name());
		
		nSnapShots++;
		snapShot=nSnapShots;
		entry.close();
	}
	snapshotFile.close();
	Serial.print(nSnapShots);

}



void saveStyle(){
	char nBuf[9]="";

	strncpy(nBuf, rythmName, 8);
	String temp = String("/" + String("STYLES") + "/" + nBuf +  ".txt");
	Serial.println(temp);
	char charBuf[temp.length() + 1];
	temp.toCharArray(charBuf, temp.length() + 1);
	SD.remove(charBuf);
	presetFile=SD.open(charBuf, FILE_WRITE);
	presetFile.print(rythmName);	
	presetFile.print("$");	
	String test="";

	bool isRepeat=false;
	for (int t = 0; t < 7; ++t)
	{

		for (int c = 0; c < 9; ++c)
			{
				byte count=0;
				byte value=1;
				byte oldValue=0;

				for (int i = 0; i < 32; ++i)
				{
					oldValue=value;
					value=memoryS[t]->weights[c][i];

					 if (value==oldValue)
					 { 
					 	isRepeat=true;
					 }else{
					 	isRepeat=false;

					 }
					 if (isRepeat)
					 {

					 	count++;
						
					 }else{
					 	
					 	if (count>0){ presetFile.print(count+1); test+=String(count+1);}
					 	switch(value){
					 		case 0:
					 			presetFile.print("a");	
					 			test+="a";	
					 		break;
					 		case 85:
					 			presetFile.print("b");	
					 			test+="b";	
					 		break;
					 		case 170:
					 			presetFile.print("c");	
					 			test+="c";	
					 		break;
					 		case 255:
					 			presetFile.print("d");	
					 			test+="d";	
					 		break;
					 	}
						count=0;
						
					 }

				}
				if (count>0){ presetFile.print(count+1); test+=String(count+1);}

				presetFile.print(",");	

		}
		presetFile.print("#");	

	}	

	presetFile.close();
	Serial.println(test);
	// strcpy(allPresets[nPresets],presetName);
}

void loadStyleTrack(byte nStyle, byte track){
	strcpy(tmpChar,"/STYLES/");
	strcat(tmpChar , StyleNames[nStyle].path);
	settingsFile = SD.open(tmpChar);
	byte array=0;
	byte trck=0;
	strcpy(tmpChar,"");
	char character;

	strcpy(memoryS[track]->name, StyleNames[nStyle].name);
	while (settingsFile.available()) {
				character = settingsFile.read();
				if (character!='#' && character!='$' && character!=',')
			 	{
			 		temp+=character;

			 	}else{
			 		if (character=='#')
			 		{
			 			trck++;
			 			temp="";
			 			

			 		}
			 		if (character=='$')
			 		{
			 			strcpy(tmpChar,"");
			 			temp="";
			 		}

			 		if (character==',' )
				 	{	
						
						if (trck==track)
						{
							char charBuf[temp.length() + 1];	
							temp.toCharArray(charBuf, temp.length() + 1);
							decompress(charBuf, track, array);
							temp="";	
					 		array++;
					 		if (array>=9)
					 		{
					 			break;
					 		}
						}
			 			temp="";
				 		
				 		


				 	}

			 	}

			}
	settingsFile.close();
}
void applyTrackSetting(byte type, byte track, byte parameter, byte lfo, byte value){
	
	switch (type) {
	    case 0:
	    	switch(parameter){
	    		case 0:tracks[track]->parameters[parameter]->value = value;break;
	    		case 1:tracks[track]->parameters[parameter]->value = value;break;
	    		case 2:break;
	    		case 3:break;
	    		case 4:tracks[track]->parameters[parameter]->value = value;break;
	    	}
	    	break;

	    case 1:
	    	switch (lfo) {
	    	    case 0: tracks[track]->parameters[parameter]->lfo.wave = value;break;
	    	    case 1: tracks[track]->parameters[parameter]->lfo.division = value;break;
	    	    case 2: tracks[track]->parameters[parameter]->lfo.amp = value;break;
	    	    case 3: tracks[track]->parameters[parameter]->lfo.dc = value;break;
	    	    case 4: tracks[track]->parameters[parameter]->lfo.pwm_option = value;break;
	    	}
	    break;
	    case 2:fillParameters[parameter].value = value;break;
	    case 3:tracks[track]->style = value;  break;
	    case 4:axisParameters[parameter].value = value;break;
	    case 5:
	    	switch (lfo) {
	    	    case 0: axisParameters[parameter].lfo.wave = value;break;
	    	    case 1: axisParameters[parameter].lfo.division = value;break;
	    	    case 2: axisParameters[parameter].lfo.amp = value;break;
	    	    case 3: axisParameters[parameter].lfo.dc = value;break;
	    	    case 4: axisParameters[parameter].lfo.pwm_option = value;break;
	    	} 
	    case 6: cutParameters[parameter]->value = value; break;
	    case 7:
	    	switch (lfo) {
	    	    case 0: cutParameters[parameter]->lfo.wave = value;break; 
	    	    case 1: cutParameters[parameter]->lfo.division = value;break;
	    	    case 2: cutParameters[parameter]->lfo.amp = value;break;
	    	    case 3: cutParameters[parameter]->lfo.dc = value;break;
	    	    case 4: cutParameters[parameter]->lfo.pwm_option = value;break;
	    	}

	    
	}

}
void readSDSnapShot() {
	String temp = String("/" + String("SESSIONS") + "/" + String(sessionName) + "/" + String(playingSnapShot) + ".txt");
	char charBuf[temp.length() + 1];
	temp.toCharArray(charBuf, temp.length() + 1);
	settingsFile = SD.open(charBuf);
	String settingName;
  	String settingValue;
	if(settingsFile){
		byte track=0;
		byte parameter=0;
		byte lfo=0;
		char character;
		while (settingsFile.available()) {
			character = settingsFile.read();
			if(character!='#' 
				&& character!='|' 
				&& character!='>' 
				&& character!='+' 
				&& character!='<' 
				&& character!='&' 
				&& character!='!' 
				&& character!='?'
				&& character!='@'
				&& character!='/'
				){
			     settingValue+=character;
			}

			if(character=='+'){
			    applyTrackSetting(0, track, parameter, lfo, byte(String(settingValue).toInt()));
			    settingValue="";
			    lfo=0;

			}
			if(character=='#'){

			    applyTrackSetting(1, track, parameter, lfo, byte(String(settingValue).toInt()));
			    settingValue="";
			    lfo++;
			    // parameter++;

			}
			if(character=='*'){
			    applyTrackSetting(2, track, parameter, lfo, byte(String(settingValue).toInt()));
			    settingValue="";
			    parameter=0;
			    lfo++;

			}
			if(character=='<'){
			    applyTrackSetting(3, track, parameter, lfo, byte(String(settingValue).toInt()));
			    settingValue="";
			    parameter++;
			    lfo=0;

			}
			if(character=='?'){
			    applyTrackSetting(4, track, parameter, lfo, byte(String(settingValue).toInt()));
			    settingValue="";
			    parameter++;
			    lfo=0;

			}
			if(character=='!'){

			    applyTrackSetting(5, track, parameter, lfo, byte(String(settingValue).toInt()));
			    settingValue="";
			    lfo++;

			}
			if(character=='@'){
			    applyTrackSetting(6, track, parameter, lfo, byte(String(settingValue).toInt()));
			    settingValue="";
			    parameter++;
			    lfo=0;

			}
			if(character=='/'){

			    applyTrackSetting(7, track, parameter, lfo, byte(String(settingValue).toInt()));
			    settingValue="";
			    lfo++;

			}
			if(character=='|' ){track++; parameter=0; };
			if(character=='&' ){parameter=0; };
			if(character=='>' ){parameter=0; };
			if(character=='+' ){lfo=0;};
			if(character=='$' ){break;};

		}

		
	}
    settingsFile.close();
    for (int i = 0; i < 7; ++i)
    {
    	loadStyleTrack( tracks[i]->style, i);

    }

}


void initCard() {
	SD.mkdir("SESSIONS");
	SD.mkdir("/SESSIONS/DEFLT");
	SD.mkdir("PRESETS");
	SD.mkdir("STYLES");
	SD.mkdir("SNAPSHOTS/DEFLT");
	SD.remove("startUp.txt");
	startUpFile = SD.open("startUp.txt", FILE_WRITE);
	startUpFile.print(sessionName);
	startUpFile.print("\n");
	startUpFile.print(presetName);
	startUpFile.print("\n");
	startUpFile.print(snapShot);
	startUpFile.close();
	Serial.println("DIRECTORY "+String(sessionName)+" created");
	Serial.println("STARTUP.txt created");
	snapShot = 0;     
}



void applySetting(byte track, byte item, byte value){
		
	switch (item) {
	    case 0:tracks[track]->parameters[7]->value=value; Serial.print("TRACK " + String(track)+ "IS NOW NOTE" + String(value));break;
	    case 1:tracks[track]->parameters[8]->value=value; Serial.print("TRACK " + String(track)+ "IS NOW CHANNEL" + String(value));break;
	    // case 2:tracks[track]->parameters[7]->value=value;break;
	    // case 3:tracks[track]->parameters[8]->value=value;break;
	    
	}

}


void readSDPreset(char presetName[]) {
	String temp = String("/" + String("PRESETS") + "/" + String(presetName) + ".txt");
	Serial.print(temp);
	char charBuf[temp.length() + 1];
	temp.toCharArray(charBuf, temp.length() + 1);
	settingsFile = SD.open(charBuf);
	String settingName;
  	String settingValue;
  	byte chan;
  	byte note;
  	byte mult;
  	byte step;
	if(settingsFile){
		byte i=0;
		byte item=0;
		char character;
		while (settingsFile.available()) {
			character = settingsFile.read();
				
				Serial.print(character);

			if(character!='#' && character!='-'){
			     settingValue+=character;
			}

			if(character=='#'){
				Serial.println("#####");
			    applySetting(i, item, byte(String(settingValue).toInt()));
			    settingValue="";
			    item++;
			}
			if(character=='-'){
				Serial.println("next");
			    i++;
			    item=0;

			}
			
			if(character=='$'){

				break;

			};

		}

		
	}
    settingsFile.close();


}



void readSDStartup() {
	startUpFile = SD.open("STARTUP.TXT");
	if(startUpFile){
		byte i=0;
		byte item=0;
		char character;
		while (startUpFile.available()) {
			character = startUpFile.read();
			if(character=='\n'){item++; i=0; character = startUpFile.read();};
			if(item==0){
				sessionName[i]=sessionName[i]=character;
			}else if(item==1){
				presetName[i]=presetName[i]=character;
			}else if(item==2){
				
				snapShot=int(String(character).toInt());
				break;
			}
			i++;
		}
		
	}else{
		startUpFile.close();
		initCard();
		savePreset();
	}

}

void loadSDPresets(){
	presetFile=SD.open("/PRESETS");
	while (true) {
		File entry =  presetFile.openNextFile();
		if (! entry) {
			// no more files
			Serial.println("**no more presets**");
			break;
		}
		for(int i=0; i<5; i++){
			allPresets[nPresets][i]=entry.name()[i];
		}
		nPresets++;
		entry.close();
	}
	presetFile.close();
	readSDPreset("DEFLT");

}



void loadStyle(byte nStyle){
	
	char character;
	for (int i = 0; i < 7; ++i)
	{
		loadStyleTrack(nStyle, i);
	}
	
}

void loadSDStyles(){
	styleFile=SD.open("/STYLES");
	
	while (true) {
		File entry =  styleFile.openNextFile();
		if (!entry) {
			// no more files
			Serial.println("**no more Styles**");
			break;
		}
		
			String temp = String("/" + String("STYLES") + "/" + String(entry.name()));
			char charBuf[temp.length() + 1];
			temp.toCharArray(charBuf, temp.length() + 1);
			settingsFile = SD.open(charBuf);
			char character;
			String atmp="";
			
			byte array=0;
			byte instrument=0;
			while (settingsFile.available()) {
				character = settingsFile.read();
				if (character!='#' && character!='$' && character!=',')
			 	{
			 		atmp+=character;

			 	}else{
			 		

				 	if (character=='$')
				 	{	
						char charBuf[atmp.length() + 1];
						atmp.toCharArray(charBuf, atmp.length() + 1);

						strncpy(StyleNames[nStyles].name, charBuf, 16); //OK BUT SHITTY
						strcpy(StyleNames[nStyles].path, entry.name());
				 		// instrument++;
				 		atmp="";
				 		break;
				 	}

			 	}
			 	

			 	

			}
			nStyles++;
			 	
		entry.close();
	}
	styleFile.close();
 	loadStyle(2);
}
