
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN                32
#define NUMPIXELS          1 //number of NeoPixels

#define BRIGHTNESS 255 // brightness 0~255

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void initWS2812() {
  pixels.begin();
  pixels.setBrightness(255);
}


void runWS2812(){
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(0,0,255));
  pixels.show();
}

int HTTM;

void initHTTM(){
  pinMode(TOUCH_PIN, INPUT);
  HTTM = analogRead(TOUCH_PIN);

}

void readHTTM(){
  Serial.print("httm value : ");
  Serial.println(HTTM);
}
