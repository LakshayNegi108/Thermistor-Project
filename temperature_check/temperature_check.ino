static int count = 0;
#define SW 8
static int inz = 0;
unsigned long start, finished, elapsed;
float d0;
float d1;
float d2;
float d3;
float d4;
float d5;

void setup() {
  Serial.begin(9600); 
  pinMode(SW,INPUT);
}

void loop() {
  start = millis();
 // Serial.print("Start:");
 // Serial.println(start);
  elapsed = 2000;

  if(digitalRead(SW) == HIGH && count == 0){
    count = 1;
    delay(200);
  }
  else if(digitalRead(SW) == HIGH && count == 1){
    count = 0;
    Serial.println("File closed");
    inz = 0;
    delay(200);
  }
if(start - finished > elapsed){
  if(count == 1){
  d0 = analogRead(0);
  d1 = analogRead(1);
  d2 = analogRead(2);
  d3 = analogRead(3);
  d4 = analogRead(4);
  d5 = analogRead(5);
  
  Serial.println(d0);
  Serial.println(d1);
  Serial.println(d2);
  Serial.println(d3);
  Serial.println(d4);
  Serial.println(d5);
  Serial.println("---------");
  }
  finished = start;
  if(inz == 0){
    if(count == 0){
    Serial.println("File not initialized");
    inz = 1;
    }
  }
 }
// Serial.print("Finished:");
// Serial.print(finished);
}
