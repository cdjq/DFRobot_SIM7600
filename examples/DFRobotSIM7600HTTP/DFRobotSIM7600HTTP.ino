/*!
   * @file DFRobotSIM7600HTTP.ino
   * @brief 验证HTTP请求上的HTTP连接
   * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
   * @license     The MIT License (MIT)
   * @author      [Baikunlin](kunlin.bai@dfrobot.com)
   * @version  V1.0
   * @date  2023-01-30
   * @url https://github.com/DFRobot/DFRobot_SIM7600
   */



#include <DFRobot_SIM7600.h>

//This URL is use for post data to tlink
#define POSTURL   "api.tlink.io/tlink_interface/api/device/createDataPonit.htm"
//This URL is use for get data from tlink, please change the SENSORID to your sensorsId
#define GETURL    "api.tlink.io/tlink_interface/api/device//getDataPoint_SENEORID.htm"

//Login website (https://www.tlink.io/) to register an account ,fill the following information based on your account
#define deviceNo  "DEVICE NO" //Device serial number
#define sensorsId "SENSOR ID" //sensor ID
#define value     "VALUE"

//如果是Arduino Leonardo 软串口RX引脚为8，TX为7
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

  Serial.println("Check SIM card......");
  if(sim7600.checkSIMStatus()){                              //Check SIM card
    Serial.println("SIM card READY");
  }else{
    Serial.println("SIM card ERROR, Check if you have insert SIM card and restart SIM7600");
    while(1);
  }

  Serial.println("Set net mode......");
  while(1){
    if(sim7600.setNetMode(sim7600.eLTE)){                    //Set net mod LTE
      Serial.println("Set LTE mode");
      break;
    }else{
      Serial.println("Fail to set mode");
      delay(1000);
    }
  }

  Serial.println("Get signal quality......");
  delay(1500);
  int signalStrength = sim7600.querySignal();               //Check signal quality
  Serial.print("signalStrength =");
  Serial.println(signalStrength);
  delay(500);

  Serial.print("POST to ");
  Serial.println(POSTURL);
  String httpbuff;
  httpbuff += "{\"deviceNo\":\"";                          //{
  httpbuff += deviceNo;                                    //   "deviceNo" : "DEVICE NO",
  httpbuff += "\",\"sensorDatas\":[{\"sensorsId\":";       //      "sensorDatas":[{
  httpbuff += sensorsId;                                   //          "sensorsId" :  SENSOR ID,
  httpbuff += ",\"value\":\"";                             //          "value"     : "  VALUE  "
  httpbuff += value;                                       //       }]
  httpbuff += "\"}]}";
  char data[httpbuff.length()+1];
  httpbuff.toCharArray(data,httpbuff.length()+1);
  if(sim7600.httpPost(POSTURL,data)){                       //HTTP POST
    Serial.println("Connected !");
    }else{
    Serial.println("Failed to connect");
  }

  Serial.print("GET from ");
  Serial.println(GETURL);
  sim7600.httpGet(GETURL);                                  //HTTP GET
  
  Serial.println("Read the Response Informat of HTTP");
  int readLength = 100;
  char readBuff[readLength];
  if(sim7600.httpRead(readBuff,readLength)){                //Read the Response Informat of HTTP
    Serial.println(readBuff);
  }

  Serial.println("Disconnect");
  sim7600.httpDisconnect();

  Serial.println("Turn off SIM7600");
  sim7600.turnOFF();                                       //Turn OFF SIM7000

}

void loop() {

  delay(1000);

}
