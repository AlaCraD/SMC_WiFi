#include <nrf_hal.h>

#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

RF24           radio(9, 10);

const byte     SIZE=32;
byte           data[SIZE];
byte           i;
byte temp;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    radio.begin();                                        // Инициируем работу nRF24L01+
    radio.setAutoAck(1);
    radio.setChannel(5);                                  // Указываем канал приёма данных (от 0 до 127), 5 - значит приём данных осуществляется на частоте 2,405 ГГц (на одном канале может быть только 1 приёмник и до 6 передатчиков)
    radio.setDataRate     (RF24_1MBPS);                   // Указываем скорость передачи данных (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), RF24_1MBPS - 1Мбит/сек
    radio.setPALevel      (RF24_PA_HIGH);                 // Указываем мощность передатчика (RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_HIGH=-6dBm, RF24_PA_MAX=0dBm)
    radio.openReadingPipe (1, 0x1234567890LL);            // Открываем 1 трубу с идентификатором 0x1234567890 для приема данных (на ожном канале может быть открыто до 6 разных труб, которые должны отличаться только последним байтом идентификатора)
    radio.startListening  ();  
    radio.powerUp();                   
}

void loop() {
//  // put your main code here, to run repeatedly:
//  if(radio.available()){                                // Если в буфере имеются принятые данные
//        radio.read(&data, sizeof(data));
//        Serial.println(data,HEX);
//  }  
//  else  { 
//    Serial.println("No data");
//    }
    if(radio.available())
    {
      radio.read(&temp, 1);
      Serial.write(temp);
      ///radio.read(&data, 10);
      //Serial.write(data, 10);
      
    } 
   
}
