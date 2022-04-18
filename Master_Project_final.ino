
#include <ezBuzzer.h>

#define noteDurations 2
#define LED_ONLY   0
#define LED_AND_BUZZER   1
#define trigPin 50
#define echoPin 51

const int LED1_PIN = 13;     // the number of the LED pin
const int LED2_PIN = 12;     // the number of the LED pin
// Variables will change:
int led1_State = LOW;   // ledState used to set the LED
int led2_State = LOW;
unsigned int blink_interval = 500;
unsigned long previousMillis = 0;   // will store last time LED was updated


const int SW1_PIN = 2; // Arduino pin connected to button's pin
const int SW2_PIN = 3; // Arduino pin connected to button's pin]
volatile int Car_Mode = LED_ONLY;
const int BUZZER_PIN = 5;
ezBuzzer buzzer(BUZZER_PIN);
// notes in the melody:
int melody_1[] = {NOTE_E5, 0};
int melody_2[] = {NOTE_GS5, 0};
// note durations: 4 = quarter note, 8 = eighth note, etc, also called tempo:
int noteDurations_50[] = {2,2};
int noteDurations_25[] = {4,4};
int noteDurations_10[] = {8,8};
int noteDurations_5[] = {16,16};


const int RGB_1_PIN = 9;;     // Red
const int RGB_2_PIN = 10;     // Green
const int RGB_3_PIN = 11;     // Blue

/*Ultrasonic Sensor (HC-SR04)*/
//ultrasonic speed : 340m/s
float duration = 0;
float distance = 0;
int state = 0;
int gpio1 = 43;
int gpio2 = 45;
int gpio3 = 47;
//int VarResist = 9;
int StartCondition = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  SerialASC.begin(9600);
  //pinMode(VarResist, OUTPUT);
  pinMode(gpio1, OUTPUT);
  pinMode(gpio2, OUTPUT);
  pinMode(gpio3, OUTPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(SW1_PIN, INPUT_PULLUP); // set arduino pin to input pull-up mode
  pinMode(SW2_PIN, INPUT_PULLUP); // set arduino pin to input pull-up mode
  attachInterrupt(digitalPinToInterrupt(SW1_PIN), Set_Mode_1, RISING);        // D2 의 신호가 0에서 1이될 때 Set_Mode_1 함수 실행
  attachInterrupt(digitalPinToInterrupt(SW2_PIN), Set_Mode_2, RISING);        // D3 의 신호가 0에서 1이될 때 Set_Mode_2 함수 실행
  pinMode(RGB_1_PIN, OUTPUT);
  pinMode(RGB_2_PIN, OUTPUT);
  pinMode(RGB_3_PIN, OUTPUT);
}

float getDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); 
  duration = pulseIn(echoPin, HIGH, 11000); //time[us]
  distance = ((float)(duration)*0.34/10)/2; //time[us]*speed[cm/us]
  SerialASC.print("Distance[cm]: ");
  SerialASC.println(distance);
  return distance;
}

int getState(float distance){
  if( (distance > 25) && (distance <= 50))
    state = 1;
  else if( (distance > 10) && (distance <= 25))
    state = 2;
  else if( (distance > 0) && (distance <= 10))
    state = 3;
  else
    state = 0;
  SerialASC.print("state: ");
  SerialASC.println(state);
  return state;
}



void sendState(int state){
  if (state == 0){
    digitalWrite(gpio1, LOW);
    digitalWrite(gpio2, LOW);
  }
  else if (state ==1) {
    digitalWrite(gpio1, LOW);
    digitalWrite(gpio2, HIGH);
  }
  else if (state ==2) {
    digitalWrite(gpio1, HIGH);
    digitalWrite(gpio2, LOW);
  }
  else {
    digitalWrite(gpio1, HIGH);
    digitalWrite(gpio2, HIGH);
  }
}

int ignitionOn(void){
  int val_resist = analogRead(A0)/4;
  if(val_resist > 100){
    StartCondition = 1;
    digitalWrite(gpio3, HIGH);
  }
  else{
    StartCondition = 0;
    digitalWrite(gpio3, LOW);
  }
  return StartCondition;
}

void Beep(int state)
{
  if ((buzzer.getState() == BUZZER_IDLE) && (Car_Mode == LED_AND_BUZZER)) { // if stopped
    if(state == 1)
    {
      int length = sizeof(noteDurations_25) / sizeof(int);
      buzzer.playMelody(melody_1, noteDurations_25, length); // playing
    }
    else if(state == 2)
    {
      int length = sizeof(noteDurations_10) / sizeof(int);
      buzzer.playMelody(melody_2, noteDurations_10, length); // playing
    }
    else if(state == 3)
    {
      int length = sizeof(noteDurations_5) / sizeof(int);
      buzzer.playMelody(melody_2, noteDurations_5, length); // playing
    }
    else
    {
      Buzzer_Stop();
    }
  }
}

void Buzzer_Stop()
{
  if (buzzer.getState() != BUZZER_IDLE) {
      buzzer.stop() ; // stop
  }
}

void LED_Blink(int state) { // blink_interval : milliseconds
  if(state == 1)
  {
    blink_interval = 500;
  }
  else if(state == 2)
  {
    blink_interval = 300;
  }
  else if(state == 3)
  {
    blink_interval = 100;
  }
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= blink_interval) {
    // if the LED is off turn it on and vice-versa:
    led1_State = (led1_State == LOW) ? HIGH : LOW;
    if(led1_State == HIGH)
    {
      led2_State = LOW;
    }
    else if(led1_State == LOW)
    {
      led2_State = HIGH;
    }
    // set the LED with the ledState of the variable:
    if(state != 0)
    {
      digitalWrite(LED1_PIN, led1_State);
      digitalWrite(LED2_PIN, led2_State);
    }
    else
    {
      digitalWrite(LED1_PIN, LOW);
      digitalWrite(LED2_PIN, LOW);
    }
    // save the last time you blinked the LED
    previousMillis = currentMillis;
  }
}

void Set_Mode_1()
{
  Car_Mode = LED_ONLY;
  SerialASC.println(Car_Mode);
}

void Set_Mode_2()
{
  Car_Mode = LED_AND_BUZZER;
  SerialASC.println(Car_Mode);
}

void RGB_Mode_Check()
{
  if(StartCondition == 0)  // Turn on RED
  {
    digitalWrite(RGB_1_PIN, HIGH);
    digitalWrite(RGB_2_PIN, LOW);
    digitalWrite(RGB_3_PIN, LOW);
  }
  else if(StartCondition == 1)
  {
    if(Car_Mode == LED_ONLY)
    {
      digitalWrite(RGB_1_PIN, LOW);
      digitalWrite(RGB_2_PIN, LOW);
      digitalWrite(RGB_3_PIN, HIGH);
    }
    else if(Car_Mode == LED_AND_BUZZER)
    {
      digitalWrite(RGB_1_PIN, LOW);
      digitalWrite(RGB_2_PIN, HIGH);
      digitalWrite(RGB_3_PIN, LOW);
    }
  }
}

void loop() {
  StartCondition = ignitionOn();
  RGB_Mode_Check();
  if (StartCondition == 0){
    buzzer.stop();
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
  }
  else {
    distance = getDistance();
    state = getState(distance);
    sendState(state);
    buzzer.loop();
    Beep(state);
    LED_Blink(state);
  }  
  //delay(100);
}
