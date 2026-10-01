// Arduino Nano + 2x HY-SRF05 ultrasonic sensors
//
// Serial command:
//   M  -> measure both sensors and return distances
//
// Response:
//   S1:123.4 cm,S2:456.7 cm

const byte TRIG1 = 2;
const byte ECHO1 = 3;

const byte TRIG2 = 4;
const byte ECHO2 = 5;

const unsigned long TIMEOUT_US = 30000UL; // ~5 m maximum

float measureDistance(byte trigPin, byte echoPin)
{
  // Make sure trigger starts LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // 10 us trigger pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure echo pulse
  unsigned long duration = pulseIn(echoPin, HIGH, TIMEOUT_US);

  // No echo received
  if (duration == 0)
    return -1.0;

  // Speed of sound:
  // distance = time * 0.0343 / 2
  return (duration * 0.0343) / 2.0;
}

void setup()
{
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);

  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);

  digitalWrite(TRIG1, LOW);
  digitalWrite(TRIG2, LOW);

  Serial.begin(115200);
}

void loop()
{
  if (Serial.available() > 0)
  {
    char command = Serial.read();

    if (command == 'M' || command == 'm')
    {
      // Measure sensors one after another.
      // This prevents ultrasonic interference between them.
      float distance1 = measureDistance(TRIG1, ECHO1);

      delay(50);

      float distance2 = measureDistance(TRIG2, ECHO2);

      // Return result
      //Serial.print("S1:");

      if (distance1 < 0)
        Serial.print(F("E"));   //Error
      else
        Serial.print(distance1, 1);  //cm

      Serial.print(F(" "));

      if (distance2 < 0)
        Serial.println(F("E"));   //Error
      else
        Serial.println(distance2, 1);  //cm

      //Serial.println(" cm");
    }
  }
}
