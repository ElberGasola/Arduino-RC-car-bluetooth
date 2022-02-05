
  // Arduino rc car bluetooth Adrian Farji
  
  #include <Servo.h>
  #include "pitches.h"

  const int motorA1      = 9;  
  const int motorA2      = 10; 
  const int motorAspeed  = 11;
  const int motorB1      = 2; 
  const int motorB2      = 3; 
  const int motorBspeed  = 7;

  int state;
  int vSpeed=255;     


  long duracion;
  long distancia;

  double distancias;

  Servo servoMotor;

  
  int melody[] = {
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
  
  int noteDurations[] = {
    4, 8, 8, 4, 4, 4, 4, 4};

void setup() {
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);

    pinMode(6, OUTPUT);
    pinMode(5, INPUT);
    servoMotor.attach(12);  

    Serial.begin(9600);
}


long medir(){
  
    digitalWrite(6, HIGH);
    delay(1);
    digitalWrite(6, LOW);
    duracion = pulseIn(5, HIGH);
    distancia = duracion / 58.2;

    return distancia;
}

void bocina(){
   for (int thisNote = 0; thisNote < 8; thisNote++) {

    int noteDuration = 1000 / noteDurations[thisNote];

    tone(8, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;

    delay(pauseBetweenNotes);

    noTone(8);
}
}
 
void loop() {
    
  distancias = medir();

    if(Serial.available() > 0){     
      state = Serial.read();   
    }
   Serial.println(state);


      // Servo movement

    if (state == '9'){
        servoMotor.write(0);}
    else if (state == '8'){
        servoMotor.write(20);}
    else if (state == '7'){
        servoMotor.write(40);}
    else if (state == '6'){
        servoMotor.write(60);}
    else if (state == '5'){
        servoMotor.write(80);}
    else if (state == '4'){
        servoMotor.write(100);}
    else if (state == '3'){
        servoMotor.write(120);}
    else if (state == '2'){
        servoMotor.write(140);}
    else if (state == '1'){
        servoMotor.write(160);}
    else if (state == '0'){
        servoMotor.write(180);}



   
     
  /***********************FOrward****************************/
    if ((state == 'F') && (distancias>30)) {
  digitalWrite (motorA1,LOW);
  delay(1);
  digitalWrite(motorA2,HIGH);                       
  delay(1);
  
  digitalWrite (motorB1,LOW);
  delay(1);
  digitalWrite(motorB2,HIGH);

  analogWrite (motorAspeed, vSpeed);
  analogWrite (motorBspeed, vSpeed);
  }
  /**********************Forward Left************************/
    else if (state == 'G') {
  digitalWrite (motorA1,LOW);
  delay(1);
  digitalWrite(motorA2,HIGH);                       
  delay(1);
  
  digitalWrite (motorB1,LOW);
  delay(1);
  digitalWrite(motorB2,HIGH);

  analogWrite (motorAspeed, 0);
  analogWrite (motorBspeed, vSpeed);
    }
  /**********************Forward Right************************/
    else if (state == 'I') {
  digitalWrite (motorA1,LOW);
  delay(1);
  digitalWrite(motorA2,HIGH);                       
  delay(1);
  
  digitalWrite (motorB1,LOW);
  delay(1);
  digitalWrite(motorB2,HIGH);

  analogWrite (motorAspeed, vSpeed);
  analogWrite (motorBspeed, 0);
    }
  /***********************Backwawrd****************************/
    else if (state == 'B') {
  digitalWrite (motorA1,HIGH);
  delay(1);
  digitalWrite(motorA2,LOW);                       
  delay(1);
  
  digitalWrite (motorB1,HIGH);
  delay(1);
  digitalWrite(motorB2,LOW);

  analogWrite (motorAspeed, vSpeed);
  analogWrite (motorBspeed, vSpeed);
    }
  /**********************Backward Left************************/
    else if (state == 'H') {
  digitalWrite (motorA1,HIGH);
  delay(1);
  digitalWrite(motorA2,LOW);                       
  delay(1);
  
  digitalWrite (motorB1,HIGH);
  delay(1);
  digitalWrite(motorB2,LOW);

  analogWrite (motorAspeed, 0);
  analogWrite (motorBspeed, vSpeed);
    }
  /**********************Backward Right************************/
    else if (state == 'J') {
  digitalWrite (motorA1,HIGH);
  delay(1);
  digitalWrite(motorA2,LOW);                       
  delay(1);
  
  digitalWrite (motorB1,HIGH);
  delay(1);
  digitalWrite(motorB2,LOW);

  analogWrite (motorAspeed, vSpeed);
  analogWrite (motorBspeed, 0);
    }
  /***************************Left*****************************/
    else if (state == 'R') {
  digitalWrite (motorA2,HIGH);
  delay(1);
  digitalWrite(motorA1,LOW);                       
  delay(1);
  
  digitalWrite (motorB2,LOW);
  delay(1);
  digitalWrite(motorB1,HIGH);

  analogWrite (motorAspeed, vSpeed);
  analogWrite (motorBspeed, vSpeed);
    }
  /***************************Right*****************************/
    else if (state == 'L') {
  digitalWrite (motorA2,LOW);
  delay(1);
  digitalWrite(motorA1,HIGH);                       
  delay(1);
  
  digitalWrite (motorB2,HIGH);
  delay(1);
  digitalWrite(motorB1,LOW);

  analogWrite (motorAspeed, vSpeed);
  analogWrite (motorBspeed, vSpeed);    
    }

  if (distancias<=30){
    analogWrite(motorA1, 0);  analogWrite(motorA2, 0); 
    analogWrite(motorB1, 0);  analogWrite(motorB2, 0);     
  }

     /************************Stop*****************************/
  //If state is equal with letter 'S', stop the car
    else if (state == 'S'){
        analogWrite(motorA1, 0);  analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);  analogWrite(motorB2, 0);
        
    }


    /************BOCINA****************/

  if (state =='V'){
    bocina();
  }
    
   
    
}
