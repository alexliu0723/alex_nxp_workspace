################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_cache.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_dma.c \
../drivers/fsl_flexcomm.c \
../drivers/fsl_flexspi.c \
../drivers/fsl_gpio.c \
../drivers/fsl_i2c.c \
../drivers/fsl_i2s.c \
../drivers/fsl_i2s_dma.c \
../drivers/fsl_inputmux.c \
../drivers/fsl_power.c \
../drivers/fsl_reset.c \
../drivers/fsl_usart.c 

C_DEPS += \
./drivers/fsl_cache.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_dma.d \
./drivers/fsl_flexcomm.d \
./drivers/fsl_flexspi.d \
./drivers/fsl_gpio.d \
./drivers/fsl_i2c.d \
./drivers/fsl_i2s.d \
./drivers/fsl_i2s_dma.d \
./drivers/fsl_inputmux.d \
./drivers/fsl_power.d \
./drivers/fsl_reset.d \
./drivers/fsl_usart.d 

OBJS += \
./drivers/fsl_cache.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_dma.o \
./drivers/fsl_flexcomm.o \
./drivers/fsl_flexspi.o \
./drivers/fsl_gpio.o \
./drivers/fsl_i2c.o \
./drivers/fsl_i2s.o \
./drivers/fsl_i2s_dma.o \
./drivers/fsl_inputmux.o \
./drivers/fsl_power.o \
./drivers/fsl_reset.o \
./drivers/fsl_usart.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MIMXRT685SFFOB -DCPU_MIMXRT685SFFOB_cm33 -D__REDLIB__ -DBOOT_HEADER_ENABLE=1 -DFSL_SDK_DRIVER_QUICK_ACCESS_ENABLE=1 -DSDK_I2C_BASED_COMPONENT_USED=1 -DCODEC_AK4458_ENABLE -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\source" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\codec" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\drivers" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\component\i2c" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\utilities" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\codec\port\cs42448" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\codec\port" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\device" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\component\uart" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\flash_config" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\component\lists" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\MIMXRT685S" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\CMSIS" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\board" -I"D:\alex_work_space\NXP_wrokspace\mimxrt685audevk_i2s_dma_tdm_record_playback\mimxrt685audevk\driver_examples\i2s\dma_tdm_record_playback" -O0 -fno-common -g3 -mcpu=cortex-m33 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_cache.d ./drivers/fsl_cache.o ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_dma.d ./drivers/fsl_dma.o ./drivers/fsl_flexcomm.d ./drivers/fsl_flexcomm.o ./drivers/fsl_flexspi.d ./drivers/fsl_flexspi.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_i2c.d ./drivers/fsl_i2c.o ./drivers/fsl_i2s.d ./drivers/fsl_i2s.o ./drivers/fsl_i2s_dma.d ./drivers/fsl_i2s_dma.o ./drivers/fsl_inputmux.d ./drivers/fsl_inputmux.o ./drivers/fsl_power.d ./drivers/fsl_power.o ./drivers/fsl_reset.d ./drivers/fsl_reset.o ./drivers/fsl_usart.d ./drivers/fsl_usart.o

.PHONY: clean-drivers

