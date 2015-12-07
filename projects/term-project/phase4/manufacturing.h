/*
 * manufacturing.h
 *
 * Modified on: Dec 6, 2015
 *      Author: Joshua Lyons and Conner Turnbull (Group 1)
 */

#ifndef MANUFACTURING_H_
#define MANUFACTURING_H_

#include "state.h"


static state_t*	manufacturing_failed();
static state_t*	manufacturing_completed();
static void		entry_to();
static void		exit_from();

#endif
