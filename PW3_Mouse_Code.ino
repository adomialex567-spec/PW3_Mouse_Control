const int leftSensorPin = A0;
const int rightSensorPin = A1;

const int leftMotorPin = 5;
const int rightMotorPin = 6;

int baseSpeed = 180;
float steeringGain = 0.4;

void setup() {
  pinMode(leftMotorPin, OUTPUT);
  pinMode(rightMotorPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int leftSensor = analogRead(leftSensorPin);
  int rightSensor = analogRead(rightSensorPin);

  // Difference between sensors determines steering demand
  int error = leftSensor - rightSensor;

  // Steering correction
  int correction = (int)(steeringGain * error);

  // Fixed base speed
  int leftMotorSpeed = baseSpeed - correction;
  int rightMotorSpeed = baseSpeed + correction;

  // Keep outputs in valid PWM range
  leftMotorSpeed = constrain(leftMotorSpeed, 0, 255);
  rightMotorSpeed = constrain(rightMotorSpeed, 0, 255);

  analogWrite(leftMotorPin, leftMotorSpeed);
  analogWrite(rightMotorPin, rightMotorSpeed);

  Serial.print("Left: ");
  Serial.print(leftSensor);
  Serial.print(" Right: ");
  Serial.print(rightSensor);
  Serial.print(" Error: ");
  Serial.print(error);
  Serial.print(" Left motor: ");
  Serial.print(leftMotorSpeed);
  Serial.print(" Right motor: ");
  Serial.println(rightMotorSpeed);

  delay(50);
}