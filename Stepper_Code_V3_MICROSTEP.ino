// Update - Added Case_LT Struture
/* 
 *Update 02/11   
 *
 *Inclusion of variable speed control through the use of sine functions 
 *  
 */

 
int delaytime = 2;
int Case_HT = 0; 
int Case_LT = 0;

void FULLSTEP_LT(int Case_LT);
void FULLSTEP_HT(int Case_HT, float SpeedA, float SpeedB);
void DOUBLESTEP(void);
void MICROSTEP(void);



void setup() {

  pinMode(12, OUTPUT);  // Channel A - Polarity (H = Forwards, L = Backwards)
  pinMode(13, OUTPUT);  // Channel B - Polarity (H = Forwards, L = Backwards)
  pinMode(9, OUTPUT);   //brake A
  pinMode(8, OUTPUT);   //brake B
}

void loop(){

  MICROSTEP();    // Sine wave - Smoother Operation 

}

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
 
//  DOUBLESTEP();   // Single and Double Step

*/




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


void FULLSTEP_HT(int Select,float A,float B){
// Two phase operation
  digitalWrite(9, LOW);     //Enable A
  digitalWrite(8, LOW);    //Enable B
////////////////////////

  switch (Select){
      
    case 0:
    digitalWrite(12, HIGH);   // Set the direction of both coils to forward
    digitalWrite(13, LOW);    
    analogWrite(3, A);      //Move A to full speed
    analogWrite(11, B);     //Move B to full speed
    delay(delaytime);
    break; 
  
    
    case 1:
    digitalWrite(12, LOW);   // Set the direction of both coils to forward
    digitalWrite(13, LOW);   
    analogWrite(3, A);      //Move A to full speed
    analogWrite(11, B);     //Move B to full speed
    delay(delaytime);
    break;
    
    case 2:
    digitalWrite(12, LOW);   // Set the direction of both coils to forward
    digitalWrite(13, HIGH);   
    analogWrite(3, A);      //Move A to full speed
    analogWrite(11, B);     //Move B to full speed
    delay(delaytime);
    break;
    
    case 3:
    digitalWrite(12, A);   // Set the direction of both coils to forward
    digitalWrite(13, B);   
    analogWrite(3, 255);      //Move A to full speed
    analogWrite(11, 255);     //Move B to full speed
    delay(delaytime);
    break;
  break;
  }
}


void DOUBLESTEP(void){
  for (int i = 0; i < 4; i++){
    FULLSTEP_LT(i);  // Full peed 
    FULLSTEP_HT(i, 255, 255);
  }
}




void MICROSTEP(void){
// Proposed plan - Use two sine waves at shifted phase angles to progressively turn on and off the appropriate coils
  for (int j = 0; j < 4; j++){
      for (int i = 0; i < 360; i++){
        float Rad = (i* 0.0174533);        // Convert the degrees value to radians - For the sine function
        float SpeedA = sin(Rad);
        float SpeedB = cos(Rad); 
        FULLSTEP_HT(j, SpeedA, SpeedB);  // Write the value to the High Torque Functions
      }
 }
}
