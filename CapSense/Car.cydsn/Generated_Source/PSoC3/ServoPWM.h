/*******************************************************************************
* File Name: ServoPWM.h  
* Version 2.20
*
* Description:
*  Contains the prototypes and constants for the functions available to the 
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

#if !defined(CY_PWM_ServoPWM_H)
#define CY_PWM_ServoPWM_H


/***************************************
* Conditional Compilation Parameters
***************************************/
#define ServoPWM_Resolution 16u
#define ServoPWM_UsingFixedFunction 0u
#define ServoPWM_DeadBandMode 0u
#define ServoPWM_KillModeMinTime 0u
#define ServoPWM_KillMode 0u
#define ServoPWM_PWMMode 0u
#define ServoPWM_PWMModeIsCenterAligned 0u
#define ServoPWM_DeadBandUsed 0u
#define ServoPWM_DeadBand2_4 0u
#if !defined(ServoPWM_PWMUDB_sSTSReg_stsreg__REMOVED)
    #define ServoPWM_UseStatus 1u
#else
    #define ServoPWM_UseStatus 0u
#endif /* !defined(ServoPWM_PWMUDB_sSTSReg_stsreg__REMOVED) */
#if !defined(ServoPWM_PWMUDB_sCTRLReg_ctrlreg__REMOVED)
    #define ServoPWM_UseControl 1u
#else
    #define ServoPWM_UseControl 0u
#endif /* !defined(ServoPWM_PWMUDB_sCTRLReg_ctrlreg__REMOVED) */
#define ServoPWM_UseOneCompareMode 1u
#define ServoPWM_MinimumKillTime 1u
#define ServoPWM_EnableMode 0u

#define ServoPWM_CompareMode1SW 0u
#define ServoPWM_CompareMode2SW 0u

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define ServoPWM__B_PWM__DISABLED 0
#define ServoPWM__B_PWM__ASYNCHRONOUS 1
#define ServoPWM__B_PWM__SINGLECYCLE 2
#define ServoPWM__B_PWM__LATCHED 3
#define ServoPWM__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define ServoPWM__B_PWM__DBMDISABLED 0
#define ServoPWM__B_PWM__DBM_2_4_CLOCKS 1
#define ServoPWM__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define ServoPWM__B_PWM__ONE_OUTPUT 0
#define ServoPWM__B_PWM__TWO_OUTPUTS 1
#define ServoPWM__B_PWM__DUAL_EDGE 2
#define ServoPWM__B_PWM__CENTER_ALIGN 3
#define ServoPWM__B_PWM__DITHER 5
#define ServoPWM__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define ServoPWM__B_PWM__LESS_THAN 1
#define ServoPWM__B_PWM__LESS_THAN_OR_EQUAL 2
#define ServoPWM__B_PWM__GREATER_THAN 3
#define ServoPWM__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define ServoPWM__B_PWM__EQUAL 0
#define ServoPWM__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct ServoPWM_backupStruct
{
    
    uint8 PWMEnableState;
       
    #if(!ServoPWM_UsingFixedFunction)
        #if (CY_PSOC5A)
            uint16 PWMUdb;               /* PWM Current Counter value  */
            uint16 PWMPeriod;            /* PWM Current Period value   */
            #if (ServoPWM_UseStatus)
                uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
            #endif /* (ServoPWM_UseStatus) */
            #if(ServoPWM_UseOneCompareMode)
                uint16 PWMCompareValue;     /* PWM Current Compare value */
            #else
                uint16 PWMCompareValue1;     /* PWM Current Compare value1 */
                uint16 PWMCompareValue2;     /* PWM Current Compare value2 */
            #endif /* (ServoPWM_UseOneCompareMode) */
            
            /* Backup for Deadband parameters */
            #if(ServoPWM_DeadBandMode == ServoPWM__B_PWM__DBM_256_CLOCKS || \
                ServoPWM_DeadBandMode == ServoPWM__B_PWM__DBM_2_4_CLOCKS)
                uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
            #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
            /* Backup Kill Mode Counter*/
            #if(ServoPWM_KillModeMinTime)
                uint8 PWMKillCounterPeriod; /* Kill Mode period value */
            #endif /* (ServoPWM_KillModeMinTime) */
            
        #endif /* (CY_PSOC5A) */
        
        #if (CY_PSOC3 || CY_PSOC5LP)
            uint16 PWMUdb;               /* PWM Current Counter value  */
            #if(!ServoPWM_PWMModeIsCenterAligned)
                uint16 PWMPeriod;
            #endif /* (!ServoPWM_PWMModeIsCenterAligned) */
            #if (ServoPWM_UseStatus)
                uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
            #endif /* (ServoPWM_UseStatus) */
            
            /* Backup for Deadband parameters */
            #if(ServoPWM_DeadBandMode == ServoPWM__B_PWM__DBM_256_CLOCKS || \
                ServoPWM_DeadBandMode == ServoPWM__B_PWM__DBM_2_4_CLOCKS)
                uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
            #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
            /* Backup Kill Mode Counter*/
            #if(ServoPWM_KillModeMinTime)
                uint8 PWMKillCounterPeriod; /* Kill Mode period value */
            #endif /* (ServoPWM_KillModeMinTime) */
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
        
        /* Backup control register */
        #if(ServoPWM_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (ServoPWM_UseControl) */
        
    #endif /* (!ServoPWM_UsingFixedFunction) */
   
}ServoPWM_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/
 
void    ServoPWM_Start(void) ;
void    ServoPWM_Stop(void) ;
#if (ServoPWM_UseStatus || ServoPWM_UsingFixedFunction)
    #define ServoPWM_SetInterruptMode(interruptMode) CY_SET_REG8(ServoPWM_STATUS_MASK_PTR, interruptMode)
    #define ServoPWM_ReadStatusRegister() CY_GET_REG8(ServoPWM_STATUS_PTR)
#endif /* (ServoPWM_UseStatus || ServoPWM_UsingFixedFunction) */
#define ServoPWM_GetInterruptSource() ServoPWM_ReadStatusRegister()
#if (ServoPWM_UseControl)
    #define ServoPWM_ReadControlRegister() CY_GET_REG8(ServoPWM_CONTROL_PTR) 
    #define ServoPWM_WriteControlRegister(control) CY_SET_REG8(ServoPWM_CONTROL_PTR, control)
#endif /* (ServoPWM_UseControl) */
#if (ServoPWM_UseOneCompareMode)
   #if (ServoPWM_CompareMode1SW)
       void    ServoPWM_SetCompareMode(uint8 comparemode) ;
   #endif /* (ServoPWM_CompareMode1SW) */
#else
    #if (ServoPWM_CompareMode1SW)
        void    ServoPWM_SetCompareMode1(uint8 comparemode) \
                                                ;
    #endif /* (ServoPWM_CompareMode1SW) */
    #if (ServoPWM_CompareMode2SW)
        void    ServoPWM_SetCompareMode2(uint8 comparemode) \
                                                ;
    #endif /* (ServoPWM_CompareMode2SW) */
#endif /* (ServoPWM_UseOneCompareMode) */

#if (!ServoPWM_UsingFixedFunction)
    uint16   ServoPWM_ReadCounter(void) ;
    #define ServoPWM_ReadCapture() CY_GET_REG16(ServoPWM_CAPTURE_LSB_PTR)
    #if (ServoPWM_UseStatus)
        void ServoPWM_ClearFIFO(void) ;
    #endif /* (ServoPWM_UseStatus) */

    void    ServoPWM_WriteCounter(uint16 counter) \
                                       ;
#endif /* (!ServoPWM_UsingFixedFunction) */

void    ServoPWM_WritePeriod(uint16 period) \
                                     ;
#define ServoPWM_ReadPeriod() CY_GET_REG16(ServoPWM_PERIOD_LSB_PTR) 
#if (ServoPWM_UseOneCompareMode)
    void    ServoPWM_WriteCompare(uint16 compare) \
                                          ;
    #define ServoPWM_ReadCompare() CY_GET_REG16(ServoPWM_COMPARE1_LSB_PTR) 
#else
    void    ServoPWM_WriteCompare1(uint16 compare) \
                                           ;
    #define ServoPWM_ReadCompare1() CY_GET_REG16(ServoPWM_COMPARE1_LSB_PTR) 
    void    ServoPWM_WriteCompare2(uint16 compare) \
                                           ;
    #define ServoPWM_ReadCompare2() CY_GET_REG16(ServoPWM_COMPARE2_LSB_PTR) 
#endif /* (ServoPWM_UseOneCompareMode) */


#if (ServoPWM_DeadBandUsed)
    void    ServoPWM_WriteDeadTime(uint8 deadtime) ;
    uint8   ServoPWM_ReadDeadTime(void) ;
#endif /* (ServoPWM_DeadBandUsed) */

#if ( ServoPWM_KillModeMinTime)
    #define ServoPWM_WriteKillTime(killtime) CY_SET_REG8(ServoPWM_KILLMODEMINTIME_PTR, killtime) 
    #define ServoPWM_ReadKillTime() CY_GET_REG8(ServoPWM_KILLMODEMINTIME_PTR) 
#endif /* ( ServoPWM_KillModeMinTime) */

void ServoPWM_Init(void) ;
void ServoPWM_Enable(void) ;
void ServoPWM_Sleep(void) ;
void ServoPWM_Wakeup(void) ;
void ServoPWM_SaveConfig(void) ;
void ServoPWM_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define ServoPWM_INIT_PERIOD_VALUE        1000u
#define ServoPWM_INIT_COMPARE_VALUE1      150u
#define ServoPWM_INIT_COMPARE_VALUE2      0u
#define ServoPWM_INIT_INTERRUPTS_MODE     ((0u << ServoPWM_STATUS_TC_INT_EN_MASK_SHIFT) | \
                                                  (0 << ServoPWM_STATUS_CMP2_INT_EN_MASK_SHIFT) | \
                                                  (0 << ServoPWM_STATUS_CMP1_INT_EN_MASK_SHIFT ) | \
                                                  (0 << ServoPWM_STATUS_KILL_INT_EN_MASK_SHIFT ))
#define ServoPWM_DEFAULT_COMPARE2_MODE    (1u << ServoPWM_CTRL_CMPMODE2_SHIFT)
#define ServoPWM_DEFAULT_COMPARE1_MODE    (1u << ServoPWM_CTRL_CMPMODE1_SHIFT)
#define ServoPWM_INIT_DEAD_TIME           1u


/********************************
*         Registers
******************************** */

#if (ServoPWM_UsingFixedFunction)
   #define ServoPWM_PERIOD_LSB          (*(reg16 *) ServoPWM_PWMHW__PER0)
   #define ServoPWM_PERIOD_LSB_PTR      ( (reg16 *) ServoPWM_PWMHW__PER0)
   #define ServoPWM_COMPARE1_LSB        (*(reg16 *) ServoPWM_PWMHW__CNT_CMP0)
   #define ServoPWM_COMPARE1_LSB_PTR    ( (reg16 *) ServoPWM_PWMHW__CNT_CMP0)
   #define ServoPWM_COMPARE2_LSB        0x00u
   #define ServoPWM_COMPARE2_LSB_PTR    0x00u
   #define ServoPWM_COUNTER_LSB         (*(reg16 *) ServoPWM_PWMHW__CNT_CMP0)
   #define ServoPWM_COUNTER_LSB_PTR     ( (reg16 *) ServoPWM_PWMHW__CNT_CMP0)
   #define ServoPWM_CAPTURE_LSB         (*(reg16 *) ServoPWM_PWMHW__CAP0)
   #define ServoPWM_CAPTURE_LSB_PTR     ( (reg16 *) ServoPWM_PWMHW__CAP0)
   #define ServoPWM_RT1                 (*(reg8 *)  ServoPWM_PWMHW__RT1)
   #define ServoPWM_RT1_PTR             ( (reg8 *)  ServoPWM_PWMHW__RT1)
      
#else
   #if(ServoPWM_PWMModeIsCenterAligned)
       #define ServoPWM_PERIOD_LSB      (*(reg16 *) ServoPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define ServoPWM_PERIOD_LSB_PTR   ((reg16 *) ServoPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
   #else
       #define ServoPWM_PERIOD_LSB      (*(reg16 *) ServoPWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #define ServoPWM_PERIOD_LSB_PTR   ((reg16 *) ServoPWM_PWMUDB_sP16_pwmdp_u0__F0_REG)
   #endif /* (ServoPWM_PWMModeIsCenterAligned) */
   #define ServoPWM_COMPARE1_LSB    (*(reg16 *) ServoPWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
   #define ServoPWM_COMPARE1_LSB_PTR ((reg16 *) ServoPWM_PWMUDB_sP16_pwmdp_u0__D0_REG)
   #define ServoPWM_COMPARE2_LSB    (*(reg16 *) ServoPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
   #define ServoPWM_COMPARE2_LSB_PTR ((reg16 *) ServoPWM_PWMUDB_sP16_pwmdp_u0__D1_REG)
   #define ServoPWM_COUNTERCAP_LSB   *(reg16 *) ServoPWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define ServoPWM_COUNTERCAP_LSB_PTR ((reg16 *) ServoPWM_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define ServoPWM_COUNTER_LSB     (*(reg16 *) ServoPWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
   #define ServoPWM_COUNTER_LSB_PTR  ((reg16 *) ServoPWM_PWMUDB_sP16_pwmdp_u0__A0_REG)
   #define ServoPWM_CAPTURE_LSB     (*(reg16 *) ServoPWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
   #define ServoPWM_CAPTURE_LSB_PTR  ((reg16 *) ServoPWM_PWMUDB_sP16_pwmdp_u0__F1_REG)
   #define ServoPWM_AUX_CONTROLDP0      (*(reg8 *) ServoPWM_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define ServoPWM_AUX_CONTROLDP0_PTR  ((reg8 *) ServoPWM_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #if (ServoPWM_Resolution == 16)
       #define ServoPWM_AUX_CONTROLDP1    (*(reg8 *) ServoPWM_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define ServoPWM_AUX_CONTROLDP1_PTR  ((reg8 *) ServoPWM_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
   #endif /* (ServoPWM_Resolution == 16) */
#endif /* (ServoPWM_UsingFixedFunction) */
   
#if(ServoPWM_KillModeMinTime )
    #define ServoPWM_KILLMODEMINTIME      (*(reg8 *) ServoPWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define ServoPWM_KILLMODEMINTIME_PTR   ((reg8 *) ServoPWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (ServoPWM_KillModeMinTime ) */

#if(ServoPWM_DeadBandMode == ServoPWM__B_PWM__DBM_256_CLOCKS)
    #define ServoPWM_DEADBAND_COUNT      (*(reg8 *) ServoPWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define ServoPWM_DEADBAND_COUNT_PTR  ((reg8 *) ServoPWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define ServoPWM_DEADBAND_LSB_PTR    ((reg8 *) ServoPWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define ServoPWM_DEADBAND_LSB        (*(reg8 *) ServoPWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(ServoPWM_DeadBandMode == ServoPWM__B_PWM__DBM_2_4_CLOCKS)
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (ServoPWM_UsingFixedFunction)
        #define ServoPWM_DEADBAND_COUNT        (*(reg8 *) ServoPWM_PWMHW__CFG0) 
        #define ServoPWM_DEADBAND_COUNT_PTR     ((reg8 *) ServoPWM_PWMHW__CFG0)
        #define ServoPWM_DEADBAND_COUNT_MASK    (0x03u << ServoPWM_DEADBAND_COUNT_SHIFT)
        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define ServoPWM_DEADBAND_COUNT_SHIFT   0x06u  
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define ServoPWM_DEADBAND_COUNT        (*(reg8 *) ServoPWM_PWMUDB_sDB3_SyncCtl_dbctrlreg__CONTROL_REG)
        #define ServoPWM_DEADBAND_COUNT_PTR     ((reg8 *) ServoPWM_PWMUDB_sDB3_SyncCtl_dbctrlreg__CONTROL_REG)
        #define ServoPWM_DEADBAND_COUNT_MASK    (0x03u << ServoPWM_DEADBAND_COUNT_SHIFT) 
        /* As defined by the verilog implementation of the Control Register */
        #define ServoPWM_DEADBAND_COUNT_SHIFT   0x00u 
    #endif /* (ServoPWM_UsingFixedFunction) */
#endif /* (ServoPWM_DeadBandMode == ServoPWM__B_PWM__DBM_256_CLOCKS) */



#if (ServoPWM_UsingFixedFunction)
    #define ServoPWM_STATUS                (*(reg8 *) ServoPWM_PWMHW__SR0)
    #define ServoPWM_STATUS_PTR            ((reg8 *) ServoPWM_PWMHW__SR0)
    #define ServoPWM_STATUS_MASK           (*(reg8 *) ServoPWM_PWMHW__SR0)
    #define ServoPWM_STATUS_MASK_PTR       ((reg8 *) ServoPWM_PWMHW__SR0)
    #define ServoPWM_CONTROL               (*(reg8 *) ServoPWM_PWMHW__CFG0)
    #define ServoPWM_CONTROL_PTR           ((reg8 *) ServoPWM_PWMHW__CFG0)    
    #define ServoPWM_CONTROL2              (*(reg8 *) ServoPWM_PWMHW__CFG1)    
    #if(CY_PSOC3 || CY_PSOC5LP)
        #define ServoPWM_CONTROL3              (*(reg8 *) ServoPWM_PWMHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define ServoPWM_GLOBAL_ENABLE         (*(reg8 *) ServoPWM_PWMHW__PM_ACT_CFG)
    #define ServoPWM_GLOBAL_ENABLE_PTR       ( (reg8 *) ServoPWM_PWMHW__PM_ACT_CFG)
    #define ServoPWM_GLOBAL_STBY_ENABLE      (*(reg8 *) ServoPWM_PWMHW__PM_STBY_CFG)
    #define ServoPWM_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) ServoPWM_PWMHW__PM_STBY_CFG)
  
  
    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define ServoPWM_BLOCK_EN_MASK          ServoPWM_PWMHW__PM_ACT_MSK
    #define ServoPWM_BLOCK_STBY_EN_MASK     ServoPWM_PWMHW__PM_STBY_MSK 
    /* Control Register definitions */
    #define ServoPWM_CTRL_ENABLE_SHIFT      0x00u
    
    #if(CY_PSOC5A)
        #define ServoPWM_CTRL_CMPMODE1_SHIFT    0x01u   /* As defined by Register map as MODE_CFG bits in CFG1*/
    #endif /* (CY_PSOC5A) */
    #if(CY_PSOC3 || CY_PSOC5LP)
        #define ServoPWM_CTRL_CMPMODE1_SHIFT    0x04u  /* As defined by Register map as MODE_CFG bits in CFG2*/
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    
    #define ServoPWM_CTRL_DEAD_TIME_SHIFT   0x06u   /* As defined by Register map */
    /* Fixed Function Block Only CFG register bit definitions */
    #define ServoPWM_CFG0_MODE              0x02u   /*  Set to compare mode */
    /* #define ServoPWM_CFG0_ENABLE            0x01u */  /* Enable the block to run */
    #define ServoPWM_CFG0_DB                0x20u   /* As defined by Register map as DB bit in CFG0 */

    /* Control Register Bit Masks */
    #define ServoPWM_CTRL_ENABLE            (0x01u << ServoPWM_CTRL_ENABLE_SHIFT)
    #define ServoPWM_CTRL_RESET             (0x01u << ServoPWM_CTRL_RESET_SHIFT)
    #define ServoPWM_CTRL_CMPMODE2_MASK     (0x07u << ServoPWM_CTRL_CMPMODE2_SHIFT)
    #if(CY_PSOC5A)
        #define ServoPWM_CTRL_CMPMODE1_MASK     (0x07u << ServoPWM_CTRL_CMPMODE1_SHIFT)
    #endif /* (CY_PSOC5A) */
    #if(CY_PSOC3 || CY_PSOC5LP)
        #define ServoPWM_CTRL_CMPMODE1_MASK     (0x07u << ServoPWM_CTRL_CMPMODE1_SHIFT)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    
    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define ServoPWM_CTRL2_IRQ_SEL_SHIFT    0x00u       
    #define ServoPWM_CTRL2_IRQ_SEL          (0x01u << ServoPWM_CTRL2_IRQ_SEL_SHIFT)  
    
    /* Status Register Bit Locations */
    #define ServoPWM_STATUS_TC_SHIFT            0x07u   /* As defined by Register map as TC in SR0 */
    #define ServoPWM_STATUS_CMP1_SHIFT          0x06u   /* As defined by the Register map as CAP_CMP in SR0 */
    
    /* Status Register Interrupt Enable Bit Locations */
    #define ServoPWM_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)    
    #define ServoPWM_STATUS_TC_INT_EN_MASK_SHIFT            (ServoPWM_STATUS_TC_SHIFT - 4)
    #define ServoPWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)  
    #define ServoPWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (ServoPWM_STATUS_CMP1_SHIFT - 4)
    
    /* Status Register Bit Masks */
    #define ServoPWM_STATUS_TC              (0x01u << ServoPWM_STATUS_TC_SHIFT)
    #define ServoPWM_STATUS_CMP1            (0x01u << ServoPWM_STATUS_CMP1_SHIFT)
    
    /* Status Register Interrupt Bit Masks*/
    #define ServoPWM_STATUS_TC_INT_EN_MASK              (ServoPWM_STATUS_TC >> 4)
    #define ServoPWM_STATUS_CMP1_INT_EN_MASK            (ServoPWM_STATUS_CMP1 >> 4)
    
    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP*/
    #define ServoPWM_RT1_SHIFT             0x04u
    #define ServoPWM_RT1_MASK              (0x03u << ServoPWM_RT1_SHIFT)/* Sync TC and CMP bit masks */
    #define ServoPWM_SYNC                  (0x03u << ServoPWM_RT1_SHIFT)
    #define ServoPWM_SYNCDSI_SHIFT         0x00u
    #define ServoPWM_SYNCDSI_MASK          (0x0Fu << ServoPWM_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    #define ServoPWM_SYNCDSI_EN            (0x0Fu << ServoPWM_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    

#else
    #define ServoPWM_STATUS                (*(reg8 *) ServoPWM_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define ServoPWM_STATUS_PTR            ((reg8 *) ServoPWM_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define ServoPWM_STATUS_MASK           (*(reg8 *) ServoPWM_PWMUDB_sSTSReg_rstSts_stsreg__MASK_REG)
    #define ServoPWM_STATUS_MASK_PTR       ((reg8 *) ServoPWM_PWMUDB_sSTSReg_rstSts_stsreg__MASK_REG)
    #define ServoPWM_STATUS_AUX_CTRL       (*(reg8 *) ServoPWM_PWMUDB_sSTSReg_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define ServoPWM_CONTROL               (*(reg8 *) ServoPWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define ServoPWM_CONTROL_PTR           ((reg8 *) ServoPWM_PWMUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    
    
    /***********************************
    *          Constants
    ***********************************/

    /* Control Register definitions */
    #define ServoPWM_CTRL_ENABLE_SHIFT      0x07u
    #define ServoPWM_CTRL_RESET_SHIFT       0x06u
    #define ServoPWM_CTRL_CMPMODE2_SHIFT    0x03u
    #define ServoPWM_CTRL_CMPMODE1_SHIFT    0x00u
    #define ServoPWM_CTRL_DEAD_TIME_SHIFT   0x00u   /* No Shift Needed for UDB block */
    /* Control Register Bit Masks */
    #define ServoPWM_CTRL_ENABLE            (0x01u << ServoPWM_CTRL_ENABLE_SHIFT)
    #define ServoPWM_CTRL_RESET             (0x01u << ServoPWM_CTRL_RESET_SHIFT)
    #define ServoPWM_CTRL_CMPMODE2_MASK     (0x07u << ServoPWM_CTRL_CMPMODE2_SHIFT)
    #define ServoPWM_CTRL_CMPMODE1_MASK     (0x07u << ServoPWM_CTRL_CMPMODE1_SHIFT) 
    
    /* Status Register Bit Locations */
    #define ServoPWM_STATUS_KILL_SHIFT          0x05u
    #define ServoPWM_STATUS_FIFONEMPTY_SHIFT    0x04u
    #define ServoPWM_STATUS_FIFOFULL_SHIFT      0x03u  
    #define ServoPWM_STATUS_TC_SHIFT            0x02u
    #define ServoPWM_STATUS_CMP2_SHIFT          0x01u
    #define ServoPWM_STATUS_CMP1_SHIFT          0x00u
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define ServoPWM_STATUS_KILL_INT_EN_MASK_SHIFT          ServoPWM_STATUS_KILL_SHIFT          
    #define ServoPWM_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    ServoPWM_STATUS_FIFONEMPTY_SHIFT    
    #define ServoPWM_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      ServoPWM_STATUS_FIFOFULL_SHIFT        
    #define ServoPWM_STATUS_TC_INT_EN_MASK_SHIFT            ServoPWM_STATUS_TC_SHIFT            
    #define ServoPWM_STATUS_CMP2_INT_EN_MASK_SHIFT          ServoPWM_STATUS_CMP2_SHIFT          
    #define ServoPWM_STATUS_CMP1_INT_EN_MASK_SHIFT          ServoPWM_STATUS_CMP1_SHIFT   
    /* Status Register Bit Masks */
    #define ServoPWM_STATUS_KILL            (0x00u << ServoPWM_STATUS_KILL_SHIFT )
    #define ServoPWM_STATUS_FIFOFULL        (0x01u << ServoPWM_STATUS_FIFOFULL_SHIFT)
    #define ServoPWM_STATUS_FIFONEMPTY      (0x01u << ServoPWM_STATUS_FIFONEMPTY_SHIFT)
    #define ServoPWM_STATUS_TC              (0x01u << ServoPWM_STATUS_TC_SHIFT)
    #define ServoPWM_STATUS_CMP2            (0x01u << ServoPWM_STATUS_CMP2_SHIFT) 
    #define ServoPWM_STATUS_CMP1            (0x01u << ServoPWM_STATUS_CMP1_SHIFT)
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define ServoPWM_STATUS_KILL_INT_EN_MASK            ServoPWM_STATUS_KILL
    #define ServoPWM_STATUS_FIFOFULL_INT_EN_MASK        ServoPWM_STATUS_FIFOFULL
    #define ServoPWM_STATUS_FIFONEMPTY_INT_EN_MASK      ServoPWM_STATUS_FIFONEMPTY
    #define ServoPWM_STATUS_TC_INT_EN_MASK              ServoPWM_STATUS_TC
    #define ServoPWM_STATUS_CMP2_INT_EN_MASK            ServoPWM_STATUS_CMP2
    #define ServoPWM_STATUS_CMP1_INT_EN_MASK            ServoPWM_STATUS_CMP1
                                                          
    /* Datapath Auxillary Control Register definitions */
    #define ServoPWM_AUX_CTRL_FIFO0_CLR     0x01u
    #define ServoPWM_AUX_CTRL_FIFO1_CLR     0x02u
    #define ServoPWM_AUX_CTRL_FIFO0_LVL     0x04u
    #define ServoPWM_AUX_CTRL_FIFO1_LVL     0x08u
    #define ServoPWM_STATUS_ACTL_INT_EN_MASK  0x10u /* As defined for the ACTL Register */
#endif /* ServoPWM_UsingFixedFunction */

#endif  /* CY_PWM_ServoPWM_H */


/* [] END OF FILE */
