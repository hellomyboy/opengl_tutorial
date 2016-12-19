#include "IOManager.h"

#include <fstream>
#include <string>


namespace Engine {

	bool IOManager::readFileToBuffer(const std::string& filePath, std::vector<unsigned char>& buffer)
	{
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail()) {
			perror(filePath.c_str());
			return false;
		}

		//seek to the end
		file.seekg(0, std::ios::end);
		int fileSize = file.tellg();
		file.seekg(0, std::ios::beg);
		fileSize -= file.tellg();

		//fileSize += 1;

		buffer.resize(fileSize);
		file.read((char *)&(buffer[0]), fileSize);

		//char s = 0;
		//buffer.push_back(s);

		file.close();
		return true;
	}

}
