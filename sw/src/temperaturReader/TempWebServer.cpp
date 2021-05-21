// brausteuerung@AndreBetz.de
#include "ESP8266WiFi.h"
#include "ESPAsyncTCP.h"
#include "TempWebServer.h"

const char index_html[] PROGMEM = R"rawliteral(
  <!DOCTYPE HTML><html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
    <style>
      html {
       font-family: Arial;
       display: inline-block;
       margin: 0px auto;
       text-align: center;
      }
      h2 { font-size: 3.0rem; }
      p { font-size: 3.0rem; }
      .units { font-size: 1.2rem; }
      .dht-labels{
        font-size: 1.5rem;
        vertical-align:middle;
        padding-bottom: 15px;
      }
    </style>
  </head>
  <body>
    <h2>Temperatur Controller</h2>
    <h3>Zwieselbrau.de</h3>
    <p>
      <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
      <span class="dht-labels">Temperature</span> 
      <span id="temperature">%TEMPERATURE%</span>
      <sup class="units">&deg;C</sup>
    </p>  
  </body>
  <script>
  setInterval(function ( ) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("temperature").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/temperature", true);
    xhttp.send();
  }, 10000 ) ;
  </script>
  </html>
)rawliteral";

String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURE"){
    return String(TempWebServer::mSettings->getActTemp());
  } 
  return String();
}

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void rootLevel(AsyncWebServerRequest *request) {
  request->send_P(200, "text/html", index_html, processor);
}

void temperaturLevel(AsyncWebServerRequest *request) {
  request->send_P(200, "text/html", String(TempWebServer::mSettings->getActTemp()).c_str());
}

Settings* TempWebServer::mSettings;

TempWebServer::TempWebServer(
       AsyncWebServer& server,
       Settings* set) :
        mServer(server)
        {
          TempWebServer::mSettings = set;
}


void TempWebServer::begin(){
      mServer.on("/", HTTP_GET, rootLevel);
      mServer.on("/temperature", HTTP_GET, temperaturLevel);
      mServer.onNotFound( notFound );
      mServer.begin();
}        
