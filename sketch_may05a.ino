//Updated may08 av Gustav o Kalle
#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 200

int moisture1 = 0;  int moisture2 = 0;  int moisture3 = 0;
int sensorValue1 = 0; int sensorValue2 = 0; int sensorValue3 = 0;
int dry = 0; int waterPin = 4; int sensePin = 5; int irPin = 6;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
}

void loop() {

  Serial.print("Sensor Values: \t");
  if (checkSensor1()){ //if pot need watering 
    waterPlant();    
  }
  if (checkSensor2()){
    motorControl(1);
    waterPlant();
    motorControl(-1);
  }
  if (checkSensor3()){
    motorControl(-1);
    waterPlant();
    motorControl(1);
  }

 }

// FUNCTIONS!!!
//Check all 3 moisture sensors. Return integer representing pot number. 
int checkSensor1(){
  sensorValue1 = analogRead(A0);
  Serial.print("Pot 1 Moisture:");
  Serial.print("\n");
  if (sensorValue1 < dry){ //lower value --> dryer
    return 1;
  }
  else{
    return 0;
  }
}
int checkSensor2(){
  sensorValue2 = analogRead(A1);
  Serial.print("Pot 2 Moisture:");
  Serial.print("\n");
  if (sensorValue2 < dry){
    return 1;
  }
  else{
    return 0;
}
}
int checkSensor3(){
  sensorValue3 = analogRead(A2);
  Serial.print("Pot 3 Moisture:");
  Serial.print("\n");
  if (sensorValue3 < dry){
    return 1;
  }
  else{
    return 0;
}
}

//motorcontrol function
void motorControl(int direction){
  if (direction == -1){ // -1 means left
  digitalWrite(dirPin,HIGH); //set spin direction.
  }
  else if(direction == 1){ // 1 means right
  digitalWrite(dirPin,LOW); 
  }

  //Continue moving until irSense reads white paper.
  int readValue = irSensor();
  while (readValue == 0){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
    readValue = irSensor();
  }
 }
//waterpump function
void waterPlant(){
  digitalWrite(waterPin, HIGH);
  delay(6000); //watering time
  digitalWrite(waterPin, LOW);
  delay(3000); //let the excess water run
}
//IR function

int irSensor(){
  digitalWrite(irPin,HIGH);
  int senseValue = digitalRead(sensePin);
  if (senseValue != 0){
    return 1;
  }
}
