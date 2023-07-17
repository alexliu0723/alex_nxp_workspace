################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../flash_config/flash_config.c 

C_DEPS += \
./flash_config/flash_config.d 

OBJS += \
./flash_config/flash_config.o 


# Each subdirectory must supply rules for building sources it contributes
flash_config/%.o: ../flash_config/%.c flash_config/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MIMXRT685SFFOB -DCPU_MIMXRT685SFFOB_cm33 -D__REDLIB__ -DBOOT_HEADER_ENABLE=1 -DFSL_SDK_DRIVER_QUICK_ACCESS_ENABLE=1 -DSDK_I2C_BASED_COMPONENT_USED=1 -DCODEC_AK4458_ENABLE -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\source" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\codec" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\drivers" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\component\i2c" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\utilities" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\codec\port\cs42448" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\codec\port" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\device" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\component\uart" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\flash_config" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\component\lists" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\MIMXRT685S" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\CMSIS" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\board" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\mimxrt685audevk\driver_examples\i2s\dma_tdm_record_playback" -O0 -fno-common -g3 -mcpu=cortex-m33 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-flash_config

clean-flash_config:
	-$(RM) ./flash_config/flash_config.d ./flash_config/flash_config.o

.PHONY: clean-flash_config

