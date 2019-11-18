const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;

const int motorIn1 = 4;
const int motorIn2 = 5;
const int motorIn3 = 6;
const int motorIn4 = 7;
int gas = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  pinMode(gasReader, INPUT);
  
 pinMode(buzzer, OUTPUT);
 digitalWrite(buzzer,HIGH);
Serial.begin(9600);
  
  }
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  Serial.println(duration);
  distance= duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance);

if(distance < 40)
{
  digitalWrite(motorIn1 , LOW);
  digitalWrite(motorIn2 , LOW);
  digitalWrite(motorIn3 , LOW);
  digitalWrite(motorIn4 , LOW);
}
else
{
  digitalWrite(motorIn1 , HIGH);
  digitalWrite(motorIn2 , HIGH);
  digitalWrite(motorIn3 , HIGH);
  digitalWrite(motorIn4 , HIGH);
}
delay(300);



delay(1000);
  if (gas < 100) {
    tone(buzzer,1000);
    delay(1000);
    
    delay(1000);
  } else {
    noTone(buzzer);
   
 }


}
