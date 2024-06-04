// ПРИМЕР ДЛЯ ОДНОЙ ИЛИ НЕСКОЛЬКИХ КНОПОК:                                             //
                                                                                       //
// (2RM) Реле электромеханическое на 2 канала (Metro-модуль):                          //
// (8X8) LED Матрица 8x8 - I2C (Metro-модуль):                                         // https://iarduino.ru/shop/Expansion-payments/led-matrica-8x8---i2c-metro-modul.html
// (BUZ) Зуммер - I2C (Metro-модуль):                                                  // https://iarduino.ru/shop/Expansion-payments/zummer---i2c-metro-modul.html
// (DHT) Датчик температуры и влажности - I2C (Metro-модуль):                          // https://iarduino.ru/shop/Sensory-Datchiki/metro_temperature_humidity.html
// (DSL) Датчик освещенности, люксметр - I2C (Metro-модуль):                           // https://iarduino.ru/shop/Sensory-Datchiki/metro_luxmeter.html
// (EXT) Расширитель выводов - I2C (Metro-модуль):                                     // https://iarduino.ru/shop/Expansion-payments/metro-expander.html
// (KEY) Кнопка - I2C (Metro-модуль):                                                  // https://iarduino.ru/shop/Expansion-payments/knopka---i2c-metro-modul.html
// (RES) Потенциометр - I2C (Metro-модуль):                                            //
// (RGB) RGB светодиод - I2C (Metro-модуль):                                           // https://iarduino.ru/shop/Expansion-payments/rgb-svetodiod---i2c-metro-modul.html
// Плата управления Metro Leonardo:                                                    // https://iarduino.ru/shop/boards/metro-leonardo.html
// Плата управления Metro ESP:                                                         // https://iarduino.ru/shop/boards/metro-esp.html
// Информация о подключении модулей к шине I2C:                                        // https://wiki.iarduino.ru/page/i2c_connection/
                                                                                       //
#include <Wire.h>                                                                      // Подключаем библиотеку для работы с аппаратной шиной I2C, до подключения библиотеки iarduino_Metro.
#include <iarduino_Metro.h>                                                            // Подключаем библиотеку.
                                                                                       //
uint8_t sum;                                                                           // Объявляем переменную для хранения количества найденных модулей Metro.
                                                                                       //
void setup(){                                                                          //
//  Определяем все модули на шине I2C и сохраняем их количество в переменную sum:      //
    sum=iarduino_Metro_Start(&Wire); // &Wire1, &Wire2 ...                             // Функция принимает два необязательных параметра: ссылка на объект шины I2C (по умолчанию &Wire), номер адресного вывода (по умолчанию 12).
//  Теперь нам доступен массив Metro содержащий sum элементов для управления модулями. // Metro[0] управляет ближайшим к Arduino модулем, Metro[1] управляет следующим модулем и т.д до последнего модуля Metro[sum-1].
                                                                                       //
//  Готовимся выводить информацию в монитор последовательного порта:                   //
    Serial.begin(9600);                                                                // Инициируем связь с монитором последовательного порта на скорости 9600 бит/сек.
    while(!Serial){;}                                                                  // Ждём готовность к работе аппаратной шины UART.
}                                                                                      //
                                                                                       //
void loop(){                                                                           //
    uint8_t j=0;                                                                       // Определяем переменную для хранения порядкового номера кнопки.
//  Проходим по всем найденным модулям:                                                //
    for(uint8_t i=0; i<sum; i++){                                                      // Модуль с N i может быть не кнопкой (а, например, светодиодом), по этому мы и ввели переменную j которая считает только кнопки.
//      Если очередной модуль i является кнопкой:                                      //
        if(Metro[i].model==MOD_KEY){                                                   // Тип модуля определяется по значению model.
            j++;                                                                       // Увеличиваем порядковый номер кнопки.
//          Если кнопка нажимается:                                                    //
            if( Metro[i].read( KEY_PUSHED ) ){                                         // Если функция read с параметром KEY_PUSHED вернула true, значит кнопка нажимается.
                Serial.print  ("Кнопка N ");                                           // (значит сейчас кнопка нажата, но при предыдущем обращении к функции read, она была отпущена)
                Serial.print  (j);                                                     //
                Serial.println(" нажимается.");                                        //
            }                                                                          //
//          Если кнопка отпускается:                                                   //
            if( Metro[i].read( KEY_RELEASED ) ){                                       // Если функция read с параметром KEY_RELEASED вернула true, значит кнопка отпускается.
                Serial.print  ("Кнопка N ");                                           // (значит сейчас кнопка отпущена, но при предыдущем обращении к функции read, она была нажата)
                Serial.print  (j);                                                     //
                Serial.println(" отпускается.");                                       //
            }                                                                          //
//          Если кнопка удерживается нажатой:                                          //
            if( Metro[i].read( KEY_PRESSED ) ){                                        // Если функция read с параметром KEY_PRESSED вернула true, значит кнопка ужерживается в нажатом состоянии.
                Serial.print  ("Кнопка N ");                                           //
                Serial.print  (j);                                                     //
                Serial.println(" удерживается.");                                      // Так как состояние "удерживается" (в отличии от "нажимается" или "отпускается") может длиться долго, то ...
            }                                                                          //
        }                                                                              // Благодаря наличию переменной j мы выводим номер кнопки, а не порядковый номер модуля.
    }                                                                                  // Значит скетч будет корректно выводить номер кнопки, даже если на шине I2C есть другие модули Metro (не являющиеся кнопками).
    delay(1000);                                                                       // ставим задержку на 1 секунду. Это предотвратит быстрое заполнение монитора строками "Кнопка N ... удерживается.".
}                                                                                      //
                                                                                       //
/*  Параметры функции read() для кнопки:                                               //
 *  KEY_PUSHED                 - вернуть флаг действия нажатия на кнопку.              // Возвращает true если кнопка была отпущена, а стала нажата.
 *  KEY_RELEASED               - вернуть флаг действия отпускания кнопки.              // Возвращает true если кнопка была нажата, а стала отпущена.
 *  KEY_CHANGED                - вернуть флаг изменения состояния кнопки.              // Возвращает true если кнопка была нажата, а стала отпущена, или была отпущена, а стала нажата.
 *  KEY_PRESSED (по умолчанию) - вернуть флаг состояния нажатия на кнопку.             // Возвращает true если кнопка нажата.
 *  KEY_HOLD3                  - вернуть флаг удержания кнопки дольше времени HOLD3.   // Возвращает true если кнопка удерживается нажатой дольше времени HOLD3. Время можно задать функцией set(HOLD1,HOLD2,HOLD3);
 *  KEY_HOLD2                  - вернуть флаг удержания кнопки дольше времени HOLD2.   // Возвращает true если кнопка удерживается нажатой дольше времени HOLD2. Время можно задать функцией set(HOLD1,HOLD2,HOLD3);
 *  KEY_HOLD1                  - вернуть флаг удержания кнопки дольше времени HOLD1.   // Возвращает true если кнопка удерживается нажатой дольше времени HOLD1. Время можно задать функцией set(HOLD1,HOLD2,HOLD3);
 *  KEY_TRIGGER                - вернуть флаг меняющий состояние при каждом нажатии.   // Возвращает флаг который меняет своё состояние (true/false) при каждом новом нажатии на кнопку.
 *  KEY_TIME                   - вернуть время текущего состояния кнопки в мс.         // Возвращает время текущего удержания или простоя кнопки.
 *  KEY_SUM                    - вернуть количество нажатий на кнопку.                 // Возвращает количество совершённых нажатий после последнего чтения этого количества.
 */
