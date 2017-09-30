//#include "StdAfx.h"
#include "C_Folder_File.h"
#include <io.h>
#include <direct.h>

void C_Folder_File::getFilesFromFolder(std::string strFolderPath, std::string strFileFilter, bool isRecursion, std::vector<std::string>& vt_str_o)
{
	_finddata_t FileInfo;

	std::string strfind = strFolderPath + "\\*";
	long handle = _findfirst(strfind.c_str(), &FileInfo);

	if (handle == -1L)
		return;

	do{
		//判断是否有子目录
		if (FileInfo.attrib & _A_SUBDIR)    
		{
			//这个语句很重要
			if( (strcmp(FileInfo.name,".") != 0 ) &&(strcmp(FileInfo.name,"..") != 0) && (isRecursion == true))   
			{
				std::string newPath = strFolderPath + "\\" + FileInfo.name;
				getFilesFromFolder(newPath, strFileFilter, isRecursion, vt_str_o);
			}
		}
		else  
		{
			std::string fileName = FileInfo.name;
			if(fileName.length() >= strFileFilter.length())
			{
				fileName = fileName.substr(fileName.length() - strFileFilter.length(), strFileFilter.length());
				if(fileName == strFileFilter)
					vt_str_o.push_back(strFolderPath + "\\" + FileInfo.name);
			}
		}
			
	}while (_findnext(handle, &FileInfo) == 0);
	_findclose(handle);
}


std::string C_Folder_File::getFileNameFromPath(std::string filePath, bool isNeedFilter)
{
	std::string fileName = filePath.substr(filePath.find_last_of("\\") + 1, filePath.length() - filePath.find_last_of("\\") - 1);
	if(isNeedFilter == true)
		return fileName;
	else
		fileName = fileName.substr(0, fileName.find_last_of("."));
	return fileName;
}


void C_Folder_File::getFoldersFormDisk(std::string strFolderPath, bool isRecursion, std::vector<std::string>& vt_strFolder_o)
{
	_finddata_t FileInfo;

	std::string strfind = strFolderPath + "\\*";
	long handle = _findfirst(strfind.c_str(), &FileInfo);

	if (handle == -1L)
		return;

	do{
		//判断是否有子目录
		if (FileInfo.attrib & _A_SUBDIR)    
		{
			//这个语句很重要
			std::string folderPath;
			if( (strcmp(FileInfo.name,".") != 0 ) &&(strcmp(FileInfo.name,"..") != 0))
			{
				folderPath = strFolderPath + "\\" + FileInfo.name;
				vt_strFolder_o.push_back(folderPath);

				if(isRecursion == true)
					getFoldersFormDisk(folderPath, isRecursion, vt_strFolder_o);
			}


		}
	}while (_findnext(handle, &FileInfo) == 0);
	_findclose(handle);
}

int C_Folder_File::getFolders(std::string strFolderPath, bool isRecursion, std::vector<std::string>& vt_strFolder_o)
{
	int maxCount = 20;

	int maxFolderLevelCount = 0;
	getFoldersFormDisk(strFolderPath, isRecursion, vt_strFolder_o);
	if(maxCount > vt_strFolder_o.size())
		maxCount = vt_strFolder_o.size();

	for(int i = 0; i < maxCount; i++)
	{
		std::vector<std::string> vt_element = splitString(vt_strFolder_o[i], "\\");
		if(maxFolderLevelCount < vt_element.size())
			maxFolderLevelCount = vt_element.size();
	}	
	return maxFolderLevelCount;
}

std::vector<std::string> C_Folder_File::splitString(std::string in, std::string delimiters)
{
	std::vector<std::string> ret;
	int iLen = in.length();
	if (iLen == 0){
		return ret;
	}	
	char *buffer = new char[iLen + 1];
	strcpy(buffer,in.c_str());

	char * token = strtok( buffer, delimiters.c_str() );
	while( token != NULL ){
		ret.push_back(token);	

		token = strtok( NULL, delimiters.c_str());
	}	
	delete []buffer;
	return ret;
}

std::string C_Folder_File::getFolderNameFromFilePath(std::string filePath)
{
	std::string str_rt = "";
	std::vector<std::string> vt_str = splitString(filePath, "\\");
	if(vt_str.size() >= 2)
		str_rt = vt_str[vt_str.size() - 2];
	return str_rt;
}

bool C_Folder_File::isFileExist(std::string filePath)
{
	if(_access(filePath.c_str(), 0) == -1)
		return false;
	else
		return true;
}

bool C_Folder_File::isFolderExist(std::string folderPath, bool isCreate)
{
	bool isExist;
	if(_access(folderPath.c_str(), 0) == -1)
	{
		isExist = false;
		if(isCreate == true)
			_mkdir(folderPath.c_str());
	}
	else
		isExist = true;
	return isExist;
}

int C_Folder_File::CopyFile(std::string src, std::string dst)
{
	const int BUF_SIZE = 256;
	FILE *in_file, *out_file;
	char data[BUF_SIZE];
	size_t bytes_in, bytes_out;
	long len = 0;

	if ( (in_file = fopen(src.c_str(), "rb")) == NULL )
		return 1;
	if ( (out_file = fopen(dst.c_str(), "wb")) == NULL )
		return 2;

	while ( (bytes_in = fread(data, 1, BUF_SIZE, in_file)) > 0 )
	{
		bytes_out = fwrite(data, 1, bytes_in, out_file);
		if ( bytes_in != bytes_out )
			return 3;
		len += bytes_out;
	}

	fclose(in_file);
	fclose(out_file);

	return 0;
}

int C_Folder_File::getMaxFolderLevel(std::vector<std::string>& vt_strFolders)
{
	int folderMaxLevel = 50;
	if(vt_strFolders.size() < folderMaxLevel)
		folderMaxLevel = vt_strFolders.size();

	int maxCount = 0;
	for(int i = 0; i < folderMaxLevel; i++)
	{
		std::vector<std::string> vt_strSplit = splitString(vt_strFolders[i], "\\");		
		if(vt_strSplit.size() > maxCount)
			maxCount = vt_strSplit.size();
	}
	return maxCount;
}