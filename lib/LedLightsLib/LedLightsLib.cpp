#include "Arduino.h"
#include "LedLightsLib.h"

//------------------------------------------------------------------

void LedLightsLib::initialise(uint8_t pin, uint8_t numPixels, uint8_t brightness)
{
#ifdef HEADLIGHT
  _strip = new Adafruit_NeoPixel(numPixels, pin, NEO_GRBW + NEO_KHZ800);
#endif
#ifdef TAILLIGHT
  _strip = new Adafruit_NeoPixel(numPixels, pin, NEO_GRB + NEO_KHZ800);
#endif
  _strip->begin();
  _brightness = brightness;

  _strip->setBrightness(_brightness);
  _strip->clear();
  _strip->show();
}
//------------------------------------------------------------------

void LedLightsLib::setBrightness(uint8_t brightness)
{
  _brightness = brightness;
  _strip->setBrightness(_brightness);
}
//------------------------------------------------------------------

void LedLightsLib::setFrontLights()
{
  _strip->setBrightness(LIGHT_BRIGHTNESS);

  setAll(COLOUR_HEADLIGHT_WHITE, 0, _strip->numPixels() - 1);
}
//------------------------------------------------------------------

void LedLightsLib::setAll(uint32_t colour, bool show)
{
  setAll(colour, 0, _strip->numPixels() - 1, show);
}
//------------------------------------------------------------------

void LedLightsLib::setAll(uint32_t colour, uint8_t start, uint8_t end, bool show)
{
  if (_strip == NULL)
  {
    Serial.printf("ERROR: light not initialised");
    return;
  }

  if (start > end || end > _strip->numPixels() - 1)
  {
    Serial.printf("ERROR: start and/or end pixels are out of range!\n");
    Serial.printf("num: %d start: %d end: %d\n", _strip->numPixels(), start, end);

    return;
  }

  for (int i = start; i <= end; i++)
  {
    setPixel(i, colour, false);
  }
  if (show)
  {
    _strip->show();
  }
}
//------------------------------------------------------------------
int LedLightsLib::numPixels()
{
  return _strip->numPixels();
}

//------------------------------------------------------------------
void LedLightsLib::setPixel(uint8_t pixel, uint32_t colour, bool show = true)
{
  _strip->setPixelColor(pixel, colour);
  if (show)
  {
    _strip->show();
  }
}

//------------------------------------------------------------------
