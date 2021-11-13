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
int count = 0;
int save = 0;
double motorSpeed = 50;
//double motorSpeed = 2.78;
//double motorSpeed = 1.1; 
unsigned long pausedTime = 0;
unsigned long paused = 0;
unsigned long elapsedTime = 0;
String percentStr = String("0%");

long button_press = -1;
long debounce_time = 500;

long hour = 0, minute = 59, second = 59;//second 
long totaltime = 3600;
long countdown_time = (hour*3600) + (minute * 60) + second;

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
  count = 0;
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
  attachInterrupt(digitalPinToInterrupt(13), toggleDelivery, FALLING); //attach button interupt to pin D2
}

void loop()
{
 if(running){
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
      // lcd.print(percentStr);
      pausedTime += millis() - paused;
      running = true;
      wasRunning = true; 
    }

    elapsedTime = millis() - pausedTime;
    long countdowntime_seconds = countdown_time - (elapsedTime / 1000);
    
    if(countdowntime_seconds == 0){
      //drive forward at full speed by pulling DIR_A High
      //and DIR_B low, while writing a full 255 to PWM to 
      //control speed
      digitalWrite(DIR_A, LOW);
      digitalWrite(DIR_B, LOW);
      analogWrite(PWM, motorSpeed);
      attachInterrupt(digitalPinToInterrupt(13), toggleReset, FALLING); //attach button interupt to pin D2
      lcd.clear();
      lcd.print("Complete, press");
      lcd.setCursor(0,1);
      lcd.print("button to reset");
      while(!reset){
        delay(10);
      }
      setup();
    }

    if (countdowntime_seconds >= 0) {
      long countdown_hour = countdowntime_seconds / 3600;
      long countdown_minute = ((countdowntime_seconds / 60)%60);
      long countdown_sec = countdowntime_seconds % 60;
      lcd.setCursor(4, 1);
        if (countdown_hour < 10) {
          lcd.print("0");
        }
      lcd.print(countdown_hour);
      lcd.print(":");
        if (countdown_minute < 10) {
          lcd.print("0");
        }
      lcd.print(countdown_minute);
      lcd.print(":");
        if (countdown_sec < 10) {
          lcd.print("0");
        }
      lcd.print(countdown_sec);
    } 
  }
  else if(!running && wasRunning){
    //drive forward at full speed by pulling DIR_A High
    //and DIR_B low, while writing a full 255 to PWM to 
    //control speed
    digitalWrite(DIR_A, LOW);
    digitalWrite(DIR_B, LOW);
    analogWrite(PWM, motorSpeed);
    paused = millis();
    lcd.clear();
    lcd.print("|| Press button");
    lcd.setCursor(0,1); 
    wasRunning = false;
  }
  delay(10);
 }

void toggleDelivery(){
 if(millis()-button_press > debounce_time) {
  running = !running;
  button_press = millis();
 }
}

void toggleReset(){
  if(millis()-button_press > debounce_time) {
    reset = true;
    button_press = millis();
  }
}
  
  
