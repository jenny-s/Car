/*******************************************************************************
* File Name: NavTimer.h
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

#if !defined(CY_Timer_v2_30_NavTimer_H)
#define CY_Timer_v2_30_NavTimer_H

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

#define NavTimer_Resolution                 32u
#define NavTimer_UsingFixedFunction         0u
#define NavTimer_UsingHWCaptureCounter      0u
#define NavTimer_SoftwareCaptureMode        0u
#define NavTimer_SoftwareTriggerMode        0u
#define NavTimer_UsingHWEnable              0u
#define NavTimer_EnableTriggerMode          0u
#define NavTimer_InterruptOnCaptureCount    1u
#define NavTimer_RunModeUsed                0u
#define NavTimer_ControlRegRemoved          0u


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct NavTimer_backupStruct
{
    uint8 TimerEnableState;
    #if(!NavTimer_UsingFixedFunction)
        #if (CY_PSOC5A)
            uint32 TimerUdb;                 /* Timer internal counter value */
            uint32 TimerPeriod;              /* Timer Period value       */
            uint8 InterruptMaskValue;       /* Timer Compare Value */
            #if (NavTimer_UsingHWCaptureCounter)
                uint32 TimerCaptureCounter;  /* Timer Capture Counter Value */
            #endif /* variable declaration for backing up Capture Counter value*/
        #endif /* variables for non retention registers in PSoC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            uint32 TimerUdb;
            uint8 InterruptMaskValue;
            #if (NavTimer_UsingHWCaptureCounter)
                uint32 TimerCaptureCounter;
            #endif /* variable declarations for backing up non retention registers in PSoC3 or PSoC5LP */
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */

        #if (!NavTimer_ControlRegRemoved)
        uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */
}NavTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    NavTimer_Start(void) ;
void    NavTimer_Stop(void) ;

void    NavTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   NavTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define NavTimer_GetInterruptSource() NavTimer_ReadStatusRegister()

#if(!NavTimer_ControlRegRemoved)
    uint8   NavTimer_ReadControlRegister(void) ;
    void    NavTimer_WriteControlRegister(uint8 control) \
        ;
#endif /* (!NavTimer_ControlRegRemoved) */

uint32  NavTimer_ReadPeriod(void) ;
void    NavTimer_WritePeriod(uint32 period) \
    ;
uint32  NavTimer_ReadCounter(void) ;
void    NavTimer_WriteCounter(uint32 counter) \
    ;
uint32  NavTimer_ReadCapture(void) ;
void    NavTimer_SoftwareCapture(void) ;


#if(!NavTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (NavTimer_SoftwareCaptureMode)
        void    NavTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!NavTimer_UsingFixedFunction) */

    #if (NavTimer_SoftwareTriggerMode)
        void    NavTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (NavTimer_SoftwareTriggerMode) */
    #if (NavTimer_EnableTriggerMode)
        void    NavTimer_EnableTrigger(void) ;
        void    NavTimer_DisableTrigger(void) ;
    #endif /* (NavTimer_EnableTriggerMode) */

    #if(NavTimer_InterruptOnCaptureCount)
        #if(!NavTimer_ControlRegRemoved)
            void    NavTimer_SetInterruptCount(uint8 interruptCount) \
                ;
        #endif /* (!NavTimer_ControlRegRemoved) */
    #endif /* (NavTimer_InterruptOnCaptureCount) */

    #if (NavTimer_UsingHWCaptureCounter)
        void    NavTimer_SetCaptureCount(uint8 captureCount) \
            ;
        uint8   NavTimer_ReadCaptureCount(void) ;
    #endif /* (NavTimer_UsingHWCaptureCounter) */

    void NavTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void NavTimer_Init(void)          ;
void NavTimer_Enable(void)        ;
void NavTimer_SaveConfig(void)    ;
void NavTimer_RestoreConfig(void) ;
void NavTimer_Sleep(void)         ;
void NavTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define NavTimer__B_TIMER__CM_NONE 0
#define NavTimer__B_TIMER__CM_RISINGEDGE 1
#define NavTimer__B_TIMER__CM_FALLINGEDGE 2
#define NavTimer__B_TIMER__CM_EITHEREDGE 3
#define NavTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define NavTimer__B_TIMER__TM_NONE 0x00u
#define NavTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define NavTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define NavTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define NavTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define NavTimer_INIT_PERIOD             4294967295u
#define NavTimer_INIT_CAPTURE_MODE       (1u << NavTimer_CTRL_CAP_MODE_SHIFT)
#define NavTimer_INIT_TRIGGER_MODE       (0u << NavTimer_CTRL_TRIG_MODE_SHIFT)
#if (NavTimer_UsingFixedFunction)
    #define NavTimer_INIT_INTERRUPT_MODE ((0u << NavTimer_STATUS_TC_INT_MASK_SHIFT) | \
                                                  (1 << NavTimer_STATUS_CAPTURE_INT_MASK_SHIFT))
#else
    #define NavTimer_INIT_INTERRUPT_MODE ((0u << NavTimer_STATUS_TC_INT_MASK_SHIFT) | \
                                                 (1 << NavTimer_STATUS_CAPTURE_INT_MASK_SHIFT) | \
                                                 (0 << NavTimer_STATUS_FIFOFULL_INT_MASK_SHIFT))
#endif /* (NavTimer_UsingFixedFunction) */
#define NavTimer_INIT_CAPTURE_COUNT      (2u)
#define NavTimer_INIT_INT_CAPTURE_COUNT  ((1u - 1) << NavTimer_CTRL_INTCNT_SHIFT)


/***************************************
*           Registers
***************************************/

#if (NavTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define NavTimer_STATUS         (*(reg8 *) NavTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define NavTimer_STATUS_MASK    (*(reg8 *) NavTimer_TimerHW__SR0 )
    #define NavTimer_CONTROL        (*(reg8 *) NavTimer_TimerHW__CFG0)
    #define NavTimer_CONTROL2       (*(reg8 *) NavTimer_TimerHW__CFG1)
    #define NavTimer_CONTROL2_PTR   ( (reg8 *) NavTimer_TimerHW__CFG1)
    #define NavTimer_RT1            (*(reg8 *) NavTimer_TimerHW__RT1)
    #define NavTimer_RT1_PTR        ( (reg8 *) NavTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define NavTimer_CONTROL3       (*(reg8 *) NavTimer_TimerHW__CFG2)
        #define NavTimer_CONTROL3_PTR   ( (reg8 *) NavTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define NavTimer_GLOBAL_ENABLE  (*(reg8 *) NavTimer_TimerHW__PM_ACT_CFG)
    #define NavTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) NavTimer_TimerHW__PM_STBY_CFG)

    #define NavTimer_CAPTURE_LSB         (* (reg16 *) NavTimer_TimerHW__CAP0 )
    #define NavTimer_CAPTURE_LSB_PTR       ((reg16 *) NavTimer_TimerHW__CAP0 )
    #define NavTimer_PERIOD_LSB          (* (reg16 *) NavTimer_TimerHW__PER0 )
    #define NavTimer_PERIOD_LSB_PTR        ((reg16 *) NavTimer_TimerHW__PER0 )
    #define NavTimer_COUNTER_LSB         (* (reg16 *) NavTimer_TimerHW__CNT_CMP0 )
    #define NavTimer_COUNTER_LSB_PTR       ((reg16 *) NavTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define NavTimer_BLOCK_EN_MASK                     NavTimer_TimerHW__PM_ACT_MSK
    #define NavTimer_BLOCK_STBY_EN_MASK                NavTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define NavTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define NavTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define NavTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define NavTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define NavTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define NavTimer_CTRL_ENABLE                        (0x01u << NavTimer_CTRL_ENABLE_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define NavTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define NavTimer_CTRL2_IRQ_SEL                      (0x01u << NavTimer_CTRL2_IRQ_SEL_SHIFT)

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define NavTimer_CTRL_MODE_SHIFT                     0x01u
        #define NavTimer_CTRL_MODE_MASK                     (0x07u << NavTimer_CTRL_MODE_SHIFT)
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define NavTimer_CTRL_RCOD_SHIFT        0x02u
        #define NavTimer_CTRL_ENBL_SHIFT        0x00u
        #define NavTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define NavTimer_CTRL_RCOD_MASK  (0x03u << NavTimer_CTRL_RCOD_SHIFT) /* ROD and COD bit masks */
        #define NavTimer_CTRL_ENBL_MASK  (0x80u << NavTimer_CTRL_ENBL_SHIFT) /* HW_EN bit mask */
        #define NavTimer_CTRL_MODE_MASK  (0x03u << NavTimer_CTRL_MODE_SHIFT) /* Run mode bit mask */

        #define NavTimer_CTRL_RCOD       (0x03u << NavTimer_CTRL_RCOD_SHIFT)
        #define NavTimer_CTRL_ENBL       (0x80u << NavTimer_CTRL_ENBL_SHIFT)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define NavTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define NavTimer_RT1_MASK                        (0x03u << NavTimer_RT1_SHIFT)
    #define NavTimer_SYNC                            (0x03u << NavTimer_RT1_SHIFT)
    #define NavTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define NavTimer_SYNCDSI_MASK                    (0x0Fu << NavTimer_SYNCDSI_SHIFT)
    /* Sync all DSI inputs */
    #define NavTimer_SYNCDSI_EN                      (0x0Fu << NavTimer_SYNCDSI_SHIFT)

    #define NavTimer_CTRL_MODE_PULSEWIDTH            (0x01u << NavTimer_CTRL_MODE_SHIFT)
    #define NavTimer_CTRL_MODE_PERIOD                (0x02u << NavTimer_CTRL_MODE_SHIFT)
    #define NavTimer_CTRL_MODE_CONTINUOUS            (0x00u << NavTimer_CTRL_MODE_SHIFT)

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define NavTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define NavTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define NavTimer_STATUS_TC_INT_MASK_SHIFT        (NavTimer_STATUS_TC_SHIFT - 4)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define NavTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (NavTimer_STATUS_CAPTURE_SHIFT - 4)

    /* Status Register Bit Masks */
    #define NavTimer_STATUS_TC                       (0x01u << NavTimer_STATUS_TC_SHIFT)
    #define NavTimer_STATUS_CAPTURE                  (0x01u << NavTimer_STATUS_CAPTURE_SHIFT)
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define NavTimer_STATUS_TC_INT_MASK              (0x01u << NavTimer_STATUS_TC_INT_MASK_SHIFT)
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define NavTimer_STATUS_CAPTURE_INT_MASK         (0x01u << NavTimer_STATUS_CAPTURE_INT_MASK_SHIFT)

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define NavTimer_STATUS              (* (reg8 *) NavTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define NavTimer_STATUS_MASK         (* (reg8 *) NavTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define NavTimer_STATUS_AUX_CTRL     (* (reg8 *) NavTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define NavTimer_CONTROL             (* (reg8 *) NavTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )

    #define NavTimer_CAPTURE_LSB         (* (reg32 *) NavTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
    #define NavTimer_CAPTURE_LSB_PTR       ((reg32 *) NavTimer_TimerUDB_sT32_timerdp_u0__F0_REG )
    #define NavTimer_PERIOD_LSB          (* (reg32 *) NavTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
    #define NavTimer_PERIOD_LSB_PTR        ((reg32 *) NavTimer_TimerUDB_sT32_timerdp_u0__D0_REG )
    #define NavTimer_COUNTER_LSB         (* (reg32 *) NavTimer_TimerUDB_sT32_timerdp_u0__A0_REG )
    #define NavTimer_COUNTER_LSB_PTR       ((reg32 *) NavTimer_TimerUDB_sT32_timerdp_u0__A0_REG )

    #if (NavTimer_UsingHWCaptureCounter)
        #define NavTimer_CAP_COUNT              (*(reg8 *) NavTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define NavTimer_CAP_COUNT_PTR          ( (reg8 *) NavTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define NavTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) NavTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define NavTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) NavTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (NavTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define NavTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define NavTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define NavTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define NavTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define NavTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define NavTimer_CTRL_INTCNT_MASK               (0x03u << NavTimer_CTRL_INTCNT_SHIFT)
    #define NavTimer_CTRL_TRIG_MODE_MASK            (0x03u << NavTimer_CTRL_TRIG_MODE_SHIFT)
    #define NavTimer_CTRL_TRIG_EN                   (0x01u << NavTimer_CTRL_TRIG_EN_SHIFT)
    #define NavTimer_CTRL_CAP_MODE_MASK             (0x03u << NavTimer_CTRL_CAP_MODE_SHIFT)
    #define NavTimer_CTRL_ENABLE                    (0x01u << NavTimer_CTRL_ENABLE_SHIFT)

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define NavTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define NavTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define NavTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define NavTimer_STATUS_TC_INT_MASK_SHIFT       NavTimer_STATUS_TC_SHIFT
    #define NavTimer_STATUS_CAPTURE_INT_MASK_SHIFT  NavTimer_STATUS_CAPTURE_SHIFT
    #define NavTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define NavTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define NavTimer_STATUS_FIFOFULL_INT_MASK_SHIFT NavTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define NavTimer_STATUS_TC                      (0x01u << NavTimer_STATUS_TC_SHIFT)
    /* Sticky Capture Event Bit-Mask */
    #define NavTimer_STATUS_CAPTURE                 (0x01u << NavTimer_STATUS_CAPTURE_SHIFT)
    /* Interrupt Enable Bit-Mask */
    #define NavTimer_STATUS_TC_INT_MASK             (0x01u << NavTimer_STATUS_TC_SHIFT)
    /* Interrupt Enable Bit-Mask */
    #define NavTimer_STATUS_CAPTURE_INT_MASK        (0x01u << NavTimer_STATUS_CAPTURE_SHIFT)
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define NavTimer_STATUS_FIFOFULL                (0x01u << NavTimer_STATUS_FIFOFULL_SHIFT)
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define NavTimer_STATUS_FIFONEMP                (0x01u << NavTimer_STATUS_FIFONEMP_SHIFT)
    /* Interrupt Enable Bit-Mask */
    #define NavTimer_STATUS_FIFOFULL_INT_MASK       (0x01u << NavTimer_STATUS_FIFOFULL_SHIFT)

    #define NavTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define NavTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define NavTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define NavTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define NavTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define NavTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_NavTimer_H */


/* [] END OF FILE */
