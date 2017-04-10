void testFillScreen(){
  fillScreen(BLACK);
  fillScreen(RED);
  fillScreen(GREEN);
  fillScreen(BLUE);
  fillScreen(BLACK);
}
void testText() {
  char text[1000];
  fillScreen(BLACK);
  setCursor(480, 320);
  setTextColor(WHITE);  setTextSize(1);
  writeTextln("Hello World!");
  setTextColor(YELLOW);
  setTextSize(2);
  writeTextln("1234.56");
  setTextColor(RED);   setTextSize(3);
  writeTextln("0xDEADBEEF");
  writeTextln(" ");
  setTextColor(GREEN);
  setTextSize(5);
  writeTextln("Groop");
  setTextSize(2);
  writeTextln("I implore thee,");
  setTextSize(1);
    writeTextln("my foonting turlingdromes.");
    writeTextln("And hooptiously drangle me");
    writeTextln("with crinkly bindlewurdles,");
    writeTextln("Or I will rend thee");
    writeTextln("in the grobberwarts");
    writeTextln("with my blurglecruncheon,");
    writeTextln("see if I don't!");
}

void testLines(uint16_t color) {
  int           x1, y1, x2, y2,
                w = 480,
                h = 320;

  fillScreen(BLACK);

  x1 = y1 = 0;
  y2    = h - 1;

  for(x2=0; x2<w; x2+=6) drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) drawLine(x1, y1, x2, y2, color);
  

  fillScreen(BLACK);

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;

  for(x2=0; x2<w; x2+=6) drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) drawLine(x1, y1, x2, y2, color);


  fillScreen(BLACK);

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  
  for(x2=0; x2<w; x2+=6) drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) drawLine(x1, y1, x2, y2, color);
 

 fillScreen(BLACK);

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  
  for(x2=0; x2<w; x2+=6) drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) drawLine(x1, y1, x2, y2, color);
 
}

void testFastLines(uint16_t color1, uint16_t color2) {
  
  int           x, y, w = 480, h = 320;

  fillScreen(BLACK);
  
  for(y=0; y<h; y+=5) drawFastHLine(0, y, w, color1);
  for(x=0; x<w; x+=5) drawFastVLine(x, 0, h, color2);

}

void testRects(uint16_t color) {
  int           n, i, i2,
                cx = 480  / 2,
                cy = 320 / 2;

  fillScreen(BLACK);
  n     = 320;
  for(i=2; i<n; i+=6) {
    i2 = i / 2;
    drawRect(cx-i2, cy-i2, i, i, color);
  }
}

void testFilledRects(uint16_t color1, uint16_t color2) {
  int           n, i, i2,
                cx = 480  / 2 - 1,
                cy = 320 / 2 - 1;

 fillScreen(BLACK);
  n = 320;
  for(i=n; i>0; i-=6) {
    i2    = i / 2;
    fillRect(cx-i2, cy-i2, i, i, color1);
    // Outlines are not included in timing results
    drawRect(cx-i2, cy-i2, i, i, color2);
  }

}

void testFilledCircles(uint8_t radius, uint16_t color) {
  int x, y, w = 480, h = 320, r2 = radius * 2;

  fillScreen(BLACK);
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      fillCircle(x, y, radius, color);
    }
  }
}

void testCircles(uint8_t radius, uint16_t color) {
  int           x, y, r2 = radius * 2,
                w = 480  + radius,
                h = 320 + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  for(x=0; x<w; x+=r2) {
    for(y=0; y<h; y+=r2) {
      drawCircle(x, y, radius, color);
    }
  }
}

void testTriangles() {
  int           n, i, cx = 480  / 2 - 1,
                      cy = 320 / 2 - 1;

  fillScreen(BLACK);
  n     = 320;
  for(i=0; i<n; i+=5) {
    drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      color565(0, 0, i));
  }
}

void testFilledTriangles() {
  int           i, cx = 480  / 2 - 1,
                   cy = 320 / 2 - 1;

  fillScreen(BLACK);
  for(i=320; i>10; i-=5) {
    fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      color565(0, i, i));
    drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      color565(i, i, 0));
  }
}

void testRoundRects() {
  int           w, i, i2,
                cx = 480  / 2 - 1,
                cy = 320 / 2 - 1;

  fillScreen(BLACK);
  w     = 320;
  for(i=0; i<w; i+=6) {
    i2 = i / 2;
    drawRoundRect(cx-i2, cy-i2, i, i, i/8, color565(i, 0, 0));
  }
}

void testFilledRoundRects() {
  int           i, i2,
                cx = 480  / 2 - 1,
                cy = 320 / 2 - 1;

  fillScreen(BLACK);

  for(i=320; i>20; i-=6) {
    i2 = i / 2;
    fillRoundRect(cx-i2, cy-i2, i, i, i/8, color565(0, i, 0));
  }
}


void testGraphics(void) {
  
  //Serial.print(F("Screen fill              "));
  testFillScreen();                 // ScreenFill ->
  delay(500);

  //Serial.print(F("Text                     "));
  testText();
  delay(3000);

  //Serial.print(F("Lines                    "));
  testLines(CYAN);
  delay(500);

  //Serial.print(F("Horiz/Vert Lines         "));
  testFastLines(RED, BLUE);
  delay(500);

  //Serial.print(F("Rectangles (outline)     "));
  testRects(GREEN);
  delay(500);

  //Serial.print(F("Rectangles (filled)      "));
  testFilledRects(YELLOW, MAGENTA);
  delay(500);

  //Serial.print(F("Circles (filled)         "));
  testFilledCircles(10, MAGENTA);

  //Serial.print(F("Circles (outline)        "));
  testCircles(10, WHITE);
  delay(500);
 
  //Serial.print(F("Triangles (outline)      "));
  testTriangles();
  delay(500);

  //Serial.print(F("Triangles (filled)       "));
  testFilledTriangles();
  delay(500);

  //Serial.print(F("Rounded rects (outline)  "));
  testRoundRects();
  delay(500);

  //Serial.print(F("Rounded rects (filled)   "));
  testFilledRoundRects();
  delay(500);

  //Serial.println(F("Done!"));
}


void rotateAText(void) {
  uint8_t rotation;
  for( rotation=0; rotation<4; rotation++) {
    setRotation(rotation);
    testText();
    delay(2000);
  }
}
