#include <logger.hh>

void Logger::CommandManager(uint8_t* dataIn){
	if(std::strncmp(reinterpret_cast<char*>(dataIn), "LGDT", 4) == 0)
		DataManager();
	else if (std::strncmp(reinterpret_cast<char*>(dataIn), "LL", 2) == 0){
		std::sprintf(dataToSave, "%u:%s", SDData.size(), dataIn);
		Save(dataToSave);
	}
}

void Logger::DataManager(){
	if(SDData.size() - 1 > previouslySendedData + expectedMinimumLogsDiffrence){ // if newCommunicationGap -> send few last logs
		for(uint8_t i = 0; i < 5 ; ++i)
			Send(SDData[SDData.size() - 1 - i]);
		if(confirmation){
			previouslySendedData = newlySendedData;
			newlySendedData = SDData.size() - 1;
		}
	}
	else if(SDData.size() - 1 > newlySendedData){ 	//if newLogDuringCommunication -> send it
		Send(SDData[newlySendedData]);
		if(confirmation){
			previouslySendedData = newlySendedData;
			newlySendedData = SDData.size() - 1;
		}
	}
	else if(newlySendedData > fullySendedData){		//if not busy -> send whole data
		Send(SDData[fullySendedData]);
		if(confirmation)
			++fullySendedData;
	}
}

void Logger::Save(std::string inputToSave){
	SDData.push_back(inputToSave); //there should be SDSave()
}

void Logger::Send(std::string inputToSend){
	HAL_UART_Transmit_DMA(huartLog, reinterpret_cast<uint8_t*>(&inputToSend[0]), 50);
}
