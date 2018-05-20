
Encoder knobOne(3,2);
Encoder knobTwo(6, 8 );
Encoder knobThree(5, 4);
Encoder knobFour(9,11);
Encoder knobFive(15,20);

Encoder* encoders[6]={&knobOne,&knobTwo,&knobThree,&knobFour, &knobFive, };
long positions[5] ={0,0,0,0,0};

int checkDirection(long oldPos, long newPosToCheck ){
		// printControl();
		// showChanged=false;
		if (oldPos<newPosToCheck)
		{
			// Serial.print("+");
			return 1;
		}else{
			// Serial.print("-");

			return -1;
		}


	}


// byte rotateVar(byte *var,byte inc, byte max){
// 	byte varto=&var;
// 	varto=
// }