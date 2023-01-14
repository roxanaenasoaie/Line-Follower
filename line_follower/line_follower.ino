#include <QTRSensors.h>
const int m11Pin = 7;
const int m12Pin = 6;
const int m21Pin = 5;
const int m22Pin = 4;
const int m1Enable = 11;
const int m2Enable = 10;
int m1Speed = 0;
int m2Speed = 0;
float kp = 6;
float ki = 0;
float kd = 2;
int p = 1;
int i = 0;
int d = 0;
int error = 0;
int lastError = 0;
const int maxSpeed = 255;
const int minSpeed = -255;
const int baseSpeed = 225;
QTRSensors qtr;
const int sensorCount = 6;
int sensorValues[sensorCount];
int sensors[sensorCount] = { 0, 0, 0, 0, 0, 0 };


void setup() {
  pinMode(m11Pin, OUTPUT);
  pinMode(m12Pin, OUTPUT);
  pinMode(m21Pin, OUTPUT);
  pinMode(m22Pin, OUTPUT);
  pinMode(m1Enable, OUTPUT);
  pinMode(m2Enable, OUTPUT);
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){ A0, A1, A2, A3, A4, A5 },
                    sensorCount);
  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  for (uint16_t i = 0; i < 100; i++) {
    if (i <= 15) {
      setMotorSpeed(170, -170);
    }
    if (i > 15 && i <= 30) {
      setMotorSpeed(-250, 250);
    }
    if (i > 30 && i < 45) {
      setMotorSpeed(250, -250);
    }
    if (i > 45 && i <= 60) {
      setMotorSpeed(-250, 250);
    }
    if (i > 60 && i < 75) {
      setMotorSpeed(170, -170);
    }
    if (i > 75) {
      setMotorSpeed(0, 0);
    }
    qtr.calibrate();
  }
  setMotorSpeed(0, 0);

    
    //to do
  
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);
}


void loop() {
  pidControl(kp, ki, kd);
}


// calculate PID value based on error, kp, kd, ki, p, i and d.
void pidControl(float kp, float ki, float kd) {
  int error = map(qtr.readLineBlack(sensorValues), 0, 5000, -75, 75);
  p = error;
  i = i + error;
  d = error - lastError;
  int motorSpeed = kp * p + ki * i + kd * d;
  lastError = error;
  m1Speed = baseSpeed;
  m2Speed = baseSpeed;
  if (error < 0) {
    m1Speed += motorSpeed;
  } else if (error > 0) {
    m2Speed -= motorSpeed;
  }
  
  m1Speed = constrain(m1Speed, -220, maxSpeed);
  m2Speed = constrain(m2Speed, -220, maxSpeed);
  setMotorSpeed(m2Speed, m1Speed);
}
void setMotorSpeed(int motor1Speed, int motor2Speed) {
  motor1Speed = -motor1Speed;
  motor2Speed = -motor2Speed;
  if (motor1Speed == 0) {
    digitalWrite(m11Pin, LOW);
    digitalWrite(m12Pin, LOW);
    analogWrite(m1Enable, motor1Speed);
  } else {
    if (motor1Speed > 0) {
      digitalWrite(m11Pin, HIGH);
      digitalWrite(m12Pin, LOW);
      analogWrite(m1Enable, motor1Speed);
    }
    if (motor1Speed < 0) {
      digitalWrite(m11Pin, LOW);
      digitalWrite(m12Pin, HIGH);
      analogWrite(m1Enable, -motor1Speed);
    }
  }
  if (motor2Speed == 0) {
    digitalWrite(m21Pin, LOW);
    digitalWrite(m22Pin, LOW);
    analogWrite(m2Enable, motor2Speed);
  } else {
    if (motor2Speed > 0) {
      digitalWrite(m21Pin, HIGH);
      digitalWrite(m22Pin, LOW);
      analogWrite(m2Enable, motor2Speed);
    }
    if (motor2Speed < 0) {
      digitalWrite(m21Pin, LOW);
      digitalWrite(m22Pin, HIGH);
      analogWrite(m2Enable, -motor2Speed);
    }
  }
}

void debugFunction() {
  Serial.print("Error: ");
  Serial.println(error);
  Serial.print("M1 speed: ");
  Serial.println(m1Speed);
  
  Serial.print("M2 speed: ");
  Serial.println(m2Speed);
  
  delay(250);
}