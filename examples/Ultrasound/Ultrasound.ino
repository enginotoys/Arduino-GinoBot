#include <ginobot.h>
// This example utilizes the front utrasound sensor of the GinoBot and tell the motos when to go forward, back and stop

/*

*************************** Commands used in this Examples ***************************
**********************https://github.com/enginotoys/Arduino-GinoBot*******************
* get_distance_front_mm() - Retriving the Distances from the from ultrasound Sensor
* move_forward()          - Commands the GinoBot to go Forward
* Move_bacwards()         - Commands the GinoBot to go Backwards
* stop()                  - Commands the GinoBot to cease any movement
* set_buzzer_frequency()  - Command the GinoBot Buzzer
* set_front_lights(r,g,b) - Sets the Colors of the Front RGB fron LEDs
* set_back_lights(r,g,b)  - Sets the Colors of the Back RGB fron LEDs

*/

// Defining Ports
#define LED 13

// Assigning Object for Library
Ginobot gbot;

// Defining Variables
int distance = 0;
int Move_Speed = 75; // Setting Speed For Motors

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
  distance = gbot.get_distance_front_mm(); // Assigning the distance to a variable
  
  if (distance >= 200)
  {
    gbot.move_forward(Move_Speed);            // Move Forward
    gbot.set_front_lights(0, 255, 0); // Front LEDs Turn Green
	  gbot.set_back_lights(0, 0, 0);    // Back LEDs Turn Off
  }
  else if (distance <= 100 )
  {
    gbot.move_backward(Move_Speed);             // Move Backward
    gbot.set_front_lights(0, 0, 0);     // Front LEDs Turn Off
	  gbot.set_back_lights(255, 0, 0);    // Back LEDs Turn Red
  }
  else
  {
    gbot.stop();
    gbot.set_front_lights(0, 0, 0);   // Front LEDs Turn Off
    gbot.set_back_lights(0, 0, 0);    // Back LEDs Turn Off
  }
    
}
