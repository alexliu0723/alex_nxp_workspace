/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v13.0
processor: MIMXRT685S
package_id: MIMXRT685SFFOB
mcu_data: ksdk2_0
processor_version: 13.0.1
pin_labels:
- {pin_num: E14, pin_signal: PIO1_9/FC5_SSEL3/SCT0_GPI7/UTICK_CAP1/CTIMER1_MAT3/ADC0_12, label: WL_REG_ON, identifier: BOARD_INITPINS_WL_REG_ON;WL_REG_ON}
- {pin_num: P15, pin_signal: PIO2_18/PDM_CLK45/FLEXSPI0B_DATA5, label: I2C_SCL}
- {pin_num: T14, pin_signal: PIO2_12/SCT0_OUT6/CTIMER2_MAT2, label: I2C_SDA}
- {pin_num: B12, pin_signal: PIO0_16/FC2_RXD_SDA_MOSI_DATA/SCT0_GPI2/SCT0_OUT2/CTIMER2_MAT2/I2S_BRIDGE_DATA_IN/SEC_PIO0_16, label: FC2_Data/I2S2}
- {pin_num: A16, pin_signal: PIO0_15/FC2_TXD_SCL_MISO_WS/SCT0_GPI1/SCT0_OUT1/CTIMER2_MAT1/I2S_BRIDGE_WS_IN/SEC_PIO0_15, label: FC2_WS/I2S2}
- {pin_num: B17, pin_signal: PIO0_14/FC2_SCK/SCT0_GPI0/SCT0_OUT0/CTIMER2_MAT0/I2S_BRIDGE_CLK_IN/SEC_PIO0_14, label: FC2_SCK/I2S2}
- {pin_num: R2, pin_signal: PIO4_4/FC7_RTS_SCL_SSEL1, label: I2C_SCL}
- {pin_num: T3, pin_signal: PIO4_3/FC7_CTS_SDA_SSEL0, label: I2C_SDA}
- {pin_num: H4, pin_signal: PIO1_0/FC4_RTS_SCL_SSEL1/SCT0_GPI1/SCT0_OUT7/CTIMER_INP8/FC3_SSEL3, label: PDN}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_iopctl.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitCS42448Pins();
    BOARD_InitDebugConsolePins();
    BOARD_InitPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitCS42448Pins:
- options: {callFromInitBoot: 'true', coreID: cm33, enableClock: 'true'}
- pin_list:
  - {pin_num: F2, peripheral: SYSCON, signal: MCLK, pin_signal: PIO1_10/MCLK/FREQME_GPIO_CLK/CTIMER_INP10/CLKOUT, pupdena: disabled, pupdsel: pullDown, ibena: disabled,
    slew_rate: normal, drive: full, amena: disabled, odena: disabled, iiena: disabled}
  - {pin_num: K15, peripheral: FLEXCOMM1, signal: RXD_SDA_MOSI_DATA, pin_signal: PIO0_9/FC1_RXD_SDA_MOSI_DATA/SCT0_GPI6/SCT0_OUT6/CTIMER1_MAT2/I2S_BRIDGE_DATA_OUT/SEC_PIO0_9,
    pupdena: disabled, pupdsel: pullDown, ibena: enabled, slew_rate: normal, drive: full, amena: disabled, odena: disabled, iiena: disabled}
  - {pin_num: J15, peripheral: FLEXCOMM1, signal: SCK, pin_signal: PIO0_7/FC1_SCK/SCT0_GPI4/SCT0_OUT4/CTIMER1_MAT0/I2S_BRIDGE_CLK_OUT/SEC_PIO0_7, pupdena: disabled,
    pupdsel: pullDown, ibena: enabled, slew_rate: normal, drive: full, amena: disabled, odena: disabled, iiena: disabled}
  - {pin_num: T3, peripheral: FLEXCOMM7, signal: CTS_SDA_SSEL0, pin_signal: PIO4_3/FC7_CTS_SDA_SSEL0, pupdena: enabled, pupdsel: pullUp, ibena: enabled, odena: disabled}
  - {pin_num: R2, peripheral: FLEXCOMM7, signal: RTS_SCL_SSEL1, pin_signal: PIO4_4/FC7_RTS_SCL_SSEL1, pupdena: enabled, pupdsel: pullUp, ibena: enabled, odena: enabled}
  - {pin_num: H4, peripheral: GPIO, signal: 'PIO1, 0', pin_signal: PIO1_0/FC4_RTS_SCL_SSEL1/SCT0_GPI1/SCT0_OUT7/CTIMER_INP8/FC3_SSEL3, pupdena: enabled, pupdsel: pullUp}
  - {pin_num: F3, peripheral: FLEXCOMM15, signal: SDA, pin_signal: PMIC_I2C_SDA}
  - {pin_num: A12, peripheral: FLEXCOMM3, signal: SCK, pin_signal: PIO0_21/FC3_SCK/CTIMER3_MAT0/TRACECLK/SEC_PIO0_21, ibena: enabled, drive: full}
  - {pin_num: A10, peripheral: FLEXCOMM3, signal: TXD_SCL_MISO_WS, pin_signal: PIO0_22/FC3_TXD_SCL_MISO_WS/CTIMER3_MAT1/TRACEDATA(0)/SEC_PIO0_22, ibena: enabled,
    drive: full}
  - {pin_num: A8, peripheral: FLEXCOMM3, signal: RXD_SDA_MOSI_DATA, pin_signal: PIO0_23/FC3_RXD_SDA_MOSI_DATA/CTIMER3_MAT2/TRACEDATA(1)/SEC_PIO0_23, ibena: enabled,
    drive: full}
  - {pin_num: A6, peripheral: FLEXCOMM4, signal: SCK, pin_signal: PIO0_28/FC4_SCK/CTIMER4_MAT0/I2S_BRIDGE_CLK_OUT/SEC_PIO0_28, ibena: enabled, drive: full}
  - {pin_num: B6, peripheral: FLEXCOMM4, signal: TXD_SCL_MISO_WS, pin_signal: PIO0_29/FC4_TXD_SCL_MISO_WS/CTIMER4_MAT1/I2S_BRIDGE_WS_OUT/SEC_PIO0_29, ibena: enabled,
    drive: full}
  - {pin_num: C6, peripheral: FLEXCOMM4, signal: RXD_SDA_MOSI_DATA, pin_signal: PIO0_30/FC4_RXD_SDA_MOSI_DATA/CTIMER4_MAT2/I2S_BRIDGE_DATA_OUT/SEC_PIO0_30, ibena: enabled,
    drive: full}
  - {pin_num: A16, peripheral: FLEXCOMM2, signal: TXD_SCL_MISO_WS, pin_signal: PIO0_15/FC2_TXD_SCL_MISO_WS/SCT0_GPI1/SCT0_OUT1/CTIMER2_MAT1/I2S_BRIDGE_WS_IN/SEC_PIO0_15,
    ibena: enabled, drive: full}
  - {pin_num: B17, peripheral: FLEXCOMM2, signal: SCK, pin_signal: PIO0_14/FC2_SCK/SCT0_GPI0/SCT0_OUT0/CTIMER2_MAT0/I2S_BRIDGE_CLK_IN/SEC_PIO0_14, ibena: enabled,
    drive: full}
  - {pin_num: B12, peripheral: FLEXCOMM2, signal: RXD_SDA_MOSI_DATA, pin_signal: PIO0_16/FC2_RXD_SDA_MOSI_DATA/SCT0_GPI2/SCT0_OUT2/CTIMER2_MAT2/I2S_BRIDGE_DATA_IN/SEC_PIO0_16,
    ibena: enabled, drive: full}
  - {pin_num: K16, peripheral: FLEXCOMM1, signal: TXD_SCL_MISO_WS, pin_signal: PIO0_8/FC1_TXD_SCL_MISO_WS/SCT0_GPI5/SCT0_OUT5/CTIMER1_MAT1/I2S_BRIDGE_WS_OUT/SEC_PIO0_8}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitCS42448Pins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M33 */
void BOARD_InitCS42448Pins(void)
{

    const uint32_t port0_pin14_config = (/* Pin is configured as FC2_SCK */
                                         IOPCTL_PIO_FUNC1 |
                                         /* Disable pull-up / pull-down function */
                                         IOPCTL_PIO_PUPD_DI |
                                         /* Enable pull-down function */
                                         IOPCTL_PIO_PULLDOWN_EN |
                                         /* Enables input buffer function */
                                         IOPCTL_PIO_INBUF_EN |
                                         /* Normal mode */
                                         IOPCTL_PIO_SLEW_RATE_NORMAL |
                                         /* Full drive enable */
                                         IOPCTL_PIO_FULLDRIVE_EN |
                                         /* Analog mux is disabled */
                                         IOPCTL_PIO_ANAMUX_DI |
                                         /* Pseudo Output Drain is disabled */
                                         IOPCTL_PIO_PSEDRAIN_DI |
                                         /* Input function is not inverted */
                                         IOPCTL_PIO_INV_DI);
    /* PORT0 PIN14 (coords: B17) is configured as FC2_SCK */
    IOPCTL_PinMuxSet(IOPCTL, 0U, 14U, port0_pin14_config);

    const uint32_t port0_pin15_config = (/* Pin is configured as FC2_TXD_SCL_MISO_WS */
                                         IOPCTL_PIO_FUNC1 |
                                         /* Disable pull-up / pull-down function */
                                         IOPCTL_PIO_PUPD_DI |
                                         /* Enable pull-down function */
                                         IOPCTL_PIO_PULLDOWN_EN |
                                         /* Enables input buffer function */
                                         IOPCTL_PIO_INBUF_EN |
                                         /* Normal mode */
                                         IOPCTL_PIO_SLEW_RATE_NORMAL |
                                         /* Full drive enable */
                                         IOPCTL_PIO_FULLDRIVE_EN |
                                         /* Analog mux is disabled */
                                         IOPCTL_PIO_ANAMUX_DI |
                                         /* Pseudo Output Drain is disabled */
                                         IOPCTL_PIO_PSEDRAIN_DI |
                                         /* Input function is not inverted */
                                         IOPCTL_PIO_INV_DI);
    /* PORT0 PIN15 (coords: A16) is configured as FC2_TXD_SCL_MISO_WS */
    IOPCTL_PinMuxSet(IOPCTL, 0U, 15U, port0_pin15_config);

    const uint32_t port0_pin16_config = (/* Pin is configured as FC2_RXD_SDA_MOSI_DATA */
                                         IOPCTL_PIO_FUNC1 |
                                         /* Disable pull-up / pull-down function */
                                         IOPCTL_PIO_PUPD_DI |
                                         /* Enable pull-down function */
                                         IOPCTL_PIO_PULLDOWN_EN |
                                         /* Enables input buffer function */
                                         IOPCTL_PIO_INBUF_EN |
                                         /* Normal mode */
                                         IOPCTL_PIO_SLEW_RATE_NORMAL |
                                         /* Full drive enable */
                                         IOPCTL_PIO_FULLDRIVE_EN |
                                         /* Analog mux is disabled */
                                         IOPCTL_PIO_ANAMUX_DI |
                                         /* Pseudo Output Drain is disabled */
                                         IOPCTL_PIO_PSEDRAIN_DI |
                                         /* Input function is not inverted */
                                         IOPCTL_PIO_INV_DI);
    /* PORT0 PIN16 (coords: B12) is configured as FC2_RXD_SDA_MOSI_DATA */
    IOPCTL_PinMuxSet(IOPCTL, 0U, 16U, port0_pin16_config);

    const uint32_t port0_pin21_config = (/* Pin is configured as FC3_SCK */
                                         IOPCTL_PIO_FUNC1 |
                                         /* Disable pull-up / pull-down function */
                                         IOPCTL_PIO_PUPD_DI |
                                         /* Enable pull-down function */
                                         IOPCTL_PIO_PULLDOWN_EN |
                                         /* Enables input buffer function */
                                         IOPCTL_PIO_INBUF_EN |
                                         /* Normal mode */
                                         IOPCTL_PIO_SLEW_RATE_NORMAL |
                                         /* Full drive enable */
                                         IOPCTL_PIO_FULLDRIVE_EN |
                                         /* Analog mux is disabled */
                                         IOPCTL_PIO_ANAMUX_DI |
                                         /* Pseudo Output Drain is disabled */
                                         IOPCTL_PIO_PSEDRAIN_DI |
                                         /* Input function is not inverted */
                                         IOPCTL_PIO_INV_DI);
    /* PORT0 PIN21 (coords: A12) is configured as FC3_SCK */
    IOPCTL_PinMuxSet(IOPCTL, 0U, 21U, port0_pin21_config);

    const uint32_t port0_pin22_config = (/* Pin is configured as FC3_TXD_SCL_MISO_WS */
                                         IOPCTL_PIO_FUNC1 |
                                         /* Disable pull-up / pull-down function */
                                         IOPCTL_PIO_PUPD_DI |
                                         /* Enable pull-down function */
                                         IOPCTL_PIO_PULLDOWN_EN |
                                         /* Enables input buffer function */
                                         IOPCTL_PIO_INBUF_EN |
                                         /* Normal mode */
                                         IOPCTL_PIO_SLEW_RATE_NORMAL |
                                         /* Full drive enable */
                                         IOPCTL_PIO_FULLDRIVE_EN |
                                         /* Analog mux is disabled */
                                         IOPCTL_PIO_ANAMUX_DI |
                                         /* Pseudo Output Drain is disabled */
                                         IOPCTL_PIO_PSEDRAIN_DI |
                                         /* Input function is not inverted */
                                         IOPCTL_PIO_INV_DI);
    /* PORT0 PIN22 (coords: A10) is configured as FC3_TXD_SCL_MISO_WS */
    IOPCTL_PinMuxSet(IOPCTL, 0U, 22U, port0_pin22_config);

    const uint32_t port0_pin23_config = (/* Pin is configured as FC3_RXD_SDA_MOSI_DATA */
                                         IOPCTL_PIO_FUNC1 |
                                         /* Disable pull-up / pull-down function */
                                         IOPCTL_PIO_PUPD_DI |
                                         /* Enable pull-down function */
                                         IOPCTL_PIO_PULLDOWN_EN |
                                         /* Enables input buffer function */
                                         IOPCTL_PIO_INBUF_EN |
                                         /* Normal mode */
                                         IOPCTL_PIO_SLEW_RATE_NORMAL |
                                         /* Full drive enable */
                                         IOPCTL_PIO_FULLDRIVE_EN |
                                         /* Analog mux is disabled */
                                         IOPCTL_PIO_ANAMUX_DI |
                                         /* Pseudo Output Drain is disabled */
                                         IOPCTL_PIO_PSEDRAIN_DI |
                                         /* Input function is not inverted */
                                         IOPCTL_PIO_INV_DI);
    /* PORT0 PIN23 (coords: A8) is configured as FC3_RXD_SDA_MOSI_DATA */
    IOPCTL_PinMuxSet(IOPCTL, 0U, 23U, port0_pin23_config);

    const uint32_t port0_pin28_config = (/* Pin is configured as FC4_SCK */
                                         IOPCTL_PIO_FUNC1 |
                                         /* Disable pull-up / pull-down function */
                                         IOPCTL_PIO_PUPD_DI |
                                         /* Enable pull-down function */
                                         IOPCTL_PIO_PULLDOWN_EN |
                                         /* Enables input buffer function */
                                         IOPCTL_PIO_INBUF_EN |
                                         /* Normal mode */
                                         IOPCTL_PIO_SLEW_RATE_NORMAL |
                                         /* Full drive enable */
                                         IOPCTL_PIO_FULLDRIVE_EN |
                                         /* Analog mux is disabled */
                                         IOPCTL_PIO_ANAMUX_DI |
                                         /* Pseudo Output Drain is disabled */
                                         IOPCTL_PIO_PSEDRAIN_DI |
                                         /* Input function is not inverted */
                                         IOPCTL_PIO_INV_DI);
    /* PORT0 PIN28 (coords: A6) is configured as FC4_SCK */
    IOPCTL_PinMuxSet(IOPCTL, 0U, 28U, port0_pin28_config);

    const uint32_t port0_pin29_config = (/* Pin is configured as FC4_TXD_SCL_MISO_WS */
                                         IOPCTL_PIO_FUNC1 |
                                         /* Disable pull-up / pull-down function */
                                         IOPCTL_PIO_PUPD_DI |
                                         /* Enable pull-down function */
                                         IOPCTL_PIO_PULLDOWN_EN |
                                         /* Enables input buffer function */
                                         IOPCTL_PIO_INBUF_EN |
                                         /* Normal mode */
                                         IOPCTL_PIO_SLEW_RATE_NORMAL |
                                         /* Full drive enable */
                                         IOPCTL_PIO_FULLDRIVE_EN |
                                         /* Analog mux is disabled */
                                         IOPCTL_PIO_ANAMUX_DI |
                                         /* Pseudo Output Drain is disabled */
                                         IOPCTL_PIO_PSEDRAIN_DI |
                                         /* Input function is not inverted */
                                         IOPCTL_PIO_INV_DI);
    /* PORT0 PIN29 (coords: B6) is configured as FC4_TXD_SCL_MISO_WS */
    IOPCTL_PinMuxSet(IOPCTL, 0U, 29U, port0_pin29_config);

    const uint32_t port0_pin30_config = (/* Pin is configured as FC4_RXD_SDA_MOSI_DATA */
                                         IOPCTL_PIO_FUNC1 |
                                         /* Disable pull-up / pull-down function */
                                         IOPCTL_PIO_PUPD_DI |
                                         /* Enable pull-down function */
                                         IOPCTL_PIO_PULLDOWN_EN |
                                         /* Enables input buffer function */
                                         IOPCTL_PIO_INBUF_EN |
                                         /* Normal mode */
                                         IOPCTL_PIO_SLEW_RATE_NORMAL |
                                         /* Full drive enable */
                                         IOPCTL_PIO_FULLDRIVE_EN |
                                         /* Analog mux is disabled */
                                         IOPCTL_PIO_ANAMUX_DI |
                                         /* Pseudo Output Drain is disabled */
                                         IOPCTL_PIO_PSEDRAIN_DI |
                                         /* Input function is not inverted */
                                         IOPCTL_PIO_INV_DI);
    /* PORT0 PIN30 (coords: C6) is configured as FC4_RXD_SDA_MOSI_DATA */
    IOPCTL_PinMuxSet(IOPCTL, 0U, 30U, port0_pin30_config);

    const uint32_t port0_pin7_config = (/* Pin is configured as FC1_SCK */
                                        IOPCTL_PIO_FUNC1 |
                                        /* Disable pull-up / pull-down function */
                                        IOPCTL_PIO_PUPD_DI |
                                        /* Enable pull-down function */
                                        IOPCTL_PIO_PULLDOWN_EN |
                                        /* Enables input buffer function */
                                        IOPCTL_PIO_INBUF_EN |
                                        /* Normal mode */
                                        IOPCTL_PIO_SLEW_RATE_NORMAL |
                                        /* Full drive enable */
                                        IOPCTL_PIO_FULLDRIVE_EN |
                                        /* Analog mux is disabled */
                                        IOPCTL_PIO_ANAMUX_DI |
                                        /* Pseudo Output Drain is disabled */
                                        IOPCTL_PIO_PSEDRAIN_DI |
                                        /* Input function is not inverted */
                                        IOPCTL_PIO_INV_DI);
    /* PORT0 PIN7 (coords: J15) is configured as FC1_SCK */
    IOPCTL_PinMuxSet(IOPCTL, 0U, 7U, port0_pin7_config);

    const uint32_t port0_pin8_config = (/* Pin is configured as FC1_TXD_SCL_MISO_WS */
                                        IOPCTL_PIO_FUNC1 |
                                        /* Disable pull-up / pull-down function */
                                        IOPCTL_PIO_PUPD_DI |
                                        /* Enable pull-down function */
                                        IOPCTL_PIO_PULLDOWN_EN |
                                        /* Disable input buffer function */
                                        IOPCTL_PIO_INBUF_DI |
                                        /* Normal mode */
                                        IOPCTL_PIO_SLEW_RATE_NORMAL |
                                        /* Normal drive */
                                        IOPCTL_PIO_FULLDRIVE_DI |
                                        /* Analog mux is disabled */
                                        IOPCTL_PIO_ANAMUX_DI |
                                        /* Pseudo Output Drain is disabled */
                                        IOPCTL_PIO_PSEDRAIN_DI |
                                        /* Input function is not inverted */
                                        IOPCTL_PIO_INV_DI);
    /* PORT0 PIN8 (coords: K16) is configured as FC1_TXD_SCL_MISO_WS */
    IOPCTL_PinMuxSet(IOPCTL, 0U, 8U, port0_pin8_config);

    const uint32_t port0_pin9_config = (/* Pin is configured as FC1_RXD_SDA_MOSI_DATA */
                                        IOPCTL_PIO_FUNC1 |
                                        /* Disable pull-up / pull-down function */
                                        IOPCTL_PIO_PUPD_DI |
                                        /* Enable pull-down function */
                                        IOPCTL_PIO_PULLDOWN_EN |
                                        /* Enables input buffer function */
                                        IOPCTL_PIO_INBUF_EN |
                                        /* Normal mode */
                                        IOPCTL_PIO_SLEW_RATE_NORMAL |
                                        /* Full drive enable */
                                        IOPCTL_PIO_FULLDRIVE_EN |
                                        /* Analog mux is disabled */
                                        IOPCTL_PIO_ANAMUX_DI |
                                        /* Pseudo Output Drain is disabled */
                                        IOPCTL_PIO_PSEDRAIN_DI |
                                        /* Input function is not inverted */
                                        IOPCTL_PIO_INV_DI);
    /* PORT0 PIN9 (coords: K15) is configured as FC1_RXD_SDA_MOSI_DATA */
    IOPCTL_PinMuxSet(IOPCTL, 0U, 9U, port0_pin9_config);

    const uint32_t port1_pin0_config = (/* Pin is configured as PIO1_0 */
                                        IOPCTL_PIO_FUNC0 |
                                        /* Enable pull-up / pull-down function */
                                        IOPCTL_PIO_PUPD_EN |
                                        /* Enable pull-up function */
                                        IOPCTL_PIO_PULLUP_EN |
                                        /* Disable input buffer function */
                                        IOPCTL_PIO_INBUF_DI |
                                        /* Normal mode */
                                        IOPCTL_PIO_SLEW_RATE_NORMAL |
                                        /* Normal drive */
                                        IOPCTL_PIO_FULLDRIVE_DI |
                                        /* Analog mux is disabled */
                                        IOPCTL_PIO_ANAMUX_DI |
                                        /* Pseudo Output Drain is disabled */
                                        IOPCTL_PIO_PSEDRAIN_DI |
                                        /* Input function is not inverted */
                                        IOPCTL_PIO_INV_DI);
    /* PORT1 PIN0 (coords: H4) is configured as PIO1_0 */
    IOPCTL_PinMuxSet(IOPCTL, 1U, 0U, port1_pin0_config);

    const uint32_t port1_pin10_config = (/* Pin is configured as MCLK */
                                         IOPCTL_PIO_FUNC1 |
                                         /* Disable pull-up / pull-down function */
                                         IOPCTL_PIO_PUPD_DI |
                                         /* Enable pull-down function */
                                         IOPCTL_PIO_PULLDOWN_EN |
                                         /* Disable input buffer function */
                                         IOPCTL_PIO_INBUF_DI |
                                         /* Normal mode */
                                         IOPCTL_PIO_SLEW_RATE_NORMAL |
                                         /* Full drive enable */
                                         IOPCTL_PIO_FULLDRIVE_EN |
                                         /* Analog mux is disabled */
                                         IOPCTL_PIO_ANAMUX_DI |
                                         /* Pseudo Output Drain is disabled */
                                         IOPCTL_PIO_PSEDRAIN_DI |
                                         /* Input function is not inverted */
                                         IOPCTL_PIO_INV_DI);
    /* PORT1 PIN10 (coords: F2) is configured as MCLK */
    IOPCTL_PinMuxSet(IOPCTL, 1U, 10U, port1_pin10_config);

    const uint32_t port4_pin3_config = (/* Pin is configured as FC7_CTS_SDA_SSEL0 */
                                        IOPCTL_PIO_FUNC1 |
                                        /* Enable pull-up / pull-down function */
                                        IOPCTL_PIO_PUPD_EN |
                                        /* Enable pull-up function */
                                        IOPCTL_PIO_PULLUP_EN |
                                        /* Enables input buffer function */
                                        IOPCTL_PIO_INBUF_EN |
                                        /* Normal mode */
                                        IOPCTL_PIO_SLEW_RATE_NORMAL |
                                        /* Normal drive */
                                        IOPCTL_PIO_FULLDRIVE_DI |
                                        /* Analog mux is disabled */
                                        IOPCTL_PIO_ANAMUX_DI |
                                        /* Pseudo Output Drain is disabled */
                                        IOPCTL_PIO_PSEDRAIN_DI |
                                        /* Input function is not inverted */
                                        IOPCTL_PIO_INV_DI);
    /* PORT4 PIN3 (coords: T3) is configured as FC7_CTS_SDA_SSEL0 */
    IOPCTL_PinMuxSet(IOPCTL, 4U, 3U, port4_pin3_config);

    const uint32_t port4_pin4_config = (/* Pin is configured as FC7_RTS_SCL_SSEL1 */
                                        IOPCTL_PIO_FUNC1 |
                                        /* Enable pull-up / pull-down function */
                                        IOPCTL_PIO_PUPD_EN |
                                        /* Enable pull-up function */
                                        IOPCTL_PIO_PULLUP_EN |
                                        /* Enables input buffer function */
                                        IOPCTL_PIO_INBUF_EN |
                                        /* Normal mode */
                                        IOPCTL_PIO_SLEW_RATE_NORMAL |
                                        /* Normal drive */
                                        IOPCTL_PIO_FULLDRIVE_DI |
                                        /* Analog mux is disabled */
                                        IOPCTL_PIO_ANAMUX_DI |
                                        /* Pseudo Output Drain is enabled */
                                        IOPCTL_PIO_PSEDRAIN_EN |
                                        /* Input function is not inverted */
                                        IOPCTL_PIO_INV_DI);
    /* PORT4 PIN4 (coords: R2) is configured as FC7_RTS_SCL_SSEL1 */
    IOPCTL_PinMuxSet(IOPCTL, 4U, 4U, port4_pin4_config);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitDebugConsolePins:
- options: {callFromInitBoot: 'true', coreID: cm33, enableClock: 'true'}
- pin_list:
  - {pin_num: H15, peripheral: FLEXCOMM0, signal: RXD_SDA_MOSI_DATA, pin_signal: PIO0_2/FC0_RXD_SDA_MOSI_DATA/CTIMER0_MAT2/I2S_BRIDGE_DATA_IN/SEC_PIO0_2, pupdena: disabled,
    pupdsel: pullDown, ibena: enabled, slew_rate: normal, drive: normal, amena: disabled, odena: disabled, iiena: disabled}
  - {pin_num: H16, peripheral: FLEXCOMM0, signal: TXD_SCL_MISO_WS, pin_signal: PIO0_1/FC0_TXD_SCL_MISO_WS/CTIMER0_MAT1/I2S_BRIDGE_WS_IN/SEC_PIO0_1, pupdena: disabled,
    pupdsel: pullDown, ibena: disabled, slew_rate: normal, drive: normal, amena: disabled, odena: disabled, iiena: disabled}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitDebugConsolePins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M33 */
void BOARD_InitDebugConsolePins(void)
{

    const uint32_t port0_pin1_config = (/* Pin is configured as FC0_TXD_SCL_MISO_WS */
                                        IOPCTL_PIO_FUNC1 |
                                        /* Disable pull-up / pull-down function */
                                        IOPCTL_PIO_PUPD_DI |
                                        /* Enable pull-down function */
                                        IOPCTL_PIO_PULLDOWN_EN |
                                        /* Disable input buffer function */
                                        IOPCTL_PIO_INBUF_DI |
                                        /* Normal mode */
                                        IOPCTL_PIO_SLEW_RATE_NORMAL |
                                        /* Normal drive */
                                        IOPCTL_PIO_FULLDRIVE_DI |
                                        /* Analog mux is disabled */
                                        IOPCTL_PIO_ANAMUX_DI |
                                        /* Pseudo Output Drain is disabled */
                                        IOPCTL_PIO_PSEDRAIN_DI |
                                        /* Input function is not inverted */
                                        IOPCTL_PIO_INV_DI);
    /* PORT0 PIN1 (coords: H16) is configured as FC0_TXD_SCL_MISO_WS */
    IOPCTL_PinMuxSet(IOPCTL, 0U, 1U, port0_pin1_config);

    const uint32_t port0_pin2_config = (/* Pin is configured as FC0_RXD_SDA_MOSI_DATA */
                                        IOPCTL_PIO_FUNC1 |
                                        /* Disable pull-up / pull-down function */
                                        IOPCTL_PIO_PUPD_DI |
                                        /* Enable pull-down function */
                                        IOPCTL_PIO_PULLDOWN_EN |
                                        /* Enables input buffer function */
                                        IOPCTL_PIO_INBUF_EN |
                                        /* Normal mode */
                                        IOPCTL_PIO_SLEW_RATE_NORMAL |
                                        /* Normal drive */
                                        IOPCTL_PIO_FULLDRIVE_DI |
                                        /* Analog mux is disabled */
                                        IOPCTL_PIO_ANAMUX_DI |
                                        /* Pseudo Output Drain is disabled */
                                        IOPCTL_PIO_PSEDRAIN_DI |
                                        /* Input function is not inverted */
                                        IOPCTL_PIO_INV_DI);
    /* PORT0 PIN2 (coords: H15) is configured as FC0_RXD_SDA_MOSI_DATA */
    IOPCTL_PinMuxSet(IOPCTL, 0U, 2U, port0_pin2_config);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: cm33, enableClock: 'true'}
- pin_list: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M33 */
void BOARD_InitPins(void)
{
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
