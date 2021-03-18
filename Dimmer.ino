/*
 * Title: Dimmer
 * Written by Shiva Teja (B.S.T)
 * GitHub Link: https://github.com/EpicShiv/Dimmer
 * 
 * Note:
 * Some of the code is used or derived from opensource community.
 * 
 * GNU GENERAL PUBLIC LICENSE
 * Version 3, 29 June 2007
 * Copyright (c) 2021, SHIVA TEJA
 * All rights reserved.
 */
 
// While uploading code define "DEBUG" to "0" and for debugging change it to "1".
#define DEBUG 1
#if DEBUG
  #define DUMPS(s) Serial.print(s)
#else
  #define DUMPS(s)
#endif

// Define the GPIO pins.
#define triac 4                   // Triac or triac driver is connected to GPIO pin 4.
#define zcr 5                     // Zero Crossing Detector is connected to GPIO pin 5.
#define pot A0                    // Potentiometer used to dimm the voltage is connected to GPIO pin A0.   

void setup()
{
  Serial.begin(9600);             // Initializes to start recieve and transmit the serial data.
  pinMode(triac, OUTPUT);         // Defining triac pin as an "OUTPUT".
  pinMode(pot, INPUT);            // Defining potentiometer pin as an "INPUT".
  pinMode(zcr, INPUT_PULLUP);     // Defining zero crossing detector pin as an "INPUT PULLUP".
  
  // Defining zcr as an external interrupt and calling ISR (Interrupt Service Routine) to handle interrupt.
  attachInterrupt(digitalPinToInterrupt(zcr), Zero_Crossing_Detector, RISING);
}

void loop()
{
  // Any extra code can be wriiten if you want to add further operations.
}

void Zero_Crossing_Detector()
{
  int potValue = analogRead(pot);
  DUMPS(potValue);
  DUMPS(" ");
  float potDelay = map(potValue * (5.0 / 1023.0),0,255,0,10000);
  DUMPS(potDelay);
  DUMPS("\r\n");
  delayMicroseconds(potDelay);
  digitalWrite(triac, HIGH);
  delayMicroseconds(100);
  digitalWrite(triac, LOW);
}
