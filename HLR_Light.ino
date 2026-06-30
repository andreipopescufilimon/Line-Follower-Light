// ================================================================
//               H Y P E R L I N E   R O B O T I C S
// ================================================================
//                    FIRMWARE:  HLR_V5.1 + V3 SPEED LOGIC
//                    PLATFORM:  ATmega328P, IFX9201SG
// ================================================================

#include <Arduino.h>
#include <Servo.h>

// ================================================================
//                        PINS
// ================================================================
#define IMP_PIN 10
#define START_PIN 12

#define PWMA 5
#define DIRA 3

#define PWMB 6
#define DIRB 4

#define LED 13

#define S0 A3
#define S1 A2
#define S2 A1
#define S3 A0
#define SENSOR_OUT A4

// ================================================================
//                        SETTINGS
// ================================================================
#define NUM_SENSORS 16
#define DEBUG_MODE false

// ================================================================
//                        PID
// ================================================================
float KP = 0.03;
float KD = 0.7;

int lastError = 0;
int lastPosition = 7500;

// ================================================================
//                        SPEEDS
// ================================================================
int baseSpeed = 170;
int maxSpeed = 245;
int turnSpeed = 160;

// ================================================================
//                        EDF
// ================================================================
Servo impellerESC;

int impTarget = 1600;
int impNow = 1000;
int rampStep = 10;
int rampInterval = 20;

unsigned long lastRamp = 0;
bool impOn = false;

// ================================================================
//                        SENSORS
// ================================================================
int sensorValues[NUM_SENSORS];

// ================================================================
//                        TURN LOGIC
// ================================================================
bool turning = false;
unsigned long turnStart = 0;
const int reverseImpulseTime = 8;

// ================================================================
//        FIXED MUX SELECT FOR WIRING: S0=A3 S1=A2 S2=A1 S3=A0
// ================================================================
inline void selectMuxChannel(uint8_t ch) {
  uint8_t out = 0;

  if (ch & 0x01) out |= (1 << PC3); // S0 on A3
  if (ch & 0x02) out |= (1 << PC2); // S1 on A2
  if (ch & 0x04) out |= (1 << PC1); // S2 on A1
  if (ch & 0x08) out |= (1 << PC0); // S3 on A0

  PORTC = (PORTC & 0xF0) | out;
}

// ================================================================
//                        FAST ADC
// ================================================================
inline uint16_t fastAnalogRead(uint8_t ch) {
  ADMUX = (1 << REFS0) | (ch & 0x0F);
  ADCSRA |= (1 << ADSC);

  while (ADCSRA & (1 << ADSC));

  uint8_t low = ADCL;
  uint8_t high = ADCH;

  return (high << 8) | low;
}

// ================================================================
//                        MOTOR CONTROL
// ================================================================
void setMotorA(int pwm) {
  pwm = constrain(pwm, -255, 255);

  analogWrite(PWMA, abs(pwm));

  if (pwm > 0) {
    PORTD &= ~(1 << PORTD3);
  } else if (pwm < 0) {
    PORTD |= (1 << PORTD3);
  }
}

void setMotorB(int pwm) {
  pwm = constrain(pwm, -255, 255);

  analogWrite(PWMB, abs(pwm));

  if (pwm > 0) {
    PORTD |= (1 << PORTD4);
  } else if (pwm < 0) {
    PORTD &= ~(1 << PORTD4);
  }
}

void stopDrive() {
  setMotorA(0);
  setMotorB(0);
}

// ================================================================
//                        EDF RAMP
// ================================================================
void updateImpeller() {
  unsigned long now = millis();

  if (now - lastRamp >= (unsigned long)rampInterval) {
    lastRamp = now;

    if (impNow < impTarget) {
      impNow = min(impNow + rampStep, impTarget);
      impellerESC.writeMicroseconds(impNow);
    } else {
      impOn = true;
    }
  }
}

// ================================================================
//                        READ LINE POSITION
// ================================================================
uint16_t readLinePosition() {
  uint32_t sum = 0;
  uint32_t weightedSum = 0;

  for (uint8_t i = 0; i < NUM_SENSORS; i++) {
    selectMuxChannel(i);
    delayMicroseconds(5);

    uint16_t value = fastAnalogRead(4);

    if (value < 200) value = 0;

    sensorValues[i] = value;

    uint16_t sensorPos = (uint32_t)i * 15000UL / (NUM_SENSORS - 1);

    sum += value;
    weightedSum += (uint32_t)value * sensorPos;
  }

  if (sum == 0) {
    return lastPosition;
  }

  lastPosition = weightedSum / sum;
  return lastPosition;
}

// ================================================================
//              ADAPTIVE SPEED BASED ON LINE POSITION
// ================================================================
void updateSpeedByPosition(uint16_t position) {
  int distanceFromCenter = abs((int)position - 7500);

  if (distanceFromCenter < 1200) {
    baseSpeed = 150;
    maxSpeed = 230;
    turnSpeed = 150;
  } 
  else if (distanceFromCenter < 3000) {
    baseSpeed = 130;
    maxSpeed = 220;
    turnSpeed = 160;
  } 
  else if (distanceFromCenter < 5000) {
    baseSpeed = 80;
    maxSpeed = 190;
    turnSpeed = 150;
  } 
  else {
    baseSpeed = 45;
    maxSpeed = 180;
    turnSpeed = 130;
  }
}

// ================================================================
//                        BRAKE TURNS
// ================================================================
void turnLeftBrake() {
  updateImpeller();

  setMotorA(-turnSpeed);
  setMotorB(turnSpeed);
  delay(reverseImpulseTime);

  setMotorA(0);
  setMotorB(turnSpeed);
}

void turnRightBrake() {
  updateImpeller();

  setMotorA(turnSpeed);
  setMotorB(-turnSpeed);
  delay(reverseImpulseTime);

  setMotorA(turnSpeed);
  setMotorB(0);
}

// ================================================================
//                        SETUP
// ================================================================
void setup() {
  pinMode(PWMA, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRB, OUTPUT);

  pinMode(START_PIN, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  DDRC |= 0x0F;

  cli();
  ADMUX = (1 << REFS0);
  ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
  sei();

  if (DEBUG_MODE) {
    Serial.begin(115200);
  }

  impellerESC.attach(IMP_PIN);
  impellerESC.writeMicroseconds(1000);

  delay(3000);

  stopDrive();

  digitalWrite(LED, HIGH);
  delay(200);
  digitalWrite(LED, LOW);
  delay(200);
  digitalWrite(LED, HIGH);

  if (DEBUG_MODE) {
    Serial.println("=== HLR_V5.1 FIXED MUX + V3 SPEED LOGIC ===");
  }
}

// ================================================================
//                        LOOP
// ================================================================
void loop() {
  bool run = digitalRead(START_PIN) == HIGH;

  if (run && !impOn) {
    updateImpeller();
    stopDrive();
    return;
  }

  if (run && impOn) {
    uint16_t position = readLinePosition();

    updateSpeedByPosition(position);

    int error = 7500 - (int)position;
    int derivative = error - lastError;
    lastError = error;

    int correction = (KP * error) + (KD * derivative);

    int leftSpeed = baseSpeed - correction;
    int rightSpeed = baseSpeed + correction;

    leftSpeed = constrain(leftSpeed, -maxSpeed, maxSpeed);
    rightSpeed = constrain(rightSpeed, -maxSpeed, maxSpeed);

    if (position <= 1000) {
      turnLeftBrake();
    } 
    else if (position >= 14000) {
      turnRightBrake();
    } 
    else {
      setMotorA(leftSpeed);
      setMotorB(rightSpeed);
    }

    if (DEBUG_MODE) {
      Serial.print("Pos: ");
      Serial.print(position);

      Serial.print("\tErr: ");
      Serial.print(error);

      Serial.print("\tBase: ");
      Serial.print(baseSpeed);

      Serial.print("\tL: ");
      Serial.print(leftSpeed);

      Serial.print("\tR: ");
      Serial.print(rightSpeed);

      Serial.print("\tSensors: ");
      for (uint8_t i = 0; i < NUM_SENSORS; i++) {
        Serial.print(sensorValues[i]);
        Serial.print(' ');
      }

      Serial.println();
    }
  } 
  else {
    if (impOn) {
      setMotorA(-80);
      setMotorB(-80);
      delay(30);

      impellerESC.writeMicroseconds(1700);
      delay(80);

      setMotorA(0);
      setMotorB(0);
      delay(20);

      impellerESC.writeMicroseconds(1000);

      impNow = 1000;
      impOn = false;
    }

    stopDrive();
  }
}