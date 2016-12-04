#define PIN_BTN 12
#define PIN_LSB 2
#define PIN_MSB 3

#define NOT(VAL) ~VAL & 0x01

int counter;
boolean MSB, LSB, prevMSB, prevLSB;

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_BTN, INPUT);
  pinMode(PIN_LSB, INPUT);
  pinMode(PIN_MSB, INPUT);
  
  digitalWrite(PIN_LSB, HIGH); //turn pullup resistor on
  digitalWrite(PIN_MSB, HIGH); //turn pullup resistor on
  MSB = true;
  LSB = true;
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  counter = 0;  
  if (isButtonPressed()) {
    Serial.println("Bottone schiacciato!");
    while (isButtonPressed());
    while (!isButtonPressed()) {
      counter += readEncoder();
      Serial.print("counter ");
      Serial.println(counter);
      delay(2);
    }
    while (isButtonPressed());
  }
}

boolean isButtonPressed() {
  int val = 0;
  for (int i = 0; i < 50; i++) {
    if (digitalRead(PIN_BTN) == HIGH) {
      val++;
      delay(1);
    }
  }
  return val > 45;
}

/* returns change in encoder state (-1,0,1) */
int8_t readEncoder()
{
  prevLSB = LSB;
  prevMSB = MSB;
  LSB = digitalRead(PIN_LSB) == HIGH;
  MSB = digitalRead(PIN_MSB) == HIGH;

  // Tells which bit changes. The increments/decrements happens in Gray code, so either one or the other changes, but not both.
  boolean changeLSB = prevLSB^LSB;
  boolean changeMSB = prevMSB^MSB;

  // Tells the direction of the rotation.
  //  sign : 0 -> rotation : -1 counterclockwise (DECREMENT)
  //  sign : 1 -> rotation : +1 clockwise (INCREMENT)
  boolean sign = (NOT(MSB) & NOT(LSB) & NOT(changeLSB)) | (NOT(MSB) & LSB & NOT(changeMSB)) | (MSB & NOT(LSB) & NOT(changeMSB)) | (MSB & LSB & NOT(changeLSB));

  if( changeMSB == changeLSB ) {
    return 0;
  }
  return sign ? 1 : -1;
}
