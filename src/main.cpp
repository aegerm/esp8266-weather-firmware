/*************************************************************
 * File: Arquivo Principal
 * Autor: Alexandre Marques
 * Data: 17/09/2019
 * Versão: 2.0
 *************************************************************/

#include <Arduino.h>
#include "configuration_mode.h"

const int button = 4;
bool validate = false;

/*
 * 
 * setup
 * 
*/
void setup()
{
  Serial.begin(115200);

  pinMode(button, INPUT_PULLUP);

  int read = digitalRead(button);

  if (read == 0)
  {
    runConfig();

    validate = true;
  }

  else
  {
    modeRuntime();
    
    validate = false;
  }
}

/*
 * 
 * loop
 * 
*/
void loop() 
{
  if (validate)
  {
    taskConfig();
  }

  else
  {
    taskRuntime();
  }
}