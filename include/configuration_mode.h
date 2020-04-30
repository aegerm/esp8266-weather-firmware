/*************************************************************
 * File: Arquivo de implementação (Biblioteca)
 * Autor: Alexandre Marques
 * Data: 17/09/2019
 * Última Modificação: 22/11/2019
 * Versão: 2.0
 *************************************************************/

#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <IRsend.h>
#include "DHT.h"

#define DHTTYPE DHT22
#define VERSION 500
#define START 6
#define CONFIG "1a"

/*
 *
 * registerConfiguration
 * 
*/
void registerConfiguration();

/*
 * 
 * htmlRender
 * 
*/
void htmlRender();

/*
 * 
 * menuWiFiConfiguration
 * 
*/
void menuWiFiConfiguration();

/*
 * 
 * confirmWiFiConfiguration
 * 
*/
void confirmWiFiConfiguration();

/*
 * 
 * startAlertLight
 * 
 * @Param onBuzzer
 * 
*/
void startAlertLight(bool onBuzzer);

/*
 * 
 * initAir
 * 
 * @Param start
 * 
*/
void initAir(bool start);

/*
 * 
 * postValue
 * 
*/
void postValue();

/*
 * 
 * runConfig
 * 
*/
void runConfig();

/*
 * 
 * modeRuntime
 * 
*/
void modeRuntime();

/*
 * 
 * taskConfig
 * 
*/
void taskConfig();

/*
 * 
 * taskRuntime
 * 
*/
void taskRuntime();

/*
 * 
 * loadConfRun
 * 
*/
void loadConfRun();