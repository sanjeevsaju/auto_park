/* Program to auto park the vehicle using HC-SR04 ultrasonic sensor and HW-095 H bridge DC motor controller */

#define min_length 15
#define min_threshold 4

/* HW-095 sensor pin configurations */
#define trigPin 11
#define echoPin 10
#define PWM_150 150
#define PWM_200 200

/* Global variable for HW-095 sensor calculatioins */
float distance;
float d;
long duration;

bool space_detected;

float getDistance() {

  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}

// Motor 1
int dir1PinA = 8;
int dir2PinA = 7;
int speedPinA = 9; // Needs to be a PWM pin to be able to control motor speed

// Motor 2
int dir1PinB = 5;
int dir2PinB = 4;
int speedPinB = 3; // Needs to be a PWM pin to be able to control motor speed

/* Vehicle maneuver functions */

void stop_motor() {

  analogWrite(speedPinA, 0);
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);

  analogWrite(speedPinB, 0);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);

}

void move_forward() {

  /* Left Motor pair */
  analogWrite(speedPinA, PWM_150);
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);

  /* Right motor pair */
  analogWrite(speedPinB, PWM_150);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);

  Serial.println("Moving forward");
  Serial.println("   "); // Creates a blank line printed on the serial monitor
  stop_motor();
}


void move_backward() {

  /* Left Motor pair */
  analogWrite(speedPinA, PWM_150);
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);

  /* Right motor pair */
  analogWrite(speedPinB, PWM_150);
  digitalWrite(dir1PinB, HIGH);
  digitalWrite(dir2PinB, LOW);

  Serial.println("Moving backward");
  Serial.println("   "); // Creates a blank line printed on the serial monitor

}

void turn_right_front() {

  /* Right motor pair */
  analogWrite(speedPinB, 0);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, LOW);

  /* Left Motor pair */
  analogWrite(speedPinA, PWM_150);
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);


  Serial.println("Turn right front");
  Serial.println("   "); // Creates a blank line printed on the serial monitor
}

void turn_left_front() {

  /* Left Motor pair */
  analogWrite(speedPinA, 0);
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, LOW);

  /* Right motor pair */
  analogWrite(speedPinB, PWM_150);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);

  Serial.println("Turn left front");
  Serial.println("   "); // Creates a blank line printed on the serial monitor
}

void turn_left_back() {

  /* Left Motor pair */
  analogWrite(speedPinA, 0);
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, LOW);

  /* Right motor pair */
  analogWrite(speedPinB, PWM_150);
  digitalWrite(dir1PinB, HIGH);
  digitalWrite(dir2PinB, LOW);

  Serial.println("Turn left back");
  Serial.println("   "); // Creates a blank line printed on the serial monitor
}

void turn_right_back() {

  /* Right motor pair */
  analogWrite(speedPinB, 0);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, LOW);

  /* Left Motor pair */
  analogWrite(speedPinA, PWM_150);
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);

  Serial.println("Turn right back");
  Serial.println("   "); // Creates a blank line printed on the serial monitor
}

void rotate_left() {

  /* Left Motor pair */
  analogWrite(speedPinA, PWM_200);
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);

  /* Right motor pair */
  analogWrite(speedPinB, PWM_200);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);

}

void rotate_right() {

  /* Left Motor pair */
  analogWrite(speedPinA, PWM_200);
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);

  /* Right motor pair */
  analogWrite(speedPinB, PWM_200);
  digitalWrite(dir1PinB, HIGH);
  digitalWrite(dir2PinB, LOW);

}

void car_fine_adjustment(float distance, float const_dist) {

  if (distance > const_dist) {
    Serial.println("Turn right front");
    turn_right_front();
    //stop_motor();
    //move_forward();
  } else if (distance < const_dist) {
    Serial.println("Turn left front");
    turn_left_front();
    //    stop_motor();
    //move_forward();
  }

}

void setup() {
  /* Setting up before the loop starts */

  /* Initializing the serial communication (stdin and stdout) @9600 baud */
  Serial.begin(9600);

  /* Define the HW-095 pins data direction from the Nano */
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  /* Define the L298N Dual H-Bridge Motor Controller Pins data direction from the Nano */
  pinMode(dir1PinA, OUTPUT);
  pinMode(dir2PinA, OUTPUT);
  pinMode(speedPinA, OUTPUT);
  pinMode(dir1PinB, OUTPUT);
  pinMode(dir2PinB, OUTPUT);
  pinMode(speedPinB, OUTPUT);

  space_detected = false;

}

void loop() {

  // put your main code here, to run repeatedly:
  Serial.println("\n");
  d = getDistance();

  if (space_detected == false) {

    if (d == 10.00) {
      Serial.println("Moving straght forward");
      move_forward();

    } else if (d < 20) {
      car_fine_adjustment(d, 10);
    } else {
      stop_motor();
    }
  } else {
    
  }

}