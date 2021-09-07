const int buttonPin = 9;
const int ledPin =  7;
#define SW 7
int b = 0;
#include <SD.h>

int buttonState = 0;
char count = '0';

void setup()
{
    Serial.begin(9600);
    Serial.print("Initializing SD card...");
    pinMode(10, OUTPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT);
    if (!SD.begin(8))
    {
        Serial.println("Card failed, or not present");
        return;
    }
    Serial.println("microSD card is ready");
}

void loop()
{
    // read the state of the pushbutton value:
   if(digitalRead(buttonPin) == HIGH){
      delay(20);
      while(digitalRead(buttonPin) == HIGH);
      delay(20);
      buttonState = 1;
   }

    if(buttonState == 1)
    {
        File dataFile = SD.open("DATA.TXT", FILE_WRITE);
        count++;
        if (dataFile)
        {
            for ( int a = 0 ; a < 11 ; a++ )
            {
                dataFile.print(a);
                dataFile.print(" multiplied by two is ");
                b = a * 2;
                dataFile.println(b, DEC);
            }
            dataFile.println("--------------------");
            dataFile.close();
        }
        else
        {
            Serial.println("error opening DATA.TXT");
        }
        Serial.println("finished");
        do {}
        while (1);
    }
    else
    {
        Serial.println("Nothing Right now");
        delay(1000);
    }
}
