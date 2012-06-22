#include "ItemManager.h"
#include <Windows.h>
ItemManager* ItemManager::instance =0;



bool ItemManager::checkDirectory(char* directoryPath, int & replayNo, int replayId,char * fileName,char * retDirectoryPath)
{
	WIN32_FIND_DATA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	TCHAR *szDir=directoryPath;
	hFind = FindFirstFile(szDir, &ffd);
	fileName[0]=0;
	DWORD creationTime=0;

	char ext[60];
   do
   {

      if ((ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&(!(ffd.dwFileAttributes&FILE_ATTRIBUTE_HIDDEN)) )
      {
		  if (strcmp(ffd.cFileName,".")&&strcmp(ffd.cFileName,".."))
		  {
				char tempDirectory[600];
				strcpy(tempDirectory,szDir);
				tempDirectory[strlen(tempDirectory)-2]=0;
				strcat(tempDirectory,"/");

				strcat(tempDirectory,ffd.cFileName);
				strcat(tempDirectory,"/*");
				if (checkDirectory(tempDirectory,replayNo,replayId,fileName,retDirectoryPath))
				{
					//retDirectoryPath =tempDirectory;
					return true;
				}
		  }
      }
		else
	  {
		int size = strlen( ffd.cFileName);

		if (strcmp(strlwr(ffd.cFileName+size-strlen(".txt")),".txt")==0)
		{

	
				strcpy(fileName,ffd.cFileName);
				strcpy(retDirectoryPath,directoryPath);
				
				char* tempS = new char [500];
				strcpy(tempS,retDirectoryPath);
				tempS[strlen(tempS)-1]=0;
				strcat(tempS,fileName);
				filePaths.push_back(tempS);
				//return true;
			

			replayNo++;
		}
	  }	  
   }
   while (FindNextFile(hFind, &ffd) != 0);
   return false;
}
char * ItemManager::getItems (char * directory)
{
	int replayNo=0;
	char  *fileName = new char[260];
	char directoryPath[600];
	checkDirectory(directory,replayNo,0,fileName,directoryPath);
	CLASS_TYPE ct = UserInput::getInstance()->getClassType();

   if (fileName[0]==0)
   {
	  // delete [] fileName;
	   return 0;
   }
   // printf("Using %s \n",fileName);
	char* tempS = new char [500];
	strcpy(tempS,directoryPath);
	tempS[strlen(tempS)-1]=0;
	strcat(tempS,fileName);
	//delete [] fileName;
    return tempS;
}