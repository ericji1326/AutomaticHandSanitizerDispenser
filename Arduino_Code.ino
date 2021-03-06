#include <Servo.h>
Servo servo;                      //intialize a servo object
int echoPin = 6;                  //records the output time from distance sensor
int trigPin = 5;                  //triggers the sound wave
int servoPin = 7;                 //sends signal to actuate servo

long duration;                    //initializing variables 
long distance;
long aveDist;
long meanDistance[3];


void setup() {
  Serial.begin(9600);                    //initialize the serial monitor
  servo.attach(servoPin);                //'attaches' servo object to servoPin
  pinMode(trigPin, OUTPUT);              //sets the trigger pin for sensor as output
  pinMode(echoPin, INPUT);               //sets the echo pin for sensor as input
  servo.write(0);                        //sets servo to point 0 (angle of 0 degrees)  
  delay(100);                            //delay 100 ms
}

long measure() {
   digitalWrite(trigPin, LOW);           //Set the trig pin to off
   delayMicroseconds(5);
   digitalWrite(trigPin, HIGH);          //Set trig pin to high (send a signal)
   delayMicroseconds(15);
   digitalWrite(trigPin, LOW);           //Set trig pin to low (turn it off)
   duration = pulseIn(echoPin, HIGH);    //Counts the number of microseconds until echoPin reads "HIGH"
   distance = (duration/2) / 29.1;           
   //its a round trip so divide by 2 and the speed of sound in microseconds to obtain distance
   return distance;
}

void loop() {
  
  //take the average of 3 measured distances to minimize random actuations
  for (int i=0;i<3;i++) {                            
  meanDistance[i]=measure();          
  delay(10);            
  }
  aveDist =(meanDistance[0]+meanDistance[1]+meanDistance[2])/3;

  if ( aveDist<10 ) {
     //if distance read is less than 10, actuate the motor 
     delay(1);
     servo.write(0);  
     delay(2000);     
     servo.write(150);            //rotate 150 degrees 
     delay(1000); 
  }   
} 
