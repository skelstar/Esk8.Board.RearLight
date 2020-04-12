#define DEBUG_OUT Serial
#define PRINTSTREAM_FALLBACK
#include "Debug.hpp"

#include <Arduino.h>
#include <elapsedMillis.h>

#include <Fsm.h>

HardwareSerial vesc_serial(2); // &vesc_serial = Serial1;

//------------------------------------------------------------------

#define LIGHTS_PIN 27
#define NUM_PIXELS 21

#include <LedLightsLib.h>
LedLightsLib light;

//------------------------------------------------------------------

void setup()
{
  Serial.begin(115200);
  Serial.printf("Ready");

  light.initialise(LIGHTS_PIN, NUM_PIXELS, LIGHT_BRIGHTNESS);
  light.setAll(light.COLOUR_RED);
}

elapsedMillis since_sent_to_board, since_smoothed_report;

void loop()
{
  vTaskDelay(10);
}