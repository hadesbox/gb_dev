#include <Arduino.h>
#include <SD.h>

#ifndef Gender_h
#define Gender_h

class Gender{
   
	public:
	char name[30];
	byte number;
	byte probability[7][9][32];

	Gender() {

	}
	void init(char nameIn[]){
		strcpy(name, nameIn);
	}
	
	void printProb(){
		for (int i = 0; i < 7; ++i)
		{
			for (int a = 0; a < 9; ++a)
			{
					for (int j = 0; j < 32; ++j)
					{
						Serial.println((probability[i][a][j]));
						// Serial.print(sizeof(probability[i][a][j]));
						Serial.print(" - ");
					}
					Serial.println(" ");

			}
		}
		

	}
	// ScaleList getScale;
	   const String classname() { return "scale";}

};

#endif
