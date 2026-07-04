#ifndef DIGIT_H
#define DIGIT_H

#include <Arduino.h>

#include <PxMatrix.h> // https://github.com/2dom/PxMatrix

#define DIGIT_ANIMATION_MORPH 0
#define DIGIT_ANIMATION_FLIP  1
#define DIGIT_ANIMATION_ROLL  2
#define DIGIT_ANIMATION_ODOMETER 3
#define DIGIT_ANIMATION_BOUNCE 4
#define DIGIT_ANIMATION_SLOT 5
#define DIGIT_ANIMATION_WIPE 6
#define DIGIT_ANIMATION_FADE 7
#define DIGIT_ANIMATION_SHUFFLE 8

class Digit {
  
  public:
    Digit(PxMATRIX* d, byte value, uint16_t xo, uint16_t yo, uint16_t color);
    void Draw(byte value);
    void Morph(byte newValue);
    void Morph(byte newValue, byte animationMode);
    byte Value();
    void DrawColon(uint16_t c);
    void SetColor(uint16_t c);
    
  private:
    PxMATRIX* _display;
    byte _value;
    uint16_t _color;
    uint16_t xOffset;
    uint16_t yOffset;
    int animSpeed = 30;

    void drawPixel(uint16_t x, uint16_t y, uint16_t c);
    void drawFillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t c);
    void drawLine(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint16_t c);
    void drawSeg(byte seg);
    void drawSegClipped(byte seg, int yMin, int yMax, uint16_t c);
    void DrawClipped(byte value, int yMin, int yMax, uint16_t c);
    void drawSegShiftedClipped(byte seg, int yOffset, int yMin, int yMax, uint16_t c);
    void DrawShiftedClipped(byte value, int yOffset, int yMin, int yMax, uint16_t c);
    uint16_t DimColor(uint16_t c, byte scale);
    void Clear();
    void Flip(byte newValue);
    void Roll(byte newValue);
    void Bounce(byte newValue);
    void Slot(byte newValue);
    void Wipe(byte newValue);
    void Fade(byte newValue);
    void Shuffle(byte newValue);
    void Morph2();
    void Morph3();
    void Morph4();
    void Morph5();
    void Morph6();
    void Morph7();
    void Morph8();
    void Morph9();
    void Morph0();
    void Morph1();
};

#endif
