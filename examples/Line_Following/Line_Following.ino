#include <ginobot.h>
// This example utilizes the two color Sensors on the bottom front side of the GinoBot

/*

*************************** Commands used in this Examples ***************************
**********************https://github.com/enginotoys/Arduino-GinoBot*******************
* get_distance_front_mm() - Retriving the Distances from the from ultrasound Sensor
* get_bottom_right()      - Retriving logical 1 or 0 depending if their if white it detected Right Bottom color Sensor
* get_bottom_left()       - Retriving logical 1 or 0 depending if their if white it detected Left Bottom color Sensor
* rotate_right()          - Commands the GinoBot to turn Right
* rotate_left()           - Commands the GinoBot to turn Left
* move_forward()          - Commands the GinoBot to go Forward
* Move_bacwards()         - Commands the GinoBot to go Backwards
* stop()                  - Commands the GinoBot to cease any movement
* set_buzzer_frequency()  - Command the GinoBot Buzzer

*/

// Defining Ports
#define LED 13

// Defining Variables
int distance = 0;
int Right = 0;
int Left = 0;
int Move_Speed = 70;
int Turn_Speed = 60;

// Assigning Object for Library
Ginobot gbot;


void setup()
{
  pinMode(LED,OUTPUT);    // Assigning Build in LED as output

  digitalWrite(LED,HIGH); //Turning On Build in LED as an indicator
  Wire.begin();		        // join i2c bus (address optional for master)
  delay(1000);             // To give some time to the GinoBot to turn initialize
  digitalWrite(LED,LOW);  //Turning Off Build in LED to show that the areduino is going to command the GinoBot

	gbot.set_buzzer_frequency(400); //Commanding the GinoBot to make a sound as a succesfull connection
	delay(200);
	gbot.set_buzzer_frequency(0);

}

void loop()
{

  Right = gbot.get_bottom_right();
  Left = gbot.get_bottom_left();
  distance = gbot.get_distance_front_mm();

  if (Right == 0 && Left == 0 && distance >150)
  {
    gbot.move_forward(Move_Speed);
  }
  else if(Right == 1 && distance >150)
  {
    gbot.rotate_left(Turn_Speed);
  }
  else if(Left == 1 && distance >150)
  {
    gbot.rotate_right(Turn_Speed);
  }
  else
  {
    gbot.stop();
  }
}
