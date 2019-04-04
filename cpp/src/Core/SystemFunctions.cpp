/**
* @file SystemFunction.cpp
* @author Spencer Hoffa
*
* @copyright 2017 Spencer Hoffa
*
* Common system functions.
*/
/*
* The zlib/libpng License
*
* Copyright (c) 2017 Spencer Hoffa
*
* This software is provided 'as-is', without any express or implied warranty.
* In no event will the authors be held liable for any damages arising from the
* use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
*		1. The origin of this software must not be misrepresented; you must not
*		claim that you wrote the original software. If you use this software in
*		a product, an acknowledgment in the product documentation would be
*		appreciated but is not required.
*
*		2. Altered source versions must be plainly marked as such, and must not
*		be misrepresented as being the original software.
*
*		3. This notice may not be removed or altered from any source
*		distribution.
*
* This liscense can also be found at: http://opensource.org/licenses/Zlib
*/

#include "XneloUtils/Config.hpp"
#include "XneloUtils/Core/SystemFunctions.hpp"

#if PLATFORM == XNELO_PLATFORM_WINDOWS
	#include "XneloUtils\Core\Windows\dirent.h"
	#include <Shlwapi.h>
	#pragma comment(lib, "Shlwapi.lib")
#else
	#include <cstring>
	#include <dirent.h>
#endif

#include <iostream>

namespace XNELO
{
	namespace CORE
	{
		std::string GetExtension(std::string filePath)
		{
#if PLATFORM == XNELO_PLATFORM_WINDOWS
			PTSTR extBegin = PathFindExtension(filePath.c_str());
			if (extBegin[0] == '.')
				return std::string(extBegin);
			else
				return std::string("");
#else //linux
			std::size_t pos = filePath.rfind('.');

			if (pos != std::string::npos &&
				pos != 0 &&
				(filePath[pos - 1] != '/' || filePath[pos - 1] != '\\'))
			{
				return filePath.substr(pos);
			}
			else
			{
				return std::string("");
			}
#endif
		}

		std::vector<std::string> GetFiles(const char * directory, bool recursive)
		{
			std::vector<std::string> foundFiles;
#if PLATFORM == XNELO_PLATFORM_WINDOWS
			DIR * dir;
			struct dirent * ent;
			if ((dir = opendir(directory)) != NULL)
			{
				while((ent = readdir(dir)) != NULL)
				{
					if ((strcmp(ent->d_name, ".") == 0) ||
						(strcmp(ent->d_name, "..") == 0))
					{
						continue;
					}

					std::string newPath(directory);
					newPath += "\\";
					newPath += ent->d_name;

					if (recursive && (ent->data.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY))
					{
						//std::string newDir(directory);
						//newDir += "\\";
						//newDir += ent->d_name;
						//GetFiles(newDir.c_str(), recursive);
						std::vector<std::string> recFiles = GetFiles(newPath.c_str(), recursive);
						for (unsigned int i = 0; i < recFiles.size(); i++)
						{
							foundFiles.push_back(recFiles[i]);
						}
					}
					else
					{
						foundFiles.push_back(newPath);
					}
				}

				closedir(dir);
			}
			else
			{ }
#endif
			return foundFiles;
		}

		std::vector<std::string> GetFilesWithExtension(const char * directory, bool recursive, const char * extension)
		{
			std::vector<std::string> returnedFiles = GetFiles(directory, recursive);
			std::vector<std::string> answer;

			for (unsigned int i = 0; i < returnedFiles.size(); ++i)
			{
				std::string ext = GetExtension(std::string(returnedFiles[i]));
				if (std::strcmp(ext.c_str(), extension) == 0)
				{
					answer.push_back(returnedFiles[i]);
				}
			}

			return answer;
		}
	}//end namespace CORE
}//end namespace XNELO
