/*
 * TwoWire.h - TWI/I2C library for Arduino Due
 * Copyright (c) 2011 Cristian Maglie <c.maglie@bug.st>.
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef SkyRover_h
#define SkyRover_h


#include "Arduino.h"


class SkyRover
{
public:

	int16_t motor_pwm[4];
	

	void begin();
	void delay( int32_t delay_data );
	void uart1_printf( char *format, ... );
	void printf( char *format, ... );

	//-- 명령/기체 상태
	// 
	int8_t arm_get_status( void );
	bool   cmd_ready( void );

	//-- USB 시리얼의 메뉴 사용 유/무 
	//
	void menu_on(void);
	void menu_off(void);

	//-- 멀티위 동작 사용 유/무 
	//
	void   mw_on( void );
	void   mw_off( void );
	int8_t mw_get_status( void );

	//-- IMU 센서 데이터 
	//
	int16_t imu_get_angle_roll( void );
	int16_t imu_get_angle_pitch( void );
	int16_t imu_get_angle_yaw( void );

	int16_t imu_get_gyro_roll( void );
	int16_t imu_get_gyro_pitch( void );
	int16_t imu_get_gyro_yaw( void );

	//-- LED 
	//
	void led_toggle( uint8_t ch );
	void led_on( uint8_t ch );
	void led_off( uint8_t ch );

	//-- 블루투스 통신 명령 데이터 
	//
	int16_t cmd_get_roll( void );
	int16_t cmd_get_pitch( void );
	int16_t cmd_get_yaw( void );
	int16_t cmd_get_throttle( void );

	//-- 모터 제어 명령 
	//
	void motor_safe_off(void);
	void motor_safe_on(void);

	void motor_set_speed_FRONT_L( int16_t speed );	
	void motor_set_speed_FRONT_R( int16_t speed );	
	void motor_set_speed_REAR_L( int16_t speed );	
	void motor_set_speed_REAR_R( int16_t speed );	

private:
};


#endif

