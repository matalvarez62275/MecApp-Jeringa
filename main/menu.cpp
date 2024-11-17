#include "menu.h"

void displayMenu(State currentState) {
  lcd.clear();
  switch (currentState) {
    case MAIN_MENU:
      lcd.print("1.Set Flow Rate");
      lcd.setCursor(0, 1);
      lcd.print("2.Set Volume");
      break;
    case SET_FLOW_RATE:
      lcd.print("Enter flow rate:");
      lcd.setCursor(12, 1);
      lcd.print("ml/h");
      lcd.setCursor(0, 1);
      lcd.print(inputBuffer);
      break;
    case SET_VOLUME:
      lcd.print("Enter volume:");
      lcd.setCursor(14, 1);
      lcd.print("ml");
      lcd.setCursor(0, 1);
      lcd.print(inputBuffer);
      break;
    case START_INFUSION:
      lcd.print("Press # to start");
      break;
    case SET_SYRINGE:
      lcd.print("<- A");
      lcd.setCursor(12, 0);
      lcd.print("D ->");
      lcd.setCursor(2, 1);
      lcd.print("# to confirm");
      break;
  }
}

void scrollMenu(State currentState) {
  static unsigned long lastScrollTime = 0;
  static int scrollIndex = 0;
  if (currentState == MAIN_MENU && millis() - lastScrollTime > 2000) {
    lastScrollTime = millis();
    scrollIndex = (scrollIndex + 1) % 5;
    lcd.clear();
    switch (scrollIndex) {
      case 0:
        lcd.print("1.Set Flow Rate");
        lcd.setCursor(0, 1);
        lcd.print("2.Set Volume");
        break;
      case 1:
        lcd.print("2.Set Volume");
        lcd.setCursor(0, 1);
        lcd.print("3.Start Infusion");
        break;
      case 2:
        lcd.print("3.Start Infusion");
        lcd.setCursor(0, 1);
        lcd.print("4.Set Syringe");
        break;
      case 3:
        lcd.print("4.Set Syringe");
        lcd.setCursor(0, 1);
        lcd.print(" ");
        break;      
      case 4:
        lcd.print(" ");
        lcd.setCursor(0, 1);
        lcd.print("1.Set Flow Rate");
        break;
    }
  }
}