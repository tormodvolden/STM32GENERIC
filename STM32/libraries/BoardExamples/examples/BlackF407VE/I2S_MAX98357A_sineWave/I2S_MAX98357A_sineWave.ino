/*
  I2S sine wave

  This example produces a digital sine wave on the I2S interface of the
  microcontroller.

  Hardware:
   microcontroller board: STM32F407VE (  512MB flash )
                          STM32F407VG ( 1024MB flash )

   amplifier:             Adafruit I2S amplifier with the MAX98357a chip
                          https://www.adafruit.com/product/3006

  Pin description

  sd  = DIN  // I2S data
  ws  = LRC  // left/right channel
  ck  = SCLK // serial data clock

  MARCH 2018 ChrisMicro

*/
#include "I2S.h"

// SPI2 pins are used for I2S.
// SPI2 is avalailable on the BalckF407VE and does not conflict with peripherals like SDIO
I2SClass I2S(SPI2, PB15 /*SD-DIN*/ , PB12 /*WS-LRC*/, PB13 /*CK-SCLK*/);
//I2SClass I2S(SPI2, PC3 /*SD-DIN*/ , PB12 /*WS-LRC*/, PB10 /*CK-SCLK*/);

#define SAMPLINGFREQUENCY 44100
#define NUMBEROFSAMPLES  SAMPLINGFREQUENCY * 1 // 1 seconds

#define DAC_MAX_AMPLITUDE 0x2000 // experimental maximum on my speakers without distortion

void setup()
{
  I2S.begin(I2S_PHILIPS_MODE, SAMPLINGFREQUENCY, 16);
}

void loop()
{
  for (int n = 0; n < NUMBEROFSAMPLES; n++) {
    const float   frequency = 440;
    const float   amplitude = DAC_MAX_AMPLITUDE;
    int16_t val = ( sin( 2 * PI * frequency / SAMPLINGFREQUENCY * n )) * amplitude;
    // the MAX98357a is only single channel. Writting both channels increases the resulting loudness
    I2S.write(val); //left
    I2S.write(val); //right
  }
  delay(3000);
}
