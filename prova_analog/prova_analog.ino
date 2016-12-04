int analogValue;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A1, OUTPUT);   //dichiarazione pin in lettura
  //pinMode(A1, OUTPUT);  //dichiarazione pin output
}

void loop() {
  analogValue = 1000;
  /*for(int i=0;i<100;i++) {
    analogValue += analogRead(A0);
    delay(1);  
  }
  analogValue /= 100;*/
  
  digitalWrite(A1,HIGH);
  delay(1000);
}
