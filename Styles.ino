void loadStyles() {
// char character;
// char prob[4];
// byte nItem=0;
// byte gen = 0;
// byte array = 0;
// int element = 0;
// // byte numPart=0;
// byte instrument = 0;
// bool reading = false;
// while (true) {

// File entry =  root.openNextFile();
// if (! entry) {
// 	// no more files
// 	Serial.println("**nomorefiles**");
// 	break;
// }

// // Serial.println(entry.name());
// // styles[gen].init(entry.name());

// // styles[gen].number = gen;
// if (entry && entry.name()[0]!='.') {
// 	while (entry.available() && gen<7) {
// 		character = entry.read();
// 		if (character == '|')
// 			{
// 			//character = entry.read();
// 			element = 0;
// 			reading = true;
// 			character = entry.read();
			
// 			}
// 		// Serial.print(character);
// 		if (reading) {
// 			if (character != ',') {
// 					prob[nItem]=character;
// 					nItem++;
// 				} else if (character==',') {
					
// 					prob[nItem]='\0';

// 					// Serial.print("->");
// 					// allStyles[gen][instrument][array][element] = String(prob).toInt();
// 					switch ( String(prob).toInt()) {
// 					    case 0:
// 					      styles[gen].probability[instrument][array][element] = 0;

// 					      break;
// 					    case 85:
// 					      styles[gen].probability[instrument][array][element] = 1;

// 					      // allStyles[gen][instrument][array][element] = &z;
// 					      // do something
// 					      break;
// 					    case 170:
// 					      styles[gen].probability[instrument][array][element] = 2;
					    	
// 					      // allStyles[gen][instrument][array][element] = &z;
// 					      // do something
// 					      break;
// 					    case 255:	
// 					      styles[gen].probability[instrument][array][element] = 3;
					    	
// 					      // allStyles[gen][instrument][array][element] = &z;
// 					      // do something
// 					      break;
// 					    default:
// 					    break;
// 					      // do something
// 					}
// 					// Serial.println(entry.name());
// 					// Serial.print("instrument " + String(instrument));
// 					// Serial.print(" - ");
// 					// Serial.print("prob "+ String(prob));
// 					// Serial.print(" - ");
// 					// // Serial.print("item "+ String(allStyles[gen].probability[array][element]));
// 					// Serial.print(" - ");
// 					// Serial.print("element " + String(element));
// 					// Serial.print(" - ");
// 					// Serial.print("array " + String(array));
// 					// delay(100);
// 					nItem=0;
// 					element++;
// 				}
// 			}
			
// 			if (character  == '\t' || character=='/') {
				
// 					prob[nItem]='\0';

// 					// Serial.print("->");
// 					// allStyles[gen][instrument][array][element] = String(prob).toInt();
// 					// Serial.println(entry.name());
// 					// Serial.print("instrument " + String(instrument));
// 					// Serial.print(" - ");
// 					// Serial.print("prob "+ String(prob));
// 					// Serial.print(" - ");
// 					// // Serial.print("item "+ String(allStyles[gen].probability[array][element]));
// 					// Serial.print(" - ");
// 					// Serial.print("element " + String(element));
// 					// Serial.print(" - ");
// 					// Serial.print("array " + String(array));
// 					// delay(100);
// 				prob[nItem]='\0';
// 				nItem=0;
// 				reading = false;
// 				// array=0;
// 				array++;
// 				// element=0;
// 				if(array==7){
// 				    instrument++;
// 				    array=0;
// 				}
// 				// instrument++;	
// 				// delay(800);
// 				strcpy(prob, "");
// 				// Serial.println(" " );
// 				// // Serial.println("new " );
// 				// Serial.println("array " + String(array));
// 				// Serial.println("gen " + String(gen));
// 				// Serial.println("instrument " + String(instrument));

// 			}
			
// 			// delay();

// 		}
// 		entry.close();
// 		// delay(800);
// 		gen++;
// 		instrument=0;
// 		array=0;
// 		nStyles++;
// 	}
// 	// styles[0].printProb();
// }
}