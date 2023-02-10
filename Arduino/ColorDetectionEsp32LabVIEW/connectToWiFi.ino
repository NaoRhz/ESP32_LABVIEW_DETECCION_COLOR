void connectToWiFi(const char* ssid, const char* pwd) {
  Serial.println("Connecting to WiFi network: " + String(ssid));
  WiFi.disconnect(true);
  WiFi.onEvent(WiFiEvent);
  WiFi.begin(ssid, pwd);
  Serial.println("Waiting for WIFI connection...");
}
