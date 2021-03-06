[![](https://iarduino.ru/img/logo.svg)](https://iarduino.ru)[![](https://wiki.iarduino.ru/img/git-shop.svg?3)](https://iarduino.ru) [![](https://wiki.iarduino.ru/img/git-wiki.svg?2)](https://wiki.iarduino.ru) [![](https://wiki.iarduino.ru/img/git-lesson.svg?2)](https://lesson.iarduino.ru)[![](https://wiki.iarduino.ru/img/git-forum.svg?2)](http://forum.trema.ru)

# iarduino\_Metro

**This is a library for Arduino IDE. It allows to control [Metro](https://iarduino.ru/search/?text=Metro) modules made by iArduino.ru**

**Данная библиотека для Arduino IDE позвляет управлять модулями [Metro](https://iarduino.ru/search/?text=Metro)**

> Подробнее про установку библиотеки читайте в нашей [инструкции](https://wiki.iarduino.ru/page/Installing_libraries/).

> Подробнее про подключение к [Arduino UNO](https://iarduino.ru/shop/boards/arduino-uno-r3.html)/[Piranha UNO](https://iarduino.ru/shop/boards/piranha-uno-r3.html) читайте на нашей [wiki](https://wiki.iarduino.ru/page/metro-info/)


| Модель | Ссылка на магазин |
|--|--|
| ![](https://wiki.iarduino.ru/img/resources/1049/1049.svg) | https://iarduino.ru/shop/Expansion-payments/led-matrica-8x8---i2c-metro-modul.html |
| ![](https://wiki.iarduino.ru/img/resources/1013/1013.svg) | https://iarduino.ru/shop/Expansion-payments/rgb-svetodiod---i2c-metro-modul.html |
| ![](https://wiki.iarduino.ru/img/resources/1017/1017.svg) | https://iarduino.ru/shop/Sensory-Datchiki/metro_luxmeter.html |
| ![](https://wiki.iarduino.ru/img/resources/1016/1016.svg) | https://iarduino.ru/shop/Sensory-Datchiki/metro_temperature_humidity.html |
| ![](https://wiki.iarduino.ru/img/resources/1015/1015.svg) | https://iarduino.ru/shop/Expansion-payments/zummer---i2c-metro-modul.html |
| ![](https://wiki.iarduino.ru/img/resources/1014/1014.svg) | https://iarduino.ru/shop/Expansion-payments/knopka---i2c-metro-modul.html |
| ![]() | Скоро здесь будет расширитель выводов |


## Назначение функций и переменных:

### Подключение библиотеки и создание массива объектов:
```C++
#include <Wire.h> // Подключаем библиотеку Wire для работы с шиной I2C.
#include <iarduino_Metro> // Подключаем библиотеку iarduino_Metro для работы с модулем/модулями линейки "Metro".

iarduino_Metro_Start( [ ВЫВОД ] ); // Поиск всех модулей, назначение им адресов и создание массива объектов Metro.
```

### Назначение переменных:

**Текущий адрес** 

```C++
Metro[ индекс ].address // Хранит текущий адрес модуля на шине I2C.
```

**Идентификатор типа** 

```C++
Metro[ индекс ].model // Хранит идентификатор типа модуля.
```

**Версия прошивки** 

```C++
Metro[ индекс ].version // Хранит версию прошивки модуля.
```

```C++
Metro[ индекс ].size // Хранит использованный для работы с модулем объем памяти ОЗУ в байтах.
```

### Назначение функций для модуля Metro - Кнопка:

> Подробное описание и примеры работы с кнопкой, находится в разделе [Wiki - Кнопка, I2C (Metro-модуль)](https://wiki.iarduino.ru/page/metro-button/) на нашем сайте.

```C++
Metro[ индекс ].read( [ПАРАМЕТР] ); // Чтение событий и состояний кнопки.
```

```C++
Metro[ индекс ].set( ВРЕМЯ1 , ВРЕМЯ2 , ВРЕМЯ3 ); // Указание времени удержания кнопки.
```

### Назначение функций для модуля Metro - RGB светодиод:

> Подробное описание и примеры работы с RGB светодиодом, находится в разделе [Wiki - RGB светодиод, i2c (Metro-модуль)](https://wiki.iarduino.ru/page/metro-led/) на нашем сайте.

**Выключение светодиода**

```C++
Metro[ индекс ].off(); // Выключение светодиода.
```

**Включение светодиода**

```C++
Metro[ индекс ].on( [ ЦВЕТ [ , ДЛИТЕЛЬНОСТЬ [ , ПАУЗА [ , КОЛИЧЕСТВО ]]]] ); // Включение светодиода.
```

**Включение светодиода**

```C++
Metro[ индекс ].on( [ RGB(красный,зелёный,синий) [ , ДЛИТЕЛЬНОСТЬ [ , ПАУЗА [ , КОЛ-ВО ]]]] ); // Включение светодиода.
```

**Включение функций перелива**

```C++
Metro[ индекс ].on( [ RGB( ФУНКЦИЯ ) [ , ДЛИТЕЛЬНОСТЬ [ , ПАУЗА ]]] ); // Включение функций перелива светодиода.
```

**Установка частоты ШИМ**

```C++
Metro[ индекс ].frequency( ЧАСТОТА ); // установка частоты ШИМ светодиода.
```

### Назначение функций для модуля Metro - Зуммер:

> Подробное описание и примеры работы с зуммером, находится в разделе [Wiki - Зуммер, i2c (Metro-модуль)](https://wiki.iarduino.ru/page/metro-zummer/) на нашем сайте.

**Выключение звука**

```C++
Metro[ индекс ].off(); // Выключение звука.
```

**Воспроизведение звука**

```C++
Metro[ индекс ].on( ЧАСТОТА , ДЛИТЕЛЬНОСТЬ , ПАУЗА , КОЛИЧЕСТВО ); // Воспроизведение звука.
```

### Назначение функций для модуля Metro - Датчик температуры и влажности:

> Подробное описание и примеры работы с датчиком, находится в разделе [Wiki - Датчик DHT, i2c (Metro-модуль)](https://wiki.iarduino.ru/page/metro-dht/) на нашем сайте.

**Чтение температуры или влажности**

```C++
Metro[ индекс ].read( [ПАРАМЕТР] ); // Чтение температуры или влажности.
```

**Указание диапазона определяющего факт изменений показаний**

```C++
Metro[ индекс ].set( ТЕМПЕРАТУРА , ВЛАЖНОСТЬ ); // Указание диапазона определяющего факт изменений показаний.
```

### Назначение функций для модуля Metro - Датчик освещенности (люксметр):

> Подробное описание и примеры работы с датчиком, находится в разделе [Wiki - Датчик освещенности, люксметр, i2c (Metro-модуль)](https://wiki.iarduino.ru/page/metro-lux/) на нашем сайте.

**Чтение освещённости**

```C++
Metro[ индекс ].read( [ПАРАМЕТР] ); // Чтение освещённости.
```

**Указание диапазона определяющего факт изменений показаний**

```C++
Metro[ индекс ].set( ОСВЕЩЁННОСТЬ ); // Указание диапазона определяющего факт изменений показаний.
```

### Назначение функций для модуля Metro - Расширитель выводов:

> Подробное описание и примеры работы с расширителем выводов, находится в разделе [Wiki - Расширитель выводов, i2c - flash (Metro-модуль)](https://wiki.iarduino.ru/page/metro-extender/) на нашем сайте.

**Чтение вывода** 

```C++
Metro[ индекс ].read( ВЫВОД [, ТИП ] ); // Чтение вывода с указанием типа уровня (логический/аналоговый).
```

**Установка уровня или поворот сервопривода**

```C++
Metro[ индекс ].set( ВЫВОД , УРОВЕНЬ [, ТИП] ); // Установка уровня (с указанием его типа), или поворот сервопривода в заданный угол.
```

**Указание частоты ШИМ**

```C++
Metro[ индекс ].frequency( ЧАСТОТА ); // Указание частоты сигнала ШИМ.
```

### Назначение функций для модуля Metro - LED Матрица 8x8:

> Подробное описание и примеры работы с LED матрицей 8x8, находится в разделе [Wiki - LED Матрица 8x8, i2c (Metro-модуль)](https://wiki.iarduino.ru/page/metro-matrix-led/) на нашем сайте.

**Вывод символа**

```C++
Metro[ индекс ].set( 'СИМВОЛ' ); // Вывод символа на экран матрицы.
```

**Вывод текста**

```C++
Metro[ индекс ].set( "ТЕКСТ" , СКОРОСТЬ [ , ПАУЗА ] ); // Вывод текста бегущей строки на экран матрицы.
```

**Выключение дисплея**

```C++
Metro[ индекс ].off( [АНИМАЦИЯ] ); // Выключение дисплея.
```

**Включение дисплея** 

```C++
Metro[ индекс ].on( [ МАССИВ ] , [ АНИМАЦИЯ ] ); // Включение дисплея и вывод изображения.
```

**Установка яркости** 

```C++
Metro[ индекс ].on( ЯРКОСТЬ ); // Установка яркости свечения дисплея.
```

**Поворот дисплея**

```C++
Metro[ индекс ].on( ПОВОРОТ ); // Поворот дисплея.
```

**Указание частоты** 

```C++
Metro[ индекс ].frequency( ЧАСТОТА ); // Указание частоты обновления кадров в секунду.
```
