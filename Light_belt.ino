

#include "FastLED.h"


#define NUM_LEDS 144

CRGB leds[NUM_LEDS];

#define PIN 6   //this is the pin that the panel is connected to the arduino

void setup()  // this is the part that set ups the light
{
  FastLED.setBrightness(18);
  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
}


void loop() {

  lighting(0xff,0xff,0xff,10, 64, true, 30);
}


void lighting(byte red, byte green, byte blue, byte meteor_size, byte trail_decay, boolean random_decay, int speed_delay){
  
  set_all(0,0,0);   // initialize all the pixels with no colour

  for(int i = 0; i < NUM_LEDS + NUM_LEDS; ++i){

    for(int j = 0; j < NUM_LEDS; ++j){
      if( (!random_decay) || (random(10)>5) ){
        fade_to_black(j , trail_decay);
      }
    }

    // draw the meteor effect
    for(int k = 0; k < meteor_size; ++k){
      if( ((i - k) < NUM_LEDS) && (i - k >= 0)){
        
        red = random( random(0, 120) , random(0, 255));
        blue = random( random(0, 120) , random(0, 255));
        //green = random( random(0, 120) , random(0, 255));
        
        set_pixel(i - k, red, green, blue);
        //set_pixel(i-j, random8(0, 165 - random()), random8(0, 165 - random()), random8(0, 165 - random()));
      }
    }
    show_strip();
    delay(speed_delay);
  }
}


void fade_to_black(int led_num, byte fade_value){
  
  #ifndef ADAFRUIT_NEOPIXEL_H
  
    leds[led_num].fadeToBlackBy(fade_value);
    
  #endif
  
}


void show_strip(){
  
  #ifndef ADAFRUIT_NEOPIXEL_H

    FastLED.show();

  #endif

}

void set_pixel(int pixel, byte red, byte green, byte blue){
 
  #ifndef ADAFRUIT_NEOPIXEL_H 

   leds[pixel].red = red;
   leds[pixel].green = green;
   leds[pixel].blue = blue;
   
  #endif
}

void set_all(byte red, byte green, byte blue){

  for(int i = 0; i < NUM_LEDS; ++i){
    set_pixel(i, red, green, blue);
  
  }
    show_strip();

}

