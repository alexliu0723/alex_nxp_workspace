/*
 * fsl_ak5558.c
 *
 *  Created on: 2023年6月5日
 *      Author: Alex.Liu
 */
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
static void Delay(void)
{
    uint32_t i;
    for (i = 0; i < 1000U; i++)
    {
        __NOP();
    }
}

void AK5558_DefaultConfig(AK5558_config_t *config)
{
    config->AK5558Mode      = kAK5558_PcmMode;
   // config->dataChannelMode = kAK5558_NormalMode;
    /* PCM mode setting. */
    config->pcmConfig.pcmSdataFormat    = kAK5558_32BitI2S;
    config->pcmConfig.pcmTdmMode        = kAK5558_Normal;
    config->pcmConfig.pcmSdsSlot        = kAK5558_CH87654321;
    /* DSD mode setting. */
    config->dsdConfig.dsdMclk         = kAK5558_mclk512fs;
    config->dsdConfig.dsdDclkPolarity = kAK5558_FallingEdge;
}
status_t AK5558_Init(AK5558_handle_t *handle, AK5558_config_t *config)
{
    assert(handle != NULL);
    assert(config != NULL);
    status_t ret = kStatus_Success;

    handle->config = config;

    /* i2c bus initialization */
    if (CODEC_I2C_Init(handle->i2cHandle, config->i2cConfig.codecI2CInstance, AK5558_I2C_BITRATE,
                       config->i2cConfig.codecI2CSourceClock) != (status_t)kStatus_HAL_I2cSuccess)
    {
        return kStatus_Fail;
    }
    /************************************/
    ret = AK5558_ModifyReg(handle, AK5558_CONTROL1, AK5558_PM2_RSTN_MASK,
                              1U << AK5558_PM2_RSTN_MASK);

    ret = AK5558_ModifyReg(handle, AK5558_CONTROL1,
                           AK5558_CONTROL1_DIF0_MASK | AK5558_CONTROL1_DIF1_MASK ,
                           (uint8_t)config->pcmConfig.pcmSdataFormat << AK5558_CONTROL1_DIF0_SHIFT);
  //  ret = AK5558_ModifyReg(handle, AK5558_CONTROL3, AK5558_CONTROL3_SELLR1_MASK,
  //                         (uint8_t)config->dataChannelMode << AK5558_CONTROL3_SELLR1_SHIFT);
    /* PCM mode*/
   /* if (config->AK5558Mode == kAK5558_PcmMode)
    {
        if (config->pcmConfig.pcmSampleFreqMode != kAK5558_ManualSettingMode)
        {
            if (config->pcmConfig.pcmSampleFreqMode == kAK5558_AutoSettingMode)
            {
                ret = AK5558_ModifyReg(handle, AK5558_CONTROL1, AK5558_CONTROL1_ACKS_MASK,
                                       1U << AK5558_CONTROL1_ACKS_SHIFT);/*Auto setting mode*/
/*            }
            else
            {
              // 4458 auto setting mode, manual setting mode
                ret = AK5558_ModifyReg(handle, AK5558_CONTROL1, AK5558_CONTROL1_ACKS_MASK,
                                       0U << AK5558_CONTROL1_ACKS_SHIFT);/*manual setting mode*/
  //          }
 //       }
        ret = AK5558_ModifyReg(handle, AK5558_CONTROL2, AK5558_CONTROL2_TDM0_MASK | AK5558_CONTROL2_TDM1_MASK,
                               (uint8_t)config->pcmConfig.pcmTdmMode << AK5558_CONTROL2_TDM0_SHIFT);
        ret = AK5558_ModifyReg(handle, AK5558_PM2, AK5558_PM2_MONO0_MASK |AK5558_PM2_MONO1_MASK ,
                               ((uint8_t)config->pcmConfig.pcmSdsSlot & 0x1U) << AK5558_PM2_MONO0_SHIFT);
 //       ret = AK5558_ModifyReg(handle, AK5558_CONTROL6, AK5558_CONTROL6_SDS1_MASK,
 //                              (((uint8_t)config->pcmConfig.pcmSdsSlot & 0x2U) >> 1U) << AK5558_CONTROL6_SDS1_SHIFT);
 //       ret = AK5558_ModifyReg(handle, AK5558_CONTROL7, AK5558_CONTROL6_SDS2_MASK,
 //                              (((uint8_t)config->pcmConfig.pcmSdsSlot & 0x4U) >> 2U) << AK5558_CONTROL6_SDS2_SHIFT);
 //   }

 //   else if (config->AK5558Mode == kAK5558_DsdMode) /*DSD mode*/
 //   {

  /*      ret = AK5558_ModifyReg(handle, AK5558_CONTROL3, AK5558_CONTROL3_DP_MASK, 1U << AK5558_CONTROL3_DP_SHIFT);
        ret = AK5558_ModifyReg(handle, AK5558_CONTROL3, AK5558_CONTROL3_DCKS_MASK,
                               (uint8_t)config->dsdConfig.dsdMclk << AK5558_CONTROL3_DCKS_SHIFT);

        ret = AK5558_ModifyReg(handle, AK5558_DSD1, AK5558_DSD1_DSDD_MASK,
                               (uint8_t)config->dsdConfig.dsdPlaybackPath << AK5558_DSD1_DSDD_SHIFT);
        ret = AK5558_ModifyReg(handle, AK5558_DSD1, AK5558_DSD1_DDM_MASK,
                               (uint8_t)config->dsdConfig.dsdDataMute << AK5558_DSD1_DDM_SHIFT);
        ret = AK5558_ModifyReg(handle, AK5558_CONTROL3, AK5558_CONTROL3_DCKB_MASK,
                               (uint8_t)config->dsdConfig.dsdDclkPolarity << AK5558_CONTROL3_DCKB_SHIFT);*/
 //   }
 //   ret = AK5558_ModifyReg(handle, AK5558_CONTROL2, AK5558_CONTROL2_SMUTE_MASK,
 //                          0U << AK5558_CONTROL2_SMUTE_SHIFT); /* Normal Operation */

    ret = AK5558_ModifyReg(handle, AK5558_PW2, AK5558_PW2_RSTN_MASK,
                           0U << AK5558_PW2_RSTN_SHIFT); /* Rest the AK5558 */
    Delay(); /* Need to wait to ensure the AK5558 has updated the above registers. */
    ret = AK5558_ModifyReg(handle, AK5558_PW2, AK5558_PW_RSTN_MASK,
                           1U << AK5558_PW2_RSTN_SHIFT); /* Normal Operation */
    Delay();

    return ret;
}
status_t AK5558_SetEncoding(AK5558_handle_t *handle, uint8_t format)
{
    AK5558_config_t *config = (AK5558_config_t *)handle->config;
    status_t ret            = kStatus_Success;

    if (format == (uint8_t)kAK5558_DsdMode)
    {

 /*       ret = AK5558_ModifyReg(handle, AK5558_CONTROL3, AK5558_CONTROL3_DP_MASK, 1U << AK5558_CONTROL3_DP_SHIFT);
        ret = AK5558_ModifyReg(handle, AK5558_CONTROL3, AK5558_CONTROL3_DCKS_MASK,
                               (uint8_t)config->dsdConfig.dsdMclk << AK5558_CONTROL3_DCKS_SHIFT);

        ret = AK5558_ModifyReg(handle, AK5558_DSD1, AK5558_DSD1_DSDD_MASK,
                               (uint8_t)config->dsdConfig.dsdPlaybackPath << AK5558_DSD1_DSDD_SHIFT);
        ret = AK5558_ModifyReg(handle, AK5558_DSD1, AK5558_DSD1_DDM_MASK,
                               (uint8_t)config->dsdConfig.dsdDataMute << AK5558_DSD1_DDM_SHIFT);
        ret = AK5558_ModifyReg(handle, AK5558_CONTROL3, AK5558_CONTROL3_DCKB_MASK,
                               (uint8_t)config->dsdConfig.dsdDclkPolarity << AK5558_CONTROL3_DCKB_SHIFT);
        config->AK5558Mode = kAK5558_DsdMode;*/
    }

    if (format == (uint8_t)kAK5558_PcmMode)
    {
/*        ret = AK5558_ModifyReg(handle, AK5558_CONTROL7, AK5558_CONTROL6_TDM0_MASK | AK5558_CONTROL6_TDM1_MASK,
                               (uint8_t)config->pcmConfig.pcmTdmMode << AK5558_CONTROL6_TDM0_SHIFT);
        ret = AK5558_ModifyReg(handle, AK5558_CONTROL7, AK5558_CONTROL7_SDS0_MASK,
                               ((uint8_t)config->pcmConfig.pcmSdsSlot & 0x1U) << AK5558_CONTROL7_SDS0_SHIFT);
        ret = AK5558_ModifyReg(handle, AK5558_CONTROL6, AK5558_CONTROL6_SDS1_MASK,
                               (((uint8_t)config->pcmConfig.pcmSdsSlot & 0x2U) >> 1U) << AK5558_CONTROL6_SDS1_SHIFT);
        ret = AK5558_ModifyReg(handle, AK5558_CONTROL6, AK5558_CONTROL6_SDS2_MASK,
                               (((uint8_t)config->pcmConfig.pcmSdsSlot & 0x4U) >> 2U) << AK5558_CONTROL6_SDS2_SHIFT);

        ret = AK5558_ModifyReg(handle, AK5558_CONTROL3, AK5558_CONTROL3_DP_MASK, 0U << AK5558_CONTROL3_DP_SHIFT);

        config->AK5558Mode = kAK5558_PcmMode;*/
    }

    return ret;
}
status_t AK5558_ConfigDataFormat(AK5558_handle_t *handle, uint32_t mclk, uint32_t sampleRate, uint32_t bitWidth)
{
    AK5558_pcm_samplefreqselect_t samplefreq;
    AK5558_dsd_dclk_t dsdsel;
    AK5558_pcm_sdata_format_t sdataFormat;
    AK5558_config_t *config = (AK5558_config_t *)handle->config;
    status_t ret            = kStatus_Success;

    if (config->AK5558Mode == kAK5558_DsdMode)
    {
        switch (sampleRate * bitWidth)
        {
            case 2048000U:
            case 2822400U:
            case 3072000U:
                dsdsel = kAK5558_dclk64fs;
                break;
            case 4096000U:
            case 5644800U:
            case 6144000U:
                dsdsel = kAK5558_dclk128fs;
                break;
            case 8192000U:
            case 11289600U:
            case 12288000U:
                dsdsel = kAK5558_dclk256fs;
                break;
            case 16284000U:
            case 22579200U:
            case 24576000U:
                break;
            default:
                ret = kStatus_Fail;
                break;
        }

        if (ret != kStatus_Success)
        {
            return ret;
        }

        ret = AK5558_ModifyReg(handle, AK5558_DSD, AK5558_DSD_DSDSEL0_MASK,
                               ((uint8_t)dsdsel & 0x1U) << AK5558_DSD_DSDSEL0_SHIFT); /* Set DSDSEL0 */
        ret = AK5558_ModifyReg(handle, AK5558_DSD, AK5558_DSD_DSDSEL1_MASK,
                               (((uint8_t)dsdsel & 0x2U) >> 1U) << AK5558_DSD_DSDSEL1_SHIFT); /* Set DSDSEL1 */
    }
    else /* PCM mode */
    {
        switch (sampleRate)
        {
            case 8000U:
            case 11025U:
            case 16000U:
            case 22050U:
            case 32000U:
            case 44100U:
            case 48000U:
                samplefreq = kAK5558_NormalSpeed;
                break;
            case 88200U:
            case 96000U:
                samplefreq = kAK5558_DoubleSpeed;
                break;
            case 176400U:
            case 192000U:
                samplefreq = kAK5558_QuadSpeed;
                break;
            case 352800U:
            case 384000U:
                samplefreq = kAK5558_OctSpeed;
                break;
            case 705600U:
            case 768000U:
                samplefreq = kAK5558_HexSpeed;
                break;
            default:
                ret = kStatus_Fail;
                break;
        }

        if (ret != kStatus_Success)
        {
            return ret;
        }

        switch (bitWidth)
        {
            case 16U:
            case 24U:
                sdataFormat = kAK5558_24BitI2S;
                break;
            case 32U:
                sdataFormat = kAK5558_32BitI2S;
                break;
            default:
                ret = kStatus_Fail;
                break;
        }

        if (ret != kStatus_Success)
        {
            return ret;
        }
     /*等要用在補*/
     //   ret = AK5558_ModifyReg(handle, AK5558_CONTROL2, AK5558_CONTROL2_DFS0_MASK | AK5558_CONTROL2_DFS1_MASK,
     //                          ((uint8_t)samplefreq & 0x3U) << AK5558_CONTROL2_DFS0_SHIFT); /* Set DFS[1:0] */
     //   ret = AK5558_ModifyReg(handle, AK5558_CONTROL4, AK5558_CONTROL4_DFS2_MASK | AK5558_CONTROL4_DFS2_MASK,
     //                          (((uint8_t)samplefreq & 0x4U) >> 2U) << AK5558_CONTROL4_DFS2_SHIFT); /* Set DFS[2] */
     //   ret = AK5558_ModifyReg(handle, AK5558_CONTROL1,AK5558_CONTROL1_DIF0_MASK | AK5558_CONTROL1_DIF1_MASK | AK5558_CONTROL1_DIF2_MASK,
     //                          (uint8_t)sdataFormat << AK5558_CONTROL1_DIF0_SHIFT);
    }

    ret = AK5558_ModifyReg(handle, AK5558_PW2, AK5558_PW2_RSTN_MASK,
                           0U << AK5558_PW2_RSTN_SHIFT); /* Rest the AK5558 */

    Delay();

    ret = AK5558_ModifyReg(handle, AK5558_PW2, AK5558_PW2_RSTN_MASK,
                           1U << AK5558_PW2_RSTN_SHIFT); /* Normal Operation */
    Delay();

    return ret;
}

status_t AK5558_Deinit(AK5558_handle_t *handle)
{
    status_t ret = kStatus_Success;

    ret = CODEC_I2C_Deinit(handle->i2cHandle);

    return ret;
}
status_t AK5558_ModuleControl(AK5558_handle_t *handle, AK5558_module_ctrl_cmd_t cmd, uint32_t data)
{
    status_t ret = kStatus_Success;

    if (cmd == kAK5558_ModuleSwitchI2SInInterface)
    {
       // ret = AK5558_SetEncoding(handle, (uint8_t)data);
    }
    else
    {
        ret = kStatus_InvalidArgument;
    }

    return ret;
}
status_t AK5558_WriteReg(AK5558_handle_t *handle, uint8_t reg, uint8_t val)
{
    assert(handle->config != NULL);
    assert(handle->config->slaveAddress != 0U);

    Delay(); /* Ensure the Codec I2C bus free before writing the slave. */

    return CODEC_I2C_Send(handle->i2cHandle, handle->config->slaveAddress, reg, 1U, (uint8_t *)&val, 1U);
}
status_t AK5558_ReadReg(AK5558_handle_t *handle, uint8_t reg, uint8_t *val)
{
    assert(handle->config != NULL);
    assert(handle->config->slaveAddress != 0U);

    Delay(); /* Ensure the Codec I2C bus free before reading the slave. */

    return CODEC_I2C_Receive(handle->i2cHandle, handle->config->slaveAddress, reg, 1U, val, 1U);
}
status_t AK5558_ModifyReg(AK5558_handle_t *handle, uint8_t reg, uint8_t mask, uint8_t val)
{
    status_t retval = kStatus_Success;
    uint8_t reg_val = 0;
    retval          = AK5558_ReadReg(handle, reg, &reg_val);
    if (retval != kStatus_Success)
    {
        return kStatus_Fail;
    }
    reg_val &= (uint8_t)~mask;
    reg_val |= val;
    retval = AK5558_WriteReg(handle, reg, reg_val);
    if (retval != kStatus_Success)
    {
        return kStatus_Fail;
    }
    return kStatus_Success;
}

