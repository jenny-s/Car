// ======================================================================
// Car.v generated from TopDesign.cysch
// 04/04/2015 at 14:03
// This file is auto generated. ANY EDITS YOU MAKE MAY BE LOST WHEN THIS FILE IS REGENERATED!!!
// ======================================================================

/* -- WARNING: The following section of defines are deprecated and will be removed in a future release -- */
`define CYDEV_CHIP_DIE_LEOPARD 1
`define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3
`define CYDEV_CHIP_REV_LEOPARD_ES3 3
`define CYDEV_CHIP_REV_LEOPARD_ES2 1
`define CYDEV_CHIP_REV_LEOPARD_ES1 0
`define CYDEV_CHIP_DIE_PANTHER 2
`define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1
`define CYDEV_CHIP_REV_PANTHER_ES1 1
`define CYDEV_CHIP_REV_PANTHER_ES0 0
`define CYDEV_CHIP_DIE_EXPECT 1
`define CYDEV_CHIP_REV_EXPECT 3
`define CYDEV_CHIP_DIE_ACTUAL 1
/* -- WARNING: The previous section of defines are deprecated and will be removed in a future release -- */
`define CYDEV_CHIP_FAMILY_UNKNOWN 0
`define CYDEV_CHIP_MEMBER_UNKNOWN 0
`define CYDEV_CHIP_FAMILY_PSOC3 1
`define CYDEV_CHIP_MEMBER_3A 1
`define CYDEV_CHIP_REVISION_3A_PRODUCTION 3
`define CYDEV_CHIP_REVISION_3A_ES3 3
`define CYDEV_CHIP_REVISION_3A_ES2 1
`define CYDEV_CHIP_REVISION_3A_ES1 0
`define CYDEV_CHIP_FAMILY_PSOC5 2
`define CYDEV_CHIP_MEMBER_5A 2
`define CYDEV_CHIP_REVISION_5A_PRODUCTION 1
`define CYDEV_CHIP_REVISION_5A_ES1 1
`define CYDEV_CHIP_REVISION_5A_ES0 0
`define CYDEV_CHIP_FAMILY_USED 1
`define CYDEV_CHIP_MEMBER_USED 1
`define CYDEV_CHIP_REVISION_USED 3
// Component: cy_virtualmux_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0"
`include "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`endif

// Component: not_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\not_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\not_v1_0\not_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\not_v1_0"
`include "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\not_v1_0\not_v1_0.v"
`endif

// Comp_v1_90(Hysteresis=0, Pd_Override=0, Polarity=0, PSOC5A=false, Speed=0, Sync=1, CY_COMPONENT_NAME=Comp_v1_90, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=CompCH0, CY_INSTANCE_SHORT_NAME=CompCH0, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=90, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=CapSense_CompCH0, )
module Comp_v1_90_0 (
    Vplus,
    CmpOut,
    Vminus,
    clock);
    inout       Vplus;
    electrical  Vplus;
    output      CmpOut;
    inout       Vminus;
    electrical  Vminus;
    input       clock;


          wire  Net_9;
          wire  Net_1;

    cy_psoc3_ctcomp_v1_0 ctComp (
        .vplus(Vplus),
        .vminus(Vminus),
        .cmpout(Net_1),
        .clk_udb(clock),
        .clock(clock));

	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign CmpOut = Net_1;


    assign Net_9 = ~Net_1;



endmodule

// Component: CapSense_CSD_AMux_v3_20
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_AMux_v3_20"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_AMux_v3_20\CapSense_CSD_AMux_v3_20.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_AMux_v3_20"
`include "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_AMux_v3_20\CapSense_CSD_AMux_v3_20.v"
`endif

// Component: CapSense_CSD_MeasureCh_v3_20
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_MeasureCh_v3_20"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_MeasureCh_v3_20\CapSense_CSD_MeasureCh_v3_20.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_MeasureCh_v3_20"
`include "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_MeasureCh_v3_20\CapSense_CSD_MeasureCh_v3_20.v"
`endif

// Component: cy_vref_v1_60
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_vref_v1_60"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_vref_v1_60\cy_vref_v1_60.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_vref_v1_60"
`include "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_vref_v1_60\cy_vref_v1_60.v"
`endif

// Component: CapSense_CSD_ClockGen_v3_20
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_ClockGen_v3_20"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_ClockGen_v3_20\CapSense_CSD_ClockGen_v3_20.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_ClockGen_v3_20"
`include "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\CapSense_CSD_ClockGen_v3_20\CapSense_CSD_ClockGen_v3_20.v"
`endif

// Component: OneTerminal
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\OneTerminal"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\OneTerminal\OneTerminal.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\OneTerminal"
`include "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\OneTerminal\OneTerminal.v"
`endif

// Component: cy_analog_virtualmux_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_analog_virtualmux_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_analog_virtualmux_v1_0\cy_analog_virtualmux_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_analog_virtualmux_v1_0"
`include "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_analog_virtualmux_v1_0\cy_analog_virtualmux_v1_0.v"
`endif

// Component: ZeroTerminal
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal"
`include "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`endif

// Component: or_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\or_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\or_v1_0\or_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\or_v1_0"
`include "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\or_v1_0\or_v1_0.v"
`endif

// IDAC8_v1_90(Current=0, Data_Source=0, Hardware_Enable=true, IDAC_Range=4, IDAC_Speed=0, Initial_Value=0, Polarity=4, Strobe_Mode=0, CY_COMPONENT_NAME=IDAC8_v1_90, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=IdacCH0, CY_INSTANCE_SHORT_NAME=IdacCH0, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=90, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=CapSense_IdacCH0, )
module IDAC8_v1_90_1 (
    iOut,
    data,
    strobe,
    en,
    ipolarity);
    inout       iOut;
    electrical  iOut;
    input      [7:0] data;
    input       strobe;
    input       en;
    input       ipolarity;

    parameter Data_Source = 0;
    parameter Initial_Value = 0;
    parameter Strobe_Mode = 0;

          wire  Net_195;
          wire  Net_194;
    electrical  Net_124;
          wire  Net_158;
          wire  Net_157;
          wire  Net_123;
          wire  Net_125;

    cy_psoc3_vidac8_v1_0 viDAC8 (
        .reset(Net_125),
        .idir(Net_158),
        .data(data[7:0]),
        .strobe(strobe),
        .vout(Net_124),
        .iout(iOut),
        .ioff(Net_123),
        .strobe_udb(strobe));
    defparam viDAC8.is_all_if_any = 0;
    defparam viDAC8.reg_data = 0;


    assign Net_157 = ~en;

    ZeroTerminal ZeroTerminal_3 (
        .z(Net_125));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_1 (
        .noconnect(Net_124));

	// VirtualMux_2 (cy_virtualmux_v1_0)
	assign Net_123 = Net_157;

	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_158 = Net_195;

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_194));

    ZeroTerminal ZeroTerminal_2 (
        .z(Net_195));



endmodule

// CapSense_CSD_v3_20(AnalogSwitchDivider=2, ClockSource=0, ConnectInactiveSensors=0, CtlModeReplacementString=SyncCtrl, CurrentSource=1, EnableTuneHelper=false, EzI2CInstanceName=EzI2C, GuardSensorEnable=false, IdacRange=4, Implementation_CH0=1, Implementation_CH1=1, IntClockFrequency=12, LowBaselineReset=5, MaximumSensors=62, MultipleAnalogSwitchDivider=false, NegativeNoiseThreshold=20, NumberOfChannels=1, PrechargePolarity=3, PrescalerOptions=1, PrsOptions=1, RawDataFilterType=0, RbNumber_CH0=0, RbNumber_CH1=0, RemoveCH1=true, RemoveVrefTerm=false, ScanSpeed=3, SensorAutoReset=false, SensorNumber_CH0=7, SensorNumber_CH1=0, SensorNumberChannel0=7, SensorNumberChannel1=0, ShieldEnable=false, SignalSizeReplacementString=uint8, SnsAlias_CH0=<?xml version='1.0'?><PinAliases Version='1'><pin0>Button0__BTN</pin0><pin1>Button1__BTN</pin1><pin2>LinearSlider0_e0__LS</pin2><pin3>LinearSlider0_e1__LS</pin3><pin4>LinearSlider0_e2__LS</pin4><pin5>LinearSlider0_e3__LS</pin5><pin6>LinearSlider0_e4__LS</pin6></PinAliases>, SnsAlias_CH1=<?xml version="1.0" ?><PinAliases Version="1"><pin0>pin1_ch1</pin0></PinAliases>, TunerProperties=, TuningMethod=1, VrefOptions=0, VrefValue=64, WaterProofingEnabled=false, WidgetResolution=8, WidgetsData=<?xml version="1.0" encoding="utf-16"?> <CyWidgetsList xmlns:version="v1.00">   <ListMainTerminal>     <CyTerminal NameIndex="0" WidgetName="Button0__BTN" />     <CyTerminal NameIndex="0" WidgetName="Button1__BTN" />     <CyTerminal NameIndex="0" WidgetName="LinearSlider0__LS" />     <CyTerminal NameIndex="1" WidgetName="LinearSlider0__LS" />     <CyTerminal NameIndex="2" WidgetName="LinearSlider0__LS" />     <CyTerminal NameIndex="3" WidgetName="LinearSlider0__LS" />     <CyTerminal NameIndex="4" WidgetName="LinearSlider0__LS" />   </ListMainTerminal>   <ListButtons>     <CyButton Name="Button0" Type="Button" Channel="First" Count="1" Angle="0" Fliped="false" Fliped2D="false" ScaleFactor="1">       <Location>         <X>2147483647</X>         <Y>2147483647</Y>       </Location>       <Properties>         <Hysteresis>5</Hysteresis>         <Debounce>1</Debounce>         <FingerThreshold>60</FingerThreshold>         <NoiseThreshold>30</NoiseThreshold>         <ScanResolution>_8</ScanResolution>       </Properties>     </CyButton>     <CyButton Name="Button1" Type="Button" Channel="First" Count="1" Angle="0" Fliped="false" Fliped2D="false" ScaleFactor="1">       <Location>         <X>2147483647</X>         <Y>2147483647</Y>       </Location>       <Properties>         <Hysteresis>5</Hysteresis>         <Debounce>1</Debounce>         <FingerThreshold>60</FingerThreshold>         <NoiseThreshold>30</NoiseThreshold>         <ScanResolution>_8</ScanResolution>       </Properties>     </CyButton>   </ListButtons>   <ListMatrixButtons />   <ListTouchPads />   <ListSliders>     <CySlider Name="LinearSlider0" Type="SliderLinear" Channel="First" Count="5" Angle="0" Fliped="false" Fliped2D="false" ScaleFactor="1" Diplexing="false" Resolution="100" FilterPropertiesPos="None">       <Location>         <X>2147483647</X>         <Y>2147483647</Y>       </Location>       <Properties>         <Hysteresis>0</Hysteresis>         <Debounce>0</Debounce>         <FingerThreshold>48</FingerThreshold>         <NoiseThreshold>24</NoiseThreshold>         <ScanResolution>_8</ScanResolution>       </Properties>     </CySlider>   </ListSliders>   <GuardSensor Name="GuardSensor" Type="Button" Channel="First" Count="1" Angle="0" Fliped="false" Fliped2D="false" ScaleFactor="1">     <Location>       <X>2147483647</X>       <Y>2147483647</Y>     </Location>     <Properties>       <Hysteresis>10</Hysteresis>       <Debounce>5</Debounce>       <FingerThreshold>100</FingerThreshold>       <NoiseThreshold>20</NoiseThreshold>       <ScanResolution>_10</ScanResolution>     </Properties>   </GuardSensor>   <GuardSensorTerminal NameIndex="0" WidgetName="GuardSensor__GRD" />   <CyScanSlotsList>     <ListScanSlots>       <CyScanSlot IDACSettings="55" Sensitivity="4" WidgetName="Button0__BTN">         <ListTerminalsNames>           <string>Button0__BTN</string>         </ListTerminalsNames>       </CyScanSlot>       <CyScanSlot IDACSettings="55" Sensitivity="4" WidgetName="Button1__BTN">         <ListTerminalsNames>           <string>Button1__BTN</string>         </ListTerminalsNames>       </CyScanSlot>       <CyScanSlot IDACSettings="35" Sensitivity="4" WidgetName="LinearSlider0__LS">         <ListTerminalsNames>           <string>LinearSlider0_e0__LS</string>         </ListTerminalsNames>       </CyScanSlot>       <CyScanSlot IDACSettings="35" Sensitivity="4" WidgetName="LinearSlider0__LS">         <ListTerminalsNames>           <string>LinearSlider0_e1__LS</string>         </ListTerminalsNames>       </CyScanSlot>       <CyScanSlot IDACSettings="35" Sensitivity="4" WidgetName="LinearSlider0__LS">         <ListTerminalsNames>           <string>LinearSlider0_e2__LS</string>         </ListTerminalsNames>       </CyScanSlot>       <CyScanSlot IDACSettings="35" Sensitivity="4" WidgetName="LinearSlider0__LS">         <ListTerminalsNames>           <string>LinearSlider0_e3__LS</string>         </ListTerminalsNames>       </CyScanSlot>       <CyScanSlot IDACSettings="35" Sensitivity="4" WidgetName="LinearSlider0__LS">         <ListTerminalsNames>           <string>LinearSlider0_e4__LS</string>         </ListTerminalsNames>       </CyScanSlot>     </ListScanSlots>     <GuardSensorScanSlot IDACSettings="200" Sensitivity="2" WidgetName="GuardSensor__GRD">       <ListTerminalsNames>         <string>GuardSensor__GRD</string>       </ListTerminalsNames>     </GuardSensorScanSlot>   </CyScanSlotsList> </CyWidgetsList>, CY_COMPONENT_NAME=CapSense_CSD_v3_20, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=CapSense, CY_INSTANCE_SHORT_NAME=CapSense, CY_MAJOR_VERSION=3, CY_MINOR_VERSION=20, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=CapSense, )
module CapSense_CSD_v3_20_2 (
    clock,
    shield,
    vref,
    bclk);
    input       clock;
    output      shield;
    inout       vref;
    electrical  vref;
    output      bclk;


          wire  PreChargeClk;
          wire  DigitalClk;
          wire  ShieldSignal;
          wire  mrst;
          wire  Cmp_CH1;
          wire  Cmp_CH0;
          wire  Ioff_CH1;
          wire  Ioff_CH0;
          wire  clk;
          wire  Net_1652;
          wire  Net_1398;
          wire  Net_548;
          wire  Net_1399;
          wire  Net_273;
          wire  Net_1401;
          wire  Net_1090;
          wire [7:0] Net_1091;
          wire  Net_1402;
          wire  Net_1403;
          wire  Net_2300;
          wire [7:0] Net_2301;
          wire  Net_2304;
          wire  Net_1503;
          wire  Net_1501;
    electrical  Net_2127;
          wire  Net_1499;
          wire [7:0] Net_1500;
          wire  Net_1651;
    electrical  Net_2124;
    electrical  Net_2060;
    electrical  Net_2163;
    electrical  Net_2160;
    electrical  Net_1961;
          wire  Net_2244;
          wire  Net_2256;
          wire  Net_2258;
          wire  Net_2318;
          wire [7:0] Net_2319;
          wire  Net_2320;
    electrical  Net_2311;
    electrical  Net_2309;
          wire  Net_2255;
    electrical  Net_2153;
    electrical  Net_2129;
    electrical  Net_2149;
    electrical  Net_2101;
    electrical  Net_1440;
    electrical  Net_2098;
    electrical  Net_1956;
    electrical  Net_2107;
    electrical  Net_1903;
    electrical  Net_2164;
    electrical  Net_2072;
    electrical  Net_2031;
    electrical  Net_2038;
    electrical  Net_2077;
          wire  Net_2270;
          wire  Net_1603;
    electrical [6:0] Net_1410;
    electrical  Net_2267;
    electrical  Net_2265;
          wire  Net_1350;
          wire  Net_2263;
    electrical  Net_2261;
    electrical  Net_2260;


	cy_clock_v1_0
		#(.id("579ff463-aee1-4a1a-af79-bf1a06ddbc35/0ad1a1a8-974e-43a0-841b-3af08590011d"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("83333333.3333333"),
		  .is_direct(0),
		  .is_digital(1))
		IntClock
		 (.clock_out(Net_2270));


	// ClockSelect_VirtualMux (cy_virtualmux_v1_0)
	assign clk = Net_2270;


	cy_isr_v1_0
		#(.int_type(2'b00))
		IsrCH0
		 (.int_signal(Net_1603));


    cy_psoc3_csabuf_v1_0 BufCH0 (
        .vref(Net_2129),
        .vout(Net_2072),
        .vchan(Net_2149));

    Comp_v1_90_0 CompCH0 (
        .Vplus(Net_2260),
        .CmpOut(Cmp_CH0),
        .Vminus(Net_2265),
        .clock(1'b0));

	wire [0:0] tmpOE__PortCH0_net;

	cy_psoc3_port_v1_0
		#(.width(7),
		  .siorefwidth(4),
		  .id("579ff463-aee1-4a1a-af79-bf1a06ddbc35/dd9c1af8-be5a-4b9e-b10c-b2d9f11dc9fc"),
		  .pin_aliases({"Button0__BTN,But","ton1__BTN,Linear","Slider0_e0__LS,L","inearSlider0_e1_","_LS,LinearSlider","0_e2__LS,LinearS","lider0_e3__LS,Li","nearSlider0_e4__","LS"}),
		  .access_mode("HW_ONLY"),
		  .layout_mode("NONCONTIGUOUS"),
		  .port_mode("ANALOG"),
		  .intr_mode(14'b00000000000000),
		  .drive_mode(21'b100100100100100100100),
		  .por_state(0),
		  .enable_shielding(7'b0000000),
		  .cs_mode(2'b11))
		PortCH0
		 (.oe(tmpOE__PortCH0_net),
		  .y(7'b0),
		  .analog(Net_1410[6:0]),
		  .precharge(PreChargeClk));

	assign tmpOE__PortCH0_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? 1'b1 : 1'b0;

	wire [0:0] tmpOE__CmodCH0_net;
	wire [0:0] tmpFB_0__CmodCH0_net;
	wire [0:0] tmpIO_0__CmodCH0_net;
	wire [0:0] tmpINTERRUPT_0__CmodCH0_net;
	electrical [0:0] tmpSIOVREF__CmodCH0_net;

	cy_psoc3_pins_v1_10
		#(.id("579ff463-aee1-4a1a-af79-bf1a06ddbc35/232398c5-3876-4e07-8f5b-7cd7657055e2"),
		  .drive_mode(3'b000),
		  .ibuf_enabled(1'b0),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("NONCONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases("Cmod_CH0"),
		  .pin_mode("A"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(1),
		  .vtrip(2'b10),
		  .width(1))
		CmodCH0
		 (.oe(tmpOE__CmodCH0_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__CmodCH0_net[0:0]}),
		  .analog({Net_2261}),
		  .io({tmpIO_0__CmodCH0_net[0:0]}),
		  .siovref(tmpSIOVREF__CmodCH0_net),
		  .interrupt({tmpINTERRUPT_0__CmodCH0_net[0:0]}));

	assign tmpOE__CmodCH0_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    // -- AMux AMuxCH0 start -- ***
    // -- Mux A --
    
    cy_psoc3_amux_v1_0 AMuxCH0(
        .muxin({
            Net_2311,
            Net_2260,
            Net_2261,
            Net_1410[6],
            Net_1410[5],
            Net_1410[4],
            Net_1410[3],
            Net_1410[2],
            Net_1410[1],
            Net_1410[0]
            }),
        .vout(Net_2072)
        );
    
    defparam AMuxCH0.muxin_width = 10;
    defparam AMuxCH0.init_mux_sel = 10'h0;
    defparam AMuxCH0.one_active = 0;
    
    // -- AMux AMuxCH0 end --

    CapSense_CSD_MeasureCh_v3_20 MeasureCH0 (
        .cmp_in(Cmp_CH0),
        .pulse(DigitalClk),
        .clock(clk),
        .ioff(Ioff_CH0),
        .interrupt(Net_1603),
        .reset(mrst),
        .start(Net_1350),
        .enable(Net_1401));
    defparam MeasureCH0.IdacOptions = 1;
    defparam MeasureCH0.ImplementationType = 1;


	cy_vref_v1_0
		#(.autoenable(1),
		  .guid("89B398AD-36A8-4627-9212-707F2986319E"),
		  .name("1.024V"))
		VrefRefCH0
		 (.vout(Net_2038));


    CapSense_CSD_ClockGen_v3_20 ClockGen (
        .clock(clk),
        .dpulse(DigitalClk),
        .ppulse(PreChargeClk),
        .start0(Net_1350),
        .mesrst(mrst),
        .start1(Net_2263),
        .enable(Net_1402),
        .reset(Net_1403),
        .shield(ShieldSignal));
    defparam ClockGen.IdacOptions = 1;
    defparam ClockGen.PrescalerOptions = 1;
    defparam ClockGen.PrsOptions = 1;

    OneTerminal OneTerminal_1 (
        .o(Net_1402));

    OneTerminal OneTerminal_2 (
        .o(Net_1401));

    OneTerminal OneTerminal_3 (
        .o(Net_1399));

	// DisableCapSBuf_VrefCH0 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 DisableCapSBuf_VrefCH0_connect(Net_2129, Net_2265);
	defparam DisableCapSBuf_VrefCH0_connect.sig_width = 1;

    ZeroTerminal ZeroTerminal_5 (
        .z(Net_1403));

	// Select_VrefCH0 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 Select_VrefCH0_connect(Net_2265, Net_2038);
	defparam Select_VrefCH0_connect.sig_width = 1;

    cy_analog_noconnect_v1_0 NoConnect_VchanCH0 (
        .noconnect(Net_2124));

	// Connect_VdacToAmuxCH0 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 Connect_VdacToAmuxCH0_connect(Net_1903, Net_2060);
	defparam Connect_VdacToAmuxCH0_connect.sig_width = 1;

    cy_analog_noconnect_v1_0 NoConnect_1_024ToAMuxCH0 (
        .noconnect(Net_2060));

	// Select_VrefOutput (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 Select_VrefOutput_connect(vref, Net_2038);
	defparam Select_VrefOutput_connect.sig_width = 1;

	// Select_VrefCH1 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 Select_VrefCH1_connect(Net_2164, Net_2038);
	defparam Select_VrefCH1_connect.sig_width = 1;

    cy_analog_noconnect_v1_0 NoConnect_VrefCH1 (
        .noconnect(Net_2163));

	// DisableCapSBuf_VrefCH1 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 DisableCapSBuf_VrefCH1_connect(Net_2098, Net_2164);
	defparam DisableCapSBuf_VrefCH1_connect.sig_width = 1;

    cy_analog_noconnect_v1_0 NoConnect_VchanCH1 (
        .noconnect(Net_2160));

	// DisableCapSBuf_VchanCH1 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 DisableCapSBuf_VchanCH1_connect(Net_2153, Net_1956);
	defparam DisableCapSBuf_VchanCH1_connect.sig_width = 1;

	// Connect_VdacToAmuxCH1 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 Connect_VdacToAmuxCH1_connect(Net_2107, Net_1961);
	defparam Connect_VdacToAmuxCH1_connect.sig_width = 1;

    cy_analog_noconnect_v1_0 NoConnect_1_024ToAMuxCH1 (
        .noconnect(Net_1961));

    cy_analog_noconnect_v1_0 NoConnect_VrefCH0 (
        .noconnect(Net_2127));

	// DisableCapSBuf_VchanCH0 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 DisableCapSBuf_VchanCH0_connect(Net_2149, Net_2261);
	defparam DisableCapSBuf_VchanCH0_connect.sig_width = 1;


    assign bclk = Net_2256 | Net_2244;

    ZeroTerminal ZeroTerminal_6 (
        .z(Net_2244));


	cy_clock_v1_0
		#(.id("579ff463-aee1-4a1a-af79-bf1a06ddbc35/96e8b2d4-d8ed-4ea5-8793-7587f4b4bf01"),
		  .source_clock_id("75C2148C-3656-4d8a-846D-0CAE99AB6FF7"),
		  .divisor(0),
		  .period("0"),
		  .is_direct(1),
		  .is_digital(1))
		Clock_tmp
		 (.clock_out(Net_2256));


    IDAC8_v1_90_1 IdacCH0 (
        .strobe(1'b0),
        .data(8'b00000000),
        .iOut(Net_2311),
        .en(Ioff_CH0),
        .ipolarity(1'b0));
    defparam IdacCH0.Data_Source = 0;
    defparam IdacCH0.Initial_Value = 0;
    defparam IdacCH0.Strobe_Mode = 0;


    assign shield = ShieldSignal;


endmodule

// CharLCD_v1_60(ConversionRoutines=true, CUSTOM0=0,E,8,8,8,E,0, CUSTOM1=0,A,A,4,4,4,0, CUSTOM2=0,E,A,E,8,8,0, CUSTOM3=0,E,A,C,A,A,0, CUSTOM4=0,E,8,C,8,E,0, CUSTOM5=0,E,8,E,2,E,0, CUSTOM6=0,E,8,E,2,E,0, CUSTOM7=0,4,4,4,0,4,0, CustomCharacterSet=0, CY_COMPONENT_NAME=CharLCD_v1_60, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=LCD, CY_INSTANCE_SHORT_NAME=LCD, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=60, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=LCD, )
module CharLCD_v1_60_3 ;



	wire [6:0] tmpOE__LCDPort_net;
	wire [6:0] tmpFB_6__LCDPort_net;
	wire [6:0] tmpIO_6__LCDPort_net;
	wire [0:0] tmpINTERRUPT_0__LCDPort_net;
	electrical [0:0] tmpSIOVREF__LCDPort_net;

	cy_psoc3_pins_v1_10
		#(.id("17f200e2-344f-4b67-a7ed-57e6b45331e5/ed092b9b-d398-4703-be89-cebf998501f6"),
		  .drive_mode(21'b110_110_110_110_110_110_110),
		  .ibuf_enabled(7'b1_1_1_1_1_1_1),
		  .init_dr_st(7'b0_0_0_0_0_0_0),
		  .input_sync(7'b1_1_1_1_1_1_1),
		  .intr_mode(14'b00_00_00_00_00_00_00),
		  .io_voltage(", , , , , , "),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(7'b0_0_0_0_0_0_0),
		  .output_conn(7'b0_0_0_0_0_0_0),
		  .output_sync(7'b0_0_0_0_0_0_0),
		  .pin_aliases(",,,,,,"),
		  .pin_mode("OOOOOOO"),
		  .por_state(4),
		  .use_annotation(7'b0_0_0_0_0_0_0),
		  .sio_group_cnt(0),
		  .sio_hyst(7'b0_0_0_0_0_0_0),
		  .sio_ibuf(""),
		  .sio_info(14'b00_00_00_00_00_00_00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(7'b0_0_0_0_0_0_0),
		  .spanning(0),
		  .vtrip(14'b10_10_10_10_10_10_10),
		  .width(7))
		LCDPort
		 (.oe(tmpOE__LCDPort_net),
		  .y({7'b0}),
		  .fb({tmpFB_6__LCDPort_net[6:0]}),
		  .io({tmpIO_6__LCDPort_net[6:0]}),
		  .siovref(tmpSIOVREF__LCDPort_net),
		  .interrupt({tmpINTERRUPT_0__LCDPort_net[0:0]}));

	assign tmpOE__LCDPort_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{7'b1111111} : {7'b1111111};



endmodule

// Component: B_PWM_v2_20
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_PWM_v2_20"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_PWM_v2_20\B_PWM_v2_20.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_PWM_v2_20"
`include "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_PWM_v2_20\B_PWM_v2_20.v"
`endif

// PWM_v2_20(CaptureMode=0, Compare1_16=true, Compare1_8=false, Compare2_16=false, Compare2_8=false, CompareStatusEdgeSense=true, CompareType1=1, CompareType1Software=0, CompareType2=1, CompareType2Software=0, CompareValue1=0, CompareValue2=63, CONTROL3=0, ControlReg=true, CtlModeReplacementString=SyncCtl, CyGetRegReplacementString=CY_GET_REG16, CySetRegReplacementString=CY_SET_REG16, DeadBand=0, DeadBand2_4=0, DeadBand256=0, DeadBandUsed=0, DeadTime=1, DitherOffset=0, EnableMode=0, FF16=false, FF8=false, FixedFunction=false, FixedFunctionUsed=0, InterruptOnCMP1=false, InterruptOnCMP2=false, InterruptOnKill=false, InterruptOnTC=false, IntOnCMP1=0, IntOnCMP2=0, IntOnKill=0, IntOnTC=0, KillMode=0, KillModeMinTime=0, MinimumKillTime=1, OneCompare=true, Period=255, PWMMode=0, PWMModeCenterAligned=0, RegDefReplacementString=reg16, RegSizeReplacementString=uint16, Resolution=16, RstStatusReplacementString=sSTSReg_rstSts, RunMode=0, Status=true, TriggerMode=0, UDB16=true, UDB8=false, UseControl=true, UseInterrupt=true, UseStatus=true, VerilogSectionReplacementString=sP16, CY_COMPONENT_NAME=PWM_v2_20, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=MotorPWM, CY_INSTANCE_SHORT_NAME=MotorPWM, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=20, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=MotorPWM, )
module PWM_v2_20_4 (
    pwm2,
    tc,
    clock,
    reset,
    pwm1,
    interrupt,
    capture,
    kill,
    enable,
    trigger,
    cmp_sel,
    pwm,
    ph1,
    ph2);
    output      pwm2;
    output      tc;
    input       clock;
    input       reset;
    output      pwm1;
    output      interrupt;
    input       capture;
    input       kill;
    input       enable;
    input       trigger;
    input       cmp_sel;
    output      pwm;
    output      ph1;
    output      ph2;

    parameter Resolution = 16;

          wire  Net_113;
          wire  Net_114;
          wire  Net_107;
          wire  Net_96;
          wire  Net_55;
          wire  Net_57;
          wire  Net_101;
          wire  Net_54;
          wire  Net_63;

    B_PWM_v2_20 PWMUDB (
        .reset(reset),
        .clock(clock),
        .tc(Net_101),
        .pwm1(pwm1),
        .pwm2(pwm2),
        .interrupt(Net_55),
        .kill(kill),
        .capture(capture),
        .enable(enable),
        .cmp_sel(cmp_sel),
        .trigger(trigger),
        .pwm(Net_96),
        .ph1(ph1),
        .ph2(ph2));
    defparam PWMUDB.CaptureMode = 0;
    defparam PWMUDB.CompareStatusEdgeSense = 1;
    defparam PWMUDB.CompareType1 = 1;
    defparam PWMUDB.CompareType2 = 1;
    defparam PWMUDB.DeadBand = 0;
    defparam PWMUDB.DitherOffset = 0;
    defparam PWMUDB.EnableMode = 0;
    defparam PWMUDB.KillMode = 0;
    defparam PWMUDB.PWMMode = 0;
    defparam PWMUDB.Resolution = 16;
    defparam PWMUDB.RunMode = 0;
    defparam PWMUDB.TriggerMode = 0;
    defparam PWMUDB.UseStatus = 1;

	// vmCompare (cy_virtualmux_v1_0)
	assign pwm = Net_96;

	// vmIRQ (cy_virtualmux_v1_0)
	assign interrupt = Net_55;

	// vmTC (cy_virtualmux_v1_0)
	assign tc = Net_101;

    OneTerminal OneTerminal_1 (
        .o(Net_113));

	// FFKillMux (cy_virtualmux_v1_0)
	assign Net_107 = Net_114;

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_114));



endmodule

// Component: B_Timer_v2_30
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Timer_v2_30"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Timer_v2_30\B_Timer_v2_30.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Timer_v2_30"
`include "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Timer_v2_30\B_Timer_v2_30.v"
`endif

// Timer_v2_30(CaptureAlternatingFall=false, CaptureAlternatingRise=false, CaptureCount=2, CaptureCounterEnabled=false, CaptureInputEnabled=true, CaptureMode=1, CONTROL3=0, ControlRegRemoved=0, CtlModeReplacementString=SyncCtl, CyGetRegReplacementString=CY_GET_REG32, CySetRegReplacementString=CY_SET_REG32, DeviceFamily=PSoC3, EnableMode=0, FF16=false, FF8=false, FixedFunction=false, FixedFunctionUsed=0, HWCaptureCounterEnabled=false, InterruptOnCapture=true, InterruptOnFIFOFull=false, InterruptOnTC=false, IntOnCapture=1, IntOnFIFOFull=0, IntOnTC=0, NumberOfCaptures=1, param45=1, Period=4294959999, RegDefReplacementString=reg32, RegSizeReplacementString=uint32, Resolution=32, RstStatusReplacementString=rstSts, RunMode=0, SiliconRevision=3, SoftwareCaptureModeEnabled=false, SoftwareTriggerModeEnabled=false, TriggerInputEnabled=false, TriggerMode=0, UDB16=false, UDB24=false, UDB32=true, UDB8=false, UDBControlReg=true, UsesHWEnable=0, VerilogSectionReplacementString=sT32, CY_COMPONENT_NAME=Timer_v2_30, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=SensorTimer, CY_INSTANCE_SHORT_NAME=SensorTimer, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=30, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=SensorTimer, )
module Timer_v2_30_5 (
    clock,
    reset,
    interrupt,
    enable,
    capture,
    trigger,
    capture_out,
    tc);
    input       clock;
    input       reset;
    output      interrupt;
    input       enable;
    input       capture;
    input       trigger;
    output      capture_out;
    output      tc;

    parameter CaptureCount = 2;
    parameter CaptureCounterEnabled = 0;
    parameter DeviceFamily = "PSoC3";
    parameter InterruptOnCapture = 1;
    parameter InterruptOnTC = 0;
    parameter Resolution = 32;
    parameter SiliconRevision = "3";

          wire  Net_260;
          wire  Net_261;
          wire  Net_266;
          wire  Net_102;
          wire  Net_55;
          wire  Net_57;
          wire  Net_53;
          wire  Net_51;

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_260));

	// VirtualMux_2 (cy_virtualmux_v1_0)
	assign interrupt = Net_55;

	// VirtualMux_3 (cy_virtualmux_v1_0)
	assign tc = Net_53;

    B_Timer_v2_30 TimerUDB (
        .reset(reset),
        .interrupt(Net_55),
        .enable(enable),
        .trigger(trigger),
        .capture_in(capture),
        .capture_out(capture_out),
        .tc(Net_53),
        .clock(clock));
    defparam TimerUDB.Capture_Count = 2;
    defparam TimerUDB.CaptureCounterEnabled = 0;
    defparam TimerUDB.CaptureMode = 1;
    defparam TimerUDB.EnableMode = 0;
    defparam TimerUDB.InterruptOnCapture = 1;
    defparam TimerUDB.Resolution = 32;
    defparam TimerUDB.RunMode = 0;
    defparam TimerUDB.TriggerMode = 0;

    OneTerminal OneTerminal_1 (
        .o(Net_102));

	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_266 = Net_102;



endmodule

// Comp_v1_90(Hysteresis=0, Pd_Override=0, Polarity=1, PSOC5A=false, Speed=1, Sync=0, CY_COMPONENT_NAME=Comp_v1_90, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=CVComp, CY_INSTANCE_SHORT_NAME=CVComp, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=90, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=CVComp, )
module Comp_v1_90_6 (
    Vplus,
    CmpOut,
    Vminus,
    clock);
    inout       Vplus;
    electrical  Vplus;
    output      CmpOut;
    inout       Vminus;
    electrical  Vminus;
    input       clock;


          wire  Net_9;
          wire  Net_1;

    cy_psoc3_ctcomp_v1_0 ctComp (
        .vplus(Vplus),
        .vminus(Vminus),
        .cmpout(Net_1),
        .clk_udb(clock),
        .clock(clock));

	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign CmpOut = Net_9;


    assign Net_9 = ~Net_1;



endmodule

// Timer_v2_30(CaptureAlternatingFall=false, CaptureAlternatingRise=false, CaptureCount=2, CaptureCounterEnabled=false, CaptureInputEnabled=true, CaptureMode=3, CONTROL3=0, ControlRegRemoved=0, CtlModeReplacementString=SyncCtl, CyGetRegReplacementString=CY_GET_REG32, CySetRegReplacementString=CY_SET_REG32, DeviceFamily=PSoC3, EnableMode=2, FF16=false, FF8=false, FixedFunction=false, FixedFunctionUsed=0, HWCaptureCounterEnabled=false, InterruptOnCapture=true, InterruptOnFIFOFull=false, InterruptOnTC=false, IntOnCapture=1, IntOnFIFOFull=0, IntOnTC=0, NumberOfCaptures=4, param45=1, Period=99999, RegDefReplacementString=reg32, RegSizeReplacementString=uint32, Resolution=32, RstStatusReplacementString=rstSts, RunMode=0, SiliconRevision=3, SoftwareCaptureModeEnabled=false, SoftwareTriggerModeEnabled=false, TriggerInputEnabled=false, TriggerMode=0, UDB16=false, UDB24=false, UDB32=true, UDB8=false, UDBControlReg=false, UsesHWEnable=1, VerilogSectionReplacementString=sT32, CY_COMPONENT_NAME=Timer_v2_30, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=TapeTimer, CY_INSTANCE_SHORT_NAME=TapeTimer, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=30, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=TapeTimer, )
module Timer_v2_30_7 (
    clock,
    reset,
    interrupt,
    enable,
    capture,
    trigger,
    capture_out,
    tc);
    input       clock;
    input       reset;
    output      interrupt;
    input       enable;
    input       capture;
    input       trigger;
    output      capture_out;
    output      tc;

    parameter CaptureCount = 2;
    parameter CaptureCounterEnabled = 0;
    parameter DeviceFamily = "PSoC3";
    parameter InterruptOnCapture = 1;
    parameter InterruptOnTC = 0;
    parameter Resolution = 32;
    parameter SiliconRevision = "3";

          wire  Net_261;
          wire  Net_260;
          wire  Net_266;
          wire  Net_102;
          wire  Net_55;
          wire  Net_57;
          wire  Net_53;
          wire  Net_51;

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_260));

	// VirtualMux_2 (cy_virtualmux_v1_0)
	assign interrupt = Net_55;

	// VirtualMux_3 (cy_virtualmux_v1_0)
	assign tc = Net_53;

    B_Timer_v2_30 TimerUDB (
        .reset(reset),
        .interrupt(Net_55),
        .enable(enable),
        .trigger(trigger),
        .capture_in(capture),
        .capture_out(capture_out),
        .tc(Net_53),
        .clock(clock));
    defparam TimerUDB.Capture_Count = 2;
    defparam TimerUDB.CaptureCounterEnabled = 0;
    defparam TimerUDB.CaptureMode = 3;
    defparam TimerUDB.EnableMode = 2;
    defparam TimerUDB.InterruptOnCapture = 1;
    defparam TimerUDB.Resolution = 32;
    defparam TimerUDB.RunMode = 0;
    defparam TimerUDB.TriggerMode = 0;

    OneTerminal OneTerminal_1 (
        .o(Net_102));

	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_266 = enable;



endmodule

// Component: B_Counter_v2_20
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Counter_v2_20"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Counter_v2_20\B_Counter_v2_20.v"
`else
`define CY_BLK_DIR "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Counter_v2_20"
`include "C:\Program Files\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_Counter_v2_20\B_Counter_v2_20.v"
`endif

// Counter_v2_20(CaptureMode=0, CaptureModeSoftware=0, ClockMode=0, CompareMode=0, CompareModeSoftware=0, CompareStatusEdgeSense=true, CompareValue=120, CONTROL3=0, ControlRegRemoved=0, CtlModeReplacementString=SyncCtl, CyGetRegReplacementString=CY_GET_REG32, CySetRegReplacementString=CY_SET_REG32, EnableMode=0, FF16=false, FF8=false, FixedFunction=false, FixedFunctionUsed=0, InitCounterValue=0, InterruptOnCapture=false, InterruptOnCompare=false, InterruptOnOverUnderFlow=false, InterruptOnTC=false, Period=4294967295, RegDefReplacementString=reg32, RegSizeReplacementString=uint32, ReloadOnCapture=false, ReloadOnCompare=false, ReloadOnOverUnder=true, ReloadOnReset=true, Resolution=32, RstStatusReplacementString=sSTSReg_rstSts, RunMode=0, UDB16=false, UDB24=false, UDB32=true, UDB8=false, UDBControlReg=true, UseInterrupt=true, VerilogSectionReplacementString=sC32, CY_COMPONENT_NAME=Counter_v2_20, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=LineCounter, CY_INSTANCE_SHORT_NAME=LineCounter, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=20, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=LineCounter, )
module Counter_v2_20_8 (
    clock,
    comp,
    tc,
    reset,
    interrupt,
    enable,
    capture,
    upCnt,
    downCnt,
    up_ndown,
    count);
    input       clock;
    output      comp;
    output      tc;
    input       reset;
    output      interrupt;
    input       enable;
    input       capture;
    input       upCnt;
    input       downCnt;
    input       up_ndown;
    input       count;

    parameter CaptureMode = 0;
    parameter ClockMode = 0;
    parameter CompareMode = 0;
    parameter CompareStatusEdgeSense = 1;
    parameter EnableMode = 0;
    parameter ReloadOnCapture = 0;
    parameter ReloadOnCompare = 0;
    parameter ReloadOnOverUnder = 1;
    parameter ReloadOnReset = 1;
    parameter Resolution = 32;
    parameter RunMode = 0;
    parameter UseInterrupt = 1;

          wire  Net_54;
          wire  Net_102;
          wire  Net_95;
          wire  Net_82;
          wire  Net_91;
          wire  Net_89;
          wire  Net_49;
          wire  Net_48;
          wire  Net_42;
          wire  Net_43;

	// int_vm (cy_virtualmux_v1_0)
	assign interrupt = Net_43;

	// TC_vm (cy_virtualmux_v1_0)
	assign tc = Net_49;

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_82));

	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign Net_89 = up_ndown;

    ZeroTerminal ZeroTerminal_2 (
        .z(Net_95));

	// vmEnableMode (cy_virtualmux_v1_0)
	assign Net_91 = enable;

    OneTerminal OneTerminal_1 (
        .o(Net_102));

    B_Counter_v2_20 CounterUDB (
        .reset(reset),
        .tc_out(Net_49),
        .cmp_out(comp),
        .clock(clock),
        .irq_out(Net_43),
        .up_ndown(Net_89),
        .upcnt(upCnt),
        .dwncnt(downCnt),
        .enable(enable),
        .capture(capture),
        .count(count));
    defparam CounterUDB.CaptureMode = 0;
    defparam CounterUDB.ClockMode = 0;
    defparam CounterUDB.CompareMode = 0;
    defparam CounterUDB.CompareStatusEdgeSense = 1;
    defparam CounterUDB.EnableMode = 0;
    defparam CounterUDB.ReloadOnCapture = 0;
    defparam CounterUDB.ReloadOnCompare = 0;
    defparam CounterUDB.ReloadOnOverUnder = 1;
    defparam CounterUDB.ReloadOnReset = 1;
    defparam CounterUDB.Resolution = 32;
    defparam CounterUDB.RunMode = 0;
    defparam CounterUDB.UseInterrupt = 1;



endmodule

// PWM_v2_20(CaptureMode=0, Compare1_16=true, Compare1_8=false, Compare2_16=false, Compare2_8=false, CompareStatusEdgeSense=true, CompareType1=1, CompareType1Software=0, CompareType2=1, CompareType2Software=0, CompareValue1=150, CompareValue2=0, CONTROL3=0, ControlReg=true, CtlModeReplacementString=SyncCtl, CyGetRegReplacementString=CY_GET_REG16, CySetRegReplacementString=CY_SET_REG16, DeadBand=0, DeadBand2_4=0, DeadBand256=0, DeadBandUsed=0, DeadTime=1, DitherOffset=0, EnableMode=0, FF16=false, FF8=false, FixedFunction=false, FixedFunctionUsed=0, InterruptOnCMP1=false, InterruptOnCMP2=false, InterruptOnKill=false, InterruptOnTC=false, IntOnCMP1=0, IntOnCMP2=0, IntOnKill=0, IntOnTC=0, KillMode=0, KillModeMinTime=0, MinimumKillTime=1, OneCompare=true, Period=1000, PWMMode=0, PWMModeCenterAligned=0, RegDefReplacementString=reg16, RegSizeReplacementString=uint16, Resolution=16, RstStatusReplacementString=sSTSReg_rstSts, RunMode=0, Status=true, TriggerMode=0, UDB16=true, UDB8=false, UseControl=true, UseInterrupt=true, UseStatus=true, VerilogSectionReplacementString=sP16, CY_COMPONENT_NAME=PWM_v2_20, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=ServoPWM, CY_INSTANCE_SHORT_NAME=ServoPWM, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=20, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=ServoPWM, )
module PWM_v2_20_9 (
    pwm2,
    tc,
    clock,
    reset,
    pwm1,
    interrupt,
    capture,
    kill,
    enable,
    trigger,
    cmp_sel,
    pwm,
    ph1,
    ph2);
    output      pwm2;
    output      tc;
    input       clock;
    input       reset;
    output      pwm1;
    output      interrupt;
    input       capture;
    input       kill;
    input       enable;
    input       trigger;
    input       cmp_sel;
    output      pwm;
    output      ph1;
    output      ph2;

    parameter Resolution = 16;

          wire  Net_114;
          wire  Net_113;
          wire  Net_107;
          wire  Net_96;
          wire  Net_55;
          wire  Net_57;
          wire  Net_101;
          wire  Net_54;
          wire  Net_63;

    B_PWM_v2_20 PWMUDB (
        .reset(reset),
        .clock(clock),
        .tc(Net_101),
        .pwm1(pwm1),
        .pwm2(pwm2),
        .interrupt(Net_55),
        .kill(kill),
        .capture(capture),
        .enable(enable),
        .cmp_sel(cmp_sel),
        .trigger(trigger),
        .pwm(Net_96),
        .ph1(ph1),
        .ph2(ph2));
    defparam PWMUDB.CaptureMode = 0;
    defparam PWMUDB.CompareStatusEdgeSense = 1;
    defparam PWMUDB.CompareType1 = 1;
    defparam PWMUDB.CompareType2 = 1;
    defparam PWMUDB.DeadBand = 0;
    defparam PWMUDB.DitherOffset = 0;
    defparam PWMUDB.EnableMode = 0;
    defparam PWMUDB.KillMode = 0;
    defparam PWMUDB.PWMMode = 0;
    defparam PWMUDB.Resolution = 16;
    defparam PWMUDB.RunMode = 0;
    defparam PWMUDB.TriggerMode = 0;
    defparam PWMUDB.UseStatus = 1;

	// vmCompare (cy_virtualmux_v1_0)
	assign pwm = Net_96;

	// vmIRQ (cy_virtualmux_v1_0)
	assign interrupt = Net_55;

	// vmTC (cy_virtualmux_v1_0)
	assign tc = Net_101;

    OneTerminal OneTerminal_1 (
        .o(Net_113));

	// FFKillMux (cy_virtualmux_v1_0)
	assign Net_107 = Net_114;

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_114));



endmodule

// top
module top ;

          wire  Net_1137;
          wire  Net_1136;
          wire  Net_1135;
          wire  Net_1134;
          wire  Net_1133;
          wire  Net_1132;
          wire  Net_1131;
          wire  Net_1130;
          wire  Net_1129;
          wire  Net_1128;
          wire  Net_1127;
          wire  Net_1126;
          wire  Net_1114;
          wire  Net_1125;
          wire  Net_1153;
          wire  Net_788;
          wire  Net_1042;
          wire  Net_1041;
          wire  Net_1040;
          wire  Net_1039;
          wire  Net_1038;
          wire  Net_1037;
          wire  Net_1035;
          wire  Net_1151;
          wire  Net_1150;
          wire  Net_1149;
          wire  Net_1141;
          wire  Net_1092;
          wire  Net_1091;
          wire  Net_1090;
          wire  Net_1089;
          wire  Net_1088;
          wire  Net_1115;
          wire  Net_1105;
          wire  Net_1104;
          wire  Net_1103;
          wire  Net_1102;
          wire  Net_1101;
          wire  Net_1100;
          wire  Net_1099;
          wire  Net_1098;
          wire  Net_1097;
          wire  Net_1096;
          wire  Net_1095;
          wire  Net_1094;
          wire  Net_70;
    electrical  Net_69;
          wire  Net_68;
          wire  Net_67;
          wire  Net_1140;
          wire  Net_1064;
          wire  Net_978;
          wire  Net_1147;
          wire  Net_657;
          wire  Net_12;
          wire  Net_327;
          wire  Net_1106;
          wire  Net_942;
    electrical  Net_989;
    electrical  Net_993;
          wire  Net_991;
          wire  Net_835;
          wire  Net_86;
          wire  Net_88;

    CapSense_CSD_v3_20_2 CapSense (
        .clock(1'b0),
        .shield(Net_68),
        .vref(Net_69),
        .bclk(Net_70));

    CharLCD_v1_60_3 LCD ();

    PWM_v2_20_4 MotorPWM (
        .reset(1'b0),
        .clock(Net_1106),
        .tc(Net_1095),
        .pwm1(Net_1096),
        .pwm2(Net_1097),
        .interrupt(Net_1098),
        .capture(1'b0),
        .kill(1'b1),
        .enable(1'b1),
        .trigger(1'b0),
        .cmp_sel(1'b0),
        .pwm(Net_657),
        .ph1(Net_1104),
        .ph2(Net_1105));
    defparam MotorPWM.Resolution = 16;

	wire [0:0] tmpOE__Pin_motor_for_net;
	wire [0:0] tmpFB_0__Pin_motor_for_net;
	wire [0:0] tmpIO_0__Pin_motor_for_net;
	wire [0:0] tmpINTERRUPT_0__Pin_motor_for_net;
	electrical [0:0] tmpSIOVREF__Pin_motor_for_net;

	cy_psoc3_pins_v1_10
		#(.id("4c15b41e-e284-4978-99e7-5aaee19bd0ce"),
		  .drive_mode(3'b010),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		Pin_motor_for
		 (.oe(tmpOE__Pin_motor_for_net),
		  .y({Net_657}),
		  .fb({tmpFB_0__Pin_motor_for_net[0:0]}),
		  .io({tmpIO_0__Pin_motor_for_net[0:0]}),
		  .siovref(tmpSIOVREF__Pin_motor_for_net),
		  .interrupt({tmpINTERRUPT_0__Pin_motor_for_net[0:0]}));

	assign tmpOE__Pin_motor_for_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};


	cy_clock_v1_0
		#(.id("1b7104e5-5e52-4c52-8eae-8e747de6058e"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("10000000000"),
		  .is_direct(0),
		  .is_digital(1))
		Clock_pwm
		 (.clock_out(Net_1106));



	cy_isr_v1_0
		#(.int_type(2'b00))
		SensorInterrupt
		 (.int_signal(Net_1088));


    Timer_v2_30_5 SensorTimer (
        .reset(Net_12),
        .interrupt(Net_1088),
        .enable(1'b1),
        .trigger(1'b0),
        .capture(Net_327),
        .capture_out(Net_1091),
        .tc(Net_1092),
        .clock(Net_1106));
    defparam SensorTimer.CaptureCount = 2;
    defparam SensorTimer.CaptureCounterEnabled = 0;
    defparam SensorTimer.DeviceFamily = "PSoC3";
    defparam SensorTimer.InterruptOnCapture = 1;
    defparam SensorTimer.InterruptOnTC = 0;
    defparam SensorTimer.Resolution = 32;
    defparam SensorTimer.SiliconRevision = "3";

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_12));

	wire [0:0] tmpOE__Pin_sensor_net;
	wire [0:0] tmpIO_0__Pin_sensor_net;
	wire [0:0] tmpINTERRUPT_0__Pin_sensor_net;
	electrical [0:0] tmpSIOVREF__Pin_sensor_net;

	cy_psoc3_pins_v1_10
		#(.id("e41224a6-074e-4069-a14c-b33c7d0a7380"),
		  .drive_mode(3'b001),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b00),
		  .width(1))
		Pin_sensor
		 (.oe(tmpOE__Pin_sensor_net),
		  .y({1'b0}),
		  .fb({Net_327}),
		  .io({tmpIO_0__Pin_sensor_net[0:0]}),
		  .siovref(tmpSIOVREF__Pin_sensor_net),
		  .interrupt({tmpINTERRUPT_0__Pin_sensor_net[0:0]}));

	assign tmpOE__Pin_sensor_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__Button_left_net;
	wire [0:0] tmpIO_0__Button_left_net;
	wire [0:0] tmpINTERRUPT_0__Button_left_net;
	electrical [0:0] tmpSIOVREF__Button_left_net;

	cy_psoc3_pins_v1_10
		#(.id("a6f3ae8c-b243-4470-92fc-3fb81b68320f"),
		  .drive_mode(3'b011),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b00),
		  .width(1))
		Button_left
		 (.oe(tmpOE__Button_left_net),
		  .y({1'b0}),
		  .fb({Net_86}),
		  .io({tmpIO_0__Button_left_net[0:0]}),
		  .siovref(tmpSIOVREF__Button_left_net),
		  .interrupt({tmpINTERRUPT_0__Button_left_net[0:0]}));

	assign tmpOE__Button_left_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};


	cy_isr_v1_0
		#(.int_type(2'b00))
		LeftButtonInterrupt
		 (.int_signal(Net_86));


	wire [0:0] tmpOE__Button_right_net;
	wire [0:0] tmpIO_0__Button_right_net;
	wire [0:0] tmpINTERRUPT_0__Button_right_net;
	electrical [0:0] tmpSIOVREF__Button_right_net;

	cy_psoc3_pins_v1_10
		#(.id("296af317-cbd9-428f-b40d-2db8c81ee96d"),
		  .drive_mode(3'b011),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b00),
		  .width(1))
		Button_right
		 (.oe(tmpOE__Button_right_net),
		  .y({1'b0}),
		  .fb({Net_88}),
		  .io({tmpIO_0__Button_right_net[0:0]}),
		  .siovref(tmpSIOVREF__Button_right_net),
		  .interrupt({tmpINTERRUPT_0__Button_right_net[0:0]}));

	assign tmpOE__Button_right_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};


	cy_isr_v1_0
		#(.int_type(2'b00))
		RightButtonInterrupt
		 (.int_signal(Net_88));


    Comp_v1_90_6 CVComp (
        .Vplus(Net_993),
        .CmpOut(Net_1147),
        .Vminus(Net_989),
        .clock(Net_991));

    Timer_v2_30_7 TapeTimer (
        .reset(Net_1140),
        .interrupt(Net_1141),
        .enable(Net_978),
        .trigger(1'b0),
        .capture(Net_1147),
        .capture_out(Net_1150),
        .tc(Net_1151),
        .clock(Net_1064));
    defparam TapeTimer.CaptureCount = 2;
    defparam TapeTimer.CaptureCounterEnabled = 0;
    defparam TapeTimer.DeviceFamily = "PSoC3";
    defparam TapeTimer.InterruptOnCapture = 1;
    defparam TapeTimer.InterruptOnTC = 0;
    defparam TapeTimer.Resolution = 32;
    defparam TapeTimer.SiliconRevision = "3";


    assign Net_1140 = ~Net_978;

	wire [0:0] tmpOE__Pin_CompositeSynch_net;
	wire [0:0] tmpIO_0__Pin_CompositeSynch_net;
	wire [0:0] tmpINTERRUPT_0__Pin_CompositeSynch_net;
	electrical [0:0] tmpSIOVREF__Pin_CompositeSynch_net;

	cy_psoc3_pins_v1_10
		#(.id("23581890-d6c4-4f08-8be2-8a2d712b2b09"),
		  .drive_mode(3'b010),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b00),
		  .width(1))
		Pin_CompositeSynch
		 (.oe(tmpOE__Pin_CompositeSynch_net),
		  .y({1'b0}),
		  .fb({Net_835}),
		  .io({tmpIO_0__Pin_CompositeSynch_net[0:0]}),
		  .siovref(tmpSIOVREF__Pin_CompositeSynch_net),
		  .interrupt({tmpINTERRUPT_0__Pin_CompositeSynch_net[0:0]}));

	assign tmpOE__Pin_CompositeSynch_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};


	cy_isr_v1_0
		#(.int_type(2'b00))
		FrameInterrupt
		 (.int_signal(Net_942));


    Counter_v2_20_8 LineCounter (
        .reset(Net_942),
        .tc(Net_1035),
        .comp(Net_978),
        .clock(Net_1064),
        .interrupt(Net_1037),
        .enable(1'b0),
        .capture(1'b0),
        .upCnt(1'b0),
        .downCnt(1'b0),
        .up_ndown(1'b1),
        .count(Net_835));
    defparam LineCounter.CaptureMode = 0;
    defparam LineCounter.ClockMode = 0;
    defparam LineCounter.CompareMode = 0;
    defparam LineCounter.CompareStatusEdgeSense = 1;
    defparam LineCounter.EnableMode = 0;
    defparam LineCounter.ReloadOnCapture = 0;
    defparam LineCounter.ReloadOnCompare = 0;
    defparam LineCounter.ReloadOnOverUnder = 1;
    defparam LineCounter.ReloadOnReset = 1;
    defparam LineCounter.Resolution = 32;
    defparam LineCounter.RunMode = 0;
    defparam LineCounter.UseInterrupt = 1;


	cy_isr_v1_0
		#(.int_type(2'b00))
		TapeInterrupt
		 (.int_signal(Net_1141));



    assign Net_942 = ~Net_788;


	cy_clock_v1_0
		#(.id("948c21f6-273b-4f54-bd32-e2a69e2fd61e"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("1000000000"),
		  .is_direct(0),
		  .is_digital(1))
		Clock_cam
		 (.clock_out(Net_1064));


	wire [0:0] tmpOE__Pin_servo_net;
	wire [0:0] tmpFB_0__Pin_servo_net;
	wire [0:0] tmpIO_0__Pin_servo_net;
	wire [0:0] tmpINTERRUPT_0__Pin_servo_net;
	electrical [0:0] tmpSIOVREF__Pin_servo_net;

	cy_psoc3_pins_v1_10
		#(.id("0f3fb567-6abd-42e1-ac75-d05852403de1"),
		  .drive_mode(3'b010),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		Pin_servo
		 (.oe(tmpOE__Pin_servo_net),
		  .y({Net_1125}),
		  .fb({tmpFB_0__Pin_servo_net[0:0]}),
		  .io({tmpIO_0__Pin_servo_net[0:0]}),
		  .siovref(tmpSIOVREF__Pin_servo_net),
		  .interrupt({tmpINTERRUPT_0__Pin_servo_net[0:0]}));

	assign tmpOE__Pin_servo_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};


	cy_clock_v1_0
		#(.id("54850b64-ee64-4d1d-9165-3a78fdb6e69c"),
		  .source_clock_id("75C2148C-3656-4d8a-846D-0CAE99AB6FF7"),
		  .divisor(0),
		  .period("0"),
		  .is_direct(1),
		  .is_digital(1))
		Clock_2
		 (.clock_out(Net_991));


	wire [0:0] tmpOE__Pin_Vref_net;
	wire [0:0] tmpFB_0__Pin_Vref_net;
	wire [0:0] tmpIO_0__Pin_Vref_net;
	wire [0:0] tmpINTERRUPT_0__Pin_Vref_net;
	electrical [0:0] tmpSIOVREF__Pin_Vref_net;

	cy_psoc3_pins_v1_10
		#(.id("8992438e-a5d0-4e1b-b1a3-d38475e79656"),
		  .drive_mode(3'b000),
		  .ibuf_enabled(1'b0),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("A"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		Pin_Vref
		 (.oe(tmpOE__Pin_Vref_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__Pin_Vref_net[0:0]}),
		  .analog({Net_989}),
		  .io({tmpIO_0__Pin_Vref_net[0:0]}),
		  .siovref(tmpSIOVREF__Pin_Vref_net),
		  .interrupt({tmpINTERRUPT_0__Pin_Vref_net[0:0]}));

	assign tmpOE__Pin_Vref_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__Pin_Camera_net;
	wire [0:0] tmpFB_0__Pin_Camera_net;
	wire [0:0] tmpIO_0__Pin_Camera_net;
	wire [0:0] tmpINTERRUPT_0__Pin_Camera_net;
	electrical [0:0] tmpSIOVREF__Pin_Camera_net;

	cy_psoc3_pins_v1_10
		#(.id("05a9c8de-3ba2-4909-8250-95fdc61c0bf4"),
		  .drive_mode(3'b000),
		  .ibuf_enabled(1'b0),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("A"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		Pin_Camera
		 (.oe(tmpOE__Pin_Camera_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__Pin_Camera_net[0:0]}),
		  .analog({Net_993}),
		  .io({tmpIO_0__Pin_Camera_net[0:0]}),
		  .siovref(tmpSIOVREF__Pin_Camera_net),
		  .interrupt({tmpINTERRUPT_0__Pin_Camera_net[0:0]}));

	assign tmpOE__Pin_Camera_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__Pin_vSynch_net;
	wire [0:0] tmpIO_0__Pin_vSynch_net;
	wire [0:0] tmpINTERRUPT_0__Pin_vSynch_net;
	electrical [0:0] tmpSIOVREF__Pin_vSynch_net;

	cy_psoc3_pins_v1_10
		#(.id("cc90c254-20b2-4205-9ba9-5cda4306993b"),
		  .drive_mode(3'b010),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b00),
		  .width(1))
		Pin_vSynch
		 (.oe(tmpOE__Pin_vSynch_net),
		  .y({1'b0}),
		  .fb({Net_788}),
		  .io({tmpIO_0__Pin_vSynch_net[0:0]}),
		  .siovref(tmpSIOVREF__Pin_vSynch_net),
		  .interrupt({tmpINTERRUPT_0__Pin_vSynch_net[0:0]}));

	assign tmpOE__Pin_vSynch_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    PWM_v2_20_9 ServoPWM (
        .reset(1'b0),
        .clock(Net_1106),
        .tc(Net_1127),
        .pwm1(Net_1128),
        .pwm2(Net_1129),
        .interrupt(Net_1130),
        .capture(1'b0),
        .kill(1'b1),
        .enable(1'b1),
        .trigger(1'b0),
        .cmp_sel(1'b0),
        .pwm(Net_1125),
        .ph1(Net_1136),
        .ph2(Net_1137));
    defparam ServoPWM.Resolution = 16;



endmodule

