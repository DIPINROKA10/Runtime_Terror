#include <AFMotor.h>
#include <SoftwareSerial.h>

SoftwareSerial bluetoothSerial(9, 10);

// Buzzer Pin
#define BUZZER 2

// Motor Mapping
// M1 = Right Front
// M2 = Left Front
// M3 = Left Rear
// M4 = Right Rear

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

char command;
int speed = 210;

void setup()
{
  bluetoothSerial.begin(9600);

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  Stop();
}

void loop()
{
  if (bluetoothSerial.available())
  {
    command = bluetoothSerial.read();

    switch(command)
    {
      case 'F': forward(); break;
      case 'B': backward(); break;
      case 'L': left(); break;
      case 'R': right(); break;
      case 'G': forwardLeft(); break;
      case 'I': forwardRight(); break;
      case 'H': backwardLeft(); break;
      case 'J': backwardRight(); break;
      case 'S': Stop(); break;

      // Buzzer
      case 'V':
        digitalWrite(BUZZER, HIGH);
        break;

      case 'v':
        digitalWrite(BUZZER, LOW);
        break;

      // Speed
      case '0': speed = 0; break;
      case '1': speed = 25; break;
      case '2': speed = 50; break;
      case '3': speed = 75; break;
      case '4': speed = 100; break;
      case '5': speed = 125; break;
      case '6': speed = 150; break;
      case '7': speed = 180; break;
      case '8': speed = 210; break;
      case '9': speed = 230; break;
      case 'q': speed = 255; break;
    }
  }
}

void setSpeedAll(int s)
{
  motor1.setSpeed(s);
  motor2.setSpeed(s);
  motor3.setSpeed(s);
  motor4.setSpeed(s);
}

//================ FORWARD =================

void forward()
{
  setSpeedAll(speed);

  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

//================ BACKWARD =================

void backward()
{
  setSpeedAll(speed);

  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

//================ LEFT =================

void left()
{
  setSpeedAll(speed);

  motor2.run(BACKWARD);
  motor3.run(BACKWARD);

  motor1.run(FORWARD);
  motor4.run(FORWARD);
}

//================ RIGHT =================

void right()
{
  setSpeedAll(speed);

  motor2.run(FORWARD);
  motor3.run(FORWARD);

  motor1.run(BACKWARD);
  motor4.run(BACKWARD);
}

//================ FORWARD LEFT =================

void forwardLeft()
{
  motor2.run(RELEASE);
  motor3.run(RELEASE);

  motor1.setSpeed(speed);
  motor4.setSpeed(speed);

  motor1.run(FORWARD);
  motor4.run(FORWARD);
}

//================ FORWARD RIGHT =================

void forwardRight()
{
  motor1.run(RELEASE);
  motor4.run(RELEASE);

  motor2.setSpeed(speed);
  motor3.setSpeed(speed);

  motor2.run(FORWARD);
  motor3.run(FORWARD);
}

//================ BACKWARD LEFT =================

void backwardLeft()
{
  motor2.run(RELEASE);
  motor3.run(RELEASE);

  motor1.setSpeed(speed);
  motor4.setSpeed(speed);

  motor1.run(BACKWARD);
  motor4.run(BACKWARD);
}

//================ BACKWARD RIGHT =================

void backwardRight()
{
  motor1.run(RELEASE);
  motor4.run(RELEASE);

  motor2.setSpeed(speed);
  motor3.setSpeed(speed);

  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
}

//================ STOP =================

void Stop()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);

  digitalWrite(BUZZER, LOW);
}