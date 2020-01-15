#include <Arduino.h>
#include <FastLED.h>

#define LED_TYPE WS2811
#define NUM_LEDS 50
#define COLOR_ORDER RGB
#define DATA_PIN 6

#define SMOOTHNESS 50
#define FADE_TIME 8
#define BRIGHTNESS 32

#define HUE_SHIFT 0
#define HUE_SHIFT_AMOUNT 1

CRGB leds[NUM_LEDS];

uint8_t holdMultiplier = 1;
uint16_t hue = 0;
uint8_t saturation = 0;
uint8_t counter = 0;

void twinkle() {
  leds[random8(50)] = CHSV(hue, saturation, 255);
  FastLED.show();
}

// void hueShift() {
//   twinkle();
//   if (hue >= 255) {
//     hue -= 255;
//   } else {
//     hue += HUE_SHIFT_AMOUNT;
//   }
// }

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  fadeToBlackBy(leds, NUM_LEDS, FADE_TIME);
}

void loop() {
  EVERY_N_MILLISECONDS(SMOOTHNESS) {
    if (counter < holdMultiplier)
    {
      counter++;
    }
    else {
      twinkle();
      counter = 0;
    }
  }
}