/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-button-toggle-led
 */

#define LED_ONLY   0
#define LED_AND_BUZZER   1

// constants won't change
const int SW1_PIN = 2; // Arduino pin connected to button's pin
const int SW2_PIN = 3; // Arduino pin connected to button's pin

volatile int Car_Mode = LED_ONLY;

void setup() {
  SerialASC.begin(9600);
  pinMode(SW1_PIN, INPUT_PULLUP); // set arduino pin to input pull-up mode
  pinMode(SW2_PIN, INPUT_PULLUP); // set arduino pin to input pull-up mode
  attachInterrupt(digitalPinToInterrupt(SW1_PIN), Set_Mode_1, RISING);        // D2 의 신호가 0에서 1이될 때 Set_Mode_1 함수 실행
  attachInterrupt(digitalPinToInterrupt(SW2_PIN), Set_Mode_2, RISING);        // D3 의 신호가 0에서 1이될 때 Set_Mode_2 함수 실행
  
}

void loop() {
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

