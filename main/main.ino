#include <LiquidCrystal.h>
#include <SD.h>

const int rs = 7, en = 6, D4 = 5, D5 = 4, D6 = 3, D7 = 2;  //Initializing LCD Pins
LiquidCrystal lcd(rs, en, D4, D5, D6, D7);

#define SW 8    //Button for Data logging

static int inz = 0;    //File Initialize flag(to print the 'file_init()' function once)
static int count = 0;
static int heading = 0;  //heading Initialize flag(to print once)
int time_period = 0;
unsigned int i = 0;
boolean long_flag = false;   //Flag for Long Button

unsigned long start, finished, elapsed;   //time period for millis
float d0, d1, d2, d3, d4, d5;   //Analog data variables

float Ra = 10400.0; //Known Resistance of Thermistor
float Rb = 10400.0; //Known Resistance of Thermistor
float Rc = 10400.0; //Known Resistance of Thermistor
float Rd = 10400.0; //Known Resistance of Thermistor
float Re = 10400.0; //Known Resistance of Thermistor
float Rf = 10400.0; //Known Resistance of Thermistor

float logR2, R2, T, T1, T2, T3, T4, T5, T6;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

//*********Serial_&_LCD_Print**************************

void print_values() {
  d0 = analogRead(0);
  d1 = analogRead(1);
  d2 = analogRead(2);
  d3 = analogRead(3);
  d4 = analogRead(4);
  d5 = analogRead(5);

  R2 = Ra * (1023.0 / (float)d0 - 1.0); //Using Voltage divider for finding the Resistor Value
  logR2 = log(R2);
  T1 = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2)); //Steinhart-Hart Equation
  T1 = T1 - 273.15;

  R2 = Rb * (1023.0 / (float)d1 - 1.0); //Using Voltage divider for finding the Resistor Value
  logR2 = log(R2);
  T2 = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2)); //Steinhart-Hart Equation
  T2 = T2 - 273.15;

  R2 = Rc * (1023.0 / (float)d2 - 1.0); //Using Voltage divider for finding the Resistor Value
  logR2 = log(R2);
  T3 = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2)); //Steinhart-Hart Equation
  T3 = T3 - 273.15;

  R2 = Rd * (1023.0 / (float)d3 - 1.0); //Using Voltage divider for finding the Resistor Value
  logR2 = log(R2);
  T4 = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2)); //Steinhart-Hart Equation
  T4 = T4 - 273.15;

  R2 = Re * (1023.0 / (float)d4 - 1.0); //Using Voltage divider for finding the Resistor Value
  logR2 = log(R2);
  T5 = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2)); //Steinhart-Hart Equation
  T5 = T5 - 273.15;

  R2 = Rf * (1023.0 / (float)d5 - 1.0); //Using Voltage divider for finding the Resistor Value
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
//****************************************************
int f_increment = 0;  //Store incremented File number
//************LCD_PRINT_FUNCTIONS*********************

void file_init() {         //Print Initialization or Data saving not started
  Serial.print("File_");
  Serial.print(f_increment);
  Serial.println( " not initialized");
  lcd.clear();
  lcd.print("   File_");
  lcd.print(f_increment);
  lcd.print(" not   ");
  lcd.setCursor(0, 1);
  lcd.print("  Initialized.  ");
  inz = 1;
}
void file_closed() {       //Print File is closed
  Serial.println("File closed");
  lcd.clear();
  lcd.println("File closed");

  String filename = "Log";   //Name of file
  String results = String(f_increment);     //Number of file(1,2,3...etc)
  String Name = (filename + results + ".csv");     //Full Name of File(Log1,Log2....)
  File dataFile = SD.open(Name, FILE_WRITE);
  dataFile.print(" ");
  dataFile.print(",");
  dataFile.print(" ");
  dataFile.print(",");
  dataFile.print(" ");
  dataFile.print(",");
  dataFile.print(" ");
  dataFile.print(",");
  dataFile.print(" ");
  dataFile.print(",");
  dataFile.print(" ");
  dataFile.print(",");
  dataFile.println(" ");
  dataFile.close();
  inz = 0;
}
void file_new() {         //Print Creating New file
  Serial.println("Creating New File");
  lcd.clear();
  lcd.print("Creating New");
  lcd.setCursor(0, 1);
  lcd.println("File");
}
//************************************************



//**************SD CARD****************************

void sd_C_file() {           //Created new file in SD card
  String filename = "Log";   //Name of file
  String results = String(f_increment);     //Number of file(1,2,3...etc)
  String Name = (filename + results + ".csv");     //Full Name of File(Log1,Log2....)

  File dataFile = SD.open(Name, FILE_WRITE);      //IF file is not created then create one, else open the existing one
  if (heading == 0) {       //Heading of the files
    dataFile.println("Time Period,T1,T2,T3,T4,T5,T6");
    heading = 1;      //To make only one heading
  }

  if (dataFile)          //Write data to the file
  {
    
    dataFile.print(time_period);
    dataFile.print(",");
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
    time_period = time_period + 1;
  }
  else
  {
    Serial.println("error opening Log file");
    lcd.clear();
    lcd.print("Error Opening");
    lcd.setCursor(0, 1);
    lcd.println("Log file");
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);     //SD CARD chip select at PIN 10 of Arduino
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
  long_flag = false;    //Reset the Long button press flag in every loop so new file does not create again
  start = millis();     //start recording time
  
  elapsed = 1000;       //Print and store data every "elapsed" time i.e 1sec

  if (digitalRead(SW) == LOW && count == 0) {     //SW pressed
    while (digitalRead(SW) == LOW) {      //***********IMP********************
      Serial.print(i);     //(DO NOT DELETE)_check the timeperiod of button pressed
      i++;
      if (i > 200) {    //if pressed longer than 200,new file created
        i = 0;
        long_flag = true;    
        file_new();
        delay(900);
        f_increment++;     //Increment File number for different name
        heading = 0;
        file_init();
        while (digitalRead(SW) == LOW);      //Wait until switch is released
      }
    }
    if (long_flag == false) {
      count = 1;
      delay(200);
      i = 0;
    }
  }
  else if (digitalRead(SW) == LOW && count == 1) {  //For closing file when SW is pressed(short) again
    count = 0;
    time_period = 0;
    file_closed();
    delay(500);
  }
  if (start - finished > elapsed) {   //Check if the 1sec is passed or not and True when 1sec is passed
    if (count == 1) {
      Serial.print("Time: ");
      Serial.println(time_period);
      sd_C_file();
      print_values();
    }
    finished = start;       //update finish when condition 'start - finished > elapsed' is true i.e. after 2sec
    if (inz == 0) {
      if (count == 0) {
        file_init();
      }
    }
  }
}
