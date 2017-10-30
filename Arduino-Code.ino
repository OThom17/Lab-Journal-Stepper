
int delaytime = 2;
void FULLSTEP(void);
void MICROSTEP(void);

void setup() {
  pinMode(12, OUTPUT); // Channel A - Polarity (H = Forwards, L = Backwards
  pinMode(13, OUTPUT); // Channel B - Polarity (H = Forwards, L = Backwards
  
  pinMode(9, OUTPUT); //brake A
  pinMode(8, OUTPUT); //brake B

}

void loop() {
  FULLSTEP();
  MICROSTEO();
}




void FULLSTEP(){

// Breaks
  digitalWrite(9, LOW);     //Enable A
  digitalWrite(8, HIGH);    //Disable B

  digitalWrite(12, HIGH);   // Set the direction
  analogWrite(3, 255);      //Move A to full speef
  
  delay(delaytime);

// Breaks  
  digitalWrite(9, HIGH);    // Disable A
  digitalWrite(8, LOW);     // Enable B

  digitalWrite(13, LOW);    //Set direction 
  analogWrite(11, 255);     // Move B with full speed
  
  delay(delaytime);

// Breaks
  digitalWrite(9, LOW);     //Enable A
  digitalWrite(8, HIGH);    // Disable B

  digitalWrite(12, LOW);    //Sets direction
  analogWrite(3, 255);      //Move A with full speed
  
  delay(delaytime);

// Breaks
  digitalWrite(9, HIGH);     //Disable A
  digitalWrite(8, LOW);      //Enable B

  digitalWrite(13, HIGH);    //Set direction
  analogWrite(11, 255);      //Move B at full speed
  
  delay(delaytime);
}



void MICROSTEP(void){
  
// Proposed plan - Use two sine waves at shifted phase angles to progressively turn on and off the appropriate coils







}


}

