#include <Arduino.h>
#ifndef Scales_h
#define Scales_h

class Scales{
   public:
	 String scaleNames[21] = {	"chromatic", "wholetone", "minor", "harmminor", "pentmin", "major", "harmmaj", "pentmaj", "diminish", "fifths", "blues", "arabian", "persian", "oriental", "javanese", "jewish", "gypsy", "dorian", "ethiopian", "cutter" };
	 String scaleShortNames[21] = {	"CHR", "WHT", "MIN", "HMI", "PMI", "MAJ", "HMA", "PMA", "DIM", "FIF", "BLU", "ARB", "PRS", "ORT", "JAV", "JWS", "GYP", "DOR", "ETH"," CUT" };
 

	  Scales() {
	  }


	   typedef struct
		{

			const String name;
			const int count;
			const byte notes[16];

		} ScaleDef;

			 ScaleDef chromatic = {"" ,12, {0,1,2,3,4,5,6,7,8,9,10,11} }  ;
			 ScaleDef whole_tone  ={"" , 7 , {0,2,4,6,8,10,12    } };
			 ScaleDef minor  ={"" ,8 , { 0,2,3,5,7,8,10,12    } } ;
			 ScaleDef harmonic_minor   ={"" ,8 , { 0,2,3,5,7,8,11,12    } };
			 ScaleDef pentatonic_minor   ={"" ,7 , {0,3,5,7,10,12,15} };
			 ScaleDef major  ={"" ,8 , {0,2,4,5,7,9,11,12} } ;
			 ScaleDef harmonic_major  ={"" ,8 , { 0,2,4,5,8,9,11,12    } } ;
			 ScaleDef pentatonic_major  ={"" ,7 , {0,2,4,7,9,12,14} } ;
			 ScaleDef diminished  ={"" ,7 , {0,2,4,7,9,12,14} } ;
			 ScaleDef fifths  ={"" ,7 , {-12,-5,0,7,12,19,24} } ;
			 ScaleDef blues  ={"" ,7 , { 0,3,5,6,7,10,12    } } ;
			 ScaleDef arabian   ={"" ,8 , {0,2,4,5,6,8,10,12    } } ;
			 ScaleDef persian  ={"" ,8 , { 0,1,4,5,6,8,11,12    } } ;
			 ScaleDef oriental  ={"" ,8 , {  0,1,4,5,6,9,10,12   } } ;
			 ScaleDef javanese  ={"" , 8 , { 0,1,3,5,7,9,10,12    } };
			 ScaleDef jewish  ={"" ,8 , {   0,1,4,5,7,8,10,12  } } ;
			 ScaleDef gypsy  ={"" ,8 , {   0,1,4,5,7,8,11,12  } } ;
			 ScaleDef dorian  ={"" ,8 , {   0,2,3,5,7,9,10,12  } } ;
			 ScaleDef ethiopian  ={"" ,8 , {  0,2,4,5,7,8,11,12   } } ;
			 ScaleDef cutter  ={"" ,16 , {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15} } ;

		ScaleDef scaleList[20] = {
				chromatic,
				whole_tone,
				minor,
				harmonic_minor,
				pentatonic_minor,
				major,
				harmonic_major,
				pentatonic_major,
				diminished,
				fifths,
				blues,
				arabian,
				persian,
				oriental,
				javanese,
				jewish,
				gypsy,
				dorian,
				ethiopian,
				cutter
		};
		ScaleDef getScale(int w){
			return scaleList[w];

		}






	   const String classname() { return "scale";}

};

#endif
