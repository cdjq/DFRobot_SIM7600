# DFRobot_SIM7600
* [English Version](./README.md)


![SVG1]

## 产品链接(https://www.dfrobot.com/product-1834.html) 

      SKU:TEL0124

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性)
* [历史](#历史)
* [创作者](#创作者)


## 概述

* 提供了一种直接向SIM7600发送AT命令的方法

## 库安装

在运行此库的demo之前，你需要下载关联库:  https://github.com/DFRobot/DFRobot_SIM
使用此库前，请首先下载库文件，将其粘贴到\Arduino\libraries目录中，然后打开examples文件夹并在该文件夹中运行演示。

## 方法

```C++
  /**
   * @fn turnON
   * @brief 开机
   * @return bool类型 返回指令操作是否成功
   */
  bool turnON(void);
  
  /**
   * @fn turnOFF
   * @brief 关机
   * @return bool类型 返回指令操作是否成功
   */
  bool turnOFF(void);

  /**
   * @fn DFRobot_SIM7600
   * @brief DFRobot_SIMcore constructor of abstract class. Construct serial ports.
   * @param s The pointer to abstract class, where you can fill in the pointer to serial object.
   * @return None
   */
  DFRobot_SIM7600(Stream *s);
  ~DFRobot_SIM7600(){};
	
  /**
   * @fn makeEcall
   * @brief 进行电子呼叫
   * @param num 拨号号码
   * @return bool类型 返回指令操作是否成功
   */
  bool makeEcall(const char *num);
	
  /**
   * @fn hangUpEcall
   * @brief 挂断电子呼叫
   * @param n
   * @n     0–停止活动eCall，将状态更改为“ECALL_APP_ECALL_ACTIVE”并清除callbackTimer
   * @n     1–结束活动ecall，但保持状态“ECALL_APP_IDLE_ALLOW_MT_ECALL”   
   * @return bool类型 返回指令操作是否成功
   */
  bool hangUpEcall(const char *n);
	
  /**
   * @fn setPosition
   * @brief 设置位置信息
   * @param lon 当前位置的经度，格式为ddd.dddddd。单位为度。范围为-180~180
   * @param lat 当前位置的纬度，格式为dd.dddddd。单位为度。范围为-90~90
   * @return bool类型 返回指令操作是否成功
   */
  bool setPosition(const char *lon,const char *lat);
	
  /**
   * @fn enableLAN
   * @brief 启用LAN功能
   * @param onoff 打开或关闭LAN 设置值 0:关闭, 1:打开
   * @return bool类型 返回指令操作是否成功
   */
  bool enableLAN(const char *onoff);
  
  /**
   * @fn setLANmode
   * @brief 设置LAN模式
   * @param mode LAN模式
   * @n     0:局域网模式
   * @n     1:wan模式
   * @n     2:静态ip模式
   * @return bool类型 返回指令操作是否成功
   */
  bool setLANmode(const char *mode);
  
  /**
   * @fn setLANconfigure
   * @brief LAN配置ip地址
   * @param ip ip地址
   * @param netmask 网络掩码
   * @return bool类型 返回指令操作是否成功
   */
  bool setLANconfigure(const char *ip,const char *netmask=NULL);
  
  /**
   * @fn callDialNumber
   * @brief 呼叫拨号号码
   * @param number 电话号码
   * @return bool类型 返回指令操作是否成功
   */
  bool callDialNumber(const char *number);
  
  /**
   * @fn callAnswer
   * @brief 呼叫应答
   * @return bool类型 返回指令操作是否成功
   */
  bool callAnswer(void);
  
  /**
   * @fn disconnectCall
   * @brief 断开呼叫
   * @return bool类型 返回指令操作是否成功
   */
  bool disconnectCall(void);
  
  /**
   * @fn selectPhonebookStorage
   * @brief 选定电话簿存储
   * @param storage 电话簿存储 
   * @n     "DC"-ME已拨电话列表; 容量：最多100个条目
   * @n     "MC"-ME未接（未接）电话列表; 容量：最多100个条目
   * @n     "RC"-ME收到的呼叫列表; 容量：最多100个条目
   * @n     "SM"-SIM电话簿; 容量：取决于SIM卡
   * @n     "ME"-移动设备电话簿; 容量：最多500个条目
   * @n     "FD"-SIM固定拨号电话簿; 容量：取决于SIM卡
   * @n     "ON"-MSISDN列表; 容量：取决于SIM卡
   * @n     "LD"-最后拨打的电话簿号码; 容量：取决于SIM卡
   * @n     "EN"-紧急号码
   * @return bool类型 返回指令操作是否成功
   */
  bool selectPhonebookStorage(const char *storage);
  
   /**
   * @fn findPhonebook
   * @brief 查找电话簿条目
   * @param findtext 名称
   * @return char*类型 返回电话信息
   */
  char* findPhonebook(const char *findtext);
  
  /**
   * @fn writePhonebook
   * @brief 写入电话簿条目
   * @param index 电话簿位置号范围内的整型值
   * @param number 电话号码
   * @param type 整数格式的地址八位字节类型
   * @n     145–当拨号字符串包含国际访问码时字符“+”
   * @n     161–国家编号。
   * @n     177–网络特定号码，ISDN格式
   * @n     129–否则
   * @param text 名称
   * @return bool类型 返回指令操作是否成功
   */
  bool writePhonebook(const char *index,const char *number,const char *type,const char *text);
  
  
  /**
   * @fn mqttConnect
   * @brief 连接mqtt服务器
   * @param clientID 客户端的唯一标识符。字符串长度从1到128字节
   * @param serverAddr 服务器地址和端口
   * @param userName 用户名
   * @param password 密码
   * @return bool类型 返回指令操作是否成功
   */
  bool mqttConnect(const char *clientID,const char *serverAddr,const char *userName = NULL,const char *password = NULL);
  
  /**
   * @fn mqttDisconnect
   * @brief 断开mqtt连接
   * @return bool类型 返回指令操作是否成功
   */
  bool mqttDisconnect(void);
  
  /**
   * @fn mqttPublish
   * @brief 发布消息主题
   * @param topic 发布主题
   * @param data 发布消息
   * @return bool类型 返回指令操作是否成功
   */
  bool mqttPublish(const char *topic,const char *data);
  
  /**
   * @fn mqttSubscribe
   * @brief 订阅主题
   * @param topic 订阅主题
   * @return bool类型 返回指令操作是否成功
   */
  bool mqttSubscribe(const char *topic);
  
  /**
   * @fn mqttUnsubscribe
   * @brief 取消订阅
   * @param topic 订阅主题
   * @return bool类型 返回指令操作是否成功
   */
  bool mqttUnsubscribe(const char *topic);
  
  /**
   * @fn checkSIMStatus
   * @brief 检查SIM卡状态
   * @return bool类型 返回指令操作是否成功
   */
  bool checkSIMStatus(void);
  
  /**
   * @fn setNetMode
   * @brief 设置网络模式
   * @param net 网络模式 
   * @n       eGSM: GSM 模式
   * @n       eLTE:   LTE 模式
   * @return bool类型 返回指令操作是否成功
   */
  bool setNetMode(eNet net);
  
  /**
   * @fn setBaudRate
   * @brief 设置波特率
   * @param rate 波特率
   * @return bool类型 返回指令操作是否成功
   */  
  bool setBaudRate(long rate);
  
  /**
   * @fn httpConnect
   * @brief 连接http服务器
   * @param host 主机服务器IP
   * @return bool类型 返回指令操作是否成功
   */    
  bool httpConnect(const char *host);
  
  /**
   * @fn httpDisconnect
   * @brief 断开http连接
   * @return bool类型 返回指令操作是否成功
   */  
  bool httpDisconnect(void);
  
  /**
   * @fn httpPost
   * @brief HTTP POST
   * @param host 主机服务器IP
   * @param data POST数据
   * @return bool类型 返回指令操作是否成功
   */  
  bool httpPost(const char *host , const char *data);
  
  /**
   * @fn httpGet
   * @brief HTTP GET
   * @param host 主机服务器IP
   * @return bool类型 返回指令操作是否成功
   */  
  bool httpGet(const char *host);
  
  /**
   * @fn httpRead
   * @brief 读取HTTP缓存数据
   * @param buf 缓存变量
   * @param length 读取数据长度
   * @return bool类型 返回指令操作是否成功
   */ 
  bool httpRead(char* buf,long length);
  
  /**
   * @fn startGPS
   * @brief 启动GPS
   * @return bool类型 返回指令操作是否成功
   */   
  bool startGPS(void);
  
  /**
   * @fn stopGPS
   * @brief 停止GPS
   * @return bool类型 返回指令操作是否成功
   */ 
  bool stopGPS(void);
  
  /**
   * @fn getGPS
   * @brief 获取GPS信息
   * @return String类型 返回GPS信息
   */ 
  String getGPS(void);
  
  /**
   * @fn startTCPIP
   * @brief 启动TCPIP
   * @return bool类型 返回指令操作是否成功
   */ 
  bool startTCPIP(void);
  
  /**
   * @fn stopTCPIP
   * @brief 停止TCPIP
   * @return bool类型 返回指令操作是否成功
   */ 
  bool stopTCPIP(void);
  
  /**
   * @fn tcpipConnect
   * @brief 连接tcpip服务器
   * @param linkNum 连接标识 范围为0-9
   * @param type 传输协议的类型
   * @n     TCP传输控制协议
   * @n     UDP用户数据报协议  
   * @param port TCP服务器的端口
   * @param serverIP 服务器的IP地址
   * @return bool类型 返回指令操作是否成功
   */  
  bool tcpipConnect(int linkNum,const char *type,long port,const char *serverIP=NULL);
  
  /**
   * @fn sendTCPIP
   * @brief 发送数据到TCP服务器
   * @param linkNum 连接标识 范围为0-9
   * @param data 发送数据
   * @return bool类型 返回指令操作是否成功
   */  
  bool sendTCPIP(uint8_t linkNum,const char *data);
  
  /**
   * @fn retrieveTCPIP
   * @brief 检索TCP/UDP缓冲区数据
   * @param linkNum 标识连接，范围(0-9)
   * @param length 要读取的数据长度，默认值1500
   * @return None
   */  
  void retrieveTCPIP(const char *linkNum,long length = 1500);
  
  /**
   * @fn setPhoneFunctiona
   * @brief 设置手机功能模式
   * @param fun 手机模式
   * @n     0–最低功能
   * @n     1–全功能，在线模式
   * @n     4–禁用手机的发射和接收RF电路
   * @n     5–工厂测试模式
   * @n     6–重置
   * @n     7–离线模式
   * @return bool类型 返回指令操作是否成功
   */   
  bool setPhoneFunctiona(const char *fun);
  
  /**
   * @fn querySignal
   * @brief 查询信号
   * @return int类型 返回信号强度
   */   
  int querySignal(void);
  
  /**
   * @fn sendMessage
   * @brief 发送短信消息
   * @param data 发送数据
   * @param number 发送电话号码
   * @return bool类型 返回指令操作是否成功
   */ 
  bool sendMessage(const char *data,const char *number);
  
  /**
   * @fn readMessage
   * @brief 阅读短信消息
   * @param index 信息索引
   * @return char*类型 返回短信信息
   */  
  char* readMessage(uint8_t index);
  
  /**
   * @fn textToSpeechTTS
   * @brief 文字转语音
   * @param text 文字内容
   * @return bool类型 返回指令操作是否成功
   */ 
  bool textToSpeechTTS(const char *text);
  
  /**
   * @fn recordWavAudio
   * @brief 录制wav音频文件
   * @param fileName 文件地址
   * @return bool类型 返回指令操作是否成功
   */ 
  bool recordWavAudio(const char *fileName);
  
  /**
   * @fn stopRecording
   * @brief 停止录制wav音频文件
   * @return bool类型 返回指令操作是否成功
   */ 
  bool stopRecording(void);
  
   /**
   * @fn playAudio
   * @brief 播放音频文件
   * @param fileName 文件地址
   * @return bool类型 返回指令操作是否成功
   */ 
  bool playAudio(const char *fileName);
  
  /**
   * @fn audioPlayStop
   * @brief 停止播放
   * @return bool类型 返回指令操作是否成功
   */ 
  bool audioPlayStop(void);

  /**
   * @fn startSSL
   * @brief 启动SSL服务
   * @return bool类型 返回指令操作是否成功
   */ 
  bool startSSL(void);
  
  /**
   * @fn stopSSL
   * @brief 停止SSL服务
   * @return bool类型 返回指令操作是否成功
   */ 
  bool stopSSL(void);
  
  /**
   * @fn connectSSL
   * @brief 连接到SSL服务器
   * @param sessionId 要操作的会话索引(0-1)
   * @param host 服务器地址
   * @param port 端口
   * @return bool类型 返回指令操作是否成功
   */ 
  bool connectSSL(const char *sessionId,const char *host,const char *port);
  
  /**
   * @fn disconnectSSL
   * @brief 断开SSL服务器连接
   * @param sessionId 要操作的会话索引(0-1)
   * @return bool类型 返回指令操作是否成功
   */ 
  bool disconnectSSL(const char *sessionId);
  
  /**
   * @fn sendSSL
   * @brief 发送数据到SSL服务器
   * @param sessionId 要操作的会话索引(0-1)
   * @param length 要发送的数据长度
   * @param data 发送的数据
   * @return bool类型 返回指令操作是否成功
   */ 
  bool sendSSL(const char *sessionId,int length,const char *data);
  
  /**
   * @fn readSSL
   * @brief 读取SSL服务器缓存数据
   * @param sessionId 要操作的会话索引(0-1)
   * @return None
   */ 
  void readSSL(const char *sessionId);
  
  /**
   * @fn startFTPS
   * @brief 启动FTPS服务
   * @return bool类型 返回指令操作是否成功
   */ 
  bool startFTPS(void);
  
  /**
   * @fn stopFTPS
   * @brief 停止FTPS服务
   * @return bool类型 返回指令操作是否成功
   */   
  bool stopFTPS(void);
  
  /**
   * @fn loginToFTPS
   * @brief 登录到FTP（S）服务器
   * @param host 服务器地址
   * @param port 端口
   * @param username 用户名
   * @param password 密码
   * @param serverType 服务器类型
   * @n     0–FTP服务器
   * @n     1–具有AUTH SSL的显式FTPS服务器
   * @n     2–具有AUTH TLS的显式FTPS服务器
   * @n     3–隐式FTPS服务
   * @return bool类型 返回指令操作是否成功
   */ 
  bool loginToFTPS(const char *host,const char *port,const char *username,const char *password,uint8_t serverType);
  
  /**
   * @fn logoutFTPS
   * @brief 注销FTP（S）服务器
   * @return bool类型 返回指令操作是否成功
   */
  bool logoutFTPS(void);
  
  /**
   * @fn getFTPSDirectory
   * @brief 获取FTP（S）服务器上的当前目录
   * @return char*类型 返回服务器上的当前目录
   */
  char* getFTPSDirectory(void); 
  
  /**
   * @fn setHTPInfo
   * @brief 设置HTP服务器信息
   * @param cmd 操作HTP服务器列表
   * @n     "ADD"：将HTP服务器项添加到列表中
   * @n     "DEL"：从列表中删除HTP服务器项(为“DEL”，host字段是要从列表中删除的HTP服务器项目)
   * @param host 服务器地址
   * @param port 端口
   * @param httpVersion HTTP版本的HTP服务
   * @n     0 – HTTP 1.0
   * @n     1 – HTTP 1.1 
   * @return bool类型 返回指令操作是否成功
   */ 
  bool setHTPInfo(const char *cmd,const char *host,const char *port=NULL,const char *httpVersion=NULL);
  
  /**
   * @fn updatingDateTime
   * @brief 使用HTP协议更新日期时间
   * @return bool类型 返回指令操作是否成功
   */
  bool updatingDateTime(void);
  
  /**
   * @fn updateSystemTime
   * @brief 更新系统时间
   * @param host NTP服务器地址
   * @param timezone 本地时区(-96 to 96)
   * @return bool类型 返回指令操作是否成功
   */ 
  bool updateSystemTime(const char *host,const char *timezone);
  
  /**
   * @fn netRegistrationStatus
   * @brief GPRS网络注册状态
   * @return String类型 返回网络注册状态
   */
  String netRegistrationStatus(void);
  
  /**
   * @fn GPSFormulaConversion
   * @brief GPS经纬度公式转换
   * @param lat 纬度
   * @param log 经度
   * @return String类型 返回转换完成的经纬度
   */ 
  String GPSFormulaConversion(const char* lat,const char* log);
  
  /**
   * @fn GPSDataProcessing
   * @brief GPS数据转换处理
   * @return String类型 返回处理完成的经纬度
   */ 
  String GPSDataProcessing(const char* data);

```

## 兼容性

主板               | 通过          | 未通过      | 未测试   | 备注
------------------ | :----------: | :----------:| :---------: | -----
Arduino Uno        |      √       |             |            | 
Leonardo           |      √       |             |            | 
Meag2560           |         √    |             |            | 

## 历史

- 2023/1/30 - 1.0.0 版本

## 创作者

- Written by  Baikunlin( kunlin.bai@dfrobot.com), 2023. (Welcome to our [website](https://www.dfrobot.com/))