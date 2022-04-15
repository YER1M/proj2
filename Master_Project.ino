#define trigPin 50
#define echoPin 51
/*Ultrasonic Sensor (HC-SR04)*/
//ultrasonic speed : 340m/s
float duration = 0;
float distance = 0;
int state = 0;

int gpio1 = 43;
int gpio2 = 45;
int gpio3 = 47;
//int Lv1 ,Lv2, Lv3, Lv4;
int VarResist = 9;
int StartCondition = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  SerialASC.begin(9600);
  pinMode(VarResist, OUTPUT);
  pinMode(gpio1, OUTPUT);
  pinMode(gpio2, OUTPUT);
  pinMode(gpio3, OUTPUT);
  
}

void loop() {
  
  StartCondition = ignitionOn();
  distance = getDistance();
  state = getState(distance);
  sendState(state);  
  delay(100);
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
  else // state == 3{
    digitalWrite(gpio1, HIGH);
    digitalWrite(gpio2, HIGH);
  }
}

int ignitionOn(void){
  int val_resist = analogRead(A0)/4;
  analogWrite(VarResist, val_resist);  // Test 가변저항

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
