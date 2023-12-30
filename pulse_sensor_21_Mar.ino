
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   

  //Set switch to true or false if you want to see data trough plotter
  //true is test false is for unity
  
  //  Variables for bpm
  int PulseSensorPurplePin = 0;    // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
  int LED13 = 13;   //  The on-board Arduion LED
  // variables will change:
  int Signal;                     //signal
  // holds the incoming raw data. Signal value can range from 0-1024
  PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"
  const int buttonPin = 8;        // the number of the pushbutton pin
  int buttonState = 0;            // variable for reading the pushbutton status
  //  Variables for smoother
  int inputPin = A3;  
  int Threshold = 360;  

  // The SetUp Function:
void setup() { 
  Serial.begin(9600);         // Set's up Serial Communication at certain speed.
  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseSensorPurplePin);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold); 
  pinMode(buttonPin, INPUT); // button\switch
  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
}

// The Main Loop Function
void loop() {
  // smoother
 //BMP
 Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.
 Threshold = map(analogRead(A3),0,1023,0,600);        // Threshold becomes counter
 
 // read the state of the pushbutton value:
 buttonState = digitalRead(buttonPin);  
   if (buttonState == HIGH) { // Send plotter serial when true
    Serial.print(Signal); 
    Serial.print(" ");                  
    Serial.println(Threshold);  // Send the Signal value to Serial Plotter. 
    }
  
  if(Signal > Threshold){                          // If the signal is above "550", then "turn-on" Arduino's on-Board LED.
     digitalWrite(LED13,HIGH);
   } else {
     digitalWrite(LED13,LOW);                    //  Else, the sigal must be below "550", so "turn-off" this LED.
   }
  
 int myBPM = pulseSensor.getBeatsPerMinute();    // Calls function on our pulseSensor object that returns BPM as an "int".
                                                 // "myBPM" hold this BPM value now. 
  if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
   //Serial.println("Heartbeat"); // If test is "true", print a message "a heartbeat happened".
   //Serial.print("BPM: ");                        // Print phrase "BPM: " 
   Serial.println(myBPM);                        // Print the value inside of myBPM. 
 }
 delay(10);
}
