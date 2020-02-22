#include <SPI.h>
#include <RF24.h>
#include <RF24_config.h>                                       // Подключаем библиотеку для работы с nRF24L01+
/*      
 *       RF24
 * Черный - GND
 * Красный - 3.3V
 * Оранжевый - 13 pin
 * Белый - 12 pin
 * Желтый - 11 pin
 * Фиолетовый - 10 pin 
 * Зеленый - 9 pin 
 * 
 *     RS232-UART  
 * Фиолетовый - 5V
 * Синий - TX(Arduino) и RXD(RS232-UART)
 * Зеленый - RX(Arduino) и TXD(RS232-UART)
 * Желтый - GND
 */

RF24           radio(9, 10);                              // Создаём объект radio для работы с библиотекой RF24, указывая номера выводов nRF24L01+ (CE, CSN)

byte           temp=0;

void setup(){
    Serial.begin(115200);
    radio.begin();                                        // Инициируем работу nRF24L01+
    radio.setAutoAck(1);
    radio.setChannel(5);                                  // Указываем канал передачи данных (от 0 до 127), 5 - значит передача данных осуществляется на частоте 2,405 ГГц (на одном канале может быть только 1 приёмник и до 6 передатчиков)
    radio.setDataRate     (RF24_1MBPS);                   // Указываем скорость передачи данных (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), RF24_1MBPS - 1Мбит/сек
    radio.setPALevel      (RF24_PA_HIGH);                 // Указываем мощность передатчика (RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_HIGH=-6dBm, RF24_PA_MAX=0dBm)
    radio.openWritingPipe (0x1234567890LL);               // Открываем трубу с идентификатором 0x1234567890 для передачи данных (на одном канале может быть открыто до 6 разных труб, которые должны отличаться только последним байтом идентификатора)
    radio.stopListening();
    radio.powerUp();
}
void loop(){
    while(Serial.available()){
        temp = Serial.read();
        radio.writeFast(&temp, 1);
    }
}
