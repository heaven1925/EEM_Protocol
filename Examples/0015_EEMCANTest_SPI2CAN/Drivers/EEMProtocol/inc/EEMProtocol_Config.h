/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    EEMProtocol_Config.h
  * @author	 Atakan ERTEKiN
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil CAN Stack
********************************************************************************/

#ifndef __EEMPROCOTOL_CONFIG_H__
#define	__EEMPROCOTOL_CONFIG_H__

/********************************************************************************/

#include "EEMProtocol.h"

/*
* All protocol numarator has to define here!
* uncomment #undef macro depend to ecu or hw
*/

/*
 * Body Control module EEM_PERIODIC protocol macro
*/
#ifndef 	BCM_MODULE
#define		BCM_MODULE
//#undef		BCM_MODULE
#endif
/* Node Addr = 0x11 */
#define		BCM_NODE			0x11UL

/*
 * Heating and Ventilation controller EEM_PERIODIC protocol macro
*/
#ifndef 	HVAC_MODULE
#define		HVAC_MODULE
#undef		HVAC_MODULE
#endif
/* Node Addr = 0x22 */
#define		HVAC_NODE			0x22UL

/*
 * Simple Computer EEM_PERIODIC protocol macro
*/
#ifndef 	SCB_MODULE
#define		SCB_MODULE
#undef		SCB_MODULE
#endif
/* Node Addr = 0x33 */
#define		SCB_NODE			0x33UL

/*
 * Battery management system EEM_PERIODIC protocol macro
*/
#ifndef		BMS_MODULE
#define		BMS_MODULE
#undef		BMS_MODULE
#endif
/* Node Addr = 0x44 */
#define		BMS_NODE			0x44UL

/*
 * Motor Driver - 1 EEM_PERIODIC protocol macro
*/
#ifndef		MS1_MODULE
#define		MS1_MODULE
#undef		MS1_MODULE
#endif
/* Node Addr = 0x55 */
#define		MS1_NODE			0x55UL

/*
 * Motor Driver - 2 EEM_PERIODIC protocol macro
*/
#ifndef		MS2_MODULE
#define		MS2_MODULE
#undef		MS2_MODULE
#endif
/* Node Addr = 0x66 */
#define		MS2_NODE			0x66UL

/*
 * Isolation Watching Device EEM_PERIODIC protocol macro
*/
#ifndef		ISO_MODULE
#define		ISO_MODULE
#undef		ISO_MODULE
#endif
/* Node Addr = 0x77 */
#define		ISO_NODE			0x77UL

/*
 * Telemetry Module EEM_PERIODIC protocol macro
*/
#ifndef		TLM_MODULE
#define		TLM_MODULE
#undef		TLM_MODULE
#endif
/* Node Addr = 0x88 */
#define		ISO_MODULE			0x88UL

/*
 * Built-In Charging unit EEM_PERIODIC protocol macro
*/
#ifndef		YSB_MODULE
#define		YSB_MODULE
#undef		YSB_MODULE
#endif
/* Node Addr = 0x88 */
#define		YSB_MODULE			0x99UL

/*
 * Message Specific ID's
 */
#define		MESSAGE01			0x01UL	/* HVAC -> BCM */
#define		MESSAGE02			0x02UL	/* HVAC -> BCM */
#define		MESSAGE03			0x03UL
#define		MESSAGE04			0x04UL
#define		MESSAGE05			0x05UL
#define		MESSAGE06			0x06UL
#define		MESSAGE07			0x07UL	/* MS1 -> BCM */
#define		MESSAGE08			0x08UL	/* MS1 -> BCM */
#define		MESSAGE09			0x09UL	/* MS2 -> BCM */
#define		MESSAGE10			0x10UL	/* MS2 -> BCM */
#define		MESSAGE11			0x11UL	/* ISO -> BCM */
#define		MESSAGE12			0x12UL	/* TLM -> BCM */
#define		MESSAGE13			0x13UL	/* YSB -> BCM */
#define		MESSAGE14			0x14UL
#define		MESSAGE15			0x15UL
#define		MESSAGE16			0x16UL	/* BMS -> BCM */
#define		MESSAGE17			0x17UL
#define		MESSAGE18			0x18UL	/* MS-1 -> BCM */
#define		MESSAGE19			0x19UL  /* MS-2 -> BCM */
#define		MESSAGE20			0x20UL	/* BCM -> MS-1 */
#define		MESSAGE21			0x21UL	/* BCM -> MS-1 */
#define		MESSAGE22			0x22UL	/* BCM -> MS-2 */
#define		MESSAGE23			0x23UL	/* BCM -> MS-2 */
#define		MESSAGE24			0x24UL	/* BCM -> BMS  */
#define		MESSAGE25			0x25UL	/* BCM -> YSB  */

/********************************************************************************/

#if defined( BCM_MODULE )
EEM_ERR_T EEM_FILTER_BCM( EEM_Protocol_obj_st* param );
#elif defined( HVAC_MODULE )
/* HVAC module has been written Cpp language in order to arduino framework */
#elif defined( SCB_MODULE )
/* Simple computer protocol has written pyhton language */
#elif defined( BMS_MODULE )
EEM_ERR_T EEM_FILTER_BMS( EEM_Protocol_obj_st* param );
#elif defined( MS1_MODULE )
EEM_ERR_T EEM_FILTER_MS1( EEM_Protocol_obj_st* param );
#elif defined( MS2_MODULE )
EEM_ERR_T EEM_FILTER_MS2( EEM_Protocol_obj_st* param );
#elif defined( ISO_MODULE )
EEM_ERR_T EEM_FILTER_ISO( EEM_Protocol_obj_st* param );
#elif defined( TLM_MODULE )
EEM_ERR_T EEM_FILTER_TLM( EEM_Protocol_obj_st* param );
#elif defined( YSB_MODULE )
EEM_ERR_T EEM_FILTER_YSB( EEM_Protocol_obj_st* param );
#endif



/********************************************************************************/

/*
 * Reserved Numarator
 * This numarator has to configurate u1 type !
 */
typedef enum
{
	NOT_RESERVED = 0,
	RESERVED	 = 1,
}EEMConfig_Reserved_et;

/*
 * Data Page Numarator
 * This numarator has to configurate u1 type !
 */
typedef enum
{
	DATAPAGE_0 = 0,
	DATAPAGE_1 = 1,
}EEMConfig_DataPage_et;


/*
 * Priortiy Numarator
 * This numarator has to configurate u3 type !
 */
typedef enum
{
	PRIORITY_000 = 0b00000000 ,
	PRIORITY_001 = 0b00000001 ,
	PRIORITY_010 = 0b00000010 ,
	PRIORITY_011 = 0b00000011 ,
	PRIORITY_100 = 0b00000100 ,
	PRIORITY_101 = 0b00000101 ,
	PRIORITY_110 = 0b00000110 ,
	PRIORITY_111 = 0b00000111 ,
}EEMConfig_Priority_et;

/*
* All protocol payload has to define here!
*/



typedef struct
{
	EEM_U32 Message01_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U8 HVAC_led01_u1           : 1 ; /* YAKS Donanımına bağlı araç içerisindeki led-01 durumu */
			EEM_U8 HVAC_led02_u1           : 1 ; /* YAKS Donanımına bağlı araç içerisindeki led-02 durumu */
			EEM_U8 HVAC_led03_u1           : 1 ; /* YAKS Donanımına bağlı araç içerisindeki led-03 durumu */
			EEM_U8 HVAC_led04_u1           : 1 ; /* YAKS Donanımına bağlı araç içerisindeki led-04 durumu */
			EEM_U8 HVAC_led05_u1           : 1 ; /* YAKS Donanımına bağlı araç içerisindeki led-05 durumu */
			EEM_U8 HVAC_led06_u1           : 1 ; /* YAKS Donanımına bağlı araç içerisindeki led-06 durumu */
			EEM_U8 HVAC_led07_u1           : 1 ; /* YAKS Donanımına bağlı araç içerisindeki led-07 durumu */
			EEM_U8 HVAC_led08_u1           : 1 ; /* YAKS Donanımına bağlı araç içerisindeki led-08 durumu */
			EEM_U8 HVAC_led09_u1           : 1 ; /* YAKS Donanımına bağlı araç içerisindeki led-09 durumu */
			EEM_U8 HVAC_led10_u1 	       : 1 ; /* YAKS Donanımına bağlı araç içerisindeki led-10 durumu */
			EEM_U8 HVAC_led11_u1 	       : 1 ; /* YAKS Donanımına bağlı araç içerisindeki led-11 durumu */
			EEM_U8 HVAC_fireVal_u4 	   	   : 4 ; /* Ateş Sensörünün analog  4bit degeri					  */
			EEM_U8 HVAC_seatPressure_u8    : 8 ; /* Koltuk Basınç sensörü analog 8bit değeri */
			EEM_U8 HVAC_rtcCalib_u1		   : 1 ; /* YAKS tarafından RTC kalibrasyon yapılacağı bilgisi */
			EEM_U8 HVAC_rtcNewSecond_u8	   : 8 ;	/* YAKS RTC Saniye bilgisi  */
			EEM_U8 HVAC_rtcNewMinutes_u8   : 8 ; /* YAKS RTC Dakika bilgisi	*/
			EEM_U8 HVAC_rtcNewHour_u8	   : 8 ; /* YAKS RTC Saat bilgisi 	*/
			EEM_U8 HVAC_rtcNewDay_u8	   : 8 ; /* YAKS RTC Saat bilgisi 	*/
			EEM_U8 HVAC_rtcNewMonth_u8	   : 8 ; /* YAKS RTC Ay bilgisi		*/
			EEM_U32:22; /* RFU */
		}SPN;
	}Message01;

	EEM_U32 Message02_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U8 HVAC_tempVal_u8            : 8 ; /* Araç Kontrol Görev Birimi ( AKS-YAKS-RPI) Sıcaklık analog 8bit değeri	*/
			EEM_U8 HVAC_humidityVal_u8		  : 8 ; /* Araç Kontrol Görev Birimi ( AKS-YAKS-RPI) Nem analog 8bit değeri					*/
			EEM_U8 HVAC_smokeVal_u4			  : 4 ; /* Duman Sensörünün analog  4bit degeri					*/
			EEM_U8 HVAC_windPressure1_u4      : 4 ; /* Sol havalandırma rüzgar basınc sensörünün analog  4bit değeri					*/	
			EEM_U8 HVAC_windPressure2_u4      : 4 ; /* Sağ havalandırma rüzgar basınc sensörünün analog 4bit değeri					*/			
			EEM_U8 HVAC_leftFrontWheel_xy_u8  : 8 ; /* Sol ön tekerleğin X-Y eksen pozisyonları yazılımsal diferansiyel geri beslemesi için					*/
			EEM_U8 HVAC_rightFrontWheel_xy_u8 : 8 ; /* Sağ ön tekerleğin X-Y eksen pozisyonları yazılımsal diferansiyel geri beslemesi için					*/
			EEM_U8 HVAC_status00_u1        	  : 1 ; /* YAKS'de denetlenen status biti 0 -> YAKS 'deki Sol ön teker açı sınırı durumunu tutar.					*/
			EEM_U8 HVAC_status01_u1           : 1 ; /* YAKS'de denetlenen status biti 1 -> YAKS 'deki Sağ ön teker açı sınırı durumunu tutar.					*/
			EEM_U8 HVAC_status02_u1           : 1 ; /* YAKS'de denetlenen status biti 2 -> YAKS 'deki .......... durumunu tutar.					*/
			EEM_U8 HVAC_status03_u1           : 1 ; /* YAKS'de denetlenen status biti 3 -> YAKS 'deki .......... durumunu tutar.					*/
			EEM_U8 HVAC_status04_u1           : 1 ; /* YAKS'de denetlenen status biti 4 -> YAKS 'deki .......... durumunu tutar.					*/
			EEM_U8 HVAC_status05_u1           : 1 ; /* YAKS'de denetlenen status biti 5 -> YAKS 'deki .......... durumunu tutar.					*/
			EEM_U8 HVAC_status06_u1           : 1 ; /* YAKS'de denetlenen status biti 6 -> YAKS 'deki .......... durumunu tutar.					*/
			EEM_U8 HVAC_status07_u1           : 1 ; /* YAKS'de denetlenen status biti 7 -> YAKS 'deki .......... durumunu tutar.					*/
			EEM_U8 HVAC_Hgear_cmd_u3	      : 3 ; /* H - Vites Durum bilgisi - 0,1,2,3,4,5,6 */
			EEM_U8 HVAC_Gear_cmd_u2	          : 2 ; /* Park - İleri- Geri Vites Durum Bilgisi							*/
			EEM_U8 HVAC_cmdbit05_u1	          : 1 ; /* YAKS'den AKS'ye gönderilen 5. komut -> ......... komutu	  	    */
			EEM_U8 HVAC_cmdbit06_u1	          : 1 ; /* YAKS'den AKS'ye gönderilen 6. komut -> ......... komutu	    	*/
			EEM_U8 HVAC_cmdbit07_u1	          : 1 ; /* YAKS'den AKS'ye gönderilen 7. komut -> ......... komutu					*/
			EEM_U8:4; /* RFU */
		}SPN;
	}Message02;
	
}HVAC_Module_st;	
	
typedef struct
{
	EEM_U32 Message04_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U8 BCM_recordCamera_u1   	: 1  ; /*  Kamera kaydını başlatacak biti tutar.			*/
			EEM_U8 BCM_stopCamera_u1	 	: 1	 ; /*  Kamera kaydını durduracak biti tutar.			*/
			EEM_U8 BCM_deleteRecord_u1   	: 1	 ; /*  Kamera kaydını iptal edecek biti tutar.			*/
			EEM_U8 BCM_sdCardErase_u1	 	: 1	 ; /*  Kamera kaydını sd karttan silecek biti tutar.	*/
			EEM_U8 BCM_sdCardSave_u1     	: 1	 ; /*  Kamera kaydını sd karta kaydedecek biti tutar.	*/
			EEM_U8 BCM_dashboardState_u1 	: 1	 ; /*  Dashboard aktif pasif-durumunu tutar. */
			EEM_U8 BCM_dashboardCmd01_u1 	: 1	 ; /*  BCM'den SCB'ye gönderilen 1. komut -> ......... komutu					*/
			EEM_U8 BCM_dashboardCmd02_u1 	: 1	 ; /*  BCM'den SCB'ye gönderilen 2. komut -> ......... komutu					*/
			EEM_U8 BCM_dashboardCmd03_u1 	: 1	 ; /*  BCM'den SCB'ye gönderilen 3. komut -> ......... komutu					*/
			EEM_U8 BCM_dashboardCmd04_u1 	: 1	 ; /*  BCM'den SCB'ye gönderilen 4. komut -> ......... komutu					*/
			EEM_U8 :1 ;          
			EEM_U8 BCM_ignitionState_u1	 	: 1	 ; /*  Kontağın açık/kapalı bilgisini tutar.			*/
			EEM_U8 :1 ;           
			EEM_U8 BCM_leftSignal_u1	 	: 1	 ; /*  Sol sinyalin açık/kapalı bilgisini tutar.					*/
			EEM_U8 BCM_rightSignal_u1	 	: 1	 ; /*  Sağ sinyalin açık/kapalı bilgisini tutar.					*/
			EEM_U8 BCM_frontLight_u1	 	: 1	 ; /*  Ön farların açık/kapalı bilgisini tutar.					*/
			EEM_U8 BCM_backLight_u1	 		: 1	 ; /*  Arka farların açık/kapalı bilgisini tutar.					*/
			EEM_U8 BCM_backSignal_u1	 	: 1	 ; /*  Dörtlü sinyallerin açık/kapalı bilgisini tutar.					*/
			EEM_U8 :1 ;            
			EEM_U8 BCM_steeringAngle_u8 	: 8	 ; /*  Direksiyonun açı bilgisini tutar.					*/
			EEM_U8 BCM_gasPedal_u8		 	: 8  ; /*  Gaz pedalından okunan değeri tutar.					 */
			EEM_U8 BCM_brakePedal_u8	 	: 8  ; /*  Fren pedalından okunan değeri tutar.					*/
			EEM_U16 BCM_diffSpeed_u16	 	: 16 ; /*  Aracın diferansiyel uygulanmış hız bilgisini tutar.					*/
			EEM_U8 BCM_charge_u8		 	: 8  ; /*  Kalan batarya bilgisini tutar.					*/
			EEM_U8 :1 ;          
			EEM_U8 BCM_leftDirection_u1 	: 1  ; /*  Aracın sağa/sola gittiği bilgisini tutar.					*/
			EEM_U8 BCM_rightDirection_u1 	: 1  ; /*  Aracın ileri/geri gittiği bilgisini tutar.					*/

		}SPN;
	}Message04;
	
	EEM_U32 Message05_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U16 BCM_leftGyro_u16  	: 16  ; /*  */
			EEM_U16 BCM_leftAcc_u16  	: 16  ; /*  */
			EEM_U16 BCM_rightGyro_u16   : 16  ; /*  */
			EEM_U16 BCM_rightAcc_u16  	: 16  ; /*  */
		}SPN;
	}Message05;
	
	
	EEM_U32 Message08_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U32 BCM_MS1_Speed_u32     	: 32  ; /*  */
			EEM_U32 BCM_MS1_Direction_u32   : 32  ; /*  */
		}SPN;
	}Message08;
	
	EEM_U32 Message18_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U8 BCM_MS1_warningFlag01    : 1  ; /*  */
			EEM_U8 BCM_MS1_warningFlag02	: 1  ;
			EEM_U8 BCM_MS1_warningFlag03	: 1  ;
			EEM_U8 BCM_MS1_warningFlag04	: 1  ;
			EEM_U8 BCM_MS1_warningFlag05	: 1  ;
			EEM_U8 BCM_MS1_warningFlag06	: 1  ;
			EEM_U8 BCM_MS1_warningFlag07	: 1  ;
			EEM_U8 BCM_MS1_warningFlag08	: 1  ;
			EEM_U8 BCM_MS1_errorFlag01		: 1  ;
			EEM_U8 BCM_MS1_errorFlag02		: 1  ;
			EEM_U8 BCM_MS1_errorFlag03		: 1  ;
			EEM_U8 BCM_MS1_errorFlag04		: 1  ;
			EEM_U8 BCM_MS1_errorFlag05		: 1  ;
			EEM_U8 BCM_MS1_errorFlag06		: 1  ;
			EEM_U8 BCM_MS1_errorFlag07		: 1  ;
			EEM_U8 BCM_MS1_errorFlag08		: 1  ;
			EEM_U8 BCM_MS1_statusBit01		: 1  ;
			EEM_U8 BCM_MS1_statusBit02		: 1  ;
			EEM_U8 BCM_MS1_statusBit03		: 1  ;
			EEM_U8 BCM_MS1_statusBit04		: 1  ;
			EEM_U8 BCM_MS1_statusBit05		: 1  ;
			EEM_U8 BCM_MS1_statusBit06		: 1  ;
			EEM_U8 BCM_MS1_statusBit07		: 1  ;
			EEM_U8 BCM_MS1_statusBit08		: 1  ;
			EEM_U8 BCM_MS1_dummyByte01		: 8	 ;
			EEM_U8 BCM_MS1_dummyByte02		: 8	 ;
			EEM_U8 BCM_MS1_dummyByte03		: 8	 ;
			EEM_U8 BCM_MS1_dummyByte04		: 8	 ;
			EEM_U8 BCM_MS1_dummyByte05		: 8	 ;
		}SPN;
	}Message18;
	
	EEM_U32 Message10_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U32 BCM_MS2_Speed     	 : 32  ; /*  */
			EEM_U32 BCM_MS2_Direction   : 32  ; /*  */
		}SPN;
	}Message10;

	EEM_U32 Message19_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U8 BCM_MS2_warningFlag01    : 1  ; /*  */
			EEM_U8 BCM_MS2_warningFlag02	: 1  ;
			EEM_U8 BCM_MS2_warningFlag03	: 1  ;
			EEM_U8 BCM_MS2_warningFlag04	: 1  ;
			EEM_U8 BCM_MS2_warningFlag05	: 1  ;
			EEM_U8 BCM_MS2_warningFlag06	: 1  ;
			EEM_U8 BCM_MS2_warningFlag07	: 1  ;
			EEM_U8 BCM_MS2_warningFlag08	: 1  ;
			EEM_U8 BCM_MS2_errorFlag01		: 1  ;
			EEM_U8 BCM_MS2_errorFlag02		: 1  ;
			EEM_U8 BCM_MS2_errorFlag03		: 1  ;
			EEM_U8 BCM_MS2_errorFlag04		: 1  ;
			EEM_U8 BCM_MS2_errorFlag05		: 1  ;
			EEM_U8 BCM_MS2_errorFlag06		: 1  ;
			EEM_U8 BCM_MS2_errorFlag07		: 1  ;
			EEM_U8 BCM_MS2_errorFlag08		: 1  ;
			EEM_U8 BCM_MS2_statusBit01		: 1  ;
			EEM_U8 BCM_MS2_statusBit02		: 1  ;
			EEM_U8 BCM_MS2_statusBit03		: 1  ;
			EEM_U8 BCM_MS2_statusBit04		: 1  ;
			EEM_U8 BCM_MS2_statusBit05		: 1  ;
			EEM_U8 BCM_MS2_statusBit06		: 1  ;
			EEM_U8 BCM_MS2_statusBit07		: 1  ;
			EEM_U8 BCM_MS2_statusBit08		: 1  ;
			EEM_U8 BCM_MS2_dummyByte01		: 8	 ;
			EEM_U8 BCM_MS2_dummyByte02		: 8	 ;
			EEM_U8 BCM_MS2_dummyByte03		: 8	 ;
			EEM_U8 BCM_MS2_dummyByte04		: 8	 ;
			EEM_U8 BCM_MS2_dummyByte05		: 8	 ;
			}SPN;
	    }Message19;


}BCM_Module_st;


typedef struct
{
	union
	{
		EEM_U8 payload[8];
		struct
		{

		}SPN;
	}Message24;

}BMS_Module_st;


typedef struct
{
	EEM_U32 Message07_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U16 MS1_rpm           : 8  ; /*  */
			EEM_U32 MS1_voltage       : 32 ; /*  */
			EEM_U16 MS1_current       : 16 ; /*  */
			EEM_U16 MS1_temp          : 8  ; /*  */
		}SPN;
	}Message07; /* 0x07 */
	
	EEM_U32 Message20_ID;
	union{
		EEM_U8 payload[8];
		struct
		{
			EEM_U32 MS1_Speed     	 	 : 32  ;
			EEM_U8	MS1_Mode		 	 : 8   ;
			EEM_U8  MS1_SuddenBrake	 	 : 1   ;
			EEM_U8	MS1_otherflag02		 : 1   ;
			EEM_U8	MS1_otherflag03		 : 1   ;
			EEM_U8	MS1_otherflag04		 : 1   ;
			EEM_U8	MS1_otherflag05		 : 1   ;
			EEM_U8	MS1_otherflag06		 : 1   ;
			EEM_U8	MS1_otherflag07		 : 1   ;
			EEM_U8	MS1_otherflag08		 : 1   ;
			EEM_U16	MS1_dummy			 : 16  ;
		}SPN;
	}Message20;

	EEM_U32 Message21_ID;
	union{
		EEM_U8 payload[8];
		struct
		{
			EEM_U32 MS1_dummy01 : 32 ;
			EEM_U32 MS1_dummy02 : 32 ;
			EEM_U32 MS1_dummy03 : 32 ;
			EEM_U32 MS1_dummy04 : 32 ;
		}SPN;
	}Message21;

}MS1_Module_st;


typedef struct
{
	EEM_U32 Message09_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U16 MS2_rpm           : 8  ; /*  */
			EEM_U32 MS2_voltage       : 32 ; /*  */
			EEM_U16 MS2_current       : 16 ; /*  */
			EEM_U16 MS2_temp          : 8  ; /*  */
		}SPN;
	}Message09;
	
	EEM_U32 Message22_ID;
	union{
		EEM_U8 payload[8];
		struct
		{
			EEM_U32 MS2_Speed     	 	 : 32  ;
			EEM_U8	MS2_Mode		 	 : 8   ;
			EEM_U8  MS2_SuddenBrake	 	 : 1   ;
			EEM_U8	MS2_otherflag02		 : 1   ;
			EEM_U8	MS2_otherflag03		 : 1   ;
			EEM_U8	MS2_otherflag04		 : 1   ;
			EEM_U8	MS2_otherflag05		 : 1   ;
			EEM_U8	MS2_otherflag06		 : 1   ;
			EEM_U8	MS2_otherflag07		 : 1   ;
			EEM_U8	MS2_otherflag08		 : 1   ;
			EEM_U16	MS2_dummy			 : 16  ;
		}SPN;
	}Message22;

	EEM_U32 Message23_ID;
	union{
		EEM_U8 payload[8];
		struct
		{
			EEM_U32 MS2_dummy01 : 32 ;
			EEM_U32 MS2_dummy02 : 32 ;
		}SPN;
	}Message23;

}MS2_Module_st;


typedef struct
{
	//@LATER
}ISO_Module_st;


typedef struct
{
	//@LATER
}TLM_Module_st;


typedef struct
{
	//@LATER
}YSB_Module_st;


#endif /* __EEMPROCOTOL_CONFIG_H__ */
/***********************************END OF FILE********************************/

