#ifndef FSM_H
#include <Fsm.h>
#endif

enum LightEvent
{
  EV_INIT_FINISHED,
  EV_WIPE_FINISHED,
};

uint32_t wipeFrom, wipeTo;

void triggerFsm(LightEvent ev);

//------------------------------------------------------------------

State state_init([] {
  DEBUG("state_on");
  light.initialise(LIGHTS_PIN, NUM_PIXELS, LIGHT_BRIGHTNESS);
  triggerFsm(EV_INIT_FINISHED);
},
                 NULL, NULL);
//------------------------------------------------------------------

elapsedMillis sinceWipedUpStep;
#define WIPED_UP_STEP_PERIOD 50
int i = 0;

State state_wipe_up(
    [] {
      i = 0;
      DEBUG("state_wipe_up");
    },
    [] {
      bool stillWiping = i < light.numPixels() / 2;

      if (sinceWipedUpStep > WIPED_UP_STEP_PERIOD && stillWiping)
      {
        sinceWipedUpStep = 0;
        light.setPixel(i, wipeTo, true);
        light.setPixel((light.numPixels() / 2) + i, wipeTo, true);
        i++;
      }
      else if (!stillWiping)
      {
        triggerFsm(EV_WIPE_FINISHED);
      }
    },
    NULL);
//------------------------------------------------------------------

State state_all_on([] {
  DEBUG("state_all_on");
#ifdef HEADLIGHT
  light.setFrontLights();
#endif
#ifdef TAILLIGHT
  light.setAll(light.COLOUR_RED);
#endif
},
                   NULL, NULL);
//------------------------------------------------------------------

void setHeadlightWipe()
{
  wipeTo = light.COLOUR_HEADLIGHT_WHITE;
}

void setTailLightWipe()
{
  wipeTo = light.COLOUR_RED;
}

Fsm fsm(&state_init);
//------------------------------------------------------------------

void addFsmTransitions()
{
#ifdef HEADLIGHT
  fsm.add_transition(&state_init, &state_wipe_up, EV_INIT_FINISHED, setHeadlightWipe);
  fsm.add_transition(&state_wipe_up, &state_all_on, EV_WIPE_FINISHED, NULL);
#endif
#ifdef TAILLIGHT
  fsm.add_transition(&state_init, &state_wipe_up, EV_INIT_FINISHED, setTailLightWipe);
  fsm.add_transition(&state_wipe_up, &state_all_on, EV_WIPE_FINISHED, NULL);
#endif
}
//------------------------------------------------------------------

char *triggerToString(LightEvent ev)
{
  switch (ev)
  {
  case EV_INIT_FINISHED:
    return "EV_INIT_FINISHED";
  case EV_WIPE_FINISHED:
    return "EV_WIPE_FINISHED";
  }
  return "";
}

void triggerFsm(LightEvent ev)
{
  DEBUG(triggerToString(ev));
  fsm.trigger((int)ev);
}
//------------------------------------------------------------------