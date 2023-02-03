/*!
   * @file DFRobotSIM7600MQTT.ino
   * @brief 从I2C传感器读取数据通过MQTT上传到云平台
   * @n 将I2C传感器读取的数据通过MQTT发送到云平台（I2C传感器为BMX160）
   * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
   * @license     The MIT License (MIT)
   * @author      [Baikunlin](kunlin.bai@dfrobot.com)
   * @version  V1.0
   * @date  2023-01-30
   * @url https://github.com/DFRobot/DFRobot_SIM7600
   */



#include <DFRobot_SIM7600.h>
#include <DFRobot_BMX160.h>

#define SERVER_IP       "tcp://iot.dfrobot.com.cn"
#define CLIENT_ID       "client test0"
#define TOPIC           "JBeYVKA4g"
#define USERNAME        "xcHL4KA4g"
#define PASSWORD        "b5HY4K0VRz"


#define PIN_TX     8
#define PIN_RX     7

DFRobot_BMX160 bmx160;

SoftwareSerial     mySerial(PIN_RX,PIN_TX);
DFRobot_SIM7600    sim7600(&mySerial);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mySerial.begin(19200);

  if (bmx160.begin() != true){                                 //初始化I2C传感器
    Serial.println("init false");
    while(1);
  }
  Serial.println("Set baud rate......");
  while (1){
    if(sim7600.setBaudRate(19200)){                            //Set SIM7600 baud rate to 19200
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

  Serial.println("Set net mode......");
  while(1){
    if(sim7600.setNetMode(sim7600.eLTE)){                       //Set net mod LTE
      Serial.println("Set LTE mode");
      break;
    }else{
      Serial.println("Fail to set mode");
      delay(1000);
    }
  }

  Serial.println("Get signal quality......");
  delay(1500);
  int signalStrength = sim7600.querySignal();                  //Check signal quality
  Serial.print("signalStrength =");
  Serial.println(signalStrength);
  delay(500);



  Serial.print("Connect to : ");
  Serial.println(SERVER_IP);
   while(1){
     if(sim7600.mqttConnect(CLIENT_ID,SERVER_IP,USERNAME,PASSWORD)){            //连接到MQTT服务器
        Serial.println("Connected !");
        break;
      }else{
        Serial.println("Failed to connect");
        delay(1000);
     }
   }
  
  delay(200);

}

void loop() {

  sBmx160SensorData_t  Oaccel;

   /* Get a new sensor event */
  bmx160.getAllData(NULL, NULL, &Oaccel);
  
  String Saccel =" x: "+ String(Oaccel.x)+" y: "+String(Oaccel.y)+" z: "+String(Oaccel.z)+"m/s^2";
  
  char   Caccel[Saccel.length()];
  Saccel.toCharArray(Caccel, Saccel.length());

  if(sim7600.mqttPublish(TOPIC, Caccel)){                   //将I2C信息发送到TOPIC主题
    Serial.println("Send OK");
  }else{
    Serial.println("Failed to send");
    return;
  }

  delay(2000);

}
