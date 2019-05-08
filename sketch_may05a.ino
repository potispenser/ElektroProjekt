//Updated may08 av Gustav
#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 200

int moisture1 = 0;  int moisture2 = 0;  int moisture3 = 0;
int sensorValue1 = 0; int sensorValue2 = 0; int sensorValue3 = 0;
int dry = 0; int waterPin = 7; int Tid = 0;

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

  Tid = checkTime();
  if (Tid < 8){
    changeColor(3); //Dawn
  }
  else if (Tid > 18){
    changeColor(2); //Evening
  }
  else{
    changeColor(1); //Day
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

  //how many steps for each pot???
  //66steps??
  for (int i = 0; i < 66; i++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }
  }

//waterpump function
void waterPlant(){
  digitalWrite(waterPin, HIGH);
  delay(6000); //watering time
  digitalWrite(waterPin, LOW);
  delay(3000); //let the excess water run
}

//light function
int checkTime(){
  int Time;
  return Time; //Need a function to find real Time in 24hr clock. 
}

void changeColor(int rgb){
  if (rgb == 1){
    setDay(); //Changes the color of lamps 
  }
  else if (rgb == 2){
    setEvening();
  }
  else if (rgb == 3){
    setDawn();
  }
}


//Set lamp functions

void setDay(){
}

void setEvening(){
}

void setDawn(){
}
