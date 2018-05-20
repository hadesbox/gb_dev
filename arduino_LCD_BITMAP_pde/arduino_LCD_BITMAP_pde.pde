/**
 * CONVERt TO  adafruit array
 * 
 * Images can be loaded and displayed to the screen at their actual size
 * or any other size. 
 */
 
// The next line is needed if running in JavaScript Mode with Processing.js
/* @pjs preload="moonwalk.jpg"; */ 

PImage img;  // Declare variable "a" of type PImage
 
  String converted="static const unsigned char PROGMEM logo16_glcd_bmp[]={\n";
void setup() {
  size(128, 64);
  // The image file must be in the data folder of the current sketch 
  // to load successfully
  img = loadImage("lfo.jpg");  // Load the image into the program  
  // img = loadImage("moonwalk.jpg");  // Load the image into the program  

 
  img.loadPixels();  
  
  for (int y = 0; y < img.height; y++) {
  // Loop through every pixel row
    for (int x = 0; x < img.width; x++) {
      // Use the formula to find the 1D location
      int loc = x + (y * img.width);
      float r = red(img.pixels[loc]);
      if (x%8==0) {
        if (x>0) {
          converted+=",";
        }
        converted+="B";
     }
     if (r<200) {
       converted+="0";
     }else{
      converted+="1";
     }
     
    }
    if (y<=0 || y<=img.width*img.height) {
        converted+=",";
      }
  }
  converted+="};";
  println(converted);
  noLoop();
}

void draw() {

}
