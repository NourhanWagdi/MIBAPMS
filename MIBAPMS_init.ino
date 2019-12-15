#include "MQ135.h"
#include <SoftwareSerial.h>

const int gasSensorPin = 0;
int air_quality;

const int buzzer = 11;

// t is the character where I store the the input from the bluetooth connected by the Serial
char t = 'X';

// TrigPin is the pin connected to ultrasonic trigger that pings for any object ahead
// Echopin is the pin connected to ultrasonic membrane that catches the signal reflected from the object
// Duration is a time interval between each signal

const int trigPin = 8;
const int echoPin = 9;
long duration;
int distance;

void setup() {

// Defining wheel motors as output
  pinMode(4 ,OUTPUT);   
  pinMode(5 ,OUTPUT);  
  pinMode(6 ,OUTPUT);   
  pinMode(7 ,OUTPUT);
  
  pinMode(trigPin, OUTPUT); // as the trigPin fire a signal so it should be marked as Output
  pinMode(echoPin, INPUT); // as the echoPin absorbs the signal so it should be marked as Input

  pinMode(gasSensorPin, INPUT);

  pinMode(buzzer, OUTPUT); // The sensor that will fire an alarm would be marked as output
  
  Serial.begin(9600); // Start the serial
}

void loop() {

// MQ135 is the Gas Sensor Module
// Define the module as it is connected to Analog Pin 0
//  MQ135 Sensorgas = MQ135(A0);

// Get pollution level in PPM format (parts per million)
//  air_quality = Sensorgas.getPPM();

  air_quality = analogRead(gasSensorPin);

//  Serial.println(air_quality);
  
// Check if the bluetooth module writes any character into the serial
  if(Serial.available()){
    t = Serial.read(); // Get the character from the Serial
    Serial.println(t);
  }  
  
// Start and turn off the Ultrasonic sensor as an Initial State 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

// Start checking for objects ahead
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

// Turn off the Ultrasonic after getting the signal back in echoPin
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
// This is a formula to calculate distance
  distance = duration * 0.034 / 2;

  Serial.print("D ");
  Serial.println(distance);
    

// Move the car based on the input coming from the bluetooth
  if(t == 'G')
  { 
    digitalWrite(4 ,LOW);
    digitalWrite(5 ,LOW);
    digitalWrite(6 ,HIGH);
    digitalWrite(7 ,HIGH);

    checkForAirPollution();
  }
  else
  {
    if(distance >= 25)
    {
      if(t == 'F') // Accelerate
      {  
        digitalWrite(4,HIGH);
        digitalWrite(5,HIGH);
        digitalWrite(6,LOW);
        digitalWrite(7,LOW);

   checkForAirPollution();
      }
      if(t == 'R') // Right
      {
        digitalWrite(4,HIGH);
        digitalWrite(5,LOW);
        digitalWrite(6,LOW);
        digitalWrite(7,LOW);

   checkForAirPollution();
      }
      if(t == 'L') // Left
      {
        digitalWrite(4 ,LOW);
        digitalWrite(5 ,HIGH);
        digitalWrite(6 ,LOW);
        digitalWrite(7 ,LOW);
   
   checkForAirPollution();
      }
      if(t == 'X') // Stop
      { 
        digitalWrite(4 ,LOW);
        digitalWrite(5 ,LOW);
        digitalWrite(6 ,LOW);
        digitalWrite(7 ,LOW);

   checkForAirPollution();
      }
    }
    else
      digitalWrite(5 ,LOW);
      digitalWrite(6 ,LOW);
    {
      digitalWrite(4 ,LOW);
      digitalWrite(7 ,LOW);

      checkForAirPollution();
    }
  }
  checkForAirPollution();
}

void checkForAirPollution() {
  Serial.println(air_quality);
  if(air_quality > 700)
  {
    digitalWrite(buzzer , HIGH);
  }
  else
  {
    digitalWrite(buzzer , LOW);
  }
}
