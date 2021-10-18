/*
SparkFun Inventor's Kit for Arduino
Example sketch 12

SparkFun Motor Driver

Use the SparkFun Motor Driver to control the speed and direction of a motor

This sketch was written by SparkFun Electronics,
with lots of help from the Arduino community.
This code is completely free for any use.
Visit http://learn.sparkfun.com/products/2 for SIK information.
Visit http://www.arduino.cc to learn more about Arduino.
*/
#include <LiquidCrystal.h>

//define the two direction logic pins and the speed / PWM pin
const int DIR_A = 5;
const int DIR_B = 4;
const int PWM = 6;
LiquidCrystal lcd (12, 11, 10, 9, 8, 7);

bool running = false;
bool wasRunning = false;
bool reset = false;
int count = 1;
int motorSpeed = 100;
const int percentMilis = 100;
int finishedMilis = percentMilis * 100;
String percentStr = String("0%");


void setup()
{
//set all pins as output
pinMode(DIR_A, OUTPUT);
pinMode(DIR_B, OUTPUT);
pinMode(PWM, OUTPUT);

   // set the number of columns and the number of lines of lcd
  lcd.begin (16, 2);
  running = false;
  wasRunning = false;
  reset = false;
  count = 1;
  percentStr = String("0%");
  // I see the message on the display
  lcd.print ("Initializing");
  reset = false;
  delay(500);
  lcd.clear();
  lcd.print("Press button to");
  lcd.setCursor(0,1);//write the rest on new line
  lcd.print("begin.");
  Serial.begin(9600);//initialize serial output for debugging FIXME
  attachInterrupt(digitalPinToInterrupt(2), toggleDelivery, FALLING); //attach button interupt to pin D2
}

void loop()
{
 if(running){
    if(count % percentMilis == 0){
      percentStr = String(count / percentMilis) + String("\%");
      lcd.clear();
      lcd.print("|>");
      lcd.setCursor(0,1);
      lcd.print(percentStr);
    }
    if(!wasRunning){
      //drive forward at full speed by pulling DIR_A High
      //and DIR_B low, while writing a full 255 to PWM to 
      //control speed
      digitalWrite(DIR_A, HIGH);
      digitalWrite(DIR_B, LOW);
      analogWrite(PWM, motorSpeed);
      lcd.clear();
      lcd.print("|>");
      lcd.setCursor(0,1);
      lcd.print(percentStr);
      running = true;
      wasRunning = true; 
    }
    if(count == finishedMilis){
      //drive forward at full speed by pulling DIR_A High
      //and DIR_B low, while writing a full 255 to PWM to 
      //control speed
      digitalWrite(DIR_A, LOW);
      digitalWrite(DIR_B, LOW);
      analogWrite(PWM, motorSpeed);
      attachInterrupt(digitalPinToInterrupt(2), toggleReset, FALLING); //attach button interupt to pin D2
      lcd.clear();
      lcd.print("Complete, press");
      lcd.setCursor(0,1);
      lcd.print("button to reset");
      while(!reset){
        delay(10);
      }
      setup();
    }
    count++;
    Serial.println(count);
    Serial.println(count %  1000);
  }
  else if(!running && wasRunning){
    //drive forward at full speed by pulling DIR_A High
    //and DIR_B low, while writing a full 255 to PWM to 
    //control speed
    digitalWrite(DIR_A, LOW);
    digitalWrite(DIR_B, LOW);
    analogWrite(PWM, motorSpeed);
    lcd.clear();
    lcd.print("|| Press button");
    lcd.setCursor(0,1); 
    wasRunning = false;
  }
  delay(10);
 }

void toggleDelivery(){
 running = !running;
 delay(5);
}

void toggleReset(){
  reset = true;
  delay(5);
}
  
  
