#include "StdAfx.h"
#include "C_Folder.h"

//#define SameWithMatLab

/*-------------------------------------------------------------------------------------------------
功能：						获取文件夹中指定的文件信息，返回一个自定义结构体
strFolderPath：				文件夹路径
strFilter：					过滤器，只有后缀（比如".txt"或者"mydoc.txt"）等于strFilter的才筛选出来
isRecursion:				是否考虑子文件夹
返回：						所有满足需求的文档的路径和文档名称。注意，必须使用deleteFilesInFolder来释放返回的内存。

-------------------------------------------------------------------------------------------------*/
vector<FilesInFolder>* C_Folder::getFileFromFolder(string* strFolderPath, string* strFilter, bool isRecursion)
{
	vector<FilesInFolder>* vt_fileInfo  = new vector<FilesInFolder>[1];
	vector<FilesInFolder> vt_fileInfoR;
	*vt_fileInfo = scanFolder(*strFolderPath, *strFilter, vt_fileInfoR, isRecursion);
	return vt_fileInfo;
}

/*-------------------------------------------------------------------------------------------------
功能：						获取文件夹中指定的文件信息，返回一个自定义结构体
strFolderPath：				文件夹路径
strFilter：					过滤器，只有后缀（比如".txt"或者"mydoc.txt"）等于strFilter的才筛选出来
isRecursion:				是否考虑子文件夹
vt_FIF:						输出项所有满足需求的文档的路径和文档名称。

-------------------------------------------------------------------------------------------------*/
void C_Folder::getFileFromFolder_faster(string* strFolderPath, string* strFilter, bool isRecursion, vector<FilesInFolder>& vt_FIF)
{
	scanFolder_faster(*strFolderPath, *strFilter, vt_FIF, isRecursion);
}

/*-------------------------------------------------------------------------------------------------
功能：					删除结构体FilesInFolder所暂用的空间
vt_FIF：				需要删除的FilesInFolder内存指针

-------------------------------------------------------------------------------------------------*/
void C_Folder::deleteFilesInFolder(vector<FilesInFolder>* vt_FIF)
{	

	(*vt_FIF).clear();
	delete[] vt_FIF; 
	vt_FIF = NULL;
}

/*-------------------------------------------------------------------------------------------------
功能：						遍历文件夹，获取文件夹中的子文件夹。
strFolderPath：				需要遍历的文件夹路径
isRecursion：				是否递归获取子文件夹中的子文件夹
返回：						strFolderPath路径中的子文件夹

-------------------------------------------------------------------------------------------------*/
vector<string> C_Folder::getFolder(string strFolderPath, bool isRecursion)
{
	vector<string> vt_folder;
	vector<string> vt_folderR;
	vt_folder = scanFolder(strFolderPath, vt_folderR, isRecursion);
	return vt_folder;
}

/*-------------------------------------------------------------------------------------------------
功能：						获取文件夹中指定的文件信息，返回一个自定义结构体，有递归操作
strFolderPath：				文件夹路径
strFilter：					过滤器，只有后缀（比如".txt"或者"mydoc.txt"）等于strFilter的才筛选出来
vt_FIF：					本次获取的文件信息，递归用，下一次递归操作时，会将正确的信息放到此变量中
isRecursion:				是否递归考虑子文件夹
返回：						所有满足需求的文档的路径和文档名称

-------------------------------------------------------------------------------------------------*/
vector<FilesInFolder> C_Folder::scanFolder(string strFolderPath, string strFilter, vector<FilesInFolder> vt_FIF, bool isRecursion)
{
	vector<FilesInFolder> vt_filePath;
	WIN32_FIND_DATA FindFileData;

	//将上一次递归的有用文档放入返回的变量中
	for(int i = 0; i < vt_FIF.size(); i++)
		vt_filePath.push_back(vt_FIF[i]);

	string strAllFilePath = strFolderPath + "\\*.*";
	string nextFile = "";

	//获取文件夹中的所有文件
	HANDLE hFind = FindFirstFile(strAllFilePath.c_str(), &FindFileData);
	if(INVALID_HANDLE_VALUE == hFind) 
		return vt_filePath;

	while(TRUE)
	{
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//处理文件夹
		{		
			if(FindFileData.cFileName[0] != '.') 
			{
				nextFile = strFolderPath + "\\" +  FindFileData.cFileName;
				if (isRecursion == true)//递归，获取子文件夹中的文件
					vt_filePath = scanFolder(nextFile, strFilter, vt_filePath, isRecursion);
			}
		}
		else//处理文件
		{
			//判断是否是需要的文件
			if(compareFilter(FindFileData.cFileName, strFilter) == true)
			{
				//获取路径和文件名字
				FilesInFolder fif;
				fif.strFilePath = strFolderPath + "\\" + FindFileData.cFileName;
				fif.strFileName = FindFileData.cFileName;
				vt_filePath.push_back(fif);
			}
		}
		if(!FindNextFile(hFind, &FindFileData))    
			break;
	}
	return vt_filePath;
}

/*-------------------------------------------------------------------------------------------------
特别注意：					此函数有内存溢出。遍历50w的数据，大约有50M的内存没有释放
功能：						获取文件夹中指定的文件信息，返回一个自定义结构体，有递归操作。和scanFolder相比，此函数更快
strFolderPath：				文件夹路径
strFilter：					过滤器，只有后缀（比如".txt"或者"mydoc.txt"）等于strFilter的才筛选出来
vt_FIF：					本次获取的文件信息，递归用，下一次递归操作时，会将正确的信息放到此变量中
isRecursion:				是否递归考虑子文件夹
返回：						所有满足需求的文档的路径和文档名称

-------------------------------------------------------------------------------------------------*/
void C_Folder::scanFolder_faster(string strFolderPath, string strFilter, vector<FilesInFolder>& vt_FIF, bool isRecursion)
{
	WIN32_FIND_DATA FindFileData;

	string strAllFilePath = strFolderPath + "\\*.*";
	string nextFile = "";

	//获取文件夹中的所有文件
	HANDLE hFind = FindFirstFile(strAllFilePath.c_str(), &FindFileData);
	if(INVALID_HANDLE_VALUE == hFind) 
		return;

	while(TRUE)
	{
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//处理文件夹
		{		
			if(FindFileData.cFileName[0] != '.') 
			{
				nextFile = strFolderPath + "\\" +  FindFileData.cFileName;
				if (isRecursion == true)//递归，获取子文件夹中的文件					
					scanFolder_faster(nextFile, strFilter, vt_FIF, isRecursion);
			}
		}
		else//处理文件
		{
			//判断是否是需要的文件
			if(compareFilter(FindFileData.cFileName, strFilter) == true)
			{
				//获取路径和文件名字
				FilesInFolder fif;
				fif.strFilePath = strFolderPath + "\\" + FindFileData.cFileName;
				fif.strFileName = FindFileData.cFileName;
				vt_FIF.push_back(fif);
			}
		}
		if(!FindNextFile(hFind, &FindFileData))    
			break;
	}
}

/*-------------------------------------------------------------------------------------------------
功能：						获取文件夹中文件夹，返回一个自定义结构体，有递归操作
strFolderPath：				文件夹路径
vt_folderName：				本次获取的文件夹信息，递归用，下一次递归操作时，会将正确的信息放到此变量中	
isRecursion：				是否递归考虑子文件夹
返回：						所有满足需求的文件夹

-------------------------------------------------------------------------------------------------*/
vector<string> C_Folder::scanFolder(string strFolderPath, vector<string> vt_folderName, bool isRecursion)
{
	vector<string> vt_folder;
	WIN32_FIND_DATA FindFileData;

	//将上一次递归的有用文件夹放入返回的变量中
	for(int i = 0; i < vt_folderName.size(); i++)
		vt_folder.push_back(vt_folderName[i]);

	string strAllFilePath = strFolderPath + "\\*.*";
	string nextFile = "";

	//获取文件夹中的所有文件
	HANDLE hFind = FindFirstFile(strAllFilePath.c_str(), &FindFileData);
	if(INVALID_HANDLE_VALUE == hFind) 
		return vt_folder;

	while(TRUE)
	{
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//处理文件夹
		{		
			if(FindFileData.cFileName[0] != '.')
			{
				nextFile = strFolderPath + "\\" +  FindFileData.cFileName;
				vt_folder.push_back(nextFile);
				if (isRecursion == true)//递归，获取子文件夹中的文件夹
					vt_folder = scanFolder(nextFile, vt_folder, isRecursion);
			}
		}

		if(!FindNextFile(hFind, &FindFileData))    
			break;
	}
	return vt_folder;
}

/*-------------------------------------------------------------------------------------------------
功能：						判断str1是否和str2的末尾的字符相同，或者判断str2是否和str1的末尾的字符相同
str1：						字符串1
str2：						字符串2	
返回：						是否相同

-------------------------------------------------------------------------------------------------*/
bool C_Folder::compareFilter(string str1, string str2)
{
	int minLen = str1.length() < str2.length() ? str1.length() : str2.length();
	bool isMatch;
	string str1Sub = str1.substr(str1.length() - minLen, minLen);
	string str2Sub = str2.substr(str2.length() - minLen, minLen);
	if(str1Sub == str2Sub) 
		isMatch = true;
	else
		isMatch = false;
	return isMatch;
}

//根据图片路径"D:\Test\2012-04-23_09-02-08_002_DO.jpg"，返回"2012-04-23_09-02-08_002_DO"

string C_Folder::getFileNameFromPath(string filePath, bool isNeedFormat)
{
	int i1 = filePath.rfind("\\");
	string str;
	str = filePath.substr(i1 + 1, filePath.length() - i1);
	if(isNeedFormat == false);
	{
		i1 = str.rfind(".");
		str = str.substr(0, i1);
	}	
	return str;
}

//根据文件路径"D:\Test\2012-04-23_09-02-08_002_DO.jpg"，返回"Test"

string C_Folder::getFolderNameFromPath(string filePath)
{	
	string str = filePath.substr(0, filePath.rfind("\\"));
	str = str.substr(str.rfind("\\") + 1, str.length() - str.rfind("\\"));
	return str;
}

//判断文件是否存在

bool C_Folder::isFileExist(string path)
{
	bool isExist = false;
	WIN32_FIND_DATA FindFolderData;
	HANDLE hFind_folder = FindFirstFile(path.c_str(), &FindFolderData);
	if(INVALID_HANDLE_VALUE == hFind_folder)   
	{				
	}
	else
	{
		isExist = true;
	}
	return isExist;
}

//判断文件夹是否存在，不存在则新建。

bool C_Folder::isFoldeExist(char* folderPath, bool isCreate)
{
	bool isExist = false;
	//判断文件夹是否存在，不存在则新建。
	WIN32_FIND_DATA FindFolderData;
	HANDLE hFind_folder = FindFirstFile(folderPath, &FindFolderData);
	if(INVALID_HANDLE_VALUE == hFind_folder)
	{
		//创建文件夹
		if(isCreate)
			CreateDirectory(folderPath, NULL);
	}
	else
	{
		isExist = true;
	}
	return isExist;
}

/*-------------------------------------------------------------------------------------------------
功能：						将str_src中的文件夹复制到str_dst中，只复制文件夹结构，不复制文件夹中的文件。
str_src：					源文件夹路径
str_dst：					目的文件夹路径
isRecursion：				是否递归
返回：						复制的文件夹数量

-------------------------------------------------------------------------------------------------*/
int C_Folder::creatFolder(string str_src, string str_dst, bool isRecursion)
{
	C_Folder OF;
	vector<string> vt_folder = OF.getFolder(str_src, false);
	if(vt_folder.size() == 0)
		return 0;
	for(int i = 0; i < vt_folder.size(); i++)
	{
		string strFolderName = vt_folder[i].substr(vt_folder[i].rfind("\\") + 1, vt_folder[i].length() - vt_folder[i].rfind("\\"));
		string str_dstFolderPath = str_dst + "\\" + strFolderName;
		char dstFolderPath[300];
		sprintf(dstFolderPath, "%s", str_dstFolderPath.c_str());
		OF.isFoldeExist(dstFolderPath, true);//判断文件夹是否存在，不存在则创建
		if(isRecursion == true)
			creatFolder(vt_folder[i].c_str(), dstFolderPath, isRecursion);
	}
	return vt_folder.size();
}

//复制文件夹source中的所有符合searchChars的数据到文件夹dis中
void C_Folder::copyFolderTo(string source, string dis, string searchChars)
{
	vector<FilesInFolder>* vt_FIF = getFileFromFolder(&source, &searchChars, false);
	for(int i = 0; i < vt_FIF->size() && i < 30; i++)
	{
		string newfilePath = dis + "\\" + (*vt_FIF)[i].strFileName;
		CopyFile((*vt_FIF)[i].strFilePath.c_str(), newfilePath.c_str(), false);
	}
	deleteFilesInFolder(vt_FIF);
}
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