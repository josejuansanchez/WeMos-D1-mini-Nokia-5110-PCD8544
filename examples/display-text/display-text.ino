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

void showText(String msg) {
  // A text size=1 allows to display 78 chars
  uint8_t MAX_CHARS_DISPLAYED = 79;
  uint8_t numberOfChunks = (msg.length() / MAX_CHARS_DISPLAYED) + 1;
  uint8_t from = 0;
  uint8_t to = MAX_CHARS_DISPLAYED;

  display.setTextSize(1);

  for(uint8_t i = 0; i < numberOfChunks; i++) {
    display.clearDisplay();
    display.print(msg.substring(from, to));
    display.display();
    from = to + 1;
    to = to + MAX_CHARS_DISPLAYED;
    delay(4000);
  }
}

//---------------------------------------------------

void showTitleAndValue(String title, int value, int titleSize = 1, int valueSize = 2) {
  uint8_t CHAR_WIDTH = 5;
  uint8_t CHAR_HEIGHT = 3;

  display.clearDisplay();
  display.setTextSize(titleSize);
  display.setCursor(LCDWIDTH/2 - ceil(CHAR_WIDTH*titleSize/2.0)*title.length(), 0);
  display.print(title);
  display.setTextSize(valueSize);
  display.setCursor(LCDWIDTH/2 - ceil(CHAR_WIDTH*valueSize/2.0)*String(value).length(), LCDHEIGHT/2 - CHAR_HEIGHT*valueSize);
  display.print(value);
  display.display();
}

//---------------------------------------------------

void showTitleAndValue(String title, float value, int titleSize = 1, int valueSize = 2) {
  uint8_t CHAR_WIDTH = 5;
  uint8_t CHAR_HEIGHT = 3;

  display.clearDisplay();
  display.setTextSize(titleSize);
  display.setCursor(LCDWIDTH/2 - ceil(CHAR_WIDTH*titleSize/2.0)*title.length(), 0);
  display.print(title);
  display.setTextSize(valueSize);
  display.setCursor(LCDWIDTH/2 - ceil(CHAR_WIDTH*valueSize/2.0)*String(value).length(), LCDHEIGHT/2 - CHAR_HEIGHT*valueSize);
  display.print(value);
  display.display();
}

//---------------------------------------------------

void test_01() {
  for(int value = -999; value <= 999; value++) {
    showTitleAndValue("int values", value);
    delay(50);
  }
}

//---------------------------------------------------

void test_02() {
  for(float value = -10.0; value <= 10.0; value = value + 0.1) {
    showTitleAndValue("float values", value);
    delay(50);
  }
}

//---------------------------------------------------

void test_03() {
  String msg = "Lorem ipsum dolor sit amet, consectetur ";
  msg += "adipiscing elit. Suspendisse scelerisque nunc sit ";
  msg += "amet dictum auctor. Vivamus molestie elit ac ante aliquet, ";
  msg += "vitae rhoncus mauris suscipit.";
  showText(msg);
}

//---------------------------------------------------

void loop() {
  test_01();
  test_02();
  test_03();
}

//---------------------------------------------------

