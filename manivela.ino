#include <ESP8266WiFi.h> // biblioteca para usar as funções de Wifi do módulo ESP8266
#include <Wire.h>         // biblioteca de comunicação I2C
#include <MQTTClient.h>
#include <string.h>

#define pin_motor 0
 
// Para conexão
const char client_id[] = "limbo_microcontroller";      //arbitrary identification
const char client_key[] = "limbo_microcontroller";     //token KEY from shiftr.io
const char client_secret[] = "55c6d7bcbfecaee9";  

const char ssid[] = "maPaulino";     //name of the used Wi-Fi network
const char pass[] = "vitaminaAbacate";         //password of the Wi-Fi network

//Definições de alguns endereços mais comuns do MPU6050
const int MPU_ADDR =      0x68; // definição do endereço do sensor MPU6050 (0x68)
const int WHO_AM_I =      0x75; // registro de identificação do dispositivo
const int PWR_MGMT_1 =    0x6B; // registro de configuração do gerenciamento de energia
const int GYRO_CONFIG =   0x1B; // registro de configuração do giroscópio
const int ACCEL_CONFIG =  0x1C; // registro de configuração do acelerômetro
const int ACCEL_XOUT =    0x3B; // registro de leitura do eixo X do acelerômetro
 
const int sda_pin = D5; // definição do pino I2C SDA
const int scl_pin = D6; // definição do pino I2C SCL
 
bool led_state = false;
String velocidade;
int vibration;

WiFiClient net;
MQTTClient client;
 
// variáveis para armazenar os dados "crus" do acelerômetro
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ; 

// função que configura a I2C com os pinos desejados 
void initI2C() 
{
  //Serial.println("---inside initI2C");
  Wire.begin(sda_pin, scl_pin);
}
 
// função que escreve um dado valor em um dado registro
void writeRegMPU(int reg, int val)      //aceita um registro e um valor como parâmetro
{
  Wire.beginTransmission(MPU_ADDR);     // inicia comunicação com endereço do MPU6050
  Wire.write(reg);                      // envia o registro com o qual se deseja trabalhar
  Wire.write(val);                      // escreve o valor no registro
  Wire.endTransmission(true);           // termina a transmissão
}
 
// função que lê de um dado registro
uint8_t readRegMPU(uint8_t reg)        // aceita um registro como parâmetro
{
  uint8_t data;
  Wire.beginTransmission(MPU_ADDR);     // inicia comunicação com endereço do MPU6050
  Wire.write(reg);                      // envia o registro com o qual se deseja trabalhar
  Wire.endTransmission(false);          // termina transmissão mas continua com I2C aberto (envia STOP e START)
  Wire.requestFrom(MPU_ADDR, 1);        // configura para receber 1 byte do registro escolhido acima
  data = Wire.read();                   // lê o byte e guarda em 'data'
  return data;                          //retorna 'data'
}
 
// função que procura pelo sensor no endereço 0x68
void findMPU(int mpu_addr)
{
  Wire.beginTransmission(MPU_ADDR);
  int data = Wire.endTransmission(true);
 
  if(data == 0)
  {
    Serial.print("Dispositivo encontrado no endereço: 0x");
    Serial.println(MPU_ADDR, HEX);
  }
  else 
  {
    Serial.println("Dispositivo não encontrado!");
  }
}
 
// função que verifica se o sensor responde e se está ativo
void checkMPU(int mpu_addr)
{
  findMPU(MPU_ADDR);
    
  int data = readRegMPU(WHO_AM_I); // Register 117 – Who Am I - 0x75
  
  if(data == 104) 
  {
    Serial.println("MPU6050 Dispositivo respondeu OK! (104)");
 
    data = readRegMPU(PWR_MGMT_1); // Register 107 – Power Management 1-0x6B
 
    if(data == 64) Serial.println("MPU6050 em modo SLEEP! (64)");
    else Serial.println("MPU6050 em modo ACTIVE!"); 
  }
  else Serial.println("Verifique dispositivo - MPU6050 NÃO disponível!");
}
 
// função de inicialização do sensor
void initMPU()
{
  setSleepOff();
  setGyroScale();
  setAccelScale();
}
 
//  função para configurar o sleep bit  
void setSleepOff()
{
  writeRegMPU(PWR_MGMT_1, 0); // escreve 0 no registro de gerenciamento de energia(0x68), colocando o sensor em o modo ACTIVE
}
 
// função para configurar as escalas do giroscópio
void setGyroScale()
{
  writeRegMPU(GYRO_CONFIG, 0);
}
 
// função para configurar as escalas do acelerômetro
void setAccelScale()
{
  writeRegMPU(ACCEL_CONFIG, 0);
}
 
// função que lê os dados 'crus'(raw data) do sensor
void readRawMPU()
{  
  Wire.beginTransmission(MPU_ADDR);       // inicia comunicação com endereço do MPU6050
  Wire.write(ACCEL_XOUT);                 // envia o registro com o qual se deseja trabalhar, começando com registro 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);            // termina transmissão mas continua com I2C aberto (envia STOP e START)
  Wire.requestFrom(MPU_ADDR, 14);         // configura para receber 14 bytes começando do registro escolhido acima (0x3B)
 
  AcX = Wire.read() << 8;                 // lê primeiro o byte mais significativo
  AcX |= Wire.read();                     // depois lê o bit menos significativo
  AcY = Wire.read() << 8;
  AcY |= Wire.read();
  AcZ = Wire.read() << 8;
  AcZ |= Wire.read();
 
  Tmp = Wire.read() << 8;
  Tmp |= Wire.read();
 
  GyX = Wire.read() << 8;
  GyX |= Wire.read();
  GyY = Wire.read() << 8;
  GyY |= Wire.read();
  GyZ = Wire.read() << 8;
  GyZ |= Wire.read(); 
 
  // Serial.print("AcX = "); Serial.print(AcX);
  // Serial.print(" | AcY = "); Serial.print(AcY);
  // Serial.print(" | AcZ = "); Serial.print(AcZ);
  // Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);
  // Serial.print(" | GyX = "); Serial.print(GyX);
  // Serial.print(" | GyY = "); Serial.print(GyY);
  // Serial.print(" | GyZ = "); Serial.println(GyZ);
 
  led_state = !led_state;
  digitalWrite(LED_BUILTIN, led_state);         // pisca LED do NodeMCU a cada leitura do sensor
  delay(50);                                        
}

void connectMQTT()
{
    Serial.print("Connecting MQTT: ");
    while (!client.connect(client_id, client_key, client_secret))
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println(" MQTT connected!");
}

void connectWIFI()
{
    Serial.print("Connecting Wi-Fi... ");
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Wi-Fi connected!");
}
 

void iniMotor(){
  pinMode(pin_motor, OUTPUT);
  digitalWrite(pin_motor, LOW);
}
 

void messageReceived(String &topic, String &payload){
  if(topic == "/vibration"){
    vibration = payload.toInt();
    configMotor();
  }
}

void configMotor(){
  Serial.println(vibration);
  if(vibration == 1){
    digitalWrite(pin_motor, HIGH);
    delay(500);
    digitalWrite(pin_motor, LOW);
    delay(500);
    digitalWrite(pin_motor, HIGH);
    delay(500);
    digitalWrite(pin_motor, LOW);
  }else{
    digitalWrite(pin_motor, LOW);
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  iniMotor();
 
  Serial.println("nIniciando configuração do MPU6050n");
  initI2C();
  initMPU();
  checkMPU(MPU_ADDR);

  Serial.println("nIniciando configuração do WiFi e MQTT");
  connectWIFI();
  client.begin("broker.shiftr.io", net);
  client.onMessage(messageReceived);
  connectMQTT();
 
  Serial.println("nConfiguração finalizada, iniciando loopn");  

  client.subscribe("/velocity");
  client.subscribe("/vibration");
}
 
void loop() {
  readRawMPU();    // lê os dados do sensor 

  client.loop();

  if(!client.connected()) {
    connectMQTT();
  }

  velocidade = String(GyX);
  client.publish("/velocity", velocidade);


  delay(100);  
}