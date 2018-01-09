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

It is possible to drive a uni-polar motor in a bi-polar mode by connecting the two 

![Stepper Motor Wiring Diagram](https://github.com/OThom17/Lab-Journal-Stepper/blob/master/Images/Stepper_Motor_Wiring.png)

# Wiring up the stepper motor in accordance with the given diagram



# Programming modes

- Full-Step Mode

Only a single phase is enabled at a time and the motor progressed 
