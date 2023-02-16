/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    EEMProtocol.c
  * @author	 Atakan ERTEKiN
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil CAN Stack
********************************************************************************/

#include "EEMProtocol_Config.h"
#include "EEMProtocol.h"

extern HVAC_Module_st	HVAC_MSG;
extern BCM_Module_st	BCM_MSG;
extern SCB_Module_st	SCB_MSG;
extern BMS_Module_st	BMS_MSG;
extern MS1_Module_st	MS1_MSG;
extern MS2_Module_st	MS2_MSG;
extern ISO_Module_st	ISO_MSG;
extern TLM_Module_st	TLM_MSG;
extern YSB_Module_st	YSB_MSG;



#if defined( BCM_MODULE )

/*******************************************************************************
	 @func    :	EEM_FILTER_BCM
	 @param   : FDCAN_FilterTypeDef sFilterConfig
	 @return  : EEM_ERR_T
	 @date	  : 7.02.2023
	 @INFO	  :	BCM Specific CANBUS Filtering Function
********************************************************************************/
EEM_ERR_T EEM_FILTER_BCM( EEM_Protocol_obj_st* param )
{
	EEM_ERR_T result = EEM_EOK;

#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))



#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))

	 param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	 param->fdHandle.sFilterConfig.FilterIndex 		= 0;
	 param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	 param->fdHandle.sFilterConfig.FilterConfig 	= FDCAN_FILTER_TO_RXFIFO0;
	 param->fdHandle.sFilterConfig.FilterID1 		= MessageID_01.identifier ;
	 param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	 param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	 if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	 {
		 return EEM_ERROR;
	 }

	 param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	 param->fdHandle.sFilterConfig.FilterIndex 		= 1;
	 param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	 param->fdHandle.sFilterConfig.FilterConfig 	= FDCAN_FILTER_TO_RXFIFO0;
	 param->fdHandle.sFilterConfig.FilterID1 		= MessageID_02.identifier ;
	 param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	 param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	 if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	 {
		 return EEM_ERROR;
	 }

	 param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	 param->fdHandle.sFilterConfig.FilterIndex 		= 2;
	 param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	 param->fdHandle.sFilterConfig.FilterConfig 	= FDCAN_FILTER_TO_RXFIFO0;
	 param->fdHandle.sFilterConfig.FilterID1 		= MessageID_07.identifier ;
	 param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	 param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	 if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	 {
		 return EEM_ERROR;
	 }

	 param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	 param->fdHandle.sFilterConfig.FilterIndex 		= 3;
	 param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	 param->fdHandle.sFilterConfig.FilterConfig 	= FDCAN_FILTER_TO_RXFIFO0;
	 param->fdHandle.sFilterConfig.FilterID1 		= MessageID_08.identifier ;
	 param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	 param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	 if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	 {
		 return EEM_ERROR;
	 }

	 param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	 param->fdHandle.sFilterConfig.FilterIndex 		= 4;
	 param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	 param->fdHandle.sFilterConfig.FilterConfig 	= FDCAN_FILTER_TO_RXFIFO0;
	 param->fdHandle.sFilterConfig.FilterID1 		= MessageID_09.identifier ;
	 param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	 param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	 if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	 {
		 return EEM_ERROR;
	 }

	 param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	 param->fdHandle.sFilterConfig.FilterIndex 		= 5;
	 param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	 param->fdHandle.sFilterConfig.FilterConfig 	= FDCAN_FILTER_TO_RXFIFO0;
	 param->fdHandle.sFilterConfig.FilterID1 		= MessageID_10.identifier ;
	 param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	 param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	 if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	 {
		 return EEM_ERROR;
	 }

	 param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	 param->fdHandle.sFilterConfig.FilterIndex 		= 6;
	 param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	 param->fdHandle.sFilterConfig.FilterConfig 	= FDCAN_FILTER_TO_RXFIFO0;
	 param->fdHandle.sFilterConfig.FilterID1 		= MessageID_18.identifier ;
	 param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	 param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	 if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	 {
		 return EEM_ERROR;
	 }

	 param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	 param->fdHandle.sFilterConfig.FilterIndex 		= 7;
	 param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	 param->fdHandle.sFilterConfig.FilterConfig 	= FDCAN_FILTER_TO_RXFIFO0;
	 param->fdHandle.sFilterConfig.FilterID1 		= MessageID_19.identifier ;
	 param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	 param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	 if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	 {
		 return EEM_ERROR;
	 }

#else

#if defined(SPI2CAN_Protocol)

	 /* MCP2515 Module specific filtering will patch later */

#else
//ERROR
#endif


#endif
	return result;
}

#elif defined( HVAC_MODULE )
/* HVAC module has been written Cpp language in order to arduino framework */
#elif defined( SCB_MODULE )
/* Simple computer protocol has written pyhton language */
#elif defined( BMS_MODULE )
EEM_ERR_T EEM_FILTER_BMS( EEM_Protocol_obj_st* param )
{
	EEM_ERR_T result = EEM_EOK;
#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))

#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))

#else

#if defined(SPI2CAN_Protocol)

#else
//ERROR
#endif

#endif
	return result;
}

#elif defined( MS1_MODULE )
EEM_ERR_T EEM_FILTER_MS1( EEM_Protocol_obj_st* param )
{
	EEM_ERR_T result = EEM_EOK;

#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))

#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))

	param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	param->fdHandle.sFilterConfig.FilterIndex 		= 0;
	param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	param->fdHandle.sFilterConfig.FilterConfig 		= FDCAN_FILTER_TO_RXFIFO0;
	param->fdHandle.sFilterConfig.FilterID1 		= MessageID_20.identifier ;
	param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	{
	 return EEM_ERROR;
	}

	param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	param->fdHandle.sFilterConfig.FilterIndex 		= 1;
	param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	param->fdHandle.sFilterConfig.FilterConfig 		= FDCAN_FILTER_TO_RXFIFO0;
	param->fdHandle.sFilterConfig.FilterID1 		= MessageID_21.identifier ;
	param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	{
	 return EEM_ERROR;
	}

#else



#if defined(SPI2CAN_Protocol)

#else
//ERROR
#endif

#endif
	return result;
}

#elif defined( MS2_MODULE )
EEM_ERR_T EEM_FILTER_MS2( EEM_Protocol_obj_st* param )
{
	EEM_ERR_T result = EEM_EOK;

#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))

#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))

	param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	param->fdHandle.sFilterConfig.FilterIndex 		= 0;
	param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	param->fdHandle.sFilterConfig.FilterConfig 		= FDCAN_FILTER_TO_RXFIFO0;
	param->fdHandle.sFilterConfig.FilterID1 		= MessageID_22.identifier ;
	param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	{
	 return EEM_ERROR;
	}

	EEM_CAN_ID_st MessageID_23    = {0}			 ;	/* 29 Bit Extended ID Frame */
	MessageID_23.Pages.priority   = PRIORITY_001 ;  /* 3 Bit Priortiy 			*/
	MessageID_23.Pages.reserved   = NOT_RESERVED ;	/* 1 Bit Reserved 			*/
	MessageID_23.Pages.dataPoint  = DATAPAGE_0	 ;	/* 1 Bit Data Page 			*/
	MessageID_23.Pages.messageID  = MESSAGE23 	 ;  /* 8 Bit Message Soft ID 	*/
	MessageID_23.Pages.DA		  = MS2_NODE	 ;	/* 8 Bit Destination Addr	*/
	MessageID_23.Pages.SA		  = BCM_NODE	 ;	/* 8 Bit Source Addr		*/

	param->fdHandle.sFilterConfig.IdType 			= FDCAN_EXTENDED_ID;
	param->fdHandle.sFilterConfig.FilterIndex 		= 1;
	param->fdHandle.sFilterConfig.FilterType 		= FDCAN_FILTER_MASK;
	param->fdHandle.sFilterConfig.FilterConfig 		= FDCAN_FILTER_TO_RXFIFO0;
	param->fdHandle.sFilterConfig.FilterID1 		= MessageID_23.identifier ;
	param->fdHandle.sFilterConfig.FilterID2 		= 0x1FFFFFFF ;
	param->fdHandle.sFilterConfig.RxBufferIndex 	= 0;
	if(HAL_FDCAN_ConfigFilter(&param->fdHandle.hfdcanHandle , &param->fdHandle.sFilterConfig) != HAL_OK)
	{
	 return EEM_ERROR;
	}

#else

#if defined(SPI2CAN_Protocol)

#else
//ERROR
#endif

#endif
	return result;
}

#elif defined( ISO_MODULE )
EEM_ERR_T EEM_FILTER_ISO( EEM_Protocol_obj_st* param )
{
	EEM_ERR_T result = EEM_EOK;
#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))

#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))

#else

#if defined(SPI2CAN_Protocol)

#else
//ERROR
#endif

#endif
	return result;
}
#elif defined( TLM_MODULE )
EEM_ERR_T EEM_FILTER_TLM( EEM_Protocol_obj_st* param )
{
	EEM_ERR_T result = EEM_EOK;
#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))

#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))

#else

#if defined(SPI2CAN_Protocol)

#else
//ERROR
#endif

#endif
	return result;
}

#elif defined( YSB_MODULE )
EEM_ERR_T EEM_FILTER_YSB( EEM_Protocol_obj_st* param )
{
	EEM_ERR_T result = EEM_EOK;
#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))

#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))

#else

#if defined(SPI2CAN_Protocol)

#else
//ERROR
#endif

#endif
	return result;
}

#endif
