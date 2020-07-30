#include "main.h"
#include "Keyer.h"
#include "fonts.h"
#include "ssd1306.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "eeprom.h"

_Bool menuOn = false;
_Bool subMenuOn = false;

static const uint8_t NUM_MENU_ITEMS = 9;
const char* menu_items[] = {
    "DIT MEMORY",
    "DAH MEMORY",
    "SWAP PADDLE",
    "LETTERSPACE",
    "WORDSPACE",
					/// up from here on & off and below here a number ///
    "LAZY DIT",
	"LAZY DAH",
	"DAH/DIT %",
	"SAVE/EXIT"
};

uint8_t activeMenu = 0;

void drawMenu(uint8_t number){
	SSD1306_Clear();

	SSD1306_GotoXY (0,18);
	SSD1306_Puts(">",&Font_11x18, 1);
	SSD1306_GotoXY (15,0);
	if (number>0)SSD1306_Puts((char*)menu_items[number-1],&Font_11x18, 1);
	SSD1306_GotoXY (15,18);
	SSD1306_Puts((char*)menu_items[number],&Font_11x18, 1);
	SSD1306_GotoXY (15,36);
	if (number<NUM_MENU_ITEMS-1)SSD1306_Puts((char*)menu_items[number+1],&Font_11x18, 1);
	SSD1306_UpdateScreen();
}

void drawSubMenu(uint8_t subNumber){
	SSD1306_Clear();
	SSD1306_GotoXY (0,0);
	SSD1306_Puts((char*)menu_items[activeMenu],&Font_11x18, 1);
	if(activeMenu < 5){
		SSD1306_GotoXY (15,18);
		SSD1306_Puts("ON",&Font_11x18, 1);
		SSD1306_GotoXY (15,36);
		SSD1306_Puts("OFF",&Font_11x18, 1);
		switch(activeMenu){
			case 0:
				if(DitMemOn == true)SSD1306_GotoXY (0,18);
				if(DitMemOn == false)SSD1306_GotoXY (0,36);
				SSD1306_Puts(">",&Font_11x18, 1);
				break;
			case 1:
				if(DahMemOn == true)SSD1306_GotoXY (0,18);
				if(DahMemOn == false)SSD1306_GotoXY (0,36);
				SSD1306_Puts(">",&Font_11x18, 1);
				break;
			case 2:
				if(SwapOn == true)SSD1306_GotoXY (0,18);
				if(SwapOn == false)SSD1306_GotoXY (0,36);
				SSD1306_Puts(">",&Font_11x18, 1);
				break;
			case 3:
				if(LetterSpaceOn == true)SSD1306_GotoXY (0,18);
				if(LetterSpaceOn == false)SSD1306_GotoXY (0,36);
				SSD1306_Puts(">",&Font_11x18, 1);
				break;
			case 4:
				if(WordSpaceOn == true)SSD1306_GotoXY (0,18);
				if(WordSpaceOn == false)SSD1306_GotoXY (0,36);
				SSD1306_Puts(">",&Font_11x18, 1);
				break;
		}
		SSD1306_UpdateScreen();
	}
	if(activeMenu >= 5){
		switch(activeMenu){
			char str[3];
			case 5:
				SSD1306_GotoXY (0,18);
				SSD1306_Puts("% IGNORE",&Font_11x18, 1);
				SSD1306_GotoXY (20,36);
				snprintf( str, 7, "%d", LazyFingerTimeDitRatio);
				SSD1306_Puts(str, &Font_11x18, 1);
				break;
			case 6:
				SSD1306_GotoXY (0,18);
				SSD1306_Puts("% IGNORE",&Font_11x18, 1);
				SSD1306_GotoXY (20,36);
				snprintf( str, 7, "%d", LazyFingerTimeDahRatio);
				SSD1306_Puts(str, &Font_11x18, 1);
				break;
			case 7:
				SSD1306_GotoXY (0,18);
				SSD1306_Puts("ratio",&Font_11x18, 1);
				SSD1306_GotoXY (20,36);
				snprintf( str, 7, "%d", DahToDitRatio);
				SSD1306_Puts(str, &Font_11x18, 1);
				break;
		}
		SSD1306_UpdateScreen();
	}


	while(subMenuOn){
		if(Last_encoder_Count-2 > TIM2->CNT){
			TIM2->CNT = 30000;
			if(activeMenu < 5){
				SSD1306_GotoXY (0,18);
				SSD1306_Puts(">",&Font_11x18, 1);
				SSD1306_GotoXY (0,36);
				SSD1306_Puts(" ",&Font_11x18, 1);
				SSD1306_UpdateScreen();
				switch(activeMenu){
					case 0: DitMemOn = true; break;
					case 1: DahMemOn = true; break;
					case 2: SwapOn = true; break;
					case 3: LetterSpaceOn = true; break;
					case 4: WordSpaceOn = true; break;
				}
			}
			if(activeMenu >= 5){
				switch(activeMenu){
					char str[3];
					case 5:
						LazyFingerTimeDitRatio += 5;
						if(LazyFingerTimeDitRatio >100)LazyFingerTimeDitRatio = 100;
						SSD1306_GotoXY (20,36);
						if(LazyFingerTimeDitRatio > 95)snprintf( str, 7, "%d", LazyFingerTimeDitRatio);
						if((LazyFingerTimeDitRatio > 9)&&(LazyFingerTimeDitRatio <=95))snprintf( str, 7, " %d", LazyFingerTimeDitRatio);
						if(LazyFingerTimeDitRatio <= 9)snprintf( str, 7, "  %d", LazyFingerTimeDitRatio);
						SSD1306_Puts(str, &Font_11x18, 1);
					break;
					case 6:
						LazyFingerTimeDahRatio += 5;
						if(LazyFingerTimeDahRatio >100)LazyFingerTimeDahRatio = 100;
						SSD1306_GotoXY (20,36);
						if(LazyFingerTimeDahRatio > 95)snprintf( str, 7, "%d", LazyFingerTimeDahRatio);
						if((LazyFingerTimeDahRatio > 9)&&(LazyFingerTimeDahRatio <= 95))snprintf( str, 7, " %d", LazyFingerTimeDahRatio);
						if(LazyFingerTimeDahRatio <= 9)snprintf( str, 7, "  %d", LazyFingerTimeDahRatio);
						SSD1306_Puts(str, &Font_11x18, 1);
					break;
					case 7:
						DahToDitRatio += 5;
						if(DahToDitRatio >100)DahToDitRatio = 100;
						SSD1306_GotoXY (20,36);
						if(DahToDitRatio > 95)snprintf( str, 7, "%d", DahToDitRatio);
						if((DahToDitRatio > 9) && (DahToDitRatio <= 95))snprintf( str, 7, " %d", DahToDitRatio);
						if(DahToDitRatio <= 9)snprintf( str, 7, "  %d", DahToDitRatio);
						SSD1306_Puts(str, &Font_11x18, 1);
					break;
				}
				SSD1306_UpdateScreen();
			}
		}

		if(Last_encoder_Count+2 < TIM2->CNT){
			TIM2->CNT = 30000;
			if(activeMenu < 5){
				SSD1306_GotoXY (0,36);
				SSD1306_Puts(">",&Font_11x18, 1);
				SSD1306_GotoXY (0,18);
				SSD1306_Puts(" ",&Font_11x18, 1);
				SSD1306_UpdateScreen();
				switch(activeMenu){
					case 0: DitMemOn = false; break;
					case 1: DahMemOn = false; break;
					case 2: SwapOn = false; break;
					case 3: LetterSpaceOn = false; break;
					case 4: WordSpaceOn = false; break;
				}
			}
			if(activeMenu >= 5){
				switch(activeMenu){
					char str[3];
					case 5:
						LazyFingerTimeDitRatio -= 5;
						if(LazyFingerTimeDitRatio < 0)LazyFingerTimeDitRatio = 0;
						SSD1306_GotoXY (20,36);
						if(LazyFingerTimeDitRatio > 95)snprintf( str, 7, "%d", LazyFingerTimeDitRatio);
						if((LazyFingerTimeDitRatio > 9)&&(LazyFingerTimeDitRatio <=95))snprintf( str, 7, " %d", LazyFingerTimeDitRatio);
						if(LazyFingerTimeDitRatio <= 9)snprintf( str, 7, "  %d", LazyFingerTimeDitRatio);
						SSD1306_Puts(str, &Font_11x18, 1);
					break;
					case 6:
						LazyFingerTimeDahRatio -= 5;
						if(LazyFingerTimeDahRatio < 0)LazyFingerTimeDahRatio = 0;
						SSD1306_GotoXY (20,36);
						if(LazyFingerTimeDahRatio > 95)snprintf( str, 7, "%d", LazyFingerTimeDahRatio);
						if((LazyFingerTimeDahRatio > 9)&&(LazyFingerTimeDahRatio <=95))snprintf( str, 7, " %d", LazyFingerTimeDahRatio);
						if(LazyFingerTimeDahRatio <= 9)snprintf( str, 7, "  %d", LazyFingerTimeDahRatio);
						SSD1306_Puts(str, &Font_11x18, 1);

					break;
					case 7:
						DahToDitRatio -= 5;
						if(DahToDitRatio < 10)DahToDitRatio = 10;
						SSD1306_GotoXY (20,36);
						if(DahToDitRatio > 95)snprintf( str, 7, "%d", DahToDitRatio);
						if((DahToDitRatio > 9) && (DahToDitRatio <= 95))snprintf( str, 7, " %d", DahToDitRatio);
						if(DahToDitRatio <= 9)snprintf( str, 7, "  %d", DahToDitRatio);
						SSD1306_Puts(str, &Font_11x18, 1);

					break;
				}
				SSD1306_UpdateScreen();
			}

		}

		if(HAL_GPIO_ReadPin(Rotary_switch_GPIO_Port,Rotary_switch_Pin) && (lastTimeEncoderPusched + 2000 < cw_Timer_Ticks)){
			lastTimeEncoderPusched = cw_Timer_Ticks;
			subMenuOn = false;
		}
	}
}

void initMenu(){
	menuOn = true;
	activeMenu = 1;
	drawMenu(activeMenu);
	while(menuOn){
		if(Last_encoder_Count-2 > TIM2->CNT){
			TIM2->CNT = 30000;
			if(activeMenu < NUM_MENU_ITEMS-1)activeMenu += 1;
			drawMenu(activeMenu);
		}
		if(Last_encoder_Count+2 < TIM2->CNT){
			TIM2->CNT = 30000;
			if(activeMenu > 0)activeMenu -= 1;
			drawMenu(activeMenu);
		}
		if((HAL_GPIO_ReadPin(Rotary_switch_GPIO_Port,Rotary_switch_Pin)) && (activeMenu != 8)  && (lastTimeEncoderPusched + 2000 < cw_Timer_Ticks)){
			lastTimeEncoderPusched = cw_Timer_Ticks;
			subMenuOn = true;
			drawSubMenu(activeMenu);
			drawMenu(activeMenu);
		}
		if((HAL_GPIO_ReadPin(Rotary_switch_GPIO_Port,Rotary_switch_Pin)) && (activeMenu == 8)&& (lastTimeEncoderPusched + 2000 < cw_Timer_Ticks)){
			lastTimeEncoderPusched = cw_Timer_Ticks;
			menuOn = false;
		}
		HAL_Delay(200);
	}
}
