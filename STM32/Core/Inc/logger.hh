#ifndef INC_LOGGER_HH_
#define INC_LOGGER_HH_

#include <cstring>
#include <string>
#include <cstdio>
#include <list>
#include <usart.h>

class Logger{
	UART_HandleTypeDef* huart;
	char data[50];
	uint64_t lastLine;
	std::list<std::string> SDData;
public:
	Logger(UART_HandleTypeDef* uart): huart(uart) {} ;
	std::string TakeCommand(uint8_t*);
	void Save(char*);
	std::string Send();
};



#endif /* INC_LOGGER_HH_ */
