#ifndef INC_LOGGER_HH_
#define INC_LOGGER_HH_

#include <cstring>
#include <string>
#include <cstdio>
#include <list>
#include <vector>
#include <usart.h>

class Logger{
	UART_HandleTypeDef* huartLog;
	bool confirmation = 1;
	const std::size_t expectedMinimumLogsDiffrence = 5;

	char* dataToSave;
	std::size_t newlySendedData, previouslySendedData, fullySendedData;
	std::vector<std::string> SDData;
public:
	Logger(UART_HandleTypeDef* _huart): huartLog(_huart) {}
	void CommandManager(uint8_t*);
	void DataManager();
	void Save(std::string);
	void Send(std::string);
};

#endif /* INC_LOGGER_HH_ */
