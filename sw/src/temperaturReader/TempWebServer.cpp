// brausteuerung@AndreBetz.de
#include "ESP8266WiFi.h"
#include "ESPAsyncTCP.h"
#include "TempWebServer.h"
#include "DbgConsole.h"

const char* PARAM_ON_INPUT  = "OnInput";
const char* PARAM_OFF_INPUT = "OffInput";
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
    </p>
    <button onclick="window.location.href='/setUp'">Setup</button>
    
    <script>
      var myVar = setInterval(myTimer, 1000);

      function myTimer() {
        var d = new Date();
        var t = d.toLocaleTimeString();
        document.getElementById("time").innerHTML = t;
        getData();
        getState();
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
      function getState() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("anaus").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "readState", true);
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
      On <input type="number" step="0.1" name="OnInput" value="%ONINPUT%" required> °C<br>
      Off <input type="number" step="0.1" name="OffInput" value="%OFFINPUT%" required> °C<br>
      <input type="submit" value="Submit">
      <button onclick="window.location.href='/'">Back</button>
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
  if(var == "OFFINPUT"){
    return String(TempWebServer::mSettings->getOffT());
  } 
  else if(var == "ONINPUT"){
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
void readState(AsyncWebServerRequest *request) {
  if ( TempWebServer::mSettings->getOnOff() ) {
    request->send_P(200, "text/html", String("On").c_str() );
  } else {
    request->send_P(200, "text/html", String("Off").c_str() );    
  }
}

void setLevelGet(AsyncWebServerRequest *request) {
  String inputMessage;
  if (request->hasParam(PARAM_ON_INPUT)) {
      inputMessage = request->getParam(PARAM_ON_INPUT)->value();
      CONSOLELN(inputMessage);
      TempWebServer::mSettings->setOnT(inputMessage.toFloat());
      TempWebServer::mSettings->setShouldSave(true);
  }
  if (request->hasParam(PARAM_OFF_INPUT)) {
      inputMessage = request->getParam(PARAM_OFF_INPUT)->value();
      CONSOLELN(inputMessage);     
      TempWebServer::mSettings->setOffT(inputMessage.toFloat());
      TempWebServer::mSettings->setShouldSave(true);
  }
  if (request->hasParam(PARAM_PW_INPUT)) {
      inputMessage = request->getParam(PARAM_PW_INPUT)->value();
  }
  request->send(200, "text/html", "<a href=\"/\">Return to Home Page</a>");
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
      mServer.on("/readState", HTTP_GET, readState);
      mServer.on("/setUp", HTTP_GET, setLevel);
      mServer.on("/setUpGet", HTTP_GET, setLevelGet);
      mServer.onNotFound( notFound );
      mServer.begin();
}        
