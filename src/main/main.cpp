#define DEBUG_OUT Serial
#define PRINTSTREAM_FALLBACK
#include "Debug.hpp"

#include <Arduino.h>
#include <elapsedMillis.h>

#include <Fsm.h>

HardwareSerial vesc_serial(2); // &vesc_serial = Serial1;

//------------------------------------------------------------------

#define LIGHTS_PIN 27
#ifdef REAR_LIGHT
#define NUM_PIXELS 31
#endif
#ifdef HEADLIGHT
#define NUM_PIXELS 8 + 8 // 8 leds each side
#endif

#include <LedLightsLib.h>
LedLightsLib light;

//------------------------------------------------------------------

void setup()
{
  Serial.begin(115200);
  Serial.printf("Esk8.Board.RearLight: Ready!");

  delay(3000);

  light.initialise(LIGHTS_PIN, NUM_PIXELS, LIGHT_BRIGHTNESS);
  delay(100);

#ifdef HEADLIGHT
  light.setFrontLights();
#endif
#ifdef REAR_LIGHT
  light.setAll(light.COLOUR_RED);
#endif
}

elapsedMillis since_refreshed_leds;

void loop()
{
  if (since_refreshed_leds > 5000)
  {
    since_refreshed_leds = 0;
#ifdef HEADLIGHT
    light.setFrontLights();
#endif
#ifdef REAR_LIGHT
    light.setAll(light.COLOUR_RED);
#endif
  }
  vTaskDelay(10);
}
