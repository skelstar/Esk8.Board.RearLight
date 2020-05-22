#define DEBUG_OUT Serial
#define PRINTSTREAM_FALLBACK
#include "Debug.hpp"

#include <Arduino.h>
#include <elapsedMillis.h>

#include <Fsm.h>

//------------------------------------------------------------------

#define LIGHTS_PIN 27
#ifdef REARLIGHT
#define NUM_PIXELS 31
#endif
#ifdef HEADLIGHT
#define NUM_PIXELS 8 + 8 // 8 leds each side
#endif

#include <LedLightsLib.h>
LedLightsLib light;

#include <state.h>

//------------------------------------------------------------------

void setup()
{
  Serial.begin(115200);
  Serial.printf("\n-----------\nEsk8.Board.RearLight: Ready!\n");

  addFsmTransitions();
}

elapsedMillis since_refreshed_leds;

void loop()
{

  fsm.run_machine();
  //   if (since_refreshed_leds > 5000)
  //   {
  //     since_refreshed_leds = 0;
  // #ifdef HEADLIGHT
  //     light.setFrontLights();
  // #endif
  // #ifdef REARLIGHT
  //     light.setAll(light.COLOUR_RED);
  // #endif
  //   }
  vTaskDelay(10);
}
