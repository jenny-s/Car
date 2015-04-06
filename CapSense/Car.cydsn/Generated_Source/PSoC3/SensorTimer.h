/*******************************************************************************
* File Name: SensorTimer.h
* Version 2.30
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v2_30_SensorTimer_H)
#define CY_Timer_v2_30_SensorTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define SensorTimer_Resolution                 32u
#define SensorTimer_UsingFixedFunction         0u
#define SensorTimer_UsingHWCaptureCounter      0u
#define SensorTimer_SoftwareCaptureMode        0u
#define SensorTimer_SoftwareTriggerMode        0u
#define SensorTimer_UsingHWEnable              0u
#define SensorTimer_EnableTriggerMode          0u
#define SensorTimer_InterruptOnCaptureCount    1u
#define SensorTimer_RunModeUsed                0u
#define SensorTimer_ControlRegRemoved          0u


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct SensorTimer_backupStruct
{
    uint8 TimerEnableState;
    #if(!SensorTimer_UsingFixedFunction)
        #if (CY_PSOC5A)
            uint32 TimerUdb;                 /* Timer internal counter value */
            uint32 TimerPeriod;              /* Timer Period value       */
            uint8 InterruptMaskValue;       /* Timer Compare Value */
            #if (SensorTimer_UsingHWCaptureCounter)
                uint32 TimerCaptureCounter;  /* Timer Capture Counter Value */
            #endif /* variable declaration for backing up Capture Counter value*/
        #endif /* variables for non retention registers in PSoC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            uint32 TimerUdb;
            uint8 InterruptMaskValue;
            #if (SensorTimer_UsingHWCaptureCounter)
                uint32 TimerCaptureCounter;
            #endif /* variable declarations for backing up non retention registers in PSoC3 or PSoC5LP */
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */

        #if (!SensorTimer_ControlRegRemoved)
        uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */
}SensorTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    SensorTimer_Start(void) ;
void    SensorTimer_Stop(void) ;

void    SensorTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   SensorTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define SensorTimer_GetInterruptSource() SensorTimer_ReadStatusRegister()

#if(!SensorTimer_ControlRegRemoved)
    uint8   SensorTimer_ReadControlRegister(void) ;
    void    SensorTimer_WriteControlRegister(uint8 control) \
        ;
#endif /* (!SensorTimer_ControlRegRemoved) */

uint32  SensorTimer_ReadPeriod(void) ;
void    SensorTimer_WritePeriod(uint32 period) \
    ;
uint32  SensorTimer_ReadCounter(void) ;
void    SensorTimer_WriteCounter(uint32 counter) \
    ;
uint32  SensorTimer_ReadCapture(void) ;
void    SensorTimer_SoftwareCapture(void) ;


#if(!SensorTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (SensorTimer_SoftwareCaptureMode)
        void    SensorTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!SensorTimer_UsingFixedFunction) */

    #if (SensorTimer_SoftwareTriggerMode)
        void    SensorTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (SensorTimer_SoftwareTriggerMode) */
    #if (SensorTimer_EnableTriggerMode)
        void    SensorTimer_EnableTrigger(void) ;
        void    SensorTimer_DisableTrigger(void) ;
    #endif /* (SensorTimer_EnableTriggerMode) */

    #if(SensorTimer_InterruptOnCaptureCount)
        #if(!SensorTimer_ControlRegRemoved)
            void    SensorTimer_SetInterruptCount(uint8 interruptCount) \
                ;
        #endif /* (!SensorTimer_ControlRegRemoved) */
    #endif /* (SensorTimer_InterruptOnCaptureCount) */

    #if (SensorTimer_UsingHWCaptureCounter)
        void    SensorTimer_SetCaptureCount(uint8 captureCount) \
            ;
        uint8   SensorTimer_ReadCaptureCount(void) ;
    #endif /* (SensorTimer_UsingHWCaptureCounter) */

    void SensorTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void SensorTimer_Init(void)          ;
void SensorTimer_Enable(void)        ;
void SensorTimer_SaveConfig(void)    ;
void SensorTimer_RestoreConfig(void) ;
void SensorTimer_Sleep(void)         ;
void SensorTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define SensorTimer__B_TIMER__CM_NONE 0
#define SensorTimer__B_TIMER__CM_RISINGEDGE 1
#define SensorTimer__B_TIMER__CM_FALLINGEDGE 2
#define SensorTimer__B_TIMER__CM_EITHEREDGE 3
#define SensorTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define SensorTimer__B_TIMER__TM_NONE 0x00u
#define SensorTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define SensorTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define SensorTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define SensorTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define SensorTimer_INIT_PERIOD             4294959999u
#define SensorTimer_INIT_CAPTURE_MODE       (1u << SensorTimer_CTRL_CAP_MODE_SHIFT)
#define SensorTimer_INIT_TRIGGER_MODE       (0u << SensorTimer_CTRL_TRIG_MODE_SHIFT)
#if (SensorTimer_UsingFixedFunction)
    #define SensorTimer_INIT_INTERRUPT_MODE ((0u << SensorTimer_STATUS_TC_INT_MASK_SHIFT) | \
                                                  (1 << SensorTimer_STATUS_CAPTURE_INT_MASK_SHIFT))
#else
    #define SensorTimer_INIT_INTERRUPT_MODE ((0u << SensorTimer_STATUS_TC_INT_MASK_SHIFT) | \
                                                 (1 << SensorTimer_STATUS_CAPTURE_INT_MASK_SHIFT) | \
                                                 (0 << SensorTimer_STATUS_FIFOFULL_INT_MASK_SHIFT))
#endif /* (SensorTimer_UsingFixedFunction) */
#define SensorTimer_INIT_CAPTURE_COUNT      (2u)
#define SensorTimer_INIT_INT_CAPTURE_COUNT  ((1u - 1) << SensorTimer_CTRL_INTCNT_SHIFT)


/***************************************
*           Registers
***************************************/

#if (SensorTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define SensorTimer_STATUS         (*(reg8 *) SensorTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define SensorTimer_STATUS_MASK    (*(reg8 *) SensorTimer_TimerHW__SR0 )
    #define SensorTimer_CONTROL        (*(reg8 *) SensorTimer_TimerHW__CFG0)
    #define SensorTimer_CONTROL2       (*(reg8 *) SensorTimer_TimerHW__CFG1)
    #define SensorTimer_CONTROL2_PTR   ( (reg8 *) SensorTimer_TimerHW__CFG1)
    #define SensorTimer_RT1            (*(reg8 *) SensorTimer_TimerHW__RT1)
    #define SensorTimer_RT1_PTR        ( (reg8 *) SensorTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define SensorTimer_CONTROL3       (*(reg8 *) SensorTimer_TimerHW__CFG2)
        #define SensorTimer_CONTROL3_PTR   ( (reg8 *) SensorTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define SensorTimer_GLOBAL_ENABLE  (*(reg8 *) SensorTimer_TimerHW__PM_ACT_CFG)
    #define SensorTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) SensorTimer_TimerHW__PM_STBY_CFG)

    #define SensorTimer_CAPTURE_LSB         (* (reg16 *) SensorTimer_TimerHW__CAP0 )
    #define SensorTimer_CAPTURE_LSB_PTR       ((reg16 *) SensorTimer_TimerHW__CAP0 )
    #define SensorTimer_PERIOD_LSB          (* (reg16 *) SensorTimer_TimerHW__PER0 )
    #define SensorTimer_PERIOD_LSB_PTR        ((reg16 *) SensorTimer_TimerHW__PER0 )
    #define SensorTimer_COUNTER_LSB         (* (reg16 *) SensorTimer_TimerHW__CNT_CMP0 )
    #define SensorTimer_COUNTER_LSB_PTR       ((reg16 *) SensorTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define SensorTimer_BLOCK_EN_MASK                     SensorTimer_TimerHW__PM_ACT_MSK
    #define SensorTimer_BLOCK_STBY_EN_MASK                SensorTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define SensorTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define SensorTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define SensorTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define SensorTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define SensorTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define SensorTimer_CTRL_ENABLE                        (0x01u << SensorTimer_CTRL_ENABLE_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define SensorTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define SensorTimer_CTRL2_IRQ_SEL                      (0x01u << SensorTimer_CTRL2_IRQ_SEL_SHIFT)

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define SensorTimer_CTRL_MODE_SHIFT                     0x01u
        #define SensorTimer_CTRL_MODE_MASK                     (0x07u << SensorTimer_CTRL_MODE_SHIFT)
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define SensorTimer_CTRL_RCOD_SHIFT        0x02u
        #define SensorTimer_CTRL_ENBL_SHIFT        0x00u
        #define SensorTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define SensorTimer_CTRL_RCOD_MASK  (0x03u << SensorTimer_CTRL_RCOD_SHIFT) /* ROD and COD bit masks */
        #define SensorTimer_CTRL_ENBL_MASK  (0x80u << SensorTimer_CTRL_ENBL_SHIFT) /* HW_EN bit mask */
        #define SensorTimer_CTRL_MODE_MASK  (0x03u << SensorTimer_CTRL_MODE_SHIFT) /* Run mode bit mask */

        #define SensorTimer_CTRL_RCOD       (0x03u << SensorTimer_CTRL_RCOD_SHIFT)
        #define SensorTimer_CTRL_ENBL       (0x80u << SensorTimer_CTRL_ENBL_SHIFT)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define SensorTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define SensorTimer_RT1_MASK                        (0x03u << SensorTimer_RT1_SHIFT)
    #define SensorTimer_SYNC                            (0x03u << SensorTimer_RT1_SHIFT)
    #define SensorTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define SensorTimer_SYNCDSI_MASK                    (0x0Fu << SensorTimer_SYNCDSI_SHIFT)
    /* Sync all DSI inputs */
    #define SensorTimer_SYNCDSI_EN                      (0x0Fu << SensorTimer_SYNCDSI_SHIFT)

    #define SensorTimer_CTRL_MODE_PULSEWIDTH            (0x01u << SensorTimer_CTRL_MODE_SHIFT)
    #define SensorTimer_CTRL_MODE_PERIOD                (0x02u << SensorTimer_CTRL_MODE_SHIFT)
    #define SensorTimer_CTRL_MODE_CONTINUOUS            (0x00u << SensorTimer_CTRL_MODE_SHIFT)

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define SensorTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define SensorTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define SensorTimer_STATUS_TC_INT_MASK_SHIFT        (SensorTimer_STATUS_TC_SHIFT - 4)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define SensorTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (SensorTimer_STATUS_CAPTURE_SHIFT - 4)

    /* Status Register Bit Masks */
    #define SensorTimer_STATUS_TC                       (0x01u << SensorTimer_STATUS_TC_SHIFT)
    #define SensorTimer_STATUS_CAPTURE                  (0x01u << SensorTimer_STATUS_CAPTURE_SHIFT)
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define SensorTimer_STATUS_TC_INT_MASK              (0x01u << SensorTimer_STATUS_TC_INT_MASK_SHIFT)
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define SensorTimer_STATUS_CAPTURE_INT_MASK         (0x01u << SensorTimer_STATUS_CAPTURE_INT_MASK_SHIFT)

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define SensorTimer_STATUS              (* (reg8 *) SensorTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define SensorTimer_STATUS_MASK         (* (reg8 *) SensorTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define SensorTimer_STATUS_AUX_CTRL     (* (reg8 *) SensorTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define SensorTimer_CONTROL             (* (reg8 *) SensorTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )

    #define SensorTimer_CAPTURE_LSB         (* (reg32 *) SensorTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
    #define SensorTimer_CAPTURE_LSB_PTR       ((reg32 *) SensorTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
    #define SensorTimer_PERIOD_LSB          (* (reg32 *) SensorTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
    #define SensorTimer_PERIOD_LSB_PTR        ((reg32 *) SensorTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
    #define SensorTimer_COUNTER_LSB         (* (reg32 *) SensorTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
    #define SensorTimer_COUNTER_LSB_PTR       ((reg32 *) SensorTimer_TimerUDB_sT32_timerdp_u0__A0_REG )

    #if (SensorTimer_UsingHWCaptureCounter)
        #define SensorTimer_CAP_COUNT              (*(reg8 *) SensorTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define SensorTimer_CAP_COUNT_PTR          ( (reg8 *) SensorTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define SensorTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) SensorTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define SensorTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) SensorTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (SensorTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define SensorTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define SensorTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define SensorTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define SensorTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define SensorTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define SensorTimer_CTRL_INTCNT_MASK               (0x03u << SensorTimer_CTRL_INTCNT_SHIFT)
    #define SensorTimer_CTRL_TRIG_MODE_MASK            (0x03u << SensorTimer_CTRL_TRIG_MODE_SHIFT)
    #define SensorTimer_CTRL_TRIG_EN                   (0x01u << SensorTimer_CTRL_TRIG_EN_SHIFT)
    #define SensorTimer_CTRL_CAP_MODE_MASK             (0x03u << SensorTimer_CTRL_CAP_MODE_SHIFT)
    #define SensorTimer_CTRL_ENABLE                    (0x01u << SensorTimer_CTRL_ENABLE_SHIFT)

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define SensorTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define SensorTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define SensorTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define SensorTimer_STATUS_TC_INT_MASK_SHIFT       SensorTimer_STATUS_TC_SHIFT
    #define SensorTimer_STATUS_CAPTURE_INT_MASK_SHIFT  SensorTimer_STATUS_CAPTURE_SHIFT
    #define SensorTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define SensorTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define SensorTimer_STATUS_FIFOFULL_INT_MASK_SHIFT SensorTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define SensorTimer_STATUS_TC                      (0x01u << SensorTimer_STATUS_TC_SHIFT)
    /* Sticky Capture Event Bit-Mask */
    #define SensorTimer_STATUS_CAPTURE                 (0x01u << SensorTimer_STATUS_CAPTURE_SHIFT)
    /* Interrupt Enable Bit-Mask */
    #define SensorTimer_STATUS_TC_INT_MASK             (0x01u << SensorTimer_STATUS_TC_SHIFT)
    /* Interrupt Enable Bit-Mask */
    #define SensorTimer_STATUS_CAPTURE_INT_MASK        (0x01u << SensorTimer_STATUS_CAPTURE_SHIFT)
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define SensorTimer_STATUS_FIFOFULL                (0x01u << SensorTimer_STATUS_FIFOFULL_SHIFT)
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define SensorTimer_STATUS_FIFONEMP                (0x01u << SensorTimer_STATUS_FIFONEMP_SHIFT)
    /* Interrupt Enable Bit-Mask */
    #define SensorTimer_STATUS_FIFOFULL_INT_MASK       (0x01u << SensorTimer_STATUS_FIFOFULL_SHIFT)

    #define SensorTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define SensorTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define SensorTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define SensorTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define SensorTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define SensorTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_SensorTimer_H */


/* [] END OF FILE */
