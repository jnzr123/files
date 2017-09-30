#pragma once
#include <vector>
#include <string>


class C_Text_v2
{
private:

public:
	~C_Text_v2(void){};
	C_Text_v2(){};

	std::vector<std::string> readTxt(std::string txtFilePath);
	std::vector<std::string> splitString(std::string in, std::string delimiters);
	void saveVtStr(std::vector<std::string> vt_str, std::string filePath);		
};
	