/*
 * statemodel.h
 *
 *  Created on: Sep 14, 2015
 *      Author: joshualyons
 */

#ifndef statemodel_h
#define statemodel_h
#include <stdlib.h>
#include "hardware.h"
#include "state.h"

extern state_t accepting;
extern state_t processing;
extern state_t manufacturing;
extern state_t shippping;

void handle_event(event current_event);

#endif
