/*
 * fsl_ak5558.h
 *
 *  Created on: 2023年6月5日
 *      Author: Alex.Liu
 */

#ifndef FSL_AK5558_H_
#define FSL_AK5558_H_
#include "fsl_common.h"
#include "fsl_codec_i2c.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*@{ */
/*reference MCU-Xpresson API*/
/*CLOCK driver version 2.1.0.*/
#define FSL_AK5558_DRIVER_VERSION (MAKE_VERSION(2, 1, 0))
/*@}*/

/*! @brief ak5558 handle size */
#ifndef AK5558_I2C_HANDLER_SIZE
#define AK5558_I2C_HANDLER_SIZE CODEC_I2C_MASTER_HANDLER_SIZE
#endif
/*! @brief define the registers offset of AK5558. */
#define AK5558_PM1                   (0x00U)
#define AK5558_PM2                   (0x01U)
#define AK5558_CONTROL1              (0x02U)
#define AK5558_CONTROL2              (0x03U)
#define AK5558_CONTROL3              (0x04U)
#define AK5558_DSD                   (0x05U)
#define AK5558_TEST1                 (0x06U)
#define AK5558_TEST2                 (0x07U)

/*! @brief define BIT info of AK5558. */
/*Register Power_Management2          */
#define AK5558_PM2_RSTN_MASK    (0x1U)
#define AK5558_PM2_RSTN_SHIFT   (0U)
#define AK5558_PM2_MONO1_MASK   (0x2U)
#define AK5558_PM2_MONO1_SHIFT  (1U)
#define AK5558_PM2_MONO2_MASK   (0x4U)
#define AK5558_PM2_MONO2_SHIFT  (2U)
/*Register CONTROL1                    */
#define AK5558_CONTROL1_HPFE_MASK  (0x1U)
#define AK5558_CONTROL1_HPFE_SHIFT (0U)
#define AK5558_CONTROL1_DIF0_MASK  (0x2U)
#define AK5558_CONTROL1_DIF0_SHIFT (1U)
#define AK5558_CONTROL1_DIF1_MASK  (0x4U)
#define AK5558_CONTROL1_DIF1_SHIFT (2U)
#define AK5558_CONTROL1_CKS0_MASK  (0x8U)
#define AK5558_CONTROL1_CKS0_SHIFT (3U)
#define AK5558_CONTROL1_CKS1_MASK  (0x10U)
#define AK5558_CONTROL1_CKS1_SHIFT (4U)
#define AK5558_CONTROL1_CKS2_MASK  (0x20U)
#define AK5558_CONTROL1_CKS2_SHIFT (5U)
#define AK5558_CONTROL1_CKS3_MASK  (0x40U)
#define AK5558_CONTROL1_CKS3_SHIFT (6U)
/*Register CONTROL2                   */
#define AK5558_CONTROL2_TDM0_MASK   (0x20U)
#define AK5558_CONTROL2_TDM0_SHIFT  (5U)
#define AK5558_CONTROL2_TDM1_MASK   (0x40U)
#define AK5558_CONTROL2_TDM1_SHIFT  (6U)
/*Register CONTROL3                   */
#define AK5558_CONTROL3_SLOW_MASK  (0x1U)
#define AK5558_CONTROL3_SLOW_SHIFT (0U)
#define AK5558_CONTROL3_SD_MASK    (0x2U)
#define AK5558_CONTROL3_SD_SHIFT   (1U)
#define AK5558_CONTROL3_DP_MASK    (0x80U)
#define AK5558_CONTROL3_DP_SHIFT   (7U)
/*Register DSD                      */
#define AK5558_DSD_DSDSEL0_MASK  (0x1U)
#define AK5558_DSD_DSDSEL0_SHIFT (0U)
#define AK5558_DSD_DSDSEL1_MASK  (0x2U)
#define AK5558_DSD_DSDSEL1_SHIFT (1U)
#define AK5558_DSD_DCKB_MASK     (0x4U)
#define AK5558_DSD_DCKB_SHIFT    (2U)
#define AK5558_DSD_PMOD_MASK     (0x8U)
#define AK5558_DSD_PMOD_SHIFT    (3U)
#define AK5558_DSD_DCKS_MASK     (0x20U)
#define AK5558_DSD_DCKS_SHIFT    (5U)


/*! @brief AK5558 I2C address. */
#define AK5558_I2C_ADDR (0x11U)
/*! @brief AK5558 I2C baudrate */
#define AK5558_I2C_BITRATE (100000U)
/*! @brief The AK5558 playback mode */
typedef enum _AK5558_mode
{
    kAK5558_PcmMode  = 0x0,
    kAK5558_DsdMode  = 0x1,
} AK5558_mode_t;

/*! @brief The MCLK select for DSD mode, defined by DCKS bit */
typedef enum _AK5558_dsd_mclk
{
    kAK5558_mclk512fs = 0x0, /*!< MCLK equals 512fs. */
    kAK5558_mclk768fs = 0x1, /*!< MCLK equals 768fs. */
} AK5558_dsd_mclk_t;
/*! @brief The DCLK select for DSD mode, defined by DSD DSDSEL bit[1:0] */
typedef enum _AK5558_dsd_dclk
{
    kAK5558_dclk64fs  = 0x0, /*!< DCLK equals 64fs. */
    kAK5558_dclk128fs = 0x1, /*!< DCLK equals 128fs. */
    kAK5558_dclk256fs = 0x2, /*!< DCLK equals 256fs. */
} AK5558_dsd_dclk_t;

/*! @brief DSD bclk polarity, defined by DSD DCKB bit[2]  */
typedef enum _AK5558_dsd_dclk_polarity
{
    kAK5558_FallingEdge = 0x0, /*!< DSD data is output from DCLK falling edge. */
    kAK5558_RisingEdge  = 0x1, /*!< DSD data is output from DCLK rising edge. */
} AK5558_dsd_dclk_polarity_t;
;
/*! @brief The sampling speed select, defined by Control 1 CKS bit[6:3] */
typedef enum _AK5558_pcm_samplefreqselect
{
    kAK5558_NormalSpeed_256fs = 0x2, /*!< 8kHZ ~ 54kHZ ,256fs 12M*/
	kAK5558_NormalSpeed_384fs = 0x5, /*!< 8kHZ ~ 54kHZ ,384fs 18mM*/
	kAK5558_NormalSpeed_512fs = 0x6, /*!< 8kHZ ~ 54kHZ ,512fs 24mM*/
	kAK5558_NormalSpeed_768fs = 0x7, /*!< 8kHZ ~ 54kHZ ,768fs 36mM*/
	kAK5558_NormalSpeed_1024fs = 0xd, /*!< 8kHZ ~ 32kHZ ,1024fs 32mM*/
    kAK5558_DoubleSpeed_256fs = 0x3, /*!< 54kHZ ~ 108kHZ,256fs 24M */
	kAK5558_DoubleSpeed_384fs = 0x4, /*!< 54kHZ ~ 108kHZ,384fs 36M */
    kAK5558_QuadSpeed_128fs   = 0x0, /*!< 108kHZ ~ 216kHZ,128fs 24M */
	kAK5558_QuadSpeed_192fs   = 0x1, /*!< 108kHZ ~ 216kHZ,192fs 36M */
    kAK5558_OctSpeed_64fs    = 0x8, /*!< 384kHZ, 64fs 24M */
	kAK5558_OctSpeed_96fs    = 0xA, /*!< 768kHZ, 96fs 36M */
    kAK5558_HexSpeed_32fs    = 0x9, /*!< 768kHZ, 32fs 24M */
	kAK5558_HexSpeed_64fs    = 0xc, /*!< 768kHZ, 64fs 49.1M */
	kAK5558_HexSpeed_48fs    = 0xb, /*!< 768kHZ, 48fs 36M */
	kAK5558_Autopeed_48fs    = 0xf, /*!< 8kHZ <= fs <= 32KHZ, Auto */

} AK5558_pcm_samplefreqselect_t;
/*! @brief The audio data interface modes, defined by Control 1 DIF bit[2:1] */
typedef enum _AK5558_pcm_sdata_format
{
    kAK5558_24BitMSB    = 0x0, /*!< 24-bit MSB justified */
    kAK5558_24BitI2S    = 0x1, /*!< 16 and 24-bit I2S compatible */
    kAK5558_32BitMSB    = 0x2, /*!< 32-bit MSB justified */
    kAK5558_32BitI2S    = 0x3, /*!< 32-bit I2S compatible */
} AK5558_pcm_sdata_format_t;
/*! @brief The TDM mode select, defined by Control 2 TDM bit[6:5] */
typedef enum _AK5558_pcm_tdm_mode
{
    kAK5558_Normal = 0x0, /*!< Normal mode */
    kAK5558_TDM128 = 0x1, /*!< BCLK is fixed to 128fs */
    kAK5558_TDM256 = 0x2, /*!< BCLK is fixed to 256fs */
    kAK5558_TDM512 = 0x3, /*!< BCLK is fixed to 512fs */
} AK5558_pcm_tdm_mode_t;

/*! @brief The audio data slot selection, defined by Power Management2 MONO bit[2:1] */
typedef enum _AK5558_pcm_sds_select
{
    kAK5558_CH87654321 = 0x0,   /*Normal Output & DSD mode*/
    kAK5558_CH00000044 = 0x1,   /*Normal Output & DSD mode*/
	kAK5558_CH0000TT44 = 0x1,   /*TDM 128 mode*/
	kAK5558_CHTTTTTT44 = 0x1,   /*TDM 256 & 512 mode*/
    kAK5558_CH00002222 = 0x2,   /*Normal Output & DSD mode*/
	//kAK5558_CH00002222 = 0x2,   /*TDM 128 mode*/
	kAK5558_CHTTTT2222 = 0x2,   /*TDM 256 & 512 mode*/
    kAK5558_CH00000008 = 0x3,   /*Normal Output & DSD mode*/
	kAK5558_CH0000TTT8 = 0x3,   /*TDM 128 mode*/
	kAK5558_CHTTTTTTT8 = 0x3,   /*TDM 256 & 512 mode*/
} AK5558_pcm_sds_select_t;

/*! @brief audio codec module control cmd */
typedef enum _AK5558_module_ctrl_cmd
{
    kAK5558_ModuleSwitchI2SInInterface = 0U, /*!< module digital interface siwtch. */
} AK5558_module_ctrl_cmd_t;
/*! @brief audio codec module digital interface
 * @anchor _AK5558_module_ctrl_i2s_in_interface
 */
enum
{
    kAK5558_ModuleI2SInInterfacePCM = 0U, /*!< Pcm interface*/
    kAK5558_ModuleI2SInInterfaceDSD = 1U, /*!< DSD interface */
};
/*! @brief Initialize DSD mode structure of AK5558 */
typedef struct _AK5558_dsd_config
{
    AK5558_dsd_mclk_t dsdMclk;
    AK5558_dsd_dclk_polarity_t dsdDclkPolarity;
} AK5558_dsd_config_t;
/*! @brief Initialize PCM mode structure of AK5558 */
typedef struct _AK5558_pcm_config
{
    AK5558_pcm_sdata_format_t pcmSdataFormat;
    AK5558_pcm_tdm_mode_t pcmTdmMode;
    AK5558_pcm_sds_select_t pcmSdsSlot;
} AK5558_pcm_config_t;
/*! @brief Initialize DSD mode structure of AK5558 */

/*! @brief Initialize structure of AK5558 */
typedef struct _AK5558_config
{
    AK5558_mode_t AK5558Mode;
    AK5558_pcm_config_t pcmConfig;
    AK5558_dsd_config_t dsdConfig;

    uint8_t slaveAddress;         /*!< code device slave address */
    codec_i2c_config_t i2cConfig; /*!< i2c bus configuration */
} AK5558_config_t;
/*! @brief AK5558 codec handler
 */
typedef struct _AK5558_handle
{
    AK5558_config_t *config;                    /*!< AK5558 config pointer */
    uint8_t i2cHandle[AK5558_I2C_HANDLER_SIZE]; /*!< i2c handle */
} AK5558_handle_t;
/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif
/*!
 * @brief Default initializes AK5558.
 *
 * @param config AK5558 configure structure.
 */
void AK5558_DefaultConfig(AK5558_config_t *config);
/*!
 * @brief Initializes AK5558.
 *
 * @param handle AK5558 handle structure.
 * @param config AK5558 configure structure.
 */
status_t AK5558_Init(AK5558_handle_t *handle, AK5558_config_t *config);
/*!
 * @brief Deinit the AK5558 codec.
 *
 * This function close all modules in AK5558 to save power.
 *
 * @param handle AK5558 handle structure pointer.
 */
status_t AK5558_Deinit(AK5558_handle_t *handle);
/*!
 * @brief Write register to AK5558 using I2C.
 *
 * @param handle AK5558 handle structure.
 * @param reg The register address in AK5558.
 * @param val Value needs to write into the register.
 */
status_t AK5558_WriteReg(AK5558_handle_t *handle, uint8_t reg, uint8_t val);

/*!
 * @brief Read register from AK5558 using I2C.
 * @param handle AK5558 handle structure.
 * @param reg The register address in AK5558.
 * @param val Value written to.
 */
status_t AK5558_ReadReg(AK5558_handle_t *handle, uint8_t reg, uint8_t *val);

/*!
 * @brief Modify some bits in the register using I2C.
 * @param handle AK5558 handle structure.
 * @param reg The register address in AK5558.
 * @param mask The mask code for the bits want to write. The bit you want to write should be 0.
 * @param val Value needs to write into the register.
 */
status_t AK5558_ModifyReg(AK5558_handle_t *handle, uint8_t reg, uint8_t mask, uint8_t val);

static void Delay(void);
#if defined(__cplusplus)
}
#endif



#endif /* FSL_AK5558_H_ */
