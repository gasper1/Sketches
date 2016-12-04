#define LEDPIN A0
#define BTNPIN A7
#define OUTPIN A15

int a7read, out;
bool ON, X, prX;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
  pinMode(BTNPIN, INPUT);
  pinMode(OUTPIN, INPUT);
  ON = 0;
  prX = 0;
}

void loop() {
  
  // Read
  a7read  = analogRead(BTNPIN);
  out     = analogRead(OUTPIN);

  // Input transduction
  prX = X;
  X = a7read < 100 ? 0 : 1;

  // State - input relation
  if(!prX && X) ON = !ON;  

  // Output actuation
  if(ON) {
    analogWrite(LEDPIN, 150);
    Serial.println(out);
  }
  else
    analogWrite(LEDPIN, 0);
  
  delay(100);
}
