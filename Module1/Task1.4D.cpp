int ledPin = 13;
int ledPinBtn = 12;
int ledPinBtn2 = 11;
int ledTimed = 10;
int inputPin = 2;
int inputPinBtn = 3;
int inputPinBtn2 = 4;
int pirState = LOW;
int btnState = LOW;
int btn2State = LOW;
int val = 0;
int valBtn = 0;
int valBtn2 = 0;

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(ledTimed, OUTPUT);
  pinMode(inputPin, INPUT);
  pinMode(inputPinBtn, INPUT);
  pinMode(inputPinBtn2, INPUT);
  
  startTimer();

  PCICR  |= B00000100; //Group 2
  PCMSK2 |= B00011100;
  Serial.begin(9600);
}

void loop()
{
  
}

void startTimer(){
  noInterrupts();
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  // we want turn led 10 to blink every 1 seconds
  //Set timer compare
  OCR1A = 15624;
  
  // Prescaler 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // Output Compare Match A Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);
  // CTC
  TCCR1B |= (1 << WGM12);
  
  
  interrupts();
}

ISR(TIMER1_COMPA_vect){
   digitalWrite(ledTimed, digitalRead(ledTimed) ^ 1);
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


void pin_BTN2_ISR()
{
  valBtn2 = digitalRead(inputPinBtn2);
  if (valBtn2 == HIGH) {
    digitalWrite(ledPinBtn2, HIGH);
    if (btn2State == LOW) {
      Serial.println("Btn 2 detected!");
      btn2State = HIGH;
    }
  } else {
    digitalWrite(ledPinBtn2, LOW);
    if (btn2State == HIGH){
      Serial.println("Btn 2 ended!");
      btn2State = LOW;
    }
  }
}

ISR (PCINT2_vect){
  
  if (val != digitalRead(inputPin)){
  	pin_ISR();
  }
  if(valBtn != digitalRead(inputPinBtn)){
    pin_BTN_ISR();
  }
  if(valBtn2 != digitalRead(inputPinBtn2)){
    pin_BTN2_ISR();
  }
}

