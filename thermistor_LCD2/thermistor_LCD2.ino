#include <LiquidCrystal.h>;

float Vo;
float R1 = 10000.0; //Known Resistance of Thermistor
float logR2, R2, T, T1, T2, T3, T4, T5, T6;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07; //Constants of Steinhart-Hart Equation

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
lcd.begin(16, 2);
// Print a message to the LCD.
Serial.begin(9600);

}

void loop() {

  //Printing temperature T1 on the Serial Monitor
  Vo = analogRead(A0);
  R2 = R1 * (1023.0 / (float)Vo - 1.0); //Using Voltage divider for finding the Resistor Value
  logR2 = log(R2);
  T1 = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); //Steinhart-Hart Equation
  T1 = T1 - 273.15;

  Serial.print("T1= "); 
  Serial.print(T1);
  Serial.println(" C"); 

  //Printing temperature T2 on the Serial Monitor
  Vo = analogRead(A1);
  R2 = R1 * (1023.0 / (float)Vo - 1.0); //Using Voltage divider for finding the Resistor Value
  logR2 = log(R2);
  T2 = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); //Steinhart-Hart Equation
  T2 = T2 - 273.15;

  Serial.print("T2= "); 
  Serial.print(T2);
  Serial.println(" C"); 

  //Printing temperature T3 on the Serial Monitor
  Vo = analogRead(A2);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);//Using Voltage divider for finding the Resistor Value
  logR2 = log(R2);
  T3 = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); //Steinhart-Hart Equation
  T3 = T3 - 273.15;

  Serial.print("T3= "); 
  Serial.print(T3);
  Serial.println(" C"); 

  //Printing temperature T4 on the Serial Monitor
  Vo = analogRead(A3);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);//Using Voltage divider for finding the Resistor Value
  logR2 = log(R2);
  T4 = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); //Steinhart-Hart Equation
  T4 = T4 - 273.15;

  Serial.print("T4= "); 
  Serial.print(T4);
  Serial.println(" C");

  //Printing temperature T5 on the Serial Monitor
  Vo = analogRead(A4);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);//Using Voltage divider for finding the Resistor Value
  logR2 = log(R2);
  T5 = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); //Steinhart-Hart Equation
  T5 = T5 - 273.15;

  Serial.print("T5= "); 
  Serial.print(T5);
  Serial.println(" C");

  //Printing temperature T6 on the Serial Monitor
  Vo = analogRead(A5);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);//Using Voltage divider for finding the Resistor Value
  logR2 = log(R2);
  T6 = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); //Steinhart-Hart Equation
  T6 = T6 - 273.15;

  Serial.print("T6= "); 
  Serial.print(T6);
  Serial.println(" C");

  
  //delay(2500);
  lcd.setCursor(0,0);
  lcd.print("T1:");
  lcd.print(T1,1);
  lcd.print("  ");
  lcd.print("T2:");
  lcd.println(T2,1);
  delay(750);

  lcd.setCursor(0,1);
  lcd.print("T3:");
  lcd.print(T3,1);
  lcd.print("  ");
  lcd.print("T4:");
  lcd.println(T4,1);
  delay(750);
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("T5:");
  lcd.print(T5,1);
  lcd.print("  ");
  lcd.print("T6:");
  lcd.println(T6,1);
  delay(1000);
  lcd.clear();

 
} 
