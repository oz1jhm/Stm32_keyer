#include "main.h"
#include "Keyer.h"
#include "menu.h"
#include "ascii.h"
#include "fonts.h"
#include "ssd1306.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "eeprom.h"

uint16_t DAHpaddleRaw = 3;

uint16_t DIHpaddleRaw = 3;

unsigned char char_ringbuffer[64];
unsigned char ptr_Get_ringbuffer = 0;
unsigned char ptr_Send_ringbuffer = 0;
uint8_t cursorPlaceX = 0;
uint8_t cursorPlaceY = 0;

uint32_t cw_Timer_Ticks = 0;

_Bool DitOn = false;
_Bool DahOn = false;
int BAUD_DURATION = 100;
_Bool txDecode = true;
uint32_t lastTimeEncoderPusched = 0;

uint8_t wpm = 40;
_Bool ultimatic = false;
_Bool buzzerOn = false;
_Bool blueLedOn = false ;
_Bool txOn = true;
_Bool DitMemOn = true;
_Bool DahMemOn = true;
_Bool SwapOn = false;
_Bool WordSpaceOn = false;
_Bool LetterSpaceOn = true;
_Bool did_Failure = false;
int8_t DahToDitRatio = 50;
static uint16_t INTERBAUD_DURATION = 0;
uint16_t INTERLETTER_DURATION = 0;
uint16_t DIT_DURATION = 0;
uint16_t DAH_DURATION = 0;
enum{WAITING_FOR_HIT,SENDING_DIT,SENDING_DAH,LETTERSPACEPAUSE,WORDSPACEPAUSE};
uint16_t state = WAITING_FOR_HIT;
uint16_t nextState = WAITING_FOR_HIT;
uint16_t prevState = LETTERSPACEPAUSE;

uint32_t Last_encoder_Count = 30000;
uint32_t Last_time_turned = 0;

uint16_t speed;
uint32_t currentTime;
uint32_t startTime;
uint32_t LazyFingerTimeDit;
int8_t  LazyFingerTimeDitRatio = 10;
uint32_t LazyFingerTimeDah;
int8_t  LazyFingerTimeDahRatio = 10;

static uint16_t Number_In_Cw_To_Ascii = 0;
_Bool cw_char_done = false;
_Bool newWorddone = true;

void CheckPaddlesStates()
{
	DAHpaddleRaw = HAL_GPIO_ReadPin(DAH_paddle2_GPIO_Port,DAH_paddle2_Pin) ;
	DIHpaddleRaw = HAL_GPIO_ReadPin(DIH_paddle2_GPIO_Port,DIH_paddle2_Pin) ;

	if(DIHpaddleRaw == false){
			if(!SwapOn)DitOn = true;
			if(SwapOn)DahOn = true;
	}
	else{
		    if(!SwapOn)DitOn = false;
			if(SwapOn)DahOn = false;
	}


	if(DAHpaddleRaw ==0){
			if(!SwapOn)DahOn = true;
			if(SwapOn)DitOn = true;
	}
	else{
		    if(!SwapOn)DahOn = false;
			if(SwapOn)DitOn = false;
	}
}

void hjhKeyerSetup(void)
{
	state = WAITING_FOR_HIT;
	readFromEEprom();
	Calculate_speed_vars();
	SSD1306_Clear();
	SSD1306_GotoXY (0,43);
	char str[3];
	snprintf( str, 7, "WPM %d", wpm );
	SSD1306_Puts(str, &Font_11x18, 1);
	SSD1306_UpdateScreen();
}

void Calculate_speed_vars()
{
	DIT_DURATION = 12000UL/wpm;
	INTERBAUD_DURATION = DIT_DURATION*1;
	INTERLETTER_DURATION = DIT_DURATION*2;
    DAH_DURATION = DIT_DURATION*((3*DahToDitRatio)/50);
    LazyFingerTimeDit = (DIT_DURATION * LazyFingerTimeDitRatio) / 100;
    LazyFingerTimeDah = (DAH_DURATION * LazyFingerTimeDahRatio) / 100;
    writeToEEprom();

}

void readspeed()
{

	if(Last_encoder_Count-2 > TIM2->CNT){
		if(cw_Timer_Ticks - Last_time_turned > 150){
			wpm += 1;
		}
		else
		{
			wpm += 3;
		}
		if(wpm>99)wpm=99;
		TIM2->CNT = 30000;
		SSD1306_GotoXY (0,43);
		char str[3];
		if (wpm>9)snprintf( str, 7, "WPM %d", wpm );
		if (wpm<=9)snprintf( str, 7, "WPM  %d", wpm );
		SSD1306_Puts(str, &Font_11x18, 1);
		SSD1306_UpdateScreen();
		Calculate_speed_vars();
		Last_time_turned = cw_Timer_Ticks;
	}
	if(Last_encoder_Count+2 < TIM2->CNT){
		if(cw_Timer_Ticks - Last_time_turned > 150){
			wpm -= 1;
		}
		else
		{
			wpm -= 3;
		}
		if(wpm<2)wpm=2;
		TIM2->CNT = 30000;
		SSD1306_GotoXY (0,43);
		char str[3];
		if (wpm>9)snprintf( str, 7, "WPM %d", wpm );
		if (wpm<=9)snprintf( str, 7, "WPM  %d", wpm );
		SSD1306_Puts(str, &Font_11x18, 1);
		SSD1306_UpdateScreen();
		Calculate_speed_vars();
		Last_time_turned = cw_Timer_Ticks;
	}

	if((HAL_GPIO_ReadPin(Rotary_switch_GPIO_Port,Rotary_switch_Pin))&& (lastTimeEncoderPusched + 2000 < cw_Timer_Ticks)){
		lastTimeEncoderPusched = cw_Timer_Ticks;
		initMenu();
		SSD1306_Clear();
		SSD1306_GotoXY (0,43);
		char str[3];
		snprintf( str, 7, "WPM %d", wpm );
		SSD1306_Puts(str, &Font_11x18, 1);
		SSD1306_UpdateScreen();
		Calculate_speed_vars();
	}

}

void TX_Relay_state(_Bool OnOff)
{
	if(OnOff == true)
	{
	  if (txOn == true){
		  HAL_GPIO_WritePin(TX1_GPIO_Port,TX1_Pin,GPIO_PIN_SET);
		  HAL_GPIO_WritePin(TX2_GPIO_Port,TX2_Pin,GPIO_PIN_SET);
		  HAL_GPIO_WritePin(TX3_GPIO_Port,TX3_Pin,GPIO_PIN_SET);
//		  HAL_GPIO_WritePin(TX_relay_GPIO_Port,TX_relay_Pin,GPIO_PIN_SET);
//		  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin,GPIO_PIN_RESET);
		  if(blueLedOn)HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin,GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
	  }

	}
	else
	{
		  HAL_GPIO_WritePin(TX1_GPIO_Port,TX1_Pin,GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(TX2_GPIO_Port,TX2_Pin,GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(TX3_GPIO_Port,TX3_Pin,GPIO_PIN_RESET);
//		  HAL_GPIO_WritePin(TX_relay_GPIO_Port,TX_relay_Pin,GPIO_PIN_RESET);
//	      HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin,GPIO_PIN_SET);
	      HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin,GPIO_PIN_SET);
	}
}

void KeyerMain()
{
	CheckPaddlesStates();
	readspeed();
		switch(state){
			case WAITING_FOR_HIT:

				if(did_Failure)HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);

				if(DahOn && nextState == WAITING_FOR_HIT)nextState = SENDING_DAH;
				if(DitOn && nextState == WAITING_FOR_HIT)nextState = SENDING_DIT;

				if(DahOn && prevState == SENDING_DIT && nextState == SENDING_DIT && DahMemOn == false)nextState = SENDING_DAH;
				if(DitOn && prevState == SENDING_DAH && nextState == SENDING_DAH && DitMemOn == false)nextState = SENDING_DAH;

				//// Ultimatic
				//if (DitOn && ultimatic && prevState == SENDING_DIT )nextState = SENDING_DIT;
				//if (DahOn && ultimatic && prevState == SENDING_DAH )nextState = SENDING_DAH;
				//// Ultimatic

				if((prevState == SENDING_DAH || prevState == SENDING_DIT) && nextState == WAITING_FOR_HIT && LetterSpaceOn)nextState = LETTERSPACEPAUSE;

				if(((cw_Timer_Ticks - (4*DIT_DURATION)) > currentTime) && (nextState == WAITING_FOR_HIT)){
									HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin,GPIO_PIN_RESET);
									HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin,GPIO_PIN_SET);
									did_Failure = false;
								}

				if(((cw_Timer_Ticks - (4*DIT_DURATION)) > currentTime) && !newWorddone && txDecode && !WordSpaceOn && (nextState == WAITING_FOR_HIT))doNewWord();
				if(((cw_Timer_Ticks - (4*DIT_DURATION)) > currentTime) && WordSpaceOn && (nextState == WAITING_FOR_HIT)) nextState = WORDSPACEPAUSE;

				break;

			case SENDING_DIT:
				if (Number_In_Cw_To_Ascii == 0) Number_In_Cw_To_Ascii = true;							// starting bit is set
				nextState = WAITING_FOR_HIT;
				TX_Relay_state(true);
				cw_char_done = false;
				newWorddone = false;
				currentTime = cw_Timer_Ticks;
				startTime = cw_Timer_Ticks;
				while (startTime + DIT_DURATION + INTERBAUD_DURATION >= currentTime)
				{
					CheckPaddlesStates();
					if ((startTime + DIT_DURATION  <= currentTime) & (cw_char_done == false)){
						TX_Relay_state(false);
						Number_In_Cw_To_Ascii = Number_In_Cw_To_Ascii << 1;								// bitshit left so we can make new dit
						Number_In_Cw_To_Ascii++;														// Because Dit is 1 we do add 1
						if(Number_In_Cw_To_Ascii > 255) Number_In_Cw_To_Ascii = 0;						// If operator make many mistakes we erase
						cw_char_done = true;
	     			}
					//// Iambic A & Iambic B
					if(!ultimatic){
						if ((currentTime > startTime + LazyFingerTimeDit) && (prevState == SENDING_DAH)){
							if(DahOn && DahMemOn)nextState = SENDING_DAH;									// Increase releasetime for lazy fingers
						}
						else{
							if(DahOn && DahMemOn && prevState != SENDING_DAH)nextState = SENDING_DAH;		//	insert shall not be with lazyfinger time
						}
					}
					//// Iambic A & Iambic B
					//// Ultimatic
					if (ultimatic && DahOn && prevState != SENDING_DAH)nextState = SENDING_DAH;
					//// Ultimatic

    				currentTime = cw_Timer_Ticks;
				};

			break;

			case SENDING_DAH:
				if(Number_In_Cw_To_Ascii == 0)Number_In_Cw_To_Ascii = 1;								// starting bit is set
				nextState = WAITING_FOR_HIT;
				TX_Relay_state(true);
				cw_char_done = false;
				newWorddone = false;
				currentTime = cw_Timer_Ticks;
				startTime = cw_Timer_Ticks;
				while (startTime + DAH_DURATION + INTERBAUD_DURATION >= currentTime)
				{
					CheckPaddlesStates();
					if ((startTime + DAH_DURATION <= currentTime) & (cw_char_done == false)){
						TX_Relay_state(false);
						Number_In_Cw_To_Ascii = Number_In_Cw_To_Ascii << 1;								// bitshit left so we can make new dah
																										// Because Dah is 0 we do nothing at all
						if(Number_In_Cw_To_Ascii > 255) Number_In_Cw_To_Ascii = 0;						// If operator make many mistakes we erase
						cw_char_done = true;
					}
					//// Iambic A and B
					if(!ultimatic){
						if ((currentTime > startTime + LazyFingerTimeDah) && (prevState == SENDING_DIT)){
							if(DitOn && DitMemOn)nextState = SENDING_DIT;									// Increase releasetime for lazy fingers
						}
						else{
							if(DitOn && DitMemOn && prevState != SENDING_DIT)nextState = SENDING_DIT;		//	insert shall not be with lazyfinger time
						}
					}
					//// Iambic A and B
					//// Ultimatic
					if (ultimatic && DitOn && prevState != SENDING_DIT)nextState = SENDING_DIT;
					//// Ultimatic

					currentTime = cw_Timer_Ticks;
				};
			break;

			case LETTERSPACEPAUSE:
				if (txDecode)doNewLetter();
				nextState = WAITING_FOR_HIT;
				currentTime = cw_Timer_Ticks;
				startTime = cw_Timer_Ticks;
				while ((startTime + INTERLETTER_DURATION >= currentTime) && LetterSpaceOn){
					CheckPaddlesStates();
					if(DahOn && nextState == WAITING_FOR_HIT)nextState = SENDING_DAH;
					if(DitOn && nextState == WAITING_FOR_HIT)nextState = SENDING_DIT;
					currentTime = cw_Timer_Ticks;
				}
			break;

			case WORDSPACEPAUSE:
				if(did_Failure)HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
				did_Failure = false;
				nextState = WAITING_FOR_HIT;
				currentTime = cw_Timer_Ticks;
				startTime = cw_Timer_Ticks;
				while (startTime + (INTERLETTER_DURATION*2) >= currentTime){
					CheckPaddlesStates();
					if(DahOn && nextState == WAITING_FOR_HIT)nextState = SENDING_DAH;
					if(DitOn && nextState == WAITING_FOR_HIT)nextState = SENDING_DIT;
					currentTime = cw_Timer_Ticks;
				}
				if(!newWorddone && txDecode)doNewWord();
				HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin,GPIO_PIN_RESET);
			break;
			}

		prevState = state;
		state = nextState;
}

void doNewLetter()
{
	  if(mySet[Number_In_Cw_To_Ascii] == 127)  did_Failure = true ;
	  char_ringbuffer[ptr_Send_ringbuffer] = mySet[Number_In_Cw_To_Ascii];
	  ptr_Send_ringbuffer = (ptr_Send_ringbuffer + 1 ) & 63;
	  Number_In_Cw_To_Ascii = 0;
}

void doNewWord()
{
		char_ringbuffer[ptr_Send_ringbuffer] = mySet[0];
		ptr_Send_ringbuffer = (ptr_Send_ringbuffer + 1 ) & 63;
		newWorddone = true;
}

void send_to_ssd1306()
{
	while(ptr_Get_ringbuffer != ptr_Send_ringbuffer){
		SSD1306_GotoXY (cursorPlaceX,cursorPlaceY);
		SSD1306_Putc (char_ringbuffer[ptr_Get_ringbuffer], &Font_11x18, 1);
		SSD1306_UpdateScreen(); //display
		cursorPlaceX += 11;
		if (cursorPlaceX > 116){
			cursorPlaceX = 0;
			cursorPlaceY +=18;
		}
		if (cursorPlaceY >18){
			cursorPlaceY = 18;
			SSD1306_Fill_UP(0);
			uint8_t tempX = 0;
			SSD1306_GotoXY (tempX,0);
			uint8_t temp_Ptr = ptr_Get_ringbuffer-11;
			temp_Ptr &= 63;
			for ( int i = 0; i <= 12;i++){
				temp_Ptr += 1;
				temp_Ptr &= 63;
				SSD1306_Putc (char_ringbuffer[temp_Ptr], &Font_11x18, 1);
				tempX += 11;
				SSD1306_GotoXY (tempX,0);
			}
			SSD1306_UpdateScreen(); //display
		}
		ptr_Get_ringbuffer = (ptr_Get_ringbuffer + 1) & 63;
	}
}




