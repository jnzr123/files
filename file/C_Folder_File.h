//功能：		处理文件夹，文件的类。

#pragma once
#include <string>
#include <vector>

#ifndef _FilesInFolder_
#define _FilesInFolder_
struct FilesInFolder
{
	std::string strFileName;
	std::string strFilePath;
};
#endif

class C_Folder_File
{
private:

/*-------------------------------------------------------------------------------------
功能：					返回文件夹中的子文件夹
input:
	strFolderPath:		文件路径
	isRecursion:		是否递归获取子文件夹
output
	vt_strFolder_o：	子文件夹路径
-------------------------------------------------------------------------------------*/
	void getFoldersFormDisk(std::string strFolderPath, bool isRecursion, std::vector<std::string>& vt_strFolder_o);

/*-------------------------------------------------------------------------------------
功能：					获取分隔符间的字符串
input:
	str:				字符串
	delimiters:			分隔符
output
	返回:				分隔符之间的字符串
-------------------------------------------------------------------------------------*/
	std::vector<std::string> splitString(std::string str, std::string delimiters);

public:
	~C_Folder_File(void){};
	C_Folder_File(){};
	
/*-------------------------------------------------------------------------------------
功能：					遍历文件夹中所需要的文件
input:
	strFolderPath:		文件夹路径
	strFileFilter:		文件类型
	isRecursion:		是否递归遍历子文件夹
output
	vt_str_o:			文件完整路径
-------------------------------------------------------------------------------------*/
	void getFilesFromFolder(std::string strFolderPath, std::string strFileFilter, bool isRecursion, std::vector<std::string>& vt_str_o);

/*-------------------------------------------------------------------------------------
功能：					返回文件完整路径中的文件名
input:
	filePath:			文件路径
	isNeedFilter:		是否需要文件后缀
output
	返回:				文件名
-------------------------------------------------------------------------------------*/
	std::string getFileNameFromPath(std::string filePath, bool isNeedFilter);

/*-------------------------------------------------------------------------------------
功能：					返回文件所在的文件夹名称
input:
	filePath:			文件路径
output
	返回:				文件所在的文件夹名称
-------------------------------------------------------------------------------------*/
	std::string getFolderNameFromFilePath(std::string filePath);

/*-------------------------------------------------------------------------------------
功能：					返回文件夹中的子文件夹
input:
	strFolderPath:		文件路径
	isRecursion:		是否递归获取子文件夹
output
	vt_strFolder_o：	子文件夹路径
	返回:				最大子文件夹层数
-------------------------------------------------------------------------------------*/
	int getFolders(std::string strFolderPath, bool isRecursion, std::vector<std::string>& vt_strFolder_o);

/*-------------------------------------------------------------------------------------
功能：					判断文件是否存在
input:
	filePath:			文件路径
output
	返回:				文件是否存在
-------------------------------------------------------------------------------------*/	
	bool isFileExist(std::string filePath);

/*-------------------------------------------------------------------------------------
功能：					判断文件夹是否存在，并且可以创建新文件夹
input:
	folderPath:			文件夹路径
	isCreate：			如果不存在，是否创建空文件夹
output
	返回:				文件夹是否存在
-------------------------------------------------------------------------------------*/	
	bool isFolderExist(std::string folderPath, bool isCreate);

/*-------------------------------------------------------------------------------------
功能：					复制文件
input:
	src:				源文件路径
	dst：				目的文件路径
output
	返回:				运行状态，0为正确，否则异常。
-------------------------------------------------------------------------------------*/	
	int CopyFile(std::string src, std::string dst);

/*-------------------------------------------------------------------------------------
功能：					获取一批文件夹路径最大的层数
input:
	vt_strFolder_o：	一批文件夹路径
output
	返回:				最大的层数
-------------------------------------------------------------------------------------*/	
	int getMaxFolderLevel(std::vector<std::string>& vt_strFolders);
};
