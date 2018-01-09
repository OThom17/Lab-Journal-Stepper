# General Document for Stepper Motor Development

#Theoretical Breakdown

- Uni & Bi-Polar Design

Uni-polar motors require wiring for each coil and always energise the phases in the same direction. This allows for the motor to be simply controlled with the drawback of additional wires. Furthermore due to only half of the coils being energised at one time the motor possesses less torque than the bi-polar alternative.

Bi-polar motors as briefly mentioned above energise both coils per step with each coil changing polarity when at 180 degrees from the starting position. Although they require less control wires the drawback of these motors is that they require additional circuitry to reverse the polarity; a common package used to do this is a H-Bridge chip.

- H Bridge Polarity Shifting

The three images below show the H-Bridge un-energised, being driven in the forward and backward direction respectively. The great advantage of this chip is that it can drive large loads with relatively small currents being delivered to the transistors used to control the current flow. Using this the motor can either be ran forward, backward, set into a free moving state or brake which restricts the motor's rotation.

![H-Bridge Schematics](https://github.com/OThom17/Lab-Journal-Motor/blob/master/Initial-Design-Photos/H-Bridge.png)


Forward Operation

![H-Bridge Forward](https://github.com/OThom17/Lab-Journal-Motor/blob/master/Initial-Design-Photos/H-BridgeFW.png)

Backward Operation

![H-Bridge Forward](https://github.com/OThom17/Lab-Journal-Motor/blob/master/Initial-Design-Photos/H-BridgeBW.png)


- Using a uni-polar motor as a  bi-polar 

It is possible to drive a uni-polar motor in a bi-polar mode by connecting the coils (BLK with GRN) and (RED with BLUE) forming two bi-polar coils. The middle wires (White & Yellow) are simple disconnected.

![Stepper Motor Wiring Diagram](https://github.com/OThom17/Lab-Journal-Stepper/blob/master/Images/Stepper_Motor_Wiring.png)



# Wiring up the stepper motor in accordance with the given diagram


# Programming modes

## Full-Step Mode (Single Phase Mode)

Only a single phase is enabled at a time making the motor progress to each discrete coil. Here the number of possible steps = number of designed steps.

Finalised Code

```
  int delaytime = 2;
  void FULLSTEP_LT(void);
  
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
```

## Comments

This code energises a single coil at a time to rotate the stator, once the other coil is switched too the original coil's polarity is shifted and the stator rotated once more. 

- Torque 
Due to only a single coil being energised at a time the available torque of this mode is relatively low.

- Angular Velocity
*** Research

## Full-Step Mode (Dual Phase Mode)

With two phases energised at once the stator is held between both coils. This mode has the same number of steps as the single phase mode however the additional coil improved the available torque.

Finalised Code

```

  int delaytime = 2;
  void FULLSTEP_HT(void);

  void setup() {
  
    pinMode(12, OUTPUT);  // Channel A - Polarity (H = Forwards, L = Backwards)
    pinMode(13, OUTPUT);  // Channel B - Polarity (H = Forwards, L = Backwards)
    pinMode(9, OUTPUT);   //brake A
    pinMode(8, OUTPUT);   //brake B
  }
  
  void loop() {
    for (int i = 0; i < 1000; i++){
      FULLSTEP_HT();  // Single Phase
    }

void FULLSTEP_HT(){
// Two phase operation
  digitalWrite(9, LOW);     //Enable A
  digitalWrite(8, LOW);    //Enable B


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
```

## Comments

- Torque

The additional coild does indeed provide a greater resistance to being stopped showing the increased torque. 

- Angular Velocity

*** Investigate

## Half-Step Mode

This mode is with the aim of increasing the number of steps. To achieve this both of the full step modes are alternated resulting in the stator aligning with the coils and then being held between and so on and so forth.

The drawback of this approach however is an alternating torque value and this would have to be considered if this were to be integreated into a system. For example the lowest torque value (Full-Step single phase mode) would have to be the maximum rated torque to avoid the skipping of steps.

Finalised Code

```
// Update - Added Case_LT Struture

int delaytime = 2;
int Case_HT = 0; 
int Case_LT = 0;


void FULLSTEP_LT(int Case_LT);
void FULLSTEP_HT(int Case_HT);
void DOUHALFSTEPBLESTEP(void);
void MICROSTEP(void);



void setup() {

  pinMode(12, OUTPUT);  // Channel A - Polarity (H = Forwards, L = Backwards)
  pinMode(13, OUTPUT);  // Channel B - Polarity (H = Forwards, L = Backwards)
  pinMode(9, OUTPUT);   //brake A
  pinMode(8, OUTPUT);   //brake B
}





void loop(){
  HALFSTEP();   // Single and Double Step
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


void HALFSTEP(void){
  for (int i = 0; i < 4; i++){
    FULLSTEP_LT(i);
    FULLSTEP_HT(i);
  }
}
```

## Comments

- Code
A case structure has been introduced to simply allows the program to alternate between the states increasing code efficiency and readability.

- Torque
As mentioned previously the torque in this mode is variable

- Angular Velocity
*** Investigate

## Microstepping

This function is focussed on making the transistions between coils as smooth as possible. To achieve this a sine and cosine wave are used to drive the coils. Due to them being out of phase by 1/4pi the transistion between the two is not as harsh as the other modes discussed.

```
// Update 25/10 Added Case_LT Struture
/* 
 *Update 02/11   
 *
 *Inclusion of variable speed control through the use of sine functions 
 *  
 */

 
int delaytime = 2;
int Case_HT = 0; 
int Case_LT = 0;


void FULLSTEP_HT(int Case_HT, float SpeedA, float SpeedB);
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


void FULLSTEP_HT(int Select,float A,float B){
// Two phase operation
  digitalWrite(9, LOW);     //Enable A
  digitalWrite(8, LOW);    //Enable B


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
```
## Comments

- Code
The MICROSTEP function takes a global time variable and increments it per cycle. This variable is them fed into a sine and cosine arduino function producing their respective values. using the FULLSTEP (Dual phase function) the values are written to the two coils.

- Torque
As with the Half-step mode the torque isn't constant through the entire rotation but experimentally it was found to be about on par with the FULLSTEP(single phase).

- Angular Velocity
In comparison to the other modes this mode was the slowest. This may be a result of the computation time taken to generate the sine and cosine values each cycle.

 
## Microstep Development

```
#define microsteps 50

// Updated code using look up tables - More efficient in cycles 
float amp = 255;
int pulseDelay = 1;
int a[microsteps];
int b[microsteps];
int idxG = 0;


void setup() {
  Serial.begin(9600);
// Generate the trig LUT's

for (int idx = 0; idx < microsteps; idx++){        // 100 seperate steps per physical step of the stepper motor
  a[idx] = 255 * (sin((2* PI* idx)/ microsteps));// Following the Amplitude * Sin((ω/Step) * t) formula
  b[idx] = 255 * (cos((2* PI* idx)/ microsteps));// As above
  
  Serial.print("A: ");
  Serial.print(a[idx]);
  Serial.print("B: ");
  Serial.println(b[idx]);
  
}

  pinMode(12, OUTPUT);  // Channel A - Polarity (H = Forwards, L = Backwards)
  pinMode(13, OUTPUT);  // Channel B - Polarity (H = Forwards, L = Backwards)
  pinMode(9, OUTPUT);   //brake A
  pinMode(8, OUTPUT);   //brake B

  digitalWrite(9, LOW);  //Let both brake A and B off
  digitalWrite(8, LOW);
}

void loop() {
    WriteMS(a[idxG], 3, 12);
    WriteMS(b[idxG], 11, 13);

    Serial.print(a[idxG]);
    Serial.print(":  ");
    Serial.println(b[idxG]);

    idxG++;
    if (idxG >= microsteps){  // Reset the step once complete
      idxG = 0;
    }
    delayMicroseconds(pulseDelay);
}


void WriteMS(int Value, int ChanAnalog, int ChanDigit){
  int AbsVal = abs(Value);
  analogWrite(ChanAnalog, AbsVal);
  if (Value > 0){
    digitalWrite(ChanDigit, HIGH);
  }
  else{
    digitalWrite(ChanDigit, LOW);
  }
}

```

## Comments

To reduce the processing time taken per cycle look-up tables have been used.





























