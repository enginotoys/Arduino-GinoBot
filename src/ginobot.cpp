//  Ginobot Class

#include "ginobot.h"

// Commands data transfers. See host MCU protocol documentation
// both arrays sizes have to be >= than I2C_CMDS_LEN in size!
int Ginobot::I2C_transaction(uint8_t *tx_data, uint8_t *rx_data)
{
	uint8_t index = 0;
	// // printf debugging:-------------------
	// Serial.print("Transmitting: ");
	// Serial.write(tx_data, I2C_CMDS_LEN);
	// Serial.println();
	// //-------------------------------------
	Wire.beginTransmission(22);
	Wire.write(tx_data, I2C_CMDS_LEN);
	Wire.endTransmission();

	delay(2);	// <---- this is how long each command transfer takes. Data take about 0.3msecs to be transfered

	if (Wire.requestFrom(22, I2C_RX_LEN) == I2C_RX_LEN)
	{
		while (Wire.available())
		{
			rx_data[index] = Wire.read();
			index++;
			if (index > I2C_RX_LEN + 1)
				break;
		}
		// printf debugging:-------------------
		// Serial.print("     Received:     ");
		// Serial.write(rx_data, index);
		// Serial.println();
		//-------------------------------------
		if (index == I2C_RX_LEN && !memcmp(rx_data, tx_data, 8))
		{
			return 1;
		}
		index = 0;
		while (Wire.available());
	}
	// if we are here communication has failed
	// make all rx_data table zeros
	memset(rx_data, 0, I2C_RX_LEN);
	return 0;	
}

Ginobot::Ginobot()
{
	Wire.begin(); // join i2c bus (address optional for master)
}

// Set color of RGB front lights (RGB, each color from 0-255)
void Ginobot::set_front_lights(uint8_t red, uint8_t green, uint8_t blue)
{
	memcpy(tx_data, "S_IN_RF_", 8);
	tx_data[8] = red;
	tx_data[9] = green;
	tx_data[10] = blue;
	I2C_transaction(tx_data, rx_data);
}

//Set color of RGB back lights (RGB, each color from 0-255)
void Ginobot::set_back_lights(uint8_t red, uint8_t green, uint8_t blue)
{
	memcpy(tx_data, "S_IN_RB_", 8);
	tx_data[8] = red;
	tx_data[9] = green;
	tx_data[10] = blue;
	I2C_transaction(tx_data, rx_data);
}

//Set buzzer frequency (0=off)
void Ginobot::set_buzzer_frequency(uint16_t frequency)
{
	memcpy(tx_data, "S_IN_BZ_", 8);
	tx_data[8] = (uint8_t)((frequency & 0xFF00) >> 8);
	tx_data[9] = (uint8_t)(frequency & 0x00FF);
	I2C_transaction(tx_data, rx_data);
}

//Set both motors spin with power percent, from -100 to 100. 
//Positive parameter moves forward, rotates clockwise, negative number the other way.
void Ginobot::move(int8_t power)
{
	memcpy(tx_data, "S_IN_MB_", 8);
	tx_data[8] = power;
	tx_data[9] = power;
	I2C_transaction(tx_data, rx_data);
}

//Set both motors spin with power percent, from 0 to 100. 
//Moves robot's body forwards.
void Ginobot::move_forward(int8_t power)
{
	memcpy(tx_data, "S_IN_MB_", 8);
	tx_data[8] = power;
	tx_data[9] = power;
	I2C_transaction(tx_data, rx_data);
}

//Set both motors spin with power percent, from 0 to 100. 
//Moves robot's body backwards.
void Ginobot::move_backward(int8_t power)
{
	memcpy(tx_data, "S_IN_MB_", 8);
	tx_data[8] = power * (-1);
	tx_data[9] = power * (-1);
	I2C_transaction(tx_data, rx_data);
}

//Set both motors spin with power percent, from -100 to 100. 
//Positive parameter moves forward, rotates clockwise, negative number the other way.
void Ginobot::rotate(int8_t power)
{
	memcpy(tx_data, "S_IN_MB_", 8);
	tx_data[8] = power;
	tx_data[9] = power * (-1);
	I2C_transaction(tx_data, rx_data);
}

//Set both motors spin with power percent, from 0 to 100. 
//Rotates the robot's body towards the left direction
void Ginobot::rotate_left(int8_t power)
{
	memcpy(tx_data, "S_IN_MB_", 8);
	tx_data[8] = power * (-1);
	tx_data[9] = power;
	I2C_transaction(tx_data, rx_data);
}

//Set both motors spin with power percent, from 0 to 100. 
//Rotates the robot's body towards the right direction
void Ginobot::rotate_right(int8_t power)
{
	memcpy(tx_data, "S_IN_MB_", 8);
	tx_data[8] = power;
	tx_data[9] = power * (-1);
	I2C_transaction(tx_data, rx_data);
}

//Stop both motors (even if encoder commands are in operation)
void Ginobot::stop(void)
{
	memcpy(tx_data, "S_IN_MB_", 8);
	tx_data[8] = 0;
	tx_data[9] = 0;
	I2C_transaction(tx_data, rx_data);
}

//Spin left wheel motor with power percent (-100 to 100, positive is forward)
// The other wheel motion is not affected
void Ginobot::wheel_left_spin(int8_t power)
{
	memcpy(tx_data, "S_IN_ML_", 8);
	tx_data[8] = power;
	I2C_transaction(tx_data, rx_data);
}

// Spin right wheel motor with power percent (-100 to 100, positive is forward)
// The other wheel motion is not affected
void Ginobot::wheel_right_spin(int8_t power)
{
	memcpy(tx_data, "S_IN_MR_", 8);
	tx_data[8] = power;
	I2C_transaction(tx_data, rx_data);
}


// Moves wheels making use of an internal "encoders" harware functionality that measures and controls each wheel's rotation in resolution steps of 11.25 degrees (1/32 of full rotation).
// Motion happens on the background of execution, next command will be executed imediatelly after this command even if position has not been reached yet. 
// To know if position is reached,  wait for 100 milli seconds at least and then use  motor_get_speed() to see if it is zero, or see that the get_wheel_xxxx_position() returns the same result over time periods > 100msecs
// Positive parameter moves forward, negative number the other way. Wheel diameter in mm has to be provided since encoders measure rotation only
void Ginobot::move_distance_mm(int16_t distance_mm, uint16_t wheel_diammeter_mm, uint8_t power)
{
	int16_t clicks;	// has sign. One click is 1/32 of a wheel rotation
	int32_t circumference_mm;
	circumference_mm = (wheel_diammeter_mm * 3142) / 1000; // we use no floats, do not change paranthesis to avoid truncation errors
	clicks = (int16_t)( (distance_mm * 32 ) / circumference_mm );	// here as well
	memcpy(tx_data, "S_IN_ME_", 8);
	tx_data[8] = (uint8_t)((clicks & 0xFF00) >> 8);
	tx_data[9] = (uint8_t)(clicks & 0x00FF);
	tx_data[10] = (uint8_t)((clicks & 0xFF00) >> 8);
	tx_data[11] = (uint8_t)(clicks & 0x00FF);
	tx_data[12] = power;
	I2C_transaction(tx_data, rx_data);
	Serial.print("Clicks: ");
	Serial.println(clicks);
}

// Moves wheels making use of an internal "encoders" harware functionality that measures and controls each wheel's rotation in resolution steps of 11.25 degrees (1/32 of full rotation).
// Motion happens on the background of execution, next command will be executed imediatelly after this command even if position has not been reached yet. 
// To know if position is reached,  wait for 100 milli seconds at least and then use  motor_get_speed() to see if it is zero, or see that the get_wheel_xxxx_position() returns the same result over time periods > 100msecs
// Positive pramameter rotates right, negative left. The parameter "clicks count" is 1/32 of wheels rotation, you have to "tune" manually your rotations since wheels sleep
void Ginobot::rotate_clicks(int16_t clicks, uint8_t power)
{
	memcpy(tx_data, "S_IN_ME_", 8);
	tx_data[8] = (uint8_t)( (clicks & 0xFF00) >> 8 );
	tx_data[9] = (uint8_t)( clicks & 0x00FF);
	tx_data[10] = (uint8_t)( ((clicks * (-1)) & 0xFF00) >> 8);
	tx_data[11] = (uint8_t)( (clicks * (-1)) & 0x00FF);
	tx_data[12] = power;
	I2C_transaction(tx_data, rx_data);
	Serial.print("Clicks: ");
	Serial.println(clicks);
}

// Rotate a wheel using the internal wheels encoders
// Moves wheels making use of an internal "encoders" harware functionality that measures and controls each wheel's rotation in resolution steps of 11.25 degrees (1/32 of full rotation).
// Angle in degrees (where applied) can be any number positive (move forwards) or negative (backwards) e.g. 1000 will rotate for 2.7 cycles forward. 
// Motion happens on the background of execution, next command will be executed imediatelly after this command even if position has not been reached yet. 
// To know if position is reached,  wait for 100 milli seconds at least and then use  motor_get_speed() to see if it is zero, or see that the get_wheel_xxxx_position() returns the same result over time periods > 100msecs
void Ginobot::wheel_left_turn(int32_t angle, uint8_t power)
{
	int32_t clicks_long;
	int32_t clicks;
	clicks_long = (angle * 1000) / 11250;
	clicks = (int16_t)clicks_long;
	memcpy(tx_data, "S_IN_ME_", 8);
	tx_data[8] = (uint8_t)( (clicks & 0xFF00) >> 8 );
	tx_data[9] = (uint8_t)( clicks & 0x00FF);
	tx_data[10] = 0;
	tx_data[11] = 0;
	tx_data[12] = power;
	I2C_transaction(tx_data, rx_data);
	Serial.print("Clicks: ");
	Serial.println(clicks);
}

// Rotate a wheel using the internal wheels encoders
// Moves wheels making use of an internal "encoders" harware functionality that measures and controls each wheel's rotation in resolution steps of 11.25 degrees (1/32 of full rotation).
// Angle in degrees (where applied) can be any number positive (move forwards) or negative (backwards) e.g. 1000 will rotate for 2.7 cycles forward. 
// Motion happens on the background of execution, next command will be executed imediatelly after this command even if position has not been reached yet. 
// To know if position is reached,  wait for 100 milli seconds at least and then use  motor_get_speed() to see if it is zero, or see that the get_wheel_xxxx_position() returns the same result over time periods > 100msecs
void Ginobot::wheel_right_turn(int32_t angle, uint8_t power)
{
	int32_t clicks_long;
	int32_t clicks;
	clicks_long = (angle * 1000) / 11250;
	clicks = (int16_t)clicks_long;
	memcpy(tx_data, "S_IN_ME_", 8);
	tx_data[8] = 0;
	tx_data[9] = 0;
	tx_data[10] = (uint8_t)( (clicks & 0xFF00) >> 8 );
	tx_data[11] = (uint8_t)( clicks & 0x00FF);
	tx_data[12] = power;
	I2C_transaction(tx_data, rx_data);
	Serial.print("Clicks: ");
	Serial.println(clicks);
}





// Set the threshold, analog value above that yields digital value false, below yields true. 
// Range:0-100 (prefered 10-70)
void Ginobot::set_IR_FL_threshold(uint8_t value)
{
	memcpy(tx_data, "S_IN_FL_", 8);
	tx_data[8] = value;
	I2C_transaction(tx_data, rx_data);
}

// Set the threshold, analog value above that yields digital value false, below yields true. 
// Range:0-100 (prefered 10-70)
void Ginobot::set_IR_FR_threshold(uint8_t value)
{
	memcpy(tx_data, "S_IN_FR_", 8);
	tx_data[8] = value;
	I2C_transaction(tx_data, rx_data);
}

// Set the threshold, analog value above that yields digital value false, below yields true. 
// Range:0-100 (prefered 10-70)
void Ginobot::set_IR_back_threshold(uint8_t value)
{
	memcpy(tx_data, "S_IN_BK_", 8);
	tx_data[8] = value;
	I2C_transaction(tx_data, rx_data);
}

// Set the threshold, analog value above that yields digital value false, below yields true. 
// Range:0-100 (prefered 10-70)
void Ginobot::set_IR_bot_L_threshold(uint8_t value)
{
	memcpy(tx_data, "S_IN_CL_", 8);
	tx_data[8] = value;
	I2C_transaction(tx_data, rx_data);
}

// Set the threshold, analog value above that yields digital value false, below yields true. 
// Range:0-100 (prefered 10-70)
void Ginobot::set_IR_bot_R_threshold(uint8_t value)
{
	memcpy(tx_data, "S_IN_CR_", 8);
	tx_data[8] = value;
	I2C_transaction(tx_data, rx_data);
}

// Set the position of an internally connected servo motor (in degrees). 
// If connected it will try to get to that position (angle)
void Ginobot::servo1_position(uint8_t value)
{
	memcpy(tx_data, "S_IN_S1_", 8);
	tx_data[8] = value;
	I2C_transaction(tx_data, rx_data);
}

// Set the position of an internally connected servo motor (in degrees). 
// If connected it will try to get to that position (angle)
void Ginobot::servo2_position(uint8_t value)
{
	memcpy(tx_data, "S_IN_S2_", 8);
	tx_data[8] = value;
	I2C_transaction(tx_data, rx_data);
}

// Get IR Front Left proximity sensor digital value (true / false)
uint8_t Ginobot::get_IR_FL()
{
	memcpy(tx_data, "G_IN_FL_", 8);
	I2C_transaction(tx_data, rx_data);
	return rx_data[8];
}

// Get IR Front Left proximity sensor analog value (0-100, the further the higher)
uint8_t Ginobot::get_IR_FL_analog()
{
	memcpy(tx_data, "G_IN_FL_", 8);
	I2C_transaction(tx_data, rx_data);
	return rx_data[9];
}

// Get IR Front Right proximity sensor digital value (true / false)
uint8_t Ginobot::get_IR_FR()
{
	memcpy(tx_data, "G_IN_FR_", 8);
	I2C_transaction(tx_data, rx_data);
	return rx_data[8];
}

// Get IR Front Right proximity sensor analog value (0-100, the further the higher)
uint8_t Ginobot::get_IR_FR_analog()
{
	memcpy(tx_data, "G_IN_FR_", 8);
	I2C_transaction(tx_data, rx_data);
	return rx_data[9];
}

// Get IR back proximity sensor digital value (true / false)
uint8_t Ginobot::get_IR_back()
{
	memcpy(tx_data, "G_IN_IB_", 8);
	I2C_transaction(tx_data, rx_data);
	return rx_data[8];
}

// Get IR back proximity sensor analog value (0-100, the further the higher)
uint8_t Ginobot::get_IR_back_analog()
{
	memcpy(tx_data, "G_IN_IB_", 8);
	I2C_transaction(tx_data, rx_data);
	return rx_data[9];
}

// Get bottom (line) color sensor proximity digital value (true / false)
uint8_t Ginobot::get_bottom_left()
{
	memcpy(tx_data, "G_IN_CL_", 8);
	I2C_transaction(tx_data, rx_data);
	return rx_data[11];
}

// Get bottom (line) color sensor proximity analog value (0-100, the further the higher)
uint8_t Ginobot::get_bottom_left_white()
{
	memcpy(tx_data, "G_IN_CL_", 8);
	I2C_transaction(tx_data, rx_data);
	return rx_data[12];
}

// Get bottom (line) color sensor color red value (0-255)
uint8_t Ginobot::get_bottom_left_red()
{
	memcpy(tx_data, "G_IN_CL_", 8);
	I2C_transaction(tx_data, rx_data);
	return rx_data[8];
}

// Get bottom (line) color sensor color green value (0-255)
uint8_t Ginobot::get_bottom_left_green()
{
	memcpy(tx_data, "G_IN_CL_", 8);
	I2C_transaction(tx_data, rx_data);
	return rx_data[9];
}

// Get bottom (line) color sensor color blue value (0-255)
uint8_t Ginobot::get_bottom_left_blue()
{
	memcpy(tx_data, "G_IN_CL_", 8);
	I2C_transaction(tx_data, rx_data);
	return rx_data[10];
}

// Get bottom (line) color sensor all values at onece (takes less I2C communication time)
// Note that arguments are pointers, use '&' if your variables are not pointers
void Ginobot::get_bottom_left_all (uint8_t* digital, uint8_t* white, uint8_t* red, uint8_t* green, uint8_t* blue)
{
	memcpy(tx_data, "G_IN_CL_", 8);
	I2C_transaction(tx_data, rx_data);
	*digital = rx_data[11];
	*white = rx_data[12];
	*red = rx_data[8];
	*green = rx_data[9];
	*blue = rx_data[10];
	return;
}

// Get bottom (line) color sensor proximity digital value (true / false)
uint8_t Ginobot::get_bottom_right()
{
	memcpy(tx_data, "G_IN_CR_", 8);
	I2C_transaction(tx_data, rx_data);
	return rx_data[11];
}

// Get bottom (line) color sensor proximity analog value (0-100, the further the higher)
uint8_t Ginobot::get_bottom_right_white()
{
	memcpy(tx_data, "G_IN_CR_", 8);
	I2C_transaction(tx_data, rx_data);
	return rx_data[12];
}

// Get bottom (line) color sensor color red value (0-255)
uint8_t Ginobot::get_bottom_right_red()
{
	memcpy(tx_data, "G_IN_CR_", 8);
	I2C_transaction(tx_data, rx_data);
	return rx_data[8];
}

// Get bottom (line) color sensor color green value (0-255)
uint8_t Ginobot::get_bottom_right_green()
{
	memcpy(tx_data, "G_IN_CR_", 8);
	I2C_transaction(tx_data, rx_data);
	return rx_data[9];
}

// Get bottom (line) color sensor color blue value (0-255)
uint8_t Ginobot::get_bottom_right_blue()
{
	memcpy(tx_data, "G_IN_CR_", 8);
	I2C_transaction(tx_data, rx_data);
	return rx_data[10];
}

// Get bottom (line) color sensor all values at onece (takes less I2C communication time)
// Note that arguments are pointers, use '&' if your variables are not pointers
void Ginobot::get_bottom_right_all (uint8_t* digital, uint8_t* white, uint8_t* red, uint8_t* green, uint8_t* blue)
{
	memcpy(tx_data, "G_IN_CR_", 8);
	I2C_transaction(tx_data, rx_data);
	*digital = rx_data[11];
	*white = rx_data[12];
	*red = rx_data[8];
	*green = rx_data[9];
	*blue = rx_data[10];
	return;
}

// Get fornt internal ultrasonic distance sensor value (in mm)
uint16_t Ginobot::get_distance_front_mm(void)
{
	memcpy(tx_data, "G_IN_US_", 8);
	I2C_transaction(tx_data, rx_data);
	return ((((uint16_t)rx_data[8]) << 8) + (uint16_t)rx_data[9]);
}

// Get the (real time) spinning speed of a wheel in RPM (rotations per minute)
// sign denotes direction (positive is forward)
int16_t Ginobot::get_wheel_left_speed(void)
{
	memcpy(tx_data, "G_IN_ML_", 8);
	I2C_transaction(tx_data, rx_data);
	return (int16_t)((((uint16_t)rx_data[8]) << 8) + (uint16_t)rx_data[9]);
}

// Get the (real time) spinning speed of a wheel in RPM (rotations per minute)
// sign denotes direction (positive is forward)
int16_t Ginobot::get_wheel_right_speed(void)
{
	memcpy(tx_data, "G_IN_MR_", 8);
	I2C_transaction(tx_data, rx_data);
	return (int16_t)((((uint16_t)rx_data[8]) << 8) + (uint16_t)rx_data[9]);
}

// Get the position of a wheel in 1/32nds of rotation. 
// Accumulated since power up, positive is forwards negative is backwards (from position on power-up)
int16_t Ginobot::get_wheel_left_position(void)
{
	memcpy(tx_data, "G_IN_PL_", 8);
	I2C_transaction(tx_data, rx_data);
	return (int16_t)((((uint16_t)rx_data[8]) << 8) + (uint16_t)rx_data[9]);
}

// Get the position of a wheel in 1/32nds of rotation. 
// Accumulated since power up, positive is forwards negative is backwards (from position on power-up)
int16_t Ginobot::get_wheel_right_position(void)
{
	memcpy(tx_data, "G_IN_PR_", 8);
	I2C_transaction(tx_data, rx_data);
	return (int16_t)((((uint16_t)rx_data[8]) << 8) + (uint16_t)rx_data[9]);
}

// An estimate of battery charge level in 0-4
uint8_t Ginobot::get_battery_level()
{
	memcpy(tx_data, "G_IN_BT_", 8);
	I2C_transaction(tx_data, rx_data);
	return rx_data[8];
}
