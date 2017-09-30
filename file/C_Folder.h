//批量处理文件夹，文件的类。

#pragma once
#include <windows.h>
#include <string>
#include <vector>

using namespace std;

#ifndef _FilesInFolder_
#define _FilesInFolder_
struct FilesInFolder
{
	string strFileName;
	string strFilePath;
};
#endif

class __declspec(dllexport) C_Folder
{
private:
	//获取文件夹中指定的文件信息，递归
	vector<FilesInFolder> scanFolder(string strFolderPath, string strFilter, vector<FilesInFolder> vt_FIF ,bool isRecursion);
	void scanFolder_faster(string strFolderPath, string strFilter, vector<FilesInFolder>& vt_FIF ,bool isRecursion);
	vector<string> scanFolder(string strFolderPath, vector<string> vt_folderName, bool isRecursion);
	//字符串比较
	bool compareFilter(string str1, string str2);
public:
	~C_Folder(void){};
	C_Folder(){};
	
	//获取文件夹中指定的文件信息，返回一个自定义结构体，注意，必须使用deleteFilesInFolder释放返回值的内存
	vector<FilesInFolder>* getFileFromFolder(string* strFolderPath, string* strFilter, bool isRecursion);
	void getFileFromFolder_faster(string* strFolderPath, string* strFilter, bool isRecursion, vector<FilesInFolder>& vt_FIF);
	//释放上面函数分配的结构体内存
	void deleteFilesInFolder(vector<FilesInFolder>* vt_FIF);	
	//获取文件夹中的子文件夹
	vector<string> getFolder(string strFolderPath, bool isRecursion);
	//从文件路径中获取文件名 C:/f1/f2/3.bmp -> 3.bmp
	string getFileNameFromPath(string filePath, bool isNeedFormat);
	//从文件路径中获取文件所在的文件夹名 C:/f1/f2/3.bmp -> f2
	string getFolderNameFromPath(string filePath);
	//判断文件是否存在
	bool isFileExist(string path);
	//判断文件夹是否存在
	bool isFoldeExist(char* folderPath, bool isCreate);
	//创建文件夹
	int creatFolder(string str_src, string str_dst, bool isRecursion);
	//复制文件夹
	void copyFolderTo(string source, string dis, string searchChars);
	//{   
	//	vector<FilesInFolder>* vt_FIF = getFileFromFolder()

	//	/*		struct _finddata_t   ffblk;  
	//	char path[256], SourcePath[256], DisPath[256];  
	//	sprintf(path,"%sq_*",source);  
	//	long done = _findfirst(path,&ffblk);  
	//	int find=0;  
	//	while (find==0)    
	//	{    
	//	if(strcmp(ffblk.name, "q_"))
	//	{
	//	sprintf(SourcePath, "%s\%s",source, ffblk.name);
	//	sprintf(DisPath, "%s\%s",dis, ffblk.name);
	//	CopyFile(SourcePath, DisPath, bcover);
	//	}
	//	find=_findnext(done,&ffblk);    
	//	}  
	//	_findclose(done); */ 
	//}
};
