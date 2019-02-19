#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
SoftwareSerial NodeSerial(D2, D3); // RX | TX
// Code By ArduinoALL
#include <PubSubClient.h>
const char* ssid = "Kuyraisas"; // แก้ ssid
const char* password = "0012345678"; // แก้ password
// Config MQTT Server
const char * topic = "/server"; // topic ชื่อ /server
#define mqtt_server "m15.cloudmqtt.com" // server
#define mqtt_port 14203   // เลข port
#define mqtt_user "rrfbpaqw" // user
#define mqtt_password "jzW3F6vT2E4k" // password
#define LED_PIN0 D0
#define LED_PIN1 D1
#define LED_PIN2 D2
#define LED_PIN3 D3
#define LED_PIN4 D4
char *Power_status = "OFF";
char *checkon_status = "Offline";
char *Clean_butt = "Not work";
char *Status_check = "Offline";
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // เชื่อมต่อ network
  pinMode(D2, INPUT);
  pinMode(D3, OUTPUT);
  NodeSerial.begin(4800);
  pinMode(LED_PIN0, OUTPUT);
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // จบการเชื่อมต่อ network

  client.setServer(mqtt_server, mqtt_port); // เชื่อมต่อ mqtt server
  client.setCallback(callback); // สร้างฟังก์ชันเมื่อมีการติดต่อจาก mqtt มา
}

void loop() {
  if (!client.connected()) {
    Serial.print("MQTT connecting...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) { // ถ้าเชื่อมต่อ mqtt สำเร็จ
      client.subscribe(topic); // ชื่อ topic ที่ต้องการติดตาม
      Serial.println("connected");
    }
    // ในกรณีเชื่อมต่อ mqtt ไม่สำเร็จ
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000); // หน่วงเวลา 5 วินาที แล้วลองใหม่
      return;
    }
  }
  client.loop();
}
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message from ");
  Serial.println(topic);
  String msg = "";
  int i = 0;
  while (i < length) {
    msg += (char)payload[i++]; // อ่านข้อความจาก topic ที่ส่งมา
  }
  Serial.print("receive ");
  Serial.println(msg); // แสดงข้อความที่ได้รับจาก topic
  //power on off msg
  if (msg == "power on") { // ถ้า topic ส่งคำว่า on
    digitalWrite(LED_PIN0, 1);
    Power_status = "icatbox : Power On";
    client.publish("/icatbox", Power_status); // ส่งข้อความกลับไปที่ topic คือ ชื่ออุปกรณ์ที่ส่ง , ข้อความ
    NodeSerial.print("110");
    NodeSerial.print("\n");

  } else if (msg == "power off") {
    digitalWrite(LED_PIN0, 0);
    Power_status = "icatbox : Power Off";
    NodeSerial.print("1100");
    NodeSerial.print("\n");
    client.publish("/icatbox", Power_status);
  } else if (msg == "status") {
    client.publish("/icatbox", Power_status);
  }
  //clean button
  if (msg == "clean") { // ถ้า topic ส่งคำว่า clean
    digitalWrite(LED_PIN0, 1);
    Clean_butt = "icatbox : Cleaned";
    client.publish("/icatbox", Clean_butt); // ส่งข้อความกลับไปที่ topic คือ ชื่ออุปกรณ์ที่ส่ง , ข้อความ
    NodeSerial.print("120");
    NodeSerial.print("\n");

  } else if (msg == "Not Clean") {
    digitalWrite(LED_PIN0, 0);
    Clean_butt = "icatbox : Not Clean";
    NodeSerial.print("1200");
    NodeSerial.print("\n");
    client.publish("/icatbox", Clean_butt);
  } else if (msg == "status") {
    client.publish("/icatbox", Clean_butt);
  }
}
