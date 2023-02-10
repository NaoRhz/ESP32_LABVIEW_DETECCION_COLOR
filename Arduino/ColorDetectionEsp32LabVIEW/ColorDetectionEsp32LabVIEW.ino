#include <WiFi.h>
#include <WiFiUdp.h>
#include "esp_camera.h"
#define LED   4

camera_fb_t* fb = NULL;
#define CHUNK_LENGTH 1460

const char* ssid = "MiFibra-D900";  //"Xperia L1_9394";  //
const char* password = "#Mf2J.19.92#@"; //"b7a210884e08";//  //

const char* udpAddress = "192.168.1.58";   //"192.168.43.130";  
const int udpPort = 8888;


void connectToWiFi(const char* ssid, const char* pwd);
void camaraEvent();
void sendPacketData(const char* buf, uint16_t len, uint16_t chunkLength);
uint32_t encode(const uint8_t* buffer,uint32_t size,uint8_t* encodedBuffer);

boolean connected = false;
WiFiUDP udp;

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

  connectToWiFi(ssid, password);
  camaraEvent();
}

uint8_t encodedBuffer[20000];

void loop() {
  if (connected) {
    esp_err_t res = ESP_OK;
    fb = esp_camera_fb_get();
    
    if (!fb) {
      Serial.println("Camera capture failed");
      esp_camera_fb_return(fb);
      return;
    }

    if (fb->format != PIXFORMAT_JPEG) {
      Serial.println("PIXFORMAT_JPEG not implemented");
      esp_camera_fb_return(fb);
      return;
    }


    uint16_t encode_len= encode(fb->buf, fb->len, encodedBuffer);
    sendPacketData((const char*)encodedBuffer, encode_len, CHUNK_LENGTH);
    esp_camera_fb_return(fb);
  }
  
  char order;
  udp.parsePacket();  
  udp.read(&order, sizeof(order));
  int ord= String(order).toInt();
  digitalWrite(LED, ord);
  delay(10);

}
