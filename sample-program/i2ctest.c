#include <stdio.h>
#include <unistd.h>
#include <mraa.h>
#define ADT7410 (0x48)
#define I2CCH (1)
#define SLEEPTIME (2)
void main(int argc, char **argv)
{
  mraa_i2c_context i2c;
  uint8_t data[2];
  int i;
  int lasttemp;
  mraa_init();
  i2c = mraa_i2c_init(I2CCH);
  mraa_i2c_address(i2c,ADT7410);
  printf("Bus initialized.\n");
  for(i = 0  , lasttemp = 0 ;; ++i)
  {
    int tmpl,tmph,tmp,th,tl;
    int tmh,tml;
    if(0 > mraa_i2c_read(i2c,data,2))
    {
      printf("Read Word Failed.\n");
      exit(1);
    }
  tmph = ((int)(data[0]));
  tmpl = ((int)(data[1]));
  tmp = tmph * 256 + tmpl;
  if(tmp == lasttemp)
  {
    sleep(SLEEPTIME);
    continue;
  }
  lasttemp = tmp;
  tmh = tmp / 128;
  tml = tmp % 128;
  printf("I2C read[%05d][%03d.%02d]\n",i,tmh,tml);
  sleep(SLEEPTIME);
  }
}