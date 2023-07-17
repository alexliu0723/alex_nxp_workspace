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
#include "fsl_cs42448.h"
#include "music.h"
/*******************************************************************************
 * Definitions
 0 Flexcomm Interface 0 RX / I2C Slave [1] DMA_ITRIG_INMUX0
 1 Flexcomm Interface 0 TX / I2C Master [1] DMA_ITRIG_INMUX1
 2 Flexcomm Interface 1 RX / I2C Slave [1] DMA_ITRIG_INMUX2
 3 Flexcomm Interface 1 TX / I2C Master [1] DMA_ITRIG_INMUX3
 4 Flexcomm Interface 2 RX / I2C Slave [1] DMA_ITRIG_INMUX4
 5 Flexcomm Interface 2 TX / I2C Master [1] DMA_ITRIG_INMUX5
 6 Flexcomm Interface 3 RX / I2C Slave [1] DMA_ITRIG_INMUX6
 7 Flexcomm Interface 3 TX / I2C Master [1] DMA_ITRIG_INMUX7
 8 Flexcomm Interface 4 RX / I2C Slave [1] DMA_ITRIG_INMUX8
 9 Flexcomm Interface 4 TX / I2C Master [1] DMA_ITRIG_INMUX9
 10 Flexcomm Interface 5 RX / I2C Slave [1] DMA_ITRIG_INMUX10
 11 Flexcomm Interface 5 TX / I2C Master [1] DMA_ITRIG_INMUX11
 12 Flexcomm Interface 6 RX / I2C Slave [1] DMA_ITRIG_INMUX12
 13 Flexcomm Interface 6 TX / I2C Master [1] DMA_ITRIG_INMUX13
 14 Flexcomm Interface 7 RX / I2C Master [1] DMA_ITRIG_INMUX14
 15 Flexcomm Interface 7 TX / I2C Master [1] DMA_ITRIG_INMUX15
 ******************************************************************************/
//#define FC2
#define FC3
//#define mytest

#define DEMO_I2S_MASTER_CLOCK_FREQUENCY CLOCK_GetMclkClkFreq()
#define DEMO_AUDIO_SAMPLE_RATE          (48000)
#define DEMO_AUDIO_PROTOCOL             kCODEC_BusTDM//kCODEC_BusI2S
#define DEMO_I2S_TX                     (I2S1)
#define FC2_I2S_TX                      (I2S2)
#define FC3_I2S_RX                      (I2S3)
#define FC4_I2S_RX                      (I2S4)
#define FC5_I2S_RX                      (I2S5)
#define FC6_I2S_RX                      (I2S6)
#define DEMO_DMA                        (DMA0)
#define DEMO_I2S_TX_CHANNEL             (3)
#define FC2_I2S_TX_CHANNEL              (5)

#define FC3_I2S_RX_CHANNEL              (6)
#define FC4_I2S_RX_CHANNEL              (8)
#define FC5_I2S_RX_CHANNEL              (10)
#define FC6_I2S_RX_CHANNEL              (12)
#define DEMO_I2S_CLOCK_DIVIDER          (24576000 / DEMO_AUDIO_SAMPLE_RATE / 32 / 8)
#define DEMO_I2S_TX_MODE                kI2S_MasterSlaveNormalMaster
#define FC2_I2S_TX_MODE                 kI2S_MasterSlaveNormalMaster
#ifdef FC2
#define DEMO_I2S_RX_CHANNEL             (4)
#define DEMO_I2S_RX                     (I2S2)
#define DEMO_I2S_RX_MODE                kI2S_MasterSlaveNormalSlave
#endif
#ifdef mytest
#define DEMO_I2S_RX_MODE                kI2S_MasterSlaveNormalMaster
#endif
#define FC3_I2S_RX_MODE                 kI2S_MasterSlaveNormalSlave
#define FC4_I2S_RX_MODE                 kI2S_MasterSlaveNormalSlave
#define FC5_I2S_RX_MODE                 kI2S_MasterSlaveNormalSlave
#define FC6_I2S_RX_MODE                 kI2S_MasterSlaveNormalSlave

#define DEMO_CODEC_I2C_BASEADDR         I2C7
#define DEMO_CODEC_I2C_INSTANCE         7U
#define DEMO_TDM_DATA_START_POSITION    1U
#define BUFFER_SIZE   (1024U)
#define BUFFER_NUMBER (4U)


/* demo audio sample rate */
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void DEMO_InitCodec(void);
static void StartSoundPlayback(void);
extern void BORAD_CodecReset(bool state);
/*******************************************************************************
 * Variables
 ******************************************************************************/
cs42448_config_t cs42448Config = {
    .DACMode      = kCS42448_ModeSlave,
    .ADCMode      = kCS42448_ModeSlave,
    .reset        = NULL,
    .master       = false,
    .i2cConfig    = {.codecI2CInstance = DEMO_CODEC_I2C_INSTANCE},
    .format       = {.sampleRate = 48000U, .bitWidth = 24U},
    .bus          = kCS42448_BusTDM,
    .slaveAddress = CS42448_I2C_ADDR,
};

codec_config_t boardCodecConfig = {.codecDevType = kCODEC_CS42448, .codecDevConfig = &cs42448Config};
AT_NONCACHEABLE_SECTION_ALIGN(static uint8_t Buffer[BUFFER_NUMBER * BUFFER_SIZE], 4);
static uint32_t tx_index = 0U, rx_index = 0U;
volatile uint32_t emptyBlock = BUFFER_NUMBER;
extern codec_config_t boardCodecConfig;
codec_handle_t codecHandle;
static i2s_config_t s_TxConfig;
static i2s_config_t s_RxConfig;
static i2s_dma_handle_t s_i2sTxHandle[2];
static dma_handle_t s_i2sTxDmaHandle[2];
static i2s_transfer_t s_TxTransfer;
#ifdef FC2
//static dma_handle_t s_i2sRxDmaHandle;
//static i2s_dma_handle_t s_i2sRxHandle;
#endif
#ifdef FC3
static dma_handle_t s_i2sRxDmaHandle[4];
static i2s_dma_handle_t s_i2sRxHandle[4];
#endif
/*******************************************************************************
 * Code
 ******************************************************************************/
static void i2s_rx_Callback(I2S_Type *base, i2s_dma_handle_t *handle, status_t completionStatus, void *userData)
{
    emptyBlock--;
}
static void i2sf3_rx_Callback(I2S_Type *base, i2s_dma_handle_t *handle, status_t completionStatus, void *userData)
{
    emptyBlock--; //*4
}
static void i2s_tx_Callback(I2S_Type *base, i2s_dma_handle_t *handle, status_t completionStatus, void *userData)
{
    emptyBlock++; //+4
}
static void i2sfc2_tx_Callback(I2S_Type *base, i2s_dma_handle_t *handle, status_t completionStatus, void *userData)
{
	i2s_transfer_t *transfer = (i2s_transfer_t *)userData;
	I2S_TxTransferSendDMA(base, handle, *transfer);
}
//static void TxCallback(I2S_Type *base, i2s_dma_handle_t *handle, status_t completionStatus, void *userData)
/*!
 * @brief Main function
 */
int main(void)
{
    i2s_transfer_t xfer;

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    CLOCK_EnableClock(kCLOCK_InputMux);

    /* I2C */


    /* attach AUDIO PLL clock to FLEXCOMM1 (I2S1) */
    CLOCK_AttachClk(kAUDIO_PLL_to_FLEXCOMM1);
    CLOCK_AttachClk(kAUDIO_PLL_to_FLEXCOMM2);
    CLOCK_AttachClk(kAUDIO_PLL_to_FLEXCOMM3);
    CLOCK_AttachClk(kAUDIO_PLL_to_FLEXCOMM4);
    CLOCK_AttachClk(kAUDIO_PLL_to_FLEXCOMM5);
    CLOCK_AttachClk(kAUDIO_PLL_to_FLEXCOMM6);
    /* attach AUDIO PLL clock to MCLK */
    CLOCK_AttachClk(kAUDIO_PLL_to_MCLK_CLK);
    CLOCK_SetClkDiv(kCLOCK_DivMclkClk, 1);
    SYSCTL1->MCLKPINDIR = SYSCTL1_MCLKPINDIR_MCLKPINDIR_MASK;

    /* Set shared signal set 0: SCK, WS from Flexcomm3 */
    //SYSCTL1->SHAREDCTRLSET[0] = SYSCTL1_SHAREDCTRLSET_SHAREDSCKSEL(1) |  SYSCTL1_SHAREDCTRLSET_SHAREDWSSEL(1);


 //   cs42448Config.i2cConfig.codecI2CSourceClock = CLOCK_GetFlexCommClkFreq(2);
 //   cs42448Config.format.mclk_HZ                = CLOCK_GetMclkClkFreq();

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
    /*********************************************************************************/
    /********************* FC1 IS2 TX Configuration **********************************/
    /*********************************************************************************/
    I2S_TxGetDefaultConfig(&s_TxConfig);
    s_TxConfig.divider     = DEMO_I2S_CLOCK_DIVIDER;
    s_TxConfig.masterSlave = DEMO_I2S_TX_MODE;
    s_TxConfig.mode        = kI2S_ModeDspWsShort;
    s_TxConfig.dataLength  = 32U;
    s_TxConfig.frameLength = 32 * 8U;
    s_TxConfig.position    = DEMO_TDM_DATA_START_POSITION;
    s_TxConfig.pack48      = true;

    I2S_TxInit(DEMO_I2S_TX, &s_TxConfig);
    I2S_TxInit(FC2_I2S_TX, &s_TxConfig);
    I2S_EnableSecondaryChannel(DEMO_I2S_TX, kI2S_SecondaryChannel1, false, 64 + DEMO_TDM_DATA_START_POSITION);
    I2S_EnableSecondaryChannel(DEMO_I2S_TX, kI2S_SecondaryChannel2, false, 128 + DEMO_TDM_DATA_START_POSITION);
    I2S_EnableSecondaryChannel(DEMO_I2S_TX, kI2S_SecondaryChannel3, false, 192 + DEMO_TDM_DATA_START_POSITION);
    /*********************************************************************************/
    /********************* FC2 IS2 RX Configuration **********************************/
    /*********************************************************************************/
    /* i2s configurations */
#ifdef FC2
    I2S_RxGetDefaultConfig(&s_RxConfig);
    s_RxConfig.divider     = DEMO_I2S_CLOCK_DIVIDER;
    s_RxConfig.masterSlave = DEMO_I2S_RX_MODE;
    s_RxConfig.mode        = kI2S_ModeDspWsLong;

    s_RxConfig.dataLength  = 32U;
    s_RxConfig.frameLength = 32 * 8U;
    s_RxConfig.position    = DEMO_TDM_DATA_START_POSITION;
    s_TxConfig.pack48      = true;

    I2S_RxInit(DEMO_I2S_RX, &s_RxConfig);
    I2S_EnableSecondaryChannel(DEMO_I2S_RX, kI2S_SecondaryChannel1, false, 64 + DEMO_TDM_DATA_START_POSITION);
    I2S_EnableSecondaryChannel(DEMO_I2S_RX, kI2S_SecondaryChannel2, false, 128 + DEMO_TDM_DATA_START_POSITION);
    I2S_EnableSecondaryChannel(DEMO_I2S_RX, kI2S_SecondaryChannel3, false, 192 + DEMO_TDM_DATA_START_POSITION);

    DMA_EnableChannel(DEMO_DMA, DEMO_I2S_RX_CHANNEL);
    DMA_SetChannelPriority(DEMO_DMA, DEMO_I2S_RX_CHANNEL, kDMA_ChannelPriority2);
    DMA_CreateHandle(&s_i2sRxDmaHandle[4], DEMO_DMA, DEMO_I2S_RX_CHANNEL);
    I2S_RxTransferCreateHandleDMA(DEMO_I2S_RX, &s_i2sRxHandle[4], &s_i2sRxDmaHandle[4], i2s_rx_Callback, NULL);

 /*   DMA_Init(DEMO_DMA);
	DMA_EnableChannel(DEMO_DMA, DEMO_I2S_TX_CHANNEL);
	DMA_SetChannelPriority(DEMO_DMA, DEMO_I2S_TX_CHANNEL, kDMA_ChannelPriority3);
	DMA_CreateHandle(&s_i2sTxDmaHandle, DEMO_DMA, DEMO_I2S_TX_CHANNEL);
	I2S_TxTransferCreateHandleDMA(DEMO_I2S_TX, &s_i2sTxHandle, &s_i2sTxDmaHandle, i2s_tx_Callback, NULL);*/
#endif
#ifdef FC3
    /*********************************************************************************/
    /********************* FC3 IS2 RX Configuration **********************************/
    /*********************************************************************************/
    /* i2s configurations */
	I2S_RxGetDefaultConfig(&s_RxConfig);
	s_RxConfig.divider     = DEMO_I2S_CLOCK_DIVIDER;
	s_RxConfig.masterSlave = FC3_I2S_RX_MODE;
	s_RxConfig.mode        = kI2S_ModeDspWsShort;//I2S_ModeDspWsLong;
	s_RxConfig.dataLength  = 32U;
	s_RxConfig.frameLength = 32 * 8U;
	s_RxConfig.position    = DEMO_TDM_DATA_START_POSITION;
	s_TxConfig.pack48      = true;

	I2S_RxInit(FC3_I2S_RX, &s_RxConfig);
	I2S_RxInit(FC4_I2S_RX, &s_RxConfig);
//	I2S_RxInit(FC5_I2S_RX, &s_RxConfig);
//	I2S_RxInit(FC6_I2S_RX, &s_RxConfig);

	I2S_EnableSecondaryChannel(FC4_I2S_RX, kI2S_SecondaryChannel1, false, 64 + DEMO_TDM_DATA_START_POSITION);
//	I2S_EnableSecondaryChannel(FC5_I2S_RX, kI2S_SecondaryChannel2, false, 128 + DEMO_TDM_DATA_START_POSITION);
//	I2S_EnableSecondaryChannel(FC6_I2S_RX, kI2S_SecondaryChannel3, false, 192 + DEMO_TDM_DATA_START_POSITION);

    DMA_EnableChannel(DEMO_DMA, FC3_I2S_RX_CHANNEL);
    DMA_SetChannelPriority(DEMO_DMA, FC3_I2S_RX_CHANNEL, kDMA_ChannelPriority3);
    DMA_CreateHandle(&s_i2sRxDmaHandle[0], DEMO_DMA, FC3_I2S_RX_CHANNEL);
    I2S_RxTransferCreateHandleDMA(FC3_I2S_RX, &s_i2sRxHandle[0], &s_i2sRxDmaHandle[0], i2sf3_rx_Callback, NULL);

    DMA_EnableChannel(DEMO_DMA, FC4_I2S_RX_CHANNEL);
	DMA_SetChannelPriority(DEMO_DMA, FC4_I2S_RX_CHANNEL, kDMA_ChannelPriority3);
	DMA_CreateHandle(&s_i2sRxDmaHandle[1], DEMO_DMA, FC4_I2S_RX_CHANNEL);
	I2S_RxTransferCreateHandleDMA(FC4_I2S_RX, &s_i2sRxHandle[1], &s_i2sRxDmaHandle[1], i2sf3_rx_Callback, NULL);


	DMA_Init(DEMO_DMA);
	DMA_EnableChannel(DEMO_DMA, DEMO_I2S_TX_CHANNEL);
	DMA_SetChannelPriority(DEMO_DMA, DEMO_I2S_TX_CHANNEL, kDMA_ChannelPriority5);
	DMA_CreateHandle(&s_i2sTxDmaHandle[0], DEMO_DMA, DEMO_I2S_TX_CHANNEL);
	I2S_TxTransferCreateHandleDMA(DEMO_I2S_TX, &s_i2sTxHandle[0], &s_i2sTxDmaHandle[0], i2s_tx_Callback, NULL);

	DMA_EnableChannel(DEMO_DMA, FC2_I2S_TX_CHANNEL);
	DMA_SetChannelPriority(DEMO_DMA, FC2_I2S_TX_CHANNEL, kDMA_ChannelPriority2);
	DMA_CreateHandle(&s_i2sTxDmaHandle[1], DEMO_DMA, FC2_I2S_TX_CHANNEL);
	//I2S_TxTransferCreateHandleDMA(FC2_I2S_TX, &s_i2sTxHandle[1], &s_i2sTxDmaHandle[1], i2sfc2_tx_Callback, NULL);

	StartSoundPlayback();


	while(1)
    {


    	 if (emptyBlock > 0)
		{
			xfer.data     = Buffer + rx_index * BUFFER_SIZE;
			xfer.dataSize = BUFFER_SIZE;
			if (kStatus_Success == I2S_RxTransferReceiveDMA(FC3_I2S_RX, &s_i2sRxHandle[0], xfer))
			{
				rx_index++;
			}
		    if (kStatus_Success == I2S_RxTransferReceiveDMA(FC4_I2S_RX, &s_i2sRxHandle[1], xfer))
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
			if (kStatus_Success == I2S_TxTransferSendDMA(DEMO_I2S_TX, &s_i2sTxHandle[0], xfer))
			{
				tx_index++;
			}
			if (tx_index == BUFFER_NUMBER)
			{
				tx_index = 0U;
			}
		}
    }

#endif


    /* codec initialization */
  //  DEMO_InitCodec();
#ifdef FC2
    PRINTF("Starting TDM record playback\n\r");

    while (1)
    {
        if (emptyBlock > 0)
        {
            xfer.data     = Buffer + rx_index * BUFFER_SIZE;
            xfer.dataSize = BUFFER_SIZE;
            if (kStatus_Success == I2S_RxTransferReceiveDMA(DEMO_I2S_RX, &s_i2sRxHandle, xfer))
           // if (kStatus_Success == I2S_RxTransferReceiveDMA(FC3_I2S_RX, &s_i2sRxHandle, xfer))
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
            if (kStatus_Success == I2S_TxTransferSendDMA(DEMO_I2S_TX, &s_i2sTxHandle, xfer))
            {
                tx_index++;
            }
            if (tx_index == BUFFER_NUMBER)
            {
                tx_index = 0U;
            }
        }
    }
    #endif
}
static void StartSoundPlayback(void)
{
	PRINTF("Setup looping playback of sine wave\r\n");

	    s_TxTransfer.data     = &g_Music[0];
	    s_TxTransfer.dataSize = sizeof(g_Music);
	    I2S_TxTransferCreateHandleDMA(FC2_I2S_TX, &s_i2sTxHandle[1], &s_i2sTxDmaHandle[1], i2sfc2_tx_Callback,(void *)&s_TxTransfer);
	    /* need to queue two transmit buffers so when the first one
	     * finishes transfer, the other immediatelly starts */
	    I2S_TxTransferSendDMA(FC2_I2S_TX, &s_i2sTxHandle[1], s_TxTransfer);
	    I2S_TxTransferSendDMA(FC2_I2S_TX, &s_i2sTxHandle[1], s_TxTransfer);
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
