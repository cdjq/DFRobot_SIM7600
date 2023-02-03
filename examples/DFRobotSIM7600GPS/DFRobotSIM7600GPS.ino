/*!
   * @file DFRobotSIM7600GPS.ino
   * @brief 获取GPS信息
   * @n 获取GPS信息并打印
   * @n 将获取的GPS度分格式转换为度格式
   * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
   * @license     The MIT License (MIT)
   * @author      [Baikunlin](kunlin.bai@dfrobot.com)
   * @version  V1.0
   * @date  2023-01-30
   * @url https://github.com/DFRobot/DFRobot_SIM7600
   */



#include <DFRobot_SIM7600.h>

#define PIN_TX     8
#define PIN_RX     7


SoftwareSerial     mySerial(PIN_RX,PIN_TX);
DFRobot_SIM7600    sim7600(&mySerial);


void setup() {
  Serial.begin(115200);
  mySerial.begin(19200);

  Serial.println("Set baud rate......");
  while (1){
    if(sim7600.setBaudRate(19200)){
      Serial.println("Set baud rate:19200");
      break;
    }else{
      Serial.println("Faile to set baud rate");
      delay(1000);
    }
  }

  Serial.println("Check SIM card......");
  if(sim7600.checkSIMStatus()){                                //Check SIM card
    Serial.println("SIM card READY");
  }else{
    Serial.println("SIM card ERROR, Check if you have insert SIM card and restart SIM7600");
    while(1);
  }

  Serial.println("Get signal quality......");
  delay(1500);
  int signalStrength = sim7600.querySignal();
  Serial.print("signalStrength =");
  Serial.println(signalStrength);
  delay(500);
}

void loop() {
  
    String GPSBuff; 
    GPSBuff = sim7600.getGPS();

    if(GPSBuff != "ERROR"){
      Serial.print("Longitude and latitude: ");
      Serial.println(GPSBuff);
    }else{
      Serial.println("ERROR");
    }

    delay(500);
}
