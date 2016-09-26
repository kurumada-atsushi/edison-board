import mraa
import time

i2c = mraa.I2c(0)
i2c.address(0x48)

while True:
  d = i2c.read(2)
  temp = (d[0] * 256.0 + d[1]) / 128.0
  print(temp)
  time.sleep(1)
