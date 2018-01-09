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

This mode is with the aim of increasing the number of steps. To achieve this both of the first 

























