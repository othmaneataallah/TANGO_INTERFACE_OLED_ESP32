#include <Arduino.h>

#include <SPI.h>
#include <U8g2lib.h>

#include "ScreenManager.h"

#define OLED_CS 5
#define OLED_DC 2
#define OLED_RESET 4

U8G2_SSD1309_128X64_NONAME0_F_4W_HW_SPI u8g2(U8G2_R0, OLED_CS, OLED_DC, OLED_RESET);

#define UP_BUTTON 32
#define BACK_BUTTON 33
#define SELECT_BUTTON 34
#define DOWN_BUTTON 35

ScreenManager screenManager; // Create an instance of ScreenManager



void setup()
{
  pinMode(UP_BUTTON, INPUT);
  pinMode(BACK_BUTTON, INPUT);
  pinMode(SELECT_BUTTON, INPUT);
  pinMode(DOWN_BUTTON, INPUT);


  u8g2.begin();
  screenManager.initialize(); // Initialize your screen manager and load all screens
}

void loop()
{
  screenManager.handleInput();              // Handle user input
  screenManager.displayCurrentScreen(u8g2); // Display the current screen
}
