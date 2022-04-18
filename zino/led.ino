
const int LED1_PIN = 13;     // the number of the LED pin
const int LED2_PIN = 12;     // the number of the LED pin

// Variables will change:
int led1_State = LOW;   // ledState used to set the LED
int led2_State = LOW;

int blink_interval = 500;

unsigned long previousMillis = 0;   // will store last time LED was updated

void setup() {
  SerialASC.begin(9600);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
}

void loop() {
  LED_Blink(4);
}

void LED_Blink(int distance) { // blink_interval : milliseconds
  if(distance < 50 && distance >= 25)
  {
    blink_interval = 500;
  }
  else if(distance < 25 && distance >= 10)
  {
    blink_interval = 350;
  }
  else if(distance < 10 && distance >= 5)
  {
    blink_interval = 200;
  }
  else if(distance < 5)
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
    if(distance <= 50)
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

