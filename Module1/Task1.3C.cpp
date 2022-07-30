
int ledPin = 13;
int ledPinBtn = 12;
int inputPin = 2;
int inputPinBtn = 3;
int pirState = LOW;
int btnState = LOW;
int val = 0;
int valBtn = 0;

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
  pinMode(inputPinBtn, INPUT);
  attachInterrupt(0, pin_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(inputPinBtn), pin_BTN_ISR, CHANGE);

  Serial.begin(9600);
}

void loop()
{
  
}

void pin_ISR() 
{
  val = digitalRead(inputPin);
  if (val == HIGH) {
    digitalWrite(ledPin, HIGH);
    if (pirState == LOW) {
      Serial.println("Motion detected!");
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW);
    if (pirState == HIGH){
      Serial.println("Motion ended!");
      pirState = LOW;
    }
  }
}

void pin_BTN_ISR()
{
  valBtn = digitalRead(inputPinBtn);
  if (valBtn == HIGH) {
    digitalWrite(ledPinBtn, HIGH);
    if (btnState == LOW) {
      Serial.println("Btn detected!");
      btnState = HIGH;
    }
  } else {
    digitalWrite(ledPinBtn, LOW);
    if (btnState == HIGH){
      Serial.println("Btn ended!");
      btnState = LOW;
    }
  }
}
