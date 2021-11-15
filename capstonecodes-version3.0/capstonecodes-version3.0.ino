#define USING_16MHZ     true
#define USING_8MHZ      false
#define USING_250KHZ    false


#define USE_TIMER_0     false
#define USE_TIMER_1     true
#define USE_TIMER_2     false
#define USE_TIMER_3     false

#include <LiquidCrystal.h>
#include "megaAVR_TimerInterrupt.h"

#define TIMER1_INTERVAL_MS        200L

//define the two direction logic pins and the speed / PWM pin
const int DIR_A = 5;
const int DIR_B = 4;
const int PWM = 6;
const int BUTTON_PIN = 13;
const int ENC_PIN = 2;

double motor_speed = 0; // measured motor speed steps/millisec (12 steps / input shaft rotation, 986.41 input shaft rotations / output shaft rotations)
double poll_int = (double)TIMER1_INTERVAL_MS/4;

long enc_count = 0; //keeps track of the rotations of the motor

long last_steps = 0;  //set each time timer interrupt runs
long step_diff = 0; //difference in steps from last steps recorded by interrupt

LiquidCrystal lcd (12, 11, 10, 9, 8, 7);

bool running = false;
bool wasRunning = false;
bool reset = false;
bool spd_update = false;

const double expected_spd = 0.3;
//const double expected_spd = 0.12;
//const double error_margin = 0.025;
 
double pwm_lvl = expected_spd * 80; //pwm level fed to the motor
//double pwm_lvl = 2.78;
//double pwm_lvl = 1.1; 
unsigned long pausedTime = 0;
unsigned long paused = 0;
unsigned long elapsedTime = 0;
String percentStr = String("0%");

long start_time = 0;

long button_press = -1;
const long debounce_time = 250;

long hour = 0, minute = 59, second = 59;//second 
long totaltime = 3600;
long countdown_time = (hour*3600) + (minute * 60) + second;

void setup()
{
  lcd.begin (16, 2);
  lcd.print ("Initializing");
  //set all pins as output
  pinMode(DIR_A, OUTPUT);
  pinMode(DIR_B, OUTPUT);
  pinMode(PWM, OUTPUT);

   // set the number of columns and the number of lines of lcd
  running = false;
  wasRunning = false;
  reset = false;
  reset = false;
  lcd.clear();
  lcd.print("Press button to");
  lcd.setCursor(0,1);//write the rest on new line
  lcd.print("begin.");
  Serial.begin(9600);//initialize serial output for debugging FIXME
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), toggleDelivery, FALLING); //attach button interupt 
  attachInterrupt(digitalPinToInterrupt(ENC_PIN), updateEncoder, CHANGE); //attach encoder
  ITimer1.init();
  if (ITimer1.attachInterruptInterval(TIMER1_INTERVAL_MS, TimerHandler1))
    Serial.println("Starting  ITimer1 OK, millis() = " + String(millis()));
  else
    Serial.println("Can't set ITimer1. Select another freq. or timer"); 
}

void loop()
{
 if(running){
    if(!wasRunning){
      digitalWrite(DIR_A, HIGH);
      digitalWrite(DIR_B, LOW);
      analogWrite(PWM, pwm_lvl);
      lcd.clear();
      lcd.print("|>");
      lcd.setCursor(0,1);
      start_time = millis();
      pausedTime += millis() - paused;
      running = true;
      wasRunning = true; 
    }

    elapsedTime = millis() - pausedTime;
    long countdowntime_seconds = countdown_time - (elapsedTime / 1000);
    
    if(countdowntime_seconds == 0){
      digitalWrite(DIR_A, LOW);
      digitalWrite(DIR_B, LOW);
      analogWrite(PWM, pwm_lvl);
      attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), toggleReset, FALLING); //attach button interupt to pin D2
      lcd.clear();
      lcd.print("Complete, press");
      lcd.setCursor(0,1);
      lcd.print("button to reset");
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

    if(millis() - start_time > 500){ //keeps motor speed from spiking at start
      motor_speed = (double)step_diff/poll_int;
      if(spd_update){
        if(motor_speed < expected_spd){
          pwm_lvl += (expected_spd - motor_speed)*10;
          analogWrite(PWM, pwm_lvl);
          //Serial.println(pwm_lvl);//FIXME
        }
        else if(motor_speed > expected_spd){
          pwm_lvl -= (motor_speed - expected_spd)*10;
          if(pwm_lvl < 0)
          pwm_lvl = 20;
          analogWrite(PWM, pwm_lvl);
          //Serial.println(pwm_lvl);//FIXME
        }
        //Serial.println(motor_speed, 4);//FIXME
        Serial.println(enc_count);//FIXME
        spd_update = false;
      } 
    }
  }
  else if(!running && wasRunning){
    //drive forward at full speed by pulling DIR_A High
    //and DIR_B low, while writing a full 255 to PWM to 
    //control speed
    digitalWrite(DIR_A, LOW);
    digitalWrite(DIR_B, LOW);
    analogWrite(PWM, pwm_lvl);
    paused = millis();
    lcd.clear();
    lcd.print("|| Press button");
    lcd.setCursor(0,1); 
    wasRunning = false;
  }
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

void updateEncoder(){
  enc_count++;
  //Serial.println(enc_count);//FIXME
}  
  
void TimerHandler1()
{
  step_diff = enc_count - last_steps;
  last_steps = enc_count;
  spd_update = true;
}
