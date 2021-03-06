// Пример для одного расширителя выводов:                                              //
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
//  Проверяем наличие модулей Metro на шине I2C:                                       //
    while(sum==0){;}                                                                   // Если модули Metro не обнаружены, то входим в бесконечный цикл while, тогда цикл loop выполняться не будет.
    while(Metro[0].model!=MOD_EXT){;}                                                  // Если ближайший к Arduino модуль Metro не является расширителем выводов, то так же входим в бесконечный цикл while.
}                                                                                      //
                                                                                       //
void loop(){                                                                           //
//  Устанавливаем уровни на выводах модуля:                                            //
    Metro[0].set(0,    0, EXT_DIGITAL);                                                // Устанавливаем на 0 выводе уровень логического 0.
    Metro[0].set(1,    0, EXT_ANALOG );                                                // Устанавливаем на 1 выводе аналоговый уровень (сигнал ШИМ) равный 0 (0%).
    Metro[0].set(2,    0, EXT_SERVO  );                                                // Устанавливаем сервопривод подключённый к 2 выводу в угол равный 0°.
    delay(500);                                                                        //
    Metro[0].set(0,    1, EXT_DIGITAL);                                                // Устанавливаем на 0 выводе уровень логической 1.
    Metro[0].set(1, 4095, EXT_ANALOG );                                                // Устанавливаем на 1 выводе аналоговый уровень (сигнал ШИМ) равный 4095 (100%).
    Metro[0].set(2,  180, EXT_SERVO  );                                                // Устанавливаем сервопривод подключённый к 2 выводу в угол равный 180°.
    delay(500);                                                                        //
/*                                                                                     //
 *   Metro[0].read( вывод , тип ); - считать уровень с вывода.                         // Функция считывает указанный тип сигнала с указанного вывода.         Вывод автоматически конфигурируется в режим работы на вход.
 *   Metro[0].set( вывод , уровень, тип ); - установть уровень на выводе.              // Функция устанавливает уровень указанного типа на указанном выводе.   Вывод автоматически конфигурируется в режим работы на выход.
 *   Metro[0].frequency( частота ); - установить частоту работы ШИМ для всех выводов.  // Функция устанавливает частоту с которой будет выводиться сигнал ШИМ. Частота ШИМ не влияет на коэффициент заполнения ШИМ.
 *                                                                                     //
 *   Частота ШИМ (по умолчанию) 490 Гц.                                                //
 *   После установки угла сервопривода функцией set( вывод , угол , EXT_SERVO );       //
 *   частота ШИМ для любого вывода снизится до 50 Гц.                                  // 
 *   Частота ШИМ не влияет на установленный коэффициент заполнения ШИМ.                // 
 */                                                                                    //
}                                                                                      //