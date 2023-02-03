/*!
   * @file DFRobotSIM7600AT.ino
   * @brief SIM7600 AT指令透传
   * @n 将串口的结束符改为换行和回车
   * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
   * @license     The MIT License (MIT)
   * @author      [Baikunlin](kunlin.bai@dfrobot.com)
   * @version  V1.0
   * @date  2023-01-30
   * @url https://github.com/DFRobot/DFRobot_SIM7600
   */


#include <SoftwareSerial.h>

SoftwareSerial     mySerial(7,8); //定义虚拟串口名为myserial,Rx为7号端口,Tx为8号端口

void setup() {

  Serial.begin(115200);
  mySerial.begin(19200);

}

void loop() {
  while (mySerial.available()) {
     Serial.write(mySerial.read());//如果Serial收到数据则通过mySerial输出 
  }
  
  while (Serial.available()) {
     mySerial.write(Serial.read());//如果myserial收到数据则通过Serial输出
  }
}
