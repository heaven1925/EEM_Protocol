/*
 * demoApp.c
 *
 *  Created on: Feb 13, 2023
 *      Author: a.ertekin
 */

#include "demoApp.h"

#include "EEMProtocol.h"
#include "EEMProtocol_Config.h"


EEM_Protocol_st	protocol;

extern BCM_Module_st	BCM_MSG;
/* HVAC module has been written Cpp language in order to arduino framework */
/* Simple computer protocol has written pyhton language */
extern BMS_Module_st	BMS_MSG;
extern MS1_Module_st	MS1_MSG;
extern MS2_Module_st	MS2_MSG;
extern ISO_Module_st	ISO_MSG;
extern TLM_Module_st	TLM_MSG;
extern YSB_Module_st	YSB_MSG;


/* 10 MS TICK IRQ Handlers */
void TIM1_UP_TIM10_IRQHandler(void)
{
  /* increase tick parameters */
  tickParameter++;

  /* Check Can FIFO's */
  EEM_PERIODIC(&protocol.obj.canPacket);

  /* Send 100ms periodic Data */
  if( ( tickParameter % 10 ) == 0 )
  {
	  memcpy(&protocol.obj.canPacket.DATA[0] , &BCM_MSG.Message07.payload[0] , 8);
	  protocol.obj.canPacket.EXTENDED_ID.identifier = BCM_MSG.Message07_ID;

	  protocol.ops.EEM_TX( &protocol.obj.canPacket , 0);

	  /* Toogle Pin every 100ms */
	  HAL_GPIO_TogglePin(LED_TEST_GPIO_Port, LED_TEST_Pin);
  }

  HAL_TIM_IRQHandler(&htim1);
}



uint16_t 	getADCValue(void)
{
	uint16_t adcValHandle = 0;

	HAL_ADC_Start(&hadc1);

	HAL_ADC_PollForConversion(&hadc1, 100);

	adcValHandle = HAL_ADC_GetValue(&hadc1);

	HAL_ADC_Stop(&hadc1);

	return adcValHandle;
}



void		applicationInit(void)
{
	protocol.ops = ops;
    protocol.ops.EEM_INIT(&protocol.obj);

    /* Send Test Data */
    memcpy(&protocol.obj.canPacket.DATA[0] , &testData[0] , 8);
    protocol.obj.canPacket.EXTENDED_ID.identifier = 0x1CFFFFFF;
    protocol.ops.EEM_TX( &protocol.obj.canPacket , 0);

}



void applicationMAIN(void)
{
	applicationInit();

	while(1)
	{
		BCM_MSG.Message08.SPN.MS1_Speed = (uint32_t)getADCValue();
	}

}
