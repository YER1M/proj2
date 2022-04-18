#include <ezBuzzer.h> // ezBuzzer library

#define noteDurations 2
#define LED_ONLY   0
#define LED_AND_BUZZER   1

const int BUZZER_PIN = 5;

ezBuzzer buzzer(BUZZER_PIN); // create ezBuzzer object that attach to a pin;

// notes in the melody:
int melody_1[] = {NOTE_E5, 0};
int melody_2[] = {NOTE_GS5, 0};

// note durations: 4 = quarter note, 8 = eighth note, etc, also called tempo:
int noteDurations_50[] = {2,2};
int noteDurations_25[] = {4,4};
int noteDurations_10[] = {8,8};
int noteDurations_5[] = {16,16};

int Car_Mode = 1; // 통합할 때 지우기

void setup() {
  // put your setup code here, to run once:
  SerialASC.begin(9600);
}

void loop() {
  buzzer.loop();
  // put your main code here, to run repeatedly:
  Beep(4);
}


void Beep(int distance)
{
  if ((buzzer.getState() == BUZZER_IDLE) && (Car_Mode == LED_AND_BUZZER)) { // if stopped
    if(distance < 50 && distance >= 25)
    {
      int length = sizeof(noteDurations_50) / sizeof(int);
      buzzer.playMelody(melody_1, noteDurations_50, length); // playing
    }
    else if(distance < 25 && distance >= 10)
    {
      int length = sizeof(noteDurations_25) / sizeof(int);
      buzzer.playMelody(melody_1, noteDurations_25, length); // playing
    }
    else if(distance < 10 && distance >= 5)
    {
      int length = sizeof(noteDurations_10) / sizeof(int);
      buzzer.playMelody(melody_2, noteDurations_10, length); // playing
    }
    else if(distance < 5)
    {
      int length = sizeof(noteDurations_5) / sizeof(int);
      buzzer.playMelody(melody_2, noteDurations_5, length); // playing
    }
  }
  
}

void Buzzer_Stop()
{
  if (buzzer.getState() != BUZZER_IDLE) {
      buzzer.stop() ; // stop
  }
}

/*
void Beep_2(int distance)
{
  if(distance >= 50)
  {
    buzzer.beep(500); // generates a 500ms beep
  }
  else if(distance < 50 && distance >= 25)
  {
    buzzer.beep(400); // generates a 400ms beep
  }
  else if(distance < 25 && distance >= 10)
  {
    buzzer.beep(300); // generates a 300ms beep
  }
  else if(distance < 10 && distance >= 5)
  {
    buzzer.beep(200); // generates a 200ms beep
  }
  else
  {
    buzzer.beep(100); // generates a 100ms beep
  }
}
*/


