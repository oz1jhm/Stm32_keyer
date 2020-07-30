#include "main.h"
#include "Keyer.h"


void writeToEEprom(){
	uint8_t control_hex = 0x66;
	HAL_I2C_Mem_Write( &hi2c2, 0xA0, 1, I2C_MEMADD_SIZE_16BIT, (uint8_t*)&control_hex, I2C_MEMADD_SIZE_8BIT, 100 );
	HAL_Delay(5);
	HAL_I2C_Mem_Write( &hi2c2, 0xA0, 2, I2C_MEMADD_SIZE_16BIT, &wpm, I2C_MEMADD_SIZE_8BIT, 100 );
	HAL_Delay(5);
	HAL_I2C_Mem_Write( &hi2c2, 0xA0, 3, I2C_MEMADD_SIZE_16BIT,(uint8_t*)&DitMemOn, I2C_MEMADD_SIZE_8BIT, 100 );
	HAL_Delay(5);
	HAL_I2C_Mem_Write( &hi2c2, 0xA0, 4, I2C_MEMADD_SIZE_16BIT,(uint8_t*)&DahMemOn, I2C_MEMADD_SIZE_8BIT, 100 );
	HAL_Delay(5);
	HAL_I2C_Mem_Write( &hi2c2, 0xA0, 5, I2C_MEMADD_SIZE_16BIT,(uint8_t*)&SwapOn, I2C_MEMADD_SIZE_8BIT, 100 );
	HAL_Delay(5);
	HAL_I2C_Mem_Write( &hi2c2, 0xA0, 6, I2C_MEMADD_SIZE_16BIT,(uint8_t*)&LetterSpaceOn, I2C_MEMADD_SIZE_8BIT, 100 );
	HAL_Delay(5);
	HAL_I2C_Mem_Write( &hi2c2, 0xA0, 7, I2C_MEMADD_SIZE_16BIT,(uint8_t*)&WordSpaceOn, I2C_MEMADD_SIZE_8BIT, 100 );
	HAL_Delay(5);
	HAL_I2C_Mem_Write( &hi2c2, 0xA0, 8, I2C_MEMADD_SIZE_16BIT,(uint8_t*)&LazyFingerTimeDitRatio, I2C_MEMADD_SIZE_8BIT, 100 );
	HAL_Delay(5);
	HAL_I2C_Mem_Write( &hi2c2, 0xA0, 9, I2C_MEMADD_SIZE_16BIT,(uint8_t*)&LazyFingerTimeDahRatio, I2C_MEMADD_SIZE_8BIT, 100 );
	HAL_Delay(5);
	HAL_I2C_Mem_Write( &hi2c2, 0xA0, 10, I2C_MEMADD_SIZE_16BIT,(uint8_t*)&DahToDitRatio, I2C_MEMADD_SIZE_8BIT, 100 );
	HAL_Delay(5);

}

void readFromEEprom(){
	uint8_t control_hex = 0;
	HAL_I2C_Mem_Read(&hi2c2, 0xA0, 1, I2C_MEMADD_SIZE_16BIT,(uint8_t*)&control_hex,I2C_MEMADD_SIZE_8BIT, 100);
	HAL_Delay(5);
	if(control_hex == 0x66){
		HAL_I2C_Mem_Read(&hi2c2, 0xA0, 2, I2C_MEMADD_SIZE_16BIT,(uint8_t*)&wpm,I2C_MEMADD_SIZE_8BIT, 100);
		HAL_Delay(5);
		HAL_I2C_Mem_Read(&hi2c2, 0xA0, 3, I2C_MEMADD_SIZE_16BIT,(uint8_t*)&DitMemOn,I2C_MEMADD_SIZE_8BIT, 100);
		HAL_Delay(5);
		HAL_I2C_Mem_Read(&hi2c2, 0xA0, 4, I2C_MEMADD_SIZE_16BIT,(uint8_t*)&DahMemOn,I2C_MEMADD_SIZE_8BIT, 100);
		HAL_Delay(5);
		HAL_I2C_Mem_Read(&hi2c2, 0xA0, 5, I2C_MEMADD_SIZE_16BIT,(uint8_t*)&SwapOn,I2C_MEMADD_SIZE_8BIT, 100);
		HAL_Delay(5);
		HAL_I2C_Mem_Read(&hi2c2, 0xA0, 6, I2C_MEMADD_SIZE_16BIT,(uint8_t*)&LetterSpaceOn,I2C_MEMADD_SIZE_8BIT, 100);
		HAL_Delay(5);
		HAL_I2C_Mem_Read(&hi2c2, 0xA0, 7, I2C_MEMADD_SIZE_16BIT,(uint8_t*)&WordSpaceOn,I2C_MEMADD_SIZE_8BIT, 100);
		HAL_Delay(5);
		HAL_I2C_Mem_Read(&hi2c2, 0xA0, 8, I2C_MEMADD_SIZE_16BIT,(uint8_t*)&LazyFingerTimeDitRatio,I2C_MEMADD_SIZE_8BIT, 100);
		HAL_Delay(5);
		HAL_I2C_Mem_Read(&hi2c2, 0xA0, 9, I2C_MEMADD_SIZE_16BIT,(uint8_t*)&LazyFingerTimeDahRatio,I2C_MEMADD_SIZE_8BIT, 100);
		HAL_Delay(5);
		HAL_I2C_Mem_Read(&hi2c2, 0xA0, 10, I2C_MEMADD_SIZE_16BIT,(uint8_t*)&DahToDitRatio,I2C_MEMADD_SIZE_8BIT, 100);
		HAL_Delay(5);
	}
}
