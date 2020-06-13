#ifndef LedLightsLib_h
#define LedLightsLib_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class LedLightsLib
{
public:
    uint32_t COLOUR_OFF = _strip->Color(0, 0, 0);
    uint32_t COLOUR_RED = _strip->Color(255, 0, 0);
    uint32_t COLOUR_GREEN = _strip->Color(0, 255, 0);
    uint32_t COLOUR_BLUE = _strip->Color(0, 0, 255);
    // uint32_t COLOUR_WHITE = _strip->Color(255, 255, 255);
    uint32_t COLOUR_HEADLIGHT_WHITE = _strip->Color(0, 0, 50, 255);

    void initialise(uint8_t pin, uint8_t numPixels, uint8_t brightness);
    void setBrightness(uint8_t brightness);
    int numPixels();
    void setAll(uint32_t colour, bool show = true);
    void setAll(uint32_t colour, uint8_t start, uint8_t end, bool show = true);
    void setFrontLights();
    void setPixel(uint8_t pixel, uint32_t colour, bool show);

private:
    Adafruit_NeoPixel *_strip;
    float _batteryCautionPercentage;
    uint8_t _brightness;
};

#endif