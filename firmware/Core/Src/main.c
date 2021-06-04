/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_tx;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

#define LED_NO    32
#define LED_BUFFER_LENGTH (LED_NO*12)

const uint8_t leddata[256*4] = { // size = 256 * 3
  0X44 , 0X44 , 0X44 , 0X44 , // 0
  0X44 , 0X44 , 0X44 , 0X47 , // 1
  0X44 , 0X44 , 0X44 , 0X74 , // 2
  0X44 , 0X44 , 0X44 , 0X77 , // 3
  0X44 , 0X44 , 0X47 , 0X44 , // 4
  0X44 , 0X44 , 0X47 , 0X47 , // 5
  0X44 , 0X44 , 0X47 , 0X74 , // 6
  0X44 , 0X44 , 0X47 , 0X77 , // 7
  0X44 , 0X44 , 0X74 , 0X44 , // 8
  0X44 , 0X44 , 0X74 , 0X47 , // 9
  0X44 , 0X44 , 0X74 , 0X74 , // 10
  0X44 , 0X44 , 0X74 , 0X77 , // 11
  0X44 , 0X44 , 0X77 , 0X44 , // 12
  0X44 , 0X44 , 0X77 , 0X47 , // 13
  0X44 , 0X44 , 0X77 , 0X74 , // 14
  0X44 , 0X44 , 0X77 , 0X77 , // 15
  0X44 , 0X47 , 0X44 , 0X44 , // 16
  0X44 , 0X47 , 0X44 , 0X47 , // 17
  0X44 , 0X47 , 0X44 , 0X74 , // 18
  0X44 , 0X47 , 0X44 , 0X77 , // 19
  0X44 , 0X47 , 0X47 , 0X44 , // 20
  0X44 , 0X47 , 0X47 , 0X47 , // 21
  0X44 , 0X47 , 0X47 , 0X74 , // 22
  0X44 , 0X47 , 0X47 , 0X77 , // 23
  0X44 , 0X47 , 0X74 , 0X44 , // 24
  0X44 , 0X47 , 0X74 , 0X47 , // 25
  0X44 , 0X47 , 0X74 , 0X74 , // 26
  0X44 , 0X47 , 0X74 , 0X77 , // 27
  0X44 , 0X47 , 0X77 , 0X44 , // 28
  0X44 , 0X47 , 0X77 , 0X47 , // 29
  0X44 , 0X47 , 0X77 , 0X74 , // 30
  0X44 , 0X47 , 0X77 , 0X77 , // 31
  0X44 , 0X74 , 0X44 , 0X44 , // 32
  0X44 , 0X74 , 0X44 , 0X47 , // 33
  0X44 , 0X74 , 0X44 , 0X74 , // 34
  0X44 , 0X74 , 0X44 , 0X77 , // 35
  0X44 , 0X74 , 0X47 , 0X44 , // 36
  0X44 , 0X74 , 0X47 , 0X47 , // 37
  0X44 , 0X74 , 0X47 , 0X74 , // 38
  0X44 , 0X74 , 0X47 , 0X77 , // 39
  0X44 , 0X74 , 0X74 , 0X44 , // 40
  0X44 , 0X74 , 0X74 , 0X47 , // 41
  0X44 , 0X74 , 0X74 , 0X74 , // 42
  0X44 , 0X74 , 0X74 , 0X77 , // 43
  0X44 , 0X74 , 0X77 , 0X44 , // 44
  0X44 , 0X74 , 0X77 , 0X47 , // 45
  0X44 , 0X74 , 0X77 , 0X74 , // 46
  0X44 , 0X74 , 0X77 , 0X77 , // 47
  0X44 , 0X77 , 0X44 , 0X44 , // 48
  0X44 , 0X77 , 0X44 , 0X47 , // 49
  0X44 , 0X77 , 0X44 , 0X74 , // 50
  0X44 , 0X77 , 0X44 , 0X77 , // 51
  0X44 , 0X77 , 0X47 , 0X44 , // 52
  0X44 , 0X77 , 0X47 , 0X47 , // 53
  0X44 , 0X77 , 0X47 , 0X74 , // 54
  0X44 , 0X77 , 0X47 , 0X77 , // 55
  0X44 , 0X77 , 0X74 , 0X44 , // 56
  0X44 , 0X77 , 0X74 , 0X47 , // 57
  0X44 , 0X77 , 0X74 , 0X74 , // 58
  0X44 , 0X77 , 0X74 , 0X77 , // 59
  0X44 , 0X77 , 0X77 , 0X44 , // 60
  0X44 , 0X77 , 0X77 , 0X47 , // 61
  0X44 , 0X77 , 0X77 , 0X74 , // 62
  0X44 , 0X77 , 0X77 , 0X77 , // 63
  0X47 , 0X44 , 0X44 , 0X44 , // 64
  0X47 , 0X44 , 0X44 , 0X47 , // 65
  0X47 , 0X44 , 0X44 , 0X74 , // 66
  0X47 , 0X44 , 0X44 , 0X77 , // 67
  0X47 , 0X44 , 0X47 , 0X44 , // 68
  0X47 , 0X44 , 0X47 , 0X47 , // 69
  0X47 , 0X44 , 0X47 , 0X74 , // 70
  0X47 , 0X44 , 0X47 , 0X77 , // 71
  0X47 , 0X44 , 0X74 , 0X44 , // 72
  0X47 , 0X44 , 0X74 , 0X47 , // 73
  0X47 , 0X44 , 0X74 , 0X74 , // 74
  0X47 , 0X44 , 0X74 , 0X77 , // 75
  0X47 , 0X44 , 0X77 , 0X44 , // 76
  0X47 , 0X44 , 0X77 , 0X47 , // 77
  0X47 , 0X44 , 0X77 , 0X74 , // 78
  0X47 , 0X44 , 0X77 , 0X77 , // 79
  0X47 , 0X47 , 0X44 , 0X44 , // 80
  0X47 , 0X47 , 0X44 , 0X47 , // 81
  0X47 , 0X47 , 0X44 , 0X74 , // 82
  0X47 , 0X47 , 0X44 , 0X77 , // 83
  0X47 , 0X47 , 0X47 , 0X44 , // 84
  0X47 , 0X47 , 0X47 , 0X47 , // 85
  0X47 , 0X47 , 0X47 , 0X74 , // 86
  0X47 , 0X47 , 0X47 , 0X77 , // 87
  0X47 , 0X47 , 0X74 , 0X44 , // 88
  0X47 , 0X47 , 0X74 , 0X47 , // 89
  0X47 , 0X47 , 0X74 , 0X74 , // 90
  0X47 , 0X47 , 0X74 , 0X77 , // 91
  0X47 , 0X47 , 0X77 , 0X44 , // 92
  0X47 , 0X47 , 0X77 , 0X47 , // 93
  0X47 , 0X47 , 0X77 , 0X74 , // 94
  0X47 , 0X47 , 0X77 , 0X77 , // 95
  0X47 , 0X74 , 0X44 , 0X44 , // 96
  0X47 , 0X74 , 0X44 , 0X47 , // 97
  0X47 , 0X74 , 0X44 , 0X74 , // 98
  0X47 , 0X74 , 0X44 , 0X77 , // 99
  0X47 , 0X74 , 0X47 , 0X44 , // 100
  0X47 , 0X74 , 0X47 , 0X47 , // 101
  0X47 , 0X74 , 0X47 , 0X74 , // 102
  0X47 , 0X74 , 0X47 , 0X77 , // 103
  0X47 , 0X74 , 0X74 , 0X44 , // 104
  0X47 , 0X74 , 0X74 , 0X47 , // 105
  0X47 , 0X74 , 0X74 , 0X74 , // 106
  0X47 , 0X74 , 0X74 , 0X77 , // 107
  0X47 , 0X74 , 0X77 , 0X44 , // 108
  0X47 , 0X74 , 0X77 , 0X47 , // 109
  0X47 , 0X74 , 0X77 , 0X74 , // 110
  0X47 , 0X74 , 0X77 , 0X77 , // 111
  0X47 , 0X77 , 0X44 , 0X44 , // 112
  0X47 , 0X77 , 0X44 , 0X47 , // 113
  0X47 , 0X77 , 0X44 , 0X74 , // 114
  0X47 , 0X77 , 0X44 , 0X77 , // 115
  0X47 , 0X77 , 0X47 , 0X44 , // 116
  0X47 , 0X77 , 0X47 , 0X47 , // 117
  0X47 , 0X77 , 0X47 , 0X74 , // 118
  0X47 , 0X77 , 0X47 , 0X77 , // 119
  0X47 , 0X77 , 0X74 , 0X44 , // 120
  0X47 , 0X77 , 0X74 , 0X47 , // 121
  0X47 , 0X77 , 0X74 , 0X74 , // 122
  0X47 , 0X77 , 0X74 , 0X77 , // 123
  0X47 , 0X77 , 0X77 , 0X44 , // 124
  0X47 , 0X77 , 0X77 , 0X47 , // 125
  0X47 , 0X77 , 0X77 , 0X74 , // 126
  0X47 , 0X77 , 0X77 , 0X77 , // 127
  0X74 , 0X44 , 0X44 , 0X44 , // 128
  0X74 , 0X44 , 0X44 , 0X47 , // 129
  0X74 , 0X44 , 0X44 , 0X74 , // 130
  0X74 , 0X44 , 0X44 , 0X77 , // 131
  0X74 , 0X44 , 0X47 , 0X44 , // 132
  0X74 , 0X44 , 0X47 , 0X47 , // 133
  0X74 , 0X44 , 0X47 , 0X74 , // 134
  0X74 , 0X44 , 0X47 , 0X77 , // 135
  0X74 , 0X44 , 0X74 , 0X44 , // 136
  0X74 , 0X44 , 0X74 , 0X47 , // 137
  0X74 , 0X44 , 0X74 , 0X74 , // 138
  0X74 , 0X44 , 0X74 , 0X77 , // 139
  0X74 , 0X44 , 0X77 , 0X44 , // 140
  0X74 , 0X44 , 0X77 , 0X47 , // 141
  0X74 , 0X44 , 0X77 , 0X74 , // 142
  0X74 , 0X44 , 0X77 , 0X77 , // 143
  0X74 , 0X47 , 0X44 , 0X44 , // 144
  0X74 , 0X47 , 0X44 , 0X47 , // 145
  0X74 , 0X47 , 0X44 , 0X74 , // 146
  0X74 , 0X47 , 0X44 , 0X77 , // 147
  0X74 , 0X47 , 0X47 , 0X44 , // 148
  0X74 , 0X47 , 0X47 , 0X47 , // 149
  0X74 , 0X47 , 0X47 , 0X74 , // 150
  0X74 , 0X47 , 0X47 , 0X77 , // 151
  0X74 , 0X47 , 0X74 , 0X44 , // 152
  0X74 , 0X47 , 0X74 , 0X47 , // 153
  0X74 , 0X47 , 0X74 , 0X74 , // 154
  0X74 , 0X47 , 0X74 , 0X77 , // 155
  0X74 , 0X47 , 0X77 , 0X44 , // 156
  0X74 , 0X47 , 0X77 , 0X47 , // 157
  0X74 , 0X47 , 0X77 , 0X74 , // 158
  0X74 , 0X47 , 0X77 , 0X77 , // 159
  0X74 , 0X74 , 0X44 , 0X44 , // 160
  0X74 , 0X74 , 0X44 , 0X47 , // 161
  0X74 , 0X74 , 0X44 , 0X74 , // 162
  0X74 , 0X74 , 0X44 , 0X77 , // 163
  0X74 , 0X74 , 0X47 , 0X44 , // 164
  0X74 , 0X74 , 0X47 , 0X47 , // 165
  0X74 , 0X74 , 0X47 , 0X74 , // 166
  0X74 , 0X74 , 0X47 , 0X77 , // 167
  0X74 , 0X74 , 0X74 , 0X44 , // 168
  0X74 , 0X74 , 0X74 , 0X47 , // 169
  0X74 , 0X74 , 0X74 , 0X74 , // 170
  0X74 , 0X74 , 0X74 , 0X77 , // 171
  0X74 , 0X74 , 0X77 , 0X44 , // 172
  0X74 , 0X74 , 0X77 , 0X47 , // 173
  0X74 , 0X74 , 0X77 , 0X74 , // 174
  0X74 , 0X74 , 0X77 , 0X77 , // 175
  0X74 , 0X77 , 0X44 , 0X44 , // 176
  0X74 , 0X77 , 0X44 , 0X47 , // 177
  0X74 , 0X77 , 0X44 , 0X74 , // 178
  0X74 , 0X77 , 0X44 , 0X77 , // 179
  0X74 , 0X77 , 0X47 , 0X44 , // 180
  0X74 , 0X77 , 0X47 , 0X47 , // 181
  0X74 , 0X77 , 0X47 , 0X74 , // 182
  0X74 , 0X77 , 0X47 , 0X77 , // 183
  0X74 , 0X77 , 0X74 , 0X44 , // 184
  0X74 , 0X77 , 0X74 , 0X47 , // 185
  0X74 , 0X77 , 0X74 , 0X74 , // 186
  0X74 , 0X77 , 0X74 , 0X77 , // 187
  0X74 , 0X77 , 0X77 , 0X44 , // 188
  0X74 , 0X77 , 0X77 , 0X47 , // 189
  0X74 , 0X77 , 0X77 , 0X74 , // 190
  0X74 , 0X77 , 0X77 , 0X77 , // 191
  0X77 , 0X44 , 0X44 , 0X44 , // 192
  0X77 , 0X44 , 0X44 , 0X47 , // 193
  0X77 , 0X44 , 0X44 , 0X74 , // 194
  0X77 , 0X44 , 0X44 , 0X77 , // 195
  0X77 , 0X44 , 0X47 , 0X44 , // 196
  0X77 , 0X44 , 0X47 , 0X47 , // 197
  0X77 , 0X44 , 0X47 , 0X74 , // 198
  0X77 , 0X44 , 0X47 , 0X77 , // 199
  0X77 , 0X44 , 0X74 , 0X44 , // 200
  0X77 , 0X44 , 0X74 , 0X47 , // 201
  0X77 , 0X44 , 0X74 , 0X74 , // 202
  0X77 , 0X44 , 0X74 , 0X77 , // 203
  0X77 , 0X44 , 0X77 , 0X44 , // 204
  0X77 , 0X44 , 0X77 , 0X47 , // 205
  0X77 , 0X44 , 0X77 , 0X74 , // 206
  0X77 , 0X44 , 0X77 , 0X77 , // 207
  0X77 , 0X47 , 0X44 , 0X44 , // 208
  0X77 , 0X47 , 0X44 , 0X47 , // 209
  0X77 , 0X47 , 0X44 , 0X74 , // 210
  0X77 , 0X47 , 0X44 , 0X77 , // 211
  0X77 , 0X47 , 0X47 , 0X44 , // 212
  0X77 , 0X47 , 0X47 , 0X47 , // 213
  0X77 , 0X47 , 0X47 , 0X74 , // 214
  0X77 , 0X47 , 0X47 , 0X77 , // 215
  0X77 , 0X47 , 0X74 , 0X44 , // 216
  0X77 , 0X47 , 0X74 , 0X47 , // 217
  0X77 , 0X47 , 0X74 , 0X74 , // 218
  0X77 , 0X47 , 0X74 , 0X77 , // 219
  0X77 , 0X47 , 0X77 , 0X44 , // 220
  0X77 , 0X47 , 0X77 , 0X47 , // 221
  0X77 , 0X47 , 0X77 , 0X74 , // 222
  0X77 , 0X47 , 0X77 , 0X77 , // 223
  0X77 , 0X74 , 0X44 , 0X44 , // 224
  0X77 , 0X74 , 0X44 , 0X47 , // 225
  0X77 , 0X74 , 0X44 , 0X74 , // 226
  0X77 , 0X74 , 0X44 , 0X77 , // 227
  0X77 , 0X74 , 0X47 , 0X44 , // 228
  0X77 , 0X74 , 0X47 , 0X47 , // 229
  0X77 , 0X74 , 0X47 , 0X74 , // 230
  0X77 , 0X74 , 0X47 , 0X77 , // 231
  0X77 , 0X74 , 0X74 , 0X44 , // 232
  0X77 , 0X74 , 0X74 , 0X47 , // 233
  0X77 , 0X74 , 0X74 , 0X74 , // 234
  0X77 , 0X74 , 0X74 , 0X77 , // 235
  0X77 , 0X74 , 0X77 , 0X44 , // 236
  0X77 , 0X74 , 0X77 , 0X47 , // 237
  0X77 , 0X74 , 0X77 , 0X74 , // 238
  0X77 , 0X74 , 0X77 , 0X77 , // 239
  0X77 , 0X77 , 0X44 , 0X44 , // 240
  0X77 , 0X77 , 0X44 , 0X47 , // 241
  0X77 , 0X77 , 0X44 , 0X74 , // 242
  0X77 , 0X77 , 0X44 , 0X77 , // 243
  0X77 , 0X77 , 0X47 , 0X44 , // 244
  0X77 , 0X77 , 0X47 , 0X47 , // 245
  0X77 , 0X77 , 0X47 , 0X74 , // 246
  0X77 , 0X77 , 0X47 , 0X77 , // 247
  0X77 , 0X77 , 0X74 , 0X44 , // 248
  0X77 , 0X77 , 0X74 , 0X47 , // 249
  0X77 , 0X77 , 0X74 , 0X74 , // 250
  0X77 , 0X77 , 0X74 , 0X77 , // 251
  0X77 , 0X77 , 0X77 , 0X44 , // 252
  0X77 , 0X77 , 0X77 , 0X47 , // 253
  0X77 , 0X77 , 0X77 , 0X74 , // 254
  0X77 , 0X77 , 0X77 , 0X77 , // 255
};

uint8_t ws_buffer[LED_BUFFER_LENGTH];

void encode_byte(uint8_t data, int16_t buffer_index) {
  int index = data * 4;
  ws_buffer[buffer_index++] = leddata[index++];
  ws_buffer[buffer_index++] = leddata[index++];
  ws_buffer[buffer_index++] = leddata[index++];
  ws_buffer[buffer_index++] = leddata[index++];
}

void generate_ws_buffer(uint8_t RData, uint8_t GData, uint8_t BData, int16_t led_no) {
  //ws2812b
  //G--R--B
  //MSB first	
  int offset = led_no * 12;
  encode_byte( GData, offset );
  encode_byte( RData, offset+4 );
  encode_byte( BData, offset+8 );   
}

void Send_2812(void)
{   
  HAL_SPI_Transmit_DMA(&hspi1, ws_buffer, LED_BUFFER_LENGTH); 

  // LMAO this defeats the point of DMA?
  while(__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_BSY ));
} 
 
void setAllPixelColor(uint8_t r, uint8_t g, uint8_t b)
{ 
   int i;
   for(i=0;i< LED_NO;i++) {
      generate_ws_buffer( r, g, b, i );
   }
   Send_2812();
}

void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b)
{	 
  generate_ws_buffer( r, g, b, n );
  Send_2812();
}
/**
 * initialize MOSI pin to LOW.  Without this, first time transmit for first LED might be wrong.
 *
 */
void initLEDMOSI(void)
{
   uint8_t buffer0[2] = { 0, 0 };
   HAL_SPI_Transmit(&hspi1, buffer0, 1, 100 );
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  initLEDMOSI();
  while (1)
  {
    int8_t i;
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    #define LED_DELAY (1000 / LED_NO)
    setAllPixelColor( 0, 0, 0);
    HAL_Delay(200);
    // red
    for ( i = 0; i < LED_NO; i++) {
       setPixelColor( i, 20, 0, 0 );
       HAL_Delay(LED_DELAY);
    }
    // green
    for ( i = 0; i < LED_NO; i++) {
       setPixelColor( i, 0, 20, 0 );
       HAL_Delay(LED_DELAY);
    }
    // blue
    for ( i = 0; i < LED_NO; i++) {
       setPixelColor( i, 0, 0, 20 );
       HAL_Delay(LED_DELAY);
    }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins : PC13 PC14 PC15 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PD0 PD1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3
                           PA4 PA6 PA8 PA9
                           PA10 PA11 PA12 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9
                          |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB10
                           PB11 PB12 PB13 PB14
                           PB15 PB4 PB5 PB6
                           PB7 PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure peripheral I/O remapping */
  __HAL_AFIO_REMAP_PD01_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
