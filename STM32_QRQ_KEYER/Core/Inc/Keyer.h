#ifndef __KEYER_H
#define __KEYER_H

uint32_t cw_Timer_Ticks;
int BAUD_DURATION;
_Bool txDecode;

//uint8_t rotationdetected, direction;
_Bool waitToCheckEncoderSwitch;
uint32_t lastTimeEncoderPusched;

uint8_t wpm;
_Bool buzzerOn;
_Bool txOn;
_Bool DitMemOn;
_Bool DahMemOn;
_Bool SwapOn;
_Bool LetterSpaceOn;
_Bool WordSpaceOn;
int8_t DahToDitRatio;
uint16_t DoneLetterSpaceStartTime;
uint16_t DoneWordSpaceStartTime;
uint32_t Last_encoder_Count;
int8_t  LazyFingerTimeDahRatio;
int8_t  LazyFingerTimeDitRatio;

void send_to_ssd1306(void);
void CheckPaddlesStates(void);
void TX_Relay_state(_Bool state);
void doNewLetter(void);
void doNewWord(void);
void doDitLedOn(uint16_t hjhid);
void KeyerMain(void);
void hjhKeyerSetup(void);
void Calculate_speed_vars(void);

#endif /* __MAIN_H */

