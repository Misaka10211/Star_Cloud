# 星云项目 Star_Cloud
造一朵粘人的云  
Smart Cloud Robot  

**【硬件 Hardware】**  
Arduino NANO  
3.7V-5V 稳压模块
8*8热成像模块 AMG8833  
2路直流电机驱动模块 DRV8833  
https://blog.csdn.net/qq_44897194/article/details/105524808  
空心杯电机  
G51锂电池太阳能充电板  
锂电池1000mAh  
太阳能板  
（可选）气压模块GY68 BMP180  

**模块测试**
- [x] 热成像模块AMG8833
- [x] 直流电机驱动模块DRV8833
- [ ] 气压模块GY68 BMP180  

**程序开发**  
- [x] 热成像识别算法
- [ ] 飞控程序
- [ ] 气压限高控制

**接线**  
*Arduino NANO*  
VIN -- 5V out(稳压模块)  
GND -- GND (稳压模块)  

*AMG8833*  
SCL -- A5(SCL)  
SDA -- A4(SDA)  
VCC -- 5V  
GND -- GND  

*DVR8833*  
M1in -- 5  
M2in -- 6  
M3in -- 7  
M4in -- 8  

**重量统计**  
锂电池        7.01g  
稳压模块      1.06g  
Arduino NANO  3.05g  
AMG8833       2.16g  
DRV8833       1.95g  
空心杯电机    0.74g x2  
螺旋桨        0.25g x2  
气球          4g x5

总计          37.21g  

重量-体积 换算公式 1.14g = 1L(氦气)  
所需氦气体积 32.64L  
