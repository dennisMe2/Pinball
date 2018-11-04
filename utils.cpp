/*
 * utils.cpp
 *
 *  Created on: Nov 3, 2018
 *      Author: dennis
 */


#include <Arduino.h>

unsigned int intMillis(){
	return (unsigned int)(millis() & 0xffff);
}


