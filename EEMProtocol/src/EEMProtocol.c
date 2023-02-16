/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    EEMProtocol.h
  * @author	 Atakan ERTEKiN
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil CAN Stack
********************************************************************************/

#include "EEMProtocol.h"
#include "EEMProtocol_Config.h"

const	EEM_Protocol_opr_st		ops = 
{
	EEM_INIT		,
	EEM_TX			,
	EEM_RX
};

BCM_Module_st	BCM_MSG;
HVAC_Module_st	HVAC_MSG;
SCB_Module_st	SCB_MSG;
BMS_Module_st	BMS_MSG;
MS1_Module_st	MS1_MSG;
MS2_Module_st	MS2_MSG;
ISO_Module_st	ISO_MSG;
TLM_Module_st	TLM_MSG;
YSB_Module_st	YSB_MSG;


/*******************************************************************************
	 @func    :	
	 @param   : 
	 @return  : 
	 @date	  : 
	 @INFO		:	
********************************************************************************/
EEM_ERR_T EEM_INIT( EEM_Protocol_obj_st*  param )
{
	
	EEM_ERR_T result = EEM_EOK;

/* Ring Buffer Init Sequance */

	param->ringBuffer.head = 0;
	param->ringBuffer.tail = 0;
	param->ringBuffer.full = EEM_FALSE;

#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))
	
	
	
	
#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))
	/*@NOTICE: All Configs for 42MHz CAN BASE CLOCK */

	param->fdHandle.hfdcanHandle.Instance 					= FDCAN1;
	param->fdHandle.hfdcanHandle.Init.FrameFormat 			= FDCAN_FRAME_CLASSIC;
	param->fdHandle.hfdcanHandle.Init.Mode 					= FDCAN_MODE_NORMAL;
	param->fdHandle.hfdcanHandle.Init.AutoRetransmission 	= ENABLE;
	param->fdHandle.hfdcanHandle.Init.TransmitPause 		= DISABLE;
	param->fdHandle.hfdcanHandle.Init.ProtocolException 	= DISABLE;
	param->fdHandle.hfdcanHandle.Init.NominalPrescaler 		= 12;
	param->fdHandle.hfdcanHandle.Init.NominalSyncJumpWidth 	= 1;
	param->fdHandle.hfdcanHandle.Init.NominalTimeSeg1 		= 11;
	param->fdHandle.hfdcanHandle.Init.NominalTimeSeg2 		= 2;
	param->fdHandle.hfdcanHandle.Init.DataPrescaler 		= 1;
	param->fdHandle.hfdcanHandle.Init.DataSyncJumpWidth 	= 1;
	param->fdHandle.hfdcanHandle.Init.DataTimeSeg1 			= 1;
	param->fdHandle.hfdcanHandle.Init.DataTimeSeg2 			= 1;
	param->fdHandle.hfdcanHandle.Init.MessageRAMOffset 		= 0;
	param->fdHandle.hfdcanHandle.Init.StdFiltersNbr 		= 0;
#if 	defined(BCM_MODULE)
	param->fdHandle.hfdcanHandle.Init.ExtFiltersNbr 		= 7;
#elif	defined( HVAC_MODULE )
/* HVAC module protocol has been written cpp language in order to arduino framework */
#elif	defined( SCB_MODULE )
/* Simple computer protocol has been written pyhton language */
#elif	defined( BMS_MODULE )
	param->fdHandle.hfdcanHandle.Init.ExtFiltersNbr 		= 2;
#elif	defined( MS1_MODULE )
	param->fdHandle.hfdcanHandle.Init.ExtFiltersNbr 		= 1;
#elif	defined( MS2_MODULE )
	param->fdHandle.hfdcanHandle.Init.ExtFiltersNbr 		= 1;
#elif	defined( ISO_MODULE )
	param->fdHandle.hfdcanHandle.Init.ExtFiltersNbr 		= 1;
#elif	defined( TLM_MODULE )
	param->fdHandle.hfdcanHandle.Init.ExtFiltersNbr 		= 1;
#else
	param->fdHandle.hfdcanHandle.Init.ExtFiltersNbr 		= 1; //@INFO: Tüm can paketleri alınır.
#endif
	param->fdHandle.hfdcanHandle.Init.RxFifo0ElmtsNbr 		= 1;
	param->fdHandle.hfdcanHandle.Init.RxFifo0ElmtSize 		= FDCAN_DATA_BYTES_8;
	param->fdHandle.hfdcanHandle.Init.RxFifo1ElmtsNbr 		= 0;
	param->fdHandle.hfdcanHandle.Init.RxFifo1ElmtSize 		= FDCAN_DATA_BYTES_8;
	param->fdHandle.hfdcanHandle.Init.RxBuffersNbr 			= 1;
	param->fdHandle.hfdcanHandle.Init.RxBufferSize 			= FDCAN_DATA_BYTES_8;
	param->fdHandle.hfdcanHandle.Init.TxEventsNbr 			= 0;
	param->fdHandle.hfdcanHandle.Init.TxBuffersNbr 			= 0;
	param->fdHandle.hfdcanHandle.Init.TxFifoQueueElmtsNbr 	= 24;
	param->fdHandle.hfdcanHandle.Init.TxFifoQueueMode 		= FDCAN_TX_FIFO_OPERATION;
	param->fdHandle.hfdcanHandle.Init.TxElmtSize 			= FDCAN_DATA_BYTES_8;
	if (HAL_FDCAN_Init(&param->fdHandle.hfdcanHandle) != HAL_OK)
	{
		return EEM_ERROR;
	}
#else

#if defined(SPI2CAN_Protocol)

	EEM_U8 ret;

	ret = CANSPI_Initialize();
	if( ret < 0 )
	{
		return EEM_ERROR;
	}

#else

#endif

#endif

	/* Message Identifier Handler */
	EEM_CAN_ID_st ID[SIZE_OF_MSG] = {0};

	ID[0].Pages.priority 	= PRIORITY_010 ;
	ID[0].Pages.reserved 	= NOT_RESERVED ;
	ID[0].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[0].Pages.messageID 	= MESSAGE01 ;
	ID[0].Pages.DA 			= BCM_NODE;
	ID[0].Pages.SA 			= HVAC_NODE ;
	HVAC_MSG.Message01_ID = ID[0].identifier ;

	ID[1].Pages.priority 	= PRIORITY_010 ;
	ID[1].Pages.reserved 	= NOT_RESERVED ;
	ID[1].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[1].Pages.messageID 	= MESSAGE02 ;
	ID[1].Pages.DA 			= BCM_NODE;
	ID[1].Pages.SA 			= HVAC_NODE ;
	HVAC_MSG.Message02_ID = ID[1].identifier ;

	ID[2].Pages.priority 	= PRIORITY_100 ;
	ID[2].Pages.reserved 	= NOT_RESERVED ;
	ID[2].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[2].Pages.messageID 	= MESSAGE03 ;
	ID[2].Pages.DA 			= TLM_NODE;
	ID[2].Pages.SA 			= BCM_NODE;
	BCM_MSG.Message03_ID = ID[2].identifier ;

	ID[3].Pages.priority 	= PRIORITY_100 ;
	ID[3].Pages.reserved 	= NOT_RESERVED ;
	ID[3].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[3].Pages.messageID 	= MESSAGE04 ;
	ID[3].Pages.DA 			= SCB_NODE;
	ID[3].Pages.SA 			= BCM_NODE;
	BCM_MSG.Message04_ID = ID[3].identifier ;

	ID[4].Pages.priority 	= PRIORITY_100 ;
	ID[4].Pages.reserved 	= NOT_RESERVED ;
	ID[4].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[4].Pages.messageID 	= MESSAGE05 ;
	ID[4].Pages.DA 			= SCB_NODE;
	ID[4].Pages.SA 			= BCM_NODE;
	BCM_MSG.Message05_ID = ID[4].identifier ;

	ID[5].Pages.priority 	= PRIORITY_100 ;
	ID[5].Pages.reserved 	= NOT_RESERVED ;
	ID[5].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[5].Pages.messageID 	= MESSAGE06 ;
	ID[5].Pages.DA 			= SCB_NODE;
	ID[5].Pages.SA 			= BMS_NODE;
	BMS_MSG.Message06_ID = ID[5].identifier ;

	ID[6].Pages.priority 	= PRIORITY_100 ;
	ID[6].Pages.reserved 	= NOT_RESERVED ;
	ID[6].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[6].Pages.messageID 	= MESSAGE07 ;
	ID[6].Pages.DA 			= SCB_NODE;
	ID[6].Pages.SA 			= BMS_NODE;
	BMS_MSG.Message07_ID = ID[6].identifier ;

	ID[7].Pages.priority 	= PRIORITY_100 ;
	ID[7].Pages.reserved 	= NOT_RESERVED ;
	ID[7].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[7].Pages.messageID 	= MESSAGE08 ;
	ID[7].Pages.DA 			= SCB_NODE;
	ID[7].Pages.SA 			= BMS_NODE;
	BMS_MSG.Message08_ID = ID[7].identifier ;

	ID[8].Pages.priority 	= PRIORITY_100 ;
	ID[8].Pages.reserved 	= NOT_RESERVED ;
	ID[8].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[8].Pages.messageID 	= MESSAGE09 ;
	ID[8].Pages.DA 			= SCB_NODE;
	ID[8].Pages.SA 			= BMS_NODE;
	BMS_MSG.Message09_ID = ID[8].identifier ;

	ID[9].Pages.priority 	= PRIORITY_100 ;
	ID[9].Pages.reserved 	= NOT_RESERVED ;
	ID[9].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[9].Pages.messageID 	= MESSAGE10 ;
	ID[9].Pages.DA 			= SCB_NODE;
	ID[9].Pages.SA 			= BMS_NODE;
	BMS_MSG.Message10_ID = ID[9].identifier ;

	ID[10].Pages.priority 	= PRIORITY_001 ;
	ID[10].Pages.reserved 	= NOT_RESERVED ;
	ID[10].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[10].Pages.messageID 	= MESSAGE11 ;
	ID[10].Pages.DA 		= MS1_NODE;
	ID[10].Pages.SA 		= BCM_NODE ;
	BCM_MSG.Message11_ID = ID[10].identifier ;

	ID[11].Pages.priority 	= PRIORITY_001 ;
	ID[11].Pages.reserved 	= NOT_RESERVED ;
	ID[11].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[11].Pages.messageID 	= MESSAGE12 ;
	ID[11].Pages.DA 		= MS2_NODE;
	ID[11].Pages.SA 		= BCM_NODE ;
	BCM_MSG.Message12_ID = ID[11].identifier ;

	ID[12].Pages.priority 	= PRIORITY_001 ;
	ID[12].Pages.reserved 	= NOT_RESERVED ;
	ID[12].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[12].Pages.messageID 	= MESSAGE13 ;
	ID[12].Pages.DA 		= BCM_NODE ;
	ID[12].Pages.SA 		= MS1_NODE ;
	MS1_MSG.Message13_ID = ID[12].identifier ;

	ID[13].Pages.priority 	= PRIORITY_001 ;
	ID[13].Pages.reserved 	= NOT_RESERVED ;
	ID[13].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[13].Pages.messageID 	= MESSAGE14 ;
	ID[13].Pages.DA 		= BCM_NODE ;
	ID[13].Pages.SA 		= MS1_NODE ;
	MS1_MSG.Message14_ID = ID[13].identifier ;

	ID[14].Pages.priority 	= PRIORITY_001 ;
	ID[14].Pages.reserved 	= NOT_RESERVED ;
	ID[14].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[14].Pages.messageID 	= MESSAGE15 ;
	ID[14].Pages.DA 		= BCM_NODE ;
	ID[14].Pages.SA 		= MS1_NODE ;
	MS1_MSG.Message15_ID = ID[14].identifier ;

    ID[15].Pages.priority 	= PRIORITY_001 ;
    ID[15].Pages.reserved 	= NOT_RESERVED ;
    ID[15].Pages.dataPoint 	= DATAPAGE_0 ;
    ID[15].Pages.messageID 	= MESSAGE16 ;
    ID[15].Pages.DA 		= BCM_NODE ;
    ID[15].Pages.SA 		= MS2_NODE ;
    MS2_MSG.Message16_ID = ID[15].identifier ;

	ID[16].Pages.priority 	= PRIORITY_001 ;
	ID[16].Pages.reserved 	= NOT_RESERVED ;
	ID[16].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[16].Pages.messageID 	= MESSAGE17 ;
	ID[16].Pages.DA 		= BCM_NODE ;
	ID[16].Pages.SA 		= MS2_NODE ;
	MS2_MSG.Message17_ID = ID[16].identifier ;

	ID[17].Pages.priority 	= PRIORITY_001 ;
	ID[17].Pages.reserved 	= NOT_RESERVED ;
	ID[17].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[17].Pages.messageID 	= MESSAGE18 ;
	ID[17].Pages.DA 		= BCM_NODE ;
	ID[17].Pages.SA 		= MS2_NODE ;
	MS2_MSG.Message18_ID = ID[17].identifier ;

	ID[18].Pages.priority 	= PRIORITY_001 ;
	ID[18].Pages.reserved 	= NOT_RESERVED ;
	ID[18].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[18].Pages.messageID 	= MESSAGE19 ;
	ID[18].Pages.DA 		= BCM_NODE ;
	ID[18].Pages.SA 		= MS1_NODE ;
	BCM_MSG.Message19_ID = ID[18].identifier ;

	ID[19].Pages.priority 	= PRIORITY_001 ;
	ID[19].Pages.reserved 	= NOT_RESERVED ;
	ID[19].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[19].Pages.messageID 	= MESSAGE20 ;
	ID[19].Pages.DA 		= BCM_NODE ;
	ID[19].Pages.SA 		= MS2_NODE ;
	BCM_MSG.Message20_ID = ID[19].identifier ;

	ID[20].Pages.priority 	= PRIORITY_011 ;
	ID[20].Pages.reserved 	= NOT_RESERVED ;
	ID[20].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[20].Pages.messageID 	= MESSAGE21 ;
	ID[20].Pages.DA 		= BCM_NODE;
	ID[20].Pages.SA 		= SCB_NODE;
	SCB_MSG.Message21_ID = ID[20].identifier ;

	ID[21].Pages.priority 	= PRIORITY_111 ;
	ID[21].Pages.reserved 	= NOT_RESERVED ;
	ID[21].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[21].Pages.messageID 	= MESSAGE22 ;
	ID[21].Pages.DA 		= BCM_NODE;
	ID[21].Pages.SA 		= TLM_NODE;
	TLM_MSG.Message22_ID = 	ID[21].identifier ;

	ID[22].Pages.priority 	= PRIORITY_111 ;
	ID[22].Pages.reserved 	= NOT_RESERVED ;
	ID[22].Pages.dataPoint 	= DATAPAGE_0 ;
	ID[22].Pages.messageID 	= MESSAGE23 ;
	ID[22].Pages.DA 		= BCM_NODE;
	ID[22].Pages.SA 		= TLM_NODE;
	TLM_MSG.Message23_ID = 	ID[22].identifier ;


#if defined( BCM_MODULE )
	if( EEM_FILTER_BCM( param ) != EEM_EOK ) return EEM_ERROR;
#elif	defined( HVAC_MODULE )
	/* HVAC module has been written Cpp language in order to arduino framework */
#elif	defined( SCB_MODULE )
/* Simple computer protocol has written pyhton language */
#elif	defined( BMS_MODULE )
	if( EEM_FILTER_BMS( param ) != EEM_EOK ) return EEM_ERROR;
#elif	defined( MS1_MODULE )
	if( EEM_FILTER_MS1( param ) != EEM_EOK ) return EEM_ERROR;
#elif	defined( MS2_MODULE )
	if( EEM_FILTER_MS2( param ) != EEM_EOK ) return EEM_ERROR;
#elif	defined( ISO_MODULE )
	if( EEM_FILTER_ISO( param ) != EEM_EOK ) return EEM_ERROR;
#elif	defined( TLM_MODULE )
	if( EEM_FILTER_TLM( param ) != EEM_EOK ) return EEM_ERROR;
#else
	/* No Filter */
#endif


#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))





#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))

	/* Configure global filter to reject all non-matching frames */
	 HAL_FDCAN_ConfigGlobalFilter(&param->fdHandle.hfdcanHandle, FDCAN_REJECT, FDCAN_REJECT, FDCAN_REJECT_REMOTE, FDCAN_REJECT_REMOTE);

	if(HAL_FDCAN_Start(&param->fdHandle.hfdcanHandle)!= HAL_OK)
	{
		return EEM_ERROR;
	}

	if (HAL_FDCAN_ActivateNotification(&param->fdHandle.hfdcanHandle, FDCAN_IT_RX_FIFO0_NEW_MESSAGE
																	   , 0) != HAL_OK)
	{
		return EEM_ERROR;
	}

	/* TEST MESSAGE FOR CAN LINE */
	/*******************************************************************************/
	FDCAN_TxHeaderTypeDef   TestTxHeader;
	EEM_U8               	TestTxData[8] = { 0xEE , EEM_VERSION , 0xEE , EEM_SUBVERSION , 0xEE , EEM_REVISION , 0xEE , 0xEE};
	TestTxHeader.Identifier 			= 0x65D;
	TestTxHeader.IdType 				= FDCAN_STANDARD_ID;
	TestTxHeader.TxFrameType 			= FDCAN_DATA_FRAME;
	TestTxHeader.DataLength 			= FDCAN_DLC_BYTES_8;
	TestTxHeader.ErrorStateIndicator 	= FDCAN_ESI_ACTIVE;
	TestTxHeader.BitRateSwitch	 		= FDCAN_BRS_OFF;
	TestTxHeader.FDFormat 				= FDCAN_CLASSIC_CAN;
	TestTxHeader.TxEventFifoControl 	= FDCAN_STORE_TX_EVENTS;
	TestTxHeader.MessageMarker 			= 0;
	if (HAL_FDCAN_AddMessageToTxFifoQ(&param->fdHandle.hfdcanHandle, &TestTxHeader, TestTxData)!= HAL_OK)
	{
		return EEM_ERROR;
	}
	/*******************************************************************************/
#else

#if defined(SPI2CAN_Protocol)

#else

#endif

#endif

	return result;
}



/*******************************************************************************
	 @func    :	
	 @param   : 
	 @return  : 
	 @date	  : 
	 @INFO	  :
********************************************************************************/
void   EEM_PUSH( EEM_RING_Buffer_st* ringBuf , EEM_CAN_Packet_st* param)
{
	EEM_U8 loopVal = 0 ;

	for(loopVal = 0 ; loopVal < 8 ; loopVal++)
	{
		ringBuf->data[ ringBuf->tail ][ loopVal ] = param->DATA[ loopVal ];
	}
	ringBuf->id[ ringBuf->tail ].identifier = param->EXTENDED_ID.identifier;
	ringBuf->byte_count++;

	ringBuf->tail = ( ringBuf->tail + 1 ) % EEM_BUFFER_SIZE ;
	
	if( ringBuf->tail == ringBuf->head )
	{
		ringBuf->full = EEM_TRUE ;
	}
	
}



/*******************************************************************************
	 @func    :	
	 @param   : 
	 @return  : 
	 @date	  : 
	 @INFO		:	
********************************************************************************/
void	EEM_POP( EEM_RING_Buffer_st* ringBuf , EEM_CAN_Packet_st* param)
{
	EEM_U8 loopVal = 0 ;

	for(loopVal = 0 ; loopVal <= 8 ; loopVal++)
	{
		param->DATA[ loopVal ] = ringBuf->data[ ringBuf->head ][ loopVal ];
	}
	param->EXTENDED_ID.identifier = ringBuf->id[ ringBuf->head ].identifier;
	ringBuf->byte_count++;
	
	ringBuf->head = (ringBuf->head + 1) % EEM_BUFFER_SIZE ;
	ringBuf->full = EEM_FALSE;


}


/*******************************************************************************
	 @func    :	
	 @param   : 
	 @return  : 
	 @date	  : 
	 @INFO		:	
********************************************************************************/
EEM_ERR_T 		EEM_TX( EEM_CAN_Packet_st* param, EEM_U32 period )
{
	EEM_ERR_T result = EEM_EOK;

#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))


#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))

	memcpy( &protocol.obj.fdHandle.txData , &param->DATA[0] , EEM_MAX_SIZE );

	protocol.obj.fdHandle.txHeader.IdType 				= FDCAN_EXTENDED_ID 				;
	protocol.obj.fdHandle.txHeader.Identifier			= param->EXTENDED_ID.identifier		;
	protocol.obj.fdHandle.txHeader.TxFrameType			= FDCAN_DATA_FRAME			        ;
	protocol.obj.fdHandle.txHeader.DataLength			= FDCAN_DLC_BYTES_8			        ;
	protocol.obj.fdHandle.txHeader.BitRateSwitch 		= FDCAN_BRS_OFF				        ;
	protocol.obj.fdHandle.txHeader.FDFormat 			= FDCAN_CLASSIC_CAN			        ; //@BACK: Classic or FD format ?
	protocol.obj.fdHandle.txHeader.TxEventFifoControl 	= FDCAN_NO_TX_EVENTS		        ;
	protocol.obj.fdHandle.txHeader.MessageMarker 		= 0							        ;

	
	if( HAL_FDCAN_AddMessageToTxFifoQ (&protocol.obj.fdHandle.hfdcanHandle  ,
									   &protocol.obj.fdHandle.txHeader		,
									    protocol.obj.fdHandle.txData			) != HAL_OK)
	{
		 	return EEM_ERROR;
	}
#else

#if defined(SPI2CAN_Protocol)

	uCAN_MSG txPacked;
	txPacked.frame.idType = dEXTENDED_CAN_MSG_ID_2_0B ;
	txPacked.frame.dlc	  = EEM_MAX_SIZE;
	txPacked.frame.id	  = param->EXTENDED_ID.identifier;

	memcpy(&txPacked.frame.data0 , &param->DATA[0] , EEM_MAX_SIZE );

	CANSPI_Transmit(&txPacked);

#else

#endif

#endif
	
	



	return result;
}


/*******************************************************************************
	 @func    :	
	 @param   : 
	 @return  : 
	 @date	  : 
	 @INFO		:	
********************************************************************************/	
EEM_ERR_T 		EEM_RX( EEM_CAN_Packet_st* 	param 	  ,
#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol))
						CAN_RxHeaderTypeDef   rxHeader	  ,
#elif (defined(STM32H750xx) && defined(FDCAN_Protocol))
						FDCAN_RxHeaderTypeDef rxHeader    ,
#else
#if defined(SPI2CAN_Protocol)
						uCAN_MSG*			rxPacked      ,
#endif
#endif
						EEM_U8*				rxData	  	   )
{
	EEM_ERR_T result = EEM_EOK;

#if defined(STM32F446xx)



#elif defined(STM32H750xx)

	memcpy( &param->DATA[0] , &rxData[0] , EEM_MAX_SIZE );
	param->EXTENDED_ID.identifier = rxHeader.Identifier;

#else

#if defined(SPI2CAN_Protocol)

	//@That library used polling method
	if( CANSPI_Receive(rxPacked) )
	{
		memcpy(&param->DATA[0] , &rxPacked->frame.data0 , EEM_MAX_SIZE  );
		param->EXTENDED_ID.identifier = rxPacked->frame.id ;
	}
	else
	{
		return EEM_ERROR;
	}

#else

#endif

#endif

	/* Received Data Handled Push Ring Buffer */
	EEM_PUSH( &protocol.obj.ringBuffer , param);

	return result;
}


/*******************************************************************************
	 @func    :	
	 @param   : 
	 @return  : 
	 @date	  : 
	 @INFO		:	
********************************************************************************/
EEM_ERR_T 	EEM_PERIODIC( EEM_CAN_Packet_st*  param )
{
	EEM_ERR_T 	   result 	= EEM_EOK;

#if (defined(STM32F446xx) || defined(STM32F407xx) && defined(BXCAN_Protocol)) || (defined(STM32H750xx) && defined(FDCAN_Protocol))
	//bxCAN ve FDCAN IRQ Handler'da recv yapmaktadir.
#else

	uCAN_MSG rxHandle = {0};

	result = EEM_RX(param, &rxHandle, NULL);
	if( result != EEM_EOK ) return result;

#endif

	while( !EEM_IS_EMPTY(&protocol.obj.ringBuffer) )
	{
	   EEM_POP(&protocol.obj.ringBuffer, param);

#ifdef DEBUG_EN
	    printf("ID : %X" , param->EXTENDED_ID );
		printf("%02 %02 %02 %02 %02 %02 %02 %02 \n" , param->DATA[0] ,
					                                  param->DATA[1] ,
		                                              param->DATA[2] ,
		                                              param->DATA[3] ,
		                                              param->DATA[4] ,
		                                              param->DATA[5] ,
		                                              param->DATA[6] ,
		                                              param->DATA[7] ,
		                                              param->DATA[0] );
#endif
	}

	
	switch( param->EXTENDED_ID.Pages.messageID )
	{
//#if defined(BCM_MODULE)

	case MESSAGE01 :

		HVAC_MSG.Message01.SPN.HVAC_led01_u1 = ( param->DATA[0] & 0x01 );
		HVAC_MSG.Message01.SPN.HVAC_led02_u1 = (( param->DATA[0] & 0x02 ) >> 1 );
		HVAC_MSG.Message01.SPN.HVAC_led03_u1 = (( param->DATA[0] & 0x04 ) >> 2 );
		HVAC_MSG.Message01.SPN.HVAC_led04_u1 = (( param->DATA[0] & 0x08 ) >> 3 );
		HVAC_MSG.Message01.SPN.HVAC_led05_u1 = (( param->DATA[0] & 0x10 ) >> 4 );
		HVAC_MSG.Message01.SPN.HVAC_led06_u1 = (( param->DATA[0] & 0x20 ) >> 5 );
		HVAC_MSG.Message01.SPN.HVAC_led07_u1 = (( param->DATA[0] & 0x40 ) >> 6 );
		HVAC_MSG.Message01.SPN.HVAC_led08_u1 = (( param->DATA[0] & 0x80 ) >> 7 );
		HVAC_MSG.Message01.SPN.HVAC_led09_u1 = ( param->DATA[1] & 0x01 );
		HVAC_MSG.Message01.SPN.HVAC_led10_u1 = (( param->DATA[1] & 0x02 ) >> 1 );
		HVAC_MSG.Message01.SPN.HVAC_led11_u1 = (( param->DATA[1] & 0x04 ) >> 2 );
		HVAC_MSG.Message01.SPN.HVAC_led12_u1 = (( param->DATA[1] & 0x08 ) >> 3 );

		HVAC_MSG.Message01.SPN.HVAC_pressureVal_u8 			= (EEM_U8)( (EEM_U8)( (param->DATA[1] & 0xF0) >> 4 )  |
												   	    				(EEM_U8)( (param->DATA[2] & 0x0F) << 4 )  );

		HVAC_MSG.Message01.SPN.HVAC_indoorTempVal_u8 		= (EEM_U8)( (EEM_U8)( (param->DATA[2] & 0xF0) >> 4 ) |
													 					(EEM_U8)( (param->DATA[3] & 0x0F) << 4 ) );

		HVAC_MSG.Message01.SPN.HVAC_indoorHumidVal_u8 		= (EEM_U8)( (EEM_U8)( (param->DATA[3] & 0xF0) >> 4 ) |
				 	 	 	 	 	 	 	 	 	 	  				(EEM_U8)( (param->DATA[4] & 0x0F) << 4 ) );

		HVAC_MSG.Message01.SPN.HVAC_rtcCalib_u1 			= (EEM_U8)( ( param->DATA[4] & 0x10) >> 4 );
		HVAC_MSG.Message01.SPN.HVAC_rtcNewSecond_u8 		= (EEM_U8)( ( param->DATA[4] & 0x20) >> 5 );
		HVAC_MSG.Message01.SPN.HVAC_rtcNewMinutes_u8 		= (EEM_U8)( ( param->DATA[4] & 0x40) >> 6 );
		HVAC_MSG.Message01.SPN.HVAC_rtcNewHour_u8 			= (EEM_U8)( ( param->DATA[4] & 0x80) >> 7 );
		HVAC_MSG.Message01.SPN.HVAC_rtcNewDay_u8 			= (EEM_U8)(   param->DATA[5] & 0x01 );
		HVAC_MSG.Message01.SPN.HVAC_rtcNewMonth_u8 			= (EEM_U8)( ( param->DATA[5] & 0x02 ) >> 1 );


	break;

	case MESSAGE02 :


	break;

	case MESSAGE07 :

	break;

	case MESSAGE08 :

	break;

	case MESSAGE09 :

	break;

	case MESSAGE10 :

	break;

	case MESSAGE18 :

	break;


	case MESSAGE19 :

	break;


	case MESSAGE24 :

	break;

	case MESSAGE20 :

	break;

	case MESSAGE21 :

	break;

	case MESSAGE22 :

	break;

	case MESSAGE23 :

	break;

	case MESSAGE25 :

	break;


	}

	
	return result;
}


/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
EEM_BOOL_T	EEM_IS_EMPTY( const EEM_RING_Buffer_st* buffer )
{
	 return (buffer->head == buffer->tail && !buffer->full);
}

/*******************************************************************************
	 @func    :
	 @param   :
	 @return  :
	 @date	  :
	 @INFO		:
********************************************************************************/
EEM_BOOL_T	EEM_IS_FULL( const EEM_RING_Buffer_st* buffer )
{
	  return buffer->full;
}







