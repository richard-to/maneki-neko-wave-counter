#include "DFRobot_RGBLCD1602.h"  // Using version 1.0 of the library

// Update these values based on your waving cat.
#define WAVE_UP_DISTANCE_CM 40
#define WAVE_DOWN_DISTANCE_CM 6
// Enable debugging through Serial
#define DEBUG false
// Used for checking presses to `select` button.
#define LCD_BTNS A0 
// Sharp IR GP2Y0A41SKOF (4-30cm, analog)
#define IR_SENSOR A1  
#define COLS 16
#define ROWS 2
#define NUM_COLORS 7
#define SELECT_BTN_MIN_VAL 800
#define SELECT_BTN_MAX_VAL 850
#define NO_BTN_MIN_VAL 1000

struct Rgb{
   int red;
   int green;
   int blue;
};

// Constants
const Rgb kRed = {255, 0, 0};
const Rgb kOrange = {255, 140, 0};
const Rgb kYellow = {255, 255, 0};
const Rgb kGreen = {0, 255, 0};
const Rgb kBlue = {0, 0, 255};
const Rgb kIndigo = {255, 0, 255};
const Rgb kViolet = {238, 130, 238};

const String kLcdText = "Number of waves:";

// Variables

// LCD library.
DFRobot_RGBLCD1602 lcd(/*lcdCols=*/COLS,/*lcdRows=*/ROWS);
// Available background colors.
Rgb colors[NUM_COLORS] = {kRed, kOrange, kYellow, kGreen, kBlue, kIndigo, kViolet};
// Current background color. Used for cycling through different colors 
// in `colors` array.
int colorIndex = 0;
// Tracks select button presses.
bool hasPressedSelect = false;
// Tracks a hand wave.
bool hasWaved = false;
// Number of hand waves.
int waveCount = 0;

void setup() {
  if (DEBUG) {
    Serial.begin(9600);
  }
  lcd.init();
  setLcdBg(kGreen);
  lcd.print(kLcdText);
  updateLcdWaveCount(waveCount);
}

void loop() {
  int distanceCm = calcIrDistance();

  // Add a small delay to avoid unnecessary processing.
  delay(100);
  
  if (DEBUG) {
    Serial.println(distanceCm);
  }

  if (selectPressed()) {
    updateLcdColor();
  }

  if (waveFinished(distanceCm)) {
    ++waveCount;
    updateLcdWaveCount(waveCount);
  }
}

// Returns true if `select` button was pressed.
//
// The buttons all feed into the `LCD_BTNS` analog pin. Each
// button split within a range of 0-1023.
//
// The `select` button supposedly yields a value of 824. But 
// since there may be interference in the signal, we add some
// buffer.
// 
// When no value is present, the value should be 1023, but we
// will also provide a buffer here too.
//
// A button press consists of a signal of 824 followed by a 
// signal of 1023. Otherwise multiple presses may be registered.
bool selectPressed() {
  int lcdKeyInput = analogRead(LCD_BTNS);

  // This is the range for `select` being pressed.
  if (lcdKeyInput > SELECT_BTN_MIN_VAL && lcdKeyInput < SELECT_BTN_MAX_VAL) {
    if (!hasPressedSelect) {
      hasPressedSelect = true;
    }
  } else if (hasPressedSelect && lcdKeyInput > NO_BTN_MIN_VAL) {
    hasPressedSelect = false;
    return true;
  }
  return false;
}

// Tracks whether that has finished waving. A wave consists 
// of a down swing followed by an up swing.
bool waveFinished(int distanceCm) {
  if (!hasWaved && distanceCm <= WAVE_DOWN_DISTANCE_CM) {
    hasWaved = true;  
  } else if (hasWaved && distanceCm > WAVE_UP_DISTANCE_CM) {
    hasWaved = false;
    return true;
  }
  return false;
}

// Cycles through the available LCD colors.
void updateLcdColor() {
  colorIndex = (colorIndex + 1) % NUM_COLORS;
  setLcdBg(colors[colorIndex]);
}

// Sets the LCD background color with the given RGB values.
void setLcdBg(Rgb color) {
  lcd.setRGB(color.red, color.green, color.blue);
}

// Updates the wave count on the LCD display.
void updateLcdWaveCount(int count) {
  lcd.setCursor(0, 1);  
  lcd.print(count);
}

// Calculates distance in centimeters from the IR sensor.
// Formula from: https://www.smart-prototyping.com/blog/Sharp-Distance-Measuring-Sensor-GP2Y0A41SK0F-Tutorial
int calcIrDistance() {
  float volts = analogRead(IR_SENSOR) * 0.0048828125;
  return 13 * pow(volts, -1);
}
