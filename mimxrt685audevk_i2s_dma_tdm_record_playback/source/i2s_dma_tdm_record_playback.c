/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdio.h>
#include "pin_mux.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_i2s_dma.h"
#include "fsl_codec_common.h"
#include "fsl_codec_adapter.h"
#include <stdbool.h>
#include "fsl_ak4458.h"
#include "fsl_gpio.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_I2S_MASTER_CLOCK_FREQUENCY CLOCK_GetMclkClkFreq()
#define DEMO_AUDIO_SAMPLE_RATE          (48000)
#define DEMO_AUDIO_PROTOCOL             kCODEC_BusTDM// kCODEC_BusI2S
#define DEMO_I2S_TX                     (I2S3)
#define DEMO_I2S_RX                     (I2S1)
#define DEMO_DMA                        (DMA0)
#define DEMO_I2S_TX_CHANNEL             (7)
#define DEMO_I2S_RX_CHANNEL             (2)
#define DEMO_I2S_CLOCK_DIVIDER          (24576000 / DEMO_AUDIO_SAMPLE_RATE / 32 / 8)
#define DEMO_I2S_TX_MODE                kI2S_MasterSlaveNormalMaster
#define DEMO_I2S_RX_MODE                kI2S_MasterSlaveNormalMaster
//#define DEMO_I2S_RX_MODE                kI2S_MasterSlaveNormalSlave
#define DEMO_CODEC_I2C_BASEADDR         I2C7
#define DEMO_CODEC_I2C_INSTANCE         7U  /*setting fc7-i2c*/
#define DEMO_TDM_DATA_START_POSITION    1U
#define BUFFER_SIZE   (1024U)
#define BUFFER_NUMBER (1U)

#define AK4588_PDN_PORT   1U
#define AK4588_PDN_PIN    0U
/* demo audio sample rate */
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void DEMO_InitCodec(void);
extern void BORAD_CodecReset(bool state);
/*******************************************************************************
 * Variables
 ******************************************************************************/
/*cs42448_config_t cs42448Config = {
    .DACMode      = kCS42448_ModeSlave,
    .ADCMode      = kCS42448_ModeSlave,
    .reset        = NULL,
    .master       = false,
    .i2cConfig    = {.codecI2CInstance = DEMO_CODEC_I2C_INSTANCE},
    .format       = {.sampleRate = 48000U, .bitWidth = 24U},
    .bus          = kCS42448_BusTDM,
    .slaveAddress = CS42448_I2C_ADDR,
};*/

ak4458_config_t ak4458Config = {
    .ak4458Mode   = kAK4458_PcmMode,
	.dataChannelMode = kAK4458_NormalMode,
	.pcmConfig    =	{.pcmSampleFreqMode= kAK4458_AutoSettingMode,.pcmSdataFormat=kAK4458_32BitI2S,.pcmTdmMode=kAK4458_TDM256,
	                 .pcmSdsSlot=kAK4458_L1234R1234},
	//.dsdConfig    =
	.slaveAddress = AK4458_I2C_ADDR,
    .i2cConfig    = {.codecI2CInstance = DEMO_CODEC_I2C_INSTANCE},
};
gpio_pin_config_t AK4458PDN_config = {
       kGPIO_DigitalOutput,
       0,
   };

codec_config_t boardCodecConfig = {.codecDevType = kCODEC_AK4458, .codecDevConfig = &ak4458Config};
AT_NONCACHEABLE_SECTION_ALIGN(static uint8_t Buffer[BUFFER_NUMBER * BUFFER_SIZE], 4);
static uint32_t tx_index = 0U, rx_index = 0U;
volatile uint32_t emptyBlock = BUFFER_NUMBER;
extern codec_config_t boardCodecConfig;
codec_handle_t codecHandle;
static i2s_config_t s_TxConfig;
static i2s_config_t s_RxConfig;
static i2s_dma_handle_t s_i2sTxHandle;
static i2s_dma_handle_t s_i2sRxHandle;
static dma_handle_t s_i2sTxDmaHandle;
static dma_handle_t s_i2sRxDmaHandle;
/*******************************************************************************
 * Code
 ******************************************************************************/
static void i2s_rx_Callback(I2S_Type *base, i2s_dma_handle_t *handle, status_t completionStatus, void *userData)
{
    emptyBlock--;
}

static void i2s_tx_Callback(I2S_Type *base, i2s_dma_handle_t *handle, status_t completionStatus, void *userData)
{
    emptyBlock++;
}

/*!
 * @brief Main function
 */
//test code
/*static void Delay(void)
{
    uint32_t i;
    for (i = 0; i < 2U; i++)
    {
        __NOP();
    }
}*/
int main(void)
{
    i2s_transfer_t xfer;

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();
    /*AK4588 PDN GPOI*/
    GPIO_PortInit(GPIO, AK4588_PDN_PORT);
    GPIO_PinInit(GPIO, AK4588_PDN_PORT, AK4588_PDN_PIN, &AK4458PDN_config);

    CLOCK_EnableClock(kCLOCK_InputMux);
    /* I2C */
    CLOCK_AttachClk(kFFRO_to_FLEXCOMM7);
    /* attach AUDIO PLL clock to FLEXCOMM1 (I2S3) tx*/
    CLOCK_AttachClk(kAUDIO_PLL_to_FLEXCOMM1);
    /* attach AUDIO PLL clock to FLEXCOMM2 (I2S2) rx*/
    CLOCK_AttachClk(kAUDIO_PLL_to_FLEXCOMM2);

    /* attach AUDIO PLL clock to MCLK */
    CLOCK_AttachClk(kAUDIO_PLL_to_MCLK_CLK);
    CLOCK_SetClkDiv(kCLOCK_DivMclkClk, 1);
    SYSCTL1->MCLKPINDIR = SYSCTL1_MCLKPINDIR_MCLKPINDIR_MASK;
   /*TEST SETTING - SET SHARED SIGANL SET 0: WS FROM FLEXCOMM1*/
  //  SYSCTL1->SHAREDCTRLSET[0] = SYSCTL1_SHAREDCTRLSET_SHAREDSCKSEL(2) |
  //  		SYSCTL1_SHAREDCTRLSET_SHAREDWSSEL(2);
   /*TEST SETTING - SET FLEXCOMM3 SCK,WS FORM SHARED SIGNAL SET 0*/
   // SYSCTL1->FCCTRLSEL[1] = SYSCTL1_FCCTRLSEL_SCKINSEL(1) | SYSCTL1_FCCTRLSEL_WSINSEL(1);
  //  cs42448Config.i2cConfig.codecI2CSourceClock = CLOCK_GetFlexCommClkFreq(2);
  //  cs42448Config.format.mclk_HZ                = CLOCK_GetMclkClkFreq();
    ak4458Config.i2cConfig.codecI2CSourceClock = CLOCK_GetFlexCommClkFreq(7);//FLEXCOMM7
  //  ak4458Config.pcmConfig.mclk_HZ                = CLOCK_GetMclkClkFreq();
    PRINTF("I2S TDM record playback example started!\n\r");


    /* i2s configurations */
    /*
     * masterSlave = kI2S_MasterSlaveNormalMaster;
     * mode = kI2S_ModeI2sClassic;
     * rightLow = false;
     * leftJust = false;
     * pdmData = false;
     * sckPol = false;
     * wsPol = false;
     * divider = 1;
     * oneChannel = false;
     * dataLength = 16;
     * frameLength = 32;
     * position = 0;
     * fifoLevel = 4;
     */
    I2S_TxGetDefaultConfig(&s_TxConfig);
    s_TxConfig.divider     = DEMO_I2S_CLOCK_DIVIDER;
    s_TxConfig.masterSlave = kI2S_MasterSlaveNormalMaster;
    s_TxConfig.mode        = kI2S_ModeDspWsShort;
  //  s_TxConfig.wsPol       = true;
    s_TxConfig.dataLength  = 32U;
    s_TxConfig.frameLength = 32 * 8U;
    s_TxConfig.position    = DEMO_TDM_DATA_START_POSITION;

    I2S_TxInit(DEMO_I2S_TX, &s_TxConfig);
    I2S_EnableSecondaryChannel(DEMO_I2S_TX, kI2S_SecondaryChannel1, false, 64 + DEMO_TDM_DATA_START_POSITION);
    I2S_EnableSecondaryChannel(DEMO_I2S_TX, kI2S_SecondaryChannel2, false, 128 + DEMO_TDM_DATA_START_POSITION);
    I2S_EnableSecondaryChannel(DEMO_I2S_TX, kI2S_SecondaryChannel3, false, 192 + DEMO_TDM_DATA_START_POSITION);

    /* i2s configurations */
    I2S_RxGetDefaultConfig(&s_RxConfig);
    s_RxConfig.divider     = DEMO_I2S_CLOCK_DIVIDER;
    s_RxConfig.masterSlave = kI2S_MasterSlaveNormalMaster;
  //  s_RxConfig.masterSlave = kI2S_MasterSlaveNormalSlave;
    s_RxConfig.mode        = kI2S_ModeDspWsShort;
    s_RxConfig.wsPol       = true;
    s_RxConfig.rightLow    = false;
	s_RxConfig.leftJust    = false;
    s_RxConfig.sckPol      = true;
    s_RxConfig.pack48      = true;
    s_RxConfig.oneChannel  = false;
    s_RxConfig.txEmptyZero = false;
    s_RxConfig.frameLength = 32 * 8U;
    s_RxConfig.dataLength  = 32U;
    s_RxConfig.position    = DEMO_TDM_DATA_START_POSITION;

    I2S_RxInit(DEMO_I2S_RX, &s_RxConfig);
    I2S_EnableSecondaryChannel(DEMO_I2S_RX, kI2S_SecondaryChannel1, false, 64 + DEMO_TDM_DATA_START_POSITION);
    I2S_EnableSecondaryChannel(DEMO_I2S_RX, kI2S_SecondaryChannel2, false, 128 + DEMO_TDM_DATA_START_POSITION);
    I2S_EnableSecondaryChannel(DEMO_I2S_RX, kI2S_SecondaryChannel3, false, 192 + DEMO_TDM_DATA_START_POSITION);

    DMA_Init(DEMO_DMA);

    DMA_EnableChannel(DEMO_DMA, DEMO_I2S_TX_CHANNEL);
    DMA_EnableChannel(DEMO_DMA, DEMO_I2S_RX_CHANNEL);
    DMA_SetChannelPriority(DEMO_DMA, DEMO_I2S_TX_CHANNEL, kDMA_ChannelPriority3);
    DMA_SetChannelPriority(DEMO_DMA, DEMO_I2S_RX_CHANNEL, kDMA_ChannelPriority2);
    DMA_CreateHandle(&s_i2sTxDmaHandle, DEMO_DMA, DEMO_I2S_TX_CHANNEL);
    DMA_CreateHandle(&s_i2sRxDmaHandle, DEMO_DMA, DEMO_I2S_RX_CHANNEL);

    I2S_TxTransferCreateHandleDMA(DEMO_I2S_TX, &s_i2sTxHandle, &s_i2sTxDmaHandle, i2s_tx_Callback, NULL);
    I2S_RxTransferCreateHandleDMA(DEMO_I2S_RX, &s_i2sRxHandle, &s_i2sRxDmaHandle, i2s_rx_Callback, NULL);

    /* codec initialization */
 //   DEMO_InitCodec();
//test code
    //reset ak4458
   // GPIO_PinWrite(GPIO, AK4588_PDN_PORT, AK4588_PDN_PIN, 1);
   // __NOP();
   // __NOP();
  //  __NOP();
  //  GPIO_PinWrite(GPIO, AK4588_PDN_PORT, AK4588_PDN_PIN, 0);


    PRINTF("Starting TDM record playback\n\r");

    while (1)
    {

        if (emptyBlock > 0)
        {

            xfer.data     = Buffer + rx_index * BUFFER_SIZE;
            xfer.dataSize = BUFFER_SIZE;
            if (kStatus_Success == I2S_RxTransferReceiveDMA(I2S2, &s_i2sRxHandle, xfer))
            {
                rx_index++;
            }
            if (rx_index == BUFFER_NUMBER)
            {
                rx_index = 0U;
            }
        }
        if (emptyBlock < BUFFER_NUMBER)
        {

            xfer.data     = Buffer + tx_index * BUFFER_SIZE;
            xfer.dataSize = BUFFER_SIZE;
            if (kStatus_Success == I2S_TxTransferSendDMA(I2S1, &s_i2sTxHandle, xfer))
            {
                tx_index++;
            }
            if (tx_index == BUFFER_NUMBER)
            {
                tx_index = 0U;
            }
        }
    }
}

static void DEMO_InitCodec(void)
{
    if (CODEC_Init(&codecHandle, &boardCodecConfig) != kStatus_Success)
    {
        PRINTF("CODEC_Init failed!\r\n");
        assert(false);
    }

    PRINTF("\r\nCodec Init Done.\r\n");
}
