/*
 * demoApp.h
 *
 *  Created on: Feb 13, 2023
 *      Author: a.ertekin
 */

#ifndef INC_DEMOAPP_H_
#define INC_DEMOAPP_H_

#include "stdbool.h"
#include "stdint.h"
#include "string.h"

#include "main.h"


uint32_t	tickParameter = 0;

const uint8_t  testData[8] = { 0xEE , 0x01 , 0xEE , 0x02 , 0xEE , 0x03 , 0xEE , 0x04 };
const uint32_t testID	  = 0x1CFFFFFF;

void 		applicationMAIN(void);
void		applicationInit(void);

uint16_t 	getADCValue(void);





#endif /* INC_DEMOAPP_H_ */
