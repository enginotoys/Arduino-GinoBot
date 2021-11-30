// Ginobot Class
#include <Arduino.h>
#include "Wire.h"

#define I2C_CMDS_LEN 30
#define I2C_RX_LEN 13

int I2C_transaction(uint8_t* tx_data, uint8_t* rx_data);

class Ginobot
{
	private:
		int I2C_transaction(uint8_t *tx_data, uint8_t *rx_data);
		uint8_t tx_data[I2C_CMDS_LEN + 2];
		uint8_t rx_data[I2C_CMDS_LEN + 2];
	public:
		Ginobot();
		void set_front_lights(uint8_t red, uint8_t green, uint8_t blue);
		void set_back_lights(uint8_t red, uint8_t green, uint8_t blue);	
		void set_buzzer_frequency(uint16_t frequency);
		void move(int8_t power);
		void move_forward(int8_t power);
		void move_backward(int8_t power);
		void rotate(int8_t power);
		void rotate_left(int8_t power);
		void rotate_right(int8_t power);
		void stop(void);
		void wheel_left_spin(int8_t power);
		void wheel_right_spin(int8_t power);

		void move_distance_mm (int16_t distance_mm, uint16_t wheel_diammeter_mm, uint8_t power);
		void rotate_clicks (int16_t clicks_count, uint8_t power);
		void wheel_left_turn(int32_t angle, uint8_t power);
		void wheel_right_turn(int32_t angle, uint8_t power);

		void set_IR_FL_threshold(uint8_t value);
		void set_IR_FR_threshold(uint8_t value);
		void set_IR_back_threshold(uint8_t value);
		void set_IR_bot_L_threshold (uint8_t value);
		void set_IR_bot_R_threshold (uint8_t value);
		void servo1_position(uint8_t value);
		void servo2_position(uint8_t value);
		uint8_t get_IR_FL();
		uint8_t get_IR_FL_analog();
		uint8_t get_IR_FR();
		uint8_t get_IR_FR_analog();
		uint8_t get_IR_back();
		uint8_t get_IR_back_analog();
		uint8_t get_bottom_left();
		uint8_t get_bottom_left_white();
		uint8_t get_bottom_left_red();
		uint8_t get_bottom_left_green();
		uint8_t get_bottom_left_blue();
		void get_bottom_left_all (uint8_t* digital, uint8_t* white, uint8_t* red, uint8_t* green, uint8_t* blue);
		uint8_t get_bottom_right();
		uint8_t get_bottom_right_white();
		uint8_t get_bottom_right_red();
		uint8_t get_bottom_right_green();
		uint8_t get_bottom_right_blue();
		void get_bottom_right_all (uint8_t* digital, uint8_t* white, uint8_t* red, uint8_t* green, uint8_t* blue);
		uint16_t get_distance_front_mm(void);
		int16_t get_wheel_left_speed();
		int16_t get_wheel_right_speed();
		int16_t get_wheel_left_position();
		int16_t get_wheel_right_position();
		uint8_t get_battery_level();

};