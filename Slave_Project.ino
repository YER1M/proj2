const int PWM_A   = 3;
const int DIR_A   = 12;
const int BRAKE_A = 9;
const int PWM_B= 11;
const int DIR_B   = 13;
const int BRAKE_B = 8;

const int gpio1 = 43;
const int gpio2 = 45;
const int gpio3 = 47;


void setup() {
   pinMode(gpio1, INPUT);
   pinMode(gpio2, INPUT);
   pinMode(gpio3, INPUT);
   
   pinMode(BRAKE_A, OUTPUT);  // Brake pin on channel A
   pinMode(DIR_A, OUTPUT);    // Direction pin on channel A
   pinMode(BRAKE_B, OUTPUT);  // Brake pin on channel B
   pinMode(DIR_B, OUTPUT);    // Direction pin on channel B

   digitalWrite(BRAKE_A, LOW);  // setting brake LOW disable motor brake
   digitalWrite(DIR_A, LOW);   // setting direction to HIGH the motor will spin forward
   digitalWrite(BRAKE_B, LOW);  // setting brake LOW disable motor brake
   digitalWrite(DIR_B, HIGH);   // setting direction to HIGH the motor will spin forward

   useArduinoPwmFreq();

   SerialASC.begin(9600);
   SerialASC.println("start");
   
}
void loop() {
  if (digitalRead(gpio3) == 0){
    digitalWrite(BRAKE_A, HIGH);
    digitalWrite(BRAKE_B, HIGH);
  }
  else{
    state = receiveState();
    motor_Rot_L(state);
  }
}

int receiveState(){
  if (digitalRead(gpio1) == 0 && digitalRead(gpio2) == 0) {state=0;}
  else if (digitalRead(gpio1) == 0 && digitalRead(gpio2) == 1) {state=1;}
  else if (digitalRead(gpio1) == 1 && digitalRead(gpio2) == 0) {state=2;}
  else if (digitalRead(gpio1) == 1 && digitalRead(gpio2) == 1) {state=3;}
}

void motor_Rot_L(int state){
  // state 0: 장애물 X, 1: 50cm, 2: 25cm, 3: 10cm
 
  SerialASC.print("state: ");
  SerialASC.println(state);
  
  if (state==0){
    analogWrite(PWM_A, 255);
    analogWrite(PWM_B, 255);
  }
  else {
    analogWrite(PWM_A, 255*0.2*(5-state));
    analogWrite(PWM_B, 255*0.2*(4-state));
  }
}
