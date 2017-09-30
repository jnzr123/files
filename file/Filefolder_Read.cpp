#include "Filefolder_Read.h"
#include "C_Folder_File.h"
#include <direct.h>
#include <io.h>
#include <iostream>

vector<std::string> BrowseFilenamesOneLayer(const char* dir, const char *filespec)
{
	vector<std::string> fileVec;

	_chdir(dir);
	_finddata_t fileInfo;
	//long lfDir=0;
	intptr_t  lfDir;
	
	fileVec.clear();

	if ((lfDir = _findfirst(filespec, &fileInfo)) == -1)
		cout << "No file is found" << endl;
	else
	{
		do
		{
			char filename[_MAX_PATH];
			strcpy_s(filename, dir);
			strcat_s(filename, "/");
			strcat_s(filename, fileInfo.name);

			fileVec.push_back(filename);
			//cout << "name=" << filename << endl;
		} while (_findnext(lfDir, &fileInfo) == 0);
	}
	_findclose(lfDir);

	return fileVec;
}