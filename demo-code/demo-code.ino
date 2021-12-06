#include <LiquidCrystal.h>

LiquidCrystal lcd (12, 11, 10, 9, 8, 7); // for nano every / tinkercad setup

byte dnArrow[8] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B10001,
  B01010,
  B00100,
};

byte upArrow[8] = {
  B00100,
  B01010,
  B10001,
  B00100,
  B00100,
  B00100,
  B00100,
};


void setup() {
  // put your setup code here, to run once:
  lcd.createChar(0, dnArrow);
  lcd.createChar(1, upArrow);
  lcd.begin(16, 2);
}

void loop() {
  lcd.clear();
  lcd.print("Initializing..."); //perhaps read from storage to know if dose in progress
  delay(2000);
  lcd.clear();
  lcd.print("Begin treatment<");
  lcd.setCursor(0,1);
  lcd.print("Settings        ");
  delay(1500);
  lcd.clear();
  lcd.print("Begin treatment ");
  lcd.setCursor(0,1);
  lcd.print("Settings       <");
  delay(2000);
  lcd.clear();
  lcd.print(" Set weight    <");
  lcd.setCursor(0,1);
  lcd.write(byte(0));
  lcd.print("Units       ");
  delay(2000);
  lcd.clear();
  lcd.print("000 lbs         ");
  lcd.setCursor(0,1);
  lcd.print("^               ");
  delay(1000);
  lcd.clear();
  lcd.print("100 lbs         ");
  lcd.setCursor(0,1);
  lcd.print("^               ");
  delay(500);
  lcd.clear();
  lcd.print("100 lbs         ");
  lcd.setCursor(0,1);
  lcd.print(" ^               ");
  delay(1000);
  lcd.clear();
  lcd.print("150 lbs         ");
  lcd.setCursor(0,1);
  lcd.print(" ^              ");
  delay(500);
  lcd.clear();
  lcd.print("150 lbs         ");
  lcd.setCursor(0,1);
  lcd.print("  ^             ");
  delay(1000);
  lcd.clear();
  lcd.print("Save?       Y N ");
  lcd.setCursor(0,1);
  lcd.print("            ^   ");
  delay(2000);
  lcd.clear();
  lcd.print(" Set weight    <");
  lcd.setCursor(0,1);
  lcd.write(byte(0));
  lcd.print("Units       ");
  delay(2000);
  lcd.clear();
  lcd.print(" Set weight     ");
  lcd.setCursor(0,1);
  lcd.write(byte(0));
  lcd.print("Units         <");
  delay(2000);
  lcd.clear();
  lcd.write(byte(1));
  lcd.print("Units       ");
  lcd.setCursor(0,1);
  lcd.print("<Back          <");
  delay(2000);
  lcd.clear();
  lcd.print("Begin treatment<");
  lcd.setCursor(0,1);
  lcd.print("Settings        ");
  delay(2000);
  lcd.clear();
  lcd.print("Paused treatment");
  lcd.setCursor(0,1);
  lcd.print("found, continue?");
  delay(2000);
  lcd.clear();
  lcd.print("Continue       <");
  lcd.setCursor(0,1);
  lcd.print("New treatement  ");
  delay(5000);
  lcd.clear();
  lcd.print("Paused treatment");
  lcd.setCursor(0,1);
  lcd.print("found, continue?");
  delay(2000);
  lcd.clear();
  lcd.print("Continue       <");
  lcd.setCursor(0,1);
  lcd.print("New treatement  ");
  delay(2000);
  lcd.clear();
  lcd.print("Continue        ");
  lcd.setCursor(0,1);
  lcd.print("New treatement <");
  delay(2000);
  lcd.clear();
  lcd.print("Press button to");
  lcd.setCursor(0,1);
  lcd.print("begin.");
  delay(2000);
  lcd.clear();
  lcd.print("00:59:59");
  lcd.setCursor(0,1);
  lcd.print("Press to pause.");
  delay(1000);
  lcd.clear();
  lcd.print("00:59:58");
  lcd.setCursor(0,1);
  lcd.print("Press to pause.");
  delay(1000);
  lcd.clear();
  lcd.print("00:59:57");
  lcd.setCursor(0,1);
  lcd.print("Press to pause.");
  delay(500);
  lcd.clear();
  lcd.print("|| Press button");
  lcd.setCursor(0,1); 
  lcd.print("to continue.   ");
  delay(3000);
  lcd.clear();
  lcd.print("00:59:56");
  lcd.setCursor(0,1);
  lcd.print("Press to pause.");
  delay(500);
  lcd.clear();
  lcd.print("00:59:55");
  lcd.setCursor(0,1);
  lcd.print("Press to pause.");
  delay(1000);
  lcd.clear();
  lcd.print("00:59:54");
  lcd.setCursor(0,1);
  lcd.print("Press to pause.");
  delay(1000);
  lcd.clear();
  lcd.print("00:59:53");
  lcd.setCursor(0,1);
  lcd.print("Press to pause.");
  delay(1000);
  lcd.clear();
  lcd.print("00:59:52");
  lcd.setCursor(0,1);
  lcd.print("Press to pause.");
  delay(1000);
  lcd.clear();
  lcd.print("00:59:51");
  lcd.setCursor(0,1);
  lcd.print("Press to pause.");
  delay(1000);
  lcd.clear();
  lcd.print("Demo Complete  ");
  delay(5000);
}
