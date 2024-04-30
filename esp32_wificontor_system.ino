#include "esp_camera.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#include "index.h"
#include "camera.h"
#include "robot_direction.h"
#include "WIFI_ID.h"

#include "global_defs.h"

#define MONITOR_BAUDRATE 115200

AsyncWebServer server(80);

void setup(void) {
  Serial.begin(MONITOR_BAUDRATE);

  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html);
  });

  server.onNotFound([](AsyncWebServerRequest *request){
    request->send_P(404, "text/plain", "File Not Found");
  });

  wsCamera.onEvent(onCameraWebSocketEvent);
  server.addHandler(&wsCamera);

  wsCarInput.onEvent(onCarInputWebSocketEvent);
  server.addHandler(&wsCarInput);

  server.begin();
  Serial.println("HTTP server started");
  setupCamera();
}


void loop() {
  wsCamera.cleanupClients();
  wsCarInput.cleanupClients();

  sendCameraPicture();
  Serial.printf("SPIRam Total heap %d, SPIRam Free Heap %d\n", ESP.getPsramSize(), ESP.getFreePsram());
}
