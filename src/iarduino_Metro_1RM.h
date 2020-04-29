																										//
#ifndef iarduino_Metro_1RM_h																			//	Функции работы с электромеханическим реле.
#define iarduino_Metro_1RM_h																			//
																										//
class iarduino_Metro_1RM: public iarduino_Metro_BASE{													//	Определяем производный класс iarduino_Metro_1RM.
	public:																								//
	/**	функции данного производного класса iarduino_Metro_1RM		**/									//
	/**	дублирую функции полиморфного класса iarduino_Metro_BASE	**/									//
																										//
//		Функции не используемые в данном модуле:														//
		bool	begin			(int i0=NOT2, int i1=NOT2	){return 0;}								//	Инициализация модуля.
		int		test			(int i0=NOT2, int i1=NOT2	){return 0;}								//	Самотестирование модуля.
		long	getVar			(int i0=NOT2				){return 0;}								//	Возврат значений переменных.
		void	setVar			(int i0=NOT2, int i1=NOT2	){        ;}								//	Получение значений переменных.
																										//
//		Выполняем действия:																				//
		bool	action			(int i0=NOT2, int i1=NOT2	){											//	
								uint8_t data[1];														//	Объявляем массив для хранения данных пакетно записываемых в модуль.
								bool    result  = false;												//	Определяем флаг результата возвращаемый функцией action.
								uint8_t sumtry  = 10;													//	Количество попыток чтения/записи.
								switch(i0){																//
								//	Действие № 0 - отключить светодиод:									//
									case 0:																//
										data[0] = 0;													//	Определяем состояние бита DIGITAL_K1 как 0.
										do{	result = objI2C.writeBytes( i1, REG_DATA+2, data, 1);		//	Записываем 1 элемент массива data в модуль с адресом i1, начиная с регистра REG_DATA+2.
											sumtry	--;	if(!result){delay(1);}							//	Уменьшаем количество попыток записи и устанавливаем задержку при неудаче.
										}	while		(!result && sumtry>0);							//	Повторяем запись если она завершилась неудачей, но не более sumtry попыток.
									break;																//
								//	Действие № 1 - включить светодиод:									//
									case 1:																//
										data[0] = 1;													//	Определяем состояние бита DIGITAL_K1 как 1.
										do{	result = objI2C.writeBytes( i1, REG_DATA+2, data, 1);		//	Записываем 1 элемент массива data в модуль с адресом i1, начиная с регистра REG_DATA+2.
											sumtry	--;	if(!result){delay(1);}							//	Уменьшаем количество попыток записи и устанавливаем задержку при неудаче.
										}	while		(!result && sumtry>0);							//	Повторяем запись если она завершилась неудачей, но не более sumtry попыток.
									break;																//
								}																		//
								return result;															//
		}																								//
																										//
	private:																							//
};																										//
																										//
#endif																									//

/* =======================================================================================================================================================================================================

Действия функций библиотеки:

off();             - отключить.
on();              - включить.

Таблица регистров модуля:

                   ╔══════════════╤══════════════╤══════════════╤══════════════╤══════════════╤══════════════╤══════════════╤══════════════╤═════════════════════════════════════════════════════════════╗
                   ║       7      │       6      │       5      │       4      │       3      │       2      │       1      │       0      │                                                             ║
                   ╠══════════════╪══════════════╪══════════════╪══════════════╪══════════════╪══════════════╪══════════════╪══════════════╪═════════════════════════════════════════════════════════════╣
0x00 REG_FLAGS_0   ║  FLG_RESET   │FLG_SELF_TEST │       -      │       -      │       -      │       -      │GET_PIN_ADDRES│GET_PIN_OUTPUT│ Служебные флаги для чтения.                                 ║
0x01 REG_BITS_0    ║  SET_RESET   │SET_SELF_TEST │       -      │       -      │       -      │       -      │       -      │SET_PIN_OUTPUT│ Служебные флаги для записи.                                 ║
0x02 REG_FLAGS_1   ║       -      │       -      │       -      │       -      │       -      │       -      │       -      │       -      │ Служебные флаги для чтения.                                 ║
0x03 REG_BITS_1    ║       -      │       -      │       -      │       -      │       -      │       -      │       -      │       -      │ Служебные флаги для записи.                                 ║
                   ╟──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┼─────────────────────────────────────────────────────────────╢
0x04 REG_MODEL   █ ║                                                             MODEL  [7-0] = 0x15 - реле электромеханическое 1 канал    │ Тип датчика                                                 ║
0x05 REG_VERSION   ║                                                             VERSION[7-0] = 0x00                                       │ Версия прошивки                                             ║
0x06 REG_ADDRESS   ║                                                             ADDRESS[6-0] = 0x09                        │ IF_PIN_ADDRES│ Текущий адрес на шине                                       ║
0x07 REG_CHIP_ID   ║                                                             CHIP_ID[7-0] = 0xC3                                       │ ID линейки чипов                                            ║
                   ╟───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┼─────────────────────────────────────────────────────────────╢
0x08 REG_WRITE   █ ║                                                             WRITE_0[7-0]                                              │ Зарезервирован                                              ║
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
0x12 REG_DATA+2  █ ║       -      │       -      │       -      │       -      │       -      │       -      │       -      │  DIGITAL_K1  │ Чтение/запись логических уровней для всех каналов.          ║
0x13 REG_DATA+3  █ ║       -      │       -      │       -      │ WRITE_HIGH_K1│       -      │       -      │       -      │ WRITE_LOW_K1 │ Установить логический «0»/«1»: 0-игнорировать; 1-установить.║
                   ╚══════════════╧══════════════╧══════════════╧══════════════╧══════════════╧══════════════╧══════════════╧══════════════╧═════════════════════════════════════════════════════════════╝

DIGITAL_K1       - Установка бита включает реле, а сброс - отключает.
WRITE_H1         - Установка бита приводит к установке бита DIGITAL_K1, что приводит к включению реле.
WRITE_L1         - Установка бита приводит к сбросу    бита DIGITAL_K1, что приводит к отключению реле.

*/