/***************************************************************************
  This is a library for the AMG88xx GridEYE 8x8 IR camera

  This sketch tries to read the pixels from the sensor

  Designed specifically to work with the Adafruit AMG88 breakout
  ----> http://www.adafruit.com/products/3538

  These sensors use I2C to communicate. The device's I2C address is 0x69

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Dean Miller for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <Adafruit_AMG88xx.h>
//定义移动、转向时电机运转时长（ms）
#define MoveTime 500
#define TurnTime 200

Adafruit_AMG88xx amg;

float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
float MINS[5];

void setup() {
    Serial.begin(9600);
    Serial.println(F("AMG88xx pixels"));

    bool status;
    
    // default settings
    status = amg.begin();
    if (!status) {
        Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
        while (1);
    }
    
    Serial.println("-- Pixels Test --");

    Serial.println();

    delay(100); // let sensor boot up
    
}


void loop() { 
    //read all the pixels
    amg.readPixels(pixels);

    //计算平均温度
    float sum=0.0;
    for(int i=1; i<=AMG88xx_PIXEL_ARRAY_SIZE; i++){
      sum+=pixels[i-1];
    }
    float avg = sum/64;
    
    //识别热源并输出图像
    for(int i=0;i<5;i++){
      MINS[i]=i;
    }
    float Min=0.0;
    int min_index=0;
    
    Serial.print("[");
    for(int i=1; i<=AMG88xx_PIXEL_ARRAY_SIZE; i++){
      if(pixels[i-1]>avg){
        Serial.print("* ");
      }
      else{
        Serial.print("o ");
      }
      if(pixels[i-1]>Min){//把表内最小值替换为更大的值
        MINS[min_index]=pixels[i-1];
      }
      Min=999.9;
      for(int i=0;i<5;i++){//更新表内当前最小值信息
        if(MINS[i]<Min){
          min_index=i;
          Min=MINS[i];
        }
      }
      //Serial.print(pixels[i-1]);
      //Serial.print(", ");
      if( i%8 == 0 ) Serial.println();
    }
    Serial.print("] Ref:");
    Serial.print(amg.readThermistor());
    Serial.print(" *C  ");
    Serial.print(avg);
    Serial.print(" OPT:");
    float SUM=0.0;
    for(int i=0;i<5;i++){
      SUM+=MINS[i];
    }
    float opt_avg=SUM/5;
    //opt_avg:优化平均值,更接近热源温度。
    Serial.print(opt_avg);
    Serial.println();
    //判断是否前进
    float base_temp = 24; //基准温度（可能根据季节、天气有所调整）
    float act_diff=1.5; //行动阈值，超过后调整距离。控制移动的灵敏度
    if(opt_avg<(base_temp-act_diff)){//离热源太远
      move_forward();
    }
    if(opt_avg>(base_temp+act_diff)){//离热源太近
      move_backward()
    }
    
    
    //判断热源方位
    float act_value = 3; //行动阈值，超过后调整方向。控制转向的灵敏度
    int left = 0;
    int right = 0;
    float K = 0.0;
    for(int i=1; i<=AMG88xx_PIXEL_ARRAY_SIZE; i++){
      if(pixels[i-1]%8<4){left+=1;}
      else{right+=1;}
    }
    right=max(1,right);//防止div by 0
    K=left/right;
    if(K>act_value){//热源偏左
      move_left();
    }
    if(K<(1/act_value)){//热源偏右
      move_right();
    }
    
    //delay a second
    delay(500);
}

//在开头定义了：移动、转向时电机运转时长（ms）MoveTime TurnTime
void move_forward(){
  //向前移动
}
void move_backward(){
  //向后移动
}

void move_left(){
  //向左转向
}
void move_right(){
  //向右转向
}
