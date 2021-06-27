#include <logger.hh>

void Logger::CommandManager(uint8_t* dataIn){
	if(std::strncmp(reinterpret_cast<char*>(dataIn), "LGDT", 4) == 0)
		DataManager();
	else if (std::strncmp((char*)(dataIn), "LL", 2) == 0){
		Save(dataIn);
	}
}

void Logger::DataManager(){
	if(SDData.size() < 7)
		return;
	if(SDData.size() - 1 > previouslySendedData + expectedMinimumLogsDiffrence){ // if newCommunicationGap -> send few last logs
		for(uint8_t i = 0; i < 5 ; ++i)
			Send(SDData[SDData.size() - 1 - i]);
		if(confirmation == 1){
			previouslySendedData = newlySendedData;
			newlySendedData = SDData.size() - 1;
		}
	}
	else if(SDData.size() - 1 > newlySendedData){ 	//if newLogDuringCommunication -> send it
		Send(SDData[newlySendedData]);
		if(confirmation == 1){
			previouslySendedData = newlySendedData;
			newlySendedData = SDData.size() - 1;
		}
	}
	else if(newlySendedData > fullySendedData){		//if not busy -> send whole data
		Send(SDData[fullySendedData]);
		if(confirmation == 1)
			++fullySendedData;
	}
}

void Logger::Save(uint8_t* inputToSave){
	char* tmp = new char[20];
	std::sprintf(tmp, "LD%u:%s", SDData.size(), &inputToSave[2]);
	SDData.push_back(tmp); //there should be SDSave()
	if(SDData.size() > 125)
		SDData.resize(100);
}

void Logger::Send(char* inputToSend){
	std::sprintf(dataToSave, "%s", inputToSend); //only debug purpose
	HAL_UART_Transmit_DMA(huartLog, (uint8_t*)(inputToSend), packetSize);
}
