#include <SoftwareSerial.h>
 
SoftwareSerial mySerial(8, 9); // RX, TX  通过软串口连接esp8266


void setup() {
  // Open serial communications and wait for port to open:
  //最好设置成波特率一样，这样虽然串口工具看到也会乱码，但是波特率不一样好很多。
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  //最好设置成波特率一样，这样虽然串口工具看到也会乱码，但是波特率不一样好很多。
  mySerial.begin(115200);
   
  // 初始化重启一次esp8266
  //  mySerial.println("AT+RST");
  //  Serial.println("AT+RST");
  //  delay(5000);
  //  echo();
  //经串口调试工具测试，不退出穿透模式，AT命令不起作用，好像默认进入了，只是好像，不确定。
    mySerial.print("+++");
    delay(3000);

 //设置为WiFi应用模式3.AP+Station模式
    mySerial.println("AT+CWMODE=3");
    Serial.println("AT+CWMODE=3\r\n"); 
    delay(3000);
    echo();
  //0为单连模式，1为多连模式
    mySerial.println("AT+CIPMUX=0");
    Serial.println("AT+CIPMUX=0"); 
    delay(3000);
    echo();
  //列出WiFi列表，建议关闭，因为性能问题经常会卡死
  //  mySerial.println("AT+CWLAP"); 
  //  Serial.println("AT+CWLAP"); 
  //  delay(2000);
  //  echo();
    mySerial.println("AT+CWJAP=\"chioor\",\"12345678\""); 
    Serial.println("AT+CWJAP=\"chioor\",\"12345678\""); 
    delay(3000);
    echo();
  //此处可以写网址，但是强烈建议写ip地址，因为大几率因为DNS问题，连接不上数据发不出去，我在这里卡了一个星期才搞明白，强烈建议写ip，官方给的也是写ip
    mySerial.println("AT+CIPSTART=\"TCP\",\"183.230.40.33\",80"); 
    Serial.println("AT+CIPSTART=\"TCP\",\"api.heclouds.com\",80"); 
    delay(3000);
    echo();
//设置TCPIP应用模式：0.非透明传输模式，缺省模式、1.透明传输模式
    mySerial.println("AT+CIPMODE=1");
    Serial.println("AT+CIPMODE=1");
    delay(3000);
    echo();
  
 
 
}
 
void loop() {
 if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
  mySerial.println("AT+CIPSEND");
  Serial.println("AT+CIPSEND");
  delay(3000);
  echo();
  post();
  post();
  mySerial.println("+++");
  Serial.println("+++");
  delay(3000);
  echo();
 }
 
void echo(){
  delay(50);
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}


void post(){
   mySerial.println("POST /devices/523122392/datapoints   HTTP/1.1");
   mySerial.println("Host: api.heclouds.com");
   mySerial.println("api-key: PZN7Bc9pviqfH=nR4=");
   mySerial.println("Content-Length: 166");
   mySerial.println("");
   mySerial.println("{\"datastreams\":[{\"id\":\"tmp\",\"datapoints\":[{\"value\": \"66\"}]}]}");
   delay(3000);
    echo();
}
