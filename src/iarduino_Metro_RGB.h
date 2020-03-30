																										//
#ifndef iarduino_Metro_RGB_h																			//	Функции работы с RGB светодиодом.
#define iarduino_Metro_RGB_h																			//
																										//
class iarduino_Metro_RGB: public iarduino_Metro_BASE{													//	Определяем производный класс iarduino_Metro_RGB.
	public:																								//
	/**	функции данного производного класса iarduino_Metro_RGB		**/									//
	/**	дублирую функции полиморфного класса iarduino_Metro_BASE	**/									//
																										//
//		Функции не используемые в данном модуле:														//
		bool	begin			(int i0=NOT2, int i1=NOT2	){return 0;}								//	Инициализация модуля.
		int		test			(int i0=NOT2, int i1=NOT2	){return 0;}								//	Самотестирование модуля.
		long	getVar			(int i0=NOT2				){return 0;}								//	Возврат значений переменных.
																										//
//		Выполняем действия:																				//
		bool	action			(int i0=NOT2, int i1=NOT2	){											//	
								uint8_t data[8] = {0,0,0,0,1,0,0,0};									//	Определяем массив для хранения данных пакетно записываемых в модуль (FLG=0, R=0, G=0, B=0, ON=1, OFF=0, BLK=0, FUNC=0).
								bool    result  = false;												//	Определяем флаг результата возвращаемый функцией action.
								uint8_t sumtry  = 10;													//	Количество попыток чтения/записи.
								if(func_end || i0==0){													//	Если установлен флаг func_end или требуется выполнить действие № 0 (отключить светодиод), то ...
								//	Отключаем выполнение цветовой функции:								//
									do{	result = objI2C.writeByte( i1, REG_DATA+7,0);					//	Записываем 0 в регистр REG_DATA+7 (FUNCTIONS) модуля с адресом i1.
										sumtry	--;	if(!result){delay(1);}								//	Уменьшаем количество попыток записи и устанавливаем задержку при неудаче.
									}	while		(!result && sumtry>0);								//	Повторяем запись если она завершилась неудачей, но не более sumtry попыток.
									delay(4);															//
									func_end=false; 													//	Сбрасываем флаг func_end.
								}																		//
								switch(i0){																//
								//	Действие № 0 - отключить светодиод:									//
									case 0:																//
										do{	result = objI2C.writeBytes( i1, REG_DATA, data, 7);			//	Записываем 7 элементов массива data в модуль с адресом i1, начиная с регистра REG_DATA.
											sumtry	--;	if(!result){delay(1);}							//	Уменьшаем количество попыток записи и устанавливаем задержку при неудаче.
										}	while		(!result && sumtry>0);							//	Повторяем запись если она завершилась неудачей, но не более sumtry попыток.
									break;																//
								//	Действие № 1 - включить светодиод:									//
									case 1:																//
										if(func){														//	Если задан номер цветовой функции, то...
											data[4] = uint8_t((time_on ==NOT2)? 10:time_on 	);			//	Определяем время для цветовой функции.
											data[5] = uint8_t((time_off==NOT2)? 10:time_off	);			//	Определяем время для цветовой функции.
											data[7] = func;												//	Определяем номер выполняемой цветовой функции.
											do{	result = objI2C.writeBytes( i1, REG_DATA, data, 8);		//	Записываем 8 элементов массива data в модуль с адресом i1, начиная с регистра REG_DATA.
												sumtry	--;	if(!result){delay(1);}						//	Уменьшаем количество попыток записи и устанавливаем задержку при неудаче.
											}	while		(!result && sumtry>0);						//	Повторяем запись если она завершилась неудачей, но не более sumtry попыток.
										}else{															//
											data[0] = 1;												//	Устанавливаем статусный флаг START.
											data[0]|= ((time_on!=NOT2 && time_off==NOT2)?0:1)<<1;		//	Определяем статусный флаг BLINK: если светодиод включается на указанное время (длительность указана, а пауза нет), то сбрасываем флаг, иначе устанавливаем.
											data[1] = uint8_t( pwm_r								);	//	Определяем коэффициент заполнения ШИМ для канала красного цвета.
											data[2] = uint8_t( pwm_g								);	//	Определяем коэффициент заполнения ШИМ для канала зелёного цвета.
											data[3] = uint8_t( pwm_b								);	//	Определяем коэффициент заполнения ШИМ для канала синего   цвета.
											data[4] = uint8_t((time_on ==NOT2)? 1:(time_on /100)	);	//	Определяем время длительности свечения.
											data[5] = uint8_t((time_off==NOT2)? 0:(time_off/100)	);	//	Определяем время паузы между свечением.
											data[6] = uint8_t((sum     ==NOT2)? 0: sum          	);	//	Определяем количество миганий.
											do{	result = objI2C.writeBytes( i1, REG_DATA, data, 7);		//	Записываем 7 элементов массива data в модуль с адресом i1, начиная с регистра REG_DATA.
												sumtry	--;	if(!result){delay(1);}						//	Уменьшаем количество попыток записи и устанавливаем задержку при неудаче.
											}	while		(!result && sumtry>0);						//	Повторяем запись если она завершилась неудачей, но не более sumtry попыток.
										}																//
									break;																//
								//	Действие № 2 - установить частоту ШИМ:								//
									case 2:																//
										do{	result = objI2C.writeByte( i1, REG_WRITE, pwm );			//	Записываем частоту ШИМ в регистр REG_WRITE модуля с адресом i1.
											sumtry	--;	if(!result){delay(1);}							//	Уменьшаем количество попыток записи и устанавливаем задержку при неудаче.
										}	while		(!result && sumtry>0);							//	Повторяем запись если она завершилась неудачей, но не более sumtry попыток.
									break;																//
								}																		//
								return result;															//
		}																								//
																										//
//		Получаем значение переменных:																	//
		void	setVar			(int i0=NOT2, int i1=NOT2	){											//
								bool f = bool(func);													//	Устанавливаем флаг f если сейчас выполняется цветовая функция
								switch(i0){																//
									case 0: func		= i1;		break;								//	Получаем номер цветовой функции, которую требуется выполнить:	0...255   =  0...255 функция
									case 1: pwm_r		= i1;		break;								//	Получаем коэффициент заполнения ШИМ для канала красного цвета:	0...255   =  0...100 %
									case 2: pwm_g		= i1;		break;								//	Получаем коэффициент заполнения ШИМ для канала зелёного цвета:	0...255   =  0...100 %
									case 3: pwm_b		= i1;		break;								//	Получаем коэффициент заполнения ШИМ для канала синего   цвета:	0...255   =  0...100 %
									case 4: time_on		= i1;		break;								//	Получаем время длительности свечения:							0...25500 =  0,0...25,5 сек.
									case 5: time_off	= i1;		break;								//	Получаем время паузы между свечением:							0...25500 =  0,0...25,5 сек.
									case 6: sum			= i1;		break;								//	Получаем количество миганий.									0...255   =  0...255 раз.
									case 7: pwm			= i1;		break;								//	Получаем значение частоты ШИМ для всех каналов цветов:			0...255   =  0...255 Гц.
								}																		//
								if(f){ if(func==0){	func_end = true; }}									//	Если цветовая функция выполнялась, а теперь нет, то устанавливаем флаг func_end.
		}																								//
																										//
	private:																							//
	/**	Внутренние переменные **/																		//
		int		pwm;																					//	Объявляем переменную для хранения частоты ШИМ для всех каналов цветов:						0...255  =  0...255 Гц.
		int		pwm_r;																					//	Объявляем переменную для хранения коэффициента заполнения ШИМ для канала красного цвета:	0...255  =  0...100 %
		int		pwm_g;																					//	Объявляем переменную для хранения коэффициента заполнения ШИМ для канала зелёного цвета:	0...255  =  0...100 %
		int		pwm_b;																					//	Объявляем переменную для хранения коэффициента заполнения ШИМ для канала синего   цвета:	0...255  =  0...100 %
		int		time_on;																				//	Объявляем переменную для хранения времени длительности свечения:							0...255  =  0,0...25,5 сек.
		int		time_off;																				//	Объявляем переменную для хранения времени паузы между свечением:							0...255  =  0,0...25,5 сек.
		int		sum;																					//	Объявляем переменную для хранения количества миганий:										0...255  =  0...255 раз.
		int		func;																					//	Объявляем переменную для хранения номера выполняемой цветовой функции:						0...255  =  0...255 функция.
		bool	func_end=1;																				//	Определяем флаг указывающий на необходимость завершения выполнения цветовой функции.
};																										//
																										//
long RGB(uint8_t colorR, uint8_t colorG, uint8_t colorB){												//
	return (long(colorR)<<16)|(long(colorG)<<8)|long(colorB);											//
}																										//
																										//
long RGB(uint8_t num){																					//
	return 0x7F000000L + num;																			//
}																										//
																										//
#endif																									//

/* =======================================================================================================================================================================================================

Действия функций библиотеки:

off();                                 - отключить                    BLINK=X START=0 TIME_ON=X TIME_OFF=X START_BLINK_SUM=0
on();                                  - включить бел. цвет постоянно BLINK=1 START=1 TIME_ON>0 TIME_OFF=0 START_BLINK_SUM=0
on(RGB);                               - включить цвет постоянно      BLINK=1 START=1 TIME_ON>0 TIME_OFF=0 START_BLINK_SUM=0
on(RGB,длительность);                  - включить на указанное время  BLINK=0 START=1 TIME_ON>0 TIME_OFF=0 START_BLINK_SUM=0
on(RGB,длительность,пауза);            - постоянно мигать             BLINK=1 START=1 TIME_ON>0 TIME_OFF>0 START_BLINK_SUM=0
on(RGB,длительность,пауза,количество); - помигать указанное кол. раз  BLINK=X START=X TIME_ON>0 TIME_OFF>0 START_BLINK_SUM>0
frequency(частота);                    - установить новую частоту     FREQUENCY=частота

Назначение дополнительных функций работы светодиода:

FUNCTIONS = 0 - обычный режим работы светодиода
FUNCTIONS = 1 - режим плавного перелива цветов. Время полного цикла перелива равно 256 * значение регистра 0x14 в миллисекундах.
FUNCTIONS = 2 - режим смены цветов радуги. Время полного цикла смены цветов  равно 256 * значение регистра 0x14 в миллисекундах.
FUNCTIONS = 3 - режим шарапнель из случайных цветов. Время между сменой цвета равно значение регистра 0x14 * значение регистра 0x15 в миллисекундах.

Таблица регистров модуля:

                   ╔══════════════╤══════════════╤══════════════╤══════════════╤══════════════╤══════════════╤══════════════╤══════════════╤═════════════════════════════════════════════════════════════╗
                   ║       7      │       6      │       5      │       4      │       3      │       2      │       1      │       0      │                                                             ║
                   ╠══════════════╪══════════════╪══════════════╪══════════════╪══════════════╪══════════════╪══════════════╪══════════════╪═════════════════════════════════════════════════════════════╣
0x00 REG_FLAGS_0   ║  FLG_RESET   │FLG_SELF_TEST │       -      │       -      │       -      │       -      │GET_PIN_ADDRES│GET_PIN_OUTPUT│ Служебные флаги для чтения.                                 ║
0x01 REG_BITS_0    ║  SET_RESET   │SET_SELF_TEST │       -      │       -      │       -      │       -      │       -      │SET_PIN_OUTPUT│ Служебные флаги для записи.                                 ║
0x02 REG_FLAGS_1   ║       -      │       -      │       -      │       -      │       -      │       -      │       -      │       -      │ Служебные флаги для чтения.                                 ║
0x03 REG_BITS_1    ║       -      │       -      │       -      │       -      │       -      │       -      │       -      │       -      │ Служебные флаги для записи.                                 ║
                   ╟──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┼─────────────────────────────────────────────────────────────╢
0x04 REG_MODEL   █ ║                                                             MODEL  [7-0] = 0x02 - светодиод RGB                       │ Тип датчика                                                 ║
0x05 REG_VERSION   ║                                                             VERSION[7-0] = 0x00                                       │ Версия прошивки                                             ║
0x06 REG_ADDRESS   ║                                                             ADDRESS[6-0] = 0x09                        │ IF_PIN_ADDRES│ Текущий адрес на шине                                       ║
0x07 REG_CHIP_ID   ║                                                             CHIP_ID[7-0] = 0xC3                                       │ ID линейки чипов                                            ║
                   ╟───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┼─────────────────────────────────────────────────────────────╢
0x08 REG_WRITE   █ ║                                                             FREQUENCY[7-0] = 0x64 = 100 Гц                            │ Частота ШИМ в Гц                                            ║
0x09 REG_WRITE+1   ║                                                             WRITE_1[7-0]                                              │ Зарезервирован                                              ║
0x0A REG_WRITE+2   ║                                                             WRITE_2[7-0]                                              │ Зарезервирован                                              ║
0x0B REG_WRITE+3   ║                                                             WRITE_3[7-0]                                              │ Зарезервирован                                              ║
0x0C REG_WRITE+4   ║                                                             WRITE_4[7-0]                                              │ Зарезервирован                                              ║
0x0D REG_WRITE+5   ║                                                             WRITE_5[7-0]                                              │ Зарезервирован                                              ║
0x0E REG_WRITE+6   ║                                                             WRITE_6[7-0]                                              │ Зарезервирован                                              ║
0x0F REG_WRITE+7   ║                                                             WRITE_7[7-0]                                              │ Зарезервирован                                              ║
                   ╟──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────┼─────────────────────────────────────────────────────────────╢
0x10 REG_DATA    █ ║       -      │       -      │       -      │       -      │       -      │       -      │    BLINK     │    START     │ Статусные флаги                                             ║
                 █ ╟──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┼─────────────────────────────────────────────────────────────╢
0x11 REG_DATA+1  █ ║                                                             RED[7-0]                                                  │ Значение ШИМ для канала красного цвета.                     ║
0x12 REG_DATA+2  █ ║                                                             GREEN[7-0]                                                │ Значение ШИМ для канала зелёного цвета.                     ║
0x13 REG_DATA+3  █ ║                                                             BLUE[7-0]                                                 │ Значение ШИМ для канала синего цвета.                       ║
0x14 REG_DATA+4  █ ║                                                             TIME_ON[7-0]                                              │ Время в течении которого ШИМ должен быть установлен.        ║
0x15 REG_DATA+5  █ ║                                                             TIME_OFF[7-0]                                             │ Время в течении которого нужно отключить все каналы цвета.  ║
0x16 REG_DATA+6  █ ║                                                             START_BLINK_SUM[7-0]                                      │ Количество миганий (сколько раз выполнить цикл TIME_ON_OFF).║
0x17 REG_DATA+7  █ ║                                                             FUNCTIONS[7-0]                                            │ Дополнительные функции работы светодиода.                   ║
                   ╚═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╧═════════════════════════════════════════════════════════════╝

FREQUENCY        - Частота ШИМ в Гц.
BLINK            - Флаг указывает установить флаг START после его сброса.
START            - Флаг указывает установить ШИМ и начать отсчет времени TIME_ON + TIME_OFF после чего сбросить флаг START.
                   Установка бита START - приведёт к установке ШИМ и началу отсчёта времени TIME_ON + TIME_OFF.
                   Сброс     бита START - приведёт прекращению отсчёта времени TIME_ON + TIME_OFF и отключению ШИМ вне зависимости от состояния флага BLINK.
RED              - Значение ШИМ для канала красного цвета.
GREEN            - Значение ШИМ для канала зелёного цвета.
BLUE             - Значение ШИМ для канала синего   цвета.
TIME_ON          - Время в течении которого ШИМ должен быть установлен (время в десятых долях секунд: от 0.0 до 25.5 сек.).
TIME_OFF         - Время в течении которого нужно отключить все каналы цвета (время в десятых долях секунд: от 0.0 до 25.5 сек.).
START_BLINK_SUM  - Запись ненулевого значения установит флаг START и сбросит флаг BLINK, но модуль будет вести себя так, как будто флаг BLINK установлен.
                   С каждым циклом TIME_ON + TIME_OFF значение регистра START_BLINK_SUM будет уменьшаться, пока не достигнет 0, тогда флаг START будет сброшен.
FUNCTIONS        - Дополнительные функции работы светодиода. Если установлено значение больше 0, то флаги регистра 0x10 игнорируются.
                   Сброс в 0 приводит к сбросу флага START, значит для перехода в обычный режим работы, нужно сначала сбросить FUNCTIONS, подождать 3-4 мс, а уже потом установить флаг START.

*/