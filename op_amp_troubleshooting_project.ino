#include <IRremote.hpp>

#define BTN_POWER 0x45
#define BTN_0 0x16
#define BTN_EQ 0x19
#define BTN_ST_REPT 0xD
#define BTN_1 0xC
#define BTN_2 0x18
#define BTN_3 0x5E
#define BTN_4 0x8
#define BTN_5 0x1C
#define BTN_6 0x5A
#define BTN_7 0x42
#define BTN_8 0x52
#define BTN_9 0x4A

int pins[] = {
  2, 3, 4, 5,
  6, 7, 8, 9,
  10, 11, 12, 13
};
int defaults[] = {
  HIGH, LOW, LOW, HIGH,
  LOW, LOW, LOW, HIGH,
  LOW, LOW, HIGH, LOW
};
int indicatorPin = A1;
int pinToLight = -1;
IRrecv irrecv(2);
decode_results results;

void setup() {
  while (!Serial);
  Serial.begin(9600);
  Serial.println("Startup");

  for (int pin : pins) {
    pinMode(pin, OUTPUT);
  }
  pinMode(indicatorPin, OUTPUT);
  IrReceiver.begin(A0, DISABLE_LED_FEEDBACK);
}

void loop() {
  for (int i = 0; i < (sizeof(pins) / sizeof(pins[0])); i++) {
    int pin = pins[i];
    if (pin == pinToLight) {
      digitalWrite(pin, !defaults[i]);
    } else {
      digitalWrite(pin, defaults[i]);
    }
  }
  
  if (!IrReceiver.decode()) return;

  bool showWorking = true;
  uint16_t command = IrReceiver.decodedIRData.command;
  switch (command) {
    case BTN_POWER:
      Serial.println("Power button");
      pinToLight = -1;
      break;
    case BTN_0:
      pinToLight = pins[0];
      Serial.println("Button 0");
      break;
    case BTN_EQ:
      pinToLight = pins[1];
      Serial.println("EQ Button");
      break;
    case BTN_ST_REPT:
      pinToLight = pins[2];
      Serial.println("ST/REPT Button");
      break;
    case BTN_1:
      pinToLight = pins[3];
      Serial.println("Button 1");
      break;
    case BTN_2:
      pinToLight = pins[4];
      Serial.println("Button 2");
      break;
    case BTN_3:
      pinToLight = pins[5];
      Serial.println("Button 3");
      break;
    case BTN_4:
      pinToLight = pins[6];
      Serial.println("Button 4");
      break;
    case BTN_5:
      pinToLight = pins[7];
      Serial.println("Button 5");
      break;
    case BTN_6:
      pinToLight = pins[8];
      Serial.println("Button 6");
      break;
    case BTN_7:
      pinToLight = pins[9];
      Serial.println("Button 7");
      break;
    case BTN_8:
      pinToLight = pins[10];
      Serial.println("Button 8");
      break;
    case BTN_9:
      pinToLight = pins[11];
      Serial.println("Button 9");
      break;
    default:
      Serial.print("Command: 0x");
      Serial.println(command, HEX);
      showWorking = false;
  }
  
  if (showWorking) {
    digitalWrite(indicatorPin, HIGH);
    delay(250);
    digitalWrite(indicatorPin, LOW);
  }
  
  IrReceiver.resume();
}
