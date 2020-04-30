/*************************************************************
 * File: Arquivo de processamento
 * Autor: Alexandre Marques
 * Data: 17/09/2019
 * Última Modificação: 22/11/2019
 * Versão: 2.0
 *************************************************************/

#include "configuration_mode.h"

struct ConfigurationEntity
{
    char ssid[64];
    char password[64];
    char api[64];
}networkConfig;

const int PORT = 80;

ESP8266WebServer _server(PORT);

WiFiClient _client;

const int _LED_RED = 0;
const int _LED_GREEN = 2;
const int _DHTPin = 5;
const int _BUZZER = 13;
const int _IR = 14;

DHT dht(_DHTPin, DHTTYPE);

IRsend irsend(_IR);

const int _SIZE = 100;

const int mhz = 38;

uint16_t rawDataOff[_SIZE] = {4550,4150, 750,1350, 750,350, 700,1400, 750,1400, 700,350, 700,400, 700,1400, 700,400, 700,350, 700,1450, 700,350, 700,400, 650,1450, 700,1450, 650,400, 700,1450, 650,450, 650,1450, 650,1500, 650,1450, 700,1450, 650,450, 600,1500, 650,1500, 650,1450, 700,400, 650,450, 600,450, 600,500, 600,1450, 650,500, 600,450, 600,1500, 650,1450, 650,1500, 650,450, 600,500, 600,450, 600,500, 600,450, 600,450, 650,450, 600,450, 600,1500, 650,1500, 650,1450, 650,1500, 650,1450, 650,5050};

uint16_t rawDataOn[_SIZE] = {4550,4150, 750,1350, 750,350, 700,1450, 700,1400, 700,400, 650,400, 700,1450, 650,400, 700,350, 700,1450, 700,350, 700,400, 700,1400, 700,1450, 700,400, 650,1450, 700,400, 650,400, 650,1500, 650,1450, 700,1450, 650,1500, 650,1450, 700,1450, 650,1500, 650,1450, 650,450, 650,400, 650,450, 650,400, 650,450, 600,450, 650,450, 600,450, 600,450, 650,1450, 650,500, 600,450, 600,450, 600,500, 600,1500, 600,1500, 650,1500, 650,450, 600,1500, 650,1500, 600,1500, 650,1500, 650,5000};

float lux = 0.00, ADC_value = 0.0048828125, LDR_value;

bool _validateAir = true;

/*
 * 
 * registerConfiguration
 * 
*/
void registerConfiguration()
{
    for (unsigned int p = 0; p < sizeof(networkConfig); p++)
    {
        EEPROM.write(START + p, *((char*)&networkConfig + p));
    }

    EEPROM.write(VERSION + 0, CONFIG[0]);
    EEPROM.write(VERSION + 1, CONFIG[1]);
    EEPROM.commit();
}

/*
 * 
 * loadConfRun
 * 
*/
 void loadConfRun()
 {
    if (EEPROM.read(VERSION + 0) == CONFIG[0] && EEPROM.read(VERSION + 1) == CONFIG[1])
    {
        for (unsigned int i = 0; i < sizeof(networkConfig); i++)
        {
            *((char*)&networkConfig + i) = EEPROM.read(START + i);
        }
    }
 }

/*
 * 
 * htmlRender
 * 
*/
void htmlRender()
{
    String _html =  "<html>";
           _html += "   <head>";
           _html += "       <meta charset=\"UTF-8\">";
           _html += "       <title>Console WeatherOS</title>";
           _html += "   </head>";
           _html += "   <body style=\"background-color: #f5f5f5; margin:0px; padding:0px;\">";
           _html += "       <div style=\"background-color: #4377c4; height: 96px;\">";
           _html += "           <h3 style=\"font-size: 20pt; color: white; font-family: arial, sans-serif; font-weight: bold; padding: 27px 50px 0px 30px;\">";
           _html += "               Console Gateway Weather Rev 1.0";
           _html += "           </h3>";
           _html += "       </div>";
           _html += "       <p style=\"text-align: center; font-size: 14pt; font-weight: bold; font-family: arial, sans-serif;\">";
           _html += "           <a href=\"/configuration\">Iniciar Configuração do Gateway</a>";
           _html += "       </p>";
           _html += "   </body>";
           _html += "</html>";

    _server.send(200, "text/html", _html);
}

/*
 * 
 * menuWiFiConfiguration
 * 
*/
void menuWiFiConfiguration()
{
    String _html =  "<html>";
           _html += "   <head>";
           _html += "       <meta charset=\"UTF-8\">";
           _html += "       <title>Console WeatherOS</title>";
           _html += "   </head>";
           _html += "   <body style=\"background-color: #f5f5f5; margin:0px; padding:0px;\">";
           _html += "       <div style=\"background-color: #4377c4; height: 96px;\">";
           _html += "           <h3 style=\"font-size: 20pt; color: white; font-family: arial, sans-serif; font-weight: bold; padding: 27px 50px 0px 30px;\">";
           _html += "               Configuração do Gateway";
           _html += "           </h3>";
           _html += "       </div>";
           _html += "           <p style=\"text-align: center; font-size: 14pt; color: #4377c4; font-family: arial, sans-serif; font-weight: bold;\">Console de Configuração do Gateway</p>";
           _html += "       <div style=\"margin: 0 auto; display: table;\">";
           _html += "           <form method=POST>";
           _html += "               <p style=\"font-family: arial, sans-serif;\">SSID: <input style=\"margin-left: 29px;\" required name=_ssid type=text value=\"";
           _html +=                     networkConfig.ssid;
           _html +=                 "\" /></p>";
           _html +=                 "<p style=\"font-family: arial, sans-serif;\">Senha: <input style=\"margin-left: 20px;\" required name=_pass type=password value=\"";
           _html +=                     networkConfig.password;
           _html +=                 "\" /></p>";
           _html +=                 "<p style=\"font-family: arial, sans-serif;\">API: <input style=\"margin-left: 41px;\" required name=_api type=text value=\"";
           _html +=                     networkConfig.api;
           _html +=                 "\" /></p>";
           _html +=                 "<p style=\"text-align: center; font-family: arial, sans-serif;\"><input name=btnSave type=submit value=Salvar /></p></form>";
           _html += "       </div>";
           _html += "   </body>";
           _html += "</html>";
    
    _server.send(200, "text/html", _html);
}

/*
 * 
 * confirmWiFiConfiguration
 * 
*/
void confirmWiFiConfiguration()
{
    String _html =  "<html>";
           _html += "   <head>";
           _html += "       <meta charset=\"UTF-8\">";
           _html += "       <title>Console WeatherOS</title>";
           _html += "   </head>";
           _html += "   <body style=\"background-color: #f5f5f5; margin:0px; padding:0px;\">";
           _html += "       <div style=\"background-color: #4377c4; height: 96px;\">";
           _html += "           <h3 style=\"font-size: 20pt; color: white; font-family: arial, sans-serif; font-weight: bold; padding: 27px 50px 35px 30px;\">";
           _html += "               Configuração do Gateway Salva com Sucesso!";
           _html += "           </h3>";
           _html += "           <p style=\"text-align: center; font-size: 14pt; color: #4377c4; font-family: arial, sans-serif; font-weight: bold;\">Configuração armazenada com sucesso!</p>";

    String thisSsid = _server.arg("_ssid");
    String thisPass = _server.arg("_pass");
    String thisServer = _server.arg("_api");

    thisSsid.toCharArray(networkConfig.ssid, 64);
    thisPass.toCharArray(networkConfig.password, 64);
    thisServer.toCharArray(networkConfig.api, 64);

    _html += "           <p style=\"font-family: arial, sans-serif; text-align: center;\">SSID: <b>";
    _html +=                 networkConfig.ssid;
    _html += "           </b></p>";
    _html += "           <p style=\"font-family: arial, sans-serif; text-align: center;\">Senha: <b>";
    _html +=                 networkConfig.password;
    _html += "           </b></p>";
    _html += "           <p style=\"font-family: arial, sans-serif; text-align: center;\">API: <b>";
    _html +=                 networkConfig.api;
    _html += "           </b></p>";
    _html += "           <form method=GET>";
    _html += "           <p style=\"text-align: center; font-family: arial, sans-serif;\"><input name=btnRegister type=submit value=Voltar /></p></form>";
    _html += "       </div>";
    _html += "   </body>";
    _html += "</html>";

    _server.send(200, "text/html", _html);

    registerConfiguration();

    ESP.restart();
}

/*
 * 
 * startAlertLight
 * 
*/
void startAlertLight(bool onBuzzer)
{
    LDR_value = analogRead(A0);

    lux = (250.000000/(ADC_value*LDR_value)) - 50.000000;

    if (onBuzzer)
    {
        pinMode(_BUZZER, OUTPUT);

        delay(1000);

        digitalWrite(_BUZZER, HIGH);

        delay(1000);

        digitalWrite(_BUZZER, LOW);
    }

    else
    {
        digitalWrite(_BUZZER, LOW);
    }
}

/*
 * 
 * initAir
 * 
 * @Param temperature float
 * 
*/
void initAir(bool start)
{
    delay(5000);

    if (start && _validateAir)
    {
        irsend.sendRaw(rawDataOn, _SIZE, mhz);

        _validateAir = false;
    }

    else if (!start && !_validateAir)
    {
        irsend.sendRaw(rawDataOff, _SIZE, mhz);

        _validateAir = true;
    }
}

/*
 * 
 * postValue
 * 
*/
void postValue()
{
    HTTPClient http;

    http.begin(networkConfig.api);

    http.addHeader("Content-Type", "application/json");

    String temp = String(dht.readTemperature());
    String humidity = String(dht.readHumidity());
    String luminosity = String(lux);

    String _data = "{ \"temperature\": " + temp + ", \"moisture\": " + humidity + ", \"luminosity\": " + luminosity + "}";

    http.POST(_data);

    String payload = http.getString();

    Serial.println(payload);

    const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;

    DynamicJsonBuffer buffer(bufferSize);

    JsonObject& object = buffer.parse(payload);

    const char* validateAir = object["startAir"];
    const char* validateLux = object["startBuzzer"];

    bool _air = String(validateAir) == "true";
    bool _lux = String(validateLux) == "true";

    startAlertLight(_lux);

    initAir(_air);

    http.end();

    delay(1000);
}

/*
 * 
 * runConfig
 * 
*/
void runConfig()
{
    Serial.begin(115200);

    Serial.println("Modo de Configuração Iniciado!");

    EEPROM.begin(512);

    pinMode(_LED_RED, OUTPUT);

    digitalWrite(_LED_GREEN, LOW);
    digitalWrite(_LED_RED, HIGH);

    IPAddress address(192, 168, 4, 2);
    IPAddress subnet(255, 255, 255, 0);
    IPAddress gateway(192, 168, 4, 1);

    WiFi.mode(WIFI_AP);

    WiFi.softAP("Gateway-Weather", "admin1234");
    WiFi.config(address, gateway, subnet);

    _server.on("/", htmlRender);
    _server.on("/configuration", HTTP_GET, menuWiFiConfiguration);
    _server.on("/configuration", HTTP_POST, confirmWiFiConfiguration);
    _server.begin();

    Serial.println("server started...");
    Serial.println(WiFi.softAPIP());
}

/*
 * 
 * modeRuntime
 * 
*/
void modeRuntime()
{
    Serial.begin(115200);

    irsend.begin();

    EEPROM.begin(512);

    Serial.println("Em execução!");

    pinMode(_LED_GREEN, OUTPUT);

    digitalWrite(_LED_GREEN, HIGH);
    digitalWrite(_LED_RED, LOW);

    loadConfRun();

    pinMode(A0,INPUT);
    pinMode(_DHTPin, INPUT);

    dht.begin();

    delay(500);

    WiFi.mode(WIFI_STA);

    WiFi.begin(networkConfig.ssid, networkConfig.password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    _server.begin();

    Serial.println("");

    Serial.println("WiFi Conectado!");
}

/*
 * 
 * taskConfig
 * 
*/
void taskConfig()
{
    _server.handleClient();
}

/*
 * 
 * taskRuntime
 * 
*/
void taskRuntime()
{
    postValue();
}