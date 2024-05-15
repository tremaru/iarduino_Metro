// ПРИМЕР ДЛЯ ОДНОГО ДАТЧИКА ОСВЕЩЁННОСТИ:                                             // В данном примере мы не просто выводим данные, а задаём диапазон для их вывода, это экономит место при выводе данных в монитор.
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
                                                                                       //
//  Проверяем наличие модулей Metro на шине I2C:                                       //
    while(sum==0){;}                                                                   // Если модули Metro не обнаружены, то входим в бесконечный цикл while, тогда цикл loop выполняться не будет.
    while(Metro[0].model!=MOD_DSL){;}                                                  // Если ближайший к Arduino модуль Metro не является датчиком освещённости, то так же входим в бесконечный цикл while.
                                                                                       //
    delay(1000);                                                                       // Ждём 1 секунду для стабилизации показаний датчика.
                                                                                       //
//  Задаём диапазон изменений показаний датчика, на который требуется реагировать:     //
    Metro[0].set(100);                                                                 // Функция set задаёт диапазон изменений в показаниях датчика (от текущего значения) для срабатывания функции read с параметрами DSL_CHANGED.
                                                                                       // Параметр функции set задаёт изменение освещённости на которое следует реагировать (от 1 до 255 лк).
//  Выводим начальную освещённость:                                                    //
    Serial.print  ("Освещённость = ");                                                 // Выводим текст.
    Serial.print  ( Metro[0].read( DSL_LUX ) );                                        // Выводим освещённость.
    Serial.println(" лк.");                                                            // Выводим текст с переводом строки.
}                                                                                      //
                                                                                       //
void loop(){                                                                           //
//  Если освещённость изменилась на заданное ранее значение:                           //
    if( Metro[0].read(DSL_CHANGED) ){                                                  // Функция read с параметром DSL_CHANGED вернёт true только если освещённость изменилась на 100 лк и более (это значение мы указали функцией set).
//      То выводим текущую освещённость:                                               // Теперь функция read с параметром DSL_CHANGED вернёт true только если освещённость опять изменится на 100 лк и более.
        Serial.print  ("Освещённость = ");                                             // Выводим текст.
        Serial.print  ( Metro[0].read( DSL_LUX ) );                                    // Выводим освещённость.
        Serial.println(" лк.");                                                        // Выводим текст с переводом строки.
    }                                                                                  //
    delay(1000);                                                                       // Ставим задержку на 1 секунду.
}                                                                                      //