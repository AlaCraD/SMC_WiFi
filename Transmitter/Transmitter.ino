
#include <SPI.h>                                          // Подключаем библиотеку для работы с шиной SPI
#include <nRF24L01.h>                                     // Подключаем файл настроек из библиотеки RF24
#include <RF24.h>                                         // Подключаем библиотеку для работы с nRF24L01+
#include <RF24_config.h>

RF24           radio(9, 10);                              // Создаём объект radio для работы с библиотекой RF24, указывая номера выводов nRF24L01+ (CE, CSN)
                                   // Создаём массив для приёма данных
//byte           sum=255;
byte           temp=0;
byte           count=0;
const byte     SIZE=32;
byte           data[SIZE];
int            i;
byte           summ[] = {10,10,10,10,10,10,10,10,10,90};

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
        //temp = count++;
        radio.writeFast(&temp, 1);
        //Serial.write(temp);
        //data[count] = temp;
        //count++;
    }
    // считываем показания Trema потенциометра с вывода A2 и записываем их в 1 элемент массива data
    
    //radio.write(&summ, sizeof(summ));
    
    

    // отправляем данные из массива data указывая сколько байт массива мы хотим отправить. Отправить данные можно с проверкой их доставки: if( radio.write(&data, sizeof(data)) ){данные приняты приёмником;}else{данные не приняты приёмником;}
}
