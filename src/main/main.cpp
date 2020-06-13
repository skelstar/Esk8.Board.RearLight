#define DEBUG_OUT Serial
#define PRINTSTREAM_FALLBACK
#include "Debug.hpp"

#include <Arduino.h>
#include <elapsedMillis.h>

#include <Fsm.h>

//------------------------------------------------------------------

#define LIGHTS_PIN 27
#define NUM_PIXELS 8 + 8 // 8 leds each side

#include <LedLightsLib.h>
LedLightsLib light;

#include <state.h>

//------------------------------------------------------------------

void setup()
{
  Serial.begin(115200);
  Serial.printf("\n-----------\n");
  Serial.printf("Esk8.Board.TailLight:\n");
#ifdef HEADLIGHT
  Serial.printf("- mode: HEADLIGHT\n");
#endif
#ifdef TAILLIGHT
  Serial.printf("- mode: TAILLIGHT\n");
#endif
  Serial.printf("- brightness: %d\n", LIGHT_BRIGHTNESS);
  Serial.println();

  addFsmTransitions();
}

elapsedMillis since_refreshed_leds;

void loop()
{
  fsm.run_machine();

  vTaskDelay(10);
}

//------------------------------------------------------------------