# tennis-ball-launcher

## [Video](https://youtu.be/vrVyTNxIxno)

This project showcases an automated tennis ball launcher that was designed, built, and programmed by Kyle Williams and I as a part of ME 4405 Mechatronics at [Georgia Tech](gatech.edu). This project won first place in the Fall 2017 Mechatronics competition based on mechanical, electrical, and software complexity and execution.

## System Overview

The system has an x-position control and a y-position control to automatically move the launcher at a specified color target.
- The x-position is moved by a DC motor and a belt drive that rotates the launcher left and right.
- They y-position is moved by a stepper motor that rotates the launcher up and down
- Two DC voltage powered high spinning wheel squeeze and launch the tennis ball.

![ball launcher](https://github.com/snaeem3/tennis-ball-launcher/assets/11710951/e465233b-9db9-4b2b-92ad-6e60141e5aba)
![Slide5](https://github.com/snaeem3/tennis-ball-launcher/assets/11710951/e4936509-e795-4b23-bb31-5fe8e74ffa15)
![Slide6](https://github.com/snaeem3/tennis-ball-launcher/assets/11710951/92b6f047-d726-44d8-a9a5-fa6e54357554)


## Control Diagram
![Slide3](https://github.com/snaeem3/tennis-ball-launcher/assets/11710951/087065bf-405d-4571-97c0-6cfe3db9af50)

The USB web camera was the sensor that provided feedback to the system. Using the MATLAB vision system package, the centroid of a specified color could be determined. The difference in position between the centroid and the center of the camera view was sent as error feedback to the MSP 432 Microcontroller via serial communication. A PID controller was used for the x-position and a P controller was used for the y-position.

![Slide1](https://github.com/snaeem3/tennis-ball-launcher/assets/11710951/9d34b853-de1c-4224-9614-adfd576e7803)
![Slide2](https://github.com/snaeem3/tennis-ball-launcher/assets/11710951/20874602-8e3b-44b3-a898-d1a2a8e1bf6c)


## Electrical Diagrams
![Slide7](https://github.com/snaeem3/tennis-ball-launcher/assets/11710951/57993241-f2b7-4d14-827a-957364e2a0e9)
![Slide8](https://github.com/snaeem3/tennis-ball-launcher/assets/11710951/1083be60-8ba8-43fa-88a8-371388f787cf)

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
