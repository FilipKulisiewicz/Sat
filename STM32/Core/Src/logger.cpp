#include <logger.hh>

std::string Logger::TakeCommand(uint8_t* dataIn){
	if(strncmp((char*)dataIn, "LGDT", 4) == 0)
		return Send();
	else{
		std::sprintf(data, "%lli:%s", lastLine, dataIn);
		Save(data);
		return "0";
	}
}
void Logger::Save(char* inputToSave){
	SDData.push_back(inputToSave);
}

std::string Logger::Send(){
	if(SDData.size() > lastLine)
		return "0";
	else
		return "0";
}
