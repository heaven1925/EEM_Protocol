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
extern HVAC_Module_st	HVAC_MSG;
extern SCB_Module_st	SCB_MSG;
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

  /* send sequance parameter */
  static uint8_t sendSequance = 0 ;
  sendSequance = tickParameter % 6 ; /* mod size of sended message count */

  /* Check Can FIFO's */
  EEM_PERIODIC(&protocol.obj.canPacket);


  /* Send 100ms periodic Data */
  if( ( tickParameter % 10 ) == 0 )
  {
	  switch( sendSequance )
	  {
	  case 0 :
		  /* Send MSG03 */
		  memcpy(&protocol.obj.canPacket.DATA[0] , &BCM_MSG.Message03.payload[0] , 8);
		  protocol.obj.canPacket.EXTENDED_ID.identifier = BCM_MSG.Message03_ID;
		  protocol.ops.EEM_TX( &protocol.obj.canPacket , 0);
	  break ;

	  case 1:
		  /* Send MSG04 */
		  memcpy(&protocol.obj.canPacket.DATA[0] , &BCM_MSG.Message04.payload[0] , 8);
		  protocol.obj.canPacket.EXTENDED_ID.identifier = BCM_MSG.Message04_ID;
		  protocol.ops.EEM_TX( &protocol.obj.canPacket , 0);
		  break;

	  case 2:
		  /* Send MSG05 */
		  memcpy(&protocol.obj.canPacket.DATA[0] , &BCM_MSG.Message05.payload[0] , 8);
		  protocol.obj.canPacket.EXTENDED_ID.identifier = BCM_MSG.Message05_ID;
		  protocol.ops.EEM_TX( &protocol.obj.canPacket , 0);
	  	  break;

	  case 3:
		  /* Send MSG11 */
		  memcpy(&protocol.obj.canPacket.DATA[0] , &BCM_MSG.Message11.payload[0] , 8);
		  protocol.obj.canPacket.EXTENDED_ID.identifier = BCM_MSG.Message11_ID;
		  protocol.ops.EEM_TX( &protocol.obj.canPacket , 0);
	  	  break;

	  case 4:
		  /* Send MSG12 */
		  memcpy(&protocol.obj.canPacket.DATA[0] , &BCM_MSG.Message12.payload[0] , 8);
		  protocol.obj.canPacket.EXTENDED_ID.identifier = BCM_MSG.Message12_ID;
		  protocol.ops.EEM_TX( &protocol.obj.canPacket , 0);
	  	  break;

	  case 5:
		  /* Send MSG19 */
		  memcpy(&protocol.obj.canPacket.DATA[0] , &BCM_MSG.Message19.payload[0] , 8);
		  protocol.obj.canPacket.EXTENDED_ID.identifier = BCM_MSG.Message19_ID;
		  protocol.ops.EEM_TX( &protocol.obj.canPacket , 0);
	  	  break;

	  case 6:
		  /* Send MSG20 */
		  memcpy(&protocol.obj.canPacket.DATA[0] , &BCM_MSG.Message03.payload[0] , 8);
		  protocol.obj.canPacket.EXTENDED_ID.identifier = BCM_MSG.Message20_ID;
		  protocol.ops.EEM_TX( &protocol.obj.canPacket , 0);
		  break;

	  default: break;

	  }

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
		BCM_MSG.Message11.SPN.BCM_MS1_Speed = (uint64_t)getADCValue();
		BCM_MSG.Message12.SPN.BCM_MS2_Speed = ~(uint64_t)getADCValue();



	}

}
