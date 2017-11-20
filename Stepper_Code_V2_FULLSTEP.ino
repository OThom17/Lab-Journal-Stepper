int delaytime = 2;
void FULLSTEP_LT(void);
void FULLSTEP_HT(void);
void DOUBLESTEP(void);
void MICROSTEP(void);

void setup() {

  pinMode(12, OUTPUT);  // Channel A - Polarity (H = Forwards, L = Backwards)
  pinMode(13, OUTPUT);  // Channel B - Polarity (H = Forwards, L = Backwards)
  pinMode(9, OUTPUT);   //brake A
  pinMode(8, OUTPUT);   //brake B
}

void loop() {
  for (int i = 0; i < 1000; i++){
    FULLSTEP_LT();  // Single Phase
  }
  for (int i = 0; i < 1000; i++){  
  FULLSTEP_HT();  // Double Phase
  }
  
//  DOUBLESTEP();   // Single and Double Step
//  MICROSTEP();    // Sine wave - Smoother Operation 
}

void FULLSTEP_LT(){

// Rotor aligns with coils one at a time. 

// Breaks
  digitalWrite(9, LOW);     //Enable A
  digitalWrite(8, HIGH);    //Disable B

  digitalWrite(12, HIGH);   // Set the direction
  analogWrite(3, 255);      //Move A to full speed
  
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


void FULLSTEP_HT(){
// Two phase operation
  digitalWrite(9, LOW);     //Enable A
  digitalWrite(8, LOW);    //Enable B
////////////////////////

  digitalWrite(12, HIGH);   // Set the direction of both coils to forward
  digitalWrite(13, HIGH);   
  analogWrite(3, 255);      //Move A to full speed
  analogWrite(11, 255);     //Move B to full speed
  
  delay(delaytime);

  digitalWrite(12, LOW);   // Set the direction of both coils to forward
  digitalWrite(13, HIGH);   
  analogWrite(3, 255);      //Move A to full speed
  analogWrite(11, 255);     //Move B to full speed
  
  delay(delaytime);

  digitalWrite(12, LOW);   // Set the direction of both coils to forward
  digitalWrite(13, LOW);   
  analogWrite(3, 255);      //Move A to full speed
  analogWrite(11, 255);     //Move B to full speed
  
  delay(delaytime);

  digitalWrite(12, HIGH);   // Set the direction of both coils to forward
  digitalWrite(13, LOW);    
  analogWrite(3, 255);      //Move A to full speed
  analogWrite(11, 255);     //Move B to full speed
  
  delay(delaytime);
}

void DOUBLESTEP(void){
  
}



void MICROSTEP(void){
  
// Proposed plan - Use two sine waves at shifted phase angles to progressively turn on and off the appropriate coils  
  



}
