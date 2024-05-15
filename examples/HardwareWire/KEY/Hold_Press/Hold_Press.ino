// ПРИМЕР РЕАГИРОВАНИЯ НА УДЕРЖАНИЕ ОДНОЙ КНОПОКИ С ЗАДАННЫМ ВРЕМЕНЕМ:                    //
// Реакция на удержание кнопки описана в примерах: Hold, Hold_Press и Time.               //
                                                                                          //
// (2RM) Реле электромеханическое на 2 канала (Metro-модуль):                             //
// (8X8) LED Матрица 8x8 - I2C (Metro-модуль):                                            // https://iarduino.ru/shop/Expansion-payments/led-matrica-8x8---i2c-metro-modul.html
// (BUZ) Зуммер - I2C (Metro-модуль):                                                     // https://iarduino.ru/shop/Expansion-payments/zummer---i2c-metro-modul.html
// (DHT) Датчик температуры и влажности - I2C (Metro-модуль):                             // https://iarduino.ru/shop/Sensory-Datchiki/metro_temperature_humidity.html
// (DSL) Датчик освещенности, люксметр - I2C (Metro-модуль):                              // https://iarduino.ru/shop/Sensory-Datchiki/metro_luxmeter.html
// (EXT) Расширитель выводов - I2C (Metro-модуль):                                        // https://iarduino.ru/shop/Expansion-payments/metro-expander.html
// (KEY) Кнопка - I2C (Metro-модуль):                                                     // https://iarduino.ru/shop/Expansion-payments/knopka---i2c-metro-modul.html
// (RES) Потенциометр - I2C (Metro-модуль):                                               //
// (RGB) RGB светодиод - I2C (Metro-модуль):                                              // https://iarduino.ru/shop/Expansion-payments/rgb-svetodiod---i2c-metro-modul.html
// Плата управления Metro Leonardo:                                                       // https://iarduino.ru/shop/boards/metro-leonardo.html
// Плата управления Metro ESP:                                                            // https://iarduino.ru/shop/boards/metro-esp.html
// Информация о подключении модулей к шине I2C:                                           // https://wiki.iarduino.ru/page/i2c_connection/
                                                                                          //
#include <Wire.h>                                                                         // Подключаем библиотеку для работы с аппаратной шиной I2C, до подключения библиотеки iarduino_Metro.
#include <iarduino_Metro.h>                                                               // Подключаем библиотеку.
                                                                                          //
uint8_t sum;                                                                              // Объявляем переменную для хранения количества найденных модулей Metro.
                                                                                          //
void setup(){                                                                             //
//  Определяем все модули на шине I2C и сохраняем их количество в переменную sum:         //
    sum=iarduino_Metro_Start(&Wire); // &Wire1, &Wire2 ...                                // Функция принимает два необязательных параметра: ссылка на объект шины I2C (по умолчанию &Wire), номер адресного вывода (по умолчанию 12).
//  Теперь нам доступен массив Metro содержащий sum элементов для управления модулями.    // Metro[0] управляет ближайшим к Arduino модулем, Metro[1] управляет следующим модулем и т.д до последнего модуля Metro[sum-1].
                                                                                          //
//  Готовимся управлять светодиодом на плате Arduino:                                     //
    pinMode     (LED_BUILTIN, OUTPUT);                                                    // Конфигурируем вывод к которому подключён светодиод как выход.
    digitalWrite(LED_BUILTIN, LOW   );                                                    // Устанавливаем низкий логический уровень на выводе к которому подключён светодиод (выключаем светодиод).
                                                                                          //
//  Проверяем наличие модулей Metro на шине I2C:                                          //
    while(sum==0){;}                                                                      // Если модули Metro не обнаружены, то входим в бесконечный цикл while, тогда цикл loop выполняться не будет.
    while(Metro[0].model!=MOD_KEY){;}                                                     // Если ближайший к Arduino модуль Metro не является кнопкой, то так же входим в бесконечный цикл while.
                                                                                          //
//  Задаём время удержания кнопки:                                                        //
    Metro[0].set(9000,6000,3000);                                                         // Функция set задаёт время удержания кнопки для срабатывания функции read с параметрами KEY_HOLD1, KEY_HOLD2 и KEY_HOLD3.
}                                                                                         // Можно указывать время от 0 до 25500мс.
                                                                                          //
void loop(){                                                                              //
//  Мигаем светодиодом на плате Arduino с частотой зависящей от времени удержания кнопки: // Время срабатывания Функции read с параметрами KEY_HOLD1, KEY_HOLD2 и KEY_HOLD3, задано функцией set.
    if(Metro[0].read(KEY_HOLD1)  ){digitalWrite(LED_BUILTIN, (millis()% 250<125) ); }else // Если кнопка удерживается дольше 9 секунд, то мигаем светодиодом каждые 1/8 секунды (светодиод из  250мс светится  125мс).
    if(Metro[0].read(KEY_HOLD2)  ){digitalWrite(LED_BUILTIN, (millis()% 500<250) ); }else // Если кнопка удерживается дольше 6 секунд, то мигаем светодиодом каждые 1/4 секунды (светодиод из  500мс светится  250мс).
    if(Metro[0].read(KEY_HOLD3)  ){digitalWrite(LED_BUILTIN, (millis()%1000<500) ); }else // Если кнопка удерживается дольше 3 секунд, то мигаем светодиодом каждые 1/2 секунды (светодиод из 1000мс светится  500мс).
    if(Metro[0].read(KEY_PRESSED)){digitalWrite(LED_BUILTIN, HIGH                ); }else // Если кнопка нажата, но не попала под предыдущие условия, значит она удерживается менее 3 секунд, тогда включаем светодиод.
                                  {digitalWrite(LED_BUILTIN, LOW                 ); }     // Данная строка будет выполняться только если не выполнено ни одно из предыдущих условий, значит кнопка не нажата, тогда выключаем светодиод.
}