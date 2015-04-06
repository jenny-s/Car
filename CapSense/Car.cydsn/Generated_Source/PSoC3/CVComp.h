/*******************************************************************************
* File Name: CVComp.c
* Version 1.90
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Analog Comparator User Module.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_COMP_CVComp_H) 
#define CY_COMP_CVComp_H

#include "cytypes.h"
#include "CyLib.h"
#include "cyfitter.h" 


#define CVComp_RECALMODE 0u

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Comp_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*       Type defines
***************************************/

/* Sleep Mode API Support */
typedef struct CVComp_backupStruct
{
    uint8 enableState;
   /* uint8 compCRReg; */
}CVComp_backupStruct;

#if (CY_PSOC5A)
    /* Stop API changes for PSoC5A */
    typedef struct _CVComp_lowPowerBackupStruct
    {
        uint8 compCRReg;
    }   CVComp_LOWPOWER_BACKUP_STRUCT;
#endif /* CY_PSOC5A */


/**************************************
*        Function Prototypes 
**************************************/

void    CVComp_Start(void)                  ;
void    CVComp_Stop(void)                   ;
void    CVComp_SetSpeed(uint8 speed)        ;
uint8   CVComp_GetCompare(void)             ;
uint16  CVComp_ZeroCal(void)                ;
void    CVComp_LoadTrim(uint16 trimVal)     ;
void CVComp_Init(void)                      ; 
void CVComp_Enable(void)                    ;
void CVComp_trimAdjust(uint8 nibble)        ;
void CVComp_SaveConfig(void)                ;
void CVComp_RestoreConfig(void)             ;
void CVComp_Sleep(void)                     ;
void CVComp_Wakeup(void)                    ;
/* Below APIs are valid only for PSoC3, PSoC5LP silicons.*/
#if (CY_PSOC3 || CY_PSOC5LP) 
    void CVComp_PwrDwnOverrideEnable(void)  ;
    void CVComp_PwrDwnOverrideDisable(void) ;
#endif /* CY_PSOC3 || CY_PSOC5LP */


/**************************************
*           API Constants        
**************************************/

/* Power constants for SetSpeed() function */
#define CVComp_SLOWSPEED   0x00u
#define CVComp_HIGHSPEED   0x01u
#define CVComp_LOWPOWER    0x02u


/***************************************
*         Trim Locations               
****************************************/

/* High speed trim values */
#define CVComp_HS_TRIM_TR0        (CY_GET_XTND_REG8(CVComp_ctComp__TRIM__TR0_HS))

#if (CY_PSOC3 || CY_PSOC5LP)
    #define CVComp_HS_TRIM_TR1    (CY_GET_XTND_REG8(CVComp_ctComp__TRIM__TR1_HS))
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

/* Low speed trim values */
#define CVComp_LS_TRIM_TR0        (CY_GET_XTND_REG8(CVComp_ctComp__TRIM__TR0 + 1))

#if (CY_PSOC3 || CY_PSOC5LP)
    #define CVComp_LS_TRIM_TR1    (CY_GET_XTND_REG8(CVComp_ctComp__TRIM__TR1 + 1))
#endif /* CY_PSOC3 || CY_PSOC5LP */


/**************************************
*           Parameter Defaults        
**************************************/

#define CVComp_DEFAULT_SPEED       1u 
#define CVComp_DEFAULT_HYSTERESIS  0u
#define CVComp_DEFAULT_POLARITY    1u
#define CVComp_DEFAULT_BYPASS_SYNC 0u
#define CVComp_DEFAULT_PWRDWN_OVRD 0u


/**************************************
*             Registers        
**************************************/

#define CVComp_CR      (* (reg8 *) CVComp_ctComp__CR )   /* Config register   */
#define CVComp_CR_PTR  (  (reg8 *) CVComp_ctComp__CR )
#define CVComp_CLK     (* (reg8 *) CVComp_ctComp__CLK )  /* Comp clock control register */
#define CVComp_CLK_PTR (  (reg8 *) CVComp_ctComp__CLK )
#define CVComp_SW0     (* (reg8 *) CVComp_ctComp__SW0 )  /* Routing registers */
#define CVComp_SW0_PTR (  (reg8 *) CVComp_ctComp__SW0 )
#define CVComp_SW2     (* (reg8 *) CVComp_ctComp__SW2 )
#define CVComp_SW2_PTR (  (reg8 *) CVComp_ctComp__SW2 )
#define CVComp_SW3     (* (reg8 *) CVComp_ctComp__SW3 )
#define CVComp_SW3_PTR (  (reg8 *) CVComp_ctComp__SW3 )
#define CVComp_SW4     (* (reg8 *) CVComp_ctComp__SW4 )
#define CVComp_SW4_PTR (  (reg8 *) CVComp_ctComp__SW4 )
#define CVComp_SW6     (* (reg8 *) CVComp_ctComp__SW6 )
#define CVComp_SW6_PTR (  (reg8 *) CVComp_ctComp__SW6 )

/* Trim registers */
/* PSoC5A */
#if (CY_PSOC5A)
    #define CVComp_TR      (* (reg8 *) CVComp_ctComp__TR )   /* Trim registers */
    #define CVComp_TR_PTR  (  (reg8 *) CVComp_ctComp__TR )
#endif /* CY_PSOC5A */

/* PSoC3, PSoC5LP or later */
#if (CY_PSOC3 || CY_PSOC5LP) 
    #define CVComp_TR0         (* (reg8 *) CVComp_ctComp__TR0 ) /* Trim register for P-type load */
    #define CVComp_TR0_PTR     (  (reg8 *) CVComp_ctComp__TR0 ) 
    #define CVComp_TR1         (* (reg8 *) CVComp_ctComp__TR1 ) /* Trim register for N-type load */
    #define CVComp_TR1_PTR     (  (reg8 *) CVComp_ctComp__TR1 ) 
#endif /* CY_PSOC3 || CY_PSOC5LP */

#define CVComp_WRK             (* (reg8 *) CVComp_ctComp__WRK )  /* Working register - output */
#define CVComp_WRK_PTR         (  (reg8 *) CVComp_ctComp__WRK )
#define CVComp_PWRMGR          (* (reg8 *) CVComp_ctComp__PM_ACT_CFG )  /* Active Power manager */
#define CVComp_PWRMGR_PTR      ( (reg8 *) CVComp_ctComp__PM_ACT_CFG )
#define CVComp_STBY_PWRMGR     (* (reg8 *) CVComp_ctComp__PM_STBY_CFG )  /* Standby Power manager */
#define CVComp_STBY_PWRMGR_PTR ( (reg8 *) CVComp_ctComp__PM_STBY_CFG )


/**************************************
*       Register Constants        
**************************************/

/* CR (Comp Control Register)             */
#define CVComp_CFG_MODE_MASK  0x78u
#define CVComp_FILTER_ON      0x40u
#define CVComp_HYST_OFF       0x20u
#define CVComp_CAL_ON         0x10u
#define CVComp_MX_AO          0x08u
#define CVComp_PWRDWN_OVRD    0x04u

#define CVComp_PWR_MODE_SHIFT 0x00u
#define CVComp_PWR_MODE_MASK  (0x03u << CVComp_PWR_MODE_SHIFT)
#define CVComp_PWR_MODE_SLOW  (0x00u << CVComp_PWR_MODE_SHIFT)
#define CVComp_PWR_MODE_FAST  (0x01u << CVComp_PWR_MODE_SHIFT)
#define CVComp_PWR_MODE_ULOW  (0x02u << CVComp_PWR_MODE_SHIFT)

/* CLK (Comp Clock Control Register)      */
#define CVComp_BYPASS_SYNC    0x10u
#define CVComp_SYNC_CLK_EN    0x08u
#define CVComp_SYNCCLK_MASK   (CVComp_BYPASS_SYNC | CVComp_SYNC_CLK_EN)

/* SW3 Routing Register definitions */
#define CVComp_CMP_SW3_INPCTL_MASK    0x09u   /* SW3 bits for inP routing control */

/* TR (Comp Trim Register)     */
#define CVComp_DEFAULT_CMP_TRIM  0x00u

/* PSoC5A */
#if (CY_PSOC5A)
    #define CVComp_CMP_TRIM1_DIR  0x08u   /* Trim direction for N-type load for offset calibration */
    #define CVComp_CMP_TRIM1_MASK 0x07u   /* Trim for N-type load for offset calibration */
    #define CVComp_CMP_TRIM2_DIR  0x80u   /* Trim direction for P-type load for offset calibration */
    #define CVComp_CMP_TRIM2_MASK 0x70u   /* Trim for P-type load for offset calibration */
#endif /* CY_PSOC5A */

/* PSoC3, PSoC5LP or later */
#if (CY_PSOC3 || CY_PSOC5LP)
    #define CVComp_CMP_TR0_DIR 0x10u    /* Trim direction for N-type load for offset calibration */
    #define CVComp_CMP_TR0_MASK 0x0Fu   /* Trim for N-type load for offset calibration */
    #define CVComp_CMP_TR1_DIR 0x10u    /* Trim direction for P-type load for offset calibration */
    #define CVComp_CMP_TR1_MASK 0x07u   /* Trim for P-type load for offset calibration */ 
#endif /* CY_PSOC3 || CY_PSOC5LP */


/* WRK (Comp output working register)     */ 
#define CVComp_CMP_OUT_MASK   CVComp_ctComp__WRK_MASK /* Specific comparator out mask */

/* PM_ACT_CFG7 (Active Power Mode CFG Register)     */ 
#define CVComp_ACT_PWR_EN     CVComp_ctComp__PM_ACT_MSK /* Power enable mask */

/* PM_STBY_CFG7 (Standby Power Mode CFG Register)     */ 
#define CVComp_STBY_PWR_EN     CVComp_ctComp__PM_STBY_MSK /* Standby Power enable mask */

#if (CY_PSOC5A)
    /* For stop API changes mask to make the COMP register CR to 0X00  */
    #define CVComp_COMP_REG_CLR             (0x00u)
#endif /* CY_PSOC5A */

#endif /* CY_COMP_CVComp_H */


/* [] END OF FILE */
