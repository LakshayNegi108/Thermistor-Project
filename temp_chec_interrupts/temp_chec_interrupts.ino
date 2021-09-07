int flag = 0;
const byte interruptPin = 2 ;
volatile byte state = LOW ;
static int inz = 0;
float d0;
float d1;
float d2;
float d3;
float d4;
float d5;

void setup() {
  Serial.begin(9600); 
  pinMode(interruptPin ,INPUT) ;
  attachInterrupt(digitalPinToInterrupt(interruptPin), glow, RISING) ;
}

void glow(){
   state = !state ;
}

void loop() {

  if(state == HIGH){
  flag = 1;
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
  delay(2000);
  }
  if(state == LOW && flag == 1){
    flag = 0;
    Serial.println("File closed");
    inz = 0;
    delay(2000);
  }
  if(inz == 0){
    if(flag == 0){
    Serial.println("File not initialized");
    inz = 1;
    }
  }
}
