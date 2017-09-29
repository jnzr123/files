#include <stdio.h>
#include <vector>
#include <string>
//将txt的内容逐行读入vector
int ReadTxt(const char* dir, std::vector<std::string>& outfile);
int C_ReadTxt(const char* filename, std::vector<std::string>& outfile);
int CPlus_ReadTxt(const char* filename, std::vector<std::string>& outfile);