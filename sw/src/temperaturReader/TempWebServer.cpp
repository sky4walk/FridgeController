// brausteuerung@AndreBetz.de
#include "ESP8266WiFi.h"
#include "ESPAsyncTCP.h"
#include "TempWebServer.h"

const char* PARAM_ON_INPUT  = "OnInput";
const char* PARAM_OFF_INPUT = "OnInput";
const char* PARAM_PW_INPUT  = "PwInput";

const char temperatur_html[] PROGMEM = R"rawliteral(
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
    <h3> <a href="http://www.Zwieselbrau.de/">Zwieselbrau.de</a></h3>
    <p id="time"></p>
    <p>
      <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
      <span class="dht-labels">Temperature</span> 
      <span id="temperature">%TEMPERATURE%</span>
      <sup class="units">&deg;C</sup>
    </p>
    <p>
      <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
      <span class="dht-labels">Strom</span> 
      <span id="anaus">%ANAUS%</span>
      <sup class="units">&deg;C</sup>
    </p>
    <button onclick="window.location.href='/setUp'">Setup</button>
    
    <script>
      var myVar = setInterval(myTimer, 1000);

      function myTimer() {
        var d = new Date();
        var t = d.toLocaleTimeString();
        document.getElementById("time").innerHTML = t;
        getData();
      }

      function getData() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("temperature").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "readTemp", true);
        xhttp.send();
      }
      
    </script>  
  </body></html>
)rawliteral";


const char setup_html[] PROGMEM = R"rawliteral(
  <!DOCTYPE HTML><html>
  <head></head>
    <h2>Controller Setup</h2>
    <h3> <a href="http://www.Zwieselbrau.de/">Zwieselbrau.de</a></h3>
    <form action="/setUpGet">
      <label for="minTemp">On :</label>
      actual Value : %ONVAL% : <input type="text" name="OnInput"><br>
      <label for="maxTemp">Off :</label>
      actual Value : %OFFVAL%: <input type="text" name="OffInput"><br>
      <label for="pwValue">Password :</label>
      <input type="text" name="PwInput"><br>
      <input type="submit" value="Save">      
  </form>
  
  <script>
  /*
    function myFunction() {
      window.location.href="/";
    }
    */
  </script>
   
  </body></html>
)rawliteral";

// processor ersetzt werte im Dokument
String processorTemp(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURE"){
    return String(TempWebServer::mSettings->getActTemp());
  }
  if(var == "ANAUS"){
    if ( TempWebServer::mSettings->getOnOff() ) {
      return String("On");
    } else {
      return String("Off");      
    }
  }  
  return String();
}

String processorSetup(const String& var){
  //Serial.println(var);
  if(var == "OFFVAL"){
    return String(TempWebServer::mSettings->getOffT());
  } 
  else if(var == "ONVAL"){
    return String(TempWebServer::mSettings->getOnT());
  } 
  return String();
}

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void rootLevel(AsyncWebServerRequest *request) {
  request->send_P(200, "text/html", temperatur_html, processorTemp);
}

void setLevel(AsyncWebServerRequest *request) {
  request->send_P(200, "text/html", setup_html, processorSetup);
}

void readTemp(AsyncWebServerRequest *request) {
  request->send_P(200, "text/html", String(TempWebServer::mSettings->getActTemp()).c_str());
}

void setLevelGet(AsyncWebServerRequest *request) {
  String inputMessage;
  if (request->hasParam(PARAM_ON_INPUT)) {
      inputMessage = request->getParam(PARAM_ON_INPUT)->value();
  }
  if (request->hasParam(PARAM_OFF_INPUT)) {
      inputMessage = request->getParam(PARAM_OFF_INPUT)->value();
  }
  if (request->hasParam(PARAM_PW_INPUT)) {
      inputMessage = request->getParam(PARAM_PW_INPUT)->value();
  }
  request->send(200, "text/text", inputMessage);
}

Settings* TempWebServer::mSettings;

TempWebServer::TempWebServer(
       AsyncWebServer& server,
       Settings* set) :
        mServer(server) {
          TempWebServer::mSettings = set;
}

void TempWebServer::begin(){
      mServer.on("/", HTTP_GET, rootLevel);
      mServer.on("/readTemp", HTTP_GET, readTemp);
      mServer.on("/setUp", HTTP_GET, setLevel);
      mServer.on("/setUpGet", HTTP_GET, setLevelGet);
      mServer.onNotFound( notFound );
      mServer.begin();
}        
