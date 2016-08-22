#include <LiquidCrystal.h>
#include <LCDKeypad.h>
#include <TimerOne.h>
 
const byte buttonPin = A0; // analogue pin 0

LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7);

enum{KEY_SELECT, KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP, KEY_NONE};
unsigned int adc_key_val[5] = {614, 815, 856, 904, 931}; // error +/-5
unsigned int NUM_KEYS = 5;
unsigned int key = KEY_NONE;

unsigned int adc_error = 5;
volatile unsigned int adc_value = 1023; // default none
unsigned int i;

String s1 = "hello, world!   ";
String s2;

// timer1 ISR
void refresh(void)
{  
  lcd.setCursor(0,0);
  lcd.print(s1);
  lcd.setCursor(0,1);
  lcd.print(s2);
}

void get_time()
{
  s2 = String(millis()/1000);  
}

void handle_keypress()
{
  // identify which key was pressed based on the latest ADC value
  adc_value = analogRead(0);
  key = KEY_NONE;
  for (i = 0; i < NUM_KEYS; i++) {
    if (adc_value < adc_key_val[i] + adc_error) {
      key = i;
      break;
    }
  }
  
  // perform action based on key
  if (key == KEY_SELECT) {
    s1 = "select key      ";
  } else if (key == KEY_RIGHT) {
    s1 = "right key       ";
  } else if (key == KEY_LEFT) {
    s1 = "left key        ";
  } else if (key == KEY_DOWN) {
    s1 = "down key        ";
  } else if (key == KEY_UP) {
    s1 = "up key          ";
  } else {
    s1 = "no key pressed  ";
  }
}

void setup(void)
{
  // LCD setup
  lcd.begin(16, 2);
  lcd.setCursor(0,0);

  pinMode(buttonPin, INPUT);
  
  // interrupt every 100ms to refresh the LCD
  Timer1.initialize(100000); // delay in us
  Timer1.attachInterrupt(refresh);
}

void loop(void)
{
  get_time();
  handle_keypress();
}
