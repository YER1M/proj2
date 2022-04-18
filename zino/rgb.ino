
#define LED_ONLY   0
#define LED_AND_BUZZER   1

const int RGB_1_PIN = 9;;     // Red
const int RGB_2_PIN = 10;     // Green
const int RGB_3_PIN = 11;     // Blue

int StartCondition = 0;// 통합할 때 지우기
int Car_Mode = 0; // 통합할 때 지우기


void setup() {
  // put your setup code here, to run once:
  SerialASC.begin(9600);
  pinMode(RGB_1_PIN, OUTPUT);
  pinMode(RGB_2_PIN, OUTPUT);
  pinMode(RGB_3_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  RGB_Mode_Check();
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

