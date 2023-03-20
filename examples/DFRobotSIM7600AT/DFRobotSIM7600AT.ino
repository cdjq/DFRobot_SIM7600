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
#include <DFRobot_SIM7600.h>

//如果是Arduino Leonardo 软串口RX引脚为D8
//SoftwareSerial     mySerial(8,7);
SoftwareSerial     mySerial(7,8);

DFRobot_SIM7600    sim7600(&mySerial);

void setup() {

  Serial.begin(115200);
  mySerial.begin(9600);           //SIM7600默认波特率9600

  Serial.println("Turn ON SIM7600......");
  if(sim7600.turnON()){                                    //Turn ON SIM7000
    Serial.println("Turn ON !");
  }
  delay(2000);
  Serial.println("Set baud rate......");
  while (1){
    if(sim7600.setBaudRate(19200)){                           //Set SIM7600 baud rate to 19200
       mySerial.begin(19200);
      Serial.println("Set baud rate:19200");   
      break;                
    }else{
      Serial.println("Faile to set baud rate");
      delay(1000);
    }
  }

}

void loop() {
  while (mySerial.available()) {
     Serial.write(mySerial.read());//如果Serial收到数据则通过mySerial输出 
  }
  
  while (Serial.available()) {
     mySerial.write(Serial.read());//如果myserial收到数据则通过Serial输出
  }
  delay(500);
}
