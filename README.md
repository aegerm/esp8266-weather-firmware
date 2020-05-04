# Weather Firmware
Este projeto foi desenvolvido utilizando C++ com o framework PlatformIO.

## Objetivo do firmware
Esse firmware tem como função ser embarcado em um dispositivo ESP8266 e realizar leituras dos sequintes sensores:
- Sensor de Luminosidade LDR (Light Dependent Resistor)
- Sensor de Temperatura\Umidade DHT22

Além de realizar a leitura dos sensores mencionados acima, o mesmo efetua o acionamento de atuadores, como:
- LED Infravermelho para acionar condicionador de AR conforme a regra obtida de um webservice
- Speaker para informar que a luz está acesa

## Modos de operação do sistema
Modo Configuração:
Ao ligar o dispositivo com o sistema em execução, deve ser pressionado o botão de configuração, para entrar
no modo de configuração. Esse modo disponibiliza um webserver, onde o usuário poderá adicionar o dispositivo
em uma rede WiFi e apontar para a API que irá realizar a leitura dos dados originados dos sensores e salvar em
uma base de dados. Após informar esses dados, será salvo as configurações na EEPROM do dispositivo, reiniciando o 
mesmo e entrando no modo de execução.

Modo Execução:
Nesse modo o dispositivo será adicionado na rede WiFi e iniciará o processo de leitura dos sensores e envio de tempos em tempos
desses dados para um webservice que tem como função salvar essas informações em uma base de dados. O dispositivo aceita receber "regras"
para acionar os seus atuadores, de um sistema web, a leitura é realizada por meio de um JSON.

## Objetivo do projeto
- Monitorar e controlar ambientes
- Automatizar e emitir alertas para usuários por meio do envio de alarmes
- Possibilidade de geração de relatórios
