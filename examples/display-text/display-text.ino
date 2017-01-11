#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// WeMos Pinout
//---------------------------------------------------
const int8_t RST_PIN = D2;
const int8_t CE_PIN = D1;
const int8_t DC_PIN = D6;
const int8_t BL_PIN = D0;

// Nokia display
//---------------------------------------------------
Adafruit_PCD8544 display = Adafruit_PCD8544(DC_PIN, CE_PIN, RST_PIN);

//---------------------------------------------------

void setup() {
  // Turn LCD backlight on
  pinMode(BL_PIN, OUTPUT);
  digitalWrite(BL_PIN, HIGH);

  // Configure LCD
  display.begin();
  display.setContrast(100);
  display.clearDisplay();

  // Temporary
  display.setRotation(2);
}

//---------------------------------------------------

void drawAxis() {
  display.drawLine(LCDWIDTH/2, 0, LCDWIDTH/2, LCDHEIGHT, BLACK);
  display.drawLine(0, LCDHEIGHT/2, LCDWIDTH, LCDHEIGHT/2, BLACK);  
}

//---------------------------------------------------

void __loop() {
  // Text size: 1 allows to display 78 chars
  // Resolution: 84 x 48

  String msg1 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur hendrerit o";
  String msg2 = "rci non libero rutrum tempus. Donec quis rhoncus nunc. Phasell";
  display.clearDisplay();
  display.print(msg1);
  display.display();
  delay(1000);
  display.clearDisplay();
  display.print(msg2);
  display.display();
  delay(1000);
}

//---------------------------------------------------

// The char '-' is taken into account
int calculateNumberOfChars(int value) {
  int numberOfChars = value < 0 ? 1 : 0;

  while(value) {
    value = value / 10;
    numberOfChars++;
  }

  return numberOfChars;
}

//---------------------------------------------------

void showTitleAndValue(String title, int value, int titleSize = 1, int valueSize = 3) {
  uint8_t CHAR_WIDTH = 5;
  uint8_t CHAR_HEIGHT = 3;

  display.clearDisplay();
  
  display.setTextSize(titleSize);
  display.setCursor(LCDWIDTH/2 - ceil(CHAR_WIDTH*titleSize/2.0)*title.length(), 0);
  display.print(title);
  
  display.setTextSize(valueSize);
  int numberOfChars = calculateNumberOfChars(value);
  display.setCursor(LCDWIDTH/2 - ceil(CHAR_WIDTH*valueSize/2.0)*numberOfChars, LCDHEIGHT/2 - CHAR_HEIGHT*valueSize);
  display.print(value);

  display.display();
}

//---------------------------------------------------

void test_01() {
  for(int value = -999; value <= 999; value++) {
    showTitleAndValue("accelerometer", value);
    delay(100);
  }
}

//---------------------------------------------------

void loop() {
  test_01();
}

//---------------------------------------------------

