/*
 * hardware.h
 *
 *  Created on: Sep 14, 2015
 *      Author: Joshua Lyons
 */

#ifndef hardware_h
#define hardware_h

typedef enum
{
    LED_OFF,
    LED_ON,
    LED_NUMBER_OF_SETTINGS
} led_setting;

typedef enum
{
    MOTOR_CLOSING,
    MOTOR_OFF,
    MOTOR_OPENING,
    MOTOR_NUMBER_OF_SETTINGS
} motor_setting;

typedef enum
{
	ORDER_RCVD,
	VALID_PYMNT,
	INVALID_PYMNT,
	MANUF_FAILED,
	MANUF_COMPLETED,
	RECIEVED,
	LOST_PACKAGE
} event;

void set_closed_indicator(led_setting value);
void set_opened_indicator(led_setting value);
void set_motor(motor_setting value);

#endif
