																										//
#ifndef iarduino_Metro_2RM_h																			//	Функции работы с электромеханическим реле.
#define iarduino_Metro_2RM_h																			//
																										//
class iarduino_Metro_2RM: public iarduino_Metro_BASE{													//	Определяем производный класс iarduino_Metro_2RM.
	public:																								//
	/**	функции данного производного класса iarduino_Metro_2RM		**/									//
	/**	дублирую функции полиморфного класса iarduino_Metro_BASE	**/									//
																										//
//		Функции не используемые в данном модуле:														//
		bool	begin			(int i0=NOT2, int i1=NOT2	){return 0;}								//	Инициализация модуля.
		int		test			(int i0=NOT2, int i1=NOT2	){return 0;}								//	Самотестирование модуля.
		long	getVar			(int i0=NOT2				){return 0;}								//	Возврат значений переменных.
																										//
//		Выполняем действия:																				//
		bool	action			(int i0=NOT2, int i1=NOT2	){											//	
								uint8_t data[1];														//	Объявляем массив для хранения данных пакетно записываемых в модуль.
								bool    result  = false;												//	Определяем флаг результата возвращаемый функцией action.
								uint8_t sumtry  = 10;													//	Количество попыток чтения/записи.
								switch(i0){																//
								//	Действие № 0 - прочитать состояние реле:							//
									case 0:																//
										data[0] = 0;													//	Готовим байт для получения данных.
										do{	result	 =	iMetroI2C.readBytes( i1, REG_DATA+2, data, 1);	//	Читаем 1 байт из модуля с адресом i1, начиная с регистра REG_DATA+2 в массив data.
											sumtry	--;	if(!result){delay(1);}							//	Уменьшаем количество попыток чтения и устанавливаем задержку при неудаче.
										}	while		(!result && sumtry>0);							//	Повторяем чтение если оно завершилось неудачей, но не более sumtry попыток.
										if(!result){return false;} result = false;						//	Если чтение неудачно, то возвращаем false.
										return (data[0] & rel_num)? true:false;							//
									break;																//
								//	Действие № 1 - отключить реле:										//
									case 1:																//
										data[0] = rel_num;												//	Определяем состояние битов WRITE_LOW_K2, WRITE_LOW_K1.
										do{	result = iMetroI2C.writeBytes( i1, REG_DATA+3, data, 1);	//	Записываем 1 элемент массива data в модуль с адресом i1, начиная с регистра REG_DATA+3.
											sumtry	--;	if(!result){delay(1);}							//	Уменьшаем количество попыток записи и устанавливаем задержку при неудаче.
										}	while		(!result && sumtry>0);							//	Повторяем запись если она завершилась неудачей, но не более sumtry попыток.
									break;																//
								//	Действие № 2 - включить реле:										//
									case 2:																//
										data[0] = (rel_num<<4);											//	Определяем состояние битов WRITE_HIGH_K2, WRITE_HIGH_K1.
										do{	result = iMetroI2C.writeBytes( i1, REG_DATA+3, data, 1);	//	Записываем 1 элемент массива data в модуль с адресом i1, начиная с регистра REG_DATA+3.
											sumtry	--;	if(!result){delay(1);}							//	Уменьшаем количество попыток записи и устанавливаем задержку при неудаче.
										}	while		(!result && sumtry>0);							//	Повторяем запись если она завершилась неудачей, но не более sumtry попыток.
									break;																//
								//	Действие № 3 - установить время сторожевого таймера:				//
									case 3:																//
										data[0] = rel_tim;												//	Определяем время сторожевого таймера.
										do{	result = iMetroI2C.writeBytes( i1, REG_DATA+0x20, data, 1);	//	Записываем 1 элемент массива data в модуль с адресом i1, начиная с регистра REG_DATA+0x20.
											sumtry	--;	if(!result){delay(1);}							//	Уменьшаем количество попыток записи и устанавливаем задержку при неудаче.
										}	while		(!result && sumtry>0);							//	Повторяем запись если она завершилась неудачей, но не более sumtry попыток.
									break;																//
								}																		//
								return result;															//
		}																								//
																										//
//		Получаем значение переменных:																	//
		void	setVar			(int i0=NOT2, int i1=NOT2	){											//
								switch(i0){																//
								//	Получен номер реле:													//
									case 0:							rel_num=0b00000000;					//	Сбрасываем флаги управления всеми реле.
										if( i1==NOT2			){	rel_num=0b00000011; }				//	Определяем флаг  управления всеми реле.
										if( i1==1    			){	rel_num=0b00000001; }				//	Определяем флаг  управления   1   реле.
										if( i1==2    			){	rel_num=0b00000010; }				//	Определяем флаг  управления   2   реле.
									break;																//
								//	Получено время до отключения реле:									//
									case 1:							rel_tim=255;						//	Устанавливаем значение отключающее сторожевой таймер реле.
										if( (i1>0) && (i1<255)	){	rel_tim=i1; }						//	Определяем время для сторожевого таймера реле.
									break;																//
								}																		//
		}																								//
																										//
	private:																							//
	/**	Внутренние переменные **/																		//
		int		rel_num;																				//	Объявляем переменную для хранения номера включаемого/отключаемого реле.
		int		rel_tim;																				//	Объявляем переменную для хранения номера включаемого/отключаемого реле.
};																										//
																										//
#endif																									//

/* =======================================================================================================================================================================================================

Действия функций библиотеки:

off  ( [номер реле] );  - отключить реле. Если номер не указан, то отключатся  все реле.
on   ( [номер реле] );  - включить  реле. Если номер не указан, то включатся   все реле.
read ( [номер реле] );  - прочитать реле. Если номер не указан, то прочитаются все реле.
set  ( [секунды]    );  - установить время сторожевого таймера. Если время не указано, то сторожевой таймер отключается.

Таблица регистров модуля:

                   ╔══════════════╤══════════════╤══════════════╤══════════════╤══════════════╤══════════════╤══════════════╤══════════════╤═════════════════════════════════════════════════════════════╗
                   ║       7      │       6      │       5      │       4      │       3      │       2      │       1      │       0      │                                                             ║
                   ╠══════════════╪══════════════╪══════════════╪══════════════╪══════════════╪══════════════╪══════════════╪══════════════╪═════════════════════════════════════════════════════════════╣
0x00 REG_FLAGS_0   ║  FLG_RESET   │FLG_SELF_TEST │       -      │       -      │       -      │       -      │GET_PIN_ADDRES│GET_PIN_OUTPUT│ Служебные флаги для чтения.                                 ║
0x01 REG_BITS_0    ║  SET_RESET   │SET_SELF_TEST │       -      │       -      │       -      │       -      │       -      │SET_PIN_OUTPUT│ Служебные флаги для записи.                                 ║
0x02 REG_FLAGS_1   ║       -      │       -      │       -      │       -      │       -      │       -      │       -      │       -      │ Служебные флаги для чтения.                                 ║
0x03 REG_BITS_1    ║       -      │       -      │       -      │       -      │       -      │       -      │       -      │       -      │ Служебные флаги для записи.                                 ║
                   ╟──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┼─────────────────────────────────────────────────────────────╢
0x04 REG_MODEL   █ ║                                                             MODEL  [7-0] = 0x0A - реле электромеханическое 2 канала   │ Тип датчика                                                 ║
0x05 REG_VERSION   ║                                                             VERSION[7-0] = 0x00                                       │ Версия прошивки                                             ║
0x06 REG_ADDRESS   ║                                                             ADDRESS[6-0] = 0x09                        │ IF_PIN_ADDRES│ Текущий адрес на шине                                       ║
0x07 REG_CHIP_ID   ║                                                             CHIP_ID[7-0] = 0xC3                                       │ ID линейки чипов                                            ║
                   ╟───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┼─────────────────────────────────────────────────────────────╢
0x08 REG_WRITE     ║                                                             WRITE_0[7-0]                                              │ Зарезервирован                                              ║
0x09 REG_WRITE+1   ║                                                             WRITE_1[7-0]                                              │ Зарезервирован                                              ║
0x0A REG_WRITE+2   ║                                                             WRITE_2[7-0]                                              │ Зарезервирован                                              ║
0x0B REG_WRITE+3   ║                                                             WRITE_3[7-0]                                              │ Зарезервирован                                              ║
0x0C REG_WRITE+4   ║                                                             WRITE_4[7-0]                                              │ Зарезервирован                                              ║
0x0D REG_WRITE+5   ║                                                             WRITE_5[7-0]                                              │ Зарезервирован                                              ║
0x0E REG_WRITE+6   ║                                                             WRITE_6[7-0]                                              │ Зарезервирован                                              ║
0x0F REG_WRITE+7   ║                                                             WRITE_7[7-0]                                              │ Зарезервирован                                              ║
                   ╟───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┼─────────────────────────────────────────────────────────────╢
0x10 REG_DATA    █ ║                                                             DATA_0[7-0]                                               │ Зарезервирован                                              ║
0x11 REG_DATA+1  █ ║                                                             DATA_0[7-0]                                               │ Зарезервирован                                              ║
                 █ ╟──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────┼─────────────────────────────────────────────────────────────╢
0x12 REG_DATA+2  █ ║       -      │       -      │       -      │       -      │       -      │       -      │  DIGITAL_K2  │  DIGITAL_K1  │ Чтение/запись логических уровней для всех каналов.          ║
0x13 REG_DATA+3  █ ║       -      │       -      │ WRITE_HIGH_K2│ WRITE_HIGH_K1│       -      │       -      │ WRITE_LOW_K2 │ WRITE_LOW_K1 │ Установить логический «0»/«1»: 0-игнорировать; 1-установить.║
                 █ ╟──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┼─────────────────────────────────────────────────────────────╢
0x14 REG_DATA+4  █ ║                                                                                                                       │ Зарезервирован                                              ║
...              █ ║                                                                                                                       │ Зарезервирован                                              ║
0x2F REG_DATA+1F █ ║                                                                                                                       │ Зарезервирован                                              ║
                 █ ╟───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┼─────────────────────────────────────────────────────────────╢
0x30 REG_DATA+20 █ ║                                                             REG_WDT[7-0]         = 0xFF-отключён. 01...254 сек.       │ Сторожевой таймер с обратным отсчётом      (0-перезагрузка) ║ (в секундах)
                   ╚═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╧═════════════════════════════════════════════════════════════╝

DIGITAL_K1       - Установка бита включает 1 реле, а сброс - отключает.
DIGITAL_K2       - Установка бита включает 2 реле, а сброс - отключает.
WRITE_H1         - Установка бита приводит к установке бита DIGITAL_K1, что приводит к включению  1 реле.
WRITE_H2         - Установка бита приводит к установке бита DIGITAL_K2, что приводит к включению  2 реле.
WRITE_L1         - Установка бита приводит к сбросу    бита DIGITAL_K1, что приводит к отключению 1 реле.
WRITE_L2         - Установка бита приводит к сбросу    бита DIGITAL_K2, что приводит к отключению 2 реле.

*/