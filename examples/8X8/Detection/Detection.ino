// Пример вывода информации о обнаруженных модулях Metro:                              //
#include <Wire.h>                                                                      // Подключаем библиотеку Wire. Для работы с Arduino/Piranha, эту библиотеку можно не подключать.
#include <iarduino_Metro.h>                                                            // Подключаем библиотеку.
                                                                                       //
uint8_t sum;                                                                           // Объявляем переменную для хранения количества найденных модулей Metro.
                                                                                       //
void setup(){                                                                          //
//  Определяем все модули на шине I2C и сохраняем их количество в переменную sum:      //
    sum=iarduino_Metro_Start();                                                        // В качестве аргумента функции iarduino_Metro_Start() можно указать номер адресного вывода (если вывод не указан, то будет использован D12).
//  Теперь нам доступен массив Metro содержащий sum элементов для управления модулями. // Metro[0] управляет ближайшим к Arduino модулем, Metro[1] управляет следующим модулем и т.д до последнего модуля Metro[sum-1].
                                                                                       //
//  Выводим информацию о найденных модулях:                                            //
                                      Serial.begin  (9600);                            // Инициируем связь с монитором последовательного порта на скорости 9600 бит/сек.
                                      while(!Serial){;}                                // Ждём готовность к работе аппаратной шины UART.
    if(sum==0){                       Serial.println(F("Модули линейки не найдены"));  // Если модули не найдены, то сообщаем об этом.
    }else{                            Serial.print  (F("Найдено модулей: "));          // Иначе, выводим:
                                      Serial.print  (sum);                             // - их количество,
                                      Serial.println(".");                             //
//      Проходим по всем найденным модулям:                                            //
        for(int i=0; i<sum; i++){     Serial.print  (i+1);                             // - номер по порядку,
                                      Serial.print  (F(")\tадрес = "));                //
                                      Serial.print  (Metro[i].address);                // - адрес на шине I2C,
                                      Serial.print  (F(",\tтип - "));                  // 
            switch(Metro[i].model){                                                    // - тип модуля (тип определяется по значению model):
                case MOD_KEY:         Serial.print  (F("кнопка   "));         break;   //
                case MOD_RGB:         Serial.print  (F("светодиод"));         break;   //
                case MOD_RES:         Serial.print  (F("потенциометр"));      break;   //
                case MOD_BUZ:         Serial.print  (F("звукоизлучатель"));   break;   //
                case MOD_DHT:         Serial.print  (F("датчик DHT"));        break;   //
                case MOD_DSL:         Serial.print  (F("датчик света"));      break;   //
                case MOD_8X8:         Serial.print  (F("матрица 8х8"));       break;   //
                default:              Serial.print  (F("не определён"));      break;   //
            }                         Serial.print  (F(",\tверсия "));                 // - выводим
                                      Serial.print  (Metro[i].version);                // - версию прошивки
                                      Serial.print  (F(", занимает "));                // - и выводим
                                      Serial.print  (Metro[i].size);                   // - занимаемое место в ОЗУ.
                                      Serial.println(F(" байт ОЗУ."));                 //
        }                                                                              //
    }                                                                                  //
}                                                                                      //
                                                                                       //
void loop(){}                                                                          //