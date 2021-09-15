#include <LiquidCrystal.h>
#include <SD.h>

static int count = 0;
#define SW 8
static int inz = 0;
unsigned long start, finished, elapsed;
float d0, d1, d2, d3, d4, d5;

const int rs = 7, en = 6, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
LiquidCrystal lcd(rs, en, D4, D5, D6, D7);

static int heading = 0;
float R1 = 10000.0; //Known Resistance of Thermistor
float logR2, R2, T, T1, T2, T3, T4, T5, T6;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void print_values() {
  d0 = analogRead(0);
  d1 = analogRead(1);
  d2 = analogRead(2);
  d3 = analogRead(3);
  d4 = analogRead(4);
  d5 = analogRead(5);

  R2 = R1 * (1023.0 / (float)d0 - 1.0); //Using Voltage divider for finding the Resistor Value
  logR2 = log(R2);
  T1 = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2)); //Steinhart-Hart Equation
  T1 = T1 - 273.15;

  R2 = R1 * (1023.0 / (float)d1 - 1.0); //Using Voltage divider for finding the Resistor Value
  logR2 = log(R2);
  T2 = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2)); //Steinhart-Hart Equation
  T2 = T2 - 273.15;

  R2 = R1 * (1023.0 / (float)d2 - 1.0); //Using Voltage divider for finding the Resistor Value
  logR2 = log(R2);
  T3 = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2)); //Steinhart-Hart Equation
  T3 = T3 - 273.15;

  R2 = R1 * (1023.0 / (float)d3 - 1.0); //Using Voltage divider for finding the Resistor Value
  logR2 = log(R2);
  T4 = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2)); //Steinhart-Hart Equation
  T4 = T4 - 273.15;

  R2 = R1 * (1023.0 / (float)d4 - 1.0); //Using Voltage divider for finding the Resistor Value
  logR2 = log(R2);
  T5 = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2)); //Steinhart-Hart Equation
  T5 = T5 - 273.15;

  R2 = R1 * (1023.0 / (float)d5 - 1.0); //Using Voltage divider for finding the Resistor Value
  logR2 = log(R2);
  T6 = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2)); //Steinhart-Hart Equation
  T6 = T6 - 273.15;

  Serial.println(T1);
  Serial.println(T2);
  Serial.println(T3);
  Serial.println(T4);
  Serial.println(T5);
  Serial.println(T6);
  Serial.println("---------");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(T1, 1);
  lcd.print(" ");
  lcd.print(T2 , 1);
  lcd.print(" ");
  lcd.print(T3, 1);
  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(T4, 1);
  lcd.print(" ");
  lcd.print(T5, 1);
  lcd.print(" ");
  lcd.print(T6, 1);
}

void file_init() {
  Serial.println("File not initialized");
  lcd.clear();
  lcd.print("    File not    ");
  lcd.setCursor(0, 1);
  lcd.print("  Initialized.  ");
  inz = 1;
}
void file_closed() {
  Serial.println("File closed");
  lcd.clear();
  lcd.println("File closed");
  inz = 0;
}
void file_new() {
  Serial.println("Creating New File");
  lcd.clear();
  lcd.print("Creating New");
  lcd.setCursor(0, 1);
  lcd.println("File");
}
int f_increment = 0;
void sd_C_file() { 
  String filename = "Log";
  String results = String(f_increment);
  String Name = (filename + results + ".csv");

  File dataFile = SD.open(Name, FILE_WRITE);
  if (heading == 0) {
    dataFile.println("T1,T2,T3,T4,T5,T6");
    heading = 1;
  }

  if (dataFile)
  {
    dataFile.print(T1, DEC);
    dataFile.print(",");
    dataFile.print(T2, DEC);
    dataFile.print(",");
    dataFile.print(T3, DEC);
    dataFile.print(",");
    dataFile.print(T4, DEC);
    dataFile.print(",");
    dataFile.print(T5, DEC);
    dataFile.print(",");
    dataFile.println(T6, DEC);

    dataFile.close();
  }
  else
  {
    Serial.println("error opening Log file");
    lcd.println("error opening Log file");
  }
}

int LED1 = 11;
int LED2 = 12;

boolean LED1State = false;
boolean LED2State = false;

boolean long_flag = false;
unsigned int i = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(SW, INPUT_PULLUP);
  if (!SD.begin(20))
  {
    Serial.println("Card failed, or not present");
    lcd.println("Card failed, or not present");
    return;
  }
  Serial.println("microSD card is ready");
  lcd.println("microSD card is ready");
  lcd.begin(16, 2);
}

void loop() {
  long_flag = false;
  start = millis();
  elapsed = 2000;

  if (digitalRead(SW) == LOW && count == 0) {
    while (digitalRead(SW) == LOW) {
      Serial.print(i);
      i++;
      if (i > 200) {
        LED1State = !LED1State;
        digitalWrite(LED1, LED1State);
        i = 0;
        long_flag = true;
        file_new();
        delay(900);
        f_increment++;
        heading = 0;
        file_init();
        while (digitalRead(SW) == LOW);
      }
    }
    if (long_flag == false) {
      count = 1;
      delay(200);
      LED2State = !LED2State;
      digitalWrite(LED2, LED2State);
      i = 0;
    }
  }
  else if (digitalRead(SW) == LOW && count == 1) {
    count = 0;
    file_closed();
    delay(200);
  }
  if (start - finished > elapsed) {
    if (count == 1) {
      sd_C_file();
      print_values();
    }
    finished = start;
    if (inz == 0) {
      if (count == 0) {
        file_init();
      }
    }
  }
}
