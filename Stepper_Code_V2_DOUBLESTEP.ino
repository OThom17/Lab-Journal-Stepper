// Update - Added Case_LT Struture

int delaytime = 2;
int Case_HT = 0; 
int Case_LT = 0;


void FULLSTEP_LT(int Case_LT);
void FULLSTEP_HT(int Case_HT);
void DOUBLESTEP(void);
void MICROSTEP(void);



void setup() {

  pinMode(12, OUTPUT);  // Channel A - Polarity (H = Forwards, L = Backwards)
  pinMode(13, OUTPUT);  // Channel B - Polarity (H = Forwards, L = Backwards)
  pinMode(9, OUTPUT);   //brake A
  pinMode(8, OUTPUT);   //brake B
}





void loop(){
/*
   for (int i = 0; i < 400; i++){
    if (Case_LT > 3){
      Case_LT = 0;
    }
    FULLSTEP_LT(Case_LT);  // Single Phase
    Case_LT = (Case_LT+1);  // Increment the motor stage
    }
    

   for (int i = 0; i < 400; i++){
    if (Case_HT > 3){
      Case_HT = 0;
    }
    FULLSTEP_HT(Case_HT);  // Single Phase
    Case_HT = (Case_HT+1);  // Increment the motor stage
    }
}
*/



  
  DOUBLESTEP();   // Single and Double Step
//  MICROSTEP();    // Sine wave - Smoother Operation 

}





void FULLSTEP_LT(int Select){

switch (Select){
    case 0:
    digitalWrite(9, LOW);     //Enable A
    digitalWrite(8, HIGH);    //Disable B
  
    digitalWrite(12, HIGH);   // Set the direction
    analogWrite(3, 255);      //Move A to full speed
    
    delay(delaytime);
      
    break;
  
    case 1:
  
    digitalWrite(9, HIGH);    // Disable A
    digitalWrite(8, LOW);     // Enable B
  
    digitalWrite(13, LOW);    //Set direction 
    analogWrite(11, 255);     // Move B with full speed
    
    delay(delaytime);
  
    break;
  
    case 2:
    digitalWrite(9, LOW);     //Enable A
    digitalWrite(8, HIGH);    // Disable B
  
    digitalWrite(12, LOW);    //Sets direction
    analogWrite(3, 255);      //Move A with full speed
    
    delay(delaytime);
    break; 
  
    case 3:
  
    digitalWrite(9, HIGH);     //Disable A
    digitalWrite(8, LOW);      //Enable B
  
    digitalWrite(13, HIGH);    //Set direction
    analogWrite(11, 255);      //Move B at full speed
    
    delay(delaytime);
    break;
break;
}
}


void FULLSTEP_HT(int Select){
// Two phase operation
  digitalWrite(9, LOW);     //Enable A
  digitalWrite(8, LOW);    //Enable B
////////////////////////

  switch (Select){
      
    case 0:
    digitalWrite(12, HIGH);   // Set the direction of both coils to forward
    digitalWrite(13, LOW);    
    analogWrite(3, 255);      //Move A to full speed
    analogWrite(11, 255);     //Move B to full speed
    delay(delaytime);
    break; 
  
    
    case 1:
    digitalWrite(12, LOW);   // Set the direction of both coils to forward
    digitalWrite(13, LOW);   
    analogWrite(3, 255);      //Move A to full speed
    analogWrite(11, 255);     //Move B to full speed
    delay(delaytime);
    break;
    
    case 2:
    digitalWrite(12, LOW);   // Set the direction of both coils to forward
    digitalWrite(13, HIGH);   
    analogWrite(3, 255);      //Move A to full speed
    analogWrite(11, 255);     //Move B to full speed
    delay(delaytime);
    break;
    
    case 3:
    digitalWrite(12, HIGH);   // Set the direction of both coils to forward
    digitalWrite(13, HIGH);   
    analogWrite(3, 255);      //Move A to full speed
    analogWrite(11, 255);     //Move B to full speed
    delay(delaytime);
    break;
  break;
  }
}


void DOUBLESTEP(void){
  for (int i = 0; i < 4; i++){
    FULLSTEP_LT(i);
    FULLSTEP_HT(i);
  }
}




void MICROSTEP(void){
  
// Proposed plan - Use two sine waves at shifted phase angles to progressively turn on and off the appropriate coils

}


