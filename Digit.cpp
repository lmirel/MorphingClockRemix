#include "Digit.h"

const byte sA = 0;
const byte sB = 1;
const byte sC = 2;
const byte sD = 3;
const byte sE = 4;
const byte sF = 5;
const byte sG = 6;
const int segHeight = 6;
const int segWidth = segHeight;
const uint16_t height = 31;
const uint16_t width = 63;

byte digitBits[] = {
  B11111100, // 0 ABCDEF--
  B01100000, // 1 -BC-----
  B11011010, // 2 AB-DE-G-
  B11110010, // 3 ABCD--G-
  B01100110, // 4 -BC--FG-
  B10110110, // 5 A-CD-FG-
  B10111110, // 6 A-CDEFG-
  B11100000, // 7 ABC-----
  B11111110, // 8 ABCDEFG-
  B11110110, // 9 ABCD_FG-
};

//byte sunBitmap[] {
//  B100100100,
//  B010001000,
//  B001110000,
//  B101110100,
//  B001110000,
//  B010001000,
//  B100100100
//};

uint16_t black;

Digit::Digit(PxMATRIX* d, byte value, uint16_t xo, uint16_t yo, uint16_t color) {
  _display = d;
  _value = value;
  xOffset = xo;
  yOffset = yo;
  _color = color;
}

byte Digit::Value() {
  return _value;
}
void Digit::drawPixel(uint16_t x, uint16_t y, uint16_t c)
{
  _display->drawPixel(xOffset + x, height - (y + yOffset), c);
}

void Digit::drawLine(uint16_t x, uint16_t y, uint16_t x2, uint16_t y2, uint16_t c)
{
  _display->drawLine(xOffset + x, height - (y + yOffset), xOffset + x2, height - (y2 + yOffset), c);
}

void Digit::drawFillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t c)
{
  _display->fillRect(xOffset + x, height - (y + yOffset), w,h, c);
}

void Digit::SetColor(uint16_t c)
{
  _color = c;
}

void Digit::DrawColon(uint16_t c)
{
  // Colon is drawn to the left of this digit
  drawFillRect(-3, segHeight-1, 2,2, c);
  drawFillRect(-3, segHeight+1+3, 2,2, c);
}

void Digit::drawSeg(byte seg)
{
  switch (seg) {
    case sA: drawLine(1, segHeight * 2 + 2, segWidth, segHeight * 2 + 2, _color); break;
    case sB: drawLine(segWidth + 1, segHeight * 2 + 1, segWidth + 1, segHeight + 2, _color); break;
    case sC: drawLine(segWidth + 1, 1, segWidth + 1, segHeight, _color); break;
    case sD: drawLine(1, 0, segWidth, 0, _color); break;
    case sE: drawLine(0, 1, 0, segHeight, _color); break;
    case sF: drawLine(0, segHeight * 2 + 1, 0, segHeight + 2, _color); break;
    case sG: drawLine(1, segHeight + 1, segWidth, segHeight + 1, _color); break;
  }
}

void Digit::drawSegClipped(byte seg, int yMin, int yMax, uint16_t c)
{
  int x1 = 0;
  int y1 = 0;
  int x2 = 0;
  int y2 = 0;

  switch (seg) {
    case sA: x1 = 1; y1 = segHeight * 2 + 2; x2 = segWidth; y2 = y1; break;
    case sB: x1 = segWidth + 1; y1 = segHeight * 2 + 1; x2 = x1; y2 = segHeight + 2; break;
    case sC: x1 = segWidth + 1; y1 = 1; x2 = x1; y2 = segHeight; break;
    case sD: x1 = 1; y1 = 0; x2 = segWidth; y2 = 0; break;
    case sE: x1 = 0; y1 = 1; x2 = 0; y2 = segHeight; break;
    case sF: x1 = 0; y1 = segHeight * 2 + 1; x2 = 0; y2 = segHeight + 2; break;
    case sG: x1 = 1; y1 = segHeight + 1; x2 = segWidth; y2 = y1; break;
  }

  if (y1 == y2) {
    if (y1 >= yMin && y1 <= yMax)
      drawLine(x1, y1, x2, y2, c);
    return;
  }

  if (y1 < y2) {
    int tmp = y1;
    y1 = y2;
    y2 = tmp;
  }

  int clippedTop = min(y1, yMax);
  int clippedBottom = max(y2, yMin);
  if (clippedTop >= clippedBottom)
    drawLine(x1, clippedTop, x2, clippedBottom, c);
}

void Digit::DrawClipped(byte value, int yMin, int yMax, uint16_t c)
{
  byte pattern = digitBits[value];
  if (bitRead(pattern, 7)) drawSegClipped(sA, yMin, yMax, c);
  if (bitRead(pattern, 6)) drawSegClipped(sB, yMin, yMax, c);
  if (bitRead(pattern, 5)) drawSegClipped(sC, yMin, yMax, c);
  if (bitRead(pattern, 4)) drawSegClipped(sD, yMin, yMax, c);
  if (bitRead(pattern, 3)) drawSegClipped(sE, yMin, yMax, c);
  if (bitRead(pattern, 2)) drawSegClipped(sF, yMin, yMax, c);
  if (bitRead(pattern, 1)) drawSegClipped(sG, yMin, yMax, c);
}

void Digit::drawSegShiftedClipped(byte seg, int yOffset, int yMin, int yMax, uint16_t c)
{
  int x1 = 0;
  int y1 = 0;
  int x2 = 0;
  int y2 = 0;

  switch (seg) {
    case sA: x1 = 1; y1 = segHeight * 2 + 2; x2 = segWidth; y2 = y1; break;
    case sB: x1 = segWidth + 1; y1 = segHeight * 2 + 1; x2 = x1; y2 = segHeight + 2; break;
    case sC: x1 = segWidth + 1; y1 = 1; x2 = x1; y2 = segHeight; break;
    case sD: x1 = 1; y1 = 0; x2 = segWidth; y2 = 0; break;
    case sE: x1 = 0; y1 = 1; x2 = 0; y2 = segHeight; break;
    case sF: x1 = 0; y1 = segHeight * 2 + 1; x2 = 0; y2 = segHeight + 2; break;
    case sG: x1 = 1; y1 = segHeight + 1; x2 = segWidth; y2 = y1; break;
  }

  y1 += yOffset;
  y2 += yOffset;

  if (y1 == y2) {
    if (y1 >= yMin && y1 <= yMax)
      drawLine(x1, y1, x2, y2, c);
    return;
  }

  if (y1 < y2) {
    int tmp = y1;
    y1 = y2;
    y2 = tmp;
  }

  int clippedTop = min(y1, yMax);
  int clippedBottom = max(y2, yMin);
  if (clippedTop >= clippedBottom)
    drawLine(x1, clippedTop, x2, clippedBottom, c);
}

void Digit::DrawShiftedClipped(byte value, int yOffset, int yMin, int yMax, uint16_t c)
{
  byte pattern = digitBits[value];
  if (bitRead(pattern, 7)) drawSegShiftedClipped(sA, yOffset, yMin, yMax, c);
  if (bitRead(pattern, 6)) drawSegShiftedClipped(sB, yOffset, yMin, yMax, c);
  if (bitRead(pattern, 5)) drawSegShiftedClipped(sC, yOffset, yMin, yMax, c);
  if (bitRead(pattern, 4)) drawSegShiftedClipped(sD, yOffset, yMin, yMax, c);
  if (bitRead(pattern, 3)) drawSegShiftedClipped(sE, yOffset, yMin, yMax, c);
  if (bitRead(pattern, 2)) drawSegShiftedClipped(sF, yOffset, yMin, yMax, c);
  if (bitRead(pattern, 1)) drawSegShiftedClipped(sG, yOffset, yMin, yMax, c);
}

uint16_t Digit::DimColor(uint16_t c, byte scale)
{
  byte r = ((c >> 11) & 0x1F) << 3;
  byte g = ((c >> 5) & 0x3F) << 2;
  byte b = (c & 0x1F) << 3;

  r = ((uint16_t)r * scale) / 255;
  g = ((uint16_t)g * scale) / 255;
  b = ((uint16_t)b * scale) / 255;

  return _display->color565(r, g, b);
}

uint16_t Digit::MinColor(uint16_t c, byte minimum)
{
  byte r = ((c >> 11) & 0x1F) << 3;
  byte g = ((c >> 5) & 0x3F) << 2;
  byte b = (c & 0x1F) << 3;

  if (r > 0 && r < minimum)
    r = minimum;
  if (g > 0 && g < minimum)
    g = minimum;
  if (b > 0 && b < minimum)
    b = minimum;

  return _display->color565(r, g, b);
}

void Digit::Clear()
{
  for (int y = 0; y <= segHeight * 2 + 2; y++)
    drawLine(0, y, segWidth + 1, y, black);
}

void Digit::Draw(byte value) {
  byte pattern = digitBits[value];
  if (bitRead(pattern, 7)) drawSeg(sA);
  if (bitRead(pattern, 6)) drawSeg(sB);
  if (bitRead(pattern, 5)) drawSeg(sC);
  if (bitRead(pattern, 4)) drawSeg(sD);
  if (bitRead(pattern, 3)) drawSeg(sE);
  if (bitRead(pattern, 2)) drawSeg(sF);
  if (bitRead(pattern, 1)) drawSeg(sG);
  _value = value;
}

void Digit::Flip(byte newValue)
{
  const int topMin = segHeight + 2;
  const int topMax = segHeight * 2 + 2;
  const int bottomMin = 0;
  const int bottomMax = segHeight;
  const int flipDelay = max(8, animSpeed / 2);

  for (int i = 0; i <= segHeight; i++) {
    Clear();
    DrawClipped(_value, bottomMin, bottomMax, _color);
    DrawClipped(_value, topMin + i, topMax, _color);
    drawLine(0, segHeight + 1, segWidth + 1, segHeight + 1, _color);
    delay(flipDelay);
  }

  for (int i = segHeight; i >= 0; i--) {
    Clear();
    DrawClipped(_value, bottomMin, bottomMax, _color);
    DrawClipped(newValue, topMin + i, topMax, _color);
    drawLine(0, segHeight + 1, segWidth + 1, segHeight + 1, _color);
    delay(flipDelay);
  }

  for (int i = 0; i <= segHeight; i++) {
    Clear();
    DrawClipped(newValue, topMin, topMax, _color);
    DrawClipped(_value, bottomMin, bottomMax - i, _color);
    drawLine(0, segHeight + 1, segWidth + 1, segHeight + 1, _color);
    delay(flipDelay);
  }

  for (int i = segHeight; i >= 0; i--) {
    Clear();
    DrawClipped(newValue, topMin, topMax, _color);
    DrawClipped(newValue, bottomMin, bottomMax - i, _color);
    drawLine(0, segHeight + 1, segWidth + 1, segHeight + 1, _color);
    delay(flipDelay);
  }

  Clear();
  Draw(newValue);
}

void Digit::Roll(byte newValue)
{
  const int digitHeight = segHeight * 2 + 2;
  const int travel = digitHeight + 2;
  const int rollDelay = max(8, animSpeed / 2);

  for (int i = 0; i <= travel; i++) {
    Clear();
    DrawShiftedClipped(_value, -i, 0, digitHeight, _color);
    DrawShiftedClipped(newValue, travel - i, 0, digitHeight, _color);
    delay(rollDelay);
  }

  Clear();
  Draw(newValue);
}

void Digit::Bounce(byte newValue)
{
  const int digitHeight = segHeight * 2 + 2;

  Roll(newValue);

  Clear();
  DrawShiftedClipped(newValue, -1, 0, digitHeight, _color);
  delay(35);
  Clear();
  DrawShiftedClipped(newValue, 1, 0, digitHeight, _color);
  delay(35);
  Clear();
  Draw(newValue);
}

void Digit::Slot(byte newValue)
{
  const int slotDelay = max(20, animSpeed);

  for (byte i = 0; i < 3; i++) {
    byte preview = (newValue + 3 - i) % 10;
    if (preview == _value || preview == newValue)
      preview = (preview + 5) % 10;
    Clear();
    Draw(preview);
    delay(slotDelay);
  }

  Roll(newValue);
}

void Digit::Wipe(byte newValue)
{
  const int digitHeight = segHeight * 2 + 2;
  const int travel = digitHeight + 2;
  const int wipeDelay = max(8, animSpeed / 2);

  for (int i = 0; i <= travel; i++) {
    Clear();
    DrawShiftedClipped(_value, i, 0, digitHeight, _color);
    DrawShiftedClipped(newValue, i - travel, 0, digitHeight, _color);
    drawLine(0, segHeight + 1, segWidth + 1, segHeight + 1, DimColor(_color, 120));
    delay(wipeDelay);
  }

  Clear();
  Draw(newValue);
}

void Digit::Fade(byte newValue)
{
  const byte fadeSteps[] = {180, 120, 70, 35};
  uint16_t traceColor = MinColor(_color, 70);

  for (byte i = 0; i < sizeof(fadeSteps); i++) {
    Clear();
    DrawClipped(_value, 0, segHeight * 2 + 2, DimColor(traceColor, fadeSteps[i]));
    DrawClipped(newValue, 0, segHeight * 2 + 2, _color);
    delay(55);
  }

  Clear();
  Draw(newValue);
}

void Digit::Shuffle(byte newValue)
{
  const int shuffleDelay = max(20, animSpeed);

  for (byte i = 0; i < 3; i++) {
    byte preview = random(10);
    if (preview == _value || preview == newValue)
      preview = (preview + 4 + i) % 10;
    Clear();
    Draw(preview);
    delay(shuffleDelay);
  }

  Clear();
  Draw(newValue);
}

void Digit::Morph2() {
  // TWO
  for (int i = 0; i <= segWidth; i++)
  {
    if (i < segWidth) {
      drawPixel(segWidth - i, segHeight * 2 + 2, _color);
      drawPixel(segWidth - i, segHeight + 1, _color);
      drawPixel(segWidth - i, 0, _color);
    }

    drawLine(segWidth + 1 - i, 1, segWidth + 1 - i, segHeight, black);
    drawLine(segWidth - i, 1, segWidth - i, segHeight, _color);
    delay(animSpeed);
  }
}

void Digit::Morph3() {
  // THREE
  for (int i = 0; i <= segWidth; i++)
  {
    drawLine(0 + i, 1, 0 + i, segHeight, black);
    drawLine(1 + i, 1, 1 + i, segHeight, _color);
    delay(animSpeed);
  }
}

void Digit::Morph4() {
  // FOUR
  for (int i = 0; i < segWidth; i++)
  {
    drawPixel(segWidth - i, segHeight * 2 + 2, black); // Erase A
    drawPixel(0, segHeight * 2 + 1 - i, _color); // Draw as F
    drawPixel(1 + i, 0, black); // Erase D
    delay(animSpeed);
  }
}

void Digit::Morph5() {
  // FIVE
  for (int i = 0; i < segWidth; i++)
  {
    drawPixel(segWidth + 1, segHeight + 2 + i, black); // Erase B
    drawPixel(segWidth - i, segHeight * 2 + 2, _color); // Draw as A
    drawPixel(segWidth - i, 0, _color); // Draw D
    delay(animSpeed);
  }
}

void Digit::Morph6() {
  // SIX
  for (int i = 0; i <= segWidth; i++)
  {
    // Move C right to left
    drawLine(segWidth - i, 1, segWidth - i, segHeight, _color);
    if (i > 0) drawLine(segWidth - i + 1, 1, segWidth - i + 1, segHeight, black);
    delay(animSpeed);
  }
}

void Digit::Morph7() {
  // SEVEN
  for (int i = 0; i <= (segWidth + 1); i++)
  {
    // Move E left to right
    drawLine(0 + i - 1, 1, 0 + i - 1, segHeight, black);
    drawLine(0 + i, 1, 0 + i, segHeight, _color);

    // Move F left to right
    drawLine(0 + i - 1, segHeight * 2 + 1, 0 + i - 1, segHeight + 2, black);
    drawLine(0 + i, segHeight * 2 + 1, 0 + i, segHeight + 2, _color);

    // Erase D and G gradually
    drawPixel(1 + i, 0, black); // D
    drawPixel(1 + i, segHeight + 1, black); // G
    delay(animSpeed);
  }
}

void Digit::Morph8() {
  // EIGHT
  for (int i = 0; i <= segWidth; i++)
  {
    // Move B right to left
    drawLine(segWidth - i, segHeight * 2 + 1, segWidth - i, segHeight + 2, _color);
    if (i > 0) drawLine(segWidth - i + 1, segHeight * 2 + 1, segWidth - i + 1, segHeight + 2, black);

    // Move C right to left
    drawLine(segWidth - i, 1, segWidth - i, segHeight, _color);
    if (i > 0) drawLine(segWidth - i + 1, 1, segWidth - i + 1, segHeight, black);

    // Gradually draw D and G
    if (i < segWidth) {
      drawPixel(segWidth - i, 0, _color); // D
      drawPixel(segWidth - i, segHeight + 1, _color); // G
    }
    delay(animSpeed);
  }
}

void Digit::Morph9() {
  // NINE
  for (int i = 0; i <= (segWidth + 1); i++)
  {
    // Move E left to right
    drawLine(0 + i - 1, 1, 0 + i - 1, segHeight, black);
    drawLine(0 + i, 1, 0 + i, segHeight, _color);
    delay(animSpeed);
  }
}

void Digit::Morph0() {
  // ZERO
  for (int i = 0; i <= segWidth; i++)
  {
    if (_value==1) { // If 1 to 0, slide B to F and E to C  
      // slide B to F 
      drawLine(segWidth - i, segHeight * 2+1 , segWidth - i, segHeight + 2, _color);
      if (i > 0) drawLine(segWidth - i + 1, segHeight * 2+1, segWidth - i + 1, segHeight + 2, black);

      // slide E to C
      drawLine(segWidth - i, 1, segWidth - i, segHeight, _color);
      if (i > 0) drawLine(segWidth - i + 1, 1, segWidth - i + 1, segHeight, black);

      if (i<segWidth) drawPixel(segWidth - i, segHeight * 2 + 2 , _color); // Draw A
      if (i<segWidth) drawPixel(segWidth - i, 0, _color); // Draw D
    }
    
    if (_value==2) { // If 2 to 0, slide B to F and Flow G to C
      // slide B to F 
      drawLine(segWidth - i, segHeight * 2+1 , segWidth - i, segHeight + 2, _color);
      if (i > 0) drawLine(segWidth - i + 1, segHeight * 2+1, segWidth - i + 1, segHeight + 2, black);
    
      drawPixel(1+i, segHeight + 1, black); // Erase G left to right
      if (i<segWidth) drawPixel(segWidth + 1, segHeight + 1- i, _color);// Draw C
    }

    if (_value==3) { // B to F, C to E
      // slide B to F 
      drawLine(segWidth - i, segHeight * 2+1 , segWidth - i, segHeight + 2, _color);
      if (i > 0) drawLine(segWidth - i + 1, segHeight * 2+1, segWidth - i + 1, segHeight + 2, black);
      
      // Move C to E
      drawLine(segWidth - i, 1, segWidth - i, segHeight, _color);
      if (i > 0) drawLine(segWidth - i + 1, 1, segWidth - i + 1, segHeight, black);

      // Erase G from right to left
      drawPixel(segWidth - i, segHeight + 1, black); // G
    }
    
    if (_value==5) { // If 5 to 0, we also need to slide F to B
      if (i<segWidth) {
        if (i>0) drawLine(1 + i, segHeight * 2 + 1, 1 + i, segHeight + 2, black);
        drawLine(2 + i, segHeight * 2 + 1, 2 + i, segHeight + 2, _color);
      }
    }
    
    if (_value==5 || _value==9) { // If 9 or 5 to 0, Flow G into E
      if (i<segWidth) drawPixel(segWidth - i, segHeight + 1, black);
      if (i<segWidth) drawPixel(0, segHeight - i, _color);
    }
    delay(animSpeed);
  }
}

void Digit::Morph1() {
  // Zero or two to One
  for (int i = 0; i <= (segWidth + 1); i++)
  {
    // Move E left to right
    drawLine(0 + i - 1, 1, 0 + i - 1, segHeight, black);
    drawLine(0 + i, 1, 0 + i, segHeight, _color);

    // Move F left to right
    drawLine(0 + i - 1, segHeight * 2 + 1, 0 + i - 1, segHeight + 2, black);
    drawLine(0 + i, segHeight * 2 + 1, 0 + i, segHeight + 2, _color);

    // Gradually Erase A, G, D
    drawPixel(1 + i, segHeight * 2 + 2, black); // A
    drawPixel(1 + i, 0, black); // D
    drawPixel(1 + i, segHeight + 1, black); // G

    delay(animSpeed);
  }
}

void Digit::Morph(byte newValue) {
  Morph(newValue, DIGIT_ANIMATION_MORPH);
}

void Digit::Morph(byte newValue, byte animationMode) {
  if (animationMode == DIGIT_ANIMATION_FLIP) {
    Flip(newValue);
    _value = newValue;
    return;
  }
  if (animationMode == DIGIT_ANIMATION_ROLL) {
    Roll(newValue);
    _value = newValue;
    return;
  }
  if (animationMode == DIGIT_ANIMATION_BOUNCE) {
    Bounce(newValue);
    _value = newValue;
    return;
  }
  if (animationMode == DIGIT_ANIMATION_SLOT) {
    Slot(newValue);
    _value = newValue;
    return;
  }
  if (animationMode == DIGIT_ANIMATION_WIPE) {
    Wipe(newValue);
    _value = newValue;
    return;
  }
  if (animationMode == DIGIT_ANIMATION_FADE) {
    Fade(newValue);
    _value = newValue;
    return;
  }
  if (animationMode == DIGIT_ANIMATION_SHUFFLE) {
    Shuffle(newValue);
    _value = newValue;
    return;
  }

  switch (newValue) {
    case 2: Morph2(); break;
    case 3: Morph3(); break;
    case 4: Morph4(); break;
    case 5: Morph5(); break;
    case 6: Morph6(); break;
    case 7: Morph7(); break;
    case 8: Morph8(); break;
    case 9: Morph9(); break;
    case 0: Morph0(); break;
    case 1: Morph1(); break;
  }
  _value = newValue;
}

