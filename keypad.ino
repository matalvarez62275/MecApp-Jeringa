  #include <Keypad.h>
  #include <LiquidCrystal_I2C.h>

  // Define the keypad
  const byte ROWS = 4; // Four rows
  const byte COLS = 4; // Four columns
  char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
  };
  byte rowPins[ROWS] = {16, 5, 4, 18}; // Connect to the row pinouts of the keypad
  byte colPins[COLS] = {19, 23, 13, 14}; // Connect to the column pinouts of the keypad

  Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

  // Define the LCD
  LiquidCrystal_I2C lcd(0x27, 16, 2);

  // FSM states
  enum State {
    MAIN_MENU,
    SET_FLOW_RATE,
    SET_VOLUME,
    START_INFUSION,
    STOP_INFUSION
  };

  State currentState = MAIN_MENU;
  int flowRate = 0;
  int volume = 0;
  String inputBuffer = "";
  unsigned long lastScrollTime = 0;
  int scrollIndex = 0;

  void setup() {
    lcd.init(); // Corrected call to init
    lcd.backlight();
    displayMenu();
  }

  void loop() {
    char key = keypad.getKey();
    if (key) {
      handleEvent(key);
    }
    scrollMenu();
  }

  void handleEvent(char key) {
    switch (currentState) {
      case MAIN_MENU:
        if (key == '1') {
          currentState = SET_FLOW_RATE;
        } else if (key == '2') {
          currentState = SET_VOLUME;
        } else if (key == '3') {
          currentState = START_INFUSION;
        } else if (key == '4') {
          currentState = STOP_INFUSION;
        }
        break;
      case SET_FLOW_RATE:
        if (key == '#') {
          flowRate = inputBuffer.toInt();
          inputBuffer = "";
          currentState = MAIN_MENU;
        } else if (key == '*') {
          inputBuffer = "";
          currentState = MAIN_MENU;
        } else {
          inputBuffer += key;
        }
        break;
      case SET_VOLUME:
        if (key == '#') {
          volume = inputBuffer.toInt();
          inputBuffer = "";
          currentState = MAIN_MENU;
        } else if (key == '*') {
          inputBuffer = "";
          currentState = MAIN_MENU;
        } else {
          inputBuffer += key;
        }
        break;
      case START_INFUSION:
        if (key == '#') {
          lcd.clear();
          lcd.print("Infusion started");
          delay(2000);
          currentState = MAIN_MENU;
        } else if (key == '*') {
          currentState = MAIN_MENU;
        }
        break;
      case STOP_INFUSION:
        if (key == '#') {
          lcd.clear();
          lcd.print("Infusion stopped");
          delay(2000);
          currentState = MAIN_MENU;
        } else if (key == '*') {
          currentState = MAIN_MENU;
        }
        break;
    }
    displayMenu();
  }

  void displayMenu() {
    lcd.clear();
    switch (currentState) {
      case MAIN_MENU:
        lcd.print("1.Set Flow Rate");
        lcd.setCursor(0, 1);
        lcd.print("2.Set Volume");
        break;
      case SET_FLOW_RATE:
        lcd.print("Enter flow rate:");
        lcd.setCursor(0, 1);
        lcd.print(inputBuffer);
        break;
      case SET_VOLUME:
        lcd.print("Enter volume:");
        lcd.setCursor(0, 1);
        lcd.print(inputBuffer);
        break;
      case START_INFUSION:
        lcd.print("Press # to start");
        break;
      case STOP_INFUSION:
        lcd.print("Press # to stop");
        break;
    }
  }

  void scrollMenu() {
    if (currentState == MAIN_MENU && millis() - lastScrollTime > 2000) { // Slower scroll
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
          lcd.print("4.Stop Infusion");
          break;
        case 3:
          lcd.print("4.Stop Infusion");
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