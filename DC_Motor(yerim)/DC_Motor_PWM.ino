const int PWM_A   = 3;
const int DIR_A   = 12;
const int BRAKE_A = 9;
const int PWM_B= 11;
const int DIR_B   = 13;
const int BRAKE_B = 8;


void setup() {
   // Configure the A output
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
   motor_Rot_L(0);
   delay(500);
   motor_Rot_L(1);
   delay(500);
   motor_Rot_L(2);
   delay(500);
   motor_Rot_L(3);
   delay(500);
}

void motor_Rot_L(int state){
  // state 0: 장애물 X, 1: 50cm, 2: 20cm, 3: 10cm
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
