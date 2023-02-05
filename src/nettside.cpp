#include "nettside.h"
#include "Arduino.h"
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "main.h"

const char* ssid = "MinSykehusSeng";
const char* password =  "jegersyk";

AsyncWebServer server(80);

void nettside_init(){
    WiFi.softAP(ssid, password);
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());

    server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/plain", String(getPressure()).c_str());
    });

    server.begin();
}