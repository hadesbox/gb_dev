#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>


#include "Oled_Screen.h"


Oled_Screen :: Oled_Screen(byte oled_mosi, byte oled_clk, byte oled_dc, byte oled_cs, byte oled_reset) :
			Adafruit_SH1106(oled_mosi, oled_clk, oled_dc, oled_reset, oled_cs){
			};
void Oled_Screen :: fail(){

		String i="CARD FAIL";
		this->setTextColor(WHITE);
		this->setTextSize(1);
		this->setCursor(0,5);
		this->print(i);
		this->display();
}
void Oled_Screen :: init(){
	tempoState=false;
		this->begin(SH1106_SWITCHCAPVCC);
		this->clearDisplay();
		static const unsigned char PROGMEM logo16_glcd_bmp[]={
B11111111,B11111111,B00011111,B00011000,B00111111,B11111111,B11111111,B11111111,B11111111,B11100011,B00011100,B11111111,B10000001,B11011100,B01111111,B11111111,
B11111111,B11111000,B00011111,B00110000,B01111111,B11111111,B11111111,B11111111,B11111111,B11000111,B00111000,B01111111,B10011111,B11001110,B00111111,B11111111,
B11111111,B11110001,B11001111,B10000000,B11111111,B11111111,B11111111,B11111111,B11111111,B10011110,B01111000,B01111111,B10010000,B11001111,B00111111,B11111111,
B11110000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000011,B11111111,B11111111,B10011100,B11110001,B11111111,B10110000,B11001111,B10001111,B11111111,
B11110111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111011,B11111111,B11111111,B00110000,B11110011,B11111111,B10011111,B11001111,B10000111,B11111111,
B11110111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111011,B11111111,B11111111,B00110011,B11110111,B11111111,B10011111,B11000011,B11000111,B11111111,
B11110111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111011,B11111111,B11111000,B00000000,B00000000,B00000001,B10011000,B01110011,B11100011,B11111111,
B11110111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111011,B11111111,B11110001,B11111111,B11001000,B00000000,B00000000,B01111011,B11110011,B11111111,
B11110111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111011,B11111111,B11100110,B00000000,B00000011,B11111111,B11000111,B11111011,B11111011,B11111111,
B11110111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111011,B11111111,B11001100,B00000000,B00000000,B00000000,B00110011,B11111011,B11111001,B11111111,
B11110111,B11000011,B00001100,B11001000,B00111000,B01100000,B11111011,B11111111,B10011000,B00000000,B00000000,B00000000,B00011001,B11111000,B11111001,B11111111,
B11110111,B10000001,B00001100,B11001000,B00011000,B01100000,B01111011,B11111111,B10010000,B00000011,B11111100,B00000110,B00001001,B00000000,B00111001,B11111111,
B11110111,B10011001,B00111100,B01001001,B10011001,B11100110,B01111011,B11111111,B00100000,B00000111,B11111110,B00111111,B11000100,B00001000,B10011001,B11111111,
B11110111,B10011001,B00111100,B01001001,B10011001,B11100110,B01111011,B11111111,B00100000,B00001111,B11111100,B11111111,B11100100,B00000000,B11011000,B11111111,
B11110111,B10011111,B00001100,B01001001,B10011000,B01100000,B01111011,B11111111,B00100000,B00011000,B11111100,B11111111,B11110110,B10000000,B11011100,B11111111,
B11110111,B10010001,B00001100,B00001001,B10011000,B01100000,B11111011,B11111111,B00100000,B00011000,B11111001,B11111000,B11110110,B00000001,B11011110,B01111111,
B11110111,B10010001,B00111100,B10001001,B10011001,B11100110,B01111011,B11111111,B00100000,B00111000,B11111001,B11111000,B11100110,B00000011,B11001110,B01111111,
B11110111,B10011001,B00111100,B10001001,B10011001,B11100110,B01111011,B11111111,B00100000,B00111111,B11111001,B11111111,B11100111,B01111111,B11001111,B01111111,
B11110111,B10011001,B00111100,B10001001,B10011001,B11100110,B01111011,B11111111,B00100000,B00011111,B11111001,B11111111,B11101111,B00111111,B11001111,B01111111,
B11110111,B10000001,B00000100,B11001000,B00011000,B00100110,B01111011,B11111111,B00010000,B00011111,B11111001,B11111111,B11001111,B00111111,B11001110,B01111111,
B11110111,B11000101,B00000100,B11001000,B00111000,B00100110,B01111011,B11111110,B00011100,B00000000,B00000000,B00011111,B10011111,B00111111,B11100000,B11111111,
B11110111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111011,B11111110,B01000111,B11100000,B00000000,B00000000,B00111111,B00011111,B11100100,B11111111,
B11110111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111011,B11111100,B11100011,B11111111,B11111111,B11111111,B11111110,B00011111,B11110110,B01111111,
B11110111,B10000011,B00001100,B11001000,B00111000,B01100000,B11111011,B11111100,B01110001,B11111111,B11111111,B11111111,B11111110,B01011111,B11110110,B00111111,
B11110111,B10000001,B00001100,B11001000,B00011000,B01100000,B01111011,B11111000,B01111000,B11111111,B11111111,B11111111,B11111110,B01011111,B11110011,B00111111,
B11110111,B10011001,B00111100,B01001001,B10011001,B11100110,B01111011,B11111010,B11110000,B00100000,B00001111,B11111111,B11111100,B11001111,B11110111,B10111111,
B11110111,B10011001,B00111100,B01001001,B10011001,B11100110,B01111011,B11111000,B01110111,B00000000,B00000000,B00000000,B11111000,B11001000,B00100111,B10011111,
B11110111,B10000011,B00001100,B01001001,B10011000,B01100000,B01111011,B11111001,B10010111,B00111111,B11111111,B10000000,B00000001,B11000000,B00010011,B10011111,
B11110111,B10000001,B00001100,B00001001,B10011000,B01100000,B11111011,B11111100,B00010111,B00111111,B11111111,B11111111,B11000111,B11000000,B10000111,B11011111,
B11110111,B10011001,B00111100,B10001001,B10011001,B11100110,B01111011,B11111110,B00000111,B01111111,B11111111,B11111111,B11111111,B11000000,B00000111,B10011111,
B11110111,B10011001,B00111100,B10001001,B10011001,B11100110,B01111011,B11111110,B01000111,B01110000,B00000000,B00111111,B11111111,B11000000,B00000111,B00011111,
B11110111,B10011001,B00111100,B10001001,B10011001,B11100110,B01111011,B11111110,B01001111,B01110011,B11000000,B00000011,B11111111,B10011111,B11100110,B00111111,
B11110111,B10000001,B00000100,B11001000,B00011000,B00100110,B01111011,B11111110,B01000001,B00110111,B11011111,B00100000,B11111111,B10011111,B11100000,B01111111,
B11110111,B10000011,B00000100,B11001000,B00111000,B00100110,B01111011,B11111110,B01001000,B00000111,B10011111,B00111100,B01111111,B10111111,B11110011,B00111111,
B11110111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111011,B11111110,B00000010,B00000000,B00000000,B00111100,B00111111,B10111100,B00110011,B10011111,
B11110111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111011,B11111110,B11100000,B00110000,B00000000,B00001101,B10111111,B00111000,B00100111,B11011111,
B11110111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111011,B11111110,B01110000,B00100111,B10111110,B00000000,B10011111,B00111000,B00100111,B11011111,
B11110111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111011,B11111100,B01111110,B00000111,B00111110,B01111000,B00011111,B00111001,B11110011,B10011111,
B11110111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111011,B11111101,B11111111,B10000000,B00000010,B01111101,B00011111,B00111111,B11110011,B00011111,
B11110111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111011,B11111100,B10000111,B00100000,B00000000,B00000001,B10011111,B00011100,B00000000,B00011111,
B11110000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000011,B11111100,B11000010,B00101111,B01111110,B10000000,B10011110,B00011100,B01000000,B10011111,
B11111111,B11111100,B11111111,B11011111,B11111111,B11111111,B11111111,B11111110,B00010010,B01101111,B01111110,B11111000,B00111110,B00011100,B00000011,B11011111,
B11111111,B11111100,B11111111,B11001111,B11111111,B11111101,B11100111,B11111111,B00000010,B00000000,B00000100,B11111011,B00111110,B10011000,B00000001,B11011111,
B11111111,B11111100,B11111111,B11001111,B11111111,B11111001,B11011011,B11111111,B10000001,B00111111,B00000000,B00111011,B00111110,B11001000,B00011001,B11011111,
B11111111,B11111110,B11111111,B10001111,B11111111,B11111101,B11011011,B11111111,B11110001,B01111111,B11111110,B00000000,B01111100,B11000000,B01111001,B10011111,
B11111111,B11111110,B01111110,B00000111,B11111111,B11111101,B11011011,B11111111,B11111000,B01111111,B11111111,B11110001,B11111100,B00001011,B11111011,B00011111,
B11111111,B11111110,B00000000,B00100111,B11111111,B11111101,B11011011,B11111111,B11000100,B01111111,B11111111,B11111111,B11111100,B00100011,B00000000,B00111111,
B11111111,B11111110,B00000001,B11110011,B11111111,B11111101,B11011011,B11111111,B00000000,B00000000,B00000011,B11111111,B11111101,B01100000,B00000000,B11111111,
B11111111,B11111111,B01111111,B11110011,B11111111,B11111101,B01100111,B11111110,B00100011,B11111111,B10000000,B00111111,B11111101,B11000000,B01101001,B11111111,
B11111111,B11111111,B00111111,B11111001,B11111111,B11111111,B11111111,B11111000,B11000111,B11111111,B11111110,B00000001,B11111000,B00001001,B01100011,B11111111,
B11111111,B11111111,B00111111,B11111100,B11111111,B11111111,B11111111,B11110001,B10001111,B11111111,B11111111,B11100000,B00111001,B11101111,B10000111,B11111111,
B11111111,B11111111,B00111111,B11111000,B01111111,B11111111,B11111111,B11100011,B10011111,B11111111,B11111111,B11111110,B00000001,B11100110,B00001111,B11111111,
B11111111,B11111111,B10011111,B11111000,B00111111,B11111111,B11111111,B10000111,B00111111,B11111111,B11111111,B11111111,B11000000,B01110000,B01111111,B11111111,
B11111111,B11111111,B10011111,B11110011,B00011111,B11111111,B11111111,B00001110,B01111111,B11111111,B11111111,B11111111,B10001110,B00111111,B11111111,B11111111,
B11111111,B11111111,B10011111,B11110011,B10001111,B11111111,B11111100,B00011110,B01111111,B11111111,B11111111,B11111111,B00011111,B00011111,B11111111,B11111111,
B11111111,B11111111,B11001111,B11000111,B11100011,B11111111,B11111100,B10011110,B00000000,B00001111,B11111111,B11111110,B00111111,B10011111,B11111111,B11111110,
B11111111,B11111111,B11000111,B00000111,B11110001,B11111111,B11111001,B00111100,B00000000,B00000000,B00111111,B11111100,B11111111,B00011111,B11111111,B11111100,
B11111111,B11111111,B11100000,B00011111,B11110000,B01111111,B11100010,B01111100,B11111111,B11111100,B00000000,B11111001,B11111110,B00001111,B11111111,B11111100,
B11111111,B11111111,B11110000,B01111111,B11110010,B00111111,B11000110,B01111101,B11111111,B11111111,B11110000,B00000011,B11111100,B11100111,B11111111,B11111001,
B11111111,B11111111,B11111001,B11111111,B11110011,B00001111,B10010000,B11111101,B11111111,B11111111,B11111111,B00000111,B11111001,B11100111,B11111111,B11100001,
B11111111,B11111111,B11111100,B11111111,B11100111,B11000001,B00010001,B11111101,B11111111,B11111111,B11111111,B11001111,B11110011,B11110011,B11111111,B11000011,
B11111111,B11111111,B11111110,B01111111,B11100111,B11110000,B00110001,B11111101,B11111111,B11111111,B11111111,B10011111,B11100011,B11111011,B11111111,B10000111,
B11111111,B11111111,B11111111,B00011111,B11001111,B11110110,B01110011,B11111101,B11111111,B11111111,B11111111,B00111111,B11100001,B11111001,B11111110,B00011111,
B11111111,B11111111,B11111111,B10001111,B10001111,B11110010,B01110011,B11111100,B00000000,B00000000,B00011110,B01111111,B11000000,B00000000,B11111100,B00011111,
};



  	this->drawBitmap(0, 0,  logo16_glcd_bmp, 128, 64, 1);
	this->display();

  	delay(500);
	this->clearDisplay();



}
void Oled_Screen :: drawParameter(byte xpos, byte ypos, byte w, byte h,String title, String text){
		String a=title;
		String b=text;

		this->setTextSize(1);
		this->setTextColor(WHITE);
		this->setCursor(xpos,ypos+1);


		this->fillRect(xpos, ypos, w, h, BLACK);
		this->print(b);

		this->setTextSize(2);
		this->setTextColor(WHITE);
		this->setCursor(xpos,ypos+10);

		this->fillRect(xpos, ypos+10, w, h/2, BLACK);

		this->print(a);
		this->display();
}
void Oled_Screen :: drawLFO(byte xpos, byte ypos, byte w, byte h,String title, String text){
		String a=title;
		String b=text;

		this->setTextSize(1);
		this->setTextColor(WHITE);
		this->setCursor(xpos,ypos+1);


		this->fillRect(xpos, ypos, w, h, BLACK);
		this->print(b);

		this->display();
}
void Oled_Screen :: drawParameterH(byte xpos, byte ypos, byte w, byte h,String title, String text){
		String a=title;
		String b=text;

		this->setTextSize(1);
		this->setTextColor(WHITE);
		this->setCursor(xpos,ypos);


		this->fillRect(xpos, ypos, 60, (h), BLACK);
		this->print(b);

		this->setTextSize(2);
		this->setTextColor(WHITE);
		this->setCursor(xpos+50,ypos);

		this->fillRect(xpos+50, ypos, 60, h, BLACK);

		this->print(a);
		this->display();
}

void Oled_Screen :: drawStyle(byte xpos, byte ypos, byte w, byte h, String text){
		String b=text;

		this->setTextSize(1);
		this->setTextColor(WHITE);
		this->setCursor(xpos,ypos+1);


		this->fillRect(xpos, ypos, w, h, BLACK);
		this->print(b);

		
		this->display();
}
void Oled_Screen :: drawStyleEdit(byte xpos, byte ypos, byte w, byte h, String text){
		String b=text;

		this->setTextSize(0);
		this->setTextColor(WHITE);
		this->setCursor(xpos,ypos+1);


		this->fillRect(xpos, ypos, w, h, BLACK);
		this->print(b);

		
		this->display();
}
void Oled_Screen :: drawParameterIcon(byte xpos, byte ypos , byte icon){
		if (icon==7 || icon ==13 || icon ==14)
		{
			this->fillRect(xpos, ypos, 8, 8, BLACK);			

		}else{
			this->fillRect(xpos, ypos, 25, 30, BLACK);			


		}
  		static const unsigned char PROGMEM kickIcon[]={B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000111,B11111110,B00000000,B00001111,B11111111,B00000000,B00011111,B11111111,B10000000,B00011111,B11111111,B10000000,B00111111,B11111111,B11000000,B00111111,B11111111,B11000000,B01111111,B11111111,B11100000,B11111111,B11111111,B11110000,B11111111,B11111111,B11110000,B01111111,B11111111,B11100000,B00111111,B11111111,B11000000,B00111111,B11111111,B11000000,B00011111,B11111111,B10000000,B00011111,B11111111,B10000000,B00001111,B11111111,B00000000,B00000111,B11111110,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,};
  		static const unsigned char PROGMEM snareIcon[]={B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000001,B10000000,B00000000,B00000001,B10000000,B00000000,B00000011,B11000000,B00000000,B00000011,B11000000,B00000000,B00000111,B11100000,B00000000,B00000111,B11100000,B00000000,B00001111,B11110000,B00000000,B00001111,B11110000,B00000000,B00011111,B11111000,B00000000,B00011111,B11111000,B00000000,B00111111,B11111100,B00000000,B00111111,B11111100,B00000000,B01111111,B11111110,B00000000,B01111111,B11111110,B00000000,B11111111,B11111111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,};
  		static const unsigned char PROGMEM clapIcon[]={B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B11111111,B11111111,B00000000,B11111111,B11111111,B00000000,B11111111,B11111111,B00000000,B11111111,B11111111,B00000000,B11111111,B11111111,B00000000,B11111111,B11111111,B00000000,B11111111,B11111111,B00000000,B11111111,B11111111,B00000000,B11111111,B11111111,B00000000,B11111111,B11111111,B00000000,B11111111,B11111111,B00000000,B11111111,B11111111,B00000000,B11111111,B11111111,B00000000,B11111111,B11111111,B00000000,B11111111,B11111111,B00000000,B11111111,B11111111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,};
  		static const unsigned char PROGMEM hatIcon[]={B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B01111111,B11111111,B10000000,B01111111,B11111111,B00000000,B00111111,B11111111,B00000000,B00111111,B11111110,B00000000,B00011111,B11111110,B00000000,B00011111,B11111100,B00000000,B00001111,B11111100,B00000000,B00001111,B11111000,B00000000,B00001111,B11111000,B00000000,B00011111,B11111000,B00000000,B00011111,B11111100,B00000000,B00111111,B11111100,B00000000,B00111111,B11111110,B00000000,B01111111,B11111110,B00000000,B01111111,B11111111,B00000000,B11111111,B11111111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,};
  		static const unsigned char PROGMEM hatOIcon[]={B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B01000000,B00000000,B00000000,B01000000,B00000000,B00000000,B11100000,B00000000,B00000000,B11100000,B00000000,B00000001,B11110000,B00000000,B00000001,B11110000,B00000000,B00000001,B11110000,B00000000,B00000011,B11111000,B00000000,B00000011,B11111000,B00000000,B00000111,B11111100,B00000000,B00001111,B11111110,B00000000,B00011111,B11111111,B00000000,B00011111,B11111111,B00000000,B00111111,B11111111,B10000000,B01111111,B11111111,B11000000,B11110000,B00000001,B11100000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,};
  		static const unsigned char PROGMEM tomIcon[]={B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000111,B00000111,B00000000,B00000111,B11011111,B00000000,B00000111,B11111111,B00000000,B00001111,B11111111,B00000000,B00001111,B11111111,B00000000,B00111111,B11111111,B11000000,B11111111,B11111111,B11110000,B11111111,B11111111,B11111000,B01111111,B11111111,B11110000,B01111111,B11111111,B11100000,B00111111,B11111111,B11100000,B00111111,B11111111,B11000000,B00111111,B11111111,B11000000,B00111111,B11111111,B11000000,B00111111,B11111111,B11000000,B01111111,B11111111,B11100000,B00111111,B11111111,B11100000,B00000001,B11111000,B00000000,B00000000,B11110000,B00000000,B00000000,B01100000,B00000000,B00000000,B01000000,B00000000,B00000000,B00000000,B00000000,};
  		static const unsigned char PROGMEM tomHiIcon[]={B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00011100,B00001110,B00000000,B00001111,B00111110,B00000000,B00001111,B11111100,B00000000,B00001111,B11111100,B00000000,B00001111,B11111100,B00000000,B00000111,B11111100,B00000000,B00001111,B11111110,B00000000,B00011111,B11111111,B10000000,B00111111,B11111111,B11000000,B01111111,B11111111,B11100000,B01111111,B11111110,B00000000,B00000001,B11110000,B00000000,B00000001,B11110000,B00000000,B00000000,B11100000,B00000000,B00000000,B01100000,B00000000,B00000000,B01100000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,};
  		static const unsigned char PROGMEM muteIcon[]={B11111111,B10011001,B10000001,B11000011,B11000011,B10000001,B10011001,B11111111,};
  		static const unsigned char PROGMEM snapShotIcon[]={B00000000,B11111110,B00000000,B00000011,B11111111,B10000000,B00001111,B11111111,B11100000,B00011111,B11111111,B11110000,B00111111,B11111111,B11111000,B00111110,B00111111,B11111000,B01111000,B00011111,B11111100,B01111000,B00001111,B11111100,B11111000,B00001111,B11111110,B11111000,B00001111,B11111110,B11111000,B00011111,B11111110,B11111100,B00011111,B11111110,B11111111,B11111111,B11111110,B11111111,B11111111,B11111110,B11111111,B11111111,B11111110,B01111111,B11111111,B11111100,B01111111,B11111111,B11111100,B00111111,B11111111,B11111000,B00111111,B11111111,B11111000,B00011111,B11111111,B11110000,B00001111,B11111111,B11100000,B00000011,B11111111,B10000000,B00000000,B11111110,B00000000,B00000000,B00000000,B00000000,};
  		static const unsigned char PROGMEM presetIcon[]={B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B01111100,B00111100,B00000000,B01111100,B01111110,B00000000,B01111100,B01111110,B00000000,B01111100,B01111110,B01111000,B01111100,B00111100,B11111100,B01111100,B00000000,B11111100,B01111100,B00000000,B11111100,B01111100,B00000000,B01111000,B01111100,B00111100,B00000000,B01111100,B01111110,B00000000,B01111100,B01111110,B00000000,B01111100,B01111110,B00000000,B01111100,B00111100,B00000000,B01111100,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,};  		
  		static const unsigned char PROGMEM fillIcon[]={B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B01111100,B00111100,B00000000,B01111100,B01111110,B00000000,B01111100,B01111110,B00000000,B01111100,B01111110,B01111000,B01111100,B00111100,B11111100,B01111100,B00000000,B11111100,B01111100,B00000000,B11111100,B01111100,B00000000,B01111000,B01111100,B00111100,B00000000,B01111100,B01111110,B00000000,B01111100,B01111110,B00000000,B01111100,B01111110,B00000000,B01111100,B00111100,B00000000,B01111100,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,};
  		static const unsigned char PROGMEM algoritmIcon[]={B00000000,B00000000,B00000000,B00000000,B00111100,B00000000,B00000000,B00111110,B00000000,B00000000,B01111110,B00000000,B00000000,B01111110,B00000000,B00000000,B01111110,B00000000,B00000000,B11111100,B00000000,B00000001,B11000000,B00000000,B00000011,B10000000,B00000000,B00000111,B00000000,B00000000,B01111110,B00000000,B00011110,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111100,B00011100,B00111111,B01111000,B00011100,B00011110,B00000000,B00011100,B00000000,B00000000,B00011100,B00000000,B00000000,B00111100,B00000000,B00000000,B01111110,B00000000,B00000000,B01111110,B00000000,B00000000,B01111110,B00000000,B00000000,B00111110,B00000000,B00000000,B00111100,B00000000,};
		static const unsigned char PROGMEM axisIcon[]={B00000000,B00011100,B00000000,B00000000,B00111110,B00000000,B00000000,B01111110,B00000000,B00000000,B01111110,B00000000,B00000000,B01111110,B00000000,B00000000,B01111110,B00000000,B00000000,B01111100,B00000000,B00000000,B11100000,B00000000,B00000000,B11100000,B00000000,B00000001,B11000000,B00000000,B00000001,B11000000,B00000000,B00000011,B10000000,B00000000,B00000011,B10000000,B00000000,B00000111,B00000000,B00000000,B00000111,B00000000,B00000000,B00001110,B00000000,B00000000,B00001110,B00000000,B00000000,B01111100,B00000000,B00001110,B01111100,B00000000,B00011110,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B01111000,B00000000,B00011110,B01111000,B00000000,B00011110,};
		static const unsigned char PROGMEM lfoIcon[]={B11111111,B00110001,B00100000,B00100100,B00100100,B00000100,B10001100,B11111111,};
		static const unsigned char PROGMEM midiIcon[]={B11000011,B10000001,B00100100,B00000000,B01000010,B00011000,B10000001,B11000011,};

  		if (icon==0)this->drawBitmap(xpos, ypos,  kickIcon, 24, 24, 1);
  		if (icon==1)this->drawBitmap(xpos, ypos,  snareIcon, 24, 24, 1);
  		if (icon==2)this->drawBitmap(xpos, ypos,  clapIcon, 24, 24, 1);
  		if (icon==3)this->drawBitmap(xpos, ypos,  hatIcon, 24, 24, 1);
  		if (icon==4)this->drawBitmap(xpos, ypos,  hatOIcon, 24, 24, 1);
  		if (icon==5)this->drawBitmap(xpos, ypos,  tomIcon, 24, 24, 1);
  		if (icon==6)this->drawBitmap(xpos, ypos,  tomHiIcon, 24, 24, 1);
  		if (icon==7)this->drawBitmap(xpos, ypos,  muteIcon, 8, 8, 1);
  		if (icon==8)this->drawBitmap(xpos, ypos,  snapShotIcon, 24, 24, 1);
  		if (icon==9)this->drawBitmap(xpos, ypos,  presetIcon, 24, 24, 1);
  		if (icon==10)this->drawBitmap(xpos, ypos, fillIcon, 24, 24, 1);
  		if (icon==11)this->drawBitmap(xpos, ypos, algoritmIcon, 24, 24, 1);
  		if (icon==12)this->drawBitmap(xpos, ypos, axisIcon, 24, 24, 1);
  		if (icon==13)this->drawBitmap(xpos, ypos, lfoIcon, 8, 8, 1);
  		if (icon==14)this->drawBitmap(xpos, ypos, midiIcon, 8, 8, 1);
  		
		
		this->display();
}
void Oled_Screen :: drawParameterInverted(byte xpos, byte ypos, byte w, byte h,String title, String text){
		String a=title;
		String b=text;

		this->setTextSize(2);
		this->setTextColor(BLACK);
		this->setCursor(xpos+1,ypos+2);


		this->fillRect(xpos, ypos, w, h, WHITE);
		this->print(b);

		this->setTextSize(1);
		this->setTextColor(WHITE);
		this->setCursor(xpos+1,ypos+18);

		this->fillRect(xpos, ypos+18, w, h/2, BLACK);

		this->print(a);
		this->display();
}


// void Oled_Screen :: drawParameter2(int xpos, int ypos, int w, int h,String title, String text){
// 		this->setTextSize(2);
// 		this->setTextColor(WHITE);
// 		this->setCursor(xpos+2,ypos+2);
// 		String a=title;

// 		this->fillRect(xpos, ypos, w, h, BLACK);
// 		this->print(a);

// 		this->setTextSize(2);
// 		this->setTextColor(WHITE);
// 		this->setCursor(xpos,ypos+22);
// 		String b=text;
// 		this->fillRect(xpos, ypos+22, w, h, BLACK);

// 		this->print(b);
// 		this->display();
// }

void Oled_Screen :: drawTextSquare(byte xpos, byte ypos, byte w, byte h,String title, String text){
		this->fillRect(xpos-2, ypos-11, w+1, h+1, BLACK);

		this->setTextSize(0);
		this->setTextColor(WHITE);
		this->setCursor(xpos,ypos-10);
		String a=title;
		this->print(a);
		this->fillRect(xpos-2, ypos-1, w, h, WHITE);
		this->setTextSize(0);
		this->setTextColor(BLACK);
		this->setCursor(xpos,ypos);
		String b=text;

		this->print(b);
		this->display();
}
void Oled_Screen :: fillBlank(byte xpos, byte ypos, byte w, byte h){
		this->fillRect(xpos-2, ypos-11, w, h*2, BLACK);

		this->display();
}

void Oled_Screen :: drawTextSquareInverted(byte xpos, byte ypos, byte w, byte h,String title, String text){
		this->fillRect(xpos-2, ypos-11, w, h, WHITE);
		this->setTextSize(0);
		this->setTextColor(BLACK);
		this->setCursor(xpos,ypos-10);
		String a=title;
		this->print(a);
		this->fillRect(xpos-2, ypos-1, w, h, BLACK);
		this->setTextSize(0);
		this->setTextColor(WHITE);
		this->setCursor(xpos,ypos);
		String b=text;

		this->print(b);
		this->display();
}
void Oled_Screen :: drawSnapshot(byte snp){
		this->fillRect(0, 18, 15, 9, BLACK);
		this->setTextSize(1);
		this->setTextColor(WHITE);
		this->setCursor(0,20);
		String a=String(snp);
		this->print(a);
		
		this->display();
}
void Oled_Screen :: clear(){
		this->clearDisplay();
		
}

void Oled_Screen :: drawOneStep(byte step, byte prob, byte y){
		this->fillRect(step*4, y, 4, 5, BLACK);
		this->fillRect(step*4, y+5-map(prob,0,255,1,5), 3, map(prob,0,255,1,5), WHITE);
		this->display();
}
void Oled_Screen :: drawOneStepEdit(byte step, byte prob, byte y){
		byte four;
		if (step%8==0)
		{
			four=1;
		}else{
			four=0;
		}
		this->fillRect(step*4, y, 4, 8, BLACK);
		this->fillRect(step*4, y+6-map(prob,0,255,1,6), 3, map(prob,0,255,1,6), WHITE);
		this->fillRect(step*4+(1), y+6, 1*four, 1*four, WHITE);
		
		this->display();
}
void Oled_Screen :: drawOneStepEditB(byte step, byte prob, byte y){
		this->fillRect(step*4, y, 4, 8, BLACK);
		this->fillRect(step*4, y+6-map(prob,0,255,1,6), 3, map(prob,0,255,1,6), BLACK);
		
		this->display();
}
void Oled_Screen :: drawAxis(int val, int offset, byte xpos, byte ypos){
		this->fillRect(xpos, ypos, 120, 10, BLACK);
		
		this->fillRect(xpos+map(val,0,1023,0,40), ypos, 2, 8, WHITE);
		this->fillRect(60+xpos+map(offset,0,1023,40,0), ypos, 2, 8, WHITE);
		this->display();
}

void Oled_Screen :: drawPixelTempo(byte tickC){

		if (tickC == 0){
			this->fillRect(110, 3, 3, 3, BLACK);
			this->fillRect(110, 5, 1, 1, WHITE);
			this->drawPixel(16, 5, WHITE);

		}
	    else
	    {
			this->fillRect(110, 3, 3, 3, WHITE);
			this->fillRect(110, 5, 1, 1, BLACK);

			this->drawPixel(126, 5, BLACK);

	    }


		this->display();
}
void Oled_Screen :: drawSector(byte sector){
		this->fillRect(120, 1, 5, 2, BLACK);
		this->fillRect(120, 1, sector, 1, WHITE);
		


		this->display();
}