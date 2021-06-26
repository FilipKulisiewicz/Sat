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
	uint8_t packetSize = 20;
	const uint8_t expectedMinimumLogsDiffrence = 5;

	char dataToSave[20];
	std::size_t newlySendedData = 0, previouslySendedData = 0, fullySendedData = 0;
	std::vector<char*> SDData;
public:
	Logger(UART_HandleTypeDef* _huart): huartLog(_huart) {}
	void CommandManager(uint8_t*);
	void DataManager();
	void Save(uint8_t*);
	void Send(char*);
};

#endif /* INC_LOGGER_HH_ */
