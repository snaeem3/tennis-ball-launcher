# tennis-ball-launcher

##[Video](https://youtu.be/vrVyTNxIxno)

This project showcases an automated tennis ball launcher that was designed, built, and programmed by Kyle Williams and I as a part of ME 4405 Mechatronics at [Georgia Tech](gatech.edu). This project won first place Fall 2017 Mechatronics competition based on mechanical, electrical, and software complexity and execution.

## System Overview

The system has an x-position control and a y-position control
The x-position is moved by a DC motor and a belt drive that rotates the launcher left and right.
They y-position is moved by a stepper motor that rotates the launcher up and down
Two DC voltage powered high spinning wheel squeeze and launch the tennis ball.

## Control Diagram

The USB web camera was the sensor that provided feedback to the system. Using the MATLAB vision system package, the centroid of a specified color could be determined. The difference in position between the centroid and the center of the camera view was sent as error feedback to the MSP 432 Microcontroller via serial communication. A PID controller was used for the x-position and a P controller was used for the y-position.

## Electrical Diagrams

## Challenges

- High Torque was required to move the system
- The selected camera had a low sampling rate and lag issues
- The wheel motors created vibration in the system as speed increased

## Future Improvements

- Replace DC Motor with Stepper motor to improve positioning precision
- Automatic release of tennis balls
- More automated speed adjustment of wheel motors
- Upgrade to a camera with a wider field of view
- Reconsider Symmetry of system to improve motion conrol
- Use encoders rather than vision to prevent lag
