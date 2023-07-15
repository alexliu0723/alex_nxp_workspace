/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_i2c.h"
#include "fsl_i2s.h"
#include "music.h"
#include "fsl_codec_common.h"
#include <stdbool.h>
#include "fsl_codec_adapter.h"
#include "fsl_cs42448.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_I2S_MASTER_CLOCK_FREQUENCY CLOCK_GetMclkClkFreq()
#define DEMO_AUDIO_BIT_WIDTH            (32)
#define DEMO_AUDIO_SAMPLE_RATE          (48000)
#define DEMO_AUDIO_PROTOCOL             kCODEC_BusTDM
#define DEMO_I2S_TX                     (I2S1)
#define DEMO_I2S_RX                     (I2S2)
#define DEMO_I2S_CLOCK_DIVIDER          (24576000 / DEMO_AUDIO_SAMPLE_RATE / 32 / 8)
#define DEMO_I2S_TX_MODE                kI2S_MasterSlaveNormalMaster
#define DEMO_I2S_RX_MODE                kI2S_MasterSlaveNormalSlave//
//#define DEMO_I2S_RX_MODE                        kI2S_MasterSlaveNormalMaster
#define BUFFER_SIZE   (1024U)
#define BUFFER_NUMBER (4U)

#define DEMO_CODEC_VOLUME               100U
#ifndef DEMO_CODEC_VOLUME
#define DEMO_CODEC_VOLUME 30U
#endif
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static void StartDigitalLoopback(void);

static void TxCallback(I2S_Type *base, i2s_handle_t *handle, status_t completionStatus, void *userData);

static void RxCallback(I2S_Type *base, i2s_handle_t *handle, status_t completionStatus, void *userData);

/*******************************************************************************
 * Variables
 ******************************************************************************/
cs42448_config_t cs42448Config = {
    .DACMode      = kCS42448_ModeSlave,
    .ADCMode      = kCS42448_ModeSlave,
    .reset        = NULL,
    .master       = false,
    .i2cConfig    = {.codecI2CInstance = BOARD_CODEC_I2C_INSTANCE},
    .format       = {.sampleRate = 48000U, .bitWidth = 16U},
    .bus          = kCS42448_BusI2S,
    .slaveAddress = CS42448_I2C_ADDR,
};

codec_config_t boardCodecConfig = {.codecDevType = kCODEC_CS42448, .codecDevConfig = &cs42448Config};
AT_NONCACHEABLE_SECTION_ALIGN(static uint8_t Buffer[BUFFER_NUMBER * BUFFER_SIZE], 4);
volatile uint32_t emptyBlock = BUFFER_NUMBER;

/*using 100 sample input and output ping-pong buffers, which give ~2ms end-to-end latency.*/
__ALIGN_BEGIN static uint8_t s_Buffer[400] __ALIGN_END; /* 100 samples => time about 2 ms */
static i2s_config_t s_TxConfig;
static i2s_config_t s_RxConfig;
static i2s_handle_t s_TxHandle;
static i2s_handle_t s_RxHandle;
static i2s_transfer_t s_TxTransfer;
static i2s_transfer_t s_RxTransfer;
extern codec_config_t boardCodecConfig;
codec_handle_t codecHandle;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Main function
 */
int main(void)
{
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    CLOCK_EnableClock(kCLOCK_InputMux);

    /* I2C */

    /* attach AUDIO PLL clock to FLEXCOMM1 (I2S2) */
    CLOCK_AttachClk(kAUDIO_PLL_to_FLEXCOMM2);
    /* attach AUDIO PLL clock to FLEXCOMM1 (I2S1) */
    CLOCK_AttachClk(kAUDIO_PLL_to_FLEXCOMM1);
    /* attach AUDIO PLL clock to FLEXCOMM3 (I2S3) */
    CLOCK_AttachClk(kAUDIO_PLL_to_FLEXCOMM3);

    /* attach AUDIO PLL clock to MCLK */
    CLOCK_AttachClk(kAUDIO_PLL_to_MCLK_CLK);
    CLOCK_SetClkDiv(kCLOCK_DivMclkClk, 1);
    SYSCTL1->MCLKPINDIR = SYSCTL1_MCLKPINDIR_MCLKPINDIR_MASK;

   // cs42448Config.i2cConfig.codecI2CSourceClock = CLOCK_GetFlexCommClkFreq(2);
   // cs42448Config.format.mclk_HZ                = CLOCK_GetMclkClkFreq();

    PRINTF("Configure codec\r\n");

    /* protocol: i2s
     * sampleRate: 48K
     * bitwidth:16
     */
  //  if (CODEC_Init(&codecHandle, &boardCodecConfig) != kStatus_Success)
  //  {
  //      PRINTF("codec_Init failed!\r\n");
 //       assert(false);
  //  }

    /* Initial volume kept low for hearing safety.
     * Adjust it to your needs, 0-100, 0 for mute, 100 for maximum volume.
     */
//    if (CODEC_SetVolume(&codecHandle, kCODEC_PlayChannelHeadphoneLeft | kCODEC_PlayChannelHeadphoneRight,
 //                       DEMO_CODEC_VOLUME) != kStatus_Success)
 //   {
 //       assert(false);
 //   }
//
 //   PRINTF("Configure I2S\r\n");

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
     * watermark = 4;
     * txEmptyZero = true;
     * pack48 = false;
     */
    I2S_TxGetDefaultConfig(&s_TxConfig);
    s_TxConfig.divider     = DEMO_I2S_CLOCK_DIVIDER;
    s_TxConfig.masterSlave = DEMO_I2S_TX_MODE;
    s_TxConfig.mode        = kI2S_ModeDspWsShort;
    s_TxConfig.dataLength  = 32U;
    s_TxConfig.frameLength = 32 * 8U;
    s_TxConfig.pack48      = true;
    s_TxConfig.position    = 1U;
    s_TxConfig.wsPol       = false;

    I2S_TxInit(DEMO_I2S_TX, &s_TxConfig);
    I2S_EnableSecondaryChannel(DEMO_I2S_TX, kI2S_SecondaryChannel1, false, 64 + 1);
    I2S_EnableSecondaryChannel(DEMO_I2S_TX, kI2S_SecondaryChannel2, false, 128 + 1);
    I2S_EnableSecondaryChannel(DEMO_I2S_TX, kI2S_SecondaryChannel3, false, 192 + 1);
    /*
     * masterSlave = kI2S_MasterSlaveNormalSlave;
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
     * watermark = 4;
     * txEmptyZero = false;
     * pack48 = false;
     */
    I2S_RxGetDefaultConfig(&s_RxConfig);
    s_RxConfig.divider     = DEMO_I2S_CLOCK_DIVIDER;
    s_RxConfig.masterSlave = DEMO_I2S_RX_MODE;
    s_RxConfig.mode        = kI2S_ModeDspWsLong;//kI2S_ModeDspWsShort;
	s_RxConfig.dataLength  = 32U;
	s_RxConfig.frameLength = 32 * 8U;
	s_RxConfig.pack48      = true;
	s_RxConfig.position    = 1U;

    I2S_RxInit(DEMO_I2S_RX, &s_RxConfig);
	I2S_EnableSecondaryChannel(DEMO_I2S_RX, kI2S_SecondaryChannel1, false, 64 + 1);
	I2S_EnableSecondaryChannel(DEMO_I2S_RX, kI2S_SecondaryChannel2, false, 128 + 1);
	I2S_EnableSecondaryChannel(DEMO_I2S_RX, kI2S_SecondaryChannel3, false, 192 + 1);

    StartDigitalLoopback();

    while (1)
    {
    }
}

static void StartDigitalLoopback(void)
{
    PRINTF("Setup digital loopback\r\n");

    s_RxTransfer.data     = &s_Buffer[0];
    s_RxTransfer.dataSize = sizeof(s_Buffer);
    s_TxTransfer.data     = &s_Buffer[0];
	s_TxTransfer.dataSize = sizeof(s_Buffer);

    I2S_RxTransferCreateHandle(DEMO_I2S_RX, &s_RxHandle, RxCallback, (void *)&s_RxTransfer);
    I2S_TxTransferCreateHandle(DEMO_I2S_TX, &s_TxHandle, TxCallback, (void *)&s_TxTransfer);

    I2S_RxTransferNonBlocking(DEMO_I2S_RX, &s_RxHandle, s_RxTransfer);
    I2S_TxTransferNonBlocking(DEMO_I2S_TX, &s_TxHandle, s_TxTransfer);

   // xfer.data     = Buffer + rx_index * BUFFER_SIZE;
   // xfer.dataSize = BUFFER_SIZE;

}

static void TxCallback(I2S_Type *base, i2s_handle_t *handle, status_t completionStatus, void *userData)
{
    /* Enqueue the same original s_Buffer all over again */
    i2s_transfer_t *transfer = (i2s_transfer_t *)userData;
    I2S_TxTransferNonBlocking(base, handle, *transfer);
}

static void RxCallback(I2S_Type *base, i2s_handle_t *handle, status_t completionStatus, void *userData)
{
    /* Enqueue the same original s_Buffer all over again */
    i2s_transfer_t *transfer = (i2s_transfer_t *)userData;
    I2S_RxTransferNonBlocking(base, handle, *transfer);
}
