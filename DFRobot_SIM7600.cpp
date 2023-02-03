#include <DFRobot_SIM7600.h>

DFRobot_SIM7600::DFRobot_SIM7600(Stream *s):DFRobot_SIMcore(s)
{
  _s = s;
}

bool DFRobot_SIM7600::makeEcall(const char *num)
{
  sendCmd("AT+CECALLS=");
  sendCmd(num);
  if(checkSendCmd(",1\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::hangUpEcall(const char *n)
{
  sendCmd("AT+CECALLE=");
  sendCmd(n);
  if(checkSendCmd("\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::setPosition(const char *lon,const char *lat)
{
  sendCmd("AT+CECALLPOS=\"");
  sendCmd(lon);
  sendCmd("\",\"");
  sendCmd(lat);
 if(checkSendCmd("\"\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::enableLAN(const char *onoff)
{
  sendCmd("AT+CENABLELAN=");
  sendCmd(onoff);
  if(checkSendCmd("\r\n","OK")){
    return true;
  }
  return false;
}



bool DFRobot_SIM7600::setLANmode(const char *mode)
{
  sendCmd("AT+CLANMODE=");
  sendCmd(mode);
  if(checkSendCmd("\r\n","OK")){
    return true;
  }
  return false;
}

bool DFRobot_SIM7600::setLANconfigure(const char *ip,const char *netmask)
{
  sendCmd("AT+CLANCTRL=3,\"");
  sendCmd(ip);
  if(netmask!=NULL){
	sendCmd("\",\"");
    sendCmd(netmask);
  }
  if(checkSendCmd("\"\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::callDialNumber(const char *number)
{
  sendCmd("ATD");
  sendCmd(number);
  if(checkSendCmd(";\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::callAnswer(void)
{
  if(checkSendCmd("ATA\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::disconnectCall(void)
{
  if(checkSendCmd("AT+CVHU=0\r\n","OK")){
    if(checkSendCmd("ATH\r\n","OK")){
      return true;
    }
    return false;
  }
  return false;
}


bool DFRobot_SIM7600::selectPhonebookStorage(const char *storage)
{
  sendCmd("AT+CPBS=\"");
  sendCmd(storage);
  if(checkSendCmd("\"\r\n","OK")){
    return true;
  }
  return false;	
}


char* DFRobot_SIM7600::findPhonebook(const char *findtext)
{
  char buf[100];
  cleanBuffer(&buf[0],100);
  sendCmd("AT+CPBF=\"");
  sendCmd(findtext);
  sendCmd("\"\r\n");
  readBuffer(&buf[0],100);
  if(NULL != strstr(buf, "OK")){
    return strstr(buf, "\n");
  }
  return strstr(buf, "ERROR");
}


bool DFRobot_SIM7600::writePhonebook(const char *index,const char *number,const char *type,const char *text)
{
  sendCmd("AT+CPBW=");
  sendCmd(index);
  sendCmd(",\"");
  sendCmd(number);
  sendCmd("\",");
  sendCmd(type);
  sendCmd(",\"");
  sendCmd(text);
  if(checkSendCmd("\"\r\n","OK")){
    return true;
  }
  return false;	
}


bool DFRobot_SIM7600::mqttConnect(const char *clientID,const char *serverAddr,const char *userName,const char *password)
{
  char clientIndex[4];
  itoa(MQTT_CLIENT_INDEX, clientIndex, 10);
  mqttDisconnect();
  if(!checkSendCmd("AT+CMQTTSTART\r\n","OK")){
    return false;
  }
  sendCmd("AT+CMQTTACCQ=");
  sendCmd(clientIndex);
  sendCmd(",\"");
  sendCmd(clientID);
  if(!checkSendCmd("\"\r\n","OK")){
    return false;
  }
  sendCmd("AT+CMQTTCONNECT=");
  sendCmd(clientIndex);
  sendCmd(",\"");
  sendCmd(serverAddr);
  sendCmd("\",60,1");
  if(userName != NULL){
	  sendCmd(",\"");
	  sendCmd(userName);
	  sendCmd("\",\"");
	  sendCmd(password);
	  sendCmd("\"");
  }
  if(checkSendCmd("\r\n","OK")){
    return true;
  }
  return false;	
}


bool DFRobot_SIM7600::mqttDisconnect(void)
{
  char clientIndex[4];
  itoa(MQTT_CLIENT_INDEX, clientIndex, 10);
  sendCmd("AT+CMQTTDISC=");
  sendCmd(clientIndex);
  checkSendCmd(",120\r\n","OK");
  delay(100);
  sendCmd("AT+CMQTTREL=");
  sendCmd(clientIndex);
  checkSendCmd("\r\n","OK");
  delay(100);
  checkSendCmd("AT+CMQTTSTOP\r\n","OK");
  return true;
}


bool DFRobot_SIM7600::mqttPublish(const char *topic,const char *data)
{
  char topicLenth[4];
  char dataLenth[4];
  char clientIndex[4];
  itoa(MQTT_CLIENT_INDEX, clientIndex, 10);
  snprintf(topicLenth, sizeof(topicLenth), "%d", strlen(topic));
  snprintf(dataLenth, sizeof(dataLenth), "%d", strlen(data));
  sendCmd("AT+CMQTTTOPIC=");
  sendCmd(clientIndex);
  sendCmd(",");
  sendCmd(topicLenth);
  if(!checkSendCmd("\r\n",">")){
    return false;
  } 
  sendCmd(topic);
  if(!checkSendCmd("\r\n","OK")){
    return false;
  }
  sendCmd("AT+CMQTTPAYLOAD=");
  sendCmd(clientIndex);
  sendCmd(",");
  sendCmd(dataLenth);
  if(!checkSendCmd("\r\n",">")){
    return false;
  }
  sendCmd(data);
  if(!checkSendCmd("\r\n","OK")){
    return false;
  } 
  if(checkSendCmd("AT+CMQTTPUB=0,1,60\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::mqttSubscribe(const char *topic)
{
  char topicLenth[4];
  char clientIndex[4];
  itoa(MQTT_CLIENT_INDEX, clientIndex, 10);
  snprintf(topicLenth, sizeof(topicLenth), "%d", strlen(topic));
  sendCmd("AT+CMQTTSUBTOPIC=");
  sendCmd(clientIndex);
  sendCmd(",");
  sendCmd(topicLenth);
  if(!checkSendCmd(",1\r\n",">")){
    return false;
  }
  sendCmd(topic);
  if(!checkSendCmd("\r\n","OK")){
    return false;
  }
  if(checkSendCmd("AT+CMQTTSUB=0\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::mqttUnsubscribe(const char *topic)
{
  char topicLenth[4];
  char clientIndex[4];
  itoa(MQTT_CLIENT_INDEX, clientIndex, 10);
  snprintf(topicLenth, sizeof(topicLenth), "%d", strlen(topic));
  sendCmd("AT+CMQTTUNSUB=");
  sendCmd(clientIndex);
  sendCmd(",");
  sendCmd(topicLenth);
  if(!checkSendCmd(",0\r\n",">")){
    return false;
  }
  sendCmd(topic);
  if(checkSendCmd("\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::checkSIMStatus(void)
{
  int count = 0;
  while(count < 3){
    if(checkSendCmd("AT\r\n","OK")){
      break;
    }else{
      count++;
      delay(300);
    }
  }
  if(count == 3){
    return false;
  }
  count = 0;
  while(count < 3){
    if(checkSendCmd("AT+CPIN?\r\n","READY")){
      break;
    }else{
      count++;
      delay(300);
    }
  }
  if(count == 3)
    return false;
  return true;
}


bool DFRobot_SIM7600::setNetMode(eNet net)
{
  if(net == eLTE){
    if(checkSendCmd("AT+CNMP=38\r\n","OK")){
      delay(300);
      return true;
    }else{
      return false;
    }
  }else if(net == eGSM){
    if(checkSendCmd("AT+CNMP=13\r\n","OK")){
      delay(300);
      return true;
    }
  }else{
    Serial.println("No such mode!");
  }
  return false;
}


bool DFRobot_SIM7600::setBaudRate(long rate)
{
  char rateBuff[10];
  sprintf(rateBuff,"%ld",rate);
  sendCmd("AT+IPR=");
  sendCmd(rateBuff);
  if(checkSendCmd("\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::httpConnect(const char *host)
{
  httpDisconnect();
  delay(1000);
  if(!checkSendCmd("AT+HTTPINIT\r\n","OK")){
    return false;
  }
  sendCmd("AT+HTTPPARA=\"URL\",\"");
  sendCmd(host);
  if(checkSendCmd("\"\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::httpDisconnect(void)
{
  if(checkSendCmd("AT+HTTPTERM\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::httpPost(const char *host , const char *data)
{
  char buf[50];
  char dataLenth[4];
  snprintf(dataLenth, sizeof(dataLenth), "%d", strlen(data));
  if(!httpConnect(host)){
    return false;
  }
  sendCmd("AT+HTTPDATA=");
  sendCmd(dataLenth);
  sendCmd(",4000\r\n");
  if(!checkSendCmd("\r\n","DOWNLOAD")){
    return false;
  }
  sendCmd(data);
  if(!checkSendCmd("\r\n","OK")){
    return false;
  }
  sendCmd("AT+HTTPACTION=1\r\n");
  uint64_t timecnt = millis();
  while(1){
    readBuffer(buf,50);
	if(NULL != strstr(buf,"+HTTPACTION:")){
	  if(NULL != strstr(buf,"200")){
        break;
      }else{
		  return false;
	  }
	}
	if((millis()-timecnt) > (2000)){
      return false;
    }
    delay(500);	
  }
  return true;
}


bool DFRobot_SIM7600::httpGet(const char *host)
{
  char buf[50];
  if(!httpConnect(host)){
    return false;
  }
  sendCmd("AT+HTTPACTION=0\r\n");
  while(1){
    readBuffer(buf,50);
	if(NULL != strstr(buf,"+HTTPACTION:")){
	  if(NULL != strstr(buf,"200")){
        break;
      }else{
		  return false;
	  }
	} 
  }
  return true;
}


bool DFRobot_SIM7600::httpRead(char* buf,long length){
  char lengthBuff[4];
  char readHead[45];
  char readTail[16];
  itoa(length, lengthBuff, 10);
  sendCmd("AT+HTTPREAD=");
  sendCmd(lengthBuff);
  sendCmd("\r\n");
  cleanBuffer(&readHead[0],46);
  readBuffer(&readHead[0],45);
  if(NULL == strstr(readHead,"OK")){
    return false;
  }
  cleanBuffer(&buf[0],length+1);
  readBuffer(&buf[0],length);
  cleanBuffer(&readTail[0],16+1);
  readBuffer(&readTail[0],16);
  if(NULL == strstr(readTail,"+HTTPREAD: 0")){
    return false;
  }
  return true;
}


bool DFRobot_SIM7600::startGPS(void)
{
  stopGPS();
  if(checkSendCmd("AT+CGPS=1\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::stopGPS(void)
{
  char buf[20];
  cleanBuffer(&buf[0],20);
  sendCmd("AT+CGPS=0\r\n");
  readBuffer(&buf[0],19);
  if(strstr(buf,"OK")){
    uint64_t timecnt = millis();
	while(1){
	  readBuffer(&buf[0],19);
	  if(strstr(buf,"+CGPS: 0")){
        return true;
	  }
	  if((millis()-timecnt)>2000){
        return false;
	  }
	}
  }
  return false;
}


String DFRobot_SIM7600::getGPS(void)
{
  delete [] _readBuf; 
  _readBuf = new char[100];
  if(!startGPS()){
	  return "ERROR";
  }
  cleanBuffer(&_readBuf[0],100);
  sendCmd("AT+CGPSINFO\r\n");
  readBuffer(&_readBuf[0],99);
  return GPSDataProcessing(strstr(_readBuf,"\n"));
}


bool DFRobot_SIM7600::startTCPIP(void)
{
  stopTCPIP();
  if(checkSendCmd("AT+NETOPEN\r\n","OK")){
    return true;
  }
  return false;
}

bool DFRobot_SIM7600::stopTCPIP(void)
{
  if(checkSendCmd("AT+NETCLOSE\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::tcpipConnect(int linkNum, const char *type,long port,const char *serverIP)
{
  char num[4];
  itoa(linkNum, num, 10);
  if(!startTCPIP()){
    return false;
  }
  sendCmd("AT+CIPOPEN=");
  sendCmd(num);
  sendCmd(",\"");
  sendCmd(type);
  itoa(port, num, 10);
  if(strcmp(type,"TCP")==0){
    sendCmd("\",\"");
    sendCmd(serverIP);
    sendCmd("\",");
    sendCmd(num);
  }else if(strcmp(type,"UDP")==0){
    sendCmd("\",,,");
    sendCmd(num);
  }else{
	  return false;
  }
  if(checkSendCmd("\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::sendTCPIP(uint8_t linkNum,const char *data)
{
  char num[4];
  itoa(linkNum, num, 10);
  char dataLenth[4];
  snprintf(dataLenth, sizeof(dataLenth), "%d", strlen(data));
  sendCmd("AT+CIPSEND=");
  sendCmd(num);
  sendCmd(",");
  sendCmd(dataLenth);
  if(!checkSendCmd("\r\n",">")){
    return false;
  }
  sendCmd(data);
  if(checkSendCmd("\r\n","OK")){
    return true;
  }
  return false;	
}


void DFRobot_SIM7600::retrieveTCPIP(const char *linkNum,long length)
{
  char lengthBuff[10];
  sprintf(lengthBuff,"%ld",length);
  sendCmd("AT+CIPRXGET=2,");
  sendCmd(linkNum);
  sendCmd(",");
  sendCmd(lengthBuff);
  sendCmd("\r\n"); 
}


bool DFRobot_SIM7600::setPhoneFunctiona(const char *fun)
{
  sendCmd("AT+CFUN=");
  sendCmd(fun);
  if(checkSendCmd("\r\n","OK")){
    return true;
  }
  return false;
}


int DFRobot_SIM7600::querySignal(void)
{
  char  signalBuffer[100];
  int i = 0,j = 0,k = 0;
  char *signalQuality;
  cleanBuffer(signalBuffer,100);
  sendCmd("AT+CSQ\r\n");
  readBuffer(signalBuffer,100);
  if(NULL != (signalQuality = strstr(signalBuffer, "+CSQ:"))){
    i = *(signalQuality + 6) - 48;
    j = *(signalQuality + 7) - 48;
    k =  (i * 10) + j;
  }else{
    return 0;
  }
  if( k == 99){
    return 0;
  }else{
    return k;
  }
}


bool DFRobot_SIM7600::sendMessage(const char *data,const char *number)
{
  char dataBuff[1]={0x1a};
  if(!checkSendCmd("AT+CMGF=1\r\n","OK")){
    return false;
  }
  sendCmd("AT+CMGS=\"");
  sendCmd(number);
  sendCmd("\"\r\n");
  if(!checkSendCmd("\"\r\n",">")){
    return false;
  }
  sendCmd(data);
  sendCmd(dataBuff);
  if(checkSendCmd("","OK")){
    return true;
  }
  return false;
}


char* DFRobot_SIM7600::readMessage(uint8_t index)
{
  char num[4];
  itoa(index, num, 10);
  delete [] _readBuf; 
  _readBuf = new char[1024];
  cleanBuffer(&_readBuf[0],1024);
  sendCmd("AT+CMGR=");
  sendCmd(num);
  sendCmd("\r\n");
  readBuffer(&_readBuf[0],1024);
  if(NULL != strstr(_readBuf, "OK")){
    return strstr(_readBuf, "\n");
  }else{
    return strstr(_readBuf, "ERROR");
  }
}


bool DFRobot_SIM7600::textToSpeechTTS(const char *text)
{
  sendCmd("AT+CTTS=2,\"");
  sendCmd(text);
  if(checkSendCmd("\"\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::recordWavAudio(const char *fileName)
{
  sendCmd("AT+CREC=1,\"");
  sendCmd(fileName);
  if(checkSendCmd("\"\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::stopRecording(void)
{
  if(checkSendCmd("AT+CREC=0\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::playAudio(const char *fileName)
{
  char buf[100];
  cleanBuffer(&buf[0],100);
  sendCmd("AT+CCMXPLAY=\"");
  sendCmd(fileName);
  sendCmd("\",0,0");
  if(checkSendCmd("\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::audioPlayStop(void)
{
  if(checkSendCmd("AT+CCMXSTOP\r\n","OK")){
    return true;
  }
  return false;
}

bool DFRobot_SIM7600::startSSL(void)
{
  stopSSL();
  if(checkSendCmd("AT+CCHSTART\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::stopSSL(void)
{
  if(checkSendCmd("AT+CCHSTOP\r\n","OK")){
    return true;
  }
  return false;
}

bool DFRobot_SIM7600::connectSSL(const char *sessionId,const char *host,const char *port)
{
  if(!startSSL()){
    return false;
  }
  sendCmd("AT+CCHOPEN=");
  sendCmd(sessionId);
  sendCmd(",\"");
  sendCmd(host);
  sendCmd("\",");
  sendCmd(port);
  sendCmd(",2");
  if(checkSendCmd("\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::disconnectSSL(const char *sessionId)
{
  sendCmd("AT+CCHCLOSE=");
  sendCmd(sessionId);
  if(checkSendCmd("\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::sendSSL(const char *sessionId,int length,const char *data)
{
  char num[4];
  itoa(length, num, 10);
  sendCmd("AT+CCHSEND=");
  sendCmd(sessionId);
  sendCmd(",");
  sendCmd(num);
  if(!checkSendCmd("\r\n",">")){
    return false;
  }
  sendCmd(data);
  if(checkSendCmd("\r\n","OK")){
    return true;
  }
  return false;
}


void DFRobot_SIM7600::readSSL(const char *sessionId)
{
  sendCmd("AT+CCHRECV=");
  sendCmd(sessionId);
  sendCmd("\r\n");
}


bool DFRobot_SIM7600::startFTPS(void)
{
  stopFTPS();
  if(checkSendCmd("AT+CFTPSSTART\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::stopFTPS(void)
{
  logoutFTPS();
  
  if(checkSendCmd("AT+CFTPSSTOP\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::loginToFTPS(const char *host,const char *port,const char *username,const char *password,uint8_t serverType)
{
  char num[4];
  char buf[100];
  if(!startFTPS()){
    return false;
  }
  itoa(serverType, num, 10);
  sendCmd("AT+CFTPSLOGIN=\"");
  sendCmd(host);
  sendCmd("\",");
  sendCmd(port);
  sendCmd(",\"");
  sendCmd(username);
  sendCmd("\",\"");
  sendCmd(password);
  sendCmd("\",");
  sendCmd(num);
  sendCmd("\r\n");
  cleanBuffer(&buf[0],100);
  readBuffer(&buf[0],99);
  if(strstr(buf, "OK")){
    uint64_t timecnt = millis();
    while(1){
      readBuffer(&buf[0],39);
	  if(strstr(buf, "+CFTPSLOGIN: 0")){
        return true;  
	  }
	  if((millis()-timecnt) > 2000){
        return false;
      }
	}
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::logoutFTPS(void)
{
  if(checkSendCmd("AT+CFTPSLOGOUT\r\n","OK")){
    return true;
  }
  return false;
}


char* DFRobot_SIM7600::getFTPSDirectory(void)
{
  char buf[100];
  cleanBuffer(&buf[0],100);
  sendCmd("AT+CFTPSPWD\r\n");
  readBuffer(&buf[0],100);
  if(strstr(buf, "OK")){
    return strstr(buf, "+CFTPSPWD:");
  }
  return strstr(buf, "ERROR");
}


bool DFRobot_SIM7600::setHTPInfo(const char *cmd,const char *host,const char *port,const char *httpVersion)
{
  sendCmd("AT+CHTPSERV=\"");
  if(strcmp(cmd,"DEL")==0){
	sendCmd(cmd);
	sendCmd("\",");
	sendCmd(host);
  }else if(strcmp(cmd,"ADD")==0){
	sendCmd(cmd);
	sendCmd("\",\"");
    sendCmd(host);
    sendCmd("\",");
    sendCmd(port);
    sendCmd(",");
    sendCmd(httpVersion);
  }
  if(checkSendCmd("\r\n","OK")){
    return true;
  }
  return false;
}


bool DFRobot_SIM7600::updatingDateTime(void)
{
  if(checkSendCmd("AT+CHTPUPDATE\r\n","OK")){
    return true;
  }
  return false;
}

bool DFRobot_SIM7600::updateSystemTime(const char *host,const char *timezone)
{
  sendCmd("AT+CNTP=\"");
  sendCmd(host);
  sendCmd("\",");
  sendCmd(timezone);
  if(!checkSendCmd("\r\n","OK")){
    return false;
  }
  if(checkSendCmd("AT+CNTP\r\n","OK")){
    return true;
  }
  return false;
}


String DFRobot_SIM7600::netRegistrationStatus(void)
{
  char buf[100];
  String status;
  cleanBuffer(&buf[0],100);
  sendCmd("AT+CGREG?\r\n");
  readBuffer(&buf[0],100);
  if(NULL == strstr(buf, "OK")){
    return "error";
  }
  for(uint8_t i = 0;i < strlen(buf);i++){
    if((int(buf[i])>47&&int(buf[i])<58)||(buf[i]==',')){
      status+=buf[i];
    }
  }  
  return status;
}


String DFRobot_SIM7600::GPSFormulaConversion(const char* lat,const char* log)
{
  String latDegree = String(int(atof(lat)/100));
  int size = 0;
  while(lat[size] != '.'){
    size++;
  }
  String latBuff;
  int latIndex = size-1;
  int latRemainder=lat[size-2]-48;
  for(uint8_t i = 0;i < strlen(lat)-size;i++){
    if(lat[latIndex] == '.'){
  	  latIndex++;
    }
    latBuff += String( ( ( (int)(lat[latIndex]-48)+(latRemainder*10) )/6) );
    latRemainder = ((int)(lat[latIndex]-48)+(latRemainder*10))%6;
    latIndex++;
    if(latIndex==int(strlen(lat))){
      if(latRemainder*10%6*10/6>=5){
        latBuff += String(latRemainder*10/6+1);
      }else{
        latBuff += String(latRemainder*10/6);
      }
    }
  }
  String latString = latDegree+'.'+latBuff;
  
  String logDegree = String(int(atof(log)/100));
  size = 0;
  while(log[size] != '.'){
    size++;
  }
  String logBuff;
  int logIndex = size-1;
  int logRemainder = log[size-2]-48;
  for(uint8_t i = 0;i < strlen(log)-size;i++){
    if(log[logIndex] == '.'){
      logIndex++;
    }
    logBuff += String( ( ( (int)(log[logIndex]-48) + (logRemainder*10) )/6) );
    logRemainder = ((int)(log[logIndex]-48)+(logRemainder*10))%6;
    logIndex++;
    if(logIndex==int(strlen(log))){
      if(logRemainder*10%6*10/6>=5){
        logBuff += String(logRemainder*10/6+1);
      }else{
        logBuff += String(logRemainder*10/6);
	  }
    }
  }
 
  String logString = logDegree+'.'+logBuff; 
  return latString+','+logString;
}


String DFRobot_SIM7600::GPSDataProcessing(const char* data)
{
  int latSign=0;
  int logSign=0;
  String lat;
  String log;
  for(uint8_t i = 0;i < strlen(data);i++ ){
    if(data[i] == ':'){
      latSign = 1;
    }
    if(data[i] == 'N'){
      logSign = 1;
      latSign = 0;
    }
    if(data[i] == 'E'){
      logSign = 0;
      break;
    }
    if((int(data[i])>47&&int(data[i])<58)||(data[i]=='.')||(data[i]=='-')){
      if(latSign == 1){
        lat += data[i];		
      }else if(logSign == 1){
        log +=data[i];
      }	  
    }
  }
  char latChar[lat.length()+1];
  lat.toCharArray(latChar,lat.length()+1);
  char logChar[log.length()+1];
  log.toCharArray(logChar,log.length()+1);
  if(lat != NULL && log != NULL){
    return GPSFormulaConversion(latChar,logChar);
  }
  return "ERROR";
}