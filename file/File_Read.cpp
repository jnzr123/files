#include "File_Read.h"

int ReadTxt(const char* dir, std::vector<std::string>& outfile){
	FILE *fp;
	char StrLine[100];             //每行最大读取的字符数
	fp = fopen(dir, "r");
	if (fp == NULL) //判断文件是否存在及可读
	{
		printf("error!");

	}
	while (!feof(fp))
	{
		fgets(StrLine, 100, fp);  //读取一行
		outfile.push_back(StrLine);
	}
	fclose(fp);  //关闭文件
	printf("file read finish \n");
	return 0;
}

int C_ReadTxt(const char* filename, std::vector<std::string>& outfile){
		FILE *fp;
	char StrLine[1024];             //每行最大读取的字符数
	if ((fp = fopen(filename, "r")) == NULL) //判断文件是否存在及可读
	{
		printf("error!");
		return -1;
	}

	while (!feof(fp))
	{
		fgets(StrLine, 1024, fp);  //读取一行
		printf("%s\n", StrLine); //输出
		outfile.push_back(UTF8ToGB(StrLine));
	}
	fclose(fp);
	return 0;
}

int CPlus_ReadTxt(const char* filename, std::vector<std::string>& outfile){
	std::string StrLine;             //每行最大读取的字符数
	std::fstream fp(filename, fstream::in);
	std::string buffer;
	while (!fp.eof())
	{
		fp >> buffer;
		//cout << buffer << endl;
		if (buffer.empty()){
			continue;
		}
		outfile.push_back(buffer);

	}
	fp.close();
	printf("file read finish \n");
	return 0;
}

