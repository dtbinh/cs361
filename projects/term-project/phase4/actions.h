/*
 * actions.h
 *
 * Modified on: Dec 6, 2015
 *      Author: Joshua Lyons and Conner Turnbull (Group 1)
 */

#ifndef ACTIONS_H_
#define ACTIONS_H_

#define order_H 2000 //high order
#define order_L 1000 //low order

#define cap_H 50 //high capacity
#define cap_L 10 //low capacity

#define dur_H 500 //high duration
#define dur_L 100 //low duration

#include <stdlib.h>
#include <stdint.h>

typedef enum
{
    DONE,
    LOST,
    FAIL
} stats;

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

void getAddress();
void chargeClient();
void startWarranty();
void updateStats(stats value);
void refund();
void resetAttempts();
int  incrementAttempts();
void getPaymentMethod();
void dispatchFactoryLines();
void shutDownFactoryLines();

#endif
