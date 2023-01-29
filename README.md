# Line-Follower

## Team

Name: Viteza :dizzy:

* [Mitrica Octavian](https://github.com/tavi22)
* [Enasoaie Roxana](https://github.com/roxanaenasoaie)

## Task

> Implement a self-calibrating Line Follower.

We were given an assembly kit, which we put together and programmed in order to complete a course.
We did not know how the course would look, but it had to follow the line without too much corrections and take turns without going off course.
The time to beat for a maximum grade was under 20s and we achieved 20.9 with our best run (sadly, it didn't count since it was our sight lap) and 21s for the official time.


## Functionality Video

[Video](https://youtube.com/shorts/qDJLuF--M2c?feature=share)

## Components

1. Arduino Uno
2. Zip-ties
3. Power source (can be of different shape). In our case, a LiPo battery
4. Wheels (2)
5. Wires for the line sensor (female - male)
6. QTR-8A reflectance sensor, along with screws
7. Ball caster
8. Extra wires from the kit or lab
9. Chassis
10. Breadboard - medium (400pts)
11. L293D motor driver
12. DC motors (2)

## Coding

  We tried an empirical model at first in order to understand how everything ties together.
  After spending all day figuring out different values for the PD function which gave the speed to the wheels, we finally hit it off with a good setup.
  The P parameter was the one that directly slowed the wheelspeed (multiplied with our mapped sensor input) so we roughly calculated how much to set it and the map interval in order to reach our lowest wheelspeed which was a negative one, since we wanted to take the turns faster and have a good speed generally.
  We also tweaked the D parameter to smooth out the transitions.
  Lastly we had to make the robot calibrate its sensors without human input and we completed the run.
  We used a QTR-8A with 6 sensors active out of 8 for detecting the line and two DC motors for powering the robot.
