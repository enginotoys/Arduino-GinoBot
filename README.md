# [GinoBot Arduino Library](https://www.engino.com/w/index.php/textcode)

# 1) Description

An Arduino library for controlling and getting readings from the various sensors and drivers of the GinoBot

# 2) Needed For This Project

1)	Ginobot
2)	Arduino Microcontroller
3)	4 Dupont Wires, two male-to-female and two male-to-male.
4)	Ginobot PCB Adaptor

# 3) Wiring

The communication between the Arduino and Ginobot is achieved using the [I2C protocol](https://www.arduino.cc/en/reference/wire).

The I2C connection is established using the SCL pin (Clock) and SDA pin (Data), located on both Arduino and Ginobot. It also required to have common ground (GND) between the Arduino and Ginbot. If you like the Arduino to power up with the GinoBot you need to also connect the Vin pin of the Arduino to the 9v located on the GinoBot’s "Host MCU Pins".

**WARNING:** **_Do not connect the 9v pin of the Ginobot to any of the other ports on the Arduino as it may damage it!_**

The Arduino must be connected in the following way:

| Arduino | GinoBot "HOST MCU" Header Pin |
| ------- | ----------------------------- |
|   SCL   |           SDA                 |
|   SDA   |           SDA                 |
|   Vin   |            9V                 |
|   GND   |           GND                 |

# Connecting Steps

## Step 1
Attach The Arduino to the GinoBot PCB Adaptor

### Top View
<img src="/assets/images/IMG_3880.JPG" width="50%">

### Buttom View
<img src ="/assets/images/IMG_3881.JPG" width="50%">

## Step 2
Remove the GinoBot's cover to expose the internal electronics.

### GinoBot With Cover
<img src="/assets/images/IMG_3865.JPG" width="50%">

### GinoBot Without Cover
<img src="/assets/images/IMG_3866.JPG" width="50%">

## Step 3
Attach the Dupont Wire to the Arduino. Please refer to the table in [Section 3](#3-Wiring).
<img src="/assets/images/IMG_3887.JPG" width="50%">

## Step 4
Attach the Dupont wires to the GinoBot "Host MCU" header. Please refer to the Table in [Section 3](#3-Wiring).
### Host Header on GinoBot
<img src="/assets/images/IMG_3867.JPG" width="50%">

### Host Header Wired
<img src="/assets/images/IMG_3868.JPG" width="50%">

## Step 5
Attach the Ginobot PCB Adaptor to the Ginobot  
<img src="/assets/images/IMG_3893.JPG" width="50%">

**_You Are Now Ready to Command the Ginobot Using The Arduino_**

# 4) Programming The Arduino

The library has beed developed to allow the Arduino to communicate with the GinoBot. It has been designed to make it easy to use with the [Arduino IDE](https://www.arduino.cc/en/software)
with multiple of [examples](https://github.com/enginotoys/Arduino-GinoBot/tree/main/examples/) to allow you to easily create your own code. You need to create an object when using the library (GinoBot "objct_name").

### The usable command are as followed:

**Commands allowing you to retrieve data from the Ginobot**

| Command                      | Description                                                                          |
| ---------------------------- | ------------------------------------------------------------------------------------ |
|   get_distance_front_mm()    | Returns the ultrasonic distance in mm. Requires ultrasound sensor present on Ginobot |
|   get_IR_FL_analog()         | Returns the Front Left IR sensor analog value (0-100)                                |
|   get_IR_FR_analog()         | Returns the Front Right IR sensor analog value (0-100)                               |
|   get_IR_Back_analog()       | Returns the Back IR sensor analog value (0-100)                                      |
|   get_IR_FL                  | Returns the Front Left IR sensor digital value (1 or 0)                              |
|   get_IR_FR                  | Returns the Front Right IR sensor digital value (1 or 0)                             |
|   get_IR_Back                | Returns the Back IR sensor digital value (1 or 0)                                    |
|   get_bottom_left            | Returns the Bottom Left IR sensor digital value (1 or 0)                             |
|   get_bottom_left_white()    | Returns the Bottom Left color sensor white intensity (0-255)                         |
|   get_bottom_left_red()      | Returns the Bottom Left color sensor red intensity (0-255)                           |
|   get_bottom_left_green()    | Returns the Bottom Left color sensor green intensity (0-255)                         |
|   get_bottom_left blue()     | Returns the Bottom Left color sensor blue intensity (0-255)                          |
|   get_bottom_right()         | Returns the Bottom Right IR sensor digital value (1 or 0)                            |
|   get_bottom_right_white()   | Returns the Bottom Right color sensor white intensity (0-255)                        |
|   get_bottom_right_red()     | Returns the Bottom Right color sensor red intensity (0-255)                          |
|   get_bottom_right_green()   | Returns the Bottom Right color sensor green intensity (0-255)                        |
|   get_bottom_right_blue()    | Returns the Bottom Right color sensor blue intensity (0-255)                         |
|   get_wheel_right_speed()    | Returns the current speed of the right wheel (0-100)                                 |
|   get_wheel_right_position() | Returns the current position of the right wheel in clicks (0 – 65535)                |
|   get_wheel_left_speed()     | Returns the current speed of the left wheel (0-100)                                  |
|   get_wheel_left_position()  | Returns the current position of the left wheel in clicks (0 – 65535)                 |
|   get_battery_level()        | Returns the current battery level (0 – 4)                                            |


**Commands allow you to control the GinoBot**

| Command                      | Description                                                                                                                              |
| ---------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------- |
| move(x)                      | Commands the Ginobot to move with speed x (-100 – 100). Moves forward if x is a positive value; moves backwards if x is a negative value |
| move_forward(x)              | Commands the Ginobot to move forward with speed x (0 - 100)                                                                              |
| move_backward(x)             | Commands the Ginobot to move backward with speed x (0 - 100)                                                                             |
| rotate(x)                    | Commands the Ginobot to rotate with speed x (0-100). Rotates right if x is a positive value; rotates left if x is a negative value       |
| rotate_right(x)              | Commands the Ginobot to rotate right with speed x (0-100)                                                                                |
| rotate_left(x)               | Commands the Ginobot to rotate left with speed x (0 -100)                                                                                |
| stop()                       | Commands the Ginobot to stop moving.                                                                                                     |
| wheel_left_spin(x)           | Commands the Ginobot to turn the left wheel with speed x (0-100)                                                                         |
| wheel_right_spin(x)          | Commands the Ginobot to turn the right with speed x (0 -100)
| move_distance_mm(x, y, z)    | Commands the Ginobot to move a specific distance in mm, where x is the distance, y is the wheel diameter in mm and z is the speed (0 – 100). A positive x value will cause the Ginobot to move forward; a negative x value will cause the Ginobot to move backward |
| rotate_clicks(x, y)          | Commands the Ginobot to rotate for a specific amount of clicks, where x is the number of clicks and y is the speed (0 – 100). A positive x value will cause the Ginobot to rotate right; a negative x value causes the Ginobot to rotate left |
| wheel_left_turn(x, y)        | Commands the Ginobot to rotate the left wheel for a specific number of clicks, where x is the number of clicks and y is the speed (0 – 100). A positive x value causes the wheel to rotate clockwise; a negative x value causes the wheel to spin anticlockwise |
| wheel_right_turn(x, y)       | Commands the Ginobot to rotate the right wheel for a specific number of clicks, where x is the number of clicks and y is the speed (0 – 100). A positive x value causes the wheel to rotate clockwise; a negative x value causes the wheel to spin anticlockwise |
| set_IR_FL_threshold(x)       | Sets the threshold value of the Front Left IR sensor (0-100). When the sensor's analog value is below this then the sensor's digital value turns to 0, when it is higher than this, its digital value turns to 1 |
| set_IR_FR_threshold(x)       | Sets the threshold value of the Front Right IR sensor (0-100). When the sensor's analog value is below this then the sensor's digital value turns to 0, when it is higher than this, its digital value turns to 1 |
| set_IR_Back_threshold(x)     | Sets the threshold value of the back IR sensor (0-100). When the sensor's analog value is below this then the sensor's digital value turns to 0, when it is higher than this, its digital value turns to 1 |
| set_IR_bot_L_threshold(x)    | Sets the threshold value of the bottom left IR sensor (0-100). When the sensor's analog value is below this then the sensor's digital value turns to 0, when it is higher than this, its digital value turns to 1 |
| set_IR_bot_R_threshold(x)    | Sets the threshold value of the bottom right IR sensor (0-100). When the sensor's analog value is below this then the sensor's digital value turns to 0, when it is higher than this, its digital value turns to 1 |
| set_front_lights(r,g,b)      | Sets the Ginobot front RGB red LED with intensity r (0-255), green LED with intensity g (0-255) and blue LED with intensity b (0-255)     |
| set_back_lights(r,g,b)       | Sets the Ginobot back RGB red LED with intensity x (0-255), green LED with intensity y (0-255) and blue LED with intensity z (0-255)      |
| set_buzzer_frequency(f)      | Sets the Ginobot buzzer frequency in Hz to f (0-65535). Setting to 0 turns the buzzer off                                                 |
| servo1_position(x)           | Sets the position for servo1 in degrees to x (0-180)                                                                                      |

**_For more information, and help getting started, please consult the examples._**
