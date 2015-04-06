/*******************************************************************************
* File Name: TapeTimer.h
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

#if !defined(CY_Timer_v2_30_TapeTimer_H)
#define CY_Timer_v2_30_TapeTimer_H

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

#define TapeTimer_Resolution                 32u
#define TapeTimer_UsingFixedFunction         0u
#define TapeTimer_UsingHWCaptureCounter      0u
#define TapeTimer_SoftwareCaptureMode        0u
#define TapeTimer_SoftwareTriggerMode        0u
#define TapeTimer_UsingHWEnable              1u
#define TapeTimer_EnableTriggerMode          0u
#define TapeTimer_InterruptOnCaptureCount    1u
#define TapeTimer_RunModeUsed                0u
#define TapeTimer_ControlRegRemoved          0u


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct TapeTimer_backupStruct
{
    uint8 TimerEnableState;
    #if(!TapeTimer_UsingFixedFunction)
        #if (CY_PSOC5A)
            uint32 TimerUdb;                 /* Timer internal counter value */
            uint32 TimerPeriod;              /* Timer Period value       */
            uint8 InterruptMaskValue;       /* Timer Compare Value */
            #if (TapeTimer_UsingHWCaptureCounter)
                uint32 TimerCaptureCounter;  /* Timer Capture Counter Value */
            #endif /* variable declaration for backing up Capture Counter value*/
        #endif /* variables for non retention registers in PSoC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            uint32 TimerUdb;
            uint8 InterruptMaskValue;
            #if (TapeTimer_UsingHWCaptureCounter)
                uint32 TimerCaptureCounter;
            #endif /* variable declarations for backing up non retention registers in PSoC3 or PSoC5LP */
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */

        #if (!TapeTimer_ControlRegRemoved)
        uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */
}TapeTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    TapeTimer_Start(void) ;
void    TapeTimer_Stop(void) ;

void    TapeTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   TapeTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define TapeTimer_GetInterruptSource() TapeTimer_ReadStatusRegister()

#if(!TapeTimer_ControlRegRemoved)
    uint8   TapeTimer_ReadControlRegister(void) ;
    void    TapeTimer_WriteControlRegister(uint8 control) \
        ;
#endif /* (!TapeTimer_ControlRegRemoved) */

uint32  TapeTimer_ReadPeriod(void) ;
void    TapeTimer_WritePeriod(uint32 period) \
    ;
uint32  TapeTimer_ReadCounter(void) ;
void    TapeTimer_WriteCounter(uint32 counter) \
    ;
uint32  TapeTimer_ReadCapture(void) ;
void    TapeTimer_SoftwareCapture(void) ;


#if(!TapeTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (TapeTimer_SoftwareCaptureMode)
        void    TapeTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!TapeTimer_UsingFixedFunction) */

    #if (TapeTimer_SoftwareTriggerMode)
        void    TapeTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (TapeTimer_SoftwareTriggerMode) */
    #if (TapeTimer_EnableTriggerMode)
        void    TapeTimer_EnableTrigger(void) ;
        void    TapeTimer_DisableTrigger(void) ;
    #endif /* (TapeTimer_EnableTriggerMode) */

    #if(TapeTimer_InterruptOnCaptureCount)
        #if(!TapeTimer_ControlRegRemoved)
            void    TapeTimer_SetInterruptCount(uint8 interruptCount) \
                ;
        #endif /* (!TapeTimer_ControlRegRemoved) */
    #endif /* (TapeTimer_InterruptOnCaptureCount) */

    #if (TapeTimer_UsingHWCaptureCounter)
        void    TapeTimer_SetCaptureCount(uint8 captureCount) \
            ;
        uint8   TapeTimer_ReadCaptureCount(void) ;
    #endif /* (TapeTimer_UsingHWCaptureCounter) */

    void TapeTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void TapeTimer_Init(void)          ;
void TapeTimer_Enable(void)        ;
void TapeTimer_SaveConfig(void)    ;
void TapeTimer_RestoreConfig(void) ;
void TapeTimer_Sleep(void)         ;
void TapeTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define TapeTimer__B_TIMER__CM_NONE 0
#define TapeTimer__B_TIMER__CM_RISINGEDGE 1
#define TapeTimer__B_TIMER__CM_FALLINGEDGE 2
#define TapeTimer__B_TIMER__CM_EITHEREDGE 3
#define TapeTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define TapeTimer__B_TIMER__TM_NONE 0x00u
#define TapeTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define TapeTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define TapeTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define TapeTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define TapeTimer_INIT_PERIOD             99999u
#define TapeTimer_INIT_CAPTURE_MODE       (3u << TapeTimer_CTRL_CAP_MODE_SHIFT)
#define TapeTimer_INIT_TRIGGER_MODE       (0u << TapeTimer_CTRL_TRIG_MODE_SHIFT)
#if (TapeTimer_UsingFixedFunction)
    #define TapeTimer_INIT_INTERRUPT_MODE ((0u << TapeTimer_STATUS_TC_INT_MASK_SHIFT) | \
                                                  (1 << TapeTimer_STATUS_CAPTURE_INT_MASK_SHIFT))
#else
    #define TapeTimer_INIT_INTERRUPT_MODE ((0u << TapeTimer_STATUS_TC_INT_MASK_SHIFT) | \
                                                 (1 << TapeTimer_STATUS_CAPTURE_INT_MASK_SHIFT) | \
                                                 (0 << TapeTimer_STATUS_FIFOFULL_INT_MASK_SHIFT))
#endif /* (TapeTimer_UsingFixedFunction) */
#define TapeTimer_INIT_CAPTURE_COUNT      (2u)
#define TapeTimer_INIT_INT_CAPTURE_COUNT  ((4u - 1) << TapeTimer_CTRL_INTCNT_SHIFT)


/***************************************
*           Registers
***************************************/

#if (TapeTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define TapeTimer_STATUS         (*(reg8 *) TapeTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define TapeTimer_STATUS_MASK    (*(reg8 *) TapeTimer_TimerHW__SR0 )
    #define TapeTimer_CONTROL        (*(reg8 *) TapeTimer_TimerHW__CFG0)
    #define TapeTimer_CONTROL2       (*(reg8 *) TapeTimer_TimerHW__CFG1)
    #define TapeTimer_CONTROL2_PTR   ( (reg8 *) TapeTimer_TimerHW__CFG1)
    #define TapeTimer_RT1            (*(reg8 *) TapeTimer_TimerHW__RT1)
    #define TapeTimer_RT1_PTR        ( (reg8 *) TapeTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define TapeTimer_CONTROL3       (*(reg8 *) TapeTimer_TimerHW__CFG2)
        #define TapeTimer_CONTROL3_PTR   ( (reg8 *) TapeTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define TapeTimer_GLOBAL_ENABLE  (*(reg8 *) TapeTimer_TimerHW__PM_ACT_CFG)
    #define TapeTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) TapeTimer_TimerHW__PM_STBY_CFG)

    #define TapeTimer_CAPTURE_LSB         (* (reg16 *) TapeTimer_TimerHW__CAP0 )
    #define TapeTimer_CAPTURE_LSB_PTR       ((reg16 *) TapeTimer_TimerHW__CAP0 )
    #define TapeTimer_PERIOD_LSB          (* (reg16 *) TapeTimer_TimerHW__PER0 )
    #define TapeTimer_PERIOD_LSB_PTR        ((reg16 *) TapeTimer_TimerHW__PER0 )
    #define TapeTimer_COUNTER_LSB         (* (reg16 *) TapeTimer_TimerHW__CNT_CMP0 )
    #define TapeTimer_COUNTER_LSB_PTR       ((reg16 *) TapeTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define TapeTimer_BLOCK_EN_MASK                     TapeTimer_TimerHW__PM_ACT_MSK
    #define TapeTimer_BLOCK_STBY_EN_MASK                TapeTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define TapeTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define TapeTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define TapeTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define TapeTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define TapeTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define TapeTimer_CTRL_ENABLE                        (0x01u << TapeTimer_CTRL_ENABLE_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define TapeTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define TapeTimer_CTRL2_IRQ_SEL                      (0x01u << TapeTimer_CTRL2_IRQ_SEL_SHIFT)

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define TapeTimer_CTRL_MODE_SHIFT                     0x01u
        #define TapeTimer_CTRL_MODE_MASK                     (0x07u << TapeTimer_CTRL_MODE_SHIFT)
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define TapeTimer_CTRL_RCOD_SHIFT        0x02u
        #define TapeTimer_CTRL_ENBL_SHIFT        0x00u
        #define TapeTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define TapeTimer_CTRL_RCOD_MASK  (0x03u << TapeTimer_CTRL_RCOD_SHIFT) /* ROD and COD bit masks */
        #define TapeTimer_CTRL_ENBL_MASK  (0x80u << TapeTimer_CTRL_ENBL_SHIFT) /* HW_EN bit mask */
        #define TapeTimer_CTRL_MODE_MASK  (0x03u << TapeTimer_CTRL_MODE_SHIFT) /* Run mode bit mask */

        #define TapeTimer_CTRL_RCOD       (0x03u << TapeTimer_CTRL_RCOD_SHIFT)
        #define TapeTimer_CTRL_ENBL       (0x80u << TapeTimer_CTRL_ENBL_SHIFT)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define TapeTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define TapeTimer_RT1_MASK                        (0x03u << TapeTimer_RT1_SHIFT)
    #define TapeTimer_SYNC                            (0x03u << TapeTimer_RT1_SHIFT)
    #define TapeTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define TapeTimer_SYNCDSI_MASK                    (0x0Fu << TapeTimer_SYNCDSI_SHIFT)
    /* Sync all DSI inputs */
    #define TapeTimer_SYNCDSI_EN                      (0x0Fu << TapeTimer_SYNCDSI_SHIFT)

    #define TapeTimer_CTRL_MODE_PULSEWIDTH            (0x01u << TapeTimer_CTRL_MODE_SHIFT)
    #define TapeTimer_CTRL_MODE_PERIOD                (0x02u << TapeTimer_CTRL_MODE_SHIFT)
    #define TapeTimer_CTRL_MODE_CONTINUOUS            (0x00u << TapeTimer_CTRL_MODE_SHIFT)

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TapeTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TapeTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TapeTimer_STATUS_TC_INT_MASK_SHIFT        (TapeTimer_STATUS_TC_SHIFT - 4)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TapeTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (TapeTimer_STATUS_CAPTURE_SHIFT - 4)

    /* Status Register Bit Masks */
    #define TapeTimer_STATUS_TC                       (0x01u << TapeTimer_STATUS_TC_SHIFT)
    #define TapeTimer_STATUS_CAPTURE                  (0x01u << TapeTimer_STATUS_CAPTURE_SHIFT)
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define TapeTimer_STATUS_TC_INT_MASK              (0x01u << TapeTimer_STATUS_TC_INT_MASK_SHIFT)
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define TapeTimer_STATUS_CAPTURE_INT_MASK         (0x01u << TapeTimer_STATUS_CAPTURE_INT_MASK_SHIFT)

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define TapeTimer_STATUS              (* (reg8 *) TapeTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define TapeTimer_STATUS_MASK         (* (reg8 *) TapeTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define TapeTimer_STATUS_AUX_CTRL     (* (reg8 *) TapeTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define TapeTimer_CONTROL             (* (reg8 *) TapeTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )

    #define TapeTimer_CAPTURE_LSB         (* (reg32 *) TapeTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
    #define TapeTimer_CAPTURE_LSB_PTR       ((reg32 *) TapeTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
    #define TapeTimer_PERIOD_LSB          (* (reg32 *) TapeTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
    #define TapeTimer_PERIOD_LSB_PTR        ((reg32 *) TapeTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
    #define TapeTimer_COUNTER_LSB         (* (reg32 *) TapeTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
    #define TapeTimer_COUNTER_LSB_PTR       ((reg32 *) TapeTimer_TimerUDB_sT32_timerdp_u0__A0_REG )

    #if (TapeTimer_UsingHWCaptureCounter)
        #define TapeTimer_CAP_COUNT              (*(reg8 *) TapeTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TapeTimer_CAP_COUNT_PTR          ( (reg8 *) TapeTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TapeTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) TapeTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define TapeTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) TapeTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (TapeTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define TapeTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define TapeTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define TapeTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define TapeTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define TapeTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define TapeTimer_CTRL_INTCNT_MASK               (0x03u << TapeTimer_CTRL_INTCNT_SHIFT)
    #define TapeTimer_CTRL_TRIG_MODE_MASK            (0x03u << TapeTimer_CTRL_TRIG_MODE_SHIFT)
    #define TapeTimer_CTRL_TRIG_EN                   (0x01u << TapeTimer_CTRL_TRIG_EN_SHIFT)
    #define TapeTimer_CTRL_CAP_MODE_MASK             (0x03u << TapeTimer_CTRL_CAP_MODE_SHIFT)
    #define TapeTimer_CTRL_ENABLE                    (0x01u << TapeTimer_CTRL_ENABLE_SHIFT)

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define TapeTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define TapeTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define TapeTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define TapeTimer_STATUS_TC_INT_MASK_SHIFT       TapeTimer_STATUS_TC_SHIFT
    #define TapeTimer_STATUS_CAPTURE_INT_MASK_SHIFT  TapeTimer_STATUS_CAPTURE_SHIFT
    #define TapeTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define TapeTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define TapeTimer_STATUS_FIFOFULL_INT_MASK_SHIFT TapeTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define TapeTimer_STATUS_TC                      (0x01u << TapeTimer_STATUS_TC_SHIFT)
    /* Sticky Capture Event Bit-Mask */
    #define TapeTimer_STATUS_CAPTURE                 (0x01u << TapeTimer_STATUS_CAPTURE_SHIFT)
    /* Interrupt Enable Bit-Mask */
    #define TapeTimer_STATUS_TC_INT_MASK             (0x01u << TapeTimer_STATUS_TC_SHIFT)
    /* Interrupt Enable Bit-Mask */
    #define TapeTimer_STATUS_CAPTURE_INT_MASK        (0x01u << TapeTimer_STATUS_CAPTURE_SHIFT)
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define TapeTimer_STATUS_FIFOFULL                (0x01u << TapeTimer_STATUS_FIFOFULL_SHIFT)
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define TapeTimer_STATUS_FIFONEMP                (0x01u << TapeTimer_STATUS_FIFONEMP_SHIFT)
    /* Interrupt Enable Bit-Mask */
    #define TapeTimer_STATUS_FIFOFULL_INT_MASK       (0x01u << TapeTimer_STATUS_FIFOFULL_SHIFT)

    #define TapeTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define TapeTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define TapeTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define TapeTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define TapeTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define TapeTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_TapeTimer_H */


/* [] END OF FILE */
