/*******************************************************************************
* File Name: LineCounter.h  
* Version 2.20
*
*  Description:
*   Contains the function prototypes and constants available to the counter
*   user module.
*
*   Note:
*    None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
    
#if !defined(CY_COUNTER_LineCounter_H)
#define CY_COUNTER_LineCounter_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Counter_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults        
**************************************/

#define LineCounter_Resolution            32u
#define LineCounter_UsingFixedFunction    0u
#define LineCounter_ControlRegRemoved     0u
#define LineCounter_COMPARE_MODE_SOFTWARE 0u
#define LineCounter_CAPTURE_MODE_SOFTWARE 0u
#define LineCounter_RunModeUsed           0u


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Mode API Support
 * Backup structure for Sleep Wake up operations
 *************************************************************************/
typedef struct LineCounter_backupStruct
{
    /* Sleep BackUp structure */
    uint8 CounterEnableState; 
    #if (CY_PSOC5A)
        uint32 CounterUdb;    /* Current Counter Value      */
        uint32 CounterPeriod; /* Counter Period Value       */
        uint32 CompareValue;  /* Counter Compare Value      */           
        uint8 InterruptMaskValue; /* Counter Compare Value */
    #endif /* (CY_PSOC5A) */

    #if (CY_PSOC3 || CY_PSOC5LP)
            uint32 CounterUdb;
            uint8 InterruptMaskValue;
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    #if (!LineCounter_ControlRegRemoved)
        uint8 CounterControlRegister;          /* Counter Control Register   */
    #endif /* (!LineCounter_ControlRegRemoved) */
}LineCounter_backupStruct;


/**************************************
 *  Function Prototypes
 *************************************/
void    LineCounter_Start(void) ;
void    LineCounter_Stop(void) ;
void    LineCounter_SetInterruptMode(uint8 interruptsMask) ;
uint8   LineCounter_ReadStatusRegister(void) ;
#define LineCounter_GetInterruptSource() LineCounter_ReadStatusRegister()
#if(!LineCounter_ControlRegRemoved)
    uint8   LineCounter_ReadControlRegister(void) ;
    void    LineCounter_WriteControlRegister(uint8 control) \
        ;
#endif /* (!LineCounter_ControlRegRemoved) */
#if (!(LineCounter_UsingFixedFunction && (CY_PSOC5A)))
    void    LineCounter_WriteCounter(uint32 counter) \
            ; 
#endif /* (!(LineCounter_UsingFixedFunction && (CY_PSOC5A))) */
uint32  LineCounter_ReadCounter(void) ;
uint32  LineCounter_ReadCapture(void) ;
void    LineCounter_WritePeriod(uint32 period) \
    ;
uint32  LineCounter_ReadPeriod( void ) ;
#if (!LineCounter_UsingFixedFunction)
    void    LineCounter_WriteCompare(uint32 compare) \
        ;
    uint32  LineCounter_ReadCompare( void ) \
        ;
#endif /* (!LineCounter_UsingFixedFunction) */

#if (LineCounter_COMPARE_MODE_SOFTWARE)
    void    LineCounter_SetCompareMode(uint8 comparemode) ;
#endif /* (LineCounter_COMPARE_MODE_SOFTWARE) */
#if (LineCounter_CAPTURE_MODE_SOFTWARE)
    void    LineCounter_SetCaptureMode(uint8 capturemode) ;
#endif /* (LineCounter_CAPTURE_MODE_SOFTWARE) */
void LineCounter_ClearFIFO(void)     ;
void LineCounter_Init(void)          ;
void LineCounter_Enable(void)        ;
void LineCounter_SaveConfig(void)    ;
void LineCounter_RestoreConfig(void) ;
void LineCounter_Sleep(void)         ;
void LineCounter_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Counter__CompareModes, Used in Compare Mode retained for backward compatibility of tests*/
#define LineCounter__B_COUNTER__LESS_THAN 1
#define LineCounter__B_COUNTER__LESS_THAN_OR_EQUAL 2
#define LineCounter__B_COUNTER__EQUAL 0
#define LineCounter__B_COUNTER__GREATER_THAN 3
#define LineCounter__B_COUNTER__GREATER_THAN_OR_EQUAL 4
#define LineCounter__B_COUNTER__SOFTWARE 5

/* Enumerated Type Counter_CompareModes */
#define LineCounter_CMP_MODE_LT 1u
#define LineCounter_CMP_MODE_LTE 2u
#define LineCounter_CMP_MODE_EQ 0u
#define LineCounter_CMP_MODE_GT 3u
#define LineCounter_CMP_MODE_GTE 4u
#define LineCounter_CMP_MODE_SOFTWARE_CONTROLLED 5u

/* Enumerated Type B_Counter__CaptureModes, Used in Capture Mode retained for backward compatibility of tests*/
#define LineCounter__B_COUNTER__NONE 0
#define LineCounter__B_COUNTER__RISING_EDGE 1
#define LineCounter__B_COUNTER__FALLING_EDGE 2
#define LineCounter__B_COUNTER__EITHER_EDGE 3
#define LineCounter__B_COUNTER__SOFTWARE_CONTROL 4

/* Enumerated Type Counter_CompareModes */
#define LineCounter_CAP_MODE_NONE 0u
#define LineCounter_CAP_MODE_RISE 1u
#define LineCounter_CAP_MODE_FALL 2u
#define LineCounter_CAP_MODE_BOTH 3u
#define LineCounter_CAP_MODE_SOFTWARE_CONTROLLED 4u


/***************************************
 *  Initialization Values
 **************************************/
#define LineCounter_INIT_PERIOD_VALUE       4294967295u
#define LineCounter_INIT_COUNTER_VALUE      0u
#if (LineCounter_UsingFixedFunction)
#define LineCounter_INIT_INTERRUPTS_MASK    ((0u << LineCounter_STATUS_ZERO_INT_EN_MASK_SHIFT))
#else
#define LineCounter_INIT_COMPARE_VALUE      120u
#define LineCounter_INIT_INTERRUPTS_MASK ((0u << LineCounter_STATUS_ZERO_INT_EN_MASK_SHIFT) | \
        (0u << LineCounter_STATUS_CAPTURE_INT_EN_MASK_SHIFT) | \
        (0u << LineCounter_STATUS_CMP_INT_EN_MASK_SHIFT) | \
        (0u << LineCounter_STATUS_OVERFLOW_INT_EN_MASK_SHIFT) | \
        (0u << LineCounter_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT))
#define LineCounter_DEFAULT_COMPARE_MODE    (0u << LineCounter_CTRL_CMPMODE0_SHIFT)
#define LineCounter_DEFAULT_CAPTURE_MODE    (0u << LineCounter_CTRL_CAPMODE0_SHIFT)
#endif /* (LineCounter_UsingFixedFunction) */


/**************************************
 *  Registers
 *************************************/
#if (LineCounter_UsingFixedFunction)
    #define LineCounter_STATICCOUNT_LSB     (*(reg16 *) LineCounter_CounterHW__CAP0 )
    #define LineCounter_STATICCOUNT_LSB_PTR ( (reg16 *) LineCounter_CounterHW__CAP0 )
    #define LineCounter_PERIOD_LSB          (*(reg16 *) LineCounter_CounterHW__PER0 )
    #define LineCounter_PERIOD_LSB_PTR      ( (reg16 *) LineCounter_CounterHW__PER0 )
    /* MODE must be set to 1 to set the compare value */
    #define LineCounter_COMPARE_LSB         (*(reg16 *) LineCounter_CounterHW__CNT_CMP0 )
    #define LineCounter_COMPARE_LSB_PTR     ( (reg16 *) LineCounter_CounterHW__CNT_CMP0 )
    /* MODE must be set to 0 to get the count */
    #define LineCounter_COUNTER_LSB         (*(reg16 *) LineCounter_CounterHW__CNT_CMP0 )
    #define LineCounter_COUNTER_LSB_PTR     ( (reg16 *) LineCounter_CounterHW__CNT_CMP0 )
    #define LineCounter_RT1                 (*(reg8 *) LineCounter_CounterHW__RT1)
    #define LineCounter_RT1_PTR             ( (reg8 *) LineCounter_CounterHW__RT1)
#else
    #define LineCounter_STATICCOUNT_LSB     (*(reg32 *) \
        LineCounter_CounterUDB_sC32_counterdp_u0__F0_REG )
    #define LineCounter_STATICCOUNT_LSB_PTR ( (reg32 *) \
        LineCounter_CounterUDB_sC32_counterdp_u0__F0_REG )
    #define LineCounter_PERIOD_LSB          (*(reg32 *) \
        LineCounter_CounterUDB_sC32_counterdp_u0__D0_REG )
    #define LineCounter_PERIOD_LSB_PTR      ( (reg32 *) \
        LineCounter_CounterUDB_sC32_counterdp_u0__D0_REG )
    #define LineCounter_COMPARE_LSB         (*(reg32 *) \
        LineCounter_CounterUDB_sC32_counterdp_u0__D1_REG )
    #define LineCounter_COMPARE_LSB_PTR     ( (reg32 *) \
        LineCounter_CounterUDB_sC32_counterdp_u0__D1_REG )
    #define LineCounter_COUNTER_LSB         (*(reg32 *) \
        LineCounter_CounterUDB_sC32_counterdp_u0__A0_REG )
    #define LineCounter_COUNTER_LSB_PTR     ( (reg32 *)\
        LineCounter_CounterUDB_sC32_counterdp_u0__A0_REG )

    #define LineCounter_AUX_CONTROLDP0 \
        (*(reg8 *) LineCounter_CounterUDB_sC32_counterdp_u0__DP_AUX_CTL_REG)
    #define LineCounter_AUX_CONTROLDP0_PTR \
        ( (reg8 *) LineCounter_CounterUDB_sC32_counterdp_u0__DP_AUX_CTL_REG)
    #if (LineCounter_Resolution == 16 || LineCounter_Resolution == 24 || LineCounter_Resolution == 32)
       #define LineCounter_AUX_CONTROLDP1 \
           (*(reg8 *) LineCounter_CounterUDB_sC32_counterdp_u1__DP_AUX_CTL_REG)
       #define LineCounter_AUX_CONTROLDP1_PTR \
           ( (reg8 *) LineCounter_CounterUDB_sC32_counterdp_u1__DP_AUX_CTL_REG)
    #endif /* (LineCounter_Resolution == 16 || LineCounter_Resolution == 24 || LineCounter_Resolution == 32) */
    #if (LineCounter_Resolution == 24 || LineCounter_Resolution == 32)
       #define LineCounter_AUX_CONTROLDP2 \
           (*(reg8 *) LineCounter_CounterUDB_sC32_counterdp_u2__DP_AUX_CTL_REG)
       #define LineCounter_AUX_CONTROLDP2_PTR \
           ( (reg8 *) LineCounter_CounterUDB_sC32_counterdp_u2__DP_AUX_CTL_REG)
    #endif /* (LineCounter_Resolution == 24 || LineCounter_Resolution == 32) */
    #if (LineCounter_Resolution == 32)
       #define LineCounter_AUX_CONTROLDP3 \
           (*(reg8 *) LineCounter_CounterUDB_sC32_counterdp_u3__DP_AUX_CTL_REG)
       #define LineCounter_AUX_CONTROLDP3_PTR \
           ( (reg8 *) LineCounter_CounterUDB_sC32_counterdp_u3__DP_AUX_CTL_REG)
    #endif /* (LineCounter_Resolution == 32) */
#endif  /* (LineCounter_UsingFixedFunction) */

#if (LineCounter_UsingFixedFunction)
    #define LineCounter_STATUS         (*(reg8 *) LineCounter_CounterHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define LineCounter_STATUS_MASK             (*(reg8 *) LineCounter_CounterHW__SR0 )
    #define LineCounter_STATUS_MASK_PTR         ( (reg8 *) LineCounter_CounterHW__SR0 )
    #define LineCounter_CONTROL                 (*(reg8 *) LineCounter_CounterHW__CFG0)
    #define LineCounter_CONTROL_PTR             ( (reg8 *) LineCounter_CounterHW__CFG0)
    #define LineCounter_CONTROL2                (*(reg8 *) LineCounter_CounterHW__CFG1)
    #define LineCounter_CONTROL2_PTR            ( (reg8 *) LineCounter_CounterHW__CFG1)
    #if (CY_PSOC3 || CY_PSOC5LP)
        #define LineCounter_CONTROL3       (*(reg8 *) LineCounter_CounterHW__CFG2)
        #define LineCounter_CONTROL3_PTR   ( (reg8 *) LineCounter_CounterHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define LineCounter_GLOBAL_ENABLE           (*(reg8 *) LineCounter_CounterHW__PM_ACT_CFG)
    #define LineCounter_GLOBAL_ENABLE_PTR       ( (reg8 *) LineCounter_CounterHW__PM_ACT_CFG)
    #define LineCounter_GLOBAL_STBY_ENABLE      (*(reg8 *) LineCounter_CounterHW__PM_STBY_CFG)
    #define LineCounter_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) LineCounter_CounterHW__PM_STBY_CFG)
    

    /********************************
    *    Constants
    ********************************/

    /* Fixed Function Block Chosen */
    #define LineCounter_BLOCK_EN_MASK          LineCounter_CounterHW__PM_ACT_MSK
    #define LineCounter_BLOCK_STBY_EN_MASK     LineCounter_CounterHW__PM_STBY_MSK 
    
    /* Control Register Bit Locations */    
    /* As defined in Register Map, part of TMRX_CFG0 register */
    #define LineCounter_CTRL_ENABLE_SHIFT      0x00u
    #define LineCounter_ONESHOT_SHIFT          0x02u
    /* Control Register Bit Masks */
    #define LineCounter_CTRL_ENABLE            (0x01u << LineCounter_CTRL_ENABLE_SHIFT)         
    #define LineCounter_ONESHOT                (0x01u << LineCounter_ONESHOT_SHIFT)

    /* Control2 Register Bit Masks */
    /* Set the mask for run mode */
    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        #define LineCounter_CTRL_MODE_SHIFT        0x01u    
        #define LineCounter_CTRL_MODE_MASK         (0x07u << LineCounter_CTRL_MODE_SHIFT)
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Use CFG2 Mode bits to set run mode */
        #define LineCounter_CTRL_MODE_SHIFT        0x00u    
        #define LineCounter_CTRL_MODE_MASK         (0x03u << LineCounter_CTRL_MODE_SHIFT)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    /* Set the mask for interrupt (raw/status register) */
    #define LineCounter_CTRL2_IRQ_SEL_SHIFT     0x00u
    #define LineCounter_CTRL2_IRQ_SEL          (0x01u << LineCounter_CTRL2_IRQ_SEL_SHIFT)     
    
    /* Status Register Bit Locations */
    #define LineCounter_STATUS_ZERO_SHIFT      0x07u  /* As defined in Register Map, part of TMRX_SR0 register */ 

    /* Status Register Interrupt Enable Bit Locations */
    #define LineCounter_STATUS_ZERO_INT_EN_MASK_SHIFT      (LineCounter_STATUS_ZERO_SHIFT - 0x04u)

    /* Status Register Bit Masks */                           
    #define LineCounter_STATUS_ZERO            (0x01u << LineCounter_STATUS_ZERO_SHIFT)

    /* Status Register Interrupt Bit Masks*/
    #define LineCounter_STATUS_ZERO_INT_EN_MASK       (LineCounter_STATUS_ZERO >> 0x04u)
    
    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define LineCounter_RT1_SHIFT            0x04u
    #define LineCounter_RT1_MASK             (0x03u << LineCounter_RT1_SHIFT)  /* Sync TC and CMP bit masks */
    #define LineCounter_SYNC                 (0x03u << LineCounter_RT1_SHIFT)
    #define LineCounter_SYNCDSI_SHIFT        0x00u
    #define LineCounter_SYNCDSI_MASK         (0x0Fu << LineCounter_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    #define LineCounter_SYNCDSI_EN           (0x0Fu << LineCounter_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    
#else /* !LineCounter_UsingFixedFunction */
    #define LineCounter_STATUS               (* (reg8 *) LineCounter_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define LineCounter_STATUS_PTR           (  (reg8 *) LineCounter_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_REG )
    #define LineCounter_STATUS_MASK          (* (reg8 *) LineCounter_CounterUDB_sSTSReg_rstSts_stsreg__MASK_REG )
    #define LineCounter_STATUS_MASK_PTR      (  (reg8 *) LineCounter_CounterUDB_sSTSReg_rstSts_stsreg__MASK_REG )
    #define LineCounter_STATUS_AUX_CTRL      (*(reg8 *) LineCounter_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define LineCounter_STATUS_AUX_CTRL_PTR  ( (reg8 *) LineCounter_CounterUDB_sSTSReg_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define LineCounter_CONTROL              (* (reg8 *) LineCounter_CounterUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    #define LineCounter_CONTROL_PTR          (  (reg8 *) LineCounter_CounterUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )


    /********************************
    *    Constants
    ********************************/
    /* Control Register Bit Locations */
    #define LineCounter_CTRL_CMPMODE0_SHIFT    0x00u       /* As defined by Verilog Implementation */
    #define LineCounter_CTRL_CAPMODE0_SHIFT    0x03u       /* As defined by Verilog Implementation */
    #define LineCounter_CTRL_RESET_SHIFT       0x06u       /* As defined by Verilog Implementation */
    #define LineCounter_CTRL_ENABLE_SHIFT      0x07u       /* As defined by Verilog Implementation */
    /* Control Register Bit Masks */
    #define LineCounter_CTRL_CMPMODE_MASK      (0x07u << LineCounter_CTRL_CMPMODE0_SHIFT)  
    #define LineCounter_CTRL_CAPMODE_MASK      (0x03u << LineCounter_CTRL_CAPMODE0_SHIFT)  
    #define LineCounter_CTRL_RESET             (0x01u << LineCounter_CTRL_RESET_SHIFT)  
    #define LineCounter_CTRL_ENABLE            (0x01u << LineCounter_CTRL_ENABLE_SHIFT) 

    /* Status Register Bit Locations */
    #define LineCounter_STATUS_CMP_SHIFT       0x00u       /* As defined by Verilog Implementation */
    #define LineCounter_STATUS_ZERO_SHIFT      0x01u       /* As defined by Verilog Implementation */
    #define LineCounter_STATUS_OVERFLOW_SHIFT  0x02u       /* As defined by Verilog Implementation */
    #define LineCounter_STATUS_UNDERFLOW_SHIFT 0x03u       /* As defined by Verilog Implementation */
    #define LineCounter_STATUS_CAPTURE_SHIFT   0x04u       /* As defined by Verilog Implementation */
    #define LineCounter_STATUS_FIFOFULL_SHIFT  0x05u       /* As defined by Verilog Implementation */
    #define LineCounter_STATUS_FIFONEMP_SHIFT  0x06u       /* As defined by Verilog Implementation */
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define LineCounter_STATUS_CMP_INT_EN_MASK_SHIFT       LineCounter_STATUS_CMP_SHIFT       
    #define LineCounter_STATUS_ZERO_INT_EN_MASK_SHIFT      LineCounter_STATUS_ZERO_SHIFT      
    #define LineCounter_STATUS_OVERFLOW_INT_EN_MASK_SHIFT  LineCounter_STATUS_OVERFLOW_SHIFT  
    #define LineCounter_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT LineCounter_STATUS_UNDERFLOW_SHIFT 
    #define LineCounter_STATUS_CAPTURE_INT_EN_MASK_SHIFT   LineCounter_STATUS_CAPTURE_SHIFT   
    #define LineCounter_STATUS_FIFOFULL_INT_EN_MASK_SHIFT  LineCounter_STATUS_FIFOFULL_SHIFT  
    #define LineCounter_STATUS_FIFONEMP_INT_EN_MASK_SHIFT  LineCounter_STATUS_FIFONEMP_SHIFT  
    /* Status Register Bit Masks */                
    #define LineCounter_STATUS_CMP             (0x01u << LineCounter_STATUS_CMP_SHIFT)  
    #define LineCounter_STATUS_ZERO            (0x01u << LineCounter_STATUS_ZERO_SHIFT) 
    #define LineCounter_STATUS_OVERFLOW        (0x01u << LineCounter_STATUS_OVERFLOW_SHIFT) 
    #define LineCounter_STATUS_UNDERFLOW       (0x01u << LineCounter_STATUS_UNDERFLOW_SHIFT) 
    #define LineCounter_STATUS_CAPTURE         (0x01u << LineCounter_STATUS_CAPTURE_SHIFT) 
    #define LineCounter_STATUS_FIFOFULL        (0x01u << LineCounter_STATUS_FIFOFULL_SHIFT)
    #define LineCounter_STATUS_FIFONEMP        (0x01u << LineCounter_STATUS_FIFONEMP_SHIFT)
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define LineCounter_STATUS_CMP_INT_EN_MASK            LineCounter_STATUS_CMP                    
    #define LineCounter_STATUS_ZERO_INT_EN_MASK           LineCounter_STATUS_ZERO            
    #define LineCounter_STATUS_OVERFLOW_INT_EN_MASK       LineCounter_STATUS_OVERFLOW        
    #define LineCounter_STATUS_UNDERFLOW_INT_EN_MASK      LineCounter_STATUS_UNDERFLOW       
    #define LineCounter_STATUS_CAPTURE_INT_EN_MASK        LineCounter_STATUS_CAPTURE         
    #define LineCounter_STATUS_FIFOFULL_INT_EN_MASK       LineCounter_STATUS_FIFOFULL        
    #define LineCounter_STATUS_FIFONEMP_INT_EN_MASK       LineCounter_STATUS_FIFONEMP         
    

    /* StatusI Interrupt Enable bit Location in the Auxilliary Control Register */
    #define LineCounter_STATUS_ACTL_INT_EN     0x10u /* As defined for the ACTL Register */
    
    /* Datapath Auxillary Control Register definitions */
    #define LineCounter_AUX_CTRL_FIFO0_CLR         0x01u   /* As defined by Register map */
    #define LineCounter_AUX_CTRL_FIFO1_CLR         0x02u   /* As defined by Register map */
    #define LineCounter_AUX_CTRL_FIFO0_LVL         0x04u   /* As defined by Register map */
    #define LineCounter_AUX_CTRL_FIFO1_LVL         0x08u   /* As defined by Register map */
    #define LineCounter_STATUS_ACTL_INT_EN_MASK    0x10u   /* As defined for the ACTL Register */
    
#endif /* LineCounter_UsingFixedFunction */

#endif  /* CY_COUNTER_LineCounter_H */


/* [] END OF FILE */

